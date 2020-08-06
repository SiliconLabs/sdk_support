/***************************************************************************//**
 * @file
 * @brief EM3XX-specific diagnostic HAL functions
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
#include "diagnostic.h"
#include "hal/micro/cortexm3/mpu.h"

#ifdef RTOS
  #include "rtos/rtos.h"
  #define freeRTOS 1
#else  // RTOS
  #define freeRTOS 0
// extern uint32_t* xTaskGetCurrentTaskStackTop(void);
// extern uint32_t* xTaskGetCurrentTaskStackBottom(void);
#endif // RTOS

//------------------------------------------------------------------------------
// Register bit definitions taken from CMSIS-CORE v5.00

/* MemManage Fault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_MMARVALID_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 7U)               /*!< SCB CFSR (MMFSR): MMARVALID Position */
#define SCB_CFSR_MMARVALID_Msk             (1UL << SCB_CFSR_MMARVALID_Pos)                /*!< SCB CFSR (MMFSR): MMARVALID Mask */

#define SCB_CFSR_MSTKERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 4U)               /*!< SCB CFSR (MMFSR): MSTKERR Position */
#define SCB_CFSR_MSTKERR_Msk               (1UL << SCB_CFSR_MSTKERR_Pos)                  /*!< SCB CFSR (MMFSR): MSTKERR Mask */

#define SCB_CFSR_MUNSTKERR_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 3U)               /*!< SCB CFSR (MMFSR): MUNSTKERR Position */
#define SCB_CFSR_MUNSTKERR_Msk             (1UL << SCB_CFSR_MUNSTKERR_Pos)                /*!< SCB CFSR (MMFSR): MUNSTKERR Mask */

#define SCB_CFSR_DACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 1U)               /*!< SCB CFSR (MMFSR): DACCVIOL Position */
#define SCB_CFSR_DACCVIOL_Msk              (1UL << SCB_CFSR_DACCVIOL_Pos)                 /*!< SCB CFSR (MMFSR): DACCVIOL Mask */

#define SCB_CFSR_IACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 0U)               /*!< SCB CFSR (MMFSR): IACCVIOL Position */
#define SCB_CFSR_IACCVIOL_Msk              (1UL /*<< SCB_CFSR_IACCVIOL_Pos*/)             /*!< SCB CFSR (MMFSR): IACCVIOL Mask */

/* BusFault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_BFARVALID_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 7U)                  /*!< SCB CFSR (BFSR): BFARVALID Position */
#define SCB_CFSR_BFARVALID_Msk            (1UL << SCB_CFSR_BFARVALID_Pos)                 /*!< SCB CFSR (BFSR): BFARVALID Mask */

#define SCB_CFSR_STKERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 4U)                  /*!< SCB CFSR (BFSR): STKERR Position */
#define SCB_CFSR_STKERR_Msk               (1UL << SCB_CFSR_STKERR_Pos)                    /*!< SCB CFSR (BFSR): STKERR Mask */

#define SCB_CFSR_UNSTKERR_Pos             (SCB_CFSR_BUSFAULTSR_Pos + 3U)                  /*!< SCB CFSR (BFSR): UNSTKERR Position */
#define SCB_CFSR_UNSTKERR_Msk             (1UL << SCB_CFSR_UNSTKERR_Pos)                  /*!< SCB CFSR (BFSR): UNSTKERR Mask */

#define SCB_CFSR_IMPRECISERR_Pos          (SCB_CFSR_BUSFAULTSR_Pos + 2U)                  /*!< SCB CFSR (BFSR): IMPRECISERR Position */
#define SCB_CFSR_IMPRECISERR_Msk          (1UL << SCB_CFSR_IMPRECISERR_Pos)               /*!< SCB CFSR (BFSR): IMPRECISERR Mask */

#define SCB_CFSR_PRECISERR_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 1U)                  /*!< SCB CFSR (BFSR): PRECISERR Position */
#define SCB_CFSR_PRECISERR_Msk            (1UL << SCB_CFSR_PRECISERR_Pos)                 /*!< SCB CFSR (BFSR): PRECISERR Mask */

#define SCB_CFSR_IBUSERR_Pos              (SCB_CFSR_BUSFAULTSR_Pos + 0U)                  /*!< SCB CFSR (BFSR): IBUSERR Position */
#define SCB_CFSR_IBUSERR_Msk              (1UL << SCB_CFSR_IBUSERR_Pos)                   /*!< SCB CFSR (BFSR): IBUSERR Mask */

