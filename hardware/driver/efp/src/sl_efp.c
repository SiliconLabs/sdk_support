/***************************************************************************//**
 * @file sl_efp.c
 * @brief EFP (Energy Friendly PMIC) driver.
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
#include "em_assert.h"
#include "em_common.h"
#include "em_cmu.h"
#include "em_core.h"
#include "em_gpio.h"
#include "em_se.h"
#include "sl_efp.h"

#include <stdbool.h>
#include <math.h>

/***************************************************************************//**
 * @addtogroup extdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup SL_EFP
 * @{
 ******************************************************************************/

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#define EFP_EFP01_I2C_ADDR   0x60

static sl_efp_handle_t host_efp = NULL;
static CORE_DECLARE_IRQ_STATE;

/***************************************************************************//**
 * @brief
 *   Configure I2C GPIO pins.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] enable
 *   If true, configure I2C pins for I2C use. If false, pins are configured as
 *   GPIO pins to enable "direct mode" EM transfer mode.
 ******************************************************************************/
static void enable_i2c_pins(sl_efp_handle_t handle, bool enable)
{
  if (enable) {
    handle->in_direct_mode = false;
    GPIO_PinModeSet(handle->init_data.i2c_sda_port, handle->init_data.i2c_sda_pin,
                    gpioModeWiredAnd, 1);
    GPIO_PinModeSet(handle->init_data.i2c_scl_port, handle->init_data.i2c_scl_pin,
                    gpioModeWiredAnd, 1);

    // Enable I2C module and clock.
    CMU_ClockEnable(handle->i2c_clock, true);
    I2C_Enable(handle->init_data.i2c_peripheral, true);

    #if defined(_SILICON_LABS_32B_SERIES_0)
      handle->init_data.i2c_peripheral->ROUTE |= I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;
    #elif defined(_SILICON_LABS_32B_SERIES_1)
      handle->init_data.i2c_peripheral->ROUTEPEN |= I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
    #elif defined(_SILICON_LABS_32B_SERIES_2)
      GPIO->I2CROUTE[handle->i2c_peripheral_index].ROUTEEN |= GPIO_I2C_ROUTEEN_SDAPEN
                                                              | GPIO_I2C_ROUTEEN_SCLPEN;
    #endif
  } else {
    handle->in_direct_mode = true;
    GPIO_PinModeSet(handle->init_data.i2c_sda_port, handle->init_data.i2c_sda_pin,
                    gpioModePushPull, 1);
    GPIO_PinModeSet(handle->init_data.i2c_scl_port, handle->init_data.i2c_scl_pin,
                    gpioModePushPull, 1);

    #if defined(_SILICON_LABS_32B_SERIES_0)
      init_data.i2c_instance->ROUTE &= ~(I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN);
    #elif defined(_SILICON_LABS_32B_SERIES_1)
      handle->init_data.i2c_peripheral->ROUTEPEN &= ~(I2C_ROUTEPEN_SDAPEN
                                                      | I2C_ROUTEPEN_SCLPEN);
    #elif defined(_SILICON_LABS_32B_SERIES_2)
      GPIO->I2CROUTE[handle->i2c_peripheral_index].ROUTEEN &= ~(GPIO_I2C_ROUTEEN_SDAPEN
                                                                | GPIO_I2C_ROUTEEN_SCLPEN);
    #endif

    // Disable I2C module and clock to save energy.
    I2C_Enable(handle->init_data.i2c_peripheral, false);
    CMU_ClockEnable(handle->i2c_clock, false);
  }
}

/***************************************************************************//**
 * @brief
 *   Perform a VDD measurement.
 *
 * @param[in] handle
 *   EFP instance handle.
 *
 * @param[in] msn_addr
 *   Register address of the most significant byte of measurement.
 *
 * @param[in] lsby_addr
 *   Register address of the least significant byte of measurement.
 *
 * @param[out] voltage_mv
 *   The result of the VDD measurement.
 *
 * @return
 *   SL_STATUS_OK or SL_STATUS_IO on I2C transfer errors.
 ******************************************************************************/
