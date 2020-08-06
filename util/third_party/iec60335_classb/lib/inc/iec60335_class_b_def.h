/***************************************************************************//**
 * @brief Defines used in the IEC60335 test assembly files
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
 
#ifndef __IEC60335_CLASS_B_DEF_H__
#define __IEC60335_CLASS_B_DEF_H__

/*! @addtogroup IEC60335_CONFIG
 * @{
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* define compiler specific symbols */
#if defined (__CC_ARM)      /*--RealView Compiler --*/
/*! @cond RealView */
    #ifndef __ASM
    #define __ASM             __asm                               /*!< asm keyword for ARM Compiler */
    #endif
    #ifndef __INLINE
    #define __INLINE          __inline                            /*!< inline keyword for ARM Compiler */
    #endif
    #define FLASH_CRC_ADDR    0x000000E0                          /*!< start address of Flash information */
    #define __STEXT           FLASH_CRC_ADDR + sizeof(FlashCRC_t) /*!< start address of Flash code */
/*! @endcond */

#elif (defined (__ICCARM__))    /*-- ICC Compiler --*/
/*! @cond ICC */
    #ifndef __ASM
    #define __ASM             __asm                 /*!< asm keyword for IAR Compiler */
    #endif
    #ifndef __INLINE
    #define __INLINE          inline                /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
    #endif
    #define FLASH_CRC_ADDR    0x000010BA            /* LENGTH = 0x20 */
    #define __STEXT           0x100
/*! @endcond */

#elif (defined (__GNUC__))      /*-- GNU Compiler --*/
/*! @cond GCC */
    #ifndef __ASM
    #define __ASM             __asm                 /*!< asm keyword for GNU Compiler          */
    #endif
    #undef __INLINE
    #define __INLINE          __inline__            /*!< inline keyword for GNU Compiler       */
extern unsigned long _crc_location;                 /* linker reference : start CRC entry      */
    #define FLASH_CRC_ADDR    &_crc_location        /*!< CRC location in Flash                 */
extern unsigned long __text_start;                  /* linker reference : start text section   */
    #define __STEXT           &__text_start         /*!< start address of Flash code           */
/*! @endcond */

#elif defined   (__TASKING__)
/*! @cond TASKING */
    #error "not implemented yet !"                  /*!< TASKING Compiler is not implemented   */
/*! @endcond */

#else
    #error "iec60355_class_b_def.h: undefined compiler"
#endif

#ifdef TESSY
/*! @cond TESSY */
#define LoopForever()    return                     /*!< macro enables automated test */
/*! @endcond */
#else
#define LoopForever()    while (1)                  /*!< macro enables automated test */
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*!
 * @}
 */

#endif /* __IEC60335_CLASS_B_DEF_H__ */

/************************************** EOF *********************************/