/* UsageFault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_DIVBYZERO_Pos            (SCB_CFSR_USGFAULTSR_Pos + 9U)                  /*!< SCB CFSR (UFSR): DIVBYZERO Position */
#define SCB_CFSR_DIVBYZERO_Msk            (1UL << SCB_CFSR_DIVBYZERO_Pos)                 /*!< SCB CFSR (UFSR): DIVBYZERO Mask */

#define SCB_CFSR_UNALIGNED_Pos            (SCB_CFSR_USGFAULTSR_Pos + 8U)                  /*!< SCB CFSR (UFSR): UNALIGNED Position */
#define SCB_CFSR_UNALIGNED_Msk            (1UL << SCB_CFSR_UNALIGNED_Pos)                 /*!< SCB CFSR (UFSR): UNALIGNED Mask */

#define SCB_CFSR_NOCP_Pos                 (SCB_CFSR_USGFAULTSR_Pos + 3U)                  /*!< SCB CFSR (UFSR): NOCP Position */
#define SCB_CFSR_NOCP_Msk                 (1UL << SCB_CFSR_NOCP_Pos)                      /*!< SCB CFSR (UFSR): NOCP Mask */

#define SCB_CFSR_INVPC_Pos                (SCB_CFSR_USGFAULTSR_Pos + 2U)                  /*!< SCB CFSR (UFSR): INVPC Position */
#define SCB_CFSR_INVPC_Msk                (1UL << SCB_CFSR_INVPC_Pos)                     /*!< SCB CFSR (UFSR): INVPC Mask */

#define SCB_CFSR_INVSTATE_Pos             (SCB_CFSR_USGFAULTSR_Pos + 1U)                  /*!< SCB CFSR (UFSR): INVSTATE Position */
#define SCB_CFSR_INVSTATE_Msk             (1UL << SCB_CFSR_INVSTATE_Pos)                  /*!< SCB CFSR (UFSR): INVSTATE Mask */

#define SCB_CFSR_UNDEFINSTR_Pos           (SCB_CFSR_USGFAULTSR_Pos + 0U)                  /*!< SCB CFSR (UFSR): UNDEFINSTR Position */
#define SCB_CFSR_UNDEFINSTR_Msk           (1UL << SCB_CFSR_UNDEFINSTR_Pos)                /*!< SCB CFSR (UFSR): UNDEFINSTR Mask */

//------------------------------------------------------------------------------
// Register bit definitions specific to the whole em3xx suite of devices.

/* SCB Auxiliary Fault Status Register (implementation defined)*/
#define SCB_AFSR_WRONGSIZE_Pos            3U
#define SCB_AFSR_WRONGSIZE_Msk            (1UL << SCB_AFSR_WRONGSIZE_Pos)

#define SCB_AFSR_PROTECTED_Pos            2U
#define SCB_AFSR_PROTECTED_Msk            (1UL << SCB_AFSR_PROTECTED_Pos)

#define SCB_AFSR_RESERVED_Pos             1U
#define SCB_AFSR_RESERVED_Msk             (1UL << SCB_AFSR_RESERVED_Pos)

#define SCB_AFSR_MISSED_Pos               0U
#define SCB_AFSR_MISSED_Msk               (1UL /*<< SCB_AFSR_MISSED_Pos*/)

//------------------------------------------------------------------------------
// Preprocessor definitions

// Reserved instruction executed after a failed assert to cause a usage fault
#define ASSERT_USAGE_OPCODE 0xDE42

// Codes for DMA channels in DMA_PROT_CH
#define DMA_PROT_CH_SC1_RX    1
#define DMA_PROT_CH_GP_ADC    3
#define DMA_PROT_CH_MAC       4
#define DMA_PROT_CH_SC2_RX    5

//------------------------------------------------------------------------------
// Local Variables

