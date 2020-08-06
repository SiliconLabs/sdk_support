/**
 * @file hal/micro/cortexm3/emf32/long-token.h
 * @brief Functions to set and retreive data in the new Long Token Section of memory
 *
 * Copyright 2018 by Silicon Labs. All rights reserved.
 */

#ifndef __LONG_TOKEN_H__
#define __LONG_TOKEN_H__

/**
 * @description Copies the token value from the flash section storage into a RAM
 * location.
 *
 * @note Only the public function should be called since the public
 * function provides the correct parameters.
 *
 * @param data: A pointer to where the data being read should be placed.
 *
 * @param address: The address to access in flash.
 *
 * @param len: The length of the data being worked on.
 */
EmberStatus halCommonGetLongTokenData(void *data, uint8_t *address, uint32_t length);

/**
 * @description Sets the value of a token in non-volatile storage.  This is
 * the internal function that the exposed API (halCommonSetMfgToken)
 * expands out to.  The API simplifies the access into this function
 * by hiding the size parameter.
 *
 * @param data: A pointer to the data being written.
 *
 * @param address: The address of the data in RAM
 *
 * @param len: The length of the data being worked on.
 */
EmberStatus halCommonSetLongTokenData(void *data, uint8_t *address, uint32_t len);

#endif // __LONG_TOKEN_H__
