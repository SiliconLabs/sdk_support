/***************************************************************************//**
 * @file
 * @brief This is the header for a simple PRS channel configuration API.
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
#include <stdint.h>
#include <stdbool.h>

/**
 * Configure the PRS to use a specific source and signal for the specified
 * channel/location combo.
 * @param channel The PRS channel to use for this signal.
 * @param loc The location to route this PRS channel to. See the datasheet for
 * more information. Set this to 0xFF to disable the output channel.
 * @param source The PRS source to use for this channel.
 * @param signal The signal in the above source to use for this channel.
 * @param invert Set this to true to invert the polarity of the output signal.
 */
void halConfigurePrs(uint8_t channel,
                     uint8_t loc,
                     uint8_t source,
                     uint8_t signal,
                     bool invert);
