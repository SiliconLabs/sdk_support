#ifndef _SL_WFX_BOARD_H_
#define _SL_WFX_BOARD_H_
/*
 * Pull in the right board PINS
 */
#if defined(EFR32MG21_BRD4180A) || defined(BRD4180A)
#include "brd4180a.h"
#elif defined(EFR32MG12_BRD4161A) || defined(BRD4161A) || defined(EFR32MG12_BRD4163A) || defined(BRD4163A) \
  || defined(EFR32MG12_BRD4164A) || defined(BRD4164A)
#include "brd4161a.h"
#elif defined(EFR32MG24_BRD4187C) || defined(BRD4187C)
#include "brd4187c.h"
#elif defined(EFR32MG24_BRD4186C) || defined(BRD4186C)
#include "brd4186c.h"
#else
#error "Need SPI Pins"
#endif /* EFR32MG21_BRD4180A */
#endif /* _SL_WFX_BOARD_H_ */
