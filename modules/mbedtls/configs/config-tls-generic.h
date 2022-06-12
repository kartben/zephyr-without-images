/*
 * Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 * Copyright (c) 2017 Intel Corporation.
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Generic configuration for TLS, manageable by Kconfig.
 */

#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

/* System support */
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_MEMORY_BUFFER_ALLOC_C
#define MBEDTLS_PLATFORM_EXIT_ALT
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES

#if defined(CONFIG_MBEDTLS_HAVE_ASM)
#define MBEDTLS_HAVE_ASM
#endif

#if defined(CONFIG_MBEDTLS_HAVE_TIME_DATE)
#define MBEDTLS_HAVE_TIME
#define MBEDTLS_HAVE_TIME_DATE
#endif

#if defined(CONFIG_MBEDTLS_TEST)
#define MBEDTLS_SELF_TEST
#define MBEDTLS_DEBUG_C
#endif

/* mbedTLS feature support */

/* Supported TLS versions */
#if defined(CONFIG_MBEDTLS_TLS_VERSION_1_0)
#define MBEDTLS_SSL_PROTO_TLS1
#endif

#if defined(CONFIG_MBEDTLS_TLS_VERSION_1_1)
#define MBEDTLS_SSL_PROTO_TLS1_1
#endif

#if defined(CONFIG_MBEDTLS_TLS_VERSION_1_2)
#define MBEDTLS_SSL_PROTO_TLS1_2
#endif


#if defined(CONFIG_MBEDTLS_TLS_VERSION_1_0) || \
    defined(CONFIG_MBEDTLS_TLS_VERSION_1_1) || \
    defined(CONFIG_MBEDTLS_TLS_VERSION_1_2)

/* Modules required for TLS */
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_SSL_SRV_C
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH

#endif

#if defined(CONFIG_MBEDTLS_DTLS)
#define MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_ANTI_REPLAY
#define MBEDTLS_SSL_DTLS_HELLO_VERIFY
#define MBEDTLS_SSL_COOKIE_C
#endif

/* Supported key exchange methods */

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_PSK_MAX_LEN)
#define MBEDTLS_PSK_MAX_LEN	CONFIG_MBEDTLS_PSK_MAX_LEN
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECDSA_DETERMINISTIC)
#define MBEDTLS_ECDSA_DETERMINISTIC
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
#define MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED
#endif

/* Supported cipher modes */

#if defined(CONFIG_MBEDTLS_CIPHER_AES_ENABLED)
#define MBEDTLS_AES_C
#endif

#if defined(CONFIG_MBEDTLS_AES_ROM_TABLES)
#define MBEDTLS_AES_ROM_TABLES
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_CAMELLIA_ENABLED)
#define MBEDTLS_CAMELLIA_C
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_DES_ENABLED)
#define MBEDTLS_DES_C
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_ARC4_ENABLED)
#define MBEDTLS_ARC4_C
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_CHACHA20_ENABLED)
#define MBEDTLS_CHACHA20_C
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_BLOWFISH_ENABLED)
#define MBEDTLS_BLOWFISH_C
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_CCM_ENABLED)
#define MBEDTLS_CCM_C
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_GCM_ENABLED)
#define MBEDTLS_GCM_C
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_MODE_XTS_ENABLED)
#define MBEDTLS_CIPHER_MODE_XTS
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_MODE_CBC_ENABLED)
#define MBEDTLS_CIPHER_MODE_CBC
#endif

#if defined(CONFIG_MBEDTLS_CIPHER_MODE_CTR_ENABLED)
#define MBEDTLS_CIPHER_MODE_CTR
#endif

/* Supported elliptic curves */