static sl_status_t get_vdd(sl_efp_handle_t handle,
                           uint8_t msn_addr,
                           uint8_t lsby_addr,
                           uint16_t *voltage_mv)
{
  sl_status_t ret_val;
  uint16_t read_value = 0;
  uint8_t adc_cc_ctrl, tmp, ss_mode;

  // Get ADC_INTERVAL value.
  ret_val = sl_efp_read_register(handle, EFP01_ADC_CC_CTRL, &adc_cc_ctrl);

  if (ret_val == SL_STATUS_OK) {
    if ((adc_cc_ctrl & _EFP01_ADC_CC_CTRL_ADC_INTERVAL_MASK) == 0) {
      // Issue an ADC start command if automated measurements are not enabled.
      ret_val = sl_efp_write_register(handle,
                                      EFP01_CMD,
                                      _EFP01_CMD_ADC_START_MASK);
    }
  }

  // Wait at least 18.5 usec for the result, read of SS mode provides the delay.
  if (ret_val == SL_STATUS_OK) {
    ret_val = sl_efp_read_register(handle, EFP01_CC_MODE, &ss_mode);
  }

  if (ret_val == SL_STATUS_OK) {                    // Read result MSB.
    ret_val = sl_efp_read_register(handle, msn_addr, &tmp);
  }

  if (ret_val == SL_STATUS_OK) {                    // Read result LSB.
    read_value = tmp << 8;
    ret_val = sl_efp_read_register(handle, lsby_addr, &tmp);
  }

  if (ret_val == SL_STATUS_OK) {                    // Scale result correctly.
    read_value |= tmp;
    if (ss_mode & _EFP01_CC_MODE_SC_MODE_MASK) {
      // Result is a VDDA measurement.
      *voltage_mv = (uint16_t)lroundf(read_value * 1.01f);
    } else {
      // Result is a VDDB measurement.
      *voltage_mv = (uint16_t)lroundf(read_value * 1.49f);
    }
  }

  return ret_val;
}

/// @endcond

/***************************************************************************//**
 * @brief
 *   Reimplementation of the EMU function with the same name.
 *
 * @details
 *   This function will be called upon wakeup from the _WFI() instruction in
 *   EMU_EnterEM2/3() functions and will set the EFP in EM0 mode.
 *   A critical section is used to get predictable EFP energy mode sequence
 *   timing.
 ******************************************************************************/
void EMU_EM23PostsleepHook(void)
{
  if (host_efp != NULL) {
    if ((host_efp->init_data.em_transition_mode == efp_em_transition_mode_gpio_bitbang)
        || (host_efp->init_data.em_transition_mode == efp_em_transition_mode_i2c)) {
      sl_efp_enter_em0(host_efp);
      CORE_EXIT_CRITICAL();
    }
  }
}

/***************************************************************************//**
 * @brief
 *   Reimplementation of the EMU function with the same name.
 *
 * @details
 *   This function will be called prior to the _WFI() instruction in
 *   EMU_EnterEM2/3() functions and will set the EFP in EM2 mode.
 *   A critical section is used to get predictable EFP energy mode sequence
 *   timing.
 ******************************************************************************/
void EMU_EM23PresleepHook(void)
{
  if (host_efp != NULL) {
    if ((host_efp->init_data.em_transition_mode == efp_em_transition_mode_gpio_bitbang)
        || (host_efp->init_data.em_transition_mode == efp_em_transition_mode_i2c)) {
      CORE_ENTER_CRITICAL();
      sl_efp_enter_em2(host_efp);
    }
  }
}

/***************************************************************************//**
 * @brief
 *   Configure I2C GPIO pins for "direct mode" EM transfer mode.
 *
 ******************************************************************************/
sl_status_t sl_efp_enable_direct_mode(sl_efp_handle_t handle)
{
  if (handle->init_data.em_transition_mode == efp_em_transition_mode_i2c) {
    return SL_STATUS_INVALID_MODE;
  }
  if (handle->in_direct_mode) {
    return SL_STATUS_OK;
  }
  return sl_efp_enter_em0(handle);
}

/***************************************************************************//**
 * @brief
 *   Set EFP in EM0 energy mode.
 ******************************************************************************/
sl_status_t sl_efp_enter_em0(sl_efp_handle_t handle)
{
  sl_status_t ret_val = SL_STATUS_OK;

  if (handle->init_data.em_transition_mode == efp_em_transition_mode_gpio_bitbang) {
    if (!handle->in_direct_mode) {
      ret_val = sl_efp_write_register_field(handle,
                                            EFP01_EM_CRSREG_CTRL,
                                            1 << _EFP01_EM_CRSREG_CTRL_DIRECT_MODE_EN_SHIFT,
                                            _EFP01_EM_CRSREG_CTRL_DIRECT_MODE_EN_MASK,
                                            _EFP01_EM_CRSREG_CTRL_DIRECT_MODE_EN_SHIFT);
      enable_i2c_pins(handle, false);
    }
    GPIO_PinOutSet(handle->init_data.i2c_scl_port, handle->init_data.i2c_scl_pin);
  } else if (handle->init_data.em_transition_mode == efp_em_transition_mode_i2c) {
    ret_val = sl_efp_write_register(handle, EFP01_EM_CRSREG_CTRL, handle->em_ctrl);
  }
  return ret_val;
}

