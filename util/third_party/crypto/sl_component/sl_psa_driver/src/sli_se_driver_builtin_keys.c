#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)

#include <psa/crypto.h>
#include "mbedtls/platform.h"
#include "sli_se_opaque_types.h"
#include "sl_se_manager_internal_keys.h"

#if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)

static psa_status_t set_builtin_key_context(
  uint8_t key_id,
  psa_key_attributes_t *attributes,
  uint8_t **p_key_buffer,
  size_t *key_buffer_size)
{
  sli_se_opaque_key_context_header_t* header =
    mbedtls_calloc(1, sizeof(sli_se_opaque_key_context_header_t) );
  if ( header == NULL ) {
    return(PSA_ERROR_INSUFFICIENT_MEMORY);
  }

  // Set key type and permissions according to key ID
  switch ( key_id ) {
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case SL_SE_KEY_SLOT_APPLICATION_ATTESTATION_KEY:
      psa_set_key_bits(attributes, 256);
      psa_set_key_type(attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1) );
      psa_set_key_usage_flags(attributes, PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH);
      psa_set_key_algorithm(attributes, PSA_ALG_ECDSA_ANY);
      break;
    case SL_SE_KEY_SLOT_SE_ATTESTATION_KEY:
      psa_set_key_bits(attributes, 256);
      psa_set_key_type(attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1) );
      psa_set_key_usage_flags(attributes, PSA_KEY_USAGE_VERIFY_HASH);
      psa_set_key_algorithm(attributes, PSA_ALG_ECDSA_ANY);
      break;
#endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
    case SL_SE_KEY_SLOT_APPLICATION_SECURE_BOOT_KEY:
      psa_set_key_bits(attributes, 256);
      psa_set_key_type(attributes, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1) );
      psa_set_key_usage_flags(attributes, PSA_KEY_USAGE_VERIFY_HASH);
      psa_set_key_algorithm(attributes, PSA_ALG_ECDSA_ANY);
      break;
    case SL_SE_KEY_SLOT_APPLICATION_SECURE_DEBUG_KEY:
      psa_set_key_bits(attributes, 256);
      psa_set_key_type(attributes, PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1) );
      psa_set_key_usage_flags(attributes, PSA_KEY_USAGE_VERIFY_HASH);
      psa_set_key_algorithm(attributes, PSA_ALG_ECDSA_ANY);
      break;
    case SL_SE_KEY_SLOT_APPLICATION_AES_128_KEY:
      psa_set_key_bits(attributes, 128);
      psa_set_key_type(attributes, PSA_KEY_TYPE_AES);
      psa_set_key_usage_flags(attributes, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
      psa_set_key_algorithm(attributes, PSA_ALG_ECB_NO_PADDING);
      break;
    default:
      return(PSA_ERROR_DOES_NOT_EXIST);
  }

  *p_key_buffer = (uint8_t*)header;
  *key_buffer_size = sizeof(sli_se_opaque_key_context_header_t);

  header->struct_version = SLI_SE_OPAQUE_KEY_CONTEXT_VERSION;
  header->builtin_key_id = key_id;

  psa_set_key_lifetime(attributes,
                       PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                         PSA_KEY_PERSISTENCE_READ_ONLY,
                         PSA_KEY_LOCATION_SLI_SE_OPAQUE) );

  return(PSA_SUCCESS);
}

psa_status_t mbedtls_psa_platform_get_builtin_key(
  psa_key_attributes_t *attributes,
  uint8_t **p_key_buffer, size_t *key_buffer_size)
{
  switch ( psa_get_key_id(attributes) ) {
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case SL_SE_BUILTIN_KEY_APPLICATION_ATTESTATION_ID:
      return(set_builtin_key_context(SL_SE_KEY_SLOT_APPLICATION_ATTESTATION_KEY,
                                     attributes,
                                     p_key_buffer,
                                     key_buffer_size) );
    case SL_SE_BUILTIN_KEY_SYSTEM_ATTESTATION_ID:
      return(set_builtin_key_context(SL_SE_KEY_SLOT_SE_ATTESTATION_KEY,
                                     attributes,
                                     p_key_buffer,
                                     key_buffer_size) );
#endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
    case SL_SE_BUILTIN_KEY_SECUREBOOT_ID:
      return(set_builtin_key_context(SL_SE_KEY_SLOT_APPLICATION_SECURE_BOOT_KEY,
                                     attributes,
                                     p_key_buffer,
                                     key_buffer_size) );
    case SL_SE_BUILTIN_KEY_SECUREDEBUG_ID:
      return(set_builtin_key_context(SL_SE_KEY_SLOT_APPLICATION_SECURE_DEBUG_KEY,
                                     attributes,
                                     p_key_buffer,
                                     key_buffer_size) );
    case SL_SE_BUILTIN_KEY_AES128_ID:
      return(set_builtin_key_context(SL_SE_KEY_SLOT_APPLICATION_AES_128_KEY,
                                     attributes,
                                     p_key_buffer,
                                     key_buffer_size) );
    default:
      return(PSA_ERROR_DOES_NOT_EXIST);
  }
}

#endif /* MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS */

#endif /* SEMAILBOX_PRESENT */
