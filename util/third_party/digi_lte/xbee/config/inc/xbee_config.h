/***************************************************************************//**
 * # License
 * 
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 * 
 ******************************************************************************/

#ifndef XBEECONFIG_H_
#define XBEECONFIG_H_

#include "xbee/device.h"

enum xbee_mode {
  XBEE_CONFIG_MODE_TRANSPARENT, // 0
  XBEE_CONFIG_MODE_API,
  XBEE_CONFIG_MODE_APIESCAPE,
  XBEE_CONFIG_MODE_NA,
  XBEE_CONFIG_MODE_MICROPYTHON,
  XBEE_CONFIG_MODE_BYPASS
};

enum xbee_carrier_profile {
  XBEE_CONFIG_CARRIER_AUTO_DETECT,  // 0
  XBEE_CONFIG_CARRIER_RESERVED,
  XBEE_CONFIG_CARRIER_ATT,          // AT&T
  XBEE_CONFIG_CARRIER_VERIZON
};

#ifdef __cplusplus
extern "C" {
#endif
/**
  @brief Configures the XBee's baudrate, API mode, and carrier profile

  @param[in]   xbee           A pointer to the XBee device object to configure
  @param[in]   baud           A valid baudrate to set on the xbee
  @param[in]   mode           An enumeration specifying the API mode
  @param[in]   carrierProfile An enumeration specifiying the carrier profile
  @param[in]   resetParam     Reset all other parameters to factory default

  @retval 0          Success
  @retval -EINVAL    Invalid parameter passed to function
  @retval -ETIMEDOUT A send or receive call has timed out
  @retval -EIO       While receiving, we got an invalid response
*/
int configureXBee(xbee_dev_t *xbee,
                  int baud,
                  enum xbee_mode mode,
                  enum xbee_carrier_profile carrierProfile,
                  bool resetParam);


/**
  @brief Configures the XBee's Access Point Name APN to predefined value

  @param[in]   xbee		A pointer to the XBee device object to configure

  @retval 0          Success
  @retval 1          Success, The APN was already set correctly
  @retval -EINVAL    Invalid parameter passed to function
  @retval -ETIMEDOUT A send or receive call has timed out
  @retval -EIO       While receiving, we got an invalid response
*/
int configureAPN(xbee_dev_t *xbee);

#ifdef __cplusplus
}
#endif

#endif /* XBEECONFIG_H_ */
