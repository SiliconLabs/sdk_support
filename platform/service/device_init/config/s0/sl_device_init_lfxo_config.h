#ifndef SL_DEVICE_INIT_LFXO_CONFIG_H
#define SL_DEVICE_INIT_LFXO_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_DEVICE_INIT_LFXO_MODE> Mode
// <i>
// <cmuOscMode_Crystal=> Crystal oscillator
// <cmuOscMode_AcCoupled=> AC-coupled buffer
// <cmuOscMode_External=> External digital clock
// <i> Default: cmuOscMode_Crystal
#define SL_DEVICE_INIT_LFXO_MODE           cmuOscMode_Crystal

// <o SL_DEVICE_INIT_LFXO_BOOST> Boost
// <i>
// <cmuLfxoBoost70=> 70% boost
// <cmuLfxoBoost100=> 100% boost
// <i> Default: cmuLfxoBoost70
#define SL_DEVICE_INIT_LFXO_BOOST          cmuLfxoBoost70

// <o SL_DEVICE_INIT_LFXO_PRECISION> LFXO precision in PPM <0-65535>
// <i> Default: 500
#define SL_DEVICE_INIT_LFXO_PRECISION      500

// <<< end of configuration section >>>

#endif // SL_DEVICE_INIT_LFXO_CONFIG_H
