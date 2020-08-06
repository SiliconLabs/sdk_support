/***************************************************************************//**
 * @file
 * @brief  EFM internal SPI Protocol implementation
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include PLATFORM_HEADER
#include "stack/include/ember.h"
#include "hal/hal.h"
#include "serial/serial.h"
#include "hal/micro/cortexm3/spi-protocol.h"
#include "spidrv.h"
#include "em_gpio.h"
#include "gpiointerrupt.h"
#include "hal/micro/cortexm3/efm32/spi-protocol-device.h"

uint8_t halHostBuffer[SPIP_BUFFER_SIZE];
uint8_t spipErrorResponseBuffer[SPIP_ERROR_RESPONSE_SIZE];
//Provide easy references the buffers for EZSP
uint8_t *halHostFrame = halHostBuffer + EZSP_LENGTH_INDEX;

// legacy support
bool spipFlagWakeFallingEdge;  //flag for detecting a falling edge on nWAKE

struct {
  volatile enum { spipNcpIdle = 0,    \
                  spipNcpCommand = 1, \
                  spipNcpWait = 2,    \
                  spipNcpResponse = 3} state;
  bool overrideResponse;      //flag for indicating errors or SPIP boot
  bool wakeup;                //flag for detecting a falling edge on nWAKE
  bool idleHostInt;           //flag for idling nHOST_INT at proper time
  uint8_t responseLength; //The true length of the Response Section
} spipNcpState;

static SPIDRV_HandleData_t spiHandleData;
static SPIDRV_Handle_t spiHandle = &spiHandleData;

static bool halInternalHostSerialTick(bool responseReady);
static void nSSEL_ISR(uint8_t pin);
static void nWAKE_ISR(uint8_t pin);
static void processSpipCommandAndRespond(uint8_t spipResponse);
static void setSpipErrorBuffer(uint8_t spiByte);
static void spiTxCallback(SPIDRV_Handle_t handle,
                          Ecode_t transferStatus,
                          int itemsTransferred);
static void wipeAndRestartSpi(void);

void halHostCallback(bool haveData)
{
  if (haveData) {
    //only assert nHOST_INT if we are outside a wake handshake (wake==1)
    //and outside of a current transaction (nSSEL=1)
    //if inside a wake handshake or transaction, delay asserting nHOST_INT
    //until the SerialTick
    if ( nWAKE_IS_NEGATED() && nSSEL_IS_NEGATED() ) {
      CLR_nHOST_INT();
    }
    spipNcpState.idleHostInt = false;
  } else {
    spipNcpState.idleHostInt = true;
  }
}

bool halHostSerialBusy(void)
{
  return ((nSSEL_IS_ASSERTED()) || (spipNcpState.state >= spipNcpWait));
}

void halHostSerialInit(void)
{
  ////---- Initialize Flags ----////
  spipFlagWakeFallingEdge = false; //start with no edge on nWAKE
  spipNcpState.idleHostInt = true; //idle nHOST_INT after telling host we booted
  //load error response buffer with the "EM260 Reset" message + reset cause
  //we do not use the setSpipErrorBuffer() function here since that function
  //assumes the second byte in the buffer is reserved (0)
  spipNcpState.overrideResponse = true; //set a flag indicating we just booted
  spipErrorResponseBuffer[0] = SPIP_RESET;
  spipErrorResponseBuffer[1] = halGetEm2xxResetInfo(); //inject reset cause
  spipNcpState.responseLength = 0;           //default length of zero

  halHostSerialPowerup();
}

void halHostSerialPowerup(void)
{
  //---- Configure SPI ----//
  wipeAndRestartSpi();

  // Initialize nHOST_INT as output
  GPIO_PinModeSet(BSP_SPINCP_NHOSTINT_PORT,
                  BSP_SPINCP_NHOSTINT_PIN,
                  gpioModePushPull,
                  1);

  GPIOINT_Init();

  #if (!defined(DISABLE_NWAKE)) && (!defined(HAL_CONFIG) || defined(BSP_SPINCP_NWAKE_PIN))
  // Initialize nWAKE as input with falling edge interrupt
  GPIO_IntDisable(1 << BSP_SPINCP_NWAKE_PIN);
  GPIO_PinModeSet(BSP_SPINCP_NWAKE_PORT,
                  BSP_SPINCP_NWAKE_PIN,
                  gpioModeInputPullFilter,
                  1);
  GPIO_IntConfig(BSP_SPINCP_NWAKE_PORT,
                 BSP_SPINCP_NWAKE_PIN,
                 false,
                 true,
                 true);
  GPIOINT_CallbackRegister(BSP_SPINCP_NWAKE_PIN, nWAKE_ISR);
  #endif

  // Initialize nSSEL as input with rising/falling edge interrupts
  GPIO_IntDisable(1 << SPI_NCP_CS_PIN);
  GPIO_PinModeSet(SPI_NCP_CS_PORT, SPI_NCP_CS_PIN, gpioModeInputPullFilter, 1);
  GPIO_IntConfig(SPI_NCP_CS_PORT, SPI_NCP_CS_PIN, true, true, true);
  GPIOINT_CallbackRegister(SPI_NCP_CS_PIN, nSSEL_ISR);

  // ----- Account for Noise and Crosstalk ------ //
  // on some hardware configurations there is a lot of noise and bootloading can fail
  // due to crosstalk. to avoid this, the slewrate is lowered here from 6 to 4, and the
  // drivestrength is lowered from 10mA to 1mA. if noise related errors still occur,
  // the slewrate can be lowered further
  GPIO_SlewrateSet(BSP_SPINCP_NHOSTINT_PORT, 4, 4);
  // the drivestrength is lowered from 10mA to 1mA by setting DRIVESTRENGTH to 1
#if defined (_GPIO_P_CTRL_DRIVEMODE_MASK)
  GPIO_DriveStrengthSet(BSP_SPINCP_NHOSTINT_PORT, 1);
#endif
}

void halHostSerialPowerdown(void)
{
  //we need to block (interrupts are off), until transmission is done
  while (nSSEL_IS_ASSERTED()) {
    halResetWatchdog();
  }
}

bool halHostSerialTick(bool responseReady)
{
  bool validCommand;
  //Processing a potential premature nSSEL deactivation inside of the Tick
  //function will generate a lot of strange conditions that are best prevented
  //insteaded of handled.
  //Normal calls to halInternalHostSerialTick are <10us.  Worst case is <30us.
  {
    DECLARE_INTERRUPT_STATE;
    DISABLE_INTERRUPTS();
    validCommand = halInternalHostSerialTick(responseReady);
    RESTORE_INTERRUPTS();
  }
  return validCommand;
}

void halNcpClearWakeFlag(void)
{
  spipFlagWakeFallingEdge = false;
}

//One layer of indirection is used so calling the public function will actually
//result in the real Tick function (this internal one) being wrapped between a
//DISABLE_INTERRUPTS() and RESTORE_INTERRUPTS() to prevent potential corruption
//from the nSSEL interrupt.
static int itemsTransferred, itemsRemaining;
static bool halInternalHostSerialTick(bool responseReady)
{
  if (spipNcpState.overrideResponse && nSSEL_IS_NEGATED()) {
    CLR_nHOST_INT();
  }
  switch (spipNcpState.state) {
    case spipNcpIdle:
      itemsTransferred = 0;
      itemsRemaining = 0;
      if (spipNcpState.wakeup) {
        CLR_nHOST_INT();
        while ( nWAKE_IS_ASSERTED() ) {
          halResetWatchdog();
        }
        SET_nHOST_INT();
        spipNcpState.wakeup = false;
        //The wake handshake is complete, but spipFlagIdleHostInt is saying
        //that there is a callback pending.
        if (!spipNcpState.idleHostInt) {
          halCommonDelayMicroseconds(50); //delay 50us so Host can get ready
          //indicate the pending callback
          CLR_nHOST_INT();
        }
      }

      if (spiHandle->state == spidrvStateIdle) {
        SPIDRV_SReceive(spiHandle,
                        halHostBuffer,
                        SPIP_BUFFER_SIZE,
                        NULL,
                        SPI_NCP_TIMEOUT);
        break;
      } else if (nSSEL_IS_ASSERTED()) {
        SET_nHOST_INT();
        spipNcpState.state = spipNcpCommand;
        // fall through to the spiNcpCommand case immediately
      } else {
        break;
      }
    case spipNcpCommand:
      SPIDRV_GetTransferStatus(spiHandle, &itemsTransferred, &itemsRemaining);
      if (itemsTransferred > 1) {
        SET_nHOST_INT();
        switch (halHostBuffer[0]) {
          case 0x0A:
            // Transition state to wait for TX buffer ready
            spipNcpState.state = spipNcpWait;
            processSpipCommandAndRespond(SPIP_VERSION);
            break;
          case 0x0B:
            // Transition state to wait for TX buffer ready
            spipNcpState.state = spipNcpWait;
            processSpipCommandAndRespond(SPIP_ALIVE);
            break;
          case 0xFD: //The Command is a Bootloader Frame
          //Fall into EZSP Frame since processing the rest of the command is
          //the same. The only difference is responding with the Unsupported
          //SPI Command error
          case 0xFE: //The Command is an EZSP Frame
            if (halHostBuffer[1] > MAX_PAYLOAD_FRAME_LENGTH) {
              wipeAndRestartSpi();
              setSpipErrorBuffer(SPIP_OVERSIZED_EZSP);
              return false; //dump! (interrupt flags are cleared above)
            } else if (itemsTransferred >= halHostBuffer[1] + 3) {
              // Transition state to wait for TX buffer ready
              spipNcpState.state = spipNcpWait;
              //check for Frame Terminator, it must be there!
              if (spipNcpState.overrideResponse) {
                halInternalHostSerialTick(true); //respond immediately!
                return false; //we overrode the command
              } else if (halHostBuffer[halHostBuffer[1] + 2]
                         != FRAME_TERMINATOR) {
                //no frame terminator found!  report missing F.T.
                setSpipErrorBuffer(SPIP_MISSING_FT);
                halInternalHostSerialTick(true); //respond immediately!
                return false; //we overrode the command
              } else if (halHostBuffer[0] == 0xFD) {
                //load error response buffer with Unsupported SPI Command error
                setSpipErrorBuffer(SPIP_UNSUPPORTED_COMMAND);
                halInternalHostSerialTick(true); //respond immediately!
                return false; //we overrode the command
              } else {
                halHostBuffer[0] = 0xFE; //mark the response EZSP Frame
                return true; //there is a valid command
              }
            }

          default:
            break;
        }
      }
      break;
    case spipNcpWait:
      if (spipNcpState.idleHostInt) {
        //the nHOST_INT signal can be asynchronously
        SET_nHOST_INT();
      }
      if (responseReady == true) {
        if (spipNcpState.overrideResponse) {
          spipNcpState.overrideResponse = false; //we no longer need to override
          //override whatever was sent with the error response message
          MEMCOPY(halHostBuffer,
                  spipErrorResponseBuffer,
                  SPIP_ERROR_RESPONSE_SIZE);
        }
        //add Frame Terminator and record true Response length
        if ( halHostBuffer[0] < 0x05 ) {
          halHostBuffer[1 + 1] = FRAME_TERMINATOR;
          spipNcpState.responseLength = 3;  //true Response length
        } else if ((halHostBuffer[0] == 0xFE) //EZSP Payload
                   || (halHostBuffer[0] == 0xFD)) { //Bootloader Payload
          //guard against oversized messages which could cause serious problems
          assert(halHostBuffer[1] <= MAX_PAYLOAD_FRAME_LENGTH);
          halHostBuffer[halHostBuffer[1] + 1 + 1] = FRAME_TERMINATOR;
          halHostBuffer[halHostBuffer[1] + 1 + 2] = 0xFF; // pad so MISO stays high
          spipNcpState.responseLength = halHostBuffer[1] + 3; //true Response length
        } else {
          halHostBuffer[1] = FRAME_TERMINATOR;
          spipNcpState.responseLength = 2;  //true Response length
        }

        SPIDRV_AbortTransfer(spiHandle);
        Ecode_t val = SPIDRV_STransmit(spiHandle,
                                       halHostBuffer,
                                       spipNcpState.responseLength,
                                       spiTxCallback,
                                       SPI_NCP_TIMEOUT);
        CLR_nHOST_INT();
        spipNcpState.state = spipNcpResponse;
      }
      break;
    case spipNcpResponse:
      SPIDRV_GetTransferStatus(spiHandle, &itemsTransferred, &itemsRemaining);
      // deassert nHOST_INT once a byte has been received;
      if (itemsTransferred > 0) {
        SET_nHOST_INT();
      }
      break;
    default:
      break;
  }
  return false;
}

// nSSEL signal (rising edge-triggered)
static void nSSEL_ISR(uint8_t pin)
{
  if (nSSEL_IS_ASSERTED()) {
    return;
  }
  // Rising edge of SS means the host is no longer receiving SPI transfers
  // Abort the transfer, triggering the callback which will reset the state of
  // the spi protocol
  if (spipNcpState.state == spipNcpResponse) {
    SPIDRV_AbortTransfer(spiHandle);
  }
  // Reset back to idle state
  spipNcpState.state = spipNcpIdle;

  if (!spipNcpState.idleHostInt) {
    //we still have more to tell the Host
    CLR_nHOST_INT();
  }
  SPIDRV_SReceive(spiHandle,
                  halHostBuffer,
                  SPIP_BUFFER_SIZE,
                  NULL,
                  SPI_NCP_TIMEOUT);
  halInternalHostSerialTick(false);
}

// nWAKE signal (falling edge-triggered)
static void nWAKE_ISR(uint8_t pin)
{
  spipNcpState.wakeup = true;
  spipFlagWakeFallingEdge = true;
}

static void processSpipCommandAndRespond(uint8_t spipResponse)
{
  // Disable reception while processing
  SPIDRV_AbortTransfer(spiHandle);
  //check for Frame Terminator, it must be there!
  if (halHostBuffer[1] == FRAME_TERMINATOR) {
    //override with the supplied spipResponse
    halHostBuffer[0] = spipResponse;
  } else {
    //no frame terminator found!  report missing F.T.
    setSpipErrorBuffer(SPIP_MISSING_FT);
  }
  halInternalHostSerialTick(true); //respond immediately!
}

static void setSpipErrorBuffer(uint8_t spiByte)
{
  if (!spipNcpState.overrideResponse) {
    //load error response buffer with the error supplied in spiByte
    spipNcpState.overrideResponse = true;      //set a flag indicating override
    spipErrorResponseBuffer[0] = spiByte; //set the SPI Byte with the error
    spipErrorResponseBuffer[1] = 0;       //this byte is currently reserved
  }
}

static void spiTxCallback(SPIDRV_Handle_t handle,
                          Ecode_t transferStatus,
                          int itemsTransferred)
{
  // make sure nHOST_INT was idled in case response/send was faster than tick
  SET_nHOST_INT();
  //if we have not sent the exact right number of bytes, Transaction is corrupt
  if ((itemsTransferred != spipNcpState.responseLength)) {
    setSpipErrorBuffer(SPIP_ABORTED_TRANSACTION);
  }
}
static void wipeAndRestartSpi(void)
{
  // Deinitialize SPI driver
  SPIDRV_DeInit(spiHandle);

  SPIDRV_Init_t initData = SPI_NCP_USART_INIT;

  // Initialize a SPI driver instance
  SPIDRV_Init(spiHandle, &initData);
}