/***************************************************************************//**
 * @brief
 *   Set EFP in EM2 energy mode.
 ******************************************************************************/
sl_status_t sl_efp_enter_em2(sl_efp_handle_t handle)
{
  uint8_t tmp;
  sl_status_t ret_val = SL_STATUS_OK;

  if (handle->init_data.em_transition_mode == efp_em_transition_mode_gpio_bitbang) {
    if (!handle->in_direct_mode) {
      ret_val = sl_efp_write_register_field(handle,
                                            EFP01_EM_CRSREG_CTRL,
                                            1 << _EFP01_EM_CRSREG_CTRL_DIRECT_MODE_EN_SHIFT,
                                            _EFP01_EM_CRSREG_CTRL_DIRECT_MODE_EN_MASK,
                                            _EFP01_EM_CRSREG_CTRL_DIRECT_MODE_EN_SHIFT);
      enable_i2c_pins(handle, false);
    }
    GPIO_PinOutClear(handle->init_data.i2c_scl_port, handle->init_data.i2c_scl_pin);
  } else if (handle->init_data.em_transition_mode == efp_em_transition_mode_i2c) {
    ret_val = sl_efp_read_register(handle, EFP01_EM_CRSREG_CTRL, &handle->em_ctrl);
    if (ret_val == SL_STATUS_OK) {
      tmp = (handle->em_ctrl & ~_EFP01_EM_CRSREG_CTRL_EM_SEL_MASK)
            | (_EFP01_EM_CRSREG_CTRL_EM_SEL_EM2
               << _EFP01_EM_CRSREG_CTRL_EM_SEL_SHIFT);
      ret_val = sl_efp_write_register(handle, EFP01_EM_CRSREG_CTRL, tmp);
    }
    if (!handle->in_direct_mode) {
      // Disable I2C module, pins and clock to save energy.
      enable_i2c_pins(handle, false);
    }
  }
  return ret_val;
}

/***************************************************************************//**
 * @brief
 *   Measure average VDD.
 ******************************************************************************/
sl_status_t sl_efp_get_vdd_avg(sl_efp_handle_t handle, uint16_t *voltage_mv)
{
  return get_vdd(handle, EFP01_VDD_AVG_MSN, EFP01_VDD_AVG_LSBY, voltage_mv);
}

/***************************************************************************//**
 * @brief
 *   Measure maximum VDD.
 ******************************************************************************/
sl_status_t sl_efp_get_vdd_max(sl_efp_handle_t handle, uint16_t *voltage_mv)
{
  return get_vdd(handle, EFP01_VDD_MAX_MSN, EFP01_VDD_MAX_LSBY, voltage_mv);
}

/***************************************************************************//**
 * @brief
 *   Measure minimum VDD.
 ******************************************************************************/
sl_status_t sl_efp_get_vdd_min(sl_efp_handle_t handle, uint16_t *voltage_mv)
{
  return get_vdd(handle, EFP01_VDD_MIN_MSN, EFP01_VDD_MIN_LSBY, voltage_mv);
}

/***************************************************************************//**
 * @brief
 *   Deinitialize EFP driver and underlying EFP hardware.
 ******************************************************************************/
