/***************************************************************************//**
 * @file sl_efp.h
 * @brief EFP (Energy Friendly PMIC) driver API definitions.
 * @version 5.7.0
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef EFP_H
#define EFP_H

#include "i2cspm.h"
#include "sl_efp01.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "sl_status.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup extdrv
 * @{
 ******************************************************************************/

/* *INDENT-OFF* */
/***************************************************************************//**
 * @addtogroup SL_EFP EFP Driver
 * @{

@brief EFP (Energy Friendly PMIC) driver.

@section EFP_DOC EFP (Energy Friendly PMIC) driver documentation

  @li @ref sl_efp_intro
  @li @ref sl_efp_configuration
  @li @ref sl_efp_example

@n @section sl_efp_intro Introduction

  The EFP is a flexible, highly efficient, multi-output power
  management IC. This driver provides an API to configure and control EFP ICs.
  The EFP is controlled by the host SoC using an I2C bus. The driver support
  systems with multipple EFP ICs.

@n @section sl_efp_configuration Configuring the EFP driver

  Your application must provide a header file named
  <em>efp_<b>instance</b>_config.h</em>. <em><b>instance</b></em> can be freely
  selected and could for example be EFP0 and EFP1 in a system with two EFP devices.
  Configuration file templates are found in the driver config folder.

  Configuration options:
  @li Energy mode transition mode. Host SoC can use several methods for
      changing EFP energy mode. Methods are either direct mode or
      I2C mode. I2C mode change EFP energy mode with I2C commands, direct mode
      use level transitions on I2C SDA and SCL lines. This provides fast energy
      mode transitions. Direct mode is achieved by host SoC using GPIO bit-banging
      or automatically by EMU hardware on SoCs with builtin EFP support (check
      EMU section of reference manual for EFP support).
  @li EFP interrupt. The EFP has an interrupt line that can be useful for a host
      SoC. Set this option to have the EFP driver configure a GPIO for this use.
  @li EFP powers host SoC. Set if the EFP IC power the host SoC, there can only
      be one EFP with this option in a system.
  @li I2C instance: Select which I2C peripheral to use.
  @li GPIO definitions for I2C SDA/SCL and IRQ pins.

  Here is an example configuration file: @n @n
  @verbatim
#ifndef EFP_INSTANCE_CONFIG_H
#define EFP_INSTANCE_CONFIG_H

#include "sl_efp.h"

#ifdef __cplusplus
extern "C" {
#endif

// <<< Use Configuration Wizard in Context Menu >>>

// <h>EFP driver configuration

// <o EFP_INSTANCE_EM_CTRL_MODE> Selects method of controlling EFP Energy Mode (EM) transitions.
// <efp_em_transition_mode_gpio_bitbang=> GPIO driven direct mode EM transitions
// <efp_em_transition_mode_i2c=> I2C transfers control EM transitions
// <efp_em_transition_mode_emu=> Builtin EMU controlled direct mode EM transitions
// <i> Default: efp_em_transition_mode_gpio_bitbang
#define EFP_INSTANCE_EM_CTRL_MODE       efp_em_transition_mode_gpio_bitbang

// <q EFP_INSTANCE_ENABLE_IRQ> Enable GPIO as interrupt input line from EFP.
// <i> Default: 1
#define EFP_INSTANCE_ENABLE_IRQ         1

// <q EFP_INSTANCE_POWERS_HOST> This EFP powers host SoC.
// <i> Default: 1
#define EFP_INSTANCE_POWERS_HOST        1

// </h> end EFP configuration

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <gpio optional> EFP_INSTANCE_IRQ
// $[GPIO_EFP_INSTANCE_IRQ]
#define EFP_INSTANCE_IRQ_PORT           gpioPortC
#define EFP_INSTANCE_IRQ_PIN            9
// [GPIO_EFP_INSTANCE_IRQ]$

// <i2c signal=SDA,SCL> EFP_INSTANCE_I2C
// $[I2C_EFP_INSTANCE_I2C]
#define EFP_INSTANCE_I2C_PERIPHERAL     I2C0

#define EFP_INSTANCE_I2C_SDA_PORT       gpioPortC
#define EFP_INSTANCE_I2C_SDA_PIN        11
#define EFP_INSTANCE_I2C_SDA_LOC        16

#define EFP_INSTANCE_I2C_SCL_PORT       gpioPortC
#define EFP_INSTANCE_I2C_SCL_PIN        10
#define EFP_INSTANCE_I2C_SCL_LOC        14
// [I2C_EFP_INSTANCE_I2C]$

// <<< sl:end pin_tool >>>

#define SL_EFP_INSTANCE_INIT {                                                         \
    .config_size = 0,                                   // No initial config           \
    .config_data = NULL,                                // No config data              \
    .is_host_efp = EFP_INSTANCE_POWERS_HOST,            // This EFP powers host SOC    \
    .em_transition_mode = EFP_INSTANCE_EM_CTRL_MODE,    // EFP EM transition mode      \
    .enable_irq_pin = EFP_INSTANCE_ENABLE_IRQ,          // Init GPIO as EFP IRQ        \
    .irq_port = EFP_INSTANCE_IRQ_PORT,                  // EFP IRQ port                \
    .irq_pin = EFP_INSTANCE_IRQ_PIN,                    // EFP IRQ pin                 \
    .i2c_peripheral = EFP_INSTANCE_I2C_PERIPHERAL,      // I2C port instance           \
    .i2c_scl_port = EFP_INSTANCE_I2C_SCL_PORT,          // SCL port                    \
    .i2c_scl_pin = EFP_INSTANCE_I2C_SCL_PIN,            // SCL pin                     \
    .i2c_sda_port = EFP_INSTANCE_I2C_SDA_PORT,          // SDA port                    \
    .i2c_sda_pin = EFP_INSTANCE_I2C_SDA_PIN,            // SDA pin                     \
    .i2c_scl_port_location = EFP_INSTANCE_I2C_SCL_LOC,  // SCL port location           \
    .i2c_sda_port_location = EFP_INSTANCE_I2C_SDA_LOC,  // SDA port location           \
}

#ifdef __cplusplus
}
#endif

#endif // EFP_INSTANCE_CONFIG_H @endverbatim

@n @section sl_efp_example EFP driver example code

  Basic example: @n @n
  @verbatim
#include "efp_instance_config.h"

sl_efp_handle_data_t efp_handle_data;          // EFP instance data structure
sl_efp_handle_t      efp = &efp_handle_data;   // EFP instance pointer

int main( void )
{

  ...

  // Initialize EFP.

  // Load all configurations into an init structure, and pass it to the
  // driver initialization function.
  sl_efp_init_data_t init = SL_EFP_INSTANCE_INIT;
  sl_efp_init(efp, &init);

  // Set voltage regulator B (VOB) output voltage and peak currents.
  sl_efp_set_vob_em01_voltage(efp, 1100);
  sl_efp_set_vob_em23_voltage(efp, 1100);
  sl_efp_set_vob_em01_peak_current(efp, 108, 3300, 1100, 3300);
  sl_efp_set_vob_em23_peak_current(efp, 108, 3300, 1100, 3300);

  // Enable VOB in buck mode.
  sl_efp_set_vob_mode(efp, efp_vob_mode_buck);

  ...

} @endverbatim

@n Code for preparing for EFP interrupts: @n @n
  @verbatim
#include "efp_instance_config.h"

int main( void )
{

  ...

  // Prepare for EFP IRQ from Coulomb counter (CC) full flag.
  sl_efp_write_register(efp, EFP01_STATUS_GM, 0xFF);    // Unmask all G flags
  sl_efp_write_register(efp, EFP01_CC_CAL, 0x28);       // Enable CC A

  // Setup GPIO interrupt.
  NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
  NVIC_EnableIRQ(GPIO_ODD_IRQn);
  GPIO_IntConfig(init.irq_port, init.irq_pin, false, true, true);

  ...

  // Force CC full flag interrupt. This will trigger an IRQ.
  sl_efp_write_register(efp, EFP01_CMD, 0x10);          // Start CC Calibration

  ...

}

void GPIO_ODD_IRQHandler(void)
{
  // Make sure any ongoing EFP I2C transfer is completed before writing to EFP.

  // Clear EFP IRQ flag.
  sl_efp_write_register(efp, EFP01_STATUS_G, 0x40);

  // Clear GPIO interrupt flag.
  GPIO_IntClear(1 << init.irq_pin);
} @endverbatim

@n Example with custom EFP configuration data. The @ref sl_efp_init() function
  can perform EFP configuration by passing an array of EFP {address,value} pairs.
  This array can be generated by the EFP calculator tool in Simplicity Studio.
@n @n @verbatim
#include "efp_instance_config.h"

#define SL_EFP_INSTANCE_GEN_SIZE 10

// Array of 10 {address,data} pairs.
#define SL_EFP_INSTANCE_GEN {      \
    { EFP01_VOA_V,        4   },   \
    { EFP01_BB_IPK,       146 },   \
    { EFP01_BB_CTRL6,     0   },   \
    { EFP01_LDOC_BB_CTRL, 0   },   \
    { EFP01_BB_CTRL3,     181 },   \
    { EFP01_VOB_EM0_V,    13  },   \
    { EFP01_VOB_EM2_V,    13  },   \
    { EFP01_BK_IPK,       38  },   \
    { EFP01_BK_CTRL2,     80  },   \
    { EFP01_BK_CTRL1,     24  },   \
}

uint8_t efp_settings[SL_EFP_INSTANCE_GEN_SIZE][2] = SL_EFP_INSTANCE_GEN;

int main( void )
{

  ...

  // Initialize EFP, pass array of custom settings to init function.
  sl_efp_init_data_t init = SL_EFP_INSTANCE_INIT;
  init.config_size        = SL_EFP_INSTANCE_GEN_SIZE;
  init.config_data        = efp_settings[0];
  sl_efp_init(efp, &init);

  ...

} @endverbatim

 ******************************************************************************/
