#ifndef SL_EFP_INST_CONFIG_H
#define SL_EFP_INST_CONFIG_H

#include "sl_efp.h"

#ifdef __cplusplus
extern "C" {
#endif

// <<< Use Configuration Wizard in Context Menu >>>

// <h>EFP driver configuration

// <o SL_EFP_EFP0_EM_CTRL_MODE> Selects method of controlling EFP Energy Mode (EM) transitions.
// <efp_em_transition_mode_gpio_bitbang=> GPIO driven direct mode EM transitions
// <efp_em_transition_mode_i2c=> I2C transfers control EM transitions
// <efp_em_transition_mode_emu=> Builtin EMU controlled direct mode EM transitions
// <i> Default: efp_em_transition_mode_i2c
#define SL_EFP_EFP0_EM_CTRL_MODE       efp_em_transition_mode_i2c

// <q SL_EFP_EFP0_ENABLE_IRQ> Enable GPIO as interrupt input line from EFP.
// <i> Default: 1
#define SL_EFP_EFP0_ENABLE_IRQ         1

// <q SL_EFP_EFP0_POWERS_HOST> This EFP powers host SoC.
// <i> Default: 1
#define SL_EFP_EFP0_POWERS_HOST        1

// </h> end EFP configuration

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <gpio optional> SL_EFP_EFP0_IRQ
// $[GPIO_SL_EFP_EFP0_IRQ]
#define SL_EFP_EFP0_IRQ_PORT                     gpioPortA
#define SL_EFP_EFP0_IRQ_PIN                      0

// [GPIO_SL_EFP_EFP0_IRQ]$

// <i2c signal=SDA,SCL> SL_EFP_EFP0_I2C
// $[I2C_SL_EFP_EFP0_I2C]
#define SL_EFP_EFP0_I2C_PERIPHERAL               I2C1
#define SL_EFP_EFP0_I2C_PERIPHERAL_NO            1

// I2C1 SDA on PC01
#define SL_EFP_EFP0_I2C_SDA_PORT                 gpioPortC
#define SL_EFP_EFP0_I2C_SDA_PIN                  1

// I2C1 SCL on PC00
#define SL_EFP_EFP0_I2C_SCL_PORT                 gpioPortC
#define SL_EFP_EFP0_I2C_SCL_PIN                  0

// [I2C_SL_EFP_EFP0_I2C]$
// <<< sl:end pin_tool >>>

#define SL_EFP_EFP0_INIT {                                                    \
    .config_size = 0,                                    /* No initial config */     \
    .config_data = NULL,                                 /* No config data */        \
    .is_host_efp = SL_EFP_EFP0_POWERS_HOST,          /* This EFP powers host */  \
    .em_transition_mode = SL_EFP_EFP0_EM_CTRL_MODE,  /* EFP EM transition mode*/ \
    .enable_irq_pin = SL_EFP_EFP0_ENABLE_IRQ,        /* Init GPIO as EFP IRQ */  \
    .irq_port = SL_EFP_EFP0_IRQ_PORT,                /* EFP IRQ port */          \
    .irq_pin = SL_EFP_EFP0_IRQ_PIN,                  /* EFP IRQ pin */           \
    .i2c_peripheral = SL_EFP_EFP0_I2C_PERIPHERAL,    /* I2C port instance */     \
    .i2c_scl_port = SL_EFP_EFP0_I2C_SCL_PORT,        /* SCL port */              \
    .i2c_scl_pin = SL_EFP_EFP0_I2C_SCL_PIN,          /* SCL pin */               \
    .i2c_sda_port = SL_EFP_EFP0_I2C_SDA_PORT,        /* SDA port */              \
    .i2c_sda_pin = SL_EFP_EFP0_I2C_SDA_PIN,          /* SDA pin */               \
}

#ifdef __cplusplus
}
#endif

#endif /* SL_EFP_INST_CONFIG_H */
