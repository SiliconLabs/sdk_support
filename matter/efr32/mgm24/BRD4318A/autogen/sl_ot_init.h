/***************************************************************************/
/**
 * @file
 * @brief This generated header includes declaration of all functions required
 * during initialization that must be defined by the OpenThread application.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 *
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 *
 * This software is distributed to you in Source Code format and is governed by
 * the sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_OT_INIT_H
#define SL_OT_INIT_H

void sl_ot_init(void);
extern void sl_ot_create_instance(void); 
extern void sl_ot_sleep_init(void); 
extern void sl_ot_cli_init(void); 
extern void sl_ot_custom_cli_init(void); 

#endif // SL_OT_INIT_H