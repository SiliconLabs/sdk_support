/***************************************************************************//**
 * @file
 * @brief NVIC Config Header
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
#include "emlib_config.h"

/** @addtogroup nvic_config
 * Nested Vectored Interrupt Controller configuration header.
 *
 * This header defines the functions called by all of the NVIC exceptions/
 * interrupts.  The following are the nine peripheral ISRs available for
 * modification.  To use one of these ISRs, it must be instantiated
 * somewhere in the HAL.  Each ISR may only be instantiated once.  It is
 * not necessary to instantiate all or any of these ISRs (a stub will
 * be automatically generated if an ISR is not instantiated).
 *
 * - \code void halTimer1Isr(void); \endcode
 * - \code void halTimer2Isr(void); \endcode
 * - \code void halSc1Isr(void);    \endcode
 * - \code void halSc1Isr(void);    \endcode
 * - \code void halAdcIsr(void);    \endcode
 * - \code void halIrqAIsr(void);   \endcode
 * - \code void halIrqBIsr(void);   \endcode
 * - \code void halIrqCIsr(void);   \endcode
 * - \code void halIrqDIsr(void);   \endcode
 *
 * @note This file should \b not be modified.
 */

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// \b NOTE NOTE NOTE NOTE NOTE NOTE - The physical layout of this file, that
// means the white space, is CRITICAL!  Since this file is \#include'ed by
// the assembly file isr-stubs.s79, the white space in this file translates
// into the white space in that file and the assembler has strict requirements.
// Specifically, there must be white space *before* each "SEGMENT()" and there
// must be an *empty line* between each "EXCEPTION()" and "SEGMENT()".
//
// \b NOTE NOTE NOTE - The order of the EXCEPTIONS in this file is critical
// since it translates to the order they are placed into the vector table in
// cstartup.
//
// The purpose of this file is to consolidate NVIC configuration, this
// includes basic exception handler (ISR) function definitions, into a single
// place where it is easily tracked and changeable.
//
// We establish 8 levels of priority (3 bits), with 0 (0 bits) of tie break
// subpriority. Lower priority values are higher priorities. This means that
// 0 is the highest and 7 is the lowest. The NVIC mapping is detailed below.
//

//The 'PRIGROUP' field is 3 bits within the AIRCR register and indicates the
//bit position within a given exception's 8-bit priority field to the left of
//which is the "binary point" separating the preemptive priority level (in the
//most-significant bits) from the subpriority (in the least-significant bits).
//The preemptive priority determines whether an interrupt can preempt an
//executing interrupt. The subpriority helps choose which interrupt to run if
//multiple interrupts with the same preemptive priority are active at the same
//time. If no supriority is given or there is a tie then the hardware defined
//exception number is used to break the tie.
//
//The table below shows for each PRIGROUP value (the PRIGROUP value is the
//number on the far left) how the priority bits are split and how this maps
//to the priorities on chip. A 'P' is preemption bit, 'S' is a subpriority bit
//and an 'X' indicates that that bit is not implemented.
//0=7:1= PPPXXXX.X
//1=6:2= PPPXXX.XX
//2=5:3= PPPXX.XXX
//3=4:4= PPPX.XXXX
//4=3:5= PPP.XXXXX
//5=2:6= PP.SXXXXX
//6=1:7= P.SSXXXXX
//7=0:8= SSSXXXXXX
//
//Below is the default priority configuration for the chip's interrupts
// Pri.Sub  Purpose
//   0.0    faults (highest)
//   1.0    FPUEH, WDOG
//   2.0    not used
//   3.0    DISABLE_INTERRUPTS(), INTERRUPTS_OFF(), ATOMIC()
//   4.0    normal interrupts
//   5.0    not used
//   6.0    not used
//   7.0    PendSV (lowest)
#if defined(FREE_RTOS)
// FreeRTOS is compatible with our default choice of PRIGROUP_POSITION
#endif
#define PRIGROUP_POSITION (4)  // PPP.XXXXX

// Priority level used by DISABLE_INTERRUPTS() and INTERRUPTS_OFF()
// Must be lower priority than pendsv
// NOTE!! INTERRUPTS_DISABLED_PRIORITY AFFECTS SPRM.S79
// NOTE!! FreeRTOSConfig.h configMAX_SYSCALL_INTERRUPT_PRIORITY must match
//        INTERRUPTS_DISABLED_PRIORITY!
#define NVIC_ATOMIC CORE_ATOMIC_BASE_PRIORITY_LEVEL
#define INTERRUPTS_DISABLED_PRIORITY  (NVIC_ATOMIC << (PRIGROUP_POSITION + 1))

