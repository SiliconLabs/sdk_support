####################################################################
# Automatically-generated file. Do not edit!                       #
# Makefile Version 15                                              #
####################################################################

BASE_SDK_PATH = /Users/lobelive/Documents/workspace/simplicity_sdk
UNAME:=$(shell $(POSIX_TOOL_PATH)uname -s | $(POSIX_TOOL_PATH)sed -e 's/^\(CYGWIN\).*/\1/' | $(POSIX_TOOL_PATH)sed -e 's/^\(MINGW\).*/\1/')
ifeq ($(UNAME),MINGW)
# Translate "C:/super" into "/C/super" for MinGW make.
SDK_PATH := /$(shell $(POSIX_TOOL_PATH)echo $(BASE_SDK_PATH) | sed s/://)
endif
SDK_PATH ?= $(BASE_SDK_PATH)
COPIED_SDK_PATH ?= simplicity_sdk_2024.6.0

# This uses the explicit build rules below
PROJECT_SOURCE_FILES =

C_SOURCE_FILES   += $(filter %.c, $(PROJECT_SOURCE_FILES))
CXX_SOURCE_FILES += $(filter %.cpp, $(PROJECT_SOURCE_FILES))
CXX_SOURCE_FILES += $(filter %.cc, $(PROJECT_SOURCE_FILES))
ASM_SOURCE_FILES += $(filter %.s, $(PROJECT_SOURCE_FILES))
ASM_SOURCE_FILES += $(filter %.S, $(PROJECT_SOURCE_FILES))
LIB_FILES        += $(filter %.a, $(PROJECT_SOURCE_FILES))

C_DEFS += \
 '-DMGM240L022RNF=1' \
 '-DSL_BOARD_NAME="BRD4319A"' \
 '-DSL_BOARD_REV="A01"' \
 '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' \
 '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' \
 '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' \
 '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' \
 '-DSL_COMPONENT_CATALOG_PRESENT=1' \
 '-DSL_CODE_COMPONENT_PERIPHERAL_SYSRTC=hal_sysrtc' \
 '-DCMSIS_NVIC_VIRTUAL=1' \
 '-DCMSIS_NVIC_VIRTUAL_HEADER_FILE="cmsis_nvic_virtual.h"' \
 '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' \
 '-DSL_MEMORY_POOL_LIGHT=1' \
 '-DOPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS=0' \
 '-DINCLUDE_xTimerPendFunctionCall=1' \
 '-DRADIO_CONFIG_DMP_SUPPORT=1' \
 '-DOPENTHREAD_CORE_CONFIG_PLATFORM_CHECK_FILE="openthread-core-efr32-config-check.h"' \
 '-DOPENTHREAD_PROJECT_CORE_CONFIG_FILE="openthread-core-efr32-config.h"' \
 '-DSL_CODE_COMPONENT_OT_PLATFORM_ABSTRACTION=ot_platform_abstraction' \
 '-DOPENTHREAD_CONFIG_FILE="sl_openthread_generic_config.h"' \
 '-DOPENTHREAD_FTD=1' \
 '-DSL_OPENTHREAD_STACK_FEATURES_CONFIG_FILE="sl_openthread_features_config.h"' \
 '-DSL_CODE_COMPONENT_POWER_MANAGER=power_manager' \
 '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' \
 '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=1' \
 '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' \
 '-DRTT_USE_ASM=0' \
 '-DSEGGER_RTT_SECTION="SEGGER_RTT"' \
 '-DCIRCULAR_QUEUE_USE_LOCAL_CONFIG_HEADER=1' \
 '-DBUFFER_POOL_ALLOCATOR_USE_LOCAL_CONFIG_HEADER=1' \
 '-DSL_CODE_COMPONENT_CORE=core' \
 '-DSL_OPENTHREAD_CUSTOM_CLI_ENABLE=1' \
 '-DSL_CODE_COMPONENT_SLEEPTIMER=sleeptimer' \
 '-DSLI_RADIOAES_REQUIRES_MASKING=1'

ASM_DEFS += \
 '-DMGM240L022RNF=1' \
 '-DSL_BOARD_NAME="BRD4319A"' \
 '-DSL_BOARD_REV="A01"' \
 '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' \
 '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' \
 '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' \
 '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' \
 '-DSL_COMPONENT_CATALOG_PRESENT=1' \
 '-DSL_CODE_COMPONENT_PERIPHERAL_SYSRTC=hal_sysrtc' \
 '-DCMSIS_NVIC_VIRTUAL=1' \
 '-DCMSIS_NVIC_VIRTUAL_HEADER_FILE="cmsis_nvic_virtual.h"' \
 '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' \
 '-DSL_MEMORY_POOL_LIGHT=1' \
 '-DOPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS=0' \
 '-DINCLUDE_xTimerPendFunctionCall=1' \
 '-DRADIO_CONFIG_DMP_SUPPORT=1' \
 '-DOPENTHREAD_CORE_CONFIG_PLATFORM_CHECK_FILE="openthread-core-efr32-config-check.h"' \
 '-DOPENTHREAD_PROJECT_CORE_CONFIG_FILE="openthread-core-efr32-config.h"' \
 '-DSL_CODE_COMPONENT_OT_PLATFORM_ABSTRACTION=ot_platform_abstraction' \
 '-DOPENTHREAD_CONFIG_FILE="sl_openthread_generic_config.h"' \
 '-DOPENTHREAD_FTD=1' \
 '-DSL_OPENTHREAD_STACK_FEATURES_CONFIG_FILE="sl_openthread_features_config.h"' \
 '-DSL_CODE_COMPONENT_POWER_MANAGER=power_manager' \
 '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' \
 '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=1' \
 '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' \
 '-DRTT_USE_ASM=0' \
 '-DSEGGER_RTT_SECTION="SEGGER_RTT"' \
 '-DCIRCULAR_QUEUE_USE_LOCAL_CONFIG_HEADER=1' \
 '-DBUFFER_POOL_ALLOCATOR_USE_LOCAL_CONFIG_HEADER=1' \
 '-DSL_CODE_COMPONENT_CORE=core' \
 '-DSL_OPENTHREAD_CUSTOM_CLI_ENABLE=1' \
 '-DSL_CODE_COMPONENT_SLEEPTIMER=sleeptimer' \
 '-DSLI_RADIOAES_REQUIRES_MASKING=1'

INCLUDES += \
 -Iautogen \
 -Iconfig \
 -Iconfig/btconf \
 -I$(SDK_PATH)/../connectedhomeip/examples/platform/silabs \
 -I$(SDK_PATH)/platform/Device/SiliconLabs/MGM24/Include \
 -I$(SDK_PATH)/platform/common/inc \
 -I$(SDK_PATH)/protocol/bluetooth/bgcommon/inc \
 -I$(SDK_PATH)/protocol/bluetooth/inc \
 -I$(SDK_PATH)/protocol/bluetooth/bgstack/ll/inc \
 -I$(SDK_PATH)/hardware/board/inc \
 -I$(SDK_PATH)/platform/driver/button/inc \
 -I$(SDK_PATH)/platform/service/clock_manager/inc \
 -I$(SDK_PATH)/platform/service/clock_manager/src \
 -I$(SDK_PATH)/platform/CMSIS/Core/Include \
 -I$(SDK_PATH)/platform/CMSIS/RTOS2/Include \
 -I$(SDK_PATH)/hardware/driver/configuration_over_swo/inc \
 -I$(SDK_PATH)/platform/driver/debug/inc \
 -I$(SDK_PATH)/platform/service/device_manager/inc \
 -I$(SDK_PATH)/platform/service/device_init/inc \
 -I$(SDK_PATH)/platform/emdrv/dmadrv/inc \
 -I$(SDK_PATH)/platform/emdrv/dmadrv/inc/s2_signals \
 -I$(SDK_PATH)/platform/emdrv/common/inc \
 -I$(SDK_PATH)/platform/emlib/inc \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/fem_util \
 -I$(SDK_PATH)/util/third_party/freertos/cmsis/Include \
 -I$(SDK_PATH)/util/third_party/freertos/kernel/include \
 -I$(SDK_PATH)/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure \
 -I$(SDK_PATH)/platform/emdrv/gpiointerrupt/inc \
 -I$(SDK_PATH)/platform/peripheral/inc \
 -I$(SDK_PATH)/platform/service/hfxo_manager/inc \
 -I$(SDK_PATH)/platform/service/interrupt_manager/inc \
 -I$(SDK_PATH)/platform/service/interrupt_manager/inc/arm \
 -I$(SDK_PATH)/platform/service/iostream/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/config \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/config/preset \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/inc \
 -I$(SDK_PATH)/util/third_party/mbedtls/include \
 -I$(SDK_PATH)/util/third_party/mbedtls/library \
 -I$(SDK_PATH)/platform/service/memory_manager/inc \
 -I$(SDK_PATH)/platform/service/memory_manager/src \
 -I$(SDK_PATH)/platform/service/memory_manager/profiler/inc \
 -I$(SDK_PATH)/platform/service/mpu/inc \
 -I$(SDK_PATH)/platform/emdrv/nvm3/inc \
 -I$(SDK_PATH)/util/third_party/openthread/src \
 -I$(SDK_PATH)/util/third_party/openthread/src/cli \
 -I$(SDK_PATH)/protocol/openthread/platform-abstraction/efr32 \
 -I$(SDK_PATH)/util/third_party/openthread/include \
 -I$(SDK_PATH)/util/third_party/openthread/include/openthread \
 -I$(SDK_PATH)/util/third_party/openthread/src/core \
 -I$(SDK_PATH)/util/third_party/openthread/src/lib \
 -I$(SDK_PATH)/util/third_party/openthread/examples/platforms \
 -I$(SDK_PATH)/util/third_party/openthread/third_party/tcplp \
 -I$(SDK_PATH)/protocol/openthread/platform-abstraction/rtos \
 -I$(SDK_PATH)/protocol/openthread/platform-abstraction/include \
 -I$(SDK_PATH)/platform/service/power_manager/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_psa_driver/inc \
 -I$(SDK_PATH)/platform/radio/rail_lib/common \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/ble \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/ieee802154 \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/wmbus \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/zwave \
 -I$(SDK_PATH)/platform/radio/rail_lib/chip/efr32/efr32xg2x \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/sidewalk \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/efr32xg24 \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_pti \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_rssi \
 -I$(SDK_PATH)/platform/security/sl_component/se_manager/inc \
 -I$(SDK_PATH)/platform/security/sl_component/se_manager/src \
 -I$(SDK_PATH)/util/plugin/security_manager \
 -I$(SDK_PATH)/util/third_party/segger/systemview/SEGGER \
 -I$(SDK_PATH)/util/silicon_labs/silabs_core/queue \
 -I$(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager \
 -I$(SDK_PATH)/platform/common/toolchain/inc \
 -I$(SDK_PATH)/protocol/openthread/include \
 -I$(SDK_PATH)/platform/service/system/inc \
 -I$(SDK_PATH)/platform/service/sleeptimer/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src \
 -I$(SDK_PATH)/platform/emdrv/uartdrv/inc \
 -I$(SDK_PATH)/platform/service/udelay/inc

GROUP_START =-Wl,--start-group
GROUP_END =-Wl,--end-group

PROJECT_LIBS = \
 -lstdc++ \
 -lgcc \
 -lc \
 -lm \
 -lnosys \
 $(SDK_PATH)/protocol/bluetooth/bgcommon/lib/build/gcc/cortex-m33/bgcommon/release/libbgcommon.a \
 $(SDK_PATH)/protocol/bluetooth/bgstack/ll/lib/libbluetooth_controller_efr32xg24_gcc_release.a \
 $(SDK_PATH)/protocol/bluetooth/build/gcc/cortex-m33/bt_host/hal/release/libbt_hal_series2.a \
 $(SDK_PATH)/protocol/bluetooth/build/gcc/cortex-m33/bt_host/release/libbt_host.a \
 $(SDK_PATH)/platform/emdrv/nvm3/lib/libnvm3_CM33_gcc.a \
 $(SDK_PATH)/protocol/openthread/libs/libsl_openthread_efr32mg2x_gcc.a \
 $(SDK_PATH)/platform/radio/rail_lib/autogen/librail_release/librail_config_mgm240l022rnf_gcc.a \
 $(SDK_PATH)/platform/radio/rail_lib/autogen/librail_release/librail_multiprotocol_module_efr32xg24_gcc_release.a

LIBS += $(GROUP_START) $(PROJECT_LIBS) $(GROUP_END)

LIB_FILES += $(filter %.a, $(PROJECT_LIBS))

C_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -std=c18 \
 -Wall \
 -Wextra \
 -Os \
 -fdata-sections \
 -ffunction-sections \
 -fomit-frame-pointer \
 -imacros sl_openthread_ble_cli_config.h \
 -imacros sl_openthread_rtos_config.h \
 -imacros sl_gcc_preinclude.h \
 -mcmse \
 -Werror=unused-function \
 -Werror=unused-label \
 -Werror=unused-parameter \
 -Werror=unused-variable \
 -Wno-sign-compare \
 -Wno-unused-parameter \
 --specs=nano.specs \
 -g

CXX_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -std=c++17 \
 -fno-rtti \
 -fno-exceptions \
 -Wall \
 -Wextra \
 -Os \
 -fdata-sections \
 -ffunction-sections \
 -fomit-frame-pointer \
 -imacros sl_openthread_ble_cli_config.h \
 -imacros sl_openthread_rtos_config.h \
 -imacros sl_gcc_preinclude.h \
 -mcmse \
 -Werror=unused-function \
 -Werror=unused-label \
 -Werror=unused-parameter \
 -Werror=unused-variable \
 -Wno-sign-compare \
 -Wno-unused-parameter \
 --specs=nano.specs \
 -g

ASM_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -imacros sl_openthread_ble_cli_config.h \
 -imacros sl_openthread_rtos_config.h \
 -imacros sl_gcc_preinclude.h \
 -x assembler-with-cpp

LD_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -T"autogen/linkerfile.ld" \
 --specs=nano.specs \
 -Xlinker -Map=$(OUTPUT_DIR)/$(PROJECTNAME).map \
 -Wl,--wrap=_free_r -Wl,--wrap=_malloc_r -Wl,--wrap=_calloc_r -Wl,--wrap=_realloc_r \
 @${StudioSdkPath}${SDK_PATH}/protocol/openthread/linker/ot-rtos-wrapper-options \
 -Wl,--gc-sections \
 -Wl,--no-warn-rwx-segments


####################################################################
# Pre/Post Build Rules                                             #
####################################################################
pre-build:
	# No pre-build defined

post-build: $(OUTPUT_DIR)/$(PROJECTNAME).out
	# No post-build defined

####################################################################
# SDK Build Rules                                                  #
####################################################################
$(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.o: $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.o

$(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.o: $(SDK_PATH)/hardware/board/src/sl_board_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/board/src/sl_board_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/board/src/sl_board_init.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.o

$(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.o: $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.o

$(OUTPUT_DIR)/sdk/platform/CMSIS/RTOS2/Source/os_systick.o: $(SDK_PATH)/platform/CMSIS/RTOS2/Source/os_systick.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/CMSIS/RTOS2/Source/os_systick.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/CMSIS/RTOS2/Source/os_systick.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/CMSIS/RTOS2/Source/os_systick.d
OBJS += $(OUTPUT_DIR)/sdk/platform/CMSIS/RTOS2/Source/os_systick.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.o: $(SDK_PATH)/platform/common/src/sl_assert.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_assert.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_assert.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_core_cortexm.o: $(SDK_PATH)/platform/common/src/sl_core_cortexm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_core_cortexm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_core_cortexm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_core_cortexm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_core_cortexm.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.o: $(SDK_PATH)/platform/common/src/sl_slist.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_slist.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_slist.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.o: $(SDK_PATH)/platform/common/src/sl_syscalls.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_syscalls.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_syscalls.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.o

$(OUTPUT_DIR)/sdk/platform/common/src/sli_cmsis_os2_ext_task_register.o: $(SDK_PATH)/platform/common/src/sli_cmsis_os2_ext_task_register.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sli_cmsis_os2_ext_task_register.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sli_cmsis_os2_ext_task_register.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sli_cmsis_os2_ext_task_register.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sli_cmsis_os2_ext_task_register.o

$(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.o: $(SDK_PATH)/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.d
OBJS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.o

$(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.o: $(SDK_PATH)/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.d
OBJS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.o

$(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_button.o: $(SDK_PATH)/platform/driver/button/src/sl_button.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/button/src/sl_button.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/button/src/sl_button.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_button.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_button.o

$(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_simple_button.o: $(SDK_PATH)/platform/driver/button/src/sl_simple_button.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/button/src/sl_simple_button.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/button/src/sl_simple_button.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_simple_button.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_simple_button.o

$(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.o: $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.o

$(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.o: $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.o

$(OUTPUT_DIR)/sdk/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o: $(SDK_PATH)/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/gpiointerrupt/src/gpiointerrupt.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o

$(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_default_common_linker.o: $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_default_common_linker.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_default_common_linker.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_default_common_linker.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_default_common_linker.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_default_common_linker.o

$(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_hal_flash.o: $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_hal_flash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_hal_flash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_hal_flash.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_hal_flash.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_hal_flash.o

$(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_lock.o: $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_lock.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_lock.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_lock.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_lock.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_lock.o

$(OUTPUT_DIR)/sdk/platform/emdrv/uartdrv/src/uartdrv.o: $(SDK_PATH)/platform/emdrv/uartdrv/src/uartdrv.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/uartdrv/src/uartdrv.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/uartdrv/src/uartdrv.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/uartdrv/src/uartdrv.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/uartdrv/src/uartdrv.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_acmp.o: $(SDK_PATH)/platform/emlib/src/em_acmp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_acmp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_acmp.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_acmp.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_acmp.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_burtc.o: $(SDK_PATH)/platform/emlib/src/em_burtc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_burtc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_burtc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_burtc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_burtc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.o: $(SDK_PATH)/platform/emlib/src/em_cmu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_cmu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_cmu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.o: $(SDK_PATH)/platform/emlib/src/em_core.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_core.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_core.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.o: $(SDK_PATH)/platform/emlib/src/em_dbg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_dbg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_dbg.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.o: $(SDK_PATH)/platform/emlib/src/em_emu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_emu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_emu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_eusart.o: $(SDK_PATH)/platform/emlib/src/em_eusart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_eusart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_eusart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_eusart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_eusart.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.o: $(SDK_PATH)/platform/emlib/src/em_gpcrc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_gpcrc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_gpcrc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.o: $(SDK_PATH)/platform/emlib/src/em_gpio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_gpio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_gpio.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.o: $(SDK_PATH)/platform/emlib/src/em_i2c.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_i2c.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_i2c.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_iadc.o: $(SDK_PATH)/platform/emlib/src/em_iadc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_iadc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_iadc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_iadc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_iadc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.o: $(SDK_PATH)/platform/emlib/src/em_ldma.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_ldma.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_ldma.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.o: $(SDK_PATH)/platform/emlib/src/em_letimer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_letimer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_letimer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.o: $(SDK_PATH)/platform/emlib/src/em_msc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_msc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_msc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_opamp.o: $(SDK_PATH)/platform/emlib/src/em_opamp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_opamp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_opamp.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_opamp.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_opamp.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_pcnt.o: $(SDK_PATH)/platform/emlib/src/em_pcnt.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_pcnt.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_pcnt.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_pcnt.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_pcnt.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.o: $(SDK_PATH)/platform/emlib/src/em_prs.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_prs.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_prs.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.o: $(SDK_PATH)/platform/emlib/src/em_rmu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_rmu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_rmu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_se.o: $(SDK_PATH)/platform/emlib/src/em_se.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_se.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_se.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_se.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_se.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.o: $(SDK_PATH)/platform/emlib/src/em_system.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_system.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_system.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.o: $(SDK_PATH)/platform/emlib/src/em_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.o: $(SDK_PATH)/platform/emlib/src/em_usart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_usart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_usart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_vdac.o: $(SDK_PATH)/platform/emlib/src/em_vdac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_vdac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_vdac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_vdac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_vdac.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.o: $(SDK_PATH)/platform/emlib/src/em_wdog.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_wdog.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_wdog.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.o

$(OUTPUT_DIR)/sdk/platform/peripheral/src/sl_hal_sysrtc.o: $(SDK_PATH)/platform/peripheral/src/sl_hal_sysrtc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/peripheral/src/sl_hal_sysrtc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/peripheral/src/sl_hal_sysrtc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/peripheral/src/sl_hal_sysrtc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/peripheral/src/sl_hal_sysrtc.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/fem_util/sl_fem_util.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/fem_util/sl_fem_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/fem_util/sl_fem_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/fem_util/sl_fem_util.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/fem_util/sl_fem_util.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/fem_util/sl_fem_util.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_rssi/sl_rail_util_rssi.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_rssi/sl_rail_util_rssi.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_rssi/sl_rail_util_rssi.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_rssi/sl_rail_util_rssi.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_rssi/sl_rail_util_rssi.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_rssi/sl_rail_util_rssi.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_sequencer/sl_rail_util_sequencer.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_hash.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_hash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_hash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_hash.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_hash.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_hash.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_signature.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_signature.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_signature.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_signature.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_signature.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_signature.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_util.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_util.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_util.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_util.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sli_se_manager_mailbox.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sli_se_manager_mailbox.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sli_se_manager_mailbox.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sli_se_manager_mailbox.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sli_se_manager_mailbox.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sli_se_manager_mailbox.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_sha.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/se_aes.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/se_aes.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/se_aes.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/se_aes.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/se_aes.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/se_aes.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/se_jpake.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/se_jpake.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/se_jpake.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/se_jpake.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/se_jpake.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/se_jpake.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_entropy_hardware.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.o: $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.o: $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_aead.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_aead.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_aead.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_aead.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_aead.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_aead.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_builtin_keys.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_builtin_keys.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_builtin_keys.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_builtin_keys.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_builtin_keys.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_builtin_keys.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_cipher.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_cipher.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_derivation.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_derivation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_derivation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_derivation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_derivation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_derivation.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_management.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_management.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_management.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_management.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_management.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_key_management.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_mac.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_mac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_mac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_mac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_mac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_mac.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_signature.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_signature.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_signature.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_signature.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_signature.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_driver_signature.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_aead.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_aead.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_aead.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_aead.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_aead.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_aead.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_cipher.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_cipher.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_mac.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_mac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_mac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_mac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_mac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_driver_mac.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_key_derivation.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_key_derivation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_key_derivation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_key_derivation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_key_derivation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_opaque_key_derivation.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_aead.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_aead.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_aead.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_aead.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_aead.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_aead.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_cipher.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_cipher.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_hash.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_hash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_hash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_hash.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_hash.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_hash.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_mac.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_mac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_mac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_mac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_mac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_driver_mac.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_key_derivation.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_key_derivation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_key_derivation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_key_derivation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_key_derivation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_transparent_key_derivation.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.o

$(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager.o: $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager.o

$(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_hal_s2.o: $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_hal_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_hal_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_hal_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_hal_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_hal_s2.o

$(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_init.o: $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_init.o

$(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.o: $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.o: $(SDK_PATH)/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.o

$(OUTPUT_DIR)/sdk/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.o: $(SDK_PATH)/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.o

$(OUTPUT_DIR)/sdk/platform/service/device_manager/src/sl_device_clock.o: $(SDK_PATH)/platform/service/device_manager/src/sl_device_clock.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_manager/src/sl_device_clock.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_manager/src/sl_device_clock.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_manager/src/sl_device_clock.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_manager/src/sl_device_clock.o

$(OUTPUT_DIR)/sdk/platform/service/device_manager/src/sl_device_peripheral.o: $(SDK_PATH)/platform/service/device_manager/src/sl_device_peripheral.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_manager/src/sl_device_peripheral.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_manager/src/sl_device_peripheral.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_manager/src/sl_device_peripheral.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_manager/src/sl_device_peripheral.o

$(OUTPUT_DIR)/sdk/platform/service/hfxo_manager/src/sl_hfxo_manager.o: $(SDK_PATH)/platform/service/hfxo_manager/src/sl_hfxo_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/hfxo_manager/src/sl_hfxo_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/hfxo_manager/src/sl_hfxo_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/hfxo_manager/src/sl_hfxo_manager.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/hfxo_manager/src/sl_hfxo_manager.o

$(OUTPUT_DIR)/sdk/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.o: $(SDK_PATH)/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.o

$(OUTPUT_DIR)/sdk/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.o: $(SDK_PATH)/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_rtt.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_rtt.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_rtt.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_rtt.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_rtt.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_rtt.o

$(OUTPUT_DIR)/sdk/platform/service/memory_manager/profiler/src/sli_memory_profiler_stubs.o: $(SDK_PATH)/platform/service/memory_manager/profiler/src/sli_memory_profiler_stubs.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/memory_manager/profiler/src/sli_memory_profiler_stubs.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/memory_manager/profiler/src/sli_memory_profiler_stubs.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/profiler/src/sli_memory_profiler_stubs.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/profiler/src/sli_memory_profiler_stubs.o

$(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager.o: $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager.o

$(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_cpp.o: $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_cpp.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_cpp.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_cpp.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_cpp.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_cpp.o

$(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.o: $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.o

$(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_pool.o: $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_pool.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_pool.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_pool.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_pool.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_pool.o

$(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_region.o: $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_region.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_region.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_region.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_region.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_region.o

$(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_retarget.o: $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_retarget.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_retarget.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/memory_manager/src/sl_memory_manager_retarget.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_retarget.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sl_memory_manager_retarget.o

$(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sli_memory_manager_common.o: $(SDK_PATH)/platform/service/memory_manager/src/sli_memory_manager_common.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/memory_manager/src/sli_memory_manager_common.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/memory_manager/src/sli_memory_manager_common.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sli_memory_manager_common.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/memory_manager/src/sli_memory_manager_common.o

$(OUTPUT_DIR)/sdk/platform/service/mpu/src/sl_mpu.o: $(SDK_PATH)/platform/service/mpu/src/sl_mpu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/mpu/src/sl_mpu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/mpu/src/sl_mpu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/mpu/src/sl_mpu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/mpu/src/sl_mpu.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s2.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s2.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o

$(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.o: $(SDK_PATH)/platform/service/system/src/sl_system_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/system/src/sl_system_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/system/src/sl_system_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.o

$(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_kernel.o: $(SDK_PATH)/platform/service/system/src/sl_system_kernel.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/system/src/sl_system_kernel.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/system/src/sl_system_kernel.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_kernel.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_kernel.o

$(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.o: $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.o

$(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.o: $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(ASMFLAGS) -c -o $@ $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S
ASMDEPS_S += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/bgcommon/src/sli_bgcommon_debug_efr32.o: $(SDK_PATH)/protocol/bluetooth/bgcommon/src/sli_bgcommon_debug_efr32.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/bgcommon/src/sli_bgcommon_debug_efr32.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/bgcommon/src/sli_bgcommon_debug_efr32.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/bgcommon/src/sli_bgcommon_debug_efr32.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/bgcommon/src/sli_bgcommon_debug_efr32.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_rtos_adaptation.o: $(SDK_PATH)/protocol/bluetooth/src/sl_bt_rtos_adaptation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sl_bt_rtos_adaptation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sl_bt_rtos_adaptation.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_rtos_adaptation.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_rtos_adaptation.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.o: $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_host_adaptation.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_host_adaptation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_host_adaptation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_host_adaptation.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_host_adaptation.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_host_adaptation.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/alarm.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/alarm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/alarm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/alarm.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/alarm.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/alarm.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/crypto.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/crypto.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/crypto.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/diag.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/diag.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/diag.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/diag.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/diag.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/diag.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/entropy.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/entropy.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/entropy.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/entropy.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/entropy.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/entropy.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/flash.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/flash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/flash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/flash.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/flash.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/flash.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/ieee802154-packet-utils.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/ieee802154-packet-utils.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/ieee802154-packet-utils.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/ieee802154-packet-utils.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/ieee802154-packet-utils.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/ieee802154-packet-utils.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/memory.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/memory.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/memory.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/memory.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/memory.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/memory.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/misc.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/misc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/misc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/misc.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/misc.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/misc.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_coex.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_coex.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_coex.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_coex.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_coex.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_coex.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_extension.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_extension.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_extension.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_extension.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_extension.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_extension.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_power_manager.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_power_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_power_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/radio_power_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_power_manager.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/radio_power_manager.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/sl_gp_interface.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/sl_gp_interface.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/sl_gp_interface.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/sl_gp_interface.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/sl_gp_interface.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/sl_gp_interface.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/sleep.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/sleep.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/sleep.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/sleep.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/sleep.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/sleep.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/soft_source_match_table.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/soft_source_match_table.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/soft_source_match_table.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/soft_source_match_table.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/soft_source_match_table.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/soft_source_match_table.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/startup-gcc.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/startup-gcc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/startup-gcc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/startup-gcc.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/startup-gcc.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/startup-gcc.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/system.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/system.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/system.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/efr32/system.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/system.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/efr32/system.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_ftd_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_ftd_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_ftd_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_ftd_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_ftd_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_ftd_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/backbone_router_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ble_secure_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ble_secure_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ble_secure_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ble_secure_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ble_secure_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ble_secure_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_agent_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_agent_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_agent_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_agent_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_agent_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_agent_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_router_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_router_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_router_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_router_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_router_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_router_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_routing_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_routing_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_routing_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_routing_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_routing_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/border_routing_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_manager_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_manager_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_manager_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_manager_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_manager_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_manager_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_monitor_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_monitor_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_monitor_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_monitor_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_monitor_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/channel_monitor_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/child_supervision_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/child_supervision_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/child_supervision_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/child_supervision_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/child_supervision_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/child_supervision_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/cli_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/cli_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/cli_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/cli_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/cli_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/cli_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_secure_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_secure_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_secure_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_secure_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_secure_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_secure_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/coap_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/commissioner_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/commissioner_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/commissioner_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/commissioner_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/commissioner_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/commissioner_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/config_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/config_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/config_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/config_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/config_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/config_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/crypto_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/crypto_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/crypto_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/crypto_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/crypto_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/crypto_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_ftd_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_ftd_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_ftd_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_ftd_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_ftd_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_ftd_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_updater_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_updater_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_updater_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_updater_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_updater_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_updater_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dataset_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/diag_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/diag_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/diag_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/diag_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/diag_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/diag_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_client_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_client_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_client_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_client_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_client_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_client_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dns_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dnssd_server_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dnssd_server_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dnssd_server_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dnssd_server_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dnssd_server_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/dnssd_server_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/error_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/error_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/error_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/error_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/error_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/error_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/heap_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/heap_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/heap_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/heap_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/heap_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/heap_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/history_tracker_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/history_tracker_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/history_tracker_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/history_tracker_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/history_tracker_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/history_tracker_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/icmp6_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/icmp6_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/icmp6_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/icmp6_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/icmp6_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/icmp6_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/instance_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/instance_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/instance_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/instance_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/instance_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/instance_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ip6_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ip6_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ip6_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ip6_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ip6_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ip6_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/jam_detection_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/jam_detection_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/jam_detection_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/jam_detection_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/jam_detection_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/jam_detection_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/joiner_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/joiner_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/joiner_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/joiner_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/joiner_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/joiner_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_metrics_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_metrics_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_metrics_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_metrics_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_metrics_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_metrics_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_raw_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_raw_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_raw_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_raw_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_raw_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_raw_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/link_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/logging_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/logging_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/logging_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/logging_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/logging_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/logging_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/mesh_diag_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/mesh_diag_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/mesh_diag_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/mesh_diag_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/mesh_diag_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/mesh_diag_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/message_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/message_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/message_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/message_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/message_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/message_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/multi_radio_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/multi_radio_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/multi_radio_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/multi_radio_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/multi_radio_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/multi_radio_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/nat64_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/nat64_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/nat64_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/nat64_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/nat64_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/nat64_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ncp_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ncp_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ncp_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ncp_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ncp_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ncp_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_publisher_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_publisher_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_publisher_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_publisher_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_publisher_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_publisher_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdata_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdiag_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdiag_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdiag_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdiag_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdiag_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/netdiag_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/network_time_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/network_time_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/network_time_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/network_time_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/network_time_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/network_time_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ping_sender_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ping_sender_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ping_sender_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ping_sender_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ping_sender_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/ping_sender_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/radio_stats_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/radio_stats_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/radio_stats_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/radio_stats_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/radio_stats_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/radio_stats_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_crypto_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_crypto_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_crypto_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_crypto_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_crypto_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_crypto_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_noncrypto_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_noncrypto_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_noncrypto_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_noncrypto_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_noncrypto_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/random_noncrypto_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/server_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/server_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/server_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/server_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/server_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/server_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/sntp_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/sntp_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/sntp_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/sntp_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/sntp_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/sntp_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_buffers_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_buffers_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_buffers_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_buffers_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_buffers_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_buffers_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_client_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_server_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_server_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_server_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_server_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_server_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/srp_server_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tasklet_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tasklet_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tasklet_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tasklet_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tasklet_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tasklet_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcat_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcat_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcat_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcat_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcat_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcat_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_ext_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_ext_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_ext_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_ext_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_ext_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_ext_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/tcp_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_ftd_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_ftd_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_ftd_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_ftd_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_ftd_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_ftd_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/thread_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/trel_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/trel_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/trel_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/trel_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/trel_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/trel_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/udp_wrapper.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/udp_wrapper.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/udp_wrapper.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/udp_wrapper.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/udp_wrapper.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/rtos-wrappers/udp_wrapper.o

$(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/sl_ot_rtos_adaptation.o: $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/sl_ot_rtos_adaptation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/sl_ot_rtos_adaptation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/platform-abstraction/rtos/sl_ot_rtos_adaptation.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/sl_ot_rtos_adaptation.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/platform-abstraction/rtos/sl_ot_rtos_adaptation.o

$(OUTPUT_DIR)/sdk/protocol/openthread/src/cli/bluetooth_cli.o: $(SDK_PATH)/protocol/openthread/src/cli/bluetooth_cli.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/src/cli/bluetooth_cli.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/src/cli/bluetooth_cli.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/src/cli/bluetooth_cli.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/src/cli/bluetooth_cli.o

$(OUTPUT_DIR)/sdk/protocol/openthread/src/cli/cli_utils.o: $(SDK_PATH)/protocol/openthread/src/cli/cli_utils.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/openthread/src/cli/cli_utils.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/openthread/src/cli/cli_utils.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/openthread/src/cli/cli_utils.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/openthread/src/cli/cli_utils.o

$(OUTPUT_DIR)/sdk/util/plugin/security_manager/security_manager.o: $(SDK_PATH)/util/plugin/security_manager/security_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/plugin/security_manager/security_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/plugin/security_manager/security_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/util/plugin/security_manager/security_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/plugin/security_manager/security_manager.o

$(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/buffer_pool_allocator.o: $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/buffer_pool_allocator.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/buffer_pool_allocator.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/buffer_pool_allocator.c
CDEPS += $(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/buffer_pool_allocator.d
OBJS += $(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/buffer_pool_allocator.o

$(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/queue/circular_queue.o: $(SDK_PATH)/util/silicon_labs/silabs_core/queue/circular_queue.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/silicon_labs/silabs_core/queue/circular_queue.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/silicon_labs/silabs_core/queue/circular_queue.c
CDEPS += $(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/queue/circular_queue.d
OBJS += $(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/queue/circular_queue.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/cmsis/Source/cmsis_os2.o: $(SDK_PATH)/util/third_party/freertos/cmsis/Source/cmsis_os2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/cmsis/Source/cmsis_os2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/cmsis/Source/cmsis_os2.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/cmsis/Source/cmsis_os2.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/cmsis/Source/cmsis_os2.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/croutine.o: $(SDK_PATH)/util/third_party/freertos/kernel/croutine.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/croutine.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/croutine.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/croutine.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/croutine.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/event_groups.o: $(SDK_PATH)/util/third_party/freertos/kernel/event_groups.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/event_groups.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/event_groups.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/event_groups.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/event_groups.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/list.o: $(SDK_PATH)/util/third_party/freertos/kernel/list.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/list.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/list.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/list.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/list.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.o: $(SDK_PATH)/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.o: $(SDK_PATH)/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/MemMang/heap_3.o: $(SDK_PATH)/util/third_party/freertos/kernel/portable/MemMang/heap_3.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/portable/MemMang/heap_3.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/portable/MemMang/heap_3.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/MemMang/heap_3.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/MemMang/heap_3.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/SiliconLabs/tick_power_manager.o: $(SDK_PATH)/util/third_party/freertos/kernel/portable/SiliconLabs/tick_power_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/portable/SiliconLabs/tick_power_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/portable/SiliconLabs/tick_power_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/SiliconLabs/tick_power_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/portable/SiliconLabs/tick_power_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/queue.o: $(SDK_PATH)/util/third_party/freertos/kernel/queue.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/queue.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/queue.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/queue.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/queue.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/stream_buffer.o: $(SDK_PATH)/util/third_party/freertos/kernel/stream_buffer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/stream_buffer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/stream_buffer.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/stream_buffer.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/stream_buffer.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/tasks.o: $(SDK_PATH)/util/third_party/freertos/kernel/tasks.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/tasks.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/tasks.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/tasks.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/tasks.o

$(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/timers.o: $(SDK_PATH)/util/third_party/freertos/kernel/timers.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/freertos/kernel/timers.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/freertos/kernel/timers.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/timers.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/freertos/kernel/timers.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/aes.o: $(SDK_PATH)/util/third_party/mbedtls/library/aes.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/aes.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/aes.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/aes.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/aes.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/asn1parse.o: $(SDK_PATH)/util/third_party/mbedtls/library/asn1parse.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/asn1parse.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/asn1parse.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/asn1parse.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/asn1parse.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/asn1write.o: $(SDK_PATH)/util/third_party/mbedtls/library/asn1write.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/asn1write.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/asn1write.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/asn1write.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/asn1write.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/base64.o: $(SDK_PATH)/util/third_party/mbedtls/library/base64.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/base64.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/base64.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/base64.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/base64.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum.o: $(SDK_PATH)/util/third_party/mbedtls/library/bignum.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/bignum.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/bignum.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_core.o: $(SDK_PATH)/util/third_party/mbedtls/library/bignum_core.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/bignum_core.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/bignum_core.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_core.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_core.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod.o: $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod_raw.o: $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod_raw.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod_raw.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/bignum_mod_raw.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod_raw.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/bignum_mod_raw.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ccm.o: $(SDK_PATH)/util/third_party/mbedtls/library/ccm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ccm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ccm.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ccm.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ccm.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.o: $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.o: $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cmac.o: $(SDK_PATH)/util/third_party/mbedtls/library/cmac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/cmac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/cmac.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cmac.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cmac.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.o: $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ctr_drbg.o: $(SDK_PATH)/util/third_party/mbedtls/library/ctr_drbg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ctr_drbg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ctr_drbg.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ctr_drbg.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ctr_drbg.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdh.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecdh.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecdh.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecdh.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdh.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdh.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdsa.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecdsa.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecdsa.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecdsa.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdsa.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecdsa.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecjpake.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecjpake.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecjpake.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecjpake.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecjpake.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecjpake.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecp.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves_new.o: $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves_new.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves_new.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ecp_curves_new.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves_new.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ecp_curves_new.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy.o: $(SDK_PATH)/util/third_party/mbedtls/library/entropy.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/entropy.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/entropy.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy_poll.o: $(SDK_PATH)/util/third_party/mbedtls/library/entropy_poll.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/entropy_poll.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/entropy_poll.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy_poll.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/entropy_poll.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/hmac_drbg.o: $(SDK_PATH)/util/third_party/mbedtls/library/hmac_drbg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/hmac_drbg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/hmac_drbg.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/hmac_drbg.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/hmac_drbg.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/md.o: $(SDK_PATH)/util/third_party/mbedtls/library/md.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/md.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/md.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/md.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/md.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/oid.o: $(SDK_PATH)/util/third_party/mbedtls/library/oid.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/oid.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/oid.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/oid.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/oid.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pem.o: $(SDK_PATH)/util/third_party/mbedtls/library/pem.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/pem.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/pem.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pem.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pem.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pk.o: $(SDK_PATH)/util/third_party/mbedtls/library/pk.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/pk.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/pk.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pk.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pk.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pk_wrap.o: $(SDK_PATH)/util/third_party/mbedtls/library/pk_wrap.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/pk_wrap.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/pk_wrap.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pk_wrap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pk_wrap.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pkparse.o: $(SDK_PATH)/util/third_party/mbedtls/library/pkparse.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/pkparse.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/pkparse.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pkparse.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pkparse.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pkwrite.o: $(SDK_PATH)/util/third_party/mbedtls/library/pkwrite.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/pkwrite.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/pkwrite.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pkwrite.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/pkwrite.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.o: $(SDK_PATH)/util/third_party/mbedtls/library/platform.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/platform.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/platform.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.o: $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_aead.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_aead.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_aead.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_aead.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_aead.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_aead.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_cipher.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_cipher.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ecp.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ecp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ecp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ecp.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ecp.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ecp.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ffdh.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ffdh.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ffdh.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ffdh.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ffdh.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ffdh.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_hash.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_hash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_hash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_hash.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_hash.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_hash.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_mac.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_mac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_mac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_mac.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_mac.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_mac.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_pake.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_pake.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_pake.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_pake.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_pake.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_pake.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_rsa.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_rsa.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_rsa.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_rsa.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_rsa.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_rsa.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_se.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_se.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_se.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_se.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_se.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_se.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_slot_management.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_slot_management.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_slot_management.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_slot_management.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_slot_management.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_slot_management.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_storage.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_storage.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_storage.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_storage.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_storage.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_storage.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/sha256.o: $(SDK_PATH)/util/third_party/mbedtls/library/sha256.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/sha256.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/sha256.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/sha256.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/sha256.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_cache.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_cache.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_cache.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_cache.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_cache.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_cache.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_ciphersuites.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_ciphersuites.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_ciphersuites.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_ciphersuites.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_ciphersuites.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_ciphersuites.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_client.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_client.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_client.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_client.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_client.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_cookie.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_cookie.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_cookie.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_cookie.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_cookie.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_cookie.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_debug_helpers_generated.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_debug_helpers_generated.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_debug_helpers_generated.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_debug_helpers_generated.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_debug_helpers_generated.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_debug_helpers_generated.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_msg.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_msg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_msg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_msg.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_msg.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_msg.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_ticket.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_ticket.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_ticket.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_ticket.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_ticket.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_ticket.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls12_client.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls12_client.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls12_client.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls12_client.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls12_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls12_client.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls12_server.o: $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls12_server.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls12_server.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/ssl_tls12_server.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls12_server.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/ssl_tls12_server.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.o: $(SDK_PATH)/util/third_party/mbedtls/library/threading.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/threading.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/threading.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509.o: $(SDK_PATH)/util/third_party/mbedtls/library/x509.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/x509.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/x509.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_create.o: $(SDK_PATH)/util/third_party/mbedtls/library/x509_create.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/x509_create.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/x509_create.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_create.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_create.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_crl.o: $(SDK_PATH)/util/third_party/mbedtls/library/x509_crl.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/x509_crl.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/x509_crl.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_crl.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_crl.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_crt.o: $(SDK_PATH)/util/third_party/mbedtls/library/x509_crt.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/x509_crt.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/x509_crt.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_crt.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_crt.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_csr.o: $(SDK_PATH)/util/third_party/mbedtls/library/x509_csr.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/x509_csr.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/x509_csr.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_csr.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509_csr.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write.o: $(SDK_PATH)/util/third_party/mbedtls/library/x509write.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/x509write.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/x509write.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write_crt.o: $(SDK_PATH)/util/third_party/mbedtls/library/x509write_crt.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/x509write_crt.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/x509write_crt.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write_crt.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write_crt.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write_csr.o: $(SDK_PATH)/util/third_party/mbedtls/library/x509write_csr.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/x509write_csr.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/x509write_csr.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write_csr.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/x509write_csr.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/apps/cli/cli_uart.o: $(SDK_PATH)/util/third_party/openthread/examples/apps/cli/cli_uart.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/examples/apps/cli/cli_uart.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/examples/apps/cli/cli_uart.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/apps/cli/cli_uart.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/apps/cli/cli_uart.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/debug_uart.o: $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/debug_uart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/debug_uart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/debug_uart.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/debug_uart.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/debug_uart.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/link_metrics.o: $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/link_metrics.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/link_metrics.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/link_metrics.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/link_metrics.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/link_metrics.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/mac_frame.o: $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/mac_frame.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/mac_frame.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/mac_frame.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/mac_frame.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/mac_frame.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/settings_ram.o: $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/settings_ram.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/settings_ram.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/settings_ram.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/settings_ram.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/settings_ram.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/uart_rtt.o: $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/uart_rtt.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/uart_rtt.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/examples/platforms/utils/uart_rtt.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/uart_rtt.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/examples/platforms/utils/uart_rtt.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_bbr.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_bbr.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_bbr.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_bbr.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_bbr.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_bbr.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_br.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_br.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_br.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_br.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_br.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_br.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_coap.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_coap.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_coap.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_coap.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_coap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_coap.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_coap_secure.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_coap_secure.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_coap_secure.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_coap_secure.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_coap_secure.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_coap_secure.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_commissioner.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_commissioner.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_commissioner.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_commissioner.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_commissioner.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_commissioner.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_dataset.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_dataset.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_dataset.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_dataset.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_dataset.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_dataset.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_dns.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_dns.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_dns.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_dns.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_dns.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_dns.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_history.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_history.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_history.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_history.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_history.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_history.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_joiner.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_joiner.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_joiner.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_joiner.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_joiner.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_joiner.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_link_metrics.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_link_metrics.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_link_metrics.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_link_metrics.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_link_metrics.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_link_metrics.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_mac_filter.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_mac_filter.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_mac_filter.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_mac_filter.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_mac_filter.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_mac_filter.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_mdns.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_mdns.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_mdns.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_mdns.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_mdns.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_mdns.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_network_data.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_network_data.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_network_data.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_network_data.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_network_data.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_network_data.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_ping.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_ping.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_ping.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_ping.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_ping.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_ping.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_srp_client.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_srp_client.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_srp_client.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_srp_client.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_srp_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_srp_client.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_srp_server.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_srp_server.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_srp_server.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_srp_server.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_srp_server.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_srp_server.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_tcat.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_tcat.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_tcat.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_tcat.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_tcat.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_tcat.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_tcp.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_tcp.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_tcp.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_tcp.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_tcp.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_tcp.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_udp.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_udp.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_udp.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_udp.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_udp.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_udp.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_utils.o: $(SDK_PATH)/util/third_party/openthread/src/cli/cli_utils.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/cli/cli_utils.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/cli/cli_utils.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_utils.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/cli/cli_utils.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/backbone_router_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/backbone_router_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/backbone_router_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/backbone_router_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/backbone_router_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/backbone_router_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/backbone_router_ftd_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/backbone_router_ftd_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/backbone_router_ftd_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/backbone_router_ftd_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/backbone_router_ftd_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/backbone_router_ftd_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ble_secure_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/ble_secure_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/ble_secure_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/ble_secure_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ble_secure_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ble_secure_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_agent_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/border_agent_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/border_agent_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/border_agent_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_agent_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_agent_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_router_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/border_router_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/border_router_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/border_router_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_router_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_router_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_routing_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/border_routing_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/border_routing_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/border_routing_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_routing_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/border_routing_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/channel_manager_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/channel_manager_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/channel_manager_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/channel_manager_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/channel_manager_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/channel_manager_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/channel_monitor_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/channel_monitor_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/channel_monitor_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/channel_monitor_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/channel_monitor_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/channel_monitor_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/child_supervision_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/child_supervision_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/child_supervision_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/child_supervision_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/child_supervision_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/child_supervision_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/coap_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/coap_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/coap_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/coap_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/coap_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/coap_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/coap_secure_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/coap_secure_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/coap_secure_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/coap_secure_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/coap_secure_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/coap_secure_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/commissioner_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/commissioner_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/commissioner_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/commissioner_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/commissioner_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/commissioner_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/crypto_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/crypto_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/crypto_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/crypto_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/crypto_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/crypto_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_ftd_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_ftd_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_ftd_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_ftd_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_ftd_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_ftd_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_updater_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_updater_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_updater_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/dataset_updater_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_updater_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dataset_updater_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/diags_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/diags_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/diags_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/diags_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/diags_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/diags_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dns_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/dns_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/dns_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/dns_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dns_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dns_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dns_server_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/dns_server_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/dns_server_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/dns_server_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dns_server_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/dns_server_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/error_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/error_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/error_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/error_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/error_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/error_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/heap_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/heap_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/heap_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/heap_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/heap_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/heap_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/history_tracker_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/history_tracker_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/history_tracker_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/history_tracker_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/history_tracker_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/history_tracker_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/icmp6_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/icmp6_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/icmp6_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/icmp6_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/icmp6_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/icmp6_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/instance_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/instance_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/instance_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/instance_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/instance_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/instance_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ip6_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/ip6_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/ip6_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/ip6_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ip6_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ip6_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/jam_detection_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/jam_detection_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/jam_detection_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/jam_detection_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/jam_detection_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/jam_detection_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/joiner_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/joiner_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/joiner_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/joiner_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/joiner_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/joiner_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/link_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/link_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/link_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_metrics_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/link_metrics_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/link_metrics_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/link_metrics_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_metrics_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_metrics_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_raw_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/link_raw_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/link_raw_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/link_raw_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_raw_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/link_raw_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/logging_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/logging_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/logging_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/logging_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/logging_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/logging_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/mdns_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/mdns_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/mdns_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/mdns_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/mdns_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/mdns_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/mesh_diag_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/mesh_diag_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/mesh_diag_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/mesh_diag_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/mesh_diag_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/mesh_diag_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/message_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/message_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/message_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/message_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/message_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/message_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/multi_radio_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/multi_radio_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/multi_radio_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/multi_radio_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/multi_radio_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/multi_radio_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/nat64_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/nat64_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/nat64_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/nat64_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/nat64_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/nat64_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdata_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/netdata_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/netdata_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/netdata_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdata_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdata_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdata_publisher_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/netdata_publisher_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/netdata_publisher_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/netdata_publisher_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdata_publisher_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdata_publisher_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdiag_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/netdiag_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/netdiag_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/netdiag_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdiag_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/netdiag_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/network_time_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/network_time_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/network_time_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/network_time_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/network_time_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/network_time_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ping_sender_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/ping_sender_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/ping_sender_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/ping_sender_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ping_sender_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/ping_sender_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/radio_stats_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/radio_stats_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/radio_stats_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/radio_stats_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/radio_stats_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/radio_stats_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/random_crypto_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/random_crypto_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/random_crypto_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/random_crypto_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/random_crypto_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/random_crypto_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/random_noncrypto_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/random_noncrypto_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/random_noncrypto_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/random_noncrypto_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/random_noncrypto_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/random_noncrypto_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/server_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/server_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/server_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/server_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/server_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/server_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/sntp_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/sntp_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/sntp_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/sntp_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/sntp_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/sntp_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_client_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_client_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_client_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_client_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_client_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_client_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_client_buffers_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_client_buffers_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_client_buffers_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_client_buffers_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_client_buffers_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_client_buffers_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_server_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_server_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_server_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/srp_server_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_server_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/srp_server_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tasklet_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/tasklet_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/tasklet_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/tasklet_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tasklet_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tasklet_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tcp_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/tcp_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/tcp_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/tcp_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tcp_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tcp_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tcp_ext_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/tcp_ext_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/tcp_ext_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/tcp_ext_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tcp_ext_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/tcp_ext_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/thread_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/thread_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/thread_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/thread_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/thread_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/thread_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/thread_ftd_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/thread_ftd_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/thread_ftd_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/thread_ftd_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/thread_ftd_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/thread_ftd_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/trel_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/trel_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/trel_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/trel_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/trel_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/trel_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/udp_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/udp_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/udp_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/udp_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/udp_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/udp_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/verhoeff_checksum_api.o: $(SDK_PATH)/util/third_party/openthread/src/core/api/verhoeff_checksum_api.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/api/verhoeff_checksum_api.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/api/verhoeff_checksum_api.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/verhoeff_checksum_api.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/api/verhoeff_checksum_api.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/backbone_tmf.o: $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/backbone_tmf.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/backbone_tmf.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/backbone_tmf.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/backbone_tmf.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/backbone_tmf.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_leader.o: $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_leader.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_leader.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_leader.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_leader.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_leader.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_local.o: $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_local.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_local.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_local.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_local.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_local.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_manager.o: $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_manager.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_manager.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/bbr_manager.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/bbr_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/multicast_listeners_table.o: $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/multicast_listeners_table.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/multicast_listeners_table.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/multicast_listeners_table.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/multicast_listeners_table.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/multicast_listeners_table.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/ndproxy_table.o: $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/ndproxy_table.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/ndproxy_table.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/backbone_router/ndproxy_table.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/ndproxy_table.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/backbone_router/ndproxy_table.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/border_router/infra_if.o: $(SDK_PATH)/util/third_party/openthread/src/core/border_router/infra_if.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/border_router/infra_if.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/border_router/infra_if.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/border_router/infra_if.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/border_router/infra_if.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/border_router/routing_manager.o: $(SDK_PATH)/util/third_party/openthread/src/core/border_router/routing_manager.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/border_router/routing_manager.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/border_router/routing_manager.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/border_router/routing_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/border_router/routing_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap.o: $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap_message.o: $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap_message.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap_message.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap_message.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap_message.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap_message.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap_secure.o: $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap_secure.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap_secure.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/coap/coap_secure.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap_secure.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/coap/coap_secure.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/appender.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/appender.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/appender.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/appender.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/appender.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/appender.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/binary_search.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/binary_search.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/binary_search.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/binary_search.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/binary_search.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/binary_search.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/crc16.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/crc16.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/crc16.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/crc16.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/crc16.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/crc16.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/data.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/data.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/data.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/data.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/data.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/data.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/error.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/error.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/error.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/error.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/error.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/error.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/frame_builder.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/frame_builder.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/frame_builder.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/frame_builder.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/frame_builder.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/frame_builder.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/frame_data.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/frame_data.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/frame_data.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/frame_data.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/frame_data.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/frame_data.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/heap.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/heap.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/heap.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap_data.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/heap_data.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/heap_data.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/heap_data.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap_data.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap_data.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap_string.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/heap_string.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/heap_string.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/heap_string.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap_string.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/heap_string.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/log.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/log.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/log.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/log.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/log.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/log.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/message.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/message.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/message.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/message.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/message.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/message.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/notifier.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/notifier.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/notifier.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/notifier.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/notifier.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/notifier.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/preference.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/preference.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/preference.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/preference.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/preference.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/preference.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/random.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/random.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/random.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/random.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/random.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/random.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/settings.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/settings.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/settings.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/settings.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/settings.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/settings.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/string.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/string.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/string.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/string.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/string.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/string.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/tasklet.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/tasklet.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/tasklet.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/tasklet.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/tasklet.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/tasklet.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/time_ticker.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/time_ticker.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/time_ticker.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/time_ticker.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/time_ticker.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/time_ticker.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/timer.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/timer.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/timer.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/timer.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/timer.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/timer.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/tlvs.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/tlvs.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/tlvs.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/tlvs.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/tlvs.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/tlvs.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/trickle_timer.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/trickle_timer.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/trickle_timer.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/trickle_timer.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/trickle_timer.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/trickle_timer.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/uptime.o: $(SDK_PATH)/util/third_party/openthread/src/core/common/uptime.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/common/uptime.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/common/uptime.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/uptime.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/common/uptime.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/aes_ccm.o: $(SDK_PATH)/util/third_party/openthread/src/core/crypto/aes_ccm.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/crypto/aes_ccm.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/crypto/aes_ccm.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/aes_ccm.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/aes_ccm.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/aes_ecb.o: $(SDK_PATH)/util/third_party/openthread/src/core/crypto/aes_ecb.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/crypto/aes_ecb.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/crypto/aes_ecb.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/aes_ecb.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/aes_ecb.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/crypto_platform.o: $(SDK_PATH)/util/third_party/openthread/src/core/crypto/crypto_platform.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/crypto/crypto_platform.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/crypto/crypto_platform.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/crypto_platform.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/crypto_platform.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/hkdf_sha256.o: $(SDK_PATH)/util/third_party/openthread/src/core/crypto/hkdf_sha256.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/crypto/hkdf_sha256.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/crypto/hkdf_sha256.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/hkdf_sha256.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/hkdf_sha256.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/hmac_sha256.o: $(SDK_PATH)/util/third_party/openthread/src/core/crypto/hmac_sha256.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/crypto/hmac_sha256.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/crypto/hmac_sha256.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/hmac_sha256.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/hmac_sha256.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/mbedtls.o: $(SDK_PATH)/util/third_party/openthread/src/core/crypto/mbedtls.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/crypto/mbedtls.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/crypto/mbedtls.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/mbedtls.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/mbedtls.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/sha256.o: $(SDK_PATH)/util/third_party/openthread/src/core/crypto/sha256.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/crypto/sha256.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/crypto/sha256.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/sha256.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/sha256.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/storage.o: $(SDK_PATH)/util/third_party/openthread/src/core/crypto/storage.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/crypto/storage.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/crypto/storage.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/storage.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/crypto/storage.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/diags/factory_diags.o: $(SDK_PATH)/util/third_party/openthread/src/core/diags/factory_diags.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/diags/factory_diags.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/diags/factory_diags.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/diags/factory_diags.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/diags/factory_diags.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/instance/instance.o: $(SDK_PATH)/util/third_party/openthread/src/core/instance/instance.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/instance/instance.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/instance/instance.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/instance/instance.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/instance/instance.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/channel_mask.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/channel_mask.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/channel_mask.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/channel_mask.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/channel_mask.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/channel_mask.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/data_poll_handler.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/data_poll_handler.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/data_poll_handler.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/data_poll_handler.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/data_poll_handler.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/data_poll_handler.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/data_poll_sender.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/data_poll_sender.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/data_poll_sender.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/data_poll_sender.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/data_poll_sender.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/data_poll_sender.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/link_raw.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/link_raw.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/link_raw.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/link_raw.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/link_raw.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/link_raw.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_filter.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_filter.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_filter.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_filter.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_filter.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_filter.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_frame.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_frame.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_frame.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_frame.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_frame.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_frame.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_links.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_links.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_links.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_links.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_links.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_links.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_types.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_types.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_types.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/mac_types.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_types.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/mac_types.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/sub_mac.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/sub_mac.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/sub_mac.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/sub_mac.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/sub_mac.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/sub_mac.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/sub_mac_callbacks.o: $(SDK_PATH)/util/third_party/openthread/src/core/mac/sub_mac_callbacks.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/mac/sub_mac_callbacks.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/mac/sub_mac_callbacks.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/sub_mac_callbacks.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/mac/sub_mac_callbacks.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/announce_begin_client.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/announce_begin_client.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/announce_begin_client.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/announce_begin_client.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/announce_begin_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/announce_begin_client.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/border_agent.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/border_agent.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/border_agent.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/border_agent.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/border_agent.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/border_agent.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/commissioner.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/commissioner.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/commissioner.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/commissioner.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/commissioner.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/commissioner.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_local.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_local.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_local.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_local.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_local.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_local.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_manager.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_manager.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_manager.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_manager.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_manager_ftd.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_manager_ftd.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_manager_ftd.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_manager_ftd.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_manager_ftd.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_manager_ftd.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_updater.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_updater.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_updater.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/dataset_updater.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_updater.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/dataset_updater.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/energy_scan_client.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/energy_scan_client.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/energy_scan_client.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/energy_scan_client.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/energy_scan_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/energy_scan_client.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/extended_panid.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/extended_panid.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/extended_panid.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/extended_panid.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/extended_panid.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/extended_panid.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/joiner.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/joiner.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/joiner.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/joiner.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/joiner.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/joiner.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/joiner_router.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/joiner_router.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/joiner_router.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/joiner_router.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/joiner_router.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/joiner_router.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop_leader.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop_leader.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop_leader.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop_leader.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop_leader.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop_leader.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop_tlvs.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop_tlvs.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop_tlvs.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/meshcop_tlvs.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop_tlvs.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/meshcop_tlvs.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/network_name.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/network_name.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/network_name.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/network_name.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/network_name.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/network_name.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/panid_query_client.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/panid_query_client.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/panid_query_client.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/panid_query_client.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/panid_query_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/panid_query_client.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/secure_transport.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/secure_transport.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/secure_transport.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/secure_transport.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/secure_transport.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/secure_transport.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/tcat_agent.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/tcat_agent.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/tcat_agent.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/tcat_agent.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/tcat_agent.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/tcat_agent.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/timestamp.o: $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/timestamp.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/timestamp.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/meshcop/timestamp.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/timestamp.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/meshcop/timestamp.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/checksum.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/checksum.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/checksum.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/checksum.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/checksum.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/checksum.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dhcp6_client.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/dhcp6_client.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/dhcp6_client.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/dhcp6_client.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dhcp6_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dhcp6_client.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dhcp6_server.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/dhcp6_server.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/dhcp6_server.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/dhcp6_server.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dhcp6_server.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dhcp6_server.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_client.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_client.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_client.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_client.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_client.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_dso.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_dso.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_dso.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_dso.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_dso.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_dso.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_platform.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_platform.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_platform.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_platform.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_platform.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_platform.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_types.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_types.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_types.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/dns_types.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_types.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dns_types.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dnssd.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/dnssd.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/dnssd.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/dnssd.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dnssd.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dnssd.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dnssd_server.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/dnssd_server.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/dnssd_server.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/dnssd_server.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dnssd_server.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/dnssd_server.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/icmp6.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/icmp6.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/icmp6.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/icmp6.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/icmp6.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/icmp6.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip4_types.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/ip4_types.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/ip4_types.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/ip4_types.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip4_types.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip4_types.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_address.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_address.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_address.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_address.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_address.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_address.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_filter.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_filter.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_filter.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_filter.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_filter.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_filter.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_headers.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_headers.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_headers.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_headers.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_headers.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_headers.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_mpl.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_mpl.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_mpl.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/ip6_mpl.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_mpl.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/ip6_mpl.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/mdns.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/mdns.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/mdns.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/mdns.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/mdns.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/mdns.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nat64_translator.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/nat64_translator.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/nat64_translator.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/nat64_translator.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nat64_translator.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nat64_translator.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nd6.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/nd6.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/nd6.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/nd6.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nd6.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nd6.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nd_agent.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/nd_agent.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/nd_agent.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/nd_agent.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nd_agent.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/nd_agent.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/netif.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/netif.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/netif.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/netif.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/netif.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/netif.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/sntp_client.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/sntp_client.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/sntp_client.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/sntp_client.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/sntp_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/sntp_client.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/socket.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/socket.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/socket.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/socket.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/socket.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/socket.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_advertising_proxy.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_advertising_proxy.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_advertising_proxy.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_advertising_proxy.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_advertising_proxy.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_advertising_proxy.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_client.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_client.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_client.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_client.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_client.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_server.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_server.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_server.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/srp_server.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_server.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/srp_server.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/tcp6.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/tcp6.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/tcp6.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/tcp6.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/tcp6.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/tcp6.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/tcp6_ext.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/tcp6_ext.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/tcp6_ext.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/tcp6_ext.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/tcp6_ext.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/tcp6_ext.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/udp6.o: $(SDK_PATH)/util/third_party/openthread/src/core/net/udp6.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/net/udp6.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/net/udp6.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/udp6.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/net/udp6.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/ble_secure.o: $(SDK_PATH)/util/third_party/openthread/src/core/radio/ble_secure.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/radio/ble_secure.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/radio/ble_secure.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/ble_secure.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/ble_secure.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio.o: $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio_callbacks.o: $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio_callbacks.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio_callbacks.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio_callbacks.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio_callbacks.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio_callbacks.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio_platform.o: $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio_platform.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio_platform.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/radio/radio_platform.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio_platform.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/radio_platform.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_interface.o: $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_interface.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_interface.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_interface.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_interface.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_interface.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_link.o: $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_link.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_link.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_link.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_link.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_link.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_packet.o: $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_packet.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_packet.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/radio/trel_packet.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_packet.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/radio/trel_packet.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/address_resolver.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/address_resolver.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/address_resolver.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/address_resolver.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/address_resolver.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/address_resolver.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/announce_begin_server.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/announce_begin_server.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/announce_begin_server.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/announce_begin_server.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/announce_begin_server.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/announce_begin_server.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/announce_sender.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/announce_sender.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/announce_sender.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/announce_sender.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/announce_sender.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/announce_sender.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/anycast_locator.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/anycast_locator.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/anycast_locator.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/anycast_locator.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/anycast_locator.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/anycast_locator.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/child.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/child.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/child.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child_supervision.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/child_supervision.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/child_supervision.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/child_supervision.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child_supervision.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child_supervision.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child_table.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/child_table.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/child_table.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/child_table.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child_table.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/child_table.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/csl_tx_scheduler.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/csl_tx_scheduler.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/csl_tx_scheduler.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/csl_tx_scheduler.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/csl_tx_scheduler.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/csl_tx_scheduler.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/discover_scanner.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/discover_scanner.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/discover_scanner.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/discover_scanner.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/discover_scanner.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/discover_scanner.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/dua_manager.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/dua_manager.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/dua_manager.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/dua_manager.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/dua_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/dua_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/energy_scan_server.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/energy_scan_server.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/energy_scan_server.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/energy_scan_server.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/energy_scan_server.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/energy_scan_server.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/indirect_sender.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/indirect_sender.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/indirect_sender.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/indirect_sender.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/indirect_sender.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/indirect_sender.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/key_manager.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/key_manager.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/key_manager.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/key_manager.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/key_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/key_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_metrics.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_metrics.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_metrics.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_metrics.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_metrics.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_metrics.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_metrics_types.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_metrics_types.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_metrics_types.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_metrics_types.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_metrics_types.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_metrics_types.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_quality.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_quality.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_quality.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/link_quality.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_quality.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/link_quality.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/lowpan.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/lowpan.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/lowpan.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/lowpan.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/lowpan.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/lowpan.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder_ftd.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder_ftd.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder_ftd.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder_ftd.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder_ftd.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder_ftd.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder_mtd.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder_mtd.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder_mtd.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/mesh_forwarder_mtd.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder_mtd.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mesh_forwarder_mtd.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_router.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_router.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_router.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_router.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_router.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_router.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_tlvs.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_tlvs.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_tlvs.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_tlvs.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_tlvs.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_tlvs.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_types.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_types.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_types.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/mle_types.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_types.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mle_types.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mlr_manager.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/mlr_manager.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/mlr_manager.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/mlr_manager.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mlr_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/mlr_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/neighbor.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/neighbor.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/neighbor.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/neighbor.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/neighbor.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/neighbor.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/neighbor_table.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/neighbor_table.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/neighbor_table.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/neighbor_table.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/neighbor_table.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/neighbor_table.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_leader.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_leader.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_leader.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_leader.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_leader.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_leader.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_leader_ftd.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_leader_ftd.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_leader_ftd.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_leader_ftd.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_leader_ftd.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_leader_ftd.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_local.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_local.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_local.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_local.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_local.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_local.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_notifier.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_notifier.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_notifier.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_notifier.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_notifier.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_notifier.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_publisher.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_publisher.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_publisher.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_publisher.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_publisher.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_publisher.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_service.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_service.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_service.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_service.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_service.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_service.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_tlvs.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_tlvs.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_tlvs.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_tlvs.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_tlvs.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_tlvs.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_types.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_types.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_types.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_data_types.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_types.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_data_types.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_diagnostic.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_diagnostic.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_diagnostic.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_diagnostic.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_diagnostic.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_diagnostic.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_diagnostic_tlvs.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_diagnostic_tlvs.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_diagnostic_tlvs.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/network_diagnostic_tlvs.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_diagnostic_tlvs.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/network_diagnostic_tlvs.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/panid_query_server.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/panid_query_server.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/panid_query_server.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/panid_query_server.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/panid_query_server.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/panid_query_server.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/radio_selector.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/radio_selector.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/radio_selector.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/radio_selector.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/radio_selector.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/radio_selector.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/router.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/router.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/router.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/router.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/router.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/router.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/router_table.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/router_table.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/router_table.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/router_table.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/router_table.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/router_table.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/src_match_controller.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/src_match_controller.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/src_match_controller.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/src_match_controller.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/src_match_controller.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/src_match_controller.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/thread_netif.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/thread_netif.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/thread_netif.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/thread_netif.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/thread_netif.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/thread_netif.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/time_sync_service.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/time_sync_service.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/time_sync_service.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/time_sync_service.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/time_sync_service.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/time_sync_service.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/tmf.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/tmf.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/tmf.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/tmf.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/tmf.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/tmf.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/uri_paths.o: $(SDK_PATH)/util/third_party/openthread/src/core/thread/uri_paths.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/thread/uri_paths.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/thread/uri_paths.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/uri_paths.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/thread/uri_paths.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/channel_manager.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/channel_manager.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/channel_manager.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/channel_manager.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/channel_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/channel_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/channel_monitor.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/channel_monitor.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/channel_monitor.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/channel_monitor.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/channel_monitor.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/channel_monitor.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/flash.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/flash.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/flash.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/flash.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/flash.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/flash.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/heap.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/heap.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/heap.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/heap.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/heap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/heap.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/history_tracker.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/history_tracker.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/history_tracker.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/history_tracker.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/history_tracker.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/history_tracker.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/jam_detector.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/jam_detector.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/jam_detector.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/jam_detector.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/jam_detector.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/jam_detector.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/link_metrics_manager.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/link_metrics_manager.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/link_metrics_manager.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/link_metrics_manager.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/link_metrics_manager.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/link_metrics_manager.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/mesh_diag.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/mesh_diag.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/mesh_diag.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/mesh_diag.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/mesh_diag.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/mesh_diag.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/otns.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/otns.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/otns.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/otns.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/otns.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/otns.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/parse_cmdline.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/parse_cmdline.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/parse_cmdline.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/parse_cmdline.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/parse_cmdline.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/parse_cmdline.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/ping_sender.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/ping_sender.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/ping_sender.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/ping_sender.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/ping_sender.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/ping_sender.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/power_calibration.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/power_calibration.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/power_calibration.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/power_calibration.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/power_calibration.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/power_calibration.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/slaac_address.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/slaac_address.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/slaac_address.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/slaac_address.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/slaac_address.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/slaac_address.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/srp_client_buffers.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/srp_client_buffers.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/srp_client_buffers.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/srp_client_buffers.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/srp_client_buffers.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/srp_client_buffers.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/verhoeff_checksum.o: $(SDK_PATH)/util/third_party/openthread/src/core/utils/verhoeff_checksum.cpp
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/src/core/utils/verhoeff_checksum.cpp'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CXX) $(CXXFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/src/core/utils/verhoeff_checksum.cpp
CXXDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/verhoeff_checksum.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/src/core/utils/verhoeff_checksum.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/cc/cc_newreno.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/cc/cc_newreno.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/cc/cc_newreno.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/cc/cc_newreno.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/cc/cc_newreno.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/cc/cc_newreno.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_fastopen.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_fastopen.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_fastopen.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_fastopen.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_fastopen.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_fastopen.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_input.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_input.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_input.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_input.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_input.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_input.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_output.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_output.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_output.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_output.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_output.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_output.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_reass.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_reass.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_reass.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_reass.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_reass.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_reass.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_sack.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_sack.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_sack.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_sack.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_sack.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_sack.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_subr.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_subr.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_subr.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_subr.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_subr.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_subr.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timer.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timer.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timer.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timewait.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timewait.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timewait.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timewait.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timewait.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_timewait.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_usrreq.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_usrreq.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_usrreq.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_usrreq.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_usrreq.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/bsdtcp/tcp_usrreq.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/bitmap.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/bitmap.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/bitmap.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/bitmap.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/bitmap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/bitmap.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/cbuf.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/cbuf.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/cbuf.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/cbuf.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/cbuf.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/cbuf.o

$(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/lbuf.o: $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/lbuf.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/lbuf.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/openthread/third_party/tcplp/lib/lbuf.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/lbuf.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/openthread/third_party/tcplp/lib/lbuf.o

$(OUTPUT_DIR)/sdk/util/third_party/segger/systemview/SEGGER/SEGGER_RTT.o: $(SDK_PATH)/util/third_party/segger/systemview/SEGGER/SEGGER_RTT.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/segger/systemview/SEGGER/SEGGER_RTT.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/segger/systemview/SEGGER/SEGGER_RTT.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/segger/systemview/SEGGER/SEGGER_RTT.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/segger/systemview/SEGGER/SEGGER_RTT.o

$(OUTPUT_DIR)/project/autogen/gatt_db.o: autogen/gatt_db.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/gatt_db.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/gatt_db.c
CDEPS += $(OUTPUT_DIR)/project/autogen/gatt_db.d
OBJS += $(OUTPUT_DIR)/project/autogen/gatt_db.o

$(OUTPUT_DIR)/project/autogen/sl_bluetooth.o: autogen/sl_bluetooth.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_bluetooth.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_bluetooth.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_bluetooth.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_bluetooth.o

$(OUTPUT_DIR)/project/autogen/sl_board_default_init.o: autogen/sl_board_default_init.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_board_default_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_board_default_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_board_default_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_board_default_init.o

$(OUTPUT_DIR)/project/autogen/sl_event_handler.o: autogen/sl_event_handler.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_event_handler.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_event_handler.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_event_handler.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_event_handler.o

$(OUTPUT_DIR)/project/autogen/sl_iostream_handles.o: autogen/sl_iostream_handles.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_iostream_handles.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_iostream_handles.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_iostream_handles.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_iostream_handles.o

$(OUTPUT_DIR)/project/autogen/sl_ot_custom_cli.o: autogen/sl_ot_custom_cli.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_ot_custom_cli.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_ot_custom_cli.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_ot_custom_cli.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_ot_custom_cli.o

$(OUTPUT_DIR)/project/autogen/sl_ot_init.o: autogen/sl_ot_init.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_ot_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_ot_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_ot_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_ot_init.o

$(OUTPUT_DIR)/project/autogen/sl_simple_button_instances.o: autogen/sl_simple_button_instances.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_simple_button_instances.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_simple_button_instances.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_simple_button_instances.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_simple_button_instances.o

$(OUTPUT_DIR)/project/autogen/sl_uartdrv_init.o: autogen/sl_uartdrv_init.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_uartdrv_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_uartdrv_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_uartdrv_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_uartdrv_init.o

# Automatically-generated Simplicity Studio Metadata
# Please do not edit or delete these lines!
# SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA
# END OF METADATA