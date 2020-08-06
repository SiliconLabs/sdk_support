/***************************************************************************//**
 * @file
 * @brief This file pulls in the appropriate MPU
 * configuration based on the specific Cortex-M3
 * being compiled.
 * THIS IS A GENERATED FILE. DO NOT EDIT.
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

#if defined(CORTEXM3_EM317)
  #include "em35x/em317/mpu-config.h"
#elif defined(CORTEXM3_EM346)
  #include "em35x/em346/mpu-config.h"
#elif defined(CORTEXM3_EM351)
  #include "em35x/em351/mpu-config.h"
#elif defined(CORTEXM3_EM355)
  #include "em35x/em355/mpu-config.h"
#elif defined(CORTEXM3_EM3555)
  #include "em35x/em3555/mpu-config.h"
#elif defined(CORTEXM3_EM356)
  #include "em35x/em356/mpu-config.h"
#elif defined(CORTEXM3_EM357)
  #include "em35x/em357/mpu-config.h"
#elif defined(CORTEXM3_EM3581)
  #include "em35x/em3581/mpu-config.h"
#elif defined(CORTEXM3_EM3582)
  #include "em35x/em3582/mpu-config.h"
#elif defined(CORTEXM3_EM3585)
  #include "em35x/em3585/mpu-config.h"
#elif defined(CORTEXM3_EM3586)
  #include "em35x/em3586/mpu-config.h"
#elif defined(CORTEXM3_EM3587)
  #include "em35x/em3587/mpu-config.h"
#elif defined(CORTEXM3_EM3588)
  #include "em35x/em3588/mpu-config.h"
#elif defined(CORTEXM3_EM359)
  #include "em35x/em359/mpu-config.h"
#elif defined(CORTEXM3_EM3591)
  #include "em35x/em3591/mpu-config.h"
#elif defined(CORTEXM3_EM3592)
  #include "em35x/em3592/mpu-config.h"
#elif defined(CORTEXM3_EM3595)
  #include "em35x/em3595/mpu-config.h"
#elif defined(CORTEXM3_EM3596)
  #include "em35x/em3596/mpu-config.h"
#elif defined(CORTEXM3_EM3597)
  #include "em35x/em3597/mpu-config.h"
#elif defined(CORTEXM3_EM3598)
  #include "em35x/em3598/mpu-config.h"
#elif defined(CORTEXM3_SKY66107)
  #include "em35x/sky66107/mpu-config.h"
#endif