sl_status_t sl_efp_deinit(sl_efp_handle_t handle)
{
  if (host_efp == handle) {
    host_efp = NULL;
  }
  enable_i2c_pins(handle, false);
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Turn the internal EMU LDO regulator that supplies DECOUPLE pin on or off.
 ******************************************************************************/
sl_status_t sl_efp_emu_ldo_enable(sl_efp_handle_t handle, bool enable)
{
  if (handle->init_data.is_host_efp) {

  #if defined(_SILICON_LABS_32B_SERIES_1)
    if (enable) {
      *(volatile uint32_t*)0x400E303C &= ~0x00000040UL;
    } else {
      *(volatile uint32_t*)0x400E303C |= 0x00000040UL;
    }
    return SL_STATUS_OK;

  #elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
    SE_Command_t command = SE_COMMAND_DEFAULT(SE_COMMAND_PROTECTED_REGISTER |
                                              SE_COMMAND_OPTION_WRITE);
    SE_addParameter(&command, 0x4000408c);    // Address
    SE_addParameter(&command, 1 << 14);       // Mask
    if (enable) {
      SE_addParameter(&command, 0);           // Value
    } else {
      SE_addParameter(&command, 1 << 14);     // Value
    }

    SE_executeCommand(&command);
    if (SE_readCommandResponse() != SE_RESPONSE_OK) {
      return SL_STATUS_FAIL;
    }
    return SL_STATUS_OK;

  #else
    #warning "Internal LDO control not implemented for this device family."
    EFM_ASSERT(false);
    return SL_STATUS_NOT_SUPPORTED;
  #endif

  } else {
    return SL_STATUS_FAIL;  // This was not a host EFP instance.
  }
}

/***************************************************************************//**
 * @brief
 *   Initialize EFP driver and configure underlying EFP hardware.
 ******************************************************************************/
sl_status_t sl_efp_init(sl_efp_handle_t handle, const sl_efp_init_data_t *init)
{
  int i;
  uint8_t *p;
  uint8_t tmp = 0;
  sl_status_t ret_val;

  if (init->is_host_efp) {
    if (host_efp == NULL) {
      host_efp = handle;
    } else {
      return SL_STATUS_FAIL;  // Only allow one host EFP instance.
    }
  }

  // Keep a copy of init data in the handle.
  handle->init_data = *init;

  // Assemble an I2C SPM initialization structure.
  I2CSPM_Init_TypeDef i2c_init = {
    .port              = init->i2c_peripheral,
    .sclPort           = init->i2c_scl_port,
    .sclPin            = init->i2c_scl_pin,
    .sdaPort           = init->i2c_sda_port,
    .sdaPin            = init->i2c_sda_pin,
    #if defined(_SILICON_LABS_32B_SERIES_0)
      .portLocation;   = init->i2c_port_location,
    #elif defined(_SILICON_LABS_32B_SERIES_1)
      .portLocationScl = init->i2c_scl_port_location,
      .portLocationSda = init->i2c_sda_port_location,
    #endif
    .i2cRefFreq        = 0,
    .i2cMaxFreq        = I2C_FREQ_FASTPLUS_MAX,
    .i2cClhr           = i2cClockHLRStandard
  };

  if ( false ) {
  #if defined(I2C0)
  } else if (init->i2c_peripheral == I2C0) {
    handle->i2c_clock = cmuClock_I2C0;
    #if defined(_SILICON_LABS_32B_SERIES_2)
      handle->i2c_peripheral_index = 0;
    #endif
  #endif
  #if defined(I2C1)
  } else if (init->i2c_peripheral == I2C1) {
    handle->i2c_clock = cmuClock_I2C1;
    #if defined(_SILICON_LABS_32B_SERIES_2)
      handle->i2c_peripheral_index = 1;
    #endif
  #endif
  #if defined(I2C2)
  } else if (init->i2c_peripheral == I2C2) {
    handle->i2c_clock = cmuClock_I2C2;
    #if defined(_SILICON_LABS_32B_SERIES_2)
      handle->i2c_peripheral_index = 2;
    #endif
  #endif
  }

  // Initialize I2C interface.
  I2CSPM_Init(&i2c_init);
  handle->in_direct_mode = false;

  // Enable I2C bus internal pullups and slow mode.
  // Note: Can be removed when all old EFP boards are obsoleted.
  ret_val = sl_efp_write_register(handle, EFP01_I2C_CTRL, 0x09);

  enable_i2c_pins(handle, true);

  // Do configuration register writes if a configuration is defined.
  if ((init->config_size > 0) && (ret_val == SL_STATUS_OK)){
    i = init->config_size;
    p = init->config_data;
    while (i && (ret_val == SL_STATUS_OK)) {
      ret_val = sl_efp_write_register(handle, *p, *(p + 1));
      i--;
      p += 2;
    }
  }

  // Configure GPIO pin as EFP IRQ input.
  if ((init->enable_irq_pin) && (ret_val == SL_STATUS_OK)) {
    // Clear interrupt flags.
    ret_val  = sl_efp_read_register(handle, EFP01_STATUS_G, &tmp);
    ret_val |= sl_efp_write_register(handle, EFP01_STATUS_G, tmp);
    ret_val |= sl_efp_read_register(handle, EFP01_STATUS_V, &tmp);
    ret_val |= sl_efp_write_register(handle, EFP01_STATUS_V, tmp);
    if (ret_val == SL_STATUS_OK) {
      GPIO_PinModeSet(init->irq_port, init->irq_pin, gpioModeInputPull, 1);
    }
  }

  // Prepare prelim workaround to speed-up EM2 wakeup timing.
  if (ret_val == SL_STATUS_OK) {
    ret_val = sl_efp_read_register(handle, EFP01_EM_CRSREG_CTRL, &handle->em_ctrl);
    handle->em_ctrl &= ~_EFP01_EM_CRSREG_CTRL_EM_SEL_MASK;
  }

  // Prepare for GPIO bitbanged "direct mode" EM transitions.
  if ((init->em_transition_mode == efp_em_transition_mode_gpio_bitbang)
      && (ret_val == SL_STATUS_OK)) {
    // Prepare GPIO for bitbang use.
    ret_val = sl_efp_enable_direct_mode(handle);
  }

  return ret_val;
}

/***************************************************************************//**
 * @brief
 *   Read EFP OTP register.
 ******************************************************************************/
sl_status_t sl_efp_read_otp(sl_efp_handle_t handle, uint8_t addr, uint8_t *data)
{
  uint8_t read_value;
  sl_status_t ret_val;

  ret_val = sl_efp_write_register(handle, 0x0F, 0x06);  // Enable OTP access.

  if (ret_val == SL_STATUS_OK) { // Need a few us delay, use reg. read as delay.
    ret_val = sl_efp_read_register(handle, EFP01_OTP_STATCTRL, &read_value);
  }

  if (ret_val == SL_STATUS_OK) {                        // Setup OTP address.
    ret_val = sl_efp_write_register(handle, EFP01_OTP_ADDR, addr & 0x7F);
  }

  if (ret_val == SL_STATUS_OK) {                        // Issue OTP read command.
    ret_val = sl_efp_write_register_field(handle,
                                          EFP01_OTP_STATCTRL,
                                          1,
                                          _EFP01_OTP_STATCTRL_CMD_READOTP_MASK,
                                          _EFP01_OTP_STATCTRL_CMD_READOTP_SHIFT);
  }

  if (ret_val == SL_STATUS_OK) { // Need a few us delay, use reg. read as delay.
    ret_val = sl_efp_read_register(handle, EFP01_OTP_STATCTRL, &read_value);
  }

  if (ret_val == SL_STATUS_OK) {                        // Readout OTP data.
    ret_val = sl_efp_read_register(handle, EFP01_OTP_RDATA, &read_value);
  }

  if (ret_val == SL_STATUS_OK) {                        // Disable OTP access.
    *data = read_value;                                 // OTP value.
    ret_val = sl_efp_write_register(handle, 0x0F, 0x00);
  }

  return ret_val;
}

/***************************************************************************//**
 * @brief
 *   Read EFP control register.
 ******************************************************************************/
sl_status_t sl_efp_read_register(sl_efp_handle_t handle, uint8_t addr, uint8_t *data)
{
  uint8_t read_value;

  I2C_TransferSeq_TypeDef seq = {
    .addr   = EFP_EFP01_I2C_ADDR,
    .flags  = I2C_FLAG_WRITE_READ,
    .buf[0] = { .data = &addr, .len = 1 },
    .buf[1] = { .data = &read_value, .len = 1 }
  };

  if (handle->in_direct_mode) {
    enable_i2c_pins(handle, true);
  }

  if (I2CSPM_Transfer(handle->init_data.i2c_peripheral, &seq) != i2cTransferDone) {
    EFM_ASSERT(false);
    return SL_STATUS_IO;
  }
  *data = read_value;
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Read EFP control register field.
 ******************************************************************************/
sl_status_t sl_efp_read_register_field(sl_efp_handle_t handle,
                                       uint8_t addr,
                                       uint8_t *data,
                                       uint8_t mask,
                                       uint8_t pos)
{
  uint8_t tmp;
  sl_status_t ret_val;

  ret_val = sl_efp_read_register(handle, addr, &tmp);
  if (ret_val == SL_STATUS_OK) {
    *data = (tmp & mask) >> pos;
  }
  return ret_val;
}

/***************************************************************************//**
 * @brief
 *   Reset EFP. Perform a full reset of the EFP, this is equivalent to a power
 *   on reset.
 ******************************************************************************/
sl_status_t sl_efp_reset(sl_efp_handle_t handle)
{
  return sl_efp_write_register(handle,EFP01_CMD, _EFP01_CMD_RESET_MASK);
}

/***************************************************************************//**
 * @brief
 *   Set EM transition mode.
 ******************************************************************************/
sl_status_t sl_efp_set_em_transition_mode(sl_efp_handle_t handle,
                                          sl_efp_em_transition_mode_t mode)
{
  handle->init_data.em_transition_mode = mode;
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOA EM01 peak output current.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_em01_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int voa_mv,
                                             unsigned int inductor_nh)
{
  long l;
  float f;

  f = (current_ma - 90.0f - (25.0f * (vddb_mv - voa_mv) / inductor_nh)) / 9.0f;
  l = lroundf(f);
  l = SL_MAX(l, 0);
  l = SL_MIN(l, _EFP01_BB_IPK_BB_IPK_MASK >> _EFP01_BB_IPK_BB_IPK_SHIFT);

  return sl_efp_write_register_field(handle, EFP01_BB_IPK, (uint8_t)l,
                                     _EFP01_BB_IPK_BB_IPK_MASK,
                                     _EFP01_BB_IPK_BB_IPK_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOA EM23 peak output current.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_em23_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int voa_mv,
                                             unsigned int inductor_nh)
{
  long l;
  float f;

  f = (current_ma - 108.0f - (25.0f * (vddb_mv - voa_mv) / inductor_nh)) / 36.0f;
  l = lroundf(f);
  l = SL_MAX(l, 0);
  l = SL_MIN(l, _EFP01_BB_IPK_BB_IPK_EM2_MASK >> _EFP01_BB_IPK_BB_IPK_EM2_SHIFT);

  return sl_efp_write_register_field(handle, EFP01_BB_IPK, (uint8_t)l,
                                     _EFP01_BB_IPK_BB_IPK_EM2_MASK,
                                     _EFP01_BB_IPK_BB_IPK_EM2_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOA mode.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_mode(sl_efp_handle_t handle, sl_efp_voa_mode_t mode)
{
  return sl_efp_write_register_field(handle, EFP01_BB_CTRL3, mode,
                                     _EFP01_BB_CTRL3_BB_MODE_MASK,
                                     _EFP01_BB_CTRL3_BB_MODE_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set VOA SW (switched output) mode.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_sw_mode(sl_efp_handle_t handle, sl_efp_voa_sw_mode_t mode)
{
  return sl_efp_write_register_field(handle, EFP01_BIAS_SW, mode,
                                     _EFP01_BIAS_SW_VOA_SW_CON_MASK,
                                     _EFP01_BIAS_SW_VOA_SW_CON_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOA output voltage.
 ******************************************************************************/
sl_status_t sl_efp_set_voa_voltage(sl_efp_handle_t handle, unsigned int voltage_mv)
{
  long l;

  l = lroundf((voltage_mv - 1737.4f) / 30.6f);
  l = SL_MAX(l, 0);
  l = SL_MIN(l, _EFP01_VOA_V_VOA_V_MASK >> _EFP01_VOA_V_VOA_V_SHIFT);

  return sl_efp_write_register(handle, EFP01_VOA_V, (uint8_t)l);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOB EM01 peak output current.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_em01_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int vob_mv,
                                             unsigned int inductor_nh)
{
  long l;
  float f;

  f = (current_ma - 90.0f - (25.0f * (vddb_mv - vob_mv) / inductor_nh)) / 9.0f;
  l = lroundf(f);
  l = SL_MAX(l, 0);
  l = SL_MIN(l, _EFP01_BK_IPK_BK_IPK_MASK >> _EFP01_BK_IPK_BK_IPK_SHIFT);

  return sl_efp_write_register_field(handle, EFP01_BK_IPK, (uint8_t)l,
                                     _EFP01_BK_IPK_BK_IPK_MASK,
                                     _EFP01_BK_IPK_BK_IPK_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOB EM01 output voltage.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_em01_voltage(sl_efp_handle_t handle, unsigned int voltage_mv)
{
  long l;

  l = lroundf((voltage_mv - 809.5f) / 22.3f);
  l = SL_MAX(l, 0);
  l = SL_MIN(l, _EFP01_VOB_EM0_V_VOB_EM0_V_MASK >> _EFP01_VOB_EM0_V_VOB_EM0_V_SHIFT);

  return sl_efp_write_register_field(handle, EFP01_VOB_EM0_V, (uint8_t)l,
                                     _EFP01_VOB_EM0_V_VOB_EM0_V_MASK,
                                     _EFP01_VOB_EM0_V_VOB_EM0_V_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOB EM23 peak output current.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_em23_peak_current(sl_efp_handle_t handle,
                                             unsigned int current_ma,
                                             unsigned int vddb_mv,
                                             unsigned int vob_mv,
                                             unsigned int inductor_nh)
{
  long l;
  float f;

  f = (current_ma - 108.0f - (25.0f * (vddb_mv - vob_mv) / inductor_nh)) / 36.0f;
  l = lroundf(f);
  l = SL_MAX(l, 0);
  l = SL_MIN(l, _EFP01_BK_IPK_BK_IPK_EM2_MASK >> _EFP01_BK_IPK_BK_IPK_EM2_SHIFT);

  return sl_efp_write_register_field(handle, EFP01_BK_IPK, (uint8_t)l,
                                     _EFP01_BK_IPK_BK_IPK_EM2_MASK,
                                     _EFP01_BK_IPK_BK_IPK_EM2_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOB EM23 output voltage.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_em23_voltage(sl_efp_handle_t handle, unsigned int voltage_mv)
{
  long l;

  l = lroundf((voltage_mv - 809.5f) / 22.3f);
  l = SL_MAX(l, 0);
  l = SL_MIN(l, _EFP01_VOB_EM2_V_VOB_EM2_V_MASK >> _EFP01_VOB_EM2_V_VOB_EM2_V_SHIFT);

  return sl_efp_write_register(handle, EFP01_VOB_EM2_V, (uint8_t)l);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOB mode.
 ******************************************************************************/
sl_status_t sl_efp_set_vob_mode(sl_efp_handle_t handle, sl_efp_vob_mode_t mode)
{
  return sl_efp_write_register_field(handle, EFP01_BK_CTRL1, mode,
                                     _EFP01_BK_CTRL1_BK_MODE_MASK,
                                     _EFP01_BK_CTRL1_BK_MODE_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Set regulator VOC output voltage.
 ******************************************************************************/
sl_status_t sl_efp_set_voc_voltage(sl_efp_handle_t handle, unsigned int voltage_mv)
{
  long l;

  l = lroundf((voltage_mv - 1717.8f) / 30.5f);
  l = SL_MAX(l, 0);
  l = SL_MIN(l, _EFP01_VOC_V_VOC_V_MASK >> _EFP01_VOC_V_VOC_V_SHIFT);

  return sl_efp_write_register_field(handle, EFP01_VOC_V, (uint8_t)l,
                                     _EFP01_VOC_V_VOC_V_MASK,
                                     _EFP01_VOC_V_VOC_V_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Write EFP control register.
 ******************************************************************************/
sl_status_t sl_efp_write_register(sl_efp_handle_t handle, uint8_t addr, uint8_t data)
{
  I2C_TransferSeq_TypeDef seq = {
    .addr   = EFP_EFP01_I2C_ADDR,
    .flags  = I2C_FLAG_WRITE_WRITE,
    .buf[0] = { .data = &addr, .len = 1 },
    .buf[1] = { .data = &data, .len = 1 }
  };

  if (handle->in_direct_mode) {
    enable_i2c_pins(handle, true);
  }

  if (I2CSPM_Transfer(handle->init_data.i2c_peripheral, &seq) != i2cTransferDone) {
    EFM_ASSERT(false);
    return SL_STATUS_IO;
  }
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Write EFP control register field.
 ******************************************************************************/
sl_status_t sl_efp_write_register_field(sl_efp_handle_t handle,
                                        uint8_t addr,
                                        uint8_t data,
                                        uint8_t mask,
                                        uint8_t pos)
{
  uint8_t tmp;
  sl_status_t ret_val;

  ret_val = sl_efp_read_register(handle, addr, &tmp);
  if (ret_val == SL_STATUS_OK) {
    tmp = (tmp & ~mask) | ((data << pos) & mask);
    ret_val = sl_efp_write_register(handle, addr, tmp);
  }
  return ret_val;
}

/** @} (end addtogroup SL_EFP) */
/** @} (end addtogroup extdrv) */
