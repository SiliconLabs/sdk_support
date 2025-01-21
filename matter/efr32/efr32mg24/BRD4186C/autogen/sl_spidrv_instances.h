#ifndef SL_SPIDRV_INSTANCES_H
#define SL_SPIDRV_INSTANCES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spidrv.h"

#ifdef RS911X_WIFI
#if !(defined(EXP_BOARD) && EXP_BOARD)
extern SPIDRV_Handle_t sl_spidrv_eusart_exp_handle;
#endif
#endif

#if (WF200_WIFI | EXP_BOARD)
extern SPIDRV_Handle_t sl_spidrv_exp_handle;
#endif

void sl_spidrv_init_instances(void);

#ifdef __cplusplus
}
#endif

#endif // SL_SPIDRV_INSTANCES_H