static PGM_P PGM cfsrBits[] =
{
  // Memory management (MPU) faults
  "IACCVIOL: attempted instruction fetch from a no-execute address",  // B0
  "DACCVIOL: attempted load or store at an illegal address",          // B1
  "",                                                                 // B2
  "MUNSTKERR: unstack from exception return caused access violation", // B3
  "MSTKERR: stacking from exception caused access violation",         // B4
  "",                                                                 // B5
  "",                                                                 // B6
  "MMARVALID: MMAR contains valid fault address",                     // B7

  // Bus faults
  "IBUSERR: instruction prefetch caused bus fault",                   // B8
  "PRECISERR: precise data bus fault",                                // B9
  "IMPRECISERR: imprecise data bus fault",                            // B10
  "UNSTKERR: unstacking on exception return caused data bus fault",   // B11
  "STKERR: stacking on exception entry caused data bus fault",        // B12
  "",                                                                 // B13
  "",                                                                 // B14
  "BFARVALID: BFAR contains valid fault address",                     // B15

  // Usage faults
  "UNDEFINSTR: tried to execute an undefined instruction",            // B16
  "INVSTATE: invalid EPSR - e.g., tried to switch to ARM mode",       // B17
  "INVPC: exception return integrity checks failed",                  // B18
  "NOCP: attempted to execute a coprocessor instruction",             // B19
  "",                                                                 // B20
  "",                                                                 // B21
  "",                                                                 // B22
  "",                                                                 // B23
  "UNALIGNED: attempted an unaligned memory access",                  // B24
  "DIVBYZERO: attempted to execute SDIV or UDIV with divisor of 0"    // B25
};

static PGM_P PGM afsrBits[] =
{
  "",                                                                 // B0
  "RESERVED: attempted access past last peripheral register address", // B1
  "PROTECTED: attempted user mode write to privileged peripheral",    // B2
  "WRONGSIZE: attempted 8/16-bit access to peripheral register"       // B3
};

static PGM_P PGM intActiveBits[] =
{
  "Timer1",       // B0
  "Timer2",       // B1
  "Management",   // B2
  "Baseband",     // B3
  "Sleep_Timer",  // B4
  "SC1",          // B5
  "SC2",          // B6
  "Security",     // B7
  "MAC_Timer",    // B8
  "MAC_TX",       // B9
  "MAC_RX",       // B10
  "ADC",          // B11
  "IRQ_A",        // B12
  "IRQ_B",        // B13
  "IRQ_C",        // B14
  "IRQ_D",        // B15
  "Debug"         // B16
};

// Names of raw crash data items - each name is null terminated, and the
// end of the array is flagged by two null bytes in a row.
// NOTE: the order of these names must match HalCrashInfoType members.
static const char nameStrings[] = "R0\0R1\0R2\0R3\0"
                                  "R4\0R5\0R6\0R7\0"
                                  "R8\0R9\0R10\0R11\0"
                                  "R12\0R13(LR)\0MSP\0PSP\0"
                                  "PC\0xPSR\0MSP used\0PSP used\0"
                                  "CSTACK bottom\0ICSR\0SHCSR\0INT_ACTIVE\0"
                                  "CFSR\0HFSR\0DFSR\0MMAR/BFAR\0AFSR\0"
                                  "Ret0\0Ret1\0Ret2\0Ret3\0"
                                  "Ret4\0Ret5\0Dat0\0Dat1\0";

//------------------------------------------------------------------------------
// Forward Declarations

//------------------------------------------------------------------------------
// Functions