#if defined(CONFIG_MBEDTLS_ECP_DP_SECP192R1_ENABLED)
#define MBEDTLS_ECP_DP_SECP192R1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_SECP224R1_ENABLED)
#define MBEDTLS_ECP_DP_SECP224R1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_SECP256R1_ENABLED)
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_SECP384R1_ENABLED)
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_SECP521R1_ENABLED)
#define MBEDTLS_ECP_DP_SECP521R1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_SECP192K1_ENABLED)
#define MBEDTLS_ECP_DP_SECP192K1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_SECP224K1_ENABLED)
#define MBEDTLS_ECP_DP_SECP224K1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_SECP256K1_ENABLED)
#define MBEDTLS_ECP_DP_SECP256K1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_BP256R1_ENABLED)
#define MBEDTLS_ECP_DP_BP256R1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_BP384R1_ENABLED)
#define MBEDTLS_ECP_DP_BP384R1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_BP512R1_ENABLED)
#define MBEDTLS_ECP_DP_BP512R1_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_CURVE25519_ENABLED)
#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_DP_CURVE448_ENABLED)
#define MBEDTLS_ECP_DP_CURVE448_ENABLED
#endif

#if defined(CONFIG_MBEDTLS_ECP_NIST_OPTIM)
#define MBEDTLS_ECP_NIST_OPTIM
#endif

/* Supported message authentication methods */

#if defined(CONFIG_MBEDTLS_MAC_MD4_ENABLED)
#define MBEDTLS_MD4_C
#endif

#if defined(CONFIG_MBEDTLS_MAC_MD5_ENABLED)
#define MBEDTLS_MD5_C
#endif

#if defined(CONFIG_MBEDTLS_MAC_SHA1_ENABLED)
#define MBEDTLS_SHA1_C
#endif

#if defined(CONFIG_MBEDTLS_MAC_SHA256_ENABLED) || \
	defined(CONFIG_MBEDTLS_HASH_SHA256_ENABLED)
#define MBEDTLS_SHA224_C
#define MBEDTLS_SHA256_C
#endif

#if defined(CONFIG_MBEDTLS_SHA256_SMALLER)
#define MBEDTLS_SHA256_SMALLER
#endif

#if defined(CONFIG_MBEDTLS_MAC_SHA384_ENABLED) || \
	defined(CONFIG_MBEDTLS_HASH_SHA384_ENABLED)
#define MBEDTLS_SHA384_C
#endif

#if defined(CONFIG_MBEDTLS_MAC_SHA512_ENABLED) || \
	defined(CONFIG_MBEDTLS_HASH_SHA512_ENABLED)
#define MBEDTLS_SHA512_C
#endif

#if defined(CONFIG_MBEDTLS_MAC_POLY1305_ENABLED)
#define MBEDTLS_POLY1305_C
#endif

#if defined(CONFIG_MBEDTLS_MAC_CMAC_ENABLED)
#define MBEDTLS_CMAC_C
#endif

/* mbedTLS modules */
#if defined(CONFIG_MBEDTLS_CTR_DRBG_ENABLED)
#define MBEDTLS_CTR_DRBG_C
#endif

#if defined(CONFIG_MBEDTLS_HMAC_DRBG_ENABLED)
#define MBEDTLS_HMAC_DRBG_C
#endif

#if defined(CONFIG_MBEDTLS_DEBUG)
#define MBEDTLS_ERROR_C
#define MBEDTLS_DEBUG_C
#define MBEDTLS_SSL_DEBUG_ALL
#define MBEDTLS_SSL_ALL_ALERT_MESSAGES
#endif

#if defined(CONFIG_MBEDTLS_MEMORY_DEBUG)
#define MBEDTLS_MEMORY_DEBUG
#endif

#if defined(CONFIG_MBEDTLS_CHACHAPOLY_AEAD_ENABLED)
#define MBEDTLS_CHACHAPOLY_C
#endif

#if defined(CONFIG_MBEDTLS_GENPRIME_ENABLED)
#define MBEDTLS_GENPRIME
#endif

#if defined(CONFIG_MBEDTLS_ENTROPY_ENABLED)
#define MBEDTLS_ENTROPY_C
#endif

#if defined(CONFIG_MBEDTLS_SSL_EXPORT_KEYS)
#define MBEDTLS_SSL_EXPORT_KEYS
#endif

#if defined(CONFIG_MBEDTLS_SSL_ALPN)
#define MBEDTLS_SSL_ALPN
#endif

#if defined(CONFIG_MBEDTLS_CIPHER)
#define MBEDTLS_CIPHER_C
#endif

