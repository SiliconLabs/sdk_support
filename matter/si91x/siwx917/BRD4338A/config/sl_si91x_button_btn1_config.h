/***************************************************************************/ /**
                                                                               * @file sl_si91x_button_config.h
                                                                               * @brief Button Driver Configuration
                                                                               *******************************************************************************
                                                                               * # License
                                                                               * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
                                                                               *******************************************************************************/

#ifndef SL_SI91X_BUTTON_BTN1_CONFIG_H
#define SL_SI91X_BUTTON_BTN1_CONFIG_H

#include "sl_si91x_button.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_BUTTON_CONFIG_BTN1_INTR> Button Interrupt Configuration
// <HIGH_LEVEL_INTERRUPT => High level interrupt
// <LOW_LEVEL_INTERRUPT => Low level interrupt
// <HIGH_LEVEL_AND_LOW_LEVEL_INTERRUPT => High level and low level interrupt
// <RISE_EDGE_INTERRUPT => Rise edge interrupt
// <FALL_EDGE_INTERRUPT => Fall edge interrupt
// <RISE_EDGE_AND_FALL_EDGE_INTERRUPT => Rise edge and fall edge interrupt
// <i> Default: RISE_EDGE_AND_FALL_EDGE_INTERRUPT
#define SL_BUTTON_CONFIG_BTN1_INTR RISE_EDGE_AND_FALL_EDGE_INTERRUPT

// <<< end of configuration section >>>

#endif // SL_SI91X_BUTTON_BTN1_CONFIG_H
