/***************************************************************************//**
 * @brief Mesh helper library
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

#include <stdint.h>
#include <stdlib.h>

#include "sl_btmesh_api.h"

#include "sl_btmesh_generic_model_capi_types.h"
#include "sl_btmesh_lib.h"
#include "sl_btmesh_serdeser.h"

/* Enough room for Property ID (2 bytes), access flags (1 byte), and
   longest currently defined property characteristic (36 bytes) */
#define LONGEST_STATE 39
#define LONGEST_REQUEST 39

uint32_t mesh_lib_transition_time_to_ms(uint8_t t)
{
  uint32_t res_ms[4] = { 100, 1000, 10000, 600000 };
  uint32_t unit = (t >> 6) & 0x03;
  uint32_t count = t & 0x3f;
  return res_ms[unit] * count;
}

struct reg {
  uint16_t model_id;
  uint16_t elem_index;
  union {
    struct {
      mesh_lib_generic_server_client_request_cb client_request_cb;
      mesh_lib_generic_server_change_cb state_changed_cb;
      mesh_lib_generic_server_recall_cb state_recall_cb;
    } server;
    struct {
      mesh_lib_generic_client_server_response_cb server_response_cb;
    } client;
  };
};

static struct reg *reg = NULL;
static size_t regs = 0;

static void *(*lib_malloc_fn)(size_t) = NULL;
static void (*lib_free_fn)(void *) = NULL;

static struct reg *find_reg(uint16_t model_id,
                            uint16_t elem_index)
{
  size_t r;
  for (r = 0; r < regs; r++) {
    if (reg[r].model_id == model_id && reg[r].elem_index == elem_index) {
      return &reg[r];
    }
  }
  return NULL;
}

static struct reg *find_free(void)
{
  size_t r;
  for (r = 0; r < regs; r++) {
    if (reg[r].model_id == 0x0000 && reg[r].elem_index == 0x0000) {
      return &reg[r];
    }
  }
  return NULL;
}

sl_status_t mesh_lib_init(void *(*malloc_fn)(size_t),
                          void (*free_fn)(void *),
                          size_t generic_models)
{
  lib_malloc_fn = malloc_fn;
  lib_free_fn = free_fn;

  if (generic_models) {
    reg = (lib_malloc_fn)(generic_models * sizeof(struct reg));
    if (!reg) {
      return SL_STATUS_NO_MORE_RESOURCE;
    }
    memset(reg, 0, generic_models * sizeof(struct reg));
    regs = generic_models;
  }

  return SL_STATUS_OK;
}

void mesh_lib_deinit(void)
{
  if (reg) {
    (lib_free_fn)(reg);
    reg = NULL;
    regs = 0;
  }
}

sl_status_t
mesh_lib_generic_server_register_handler(uint16_t model_id,
                                         uint16_t elem_index,
                                         mesh_lib_generic_server_client_request_cb cb,
                                         mesh_lib_generic_server_change_cb ch,
                                         mesh_lib_generic_server_recall_cb recall)
{
  struct reg *reg = NULL;

  reg = find_reg(model_id, elem_index);
  if (reg) {
    return SL_STATUS_INVALID_STATE; // already exists
  }

  reg = find_free();
  if (!reg) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  reg->model_id = model_id;
  reg->elem_index = elem_index;
  reg->server.client_request_cb = cb;
  reg->server.state_changed_cb = ch;
  reg->server.state_recall_cb = recall;
  return SL_STATUS_OK;
}

sl_status_t
mesh_lib_generic_client_register_handler(uint16_t model_id,
                                         uint16_t elem_index,
                                         mesh_lib_generic_client_server_response_cb cb)
{
  struct reg *reg = NULL;

  reg = find_reg(model_id, elem_index);
  if (reg) {
    return SL_STATUS_INVALID_STATE; // already exists
  }

  reg = find_free();
  if (!reg) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  reg->model_id = model_id;
  reg->elem_index = elem_index;
  reg->client.server_response_cb = cb;
  return SL_STATUS_OK;
}

void mesh_lib_generic_server_event_handler(sl_btmesh_msg_t *evt)
{
  sl_btmesh_evt_generic_server_client_request_t *req = NULL;
  sl_btmesh_evt_generic_server_state_changed_t *chg = NULL;
  sl_btmesh_evt_generic_server_state_recall_t *recall = NULL;
  struct mesh_generic_request request;
  struct mesh_generic_state current;
  struct mesh_generic_state target;
  int has_target;
  struct reg *reg;

  if (!evt) {
    return;
  }

  switch (SL_BGAPI_MSG_ID(evt->header)) {
    case sl_btmesh_evt_generic_server_client_request_id:
      req = &(evt->data.evt_generic_server_client_request);
      reg = find_reg(req->model_id, req->elem_index);
      if (reg) {
        if (mesh_lib_deserialize_request(&request,
                                         (mesh_generic_request_t)req->type,
                                         req->parameters.data,
                                         req->parameters.len) == 0) {
          (reg->server.client_request_cb)(req->model_id,
                                          req->elem_index,
                                          req->client_address,
                                          req->server_address,
                                          req->appkey_index,
                                          &request,
                                          req->transition_ms,
                                          req->delay_ms,
                                          req->flags);
        }
      }
      break;
    case sl_btmesh_evt_generic_server_state_changed_id:
      chg = &(evt->data.evt_generic_server_state_changed);
      reg = find_reg(chg->model_id, chg->elem_index);
      if (reg) {
        if (mesh_lib_deserialize_state(&current,
                                       &target,
                                       &has_target,
                                       (mesh_generic_state_t)chg->type,
                                       chg->parameters.data,
                                       chg->parameters.len) == 0) {
          (reg->server.state_changed_cb)(chg->model_id,
                                         chg->elem_index,
                                         &current,
                                         has_target ? &target : NULL,
                                         chg->remaining_ms);
        }
      }
      break;
    case sl_btmesh_evt_generic_server_state_recall_id:
      recall = &(evt->data.evt_generic_server_state_recall);
      reg = find_reg(recall->model_id, recall->elem_index);
      if (reg) {
        if (mesh_lib_deserialize_state(&current,
                                       &target,
                                       &has_target,
                                       (mesh_generic_state_t)recall->type,
                                       recall->parameters.data,
                                       recall->parameters.len) == 0) {
          (reg->server.state_recall_cb)(recall->model_id,
                                        recall->elem_index,
                                        &current,
                                        has_target ? &target : NULL,
                                        recall->transition_time_ms);
        }
      }
      break;
  }
}