//Exceptions with fixed priorities cannot be changed by software.  Simply make
//them 0 since they are high priorities anyways.
#define NVIC_FIXED (0)
//Reserved exceptions are not instantiated in the hardware.  Therefore
//exception priorities don't exist so just default them to lowest level.
#define NVIC_NONE  (0xFF)

#ifndef SEGMENT
  #define SEGMENT()
#endif
#ifndef SEGMENT2
  #define SEGMENT2()
#endif
#ifndef FIXED_EXCEPTION
  #define FIXED_EXCEPTION(vectorNumber, functionName, deviceIrqn, deviceIrqHandler) \
  EXCEPTION(vectorNumber, functionName, deviceIrqn, deviceIrqHandler, NVIC_FIXED, 0)
#endif
#ifndef PERM_EXCEPTION
  #define PERM_EXCEPTION(vectorNumber, functionName, deviceIrqn, deviceIrqHandler) \
  FIXED_EXCEPTION(vectorNumber, functionName, deviceIrqn, deviceIrqHandler)
#endif

// SEGMENT()
//   **Place holder required by isr-stubs.s79 to define __CODE__**
// SEGMENT2()
//   **Place holder required by isr-stubs.s79 to define __THUMB__**
// EXCEPTION(vectorNumber, functionName, priorityLevel, subpriority)
//   vectorNumber = exception number defined by hardware (not used anywhere)
//   functionName = name of the function that the exception should trigger
//   priorityLevel = priority level of the function
//   supriority = Used to break ties between exceptions at the same level
// FIXED_EXCEPTION
//   is used to define an exception that doesn't have a corresponding
//   priority level register so it should be ignored by the code that
//   sets interrupt priorities.  While there is a NVIC_FIXED priority
//   level for completeness of information, it's safest to simply not
//   try to set a register that doesn't exist/cannot be set.
// PERM_EXCEPTION
//   is used to define an exception that should not be intercepted by the
//   interrupt debugging logic, or that not should have a weak stub defined.
//   Otherwise the definition is the same as FIXED_EXCEPTION.

//INTENTIONALLY INDENTED AND SPACED APART! Keep it that way!  See comment above!

