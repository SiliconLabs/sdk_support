/***************************************************************************//**
 * @brief header for c based interrupt test
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
 
#ifndef __IEC60335_CLASS_B_INTERRUPT_TEST_H__
#define __IEC60335_CLASS_B_INTERRUPT_TEST_H__

#include "iec60335_class_b.h"

/*! @addtogroup IEC60335_IRQ_TEST
 * @{
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define IgnoreIRQHandler    0   /*!< original handler is ignored */
#define CallIRQHandler      1   /*!< original handler is called */

/*!
 * @brief  call the original vector
 *
 * @param vect IRQ index
 * @image html Interrupt_call.jpg
 */
/* void __call_Vect(uint32_t vect); */

/*!
 * @brief   Interrupt replacement handler to check interrupt occurrences
 * @note    The interrupt test requires an intermediate call and work on the test data.
 *          To achieve this goal the replacement handler is called instead of the user handler.
 *          If the corresponding Mode flag is set the routine calls the original vector handler.
 * @image html Interrupt_Replacement.jpg
 */
void IEC60335_IRQReplacementHandler(void);

/*!
 * @brief   Initialization of a specified interrupt test
 * @param   IRQn            number of the interrupt to test\n
 *                          if number smaller than "SysTick_IRQn" the function deactivates all tests\n
 *                          numbers bigger than "PendSV_IRQn" activates the test\n
 *                          calling a second time with the same IRQn will deactivate this test
 * @param   Mode            configure interrupt is calling the original handler
 * @param   CountSetup      counters of interrupt occurrences
 * @note    The interrupt test is deactivated when called with a exception number (< SysTick_IRQn) on the IRQn parameter.
 *          In this case the original vector table is restored and all flags are deleted.
 * @attention Ensure to place the function call #IEC60335_ClassB_InterruptOcurred into the corresponding
 * interrupt service handler!
 * @image html Interrupt_Init.jpg
 */
void IEC60335_ClassB_InitInterruptTest(IRQn_Type IRQn, uint8_t Mode, IRQTestData_t *CountSetup);

/*!
 * @brief   The interrupt check routine must be called once in known equidistant times.
 *
 * @attention   If this function is disturbed by active tested interrupts,
 *              the result counter may be out of range.
 * @param   IRQn   number of the interrupt to test
 * @return  passed or failed. See \link #testResult_enum testResult_t \endlink.
 * @image html Interrupt_Check.jpg
 */
testResult_t IEC60335_ClassB_InterruptCheck(IRQn_Type IRQn);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*!
 * @}
 */

#endif  /* __IEC60335_CLASS_B_INTERRUPT_TEST_H__ */

/************************************** EOF *********************************/
