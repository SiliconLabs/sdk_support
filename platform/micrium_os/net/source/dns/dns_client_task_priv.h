/***************************************************************************//**
 * @file
 * @brief Network - DNS Client Task Module
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.
 * The software is governed by the sections of the MSLA applicable to Micrium
 * Software.
 *
 ******************************************************************************/

/********************************************************************************************************
 ********************************************************************************************************
 *                                               MODULE
 ********************************************************************************************************
 *******************************************************************************************************/

#ifndef  _DNS_CLIENT_TASK_PRIV_H_
#define  _DNS_CLIENT_TASK_PRIV_H_

/********************************************************************************************************
 ********************************************************************************************************
 *                                            INCLUDE FILES
 ********************************************************************************************************
 *******************************************************************************************************/

#include  "dns_client_priv.h"

#include  "../../include/dns_client.h"

/********************************************************************************************************
 ********************************************************************************************************
 *                                         FUNCTION PROTOTYPES
 ********************************************************************************************************
 *******************************************************************************************************/

#if 0
void DNScTask_Init(DNSc_DATA    *p_data,
                   CPU_INT32U   task_prio,
                   CPU_STK_SIZE stk_size_elements,
                   void         *p_stk,
                   RTOS_ERR     *p_err);
#endif

DNSc_STATUS DNScTask_HostResolve(DNSc_HOST_OBJ *p_host,
                                 DNSc_FLAGS    flags,
                                 DNSc_REQ_CFG  *p_cfg,
                                 RTOS_ERR      *p_err);

/********************************************************************************************************
 ********************************************************************************************************
 *                                             MODULE END
 ********************************************************************************************************
 *******************************************************************************************************/

#endif // _DNS_CLIENT_TASK_PRIV_H_