/* *INDENT-ON* */


/// Method for controlling EFP Energy Mode (EM) transitions.
typedef enum {
  efp_em_transition_mode_gpio_bitbang,  ///< GPIO driven "direct mode" EM transitions.
  efp_em_transition_mode_i2c,           ///< I2C transfers control EM transitions.
  efp_em_transition_mode_emu            ///< Built in EMU controlled "direct mode" EM transitions.
} sl_efp_em_transition_mode_t;

/// VOA regulator modes.
typedef enum {
  efp_voa_mode_disabled                = _EFP01_BB_CTRL3_BB_MODE_DISABLED,      ///< VOA disabled.
  efp_voa_mode_wired_buck              = _EFP01_BB_CTRL3_BB_MODE_WIREDBUCK,     ///< VOA wired buck.
  efp_voa_mode_wired_boost             = _EFP01_BB_CTRL3_BB_MODE_WIREDBOOST,    ///< VOA wired boost.
  efp_voa_mode_wired_buck_ldo          = _EFP01_BB_CTRL3_BB_MODE_WIREDBUCKLDO,  ///< VOA wired buck and LDO.
  efp_voa_mode_buck_boost_autonomous   = _EFP01_BB_CTRL3_BB_MODE_AUTONOMOUS,    ///< VOA buck boost autonomous.
  efp_voa_mode_buck_boost_forced_buck  = _EFP01_BB_CTRL3_BB_MODE_FORCEBUCK,     ///< VOA buck boost forced buck.
  efp_voa_mode_buck_boost_forced_ntm   = _EFP01_BB_CTRL3_BB_MODE_FORCENTM,      ///< VOA buck boost forced NTM.
  efp_voa_mode_buck_boost_forced_boost = _EFP01_BB_CTRL3_BB_MODE_FORCEBOOST     ///< VOA buck boost forced boost.
} sl_efp_voa_mode_t;

