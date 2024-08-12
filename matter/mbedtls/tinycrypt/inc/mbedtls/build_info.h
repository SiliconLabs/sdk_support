
#ifndef MBEDTLS_BUILD_INFO_H
#define MBEDTLS_BUILD_INFO_H

// Custom file added to provide the necessary headers for the generated
// sl_mbedtls_config header. File keeps the previous logic by only including
// check_config without needing to modfy the generated files.

#if defined(MBEDTLS_USER_CONFIG_FILE)
#include MBEDTLS_USER_CONFIG_FILE
#endif

#include <mbedtls/check_config.h>

#endif /* MBEDTLS_BUILD_INFO_H */
