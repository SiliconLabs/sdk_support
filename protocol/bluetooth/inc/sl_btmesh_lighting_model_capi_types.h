/******************************************************************************/
/**
 * @file   sl_btmesh_lighting_model_capi_types.h
 * @brief  Silicon Labs Bluetooth Mesh Lighting Model API
 *
 * Please see the @ref mesh_generic "generic model API"
 *
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

/*
 * C API for lighting models
 */

#ifndef SL_BTMESH_LIGHTING_MODEL_CAPI_TYPES_H
#define SL_BTMESH_LIGHTING_MODEL_CAPI_TYPES_H

/*
 * Lighting model IDs
 */
/** Light lightness server */
#define MESH_LIGHTING_LIGHTNESS_SERVER_MODEL_ID 0x1300
/** Light lightness setup server */
#define MESH_LIGHTING_LIGHTNESS_SETUP_SERVER_MODEL_ID 0x1301
/** Light lightness client */
#define MESH_LIGHTING_LIGHTNESS_CLIENT_MODEL_ID 0x1302

/** Light CTL server */
#define MESH_LIGHTING_CTL_SERVER_MODEL_ID 0x1303
/** Light CTL setup server */
#define MESH_LIGHTING_CTL_SETUP_SERVER_MODEL_ID 0x1304
/** Light CTL client */
#define MESH_LIGHTING_CTL_CLIENT_MODEL_ID 0x1305
/** Light CTL temperature server */
#define MESH_LIGHTING_CTL_TEMPERATURE_SERVER_MODEL_ID 0x1306

/** Light CTL Temperature Minimum */
#define MESH_LIGHTING_CTL_TEMPERATURE_MIN 0x0320

/** Light CTL Temperature Maximum */
#define MESH_LIGHTING_CTL_TEMPERATURE_MAX 0x4e20

/** Light HSL server */
#define MESH_LIGHTING_HSL_SERVER_MODEL_ID 0x1307
/** Light HSL setup server */
#define MESH_LIGHTING_HSL_SETUP_SERVER_MODEL_ID 0x1308
/** Light HSL client */
#define MESH_LIGHTING_HSL_CLIENT_MODEL_ID 0x1309
/** Light HSL hue server */
#define MESH_LIGHTING_HSL_HUE_SERVER_MODEL_ID 0x130a
/** Light HSL saturation server */
#define MESH_LIGHTING_HSL_SATURATION_SERVER_MODEL_ID 0x130b

/** Light xyl server */
#define MESH_LIGHTING_XYL_SERVER_MODEL_ID 0x130c
/** Light xyl setup server */
#define MESH_LIGHTING_XYL_SETUP_SERVER_MODEL_ID 0x130d
/** Light xyl client */
#define MESH_LIGHTING_XYL_CLIENT_MODEL_ID 0x130e

/**
 * API for handling state binding between LC and Light Lightness model
 */
typedef void (*mesh_lc_light_lightness_linear_binding_fn) (mesh_model_t model);

#endif /* SL_BTMESH_LIGHTING_MODEL_CAPI_TYPES_H */