/// VOA SW (switched output) modes.
typedef enum {
  efp_voa_sw_mode_off                  = _EFP01_BIAS_SW_VOA_SW_CON_OFF,     ///< VOA SW off.
  efp_voa_sw_mode_on                   = _EFP01_BIAS_SW_VOA_SW_CON_ON,      ///< VOA SW on in EM0, EM2 and EM4.
  efp_voa_sw_mode_on_in_em0            = _EFP01_BIAS_SW_VOA_SW_CON_ONINEM0, ///< VOA SW on in EM0 only.
  efp_voa_sw_mode_on_in_em02           = _EFP01_BIAS_SW_VOA_SW_CON_ONINEM02 ///< VOA SW on in EM0 and EM2.
} sl_efp_voa_sw_mode_t;

/// VOB regulator modes.
typedef enum {
  efp_vob_mode_disabled = _EFP01_BK_CTRL1_BK_MODE_DISABLED,   ///< VOB disabled.
  efp_vob_mode_buck     = _EFP01_BK_CTRL1_BK_MODE_BUCKONLY,   ///< VOB buck only.
  efp_vob_mode_ldo      = _EFP01_BK_CTRL1_BK_MODE_LDOONLY,    ///< VOB LDO only.
  efp_vob_mode_buck_ldo = _EFP01_BK_CTRL1_BK_MODE_BUCKLDO     ///< VOB buck and LDO.
} sl_efp_vob_mode_t;