void mesh_lib_generic_client_event_handler(sl_btmesh_msg_t *evt)
{
  sl_btmesh_evt_generic_client_server_status_t *res = NULL;
  struct mesh_generic_state current;
  struct mesh_generic_state target;
  int has_target;
  struct reg *reg;

  if (!evt) {
    return;
  }

  switch (SL_BGAPI_MSG_ID(evt->header)) {
    case sl_btmesh_evt_generic_client_server_status_id:
      res = &(evt->data.evt_generic_client_server_status);
      reg = find_reg(res->model_id, res->elem_index);
      if (reg) {
        if (mesh_lib_deserialize_state(&current,
                                       &target,
                                       &has_target,
                                       (mesh_generic_state_t)res->type,
                                       res->parameters.data,
                                       res->parameters.len) == 0) {
          (reg->client.server_response_cb)(res->model_id,
                                           res->elem_index,
                                           res->client_address,
                                           res->server_address,
                                           &current,
                                           has_target ? &target : NULL,
                                           res->remaining_ms,
                                           res->flags);
        }
      }
      break;
  }
}

sl_status_t
mesh_lib_generic_server_respond(uint16_t model_id,
                                uint16_t element_index,
                                uint16_t client_addr,
                                uint16_t appkey_index,
                                const struct mesh_generic_state *current,
                                const struct mesh_generic_state *target,
                                uint32_t remaining_ms,
                                uint8_t response_flags)
{
  uint8_t buf[LONGEST_STATE];
  size_t len;

  if (mesh_lib_serialize_state(current, target, buf, sizeof(buf), &len) != 0) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  return sl_btmesh_generic_server_respond(client_addr,
                                          element_index,
                                          model_id,
                                          appkey_index,
                                          remaining_ms,
                                          response_flags,
                                          current->kind,
                                          len,
                                          buf);
}

sl_status_t
mesh_lib_generic_server_update(uint16_t model_id,
                               uint16_t element_index,
                               const struct mesh_generic_state *current,
                               const struct mesh_generic_state *target,
                               uint32_t remaining_ms)
{
  uint8_t buf[LONGEST_STATE];
  size_t len;

  if (mesh_lib_serialize_state(current, target, buf, sizeof(buf), &len) != 0) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  return sl_btmesh_generic_server_update(element_index,
                                         model_id,
                                         remaining_ms,
                                         current->kind,
                                         len,
                                         buf);
}

sl_status_t
mesh_lib_generic_server_publish(uint16_t model_id,
                                uint16_t element_index,
                                mesh_generic_state_t kind)
{
  return sl_btmesh_generic_server_publish(element_index,
                                          model_id,
                                          kind);
}

sl_status_t mesh_lib_generic_client_get(uint16_t model_id,
                                        uint16_t element_index,
                                        uint16_t server_addr,
                                        uint16_t appkey_index,
                                        mesh_generic_state_t kind)
{
  return sl_btmesh_generic_client_get(server_addr,
                                      element_index,
                                      model_id,
                                      appkey_index,
                                      kind);
}

sl_status_t mesh_lib_generic_client_set(uint16_t model_id,
                                        uint16_t element_index,
                                        uint16_t server_addr,
                                        uint16_t appkey_index,
                                        uint8_t transaction_id,
                                        const struct mesh_generic_request *request,
                                        uint32_t transition_ms,
                                        uint16_t delay_ms,
                                        uint8_t flags)
{
  uint8_t buf[LONGEST_REQUEST];
  size_t len;

  if (mesh_lib_serialize_request(request, buf, sizeof(buf), &len) != 0) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  return sl_btmesh_generic_client_set(server_addr,
                                      element_index,
                                      model_id,
                                      appkey_index,
                                      transaction_id,
                                      transition_ms,
                                      delay_ms,
                                      flags,
                                      request->kind,
                                      len,
                                      buf);
}

sl_status_t
mesh_lib_generic_client_publish(uint16_t model_id,
                                uint16_t element_index,
                                uint8_t transaction_id,
                                const struct mesh_generic_request *request,
                                uint32_t transition_ms,
                                uint16_t delay_ms,
                                uint8_t request_flags)
{
  uint8_t buf[LONGEST_REQUEST];
  size_t len;

  if (mesh_lib_serialize_request(request, buf, sizeof(buf), &len) != 0) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  return sl_btmesh_generic_client_publish(element_index,
                                          model_id,
                                          transaction_id,
                                          transition_ms,
                                          delay_ms,
                                          request_flags,
                                          request->kind,
                                          len,
                                          buf);
}