void halPrintCrashSummary(uint8_t port)
{
  HalCrashInfoType *c = &halResetInfo.crash;
  uint32_t sp, stackBegin, stackEnd, size, used;
  uint16_t pct;
  uint8_t *mode;
  const char *stack;
  uint8_t bit;

  if ((c->LR & 4u) != 0u) {
    stack = "process";
    sp = c->processSP;
    used = c->processSPUsed;
    stackBegin = c->processSP;
    stackEnd = c->processSP;
  } else {
    stack = "main";
    sp = c->mainSP;
    used = c->mainSPUsed;
    stackBegin = (uint32_t)c->mainStackBottom;
    stackEnd = (uint32_t)(uint32_t *)_CSTACK_SEGMENT_END;
  }

  mode = (uint8_t *)(((c->LR & 8u) != 0u) ? "Thread" : "Handler");
  size = stackEnd - stackBegin;
  pct = (uint16_t) (size != 0u
                    ? ((100u * used) + (size / 2u)) / size
                    : 0u);
  (void) emberSerialPrintfLine(port,
                               "%p mode using %p stack (%4x to %4x), SP = %4x",
                               mode, stack, stackBegin, stackEnd, sp);
  (void) emberSerialPrintfLine(port,
                               "%u bytes used (%u%%) in %p stack"
                               " (out of %u bytes total)",
                               (uint16_t)used, pct, stack, (uint16_t)size);
  if ( ((c->LR & 4u) == 0u)
       && (used == size - 4u * RESETINFO_WORDS)
       && (c->mainStackBottom < (uint32_t) (uint32_t *)_RESETINFO_SEGMENT_END)) {
    // Here the stack overlaps the RESETINFO region and when we checked
    // stack usage we avoided checking that region because we'd already
    // started using it -- so if we found the stack almost full to that
    // point, warn that it might actually have been completely full.
    (void) emberSerialPrintfLine(port,
                                 "Stack _may_ have used up to 100%% of total.");
  }
  // Valid SP range is [stackBegin, stackEnd] inclusive, but contents
  // of stack only go into [stackBegin, stackend).
  if ((sp > stackEnd) || (sp < stackBegin)) {
    (void) emberSerialPrintfLine(port, "SP is outside %p stack range!", stack);
  }
  (void) emberSerialWaitSend(port);
  if (c->intActive.word != 0u) {
    (void) emberSerialPrintf(port,
                             "Interrupts active (or pre-empted and stacked):");
    for (bit = (uint8_t) TIM1_IRQn; bit <= (uint8_t) DEBUG_IRQn; bit++) {
      // The L is added to work around a CSTAT bug.
      if ((c->intActive.word & (1UL << bit)) != 0u
          && (uint8_t) *intActiveBits[bit] != 0u) {
        (void) emberSerialPrintf(port, " %p", intActiveBits[bit]);
      }
    }
    (void) emberSerialPrintCarriageReturn(port);
  } else {
    (void) emberSerialPrintfLine(port, "No interrupts active");
  }
}