/// EFP driver initialization structure.
typedef struct {
  unsigned int        config_size;                ///< Number of register writes inside the configuration data. Set to 0 on preprogrammed parts.
  uint8_t             *config_data;               ///< Configuration data, pairs of (addr,data),(addr,data),... Set to NULL on preprogrammed parts.
  bool                is_host_efp;                ///< True if this EFP powers host SoC.
  sl_efp_em_transition_mode_t em_transition_mode; ///< Method for controlling EFP Energy Mode (EM) transitions.
  bool                enable_irq_pin;             ///< Initialize a GPIO pin as EFP IRQ input.
  GPIO_Port_TypeDef   irq_port;                   ///< GPIO port to use for EFP IRQ GPIO pin.
  unsigned int        irq_pin;                    ///< GPIO pin number to use for EFP IRQ GPIO pin.
  I2C_TypeDef         *i2c_peripheral;            ///< I2C peripheral instance pointer.
  GPIO_Port_TypeDef   i2c_scl_port;               ///< GPIO port to use for I2C SCL signal.
  unsigned int        i2c_scl_pin;                ///< GPIO pin number to use for I2C SCL signal.
  GPIO_Port_TypeDef   i2c_sda_port;               ///< GPIO port to use for I2C SDA signal.
  unsigned int        i2c_sda_pin;                ///< GPIO pin number to use for I2C SDA signal.
  #if defined(_SILICON_LABS_32B_SERIES_0)
    unsigned int      i2c_port_location;          ///< I2C location number to use for I2C signals.
  #elif defined(_SILICON_LABS_32B_SERIES_1)
    unsigned int      i2c_scl_port_location;      ///< I2C location number to use for I2C SCL signal.
    unsigned int      i2c_sda_port_location;      ///< I2C location number to use for I2C SDA signal.
  #endif
} sl_efp_init_data_t;

/// An EFP driver instance handle data structure.
/// The handle is allocated by the application using the EFP driver.
/// Several concurrent driver instances can coexist in an application. The
/// application is neither supposed to write nor read the contents of the handle.
typedef struct {
  /// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
  sl_efp_init_data_t  init_data;
  unsigned int        i2c_peripheral_index;
  CMU_Clock_TypeDef   i2c_clock;
  bool                in_direct_mode;
  uint8_t             em_ctrl;
  /// @endcond
} sl_efp_handle_data_t;

/// An EFP driver instance handle.
typedef sl_efp_handle_data_t *sl_efp_handle_t;