#if defined(CONFIG_MBEDTLS_MD)
#define MBEDTLS_MD_C
#endif

/* Automatic dependencies */

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)
#define MBEDTLS_DHM_C
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)
#define MBEDTLS_ECDH_C
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)
#define MBEDTLS_RSA_C
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PKCS1_V21
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)
#define MBEDTLS_X509_CRT_PARSE_C
#endif

#if defined (CONFIG_MBEDTLS_PEM_CERTIFICATE_FORMAT) && \
    defined(MBEDTLS_X509_CRT_PARSE_C)
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_BASE64_C
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
#define MBEDTLS_ECDSA_C
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
#define MBEDTLS_ECJPAKE_C
#endif

#if defined(MBEDTLS_ECDH_C) || \
    defined(MBEDTLS_ECDSA_C) || \
    defined(MBEDTLS_ECJPAKE_C)
#define MBEDTLS_ECP_C
#endif

#if defined(MBEDTLS_X509_CRT_PARSE_C)
#define MBEDTLS_X509_USE_C
#endif

#if defined(MBEDTLS_X509_USE_C) || \
    defined(MBEDTLS_ECDSA_C)
#define MBEDTLS_ASN1_PARSE_C
#endif

#if defined(MBEDTLS_ECDSA_C)
#define MBEDTLS_ASN1_WRITE_C
#endif

#if defined(MBEDTLS_DHM_C) || \
    defined(MBEDTLS_ECP_C) || \
    defined(MBEDTLS_RSA_C) || \
    defined(MBEDTLS_X509_USE_C) || \
    defined(MBEDTLS_GENPRIME)
#define MBEDTLS_BIGNUM_C
#endif

#if defined(MBEDTLS_RSA_C) || \
    defined(MBEDTLS_X509_USE_C)
#define MBEDTLS_OID_C
#endif

#if defined(MBEDTLS_X509_USE_C)
#define MBEDTLS_PK_PARSE_C
#endif

#if defined(CONFIG_MBEDTLS_PK_WRITE_C)
#define MBEDTLS_PK_WRITE_C
#endif

#if defined(MBEDTLS_PK_PARSE_C) || defined(MBEDTLS_PK_WRITE_C)
#define MBEDTLS_PK_C
#endif

#if defined(CONFIG_MBEDTLS_PKCS5_C)
#define MBEDTLS_PKCS5_C
#endif

#define MBEDTLS_SSL_IN_CONTENT_LEN  CONFIG_MBEDTLS_SSL_MAX_CONTENT_LEN
#define MBEDTLS_SSL_OUT_CONTENT_LEN  CONFIG_MBEDTLS_SSL_MAX_CONTENT_LEN

/* Enable OpenThread optimizations. */
#if defined(CONFIG_MBEDTLS_OPENTHREAD_OPTIMIZATIONS_ENABLED)
#define MBEDTLS_MPI_WINDOW_SIZE            1 /**< Maximum windows size used. */
#define MBEDTLS_MPI_MAX_SIZE              32 /**< Maximum number of bytes for usable MPIs. */
#define MBEDTLS_ECP_WINDOW_SIZE            2 /**< Maximum window size used */
#define MBEDTLS_ECP_FIXED_POINT_OPTIM      0 /**< Enable fixed-point speed-up */
#define MBEDTLS_ENTROPY_MAX_SOURCES        1 /**< Maximum number of sources supported */
#endif

#if defined(CONFIG_MBEDTLS_SERVER_NAME_INDICATION) && \
    defined(MBEDTLS_X509_CRT_PARSE_C)
#define MBEDTLS_SSL_SERVER_NAME_INDICATION
#endif

#if defined(CONFIG_MBEDTLS_SSL_CACHE_C)
#define MBEDTLS_SSL_CACHE_C
#define MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT CONFIG_MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT
#define MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES CONFIG_MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES
#endif

#if defined(CONFIG_MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
#define MBEDTLS_SSL_EXTENDED_MASTER_SECRET
#endif

/* User config file */

#if defined(CONFIG_MBEDTLS_USER_CONFIG_FILE)
#include CONFIG_MBEDTLS_USER_CONFIG_FILE
#endif

#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */
