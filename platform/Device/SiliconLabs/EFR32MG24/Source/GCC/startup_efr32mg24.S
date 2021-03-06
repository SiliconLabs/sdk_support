/**************************************************************************//**
 * @file
 * @brief CMSIS Compatible EFR32MG24 startup file for GCC.
 *        Should be used with GCC 'GNU Tools ARM Embedded'
 ******************************************************************************
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
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

    .syntax     unified
    .arch       armv8-m.main
    .section    .stack
    .align      3
#ifdef __STACK_SIZE
    .equ        Stack_Size, __STACK_SIZE
#else
    .equ        Stack_Size, 0x00000400
#endif
    .globl      __StackTop
    .globl      __StackLimit
__StackLimit:
    .space      Stack_Size
    .size       __StackLimit, . - __StackLimit
__StackTop:
    .size       __StackTop, . - __StackTop

    .section    .heap
    .align      3
#ifdef __HEAP_SIZE
    .equ        Heap_Size, __HEAP_SIZE
#else
    .equ        Heap_Size, 0x00000C00
#endif
    .globl      __HeapBase
    .globl      __HeapLimit
__HeapBase:
    .if Heap_Size
    .space      Heap_Size
    .endif
    .size       __HeapBase, . - __HeapBase
__HeapLimit:
    .size       __HeapLimit, . - __HeapLimit

    .section    .vectors
    .align      2
    .globl      __Vectors
__Vectors:
    .long       __StackTop            /* Top of Stack */
    .long       Reset_Handler         /* Reset Handler */
    .long       NMI_Handler           /* NMI Handler */
    .long       HardFault_Handler     /* Hard Fault Handler */
    .long       MemManage_Handler     /* MPU Fault Handler */
    .long       BusFault_Handler      /* Bus Fault Handler */
    .long       UsageFault_Handler    /* Usage Fault Handler */
    .long       Default_Handler       /* Reserved */
    .long       Default_Handler       /* Reserved */
    .long       Default_Handler       /* Reserved */
    .long       Default_Handler       /* Reserved */
    .long       SVC_Handler           /* SVCall Handler */
    .long       DebugMon_Handler      /* Debug Monitor Handler */
    .long       sl_app_properties     /* Application properties */
    .long       PendSV_Handler        /* PendSV Handler */
    .long       SysTick_Handler       /* SysTick Handler */

    /* External interrupts */
    .long       SMU_SECURE_IRQHandler   /* 0 - SMU_SECURE */
    .long       SMU_PRIVILEGED_IRQHandler /* 1 - SMU_PRIVILEGED */
    .long       SMU_NS_PRIVILEGED_IRQHandler /* 2 - SMU_NS_PRIVILEGED */
    .long       EMU_IRQHandler          /* 3 - EMU */
    .long       TIMER0_IRQHandler       /* 4 - TIMER0 */
    .long       TIMER1_IRQHandler       /* 5 - TIMER1 */
    .long       TIMER2_IRQHandler       /* 6 - TIMER2 */
    .long       TIMER3_IRQHandler       /* 7 - TIMER3 */
    .long       TIMER4_IRQHandler       /* 8 - TIMER4 */
    .long       USART0_RX_IRQHandler    /* 9 - USART0_RX */
    .long       USART0_TX_IRQHandler    /* 10 - USART0_TX */
    .long       EUSART0_RX_IRQHandler   /* 11 - EUSART0_RX */
    .long       EUSART0_TX_IRQHandler   /* 12 - EUSART0_TX */
    .long       EUSART1_RX_IRQHandler   /* 13 - EUSART1_RX */
    .long       EUSART1_TX_IRQHandler   /* 14 - EUSART1_TX */
    .long       MVP_IRQHandler          /* 15 - MVP */
    .long       ICACHE0_IRQHandler      /* 16 - ICACHE0 */
    .long       BURTC_IRQHandler        /* 17 - BURTC */
    .long       LETIMER0_IRQHandler     /* 18 - LETIMER0 */
    .long       SYSCFG_IRQHandler       /* 19 - SYSCFG */
    .long       MPAHBRAM_IRQHandler     /* 20 - MPAHBRAM */
    .long       LDMA_IRQHandler         /* 21 - LDMA */
    .long       LFXO_IRQHandler         /* 22 - LFXO */
    .long       LFRCO_IRQHandler        /* 23 - LFRCO */
    .long       ULFRCO_IRQHandler       /* 24 - ULFRCO */
    .long       GPIO_ODD_IRQHandler     /* 25 - GPIO_ODD */
    .long       GPIO_EVEN_IRQHandler    /* 26 - GPIO_EVEN */
    .long       I2C0_IRQHandler         /* 27 - I2C0 */
    .long       I2C1_IRQHandler         /* 28 - I2C1 */
    .long       EMUDG_IRQHandler        /* 29 - EMUDG */
    .long       AGC_IRQHandler          /* 30 - AGC */
    .long       BUFC_IRQHandler         /* 31 - BUFC */
    .long       FRC_PRI_IRQHandler      /* 32 - FRC_PRI */
    .long       FRC_IRQHandler          /* 33 - FRC */
    .long       MODEM_IRQHandler        /* 34 - MODEM */
    .long       PROTIMER_IRQHandler     /* 35 - PROTIMER */
    .long       RAC_RSM_IRQHandler      /* 36 - RAC_RSM */
    .long       RAC_SEQ_IRQHandler      /* 37 - RAC_SEQ */
    .long       HOSTMAILBOX_IRQHandler  /* 38 - HOSTMAILBOX */
    .long       SYNTH_IRQHandler        /* 39 - SYNTH */
    .long       ACMP0_IRQHandler        /* 40 - ACMP0 */
    .long       ACMP1_IRQHandler        /* 41 - ACMP1 */
    .long       WDOG0_IRQHandler        /* 42 - WDOG0 */
    .long       WDOG1_IRQHandler        /* 43 - WDOG1 */
    .long       HFXO0_IRQHandler        /* 44 - HFXO0 */
    .long       HFRCO0_IRQHandler       /* 45 - HFRCO0 */
    .long       HFRCOEM23_IRQHandler    /* 46 - HFRCOEM23 */
    .long       CMU_IRQHandler          /* 47 - CMU */
    .long       AES_IRQHandler          /* 48 - AES */
    .long       IADC_IRQHandler         /* 49 - IADC */
    .long       MSC_IRQHandler          /* 50 - MSC */
    .long       DPLL0_IRQHandler        /* 51 - DPLL0 */
    .long       EMUEFP_IRQHandler       /* 52 - EMUEFP */
    .long       DCDC_IRQHandler         /* 53 - DCDC */
    .long       PCNT0_IRQHandler        /* 54 - PCNT0 */
    .long       SW0_IRQHandler          /* 55 - SW0 */
    .long       SW1_IRQHandler          /* 56 - SW1 */
    .long       SW2_IRQHandler          /* 57 - SW2 */
    .long       SW3_IRQHandler          /* 58 - SW3 */
    .long       KERNEL0_IRQHandler      /* 59 - KERNEL0 */
    .long       KERNEL1_IRQHandler      /* 60 - KERNEL1 */
    .long       M33CTI0_IRQHandler      /* 61 - M33CTI0 */
    .long       M33CTI1_IRQHandler      /* 62 - M33CTI1 */
    .long       FPUEXH_IRQHandler       /* 63 - FPUEXH */
    .long       SETAMPERHOST_IRQHandler /* 64 - SETAMPERHOST */
    .long       SEMBRX_IRQHandler       /* 65 - SEMBRX */
    .long       SEMBTX_IRQHandler       /* 66 - SEMBTX */
    .long       SYSRTC_APP_IRQHandler   /* 67 - SYSRTC_APP */
    .long       SYSRTC_SEQ_IRQHandler   /* 68 - SYSRTC_SEQ */
    .long       KEYSCAN_IRQHandler      /* 69 - KEYSCAN */
    .long       RFECA0_IRQHandler       /* 70 - RFECA0 */
    .long       RFECA1_IRQHandler       /* 71 - RFECA1 */
    .long       VDAC0_IRQHandler        /* 72 - VDAC0 */
    .long       VDAC1_IRQHandler        /* 73 - VDAC1 */
    .long       AHB2AHB0_IRQHandler     /* 74 - AHB2AHB0 */
    .long       AHB2AHB1_IRQHandler     /* 75 - AHB2AHB1 */

    .size       __Vectors, . - __Vectors

    .text
    .thumb
    .thumb_func
    .align      2
    .globl      Reset_Handler
    .type       Reset_Handler, %function
Reset_Handler:

#ifndef __NO_SYSTEM_INIT
    ldr     r0, =SystemInit
    blx     r0
#endif

/*  Firstly it copies data from read only memory to RAM. There are two schemes
 *  to copy. One can copy more than one sections. Another can only copy
 *  one section.  The former scheme needs more instructions and read-only
 *  data to implement than the latter.
 *  Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.
 */

#ifdef __STARTUP_COPY_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of triplets, each of which specify:
 *    offset 0: LMA of start of a section to copy from
 *    offset 4: VMA of start of a section to copy to
 *    offset 8: size of the section to copy. Must be multiply of 4
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
    ldr     r4, =__copy_table_start__
    ldr     r5, =__copy_table_end__

.L_loop0:
    cmp     r4, r5
    bge     .L_loop0_done
    ldr     r1, [r4]
    ldr     r2, [r4, #4]
    ldr     r3, [r4, #8]

.L_loop0_0:
    subs    r3, #4
    ittt    ge
    ldrge   r0, [r1, r3]
    strge   r0, [r2, r3]
    bge     .L_loop0_0

    adds    r4, #12
    b       .L_loop0

.L_loop0_done:
#else
/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
    ldr     r1, =__etext
    ldr     r2, =__data_start__
    ldr     r3, =__data_end__
.L_loop1:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt     .L_loop1
#endif /* __STARTUP_COPY_MULTIPLE */

/*  This part of work usually is done in C library startup code. Otherwise,
 *  define this macro to enable it in this startup.
 *
 *  There are two schemes too. One can clear multiple BSS sections. Another
 *  can only clear one section. The former is more size expensive than the
 *  latter.
 *
 *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
 */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __zero_table_start__ and __zero_table_end__,
 *  there are array of tuples specifying:
 *    offset 0: Start of a BSS section
 *    offset 4: Size of this BSS section. Must be multiply of 4
 */
    ldr     r3, =__zero_table_start__
    ldr     r4, =__zero_table_end__

.L_loop2:
    cmp     r3, r4
    bge     .L_loop2_done
    ldr     r1, [r3]
    ldr     r2, [r3, #4]
    movs    r0, 0

.L_loop2_0:
    subs    r2, #4
    itt     ge
    strge   r0, [r1, r2]
    bge     .L_loop2_0
    adds    r3, #8
    b       .L_loop2
.L_loop2_done:
#elif defined (__STARTUP_CLEAR_BSS)
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
    ldr     r1, =__bss_start__
    ldr     r2, =__bss_end__

    movs    r0, 0
.L_loop3:
    cmp     r1, r2
    itt     lt
    strlt   r0, [r1], #4
    blt     .L_loop3
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

#ifndef __START
#define __START _start
#endif
    bl      __START

    .pool
    .size   Reset_Handler, . - Reset_Handler

    .align  1
    .thumb_func
    .weak   Default_Handler
    .type   Default_Handler, %function
    .weak   sl_app_properties
    .type   sl_app_properties, %common
Default_Handler:
sl_app_properties: /* Provide a dummy value for the sl_app_properties symbol. */
    b       .
    .size   Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers.
 */
    .macro  def_irq_handler	handler_name
    .weak   \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler     NMI_Handler
    def_irq_handler     HardFault_Handler
    def_irq_handler     MemManage_Handler
    def_irq_handler     BusFault_Handler
    def_irq_handler     UsageFault_Handler
    def_irq_handler     SVC_Handler
    def_irq_handler     DebugMon_Handler
    def_irq_handler     PendSV_Handler
    def_irq_handler     SysTick_Handler
    def_irq_handler     SMU_SECURE_IRQHandler
    def_irq_handler     SMU_PRIVILEGED_IRQHandler
    def_irq_handler     SMU_NS_PRIVILEGED_IRQHandler
    def_irq_handler     EMU_IRQHandler
    def_irq_handler     TIMER0_IRQHandler
    def_irq_handler     TIMER1_IRQHandler
    def_irq_handler     TIMER2_IRQHandler
    def_irq_handler     TIMER3_IRQHandler
    def_irq_handler     TIMER4_IRQHandler
    def_irq_handler     USART0_RX_IRQHandler
    def_irq_handler     USART0_TX_IRQHandler
    def_irq_handler     EUSART0_RX_IRQHandler
    def_irq_handler     EUSART0_TX_IRQHandler
    def_irq_handler     EUSART1_RX_IRQHandler
    def_irq_handler     EUSART1_TX_IRQHandler
    def_irq_handler     MVP_IRQHandler
    def_irq_handler     ICACHE0_IRQHandler
    def_irq_handler     BURTC_IRQHandler
    def_irq_handler     LETIMER0_IRQHandler
    def_irq_handler     SYSCFG_IRQHandler
    def_irq_handler     MPAHBRAM_IRQHandler
    def_irq_handler     LDMA_IRQHandler
    def_irq_handler     LFXO_IRQHandler
    def_irq_handler     LFRCO_IRQHandler
    def_irq_handler     ULFRCO_IRQHandler
    def_irq_handler     GPIO_ODD_IRQHandler
    def_irq_handler     GPIO_EVEN_IRQHandler
    def_irq_handler     I2C0_IRQHandler
    def_irq_handler     I2C1_IRQHandler
    def_irq_handler     EMUDG_IRQHandler
    def_irq_handler     AGC_IRQHandler
    def_irq_handler     BUFC_IRQHandler
    def_irq_handler     FRC_PRI_IRQHandler
    def_irq_handler     FRC_IRQHandler
    def_irq_handler     MODEM_IRQHandler
    def_irq_handler     PROTIMER_IRQHandler
    def_irq_handler     RAC_RSM_IRQHandler
    def_irq_handler     RAC_SEQ_IRQHandler
    def_irq_handler     HOSTMAILBOX_IRQHandler
    def_irq_handler     SYNTH_IRQHandler
    def_irq_handler     ACMP0_IRQHandler
    def_irq_handler     ACMP1_IRQHandler
    def_irq_handler     WDOG0_IRQHandler
    def_irq_handler     WDOG1_IRQHandler
    def_irq_handler     HFXO0_IRQHandler
    def_irq_handler     HFRCO0_IRQHandler
    def_irq_handler     HFRCOEM23_IRQHandler
    def_irq_handler     CMU_IRQHandler
    def_irq_handler     AES_IRQHandler
    def_irq_handler     IADC_IRQHandler
    def_irq_handler     MSC_IRQHandler
    def_irq_handler     DPLL0_IRQHandler
    def_irq_handler     EMUEFP_IRQHandler
    def_irq_handler     DCDC_IRQHandler
    def_irq_handler     PCNT0_IRQHandler
    def_irq_handler     SW0_IRQHandler
    def_irq_handler     SW1_IRQHandler
    def_irq_handler     SW2_IRQHandler
    def_irq_handler     SW3_IRQHandler
    def_irq_handler     KERNEL0_IRQHandler
    def_irq_handler     KERNEL1_IRQHandler
    def_irq_handler     M33CTI0_IRQHandler
    def_irq_handler     M33CTI1_IRQHandler
    def_irq_handler     FPUEXH_IRQHandler
    def_irq_handler     SETAMPERHOST_IRQHandler
    def_irq_handler     SEMBRX_IRQHandler
    def_irq_handler     SEMBTX_IRQHandler
    def_irq_handler     SYSRTC_APP_IRQHandler
    def_irq_handler     SYSRTC_SEQ_IRQHandler
    def_irq_handler     KEYSCAN_IRQHandler
    def_irq_handler     RFECA0_IRQHandler
    def_irq_handler     RFECA1_IRQHandler
    def_irq_handler     VDAC0_IRQHandler
    def_irq_handler     VDAC1_IRQHandler
    def_irq_handler     AHB2AHB0_IRQHandler
    def_irq_handler     AHB2AHB1_IRQHandler

    .end