// EFP driver API function prototypes.
sl_status_t sl_efp_deinit(sl_efp_handle_t handle);
sl_status_t sl_efp_enable_direct_mode(sl_efp_handle_t handle);
sl_status_t sl_efp_enter_em0(sl_efp_handle_t handle);
sl_status_t sl_efp_enter_em2(sl_efp_handle_t handle);
sl_status_t sl_efp_get_vdd_avg(sl_efp_handle_t handle, uint16_t *voltage_mv);
sl_status_t sl_efp_get_vdd_max(sl_efp_handle_t handle, uint16_t *voltage_mv);
sl_status_t sl_efp_get_vdd_min(sl_efp_handle_t handle, uint16_t *voltage_mv);
sl_status_t sl_efp_init(sl_efp_handle_t handle, const sl_efp_init_data_t *init);
sl_status_t sl_efp_read_otp(sl_efp_handle_t handle, uint8_t addr, uint8_t *data);
sl_status_t sl_efp_read_register(sl_efp_handle_t handle, uint8_t addr, uint8_t *data);
sl_status_t sl_efp_read_register_field(sl_efp_handle_t handle,
                                       uint8_t addr, uint8_t *data,
                                       uint8_t mask, uint8_t pos);
sl_status_t sl_efp_reset(sl_efp_handle_t handle);
sl_status_t sl_efp_set_em_transition_mode(sl_efp_handle_t handle,
                                          sl_efp_em_transition_mode_t mode);
sl_status_t sl_efp_set_voa_em01_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int voa_mv,
                                             unsigned int inductor_nh);
sl_status_t sl_efp_set_voa_em23_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int voa_mv,
                                             unsigned int inductor_nh);
sl_status_t sl_efp_set_voa_mode(sl_efp_handle_t handle, sl_efp_voa_mode_t mode);
sl_status_t sl_efp_set_voa_sw_mode(sl_efp_handle_t handle, sl_efp_voa_sw_mode_t mode);
sl_status_t sl_efp_set_voa_voltage(sl_efp_handle_t handle, unsigned int voltage_mv);
sl_status_t sl_efp_set_vob_em01_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int vob_mv,
                                             unsigned int inductor_nh);
sl_status_t sl_efp_set_vob_em01_voltage(sl_efp_handle_t handle, unsigned int voltage_mv);
sl_status_t sl_efp_set_vob_em23_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int vob_mv,
                                             unsigned int inductor_nh);
sl_status_t sl_efp_set_vob_em23_voltage(sl_efp_handle_t handle, unsigned int voltage_mv);
sl_status_t sl_efp_set_vob_mode(sl_efp_handle_t handle, sl_efp_vob_mode_t mode);
sl_status_t sl_efp_set_voc_voltage(sl_efp_handle_t handle, unsigned int voltage_mv);
sl_status_t sl_efp_emu_ldo_enable(sl_efp_handle_t handle, bool enable);
sl_status_t sl_efp_write_register(sl_efp_handle_t handle, uint8_t addr, uint8_t data);
sl_status_t sl_efp_write_register_field(sl_efp_handle_t handle,
                                        uint8_t addr, uint8_t data,
                                        uint8_t mask, uint8_t pos);


// Documented prototypes

/***************************************************************************//**
 * @brief
 *   Deinitialize EFP driver and underlying EFP hardware.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @return
 *   SL_STATUS_OK.
 ******************************************************************************/
sl_status_t sl_efp_deinit(sl_efp_handle_t handle);

/***************************************************************************//**
 * @brief
 *   Configure I2C GPIO pins for "direct mode" EM transfer mode.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @note
 *   This must be the last EFP driver function called prior to entering EM2/3
 *   via EMU_EnterEMx() calls. Any EFP API call that involves an I2C transfer
 *   will leave the I2C GPIO pins in I2C mode.
 *
 * @return
 *   SL_STATUS_OK on success.
 *   SL_STATUS_INVALID_MODE if current EM transfer mode is I2C.
 *   SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_enable_direct_mode(sl_efp_handle_t handle);

/***************************************************************************//**
 * @brief
 *   Set EFP in EM0 energy mode.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_enter_em0(sl_efp_handle_t handle);

/***************************************************************************//**
 * @brief
 *   Set EFP in EM2 energy mode.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_enter_em2(sl_efp_handle_t handle);

/***************************************************************************//**
 * @brief
 *   Measure average VDD.
 *
 * @note
 *   This function will measure VDDA or VDDB depending of the voltage on the
 *   VDDA pin after power on. If VDDA is powered this function returns a VDDA
 *   reading, otherwise a VDDB reading is returned.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[out] voltage_mv
 *   Average VDD voltage expressed in miilivolts.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_get_vdd_avg(sl_efp_handle_t handle, uint16_t *voltage_mv);

/***************************************************************************//**
 * @brief
 *   Measure maximum VDD.
 *
 * @note
 *   This function will measure VDDA or VDDB depending of the voltage on the
 *   VDDA pin after power on. If VDDA is powered this function returns a VDDA
 *   reading, otherwise a VDDB reading is returned.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[out] voltage_mv
 *   Maximum VDD voltage expressed in miilivolts.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_get_vdd_max(sl_efp_handle_t handle, uint16_t *voltage_mv);

/***************************************************************************//**
 * @brief
 *   Measure minimum VDD.
 *
 * @note
 *   This function will measure VDDA or VDDB depending of the voltage on the
 *   VDDA pin after power on. If VDDA is powered this function returns a VDDA
 *   reading, otherwise a VDDB reading is returned.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[out] voltage_mv
 *   Minimum VDD voltage expressed in miilivolts.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_get_vdd_min(sl_efp_handle_t handle, uint16_t *voltage_mv);

/***************************************************************************//**
 * @brief
 *   Initialize EFP driver and configure underlying EFP hardware.
 *
 * @note This function must not be called from interrupt context.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] init
 *   Initialization data structure.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors, or SL_STATUS_FAIL
 *   on illegal initialization.
 ******************************************************************************/
sl_status_t sl_efp_init(sl_efp_handle_t handle, const sl_efp_init_data_t *init);

/***************************************************************************//**
 * @brief
 *   Read EFP OTP register.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] addr
 *   Register address.
 *
 * @param[out] data
 *   The value read from the OTP register.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_read_otp(sl_efp_handle_t handle, uint8_t addr, uint8_t *data);

/***************************************************************************//**
 * @brief
 *   Read EFP control register.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] addr
 *   Register address.
 *
 * @param[out] data
 *   The value read from the register.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_read_register(sl_efp_handle_t handle, uint8_t addr, uint8_t *data);

/***************************************************************************//**
 * @brief
 *   Read EFP control register field.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] addr
 *   Register address.
 *
 * @param[out] data
 *   The value read from the register field.
 *
 * @param[in] mask
 *   Bit mask corresponding to target bit field.
 *
 * @param[in] pos
 *   Bit number of least significant bit of target bit field.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_read_register_field(sl_efp_handle_t handle,
                                       uint8_t addr, uint8_t *data,
                                       uint8_t mask, uint8_t pos);

/***************************************************************************//**
 * @brief
 *   Reset EFP. Perform a full reset of the EFP, this is eqvivalent to a power
 *   on reset.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_reset(sl_efp_handle_t handle);

/***************************************************************************//**
 * @brief
 *   Set EM transition mode.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] mode
 *   New EFP Energy Mode (EM) transition mode. See @ref sl_efp_em_transition_mode_t
 *   for valid modes.
 *
 * @return
 *   SL_STATUS_OK.
 ******************************************************************************/
sl_status_t sl_efp_set_em_transition_mode(sl_efp_handle_t handle,
                                          sl_efp_em_transition_mode_t mode);

/***************************************************************************//**
 * @brief
 *   Set regulator VOA EM01 peak output current.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] current_ma
 *   Target peak current expressed in milliamperes.
 *
 * @param[in] vddb_mv
 *   VDDB expressed in millivolt.
 *
 * @param[in] voa_mv
 *   VOA expressed in millivolt.
 *
 * @param[in] inductor_nh
 *   Inductor size expressed in nanohenry.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_em01_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int voa_mv,
                                             unsigned int inductor_nh);

/***************************************************************************//**
 * @brief
 *   Set regulator VOA EM23 peak output current.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] current_ma
 *   Target peak current expressed in milliamperes.
 *
 * @param[in] vddb_mv
 *   VDDB expressed in millivolt.
 *
 * @param[in] voa_mv
 *   VOA expressed in millivolt.
 *
 * @param[in] inductor_nh
 *   Inductor size expressed in nanohenry.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_em23_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int voa_mv,
                                             unsigned int inductor_nh);

/***************************************************************************//**
 * @brief
 *   Set regulator VOA mode.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] mode
 *   Regulator mode.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_mode(sl_efp_handle_t handle, sl_efp_voa_mode_t mode);

/***************************************************************************//**
 * @brief
 *   Set VOA SW (switched output) mode.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] mode
 *   VOA SW mode.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_sw_mode(sl_efp_handle_t handle, sl_efp_voa_sw_mode_t mode);

/***************************************************************************//**
 * @brief
 *   Set regulator VOA output voltage.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] voltage_mv
 *   Voltage in millivolt.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_voltage(sl_efp_handle_t handle, unsigned int voltage_mv);

/***************************************************************************//**
 * @brief
 *   Set regulator VOB EM01 peak output current.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] current_ma
 *   Target peak current expressed in milliamperes.
 *
 * @param[in] vddb_mv
 *   VDDB expressed in millivolt.
 *
 * @param[in] vob_mv
 *   VOB expressed in millivolt.
 *
 * @param[in] inductor_nh
 *   Inductor size expressed in nanohenry.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_em01_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int vob_mv,
                                             unsigned int inductor_nh);

/***************************************************************************//**
 * @brief
 *   Set regulator VOB EM01 output voltage.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] voltage_mv
 *   Voltage in millivolt.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_em01_voltage(sl_efp_handle_t handle, unsigned int voltage_mv);

/***************************************************************************//**
 * @brief
 *   Set regulator VOB EM23 peak output current.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] current_ma
 *   Target peak current expressed in milliamperes.
 *
 * @param[in] vddb_mv
 *   VDDB expressed in millivolt.
 *
 * @param[in] vob_mv
 *   VOB expressed in millivolt.
 *
 * @param[in] inductor_nh
 *   Inductor size expressed in nanohenry.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_em23_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int vob_mv,
                                             unsigned int inductor_nh);

/***************************************************************************//**
 * @brief
 *   Set regulator VOB EM23 output voltage.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] voltage_mv
 *   Voltage in millivolt.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_em23_voltage(sl_efp_handle_t handle, unsigned int voltage_mv);

/***************************************************************************//**
 * @brief
 *   Set regulator VOB mode.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] mode
 *   Regulator mode.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_mode(sl_efp_handle_t handle, sl_efp_vob_mode_t mode);

/***************************************************************************//**
 * @brief
 *   Set regulator VOC output voltage.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] voltage_mv
 *   Voltage in millivolt.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_set_voc_voltage(sl_efp_handle_t handle, unsigned int voltage_mv);

/***************************************************************************//**
 * @brief
 *   Turn the internal EMU LDO regulator that supplies DECOUPLE pin on or off.
 *
 * @note
 *   Make sure that an external source supply the DECOUPLE pin turning the
 *   LDO off.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] enable
 *   True to turn LDO on, false to turn off.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_NOT_SUPPORTED, or SL_STATUS_FAIL if not a host
 *   EFP instance.
 ******************************************************************************/
sl_status_t sl_efp_emu_ldo_enable(sl_efp_handle_t handle, bool enable);

/***************************************************************************//**
 * @brief
 *   Write EFP control register.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] addr
 *   Register address.
 *
 * @param[in] data
 *   The value to write to the register.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_write_register(sl_efp_handle_t handle, uint8_t addr, uint8_t data);

/***************************************************************************//**
 * @brief
 *   Write EFP control register field.
 *
 * @note
 *   This function performs a read-modify-write of a EFP register.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] addr
 *   Register address.
 *
 * @param[in] data
 *   The value to write to the register field.
 *
 * @param[in] mask
 *   Bit mask corresponding to target bit field.
 *
 * @param[in] pos
 *   Bit number of least significant bit of target bit field.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
sl_status_t sl_efp_write_register_field(sl_efp_handle_t handle,
                                        uint8_t addr, uint8_t data,
                                        uint8_t mask, uint8_t pos);

/** @} (end addtogroup SL_EFP) */
/** @} (end addtogroup extdrv) */

#ifdef __cplusplus
}
#endif

#endif // #define EFP_H
