/***************************************************************************//**
 * @brief header file containing all global types and definitions for unit tests
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
 
#ifndef __IEC60335_CLASS_B_TESSY_H__
#define __IEC60335_CLASS_B_TESSY_H__

#ifdef TESSY
#undef RTC
#undef CMU
#undef TIMER0
#undef SysTick
#undef NVIC
#undef SCB
#undef RMU
#undef WDOG
#ifdef __I
#undef __I
#define __I volatile
#endif
RTC_TypeDef*         RTC_Register     = (RTC_TypeDef*)  RTC_BASE;
CMU_TypeDef*         CMU_Register     = (CMU_TypeDef*)  CMU_BASE;
TIMER_TypeDef*       TIMER0_Register  = (TIMER_TypeDef*)TIMER0_BASE;
SysTick_Type*        SysTick_Register = (SysTick_Type*) SysTick_BASE;
NVIC_Type*           NVIC_Register    = (NVIC_Type*)    NVIC_BASE;
SCB_Type*            SCB_Register     = (SCB_Type*)     SCB_BASE;
RMU_TypeDef*         RMU_Register     = (RMU_TypeDef*)  RMU_BASE;
WDOG_TypeDef*        WDOG_Register    = (WDOG_TypeDef*) WDOG_BASE;
#define RTC          RTC_Register
#define CMU          CMU_Register
#define TIMER0       TIMER0_Register
#define SysTick      SysTick_Register
#define NVIC         NVIC_Register
#define SCB          SCB_Register
#define RMU          RMU_Register
#define WDOG         WDOG_Register
#endif

#endif  /* __IEC60335_CLASS_B_TESSY_H__ */

/************************************** EOF *********************************/