void halPrintCrashDetails(uint8_t port)
{
  HalCrashInfoType *c = &halResetInfo.crash;
  uint16_t reason = halGetExtendedResetInfo();
  uint8_t bit;
  const char *chan;

  switch (reason) {
    case RESET_WATCHDOG_EXPIRED:
      (void) emberSerialPrintfLine(port, "Reset cause: Watchdog expired, no reliable extra information");
      (void) emberSerialWaitSend(port);
      break;
    case RESET_WATCHDOG_CAUGHT:
      (void) emberSerialPrintfLine(port, "Reset cause: Watchdog caught with enhanced info");
      (void) emberSerialPrintfLine(port, "Instruction address: %4x", c->PC);
      (void) emberSerialWaitSend(port);
      break;

    case RESET_FAULT_PROTDMA:
      switch (c->data.dmaProt.channel) {
        case DMA_PROT_CH_SC1_RX:
          chan = "SC1 Rx";
          break;
        case DMA_PROT_CH_GP_ADC:
          chan = "ADC";
          break;
        case DMA_PROT_CH_MAC:
          chan = "MAC Rx";
          break;
        case DMA_PROT_CH_SC2_RX:
          chan = "SC2 Rx";
          break;
        default:
          chan = "??";
          break;
      }
      (void) emberSerialPrintfLine(port, "Reset cause: DMA protection violation");
      (void) emberSerialPrintfLine(port, "DMA: %p, address: %4x",
                                   chan, c->data.dmaProt.address);
      (void) emberSerialWaitSend(port);
      break;

    case RESET_CRASH_ASSERT:
      (void) emberSerialPrintfLine(port, "Reset cause: Assert %p:%d",
                                   c->data.assertInfo.file, c->data.assertInfo.line);
      (void) emberSerialWaitSend(port);
      break;

    case RESET_FAULT_HARD:
      (void) emberSerialPrintfLine(port, "Reset cause: Hard Fault");
      if (c->hfsr.bits.VECTTBL != 0u) {
        (void) emberSerialPrintfLine(port,
                                     "HFSR.VECTTBL: error reading vector table for an exception");
      }
      if (c->hfsr.bits.FORCED != 0u) {
        (void) emberSerialPrintfLine(port,
                                     "HFSR.FORCED: configurable fault could not activate");
      }
      if (c->hfsr.bits.DEBUGEVT != 0u) {
        (void) emberSerialPrintfLine(port,
                                     "HFSR.DEBUGEVT: fault related to debug - e.g., executed BKPT");
      }
      (void) emberSerialWaitSend(port);
      break;

    case RESET_FAULT_MEM:
      (void) emberSerialPrintfLine(port, "Reset cause: Memory Management Fault");
      if ((c->cfsr.word & (SCB_CFSR_DACCVIOL_Msk | SCB_CFSR_IACCVIOL_Msk))
          != 0u) {
        (void) emberSerialPrintfLine(port, "Instruction address: %4x", c->PC);
      }
      if (c->cfsr.bits.MMARVALID != 0u) {
        (void) emberSerialPrintfLine(port, "Illegal access address: %4x", c->faultAddress);
      }
      for (bit = SCB_CFSR_IACCVIOL_Pos; bit <= SCB_CFSR_MMARVALID_Pos; bit++) {
        if ((c->cfsr.word & (1UL << bit)) != 0u
            && (uint8_t) *cfsrBits[bit] != 0u) {
          (void) emberSerialPrintfLine(port, "CFSR.%p", cfsrBits[bit]);
        }
      }
      (void) emberSerialWaitSend(port);
      break;

    case RESET_FAULT_BUS:
      (void) emberSerialPrintfLine(port, "Reset cause: Bus Fault");
      (void) emberSerialPrintfLine(port, "Instruction address: %4x", c->PC);
      if (c->cfsr.bits.IMPRECISERR != 0u) {
        (void) emberSerialPrintfLine(port,
                                     "Address is of an instruction after bus fault occurred, not the cause.");
      }
      if (c->cfsr.bits.BFARVALID != 0u) {
        (void) emberSerialPrintfLine(port, "Illegal access address: %4x",
                                     c->faultAddress);
      }
      for (bit = SCB_CFSR_IBUSERR_Pos; bit <= SCB_CFSR_BFARVALID_Pos; bit++) {
        if ((c->cfsr.word & (1UL << bit)) != 0u
            && (uint8_t) *cfsrBits[bit] != 0u) {
          (void) emberSerialPrintfLine(port, "CFSR.%p", cfsrBits[bit]);
        }
      }
      if ((c->cfsr.word & 0xFFu) == 0u) {
        (void) emberSerialPrintfLine(port, "CFSR.(none) load or store at an illegal address");
      }
      for (bit = SCB_AFSR_RESERVED_Pos; bit <= SCB_AFSR_WRONGSIZE_Pos; bit++) {
        if ((c->afsr.word & (1UL << bit)) != 0u
            && (uint8_t) *afsrBits[bit] != 0u) {
          (void) emberSerialPrintfLine(port, "AFSR.%p", afsrBits[bit]);
        }
      }
      (void) emberSerialWaitSend(port);
      break;

    case RESET_FAULT_USAGE:
      (void) emberSerialPrintfLine(port, "Reset cause: Usage Fault");
      (void) emberSerialPrintfLine(port, "Instruction address: %4x", c->PC);
      for (bit = SCB_CFSR_UNDEFINSTR_Pos; bit <= SCB_CFSR_DIVBYZERO_Pos; bit++) {
        if ((c->cfsr.word & (1UL << bit)) != 0u
            && (uint8_t) *cfsrBits[bit] != 0u) {
          (void) emberSerialPrintfLine(port, "CFSR.%p", cfsrBits[bit]);
        }
      }
      (void) emberSerialWaitSend(port);
      break;

    case RESET_FAULT_DBGMON:
      (void) emberSerialPrintfLine(port, "Reset cause: Debug Monitor Fault");
      (void) emberSerialPrintfLine(port, "Instruction address: %4x", c->PC);
      (void) emberSerialWaitSend(port);
      break;

    default:
      break;
  }
}

// Output an array of 32 bit values, 4 per line, each preceded by its name.
void halPrintCrashData(uint8_t port)
{
  uint32_t *data = (uint32_t *)&halResetInfo.crash.R0;
  char const *name = nameStrings;
  char const *separator;
  uint8_t i = 0u;

  while (*name != '\0') {
    (void) emberSerialPrintf(port, "%p = %4x", name, *data++);
    while ((uint8_t) *name++ != 0u) {
    }                   // intentionally empty while loop body

    /*lint -save -e448 */
    separator = ((uint8_t) *name != 0u && ((i & 3u) != 3u)) ? ", " : "\r\n";

    /*lint -restore */
    (void) emberSerialPrintf(port, separator);
    (void) emberSerialWaitSend(port);
    i++;
  }
}

uint16_t halGetPCDiagnostics(void)
{
  return 0;
}

void halStartPCDiagnostics(void)
{
}

void halStopPCDiagnostics(void)
{
}
