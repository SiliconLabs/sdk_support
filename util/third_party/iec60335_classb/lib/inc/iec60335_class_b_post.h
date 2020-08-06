/***************************************************************************//**
 * @brief header file for POST test
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
 #ifndef __IEC60335_CLASS_B_POST_H__
#define __IEC60335_CLASS_B_POST_H__

/*! @addtogroup IEC60335_POST
 * @{
 * @image html POST.jpg
 */

#include "iec60335_class_b_typedef.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*!
 * @brief   This function runs a colletion of POST tests
 *          and will suck in error condition
 *
 * @attention  This function must be called once befor memeory initialization.
 */
void IEC60335_ClassB_POST(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*!
 * @}
 */

#endif  /* __IEC60335_CLASS_B_POST_H__ */

/************************************** EOF *********************************/
