/***************************************************************************//**
 * @file
 * @brief Definition and prototypes related to the Cortex MPU.
 *
 * In EM3xx applications (but not bootloaders), the addresses protested are
 * determined by the mpu-config.h configuration header for the part under
 * compilation. In particular, no execution from RAM is allowed while the MPU is
 * active. BYPASS_MPU can be used to temporarily disable MPU protection, but
 * care should be taken to turn it off only for the minimum time necessary.
 *
 * In EFR32 applications, the Simple MPU driver is leveraged to disallow running
 * from all RAM except the area specifically set aside for RAM functions.
 * Due to a known incompatibility, the Simple MPU component is not used to
 * initialize the MPU when running DMP or other Micrium-based applications.
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
#ifndef __MPU_H__
#define __MPU_H__

// A region is defined by a struct with two parts, base address and attributes,
// that are loaded into the MPU_BASE and MPU_ATTR registers, respectively.
typedef struct mpu {
  uint32_t base;
  uint32_t attr;
} mpu_t;

// Define a macro to assemble data for the MPU_ATTR register from the various
// bit fields. Each argument is a bit field except for mem_type that
// combines the tex, s, c and b fields, shifted into their proper positions.
#define MATTR(xn, ap, mem_type, srd, size, enable) \
  (                                                \
    ((xn)     << MPU_RASR_XN_Pos)                  \
    | ((ap)     << MPU_RASR_AP_Pos)                \
    | (mem_type)                                   \
    | ((srd)    << MPU_RASR_SRD_Pos)               \
    | ((size)   << MPU_RASR_SIZE_Pos)              \
    | ((enable) << MPU_RASR_ENABLE_Pos)            \
  )

// Define a macro to allow the concise definition of a memory type.
#define MEM_TYPE(tex, sMpu, cMpu, bMpu) \
  (                                     \
    ((tex)    << MPU_RASR_TEX_Pos)      \
    | ((sMpu)      << MPU_RASR_S_Pos)   \
    | ((cMpu)      << MPU_RASR_C_Pos)   \
    | ((bMpu)      << MPU_RASR_B_Pos)   \
  )

// Number of MPU regions on the Cortex M3
#define NUM_MPU_REGIONS 8

// Region size (SIZE) field values
// Size must be a power of two, from 32 bytes to 4 gigabytes.
// Regions less than 256 bytes cannot be divided into 8 sub regions
#define SIZE_32B    0x04
#define SIZE_64B    0x05
#define SIZE_128B   0x06
#define SIZE_256B   0x07
#define SIZE_512B   0x08
#define SIZE_1K     0x09
#define SIZE_2K     0x0A
#define SIZE_4K     0x0B
#define SIZE_8K     0x0C
#define SIZE_16K    0x0D
#define SIZE_32K    0x0E
#define SIZE_64K    0x0F
#define SIZE_128K   0x10
#define SIZE_256K   0x11
#define SIZE_512K   0x12
#define SIZE_1M     0x13
#define SIZE_2M     0x14
#define SIZE_4M     0x15
#define SIZE_8M     0x16
#define SIZE_16M    0x17
#define SIZE_32M    0x18
#define SIZE_54M    0x19
#define SIZE_128M   0x1A
#define SIZE_256M   0x1B
#define SIZE_512M   0x1C
#define SIZE_1G     0x1D
#define SIZE_2G     0x1E
#define SIZE_4G     0x1F

// Data access permission (AP) field values
// Access permissions       Privileged  User
#define PNA_UNA     0   //  no access   no access
#define PRW_UNA     1   //  read/write  no access
#define PRW_URO     2   //  read/write  read-only
#define PRW_URW     3   //  read/write  read/write
#define PRO_UNA     5   //  read-only   no accesss
#define PRO_URO     6   //  read-only   read-only

// Define memory types through four MPU_ATTR fields:
// type extension (TEX), sharable (S), cacheable (C) and bufferable (B).
//
// ARM documentation regarding the precise effects of these fields on
// Cortex M3 is not very clear. It seems that most of the functions
// controlled by these fields are only relevant to a multi-processor
// architecture with cache and bus-snooping hardware.
//
// The types defined here have the following characteristics:
// MEM_NORMAL:
//            Outer and inner cache write-back. Write and read allocate.
//            Normal memory type.
//            Shareability controlled by the S bit.
// MEM_DEVICE:
//            Nonshared device.
//            Device memory type.
//            Not shareable.
//
// Memory types             tex s  c  b
#define MEM_NORMAL  MEM_TYPE(1, 0, 1, 1)
#define MEM_DEVICE  MEM_TYPE(2, 0, 0, 0)

#include "hal/micro/cortexm3/mpu-config.h"

//A simple utility macro for temporarily turning off the MPU.  Turning off
//the MPU is dangerous and should only be done in critical situations, such
//as executing from RAM and writing Flash.
#if defined(_HAL_MPU_UNUSED_) || defined(CORTEXM3_EFM32_MICRO)
//Ember bootloaders and EFR apps don't use the MPU in the same way EM35x apps
// do, so no there's no need to bypass it.
  #define BYPASS_MPU(blah) blah
#else
  #define BYPASS_MPU(blah)               \
  {                                      \
    uint32_t MPU_CTRL_SAVED = MPU->CTRL; \
    MPU->CTRL &= ~MPU_CTRL_ENABLE_Msk;   \
    _executeBarrierInstructions();       \
    { blah }                             \
    MPU->CTRL = MPU_CTRL_SAVED;          \
    _executeBarrierInstructions();       \
  }
#endif

void halInternalLoadMPU(mpu_t *mp);
void halInternalEnableMPU(void);
void halInternalDisableMPU(void);
void halInternalSetMPUGuardRegionStart(uint32_t baseAddress);






#endif//__MPU_H__