/* *INDENT-OFF**/
    SEGMENT()
    SEGMENT2()
    PERM_EXCEPTION( 1, halEntryPoint, (IRQn_Type)(-15), Reset_Handler) //Reset

    SEGMENT()
    SEGMENT2()
    FIXED_EXCEPTION(2, halNmiIsr, NonMaskableInt_IRQn, NMI_Handler)

    SEGMENT()
    SEGMENT2()
    FIXED_EXCEPTION(3, halHardFaultIsr, HardFault_IRQn, HardFault_Handler)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(      4, halMemoryFaultIsr, MemoryManagement_IRQn, MemManage_Handler,        0,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(      5, halBusFaultIsr, BusFault_IRQn, BusFault_Handler,           0,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(      6, halUsageFaultIsr, UsageFault_IRQn, UsageFault_Handler,         0,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(      7, halReserved07Isr, (IRQn_Type)(-9), halReserved07Isr, NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(      8, halReserved08Isr, (IRQn_Type)(-8), halReserved08Isr, NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(      9, halReserved09Isr, (IRQn_Type)(-7), halReserved09Isr, NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     10, halReserved10Isr, (IRQn_Type)(-6), halReserved10Isr, NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()     // Above ATOMIC for FREE_RTOS task startup from ATOMIC level
    EXCEPTION(     11, halSvCallIsr, SVCall_IRQn, SVC_Handler, NVIC_ATOMIC-1,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     12, halDebugMonitorIsr, DebugMonitor_IRQn, DebugMon_Handler,       4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     13, halReserved13Isr, (IRQn_Type)(-3), halReserved13Isr, NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()     // Should be lowest priority
    EXCEPTION(     14, halPendSvIsr, PendSV_IRQn, PendSV_Handler,             7,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     15, halInternalSysTickIsr, SysTick_IRQn, SysTick_Handler,    4,         0)

    //The following handlers map to "External Interrupts 16 and above"
    //In the NVIC Interrupt registers, this corresponds to bits 33:0 with bit
    //0 being EMU (exception 16) and bit 33 being FPUEH (exception 49), etc.
    SEGMENT()
    SEGMENT2()
    EXCEPTION(     16, EMU_IRQHandler,EMU_IRQn,EMU_IRQHandler,               4,         0)

    SEGMENT()
    SEGMENT2()     // FRC High-pri a step above normal
    EXCEPTION(     17, FRC_PRI_IRQHandler,FRC_PRI_IRQn,FRC_PRI_IRQHandler,           3,         0)

    SEGMENT()
    SEGMENT2()     // WDOG warning is closest we can get to NMI
    EXCEPTION(     18, WDOG0_IRQHandler,WDOG0_IRQn,WDOG0_IRQHandler,             1,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     19, FRC_IRQHandler,FRC_IRQn,FRC_IRQHandler,               4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     20, MODEM_IRQHandler,MODEM_IRQn,MODEM_IRQHandler,             4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     21, RAC_SEQ_IRQHandler,RAC_SEQ_IRQn,RAC_SEQ_IRQHandler,           4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     22, RAC_RSM_IRQHandler,RAC_RSM_IRQn,RAC_RSM_IRQHandler,           4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     23, BUFC_IRQHandler,BUFC_IRQn,BUFC_IRQHandler,              4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     24, LDMA_IRQHandler,LDMA_IRQn,LDMA_IRQHandler,              4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     25, GPIO_EVEN_IRQHandler,GPIO_EVEN_IRQn,GPIO_EVEN_IRQHandler,         4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     26, TIMER0_IRQHandler,TIMER0_IRQn,TIMER0_IRQHandler,            4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     27, USART0_RX_IRQHandler,USART0_RX_IRQn,USART0_RX_IRQHandler,         4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     28, USART0_TX_IRQHandler,USART0_TX_IRQn,USART0_TX_IRQHandler,         4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     29, ACMP0_IRQHandler,ACMP0_IRQn,ACMP0_IRQHandler,             4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     30, ADC0_IRQHandler,ADC0_IRQn,ADC0_IRQHandler,              4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     31, IDAC0_IRQHandler,IDAC0_IRQn,IDAC0_IRQHandler,             4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     32, I2C0_IRQHandler,I2C0_IRQn,I2C0_IRQHandler,              4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     33, GPIO_ODD_IRQHandler,GPIO_ODD_IRQn,GPIO_ODD_IRQHandler,          4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     34, TIMER1_IRQHandler,TIMER1_IRQn,TIMER1_IRQHandler,            4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     35, USART1_RX_IRQHandler,USART1_RX_IRQn,USART1_RX_IRQHandler,         4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     36, USART1_TX_IRQHandler,USART1_TX_IRQn,USART1_TX_IRQHandler,         4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     37, LEUART0_IRQHandler,LEUART0_IRQn,LEUART0_IRQHandler,           4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     38, PCNT0_IRQHandler,PCNT0_IRQn,PCNT0_IRQHandler,             4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     39, CMU_IRQHandler,CMU_IRQn,CMU_IRQHandler,               4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     40, MSC_IRQHandler,MSC_IRQn,MSC_IRQHandler,               4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     41, CRYPTO_IRQHandler,CRYPTO_IRQn,CRYPTO_IRQHandler,            4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     42, LETIMER0_IRQHandler,LETIMER0_IRQn,LETIMER0_IRQHandler,          4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     43, AGC_IRQHandler,AGC_IRQn,AGC_IRQHandler,               4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     44, PROTIMER_IRQHandler,PROTIMER_IRQn,PROTIMER_IRQHandler,          4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     45, RTCC_IRQHandler,RTCC_IRQn,RTCC_IRQHandler,              4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     46, SYNTH_IRQHandler,SYNTH_IRQn,SYNTH_IRQHandler,             4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     47, CRYOTIMER_IRQHandler,CRYOTIMER_IRQn,CRYOTIMER_IRQHandler,         4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     48, RFSENSE_IRQHandler,RFSENSE_IRQn,RFSENSE_IRQHandler,           4,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     49, FPUEH_IRQHandler,FPUEH_IRQn,FPUEH_IRQHandler,             1,         0)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     50, halReserved50Isr,(IRQn_Type)(50-16),halReserved50Isr,     NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     51, halReserved51Isr,(IRQn_Type)(51-16),halReserved51Isr,     NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     52, halReserved52Isr,(IRQn_Type)(52-16),halReserved52Isr,     NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     53, halReserved53Isr,(IRQn_Type)(53-16),halReserved53Isr,     NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     54, halReserved54Isr,(IRQn_Type)(54-16),halReserved54Isr,     NVIC_NONE, NVIC_NONE)

    SEGMENT()
    SEGMENT2()
    EXCEPTION(     55, halReserved55Isr,(IRQn_Type)(55-16),halReserved55Isr,     NVIC_NONE, NVIC_NONE)
/* *INDENT-ON**/

#undef SEGMENT
#undef SEGMENT2
#undef PERM_EXCEPTION

#endif //DOXYGEN_SHOULD_SKIP_THIS
