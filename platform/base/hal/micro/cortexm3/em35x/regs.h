/***************************************************************************//**
 * @file
 * @brief This file pulls in the appropriate register
 * headers based on the specific Cortex-M3 being
 * compiled.
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
  #include "em317/regs.h"
#elif defined(CORTEXM3_EM346)
  #include "em346/regs.h"
#elif defined(CORTEXM3_EM351)
  #include "em351/regs.h"
#elif defined(CORTEXM3_EM355)
  #include "em355/regs.h"
#elif defined(CORTEXM3_EM3555)
  #include "em3555/regs.h"
#elif defined(CORTEXM3_EM356)
  #include "em356/regs.h"
#elif defined(CORTEXM3_EM357)
  #include "em357/regs.h"
#elif defined(CORTEXM3_EM3581)
  #include "em3581/regs.h"
#elif defined(CORTEXM3_EM3582)
  #include "em3582/regs.h"
#elif defined(CORTEXM3_EM3585)
  #include "em3585/regs.h"
#elif defined(CORTEXM3_EM3586)
  #include "em3586/regs.h"
#elif defined(CORTEXM3_EM3587)
  #include "em3587/regs.h"
#elif defined(CORTEXM3_EM3588)
  #include "em3588/regs.h"
#elif defined(CORTEXM3_EM359)
  #include "em359/regs.h"
#elif defined(CORTEXM3_EM3591)
  #include "em3591/regs.h"
#elif defined(CORTEXM3_EM3592)
  #include "em3592/regs.h"
#elif defined(CORTEXM3_EM3595)
  #include "em3595/regs.h"
#elif defined(CORTEXM3_EM3596)
  #include "em3596/regs.h"
#elif defined(CORTEXM3_EM3597)
  #include "em3597/regs.h"
#elif defined(CORTEXM3_EM3598)
  #include "em3598/regs.h"
#elif defined(CORTEXM3_SKY66107)
  #include "sky66107/regs.h"
#else
  #error Unknown Cortex-M3 micro
#endif
