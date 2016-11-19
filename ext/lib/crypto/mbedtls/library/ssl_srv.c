/*
 *  SSLv3/TLSv1 server-side functions
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_SSL_SRV_C)

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#define mbedtls_calloc    calloc
#define mbedtls_free      free
#endif

#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/ssl_internal.h"

#include <string.h>

#if defined(MBEDTLS_ECP_C)
#include "mbedtls/ecp.h"
#endif

#if defined(MBEDTLS_HAVE_TIME)
#include "mbedtls/platform_time.h"
#endif

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
/* Implementation that should never be optimized out by the compiler */
static void mbedtls_zeroize( void *v, size_t n ) {
    volatile unsigned char *p = v; while( n-- ) *p++ = 0;
}
#endif

#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY)
int mbedtls_ssl_set_client_transport_id( mbedtls_ssl_context *ssl,
                                 const unsigned char *info,
                                 size_t ilen )
{
    if( ssl->conf->endpoint != MBEDTLS_SSL_IS_SERVER )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    mbedtls_free( ssl->cli_id );

    if( ( ssl->cli_id = mbedtls_calloc( 1, ilen ) ) == NULL )
        return( MBEDTLS_ERR_SSL_ALLOC_FAILED );

    memcpy( ssl->cli_id, info, ilen );
    ssl->cli_id_len = ilen;

    return( 0 );
}

void mbedtls_ssl_conf_dtls_cookies( mbedtls_ssl_config *conf,
                           mbedtls_ssl_cookie_write_t *f_cookie_write,
                           mbedtls_ssl_cookie_check_t *f_cookie_check,
                           void *p_cookie )
{
    conf->f_cookie_write = f_cookie_write;
    conf->f_cookie_check = f_cookie_check;
    conf->p_cookie       = p_cookie;
}
#endif /* MBEDTLS_SSL_DTLS_HELLO_VERIFY */

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
static int ssl_parse_servername_ext( mbedtls_ssl_context *ssl,
                                     const unsigned char *buf,
                                     size_t len )
{
    int ret;
    size_t servername_list_size, hostname_len;
    const unsigned char *p;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "parse ServerName extension" ) );

    servername_list_size = ( ( buf[0] << 8 ) | ( buf[1] ) );
    if( servername_list_size + 2 != len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    p = buf + 2;
    while( servername_list_size > 0 )
    {
        hostname_len = ( ( p[1] << 8 ) | p[2] );
        if( hostname_len + 3 > servername_list_size )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
        }

        if( p[0] == MBEDTLS_TLS_EXT_SERVERNAME_HOSTNAME )
        {
            ret = ssl->conf->f_sni( ssl->conf->p_sni,
                                    ssl, p + 3, hostname_len );
            if( ret != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "ssl_sni_wrapper", ret );
                mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                        MBEDTLS_SSL_ALERT_MSG_UNRECOGNIZED_NAME );
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }
            return( 0 );
        }

        servername_list_size -= hostname_len + 3;
        p += hostname_len + 3;
    }

    if( servername_list_size != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    return( 0 );
}
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */

static int ssl_parse_renegotiation_info( mbedtls_ssl_context *ssl,
                                         const unsigned char *buf,
                                         size_t len )
{
    int ret;

#if defined(MBEDTLS_SSL_RENEGOTIATION)
    if( ssl->renego_status != MBEDTLS_SSL_INITIAL_HANDSHAKE )
    {
        /* Check verify-data in constant-time. The length OTOH is no secret */
        if( len    != 1 + ssl->verify_data_len ||
            buf[0] !=     ssl->verify_data_len ||
            mbedtls_ssl_safer_memcmp( buf + 1, ssl->peer_verify_data,
                          ssl->verify_data_len ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "non-matching renegotiation info" ) );

            if( ( ret = mbedtls_ssl_send_fatal_handshake_failure( ssl ) ) != 0 )
                return( ret );

            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
        }
    }
    else
#endif /* MBEDTLS_SSL_RENEGOTIATION */
    {
        if( len != 1 || buf[0] != 0x0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "non-zero length renegotiation info" ) );

            if( ( ret = mbedtls_ssl_send_fatal_handshake_failure( ssl ) ) != 0 )
                return( ret );

            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
        }

        ssl->secure_renegotiation = MBEDTLS_SSL_SECURE_RENEGOTIATION;
    }

    return( 0 );
}

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
static int ssl_parse_signature_algorithms_ext( mbedtls_ssl_context *ssl,
                                               const unsigned char *buf,
                                               size_t len )
{
    size_t sig_alg_list_size;
    const unsigned char *p;
    const unsigned char *end = buf + len;
    const int *md_cur;


    sig_alg_list_size = ( ( buf[0] << 8 ) | ( buf[1] ) );
    if( sig_alg_list_size + 2 != len ||
        sig_alg_list_size % 2 != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    /*
     * For now, ignore the SignatureAlgorithm part and rely on offered
     * ciphersuites only for that part. To be fixed later.
     *
     * So, just look at the HashAlgorithm part.
     */
    for( md_cur = ssl->conf->sig_hashes; *md_cur != MBEDTLS_MD_NONE; md_cur++ ) {
        for( p = buf + 2; p < end; p += 2 ) {
            if( *md_cur == (int) mbedtls_ssl_md_alg_from_hash( p[0] ) ) {
                ssl->handshake->sig_alg = p[0];
                goto have_sig_alg;
            }
        }
    }

    /* Some key echanges do not need signatures at all */
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "no signature_algorithm in common" ) );
    return( 0 );

have_sig_alg:
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, signature_algorithm ext: %d",
                   ssl->handshake->sig_alg ) );

    return( 0 );
}
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 &&
          MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED */

#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
static int ssl_parse_supported_elliptic_curves( mbedtls_ssl_context *ssl,
                                                const unsigned char *buf,
                                                size_t len )
{
    size_t list_size, our_size;
    const unsigned char *p;
    const mbedtls_ecp_curve_info *curve_info, **curves;

    list_size = ( ( buf[0] << 8 ) | ( buf[1] ) );
    if( list_size + 2 != len ||
        list_size % 2 != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    /* Should never happen unless client duplicates the extension */
    if( ssl->handshake->curves != NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    /* Don't allow our peer to make us allocate too much memory,
     * and leave room for a final 0 */
    our_size = list_size / 2 + 1;
    if( our_size > MBEDTLS_ECP_DP_MAX )
        our_size = MBEDTLS_ECP_DP_MAX;

    if( ( curves = mbedtls_calloc( our_size, sizeof( *curves ) ) ) == NULL )
        return( MBEDTLS_ERR_SSL_ALLOC_FAILED );

    ssl->handshake->curves = curves;

    p = buf + 2;
    while( list_size > 0 && our_size > 1 )
    {
        curve_info = mbedtls_ecp_curve_info_from_tls_id( ( p[0] << 8 ) | p[1] );

        if( curve_info != NULL )
        {
            *curves++ = curve_info;
            our_size--;
        }

        list_size -= 2;
        p += 2;
    }

    return( 0 );
}

static int ssl_parse_supported_point_formats( mbedtls_ssl_context *ssl,
                                              const unsigned char *buf,
                                              size_t len )
{
    size_t list_size;
    const unsigned char *p;

    list_size = buf[0];
    if( list_size + 1 != len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    p = buf + 1;
    while( list_size > 0 )
    {
        if( p[0] == MBEDTLS_ECP_PF_UNCOMPRESSED ||
            p[0] == MBEDTLS_ECP_PF_COMPRESSED )
        {
#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C)
            ssl->handshake->ecdh_ctx.point_format = p[0];
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
            ssl->handshake->ecjpake_ctx.point_format = p[0];
#endif
            MBEDTLS_SSL_DEBUG_MSG( 4, ( "point format selected: %d", p[0] ) );
            return( 0 );
        }

        list_size--;
        p++;
    }

    return( 0 );
}
#endif /* MBEDTLS_ECDH_C || MBEDTLS_ECDSA_C ||
          MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
static int ssl_parse_ecjpake_kkpp( mbedtls_ssl_context *ssl,
                                   const unsigned char *buf,
                                   size_t len )
{
    int ret;

    if( mbedtls_ecjpake_check( &ssl->handshake->ecjpake_ctx ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "skip ecjpake kkpp extension" ) );
        return( 0 );
    }

    if( ( ret = mbedtls_ecjpake_read_round_one( &ssl->handshake->ecjpake_ctx,
                                                buf, len ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_read_round_one", ret );
        return( ret );
    }

    /* Only mark the extension as OK when we're sure it is */
    ssl->handshake->cli_exts |= MBEDTLS_TLS_EXT_ECJPAKE_KKPP_OK;

    return( 0 );
}
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
static int ssl_parse_max_fragment_length_ext( mbedtls_ssl_context *ssl,
                                              const unsigned char *buf,
                                              size_t len )
{
    if( len != 1 || buf[0] >= MBEDTLS_SSL_MAX_FRAG_LEN_INVALID )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    ssl->session_negotiate->mfl_code = buf[0];

    return( 0 );
}
#endif /* MBEDTLS_SSL_MAX_FRAGMENT_LENGTH */

#if defined(MBEDTLS_SSL_TRUNCATED_HMAC)
static int ssl_parse_truncated_hmac_ext( mbedtls_ssl_context *ssl,
                                         const unsigned char *buf,
                                         size_t len )
{
    if( len != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    ((void) buf);

    if( ssl->conf->trunc_hmac == MBEDTLS_SSL_TRUNC_HMAC_ENABLED )
        ssl->session_negotiate->trunc_hmac = MBEDTLS_SSL_TRUNC_HMAC_ENABLED;

    return( 0 );
}
#endif /* MBEDTLS_SSL_TRUNCATED_HMAC */

#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
static int ssl_parse_encrypt_then_mac_ext( mbedtls_ssl_context *ssl,
                                      const unsigned char *buf,
                                      size_t len )
{
    if( len != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    ((void) buf);

    if( ssl->conf->encrypt_then_mac == MBEDTLS_SSL_ETM_ENABLED &&
        ssl->minor_ver != MBEDTLS_SSL_MINOR_VERSION_0 )
    {
        ssl->session_negotiate->encrypt_then_mac = MBEDTLS_SSL_ETM_ENABLED;
    }

    return( 0 );
}
#endif /* MBEDTLS_SSL_ENCRYPT_THEN_MAC */

#if defined(MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
static int ssl_parse_extended_ms_ext( mbedtls_ssl_context *ssl,
                                      const unsigned char *buf,
                                      size_t len )
{
    if( len != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    ((void) buf);

    if( ssl->conf->extended_ms == MBEDTLS_SSL_EXTENDED_MS_ENABLED &&
        ssl->minor_ver != MBEDTLS_SSL_MINOR_VERSION_0 )
    {
        ssl->handshake->extended_ms = MBEDTLS_SSL_EXTENDED_MS_ENABLED;
    }

    return( 0 );
}
#endif /* MBEDTLS_SSL_EXTENDED_MASTER_SECRET */

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
static int ssl_parse_session_ticket_ext( mbedtls_ssl_context *ssl,
                                         unsigned char *buf,
                                         size_t len )
{
    int ret;
    mbedtls_ssl_session session;

    mbedtls_ssl_session_init( &session );

    if( ssl->conf->f_ticket_parse == NULL ||
        ssl->conf->f_ticket_write == NULL )
    {
        return( 0 );
    }

    /* Remember the client asked us to send a new ticket */
    ssl->handshake->new_session_ticket = 1;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "ticket length: %d", len ) );

    if( len == 0 )
        return( 0 );

#if defined(MBEDTLS_SSL_RENEGOTIATION)
    if( ssl->renego_status != MBEDTLS_SSL_INITIAL_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ticket rejected: renegotiating" ) );
        return( 0 );
    }
#endif /* MBEDTLS_SSL_RENEGOTIATION */

    /*
     * Failures are ok: just ignore the ticket and proceed.
     */
    if( ( ret = ssl->conf->f_ticket_parse( ssl->conf->p_ticket, &session,
                                           buf, len ) ) != 0 )
    {
        mbedtls_ssl_session_free( &session );

        if( ret == MBEDTLS_ERR_SSL_INVALID_MAC )
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "ticket is not authentic" ) );
        else if( ret == MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED )
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "ticket is expired" ) );
        else
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_ticket_parse", ret );

        return( 0 );
    }

    /*
     * Keep the session ID sent by the client, since we MUST send it back to
     * inform them we're accepting the ticket  (RFC 5077 section 3.4)
     */
    session.id_len = ssl->session_negotiate->id_len;
    memcpy( &session.id, ssl->session_negotiate->id, session.id_len );

    mbedtls_ssl_session_free( ssl->session_negotiate );
    memcpy( ssl->session_negotiate, &session, sizeof( mbedtls_ssl_session ) );

    /* Zeroize instead of free as we copied the content */
    mbedtls_zeroize( &session, sizeof( mbedtls_ssl_session ) );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "session successfully restored from ticket" ) );

    ssl->handshake->resume = 1;

    /* Don't send a new ticket after all, this one is OK */
    ssl->handshake->new_session_ticket = 0;

    return( 0 );
}
#endif /* MBEDTLS_SSL_SESSION_TICKETS */

#if defined(MBEDTLS_SSL_ALPN)
static int ssl_parse_alpn_ext( mbedtls_ssl_context *ssl,
                               const unsigned char *buf, size_t len )
{
    size_t list_len, cur_len, ours_len;
    const unsigned char *theirs, *start, *end;
    const char **ours;

    /* If ALPN not configured, just ignore the extension */
    if( ssl->conf->alpn_list == NULL )
        return( 0 );

    /*
     * opaque ProtocolName<1..2^8-1>;
     *
     * struct {
     *     ProtocolName protocol_name_list<2..2^16-1>
     * } ProtocolNameList;
     */

    /* Min length is 2 (list_len) + 1 (name_len) + 1 (name) */
    if( len < 4 )
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );

    list_len = ( buf[0] << 8 ) | buf[1];
    if( list_len != len - 2 )
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );

    /*
     * Use our order of preference
     */
    start = buf + 2;
    end = buf + len;
    for( ours = ssl->conf->alpn_list; *ours != NULL; ours++ )
    {
        ours_len = strlen( *ours );
        for( theirs = start; theirs != end; theirs += cur_len )
        {
            /* If the list is well formed, we should get equality first */
            if( theirs > end )
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );

            cur_len = *theirs++;

            /* Empty strings MUST NOT be included */
            if( cur_len == 0 )
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );

            if( cur_len == ours_len &&
                memcmp( theirs, *ours, cur_len ) == 0 )
            {
                ssl->alpn_chosen = *ours;
                return( 0 );
            }
        }
    }

    /* If we get there, no match was found */
    mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                            MBEDTLS_SSL_ALERT_MSG_NO_APPLICATION_PROTOCOL );
    return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
}
#endif /* MBEDTLS_SSL_ALPN */

/*
 * Auxiliary functions for ServerHello parsing and related actions
 */

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/*
 * Return 0 if the given key uses one of the acceptable curves, -1 otherwise
 */
#if defined(MBEDTLS_ECDSA_C)
static int ssl_check_key_curve( mbedtls_pk_context *pk,
                                const mbedtls_ecp_curve_info **curves )
{
    const mbedtls_ecp_curve_info **crv = curves;
    mbedtls_ecp_group_id grp_id = mbedtls_pk_ec( *pk )->grp.id;

    while( *crv != NULL )
    {
        if( (*crv)->grp_id == grp_id )
            return( 0 );
        crv++;
    }

    return( -1 );
}
#endif /* MBEDTLS_ECDSA_C */

/*
 * Try picking a certificate for this ciphersuite,
 * return 0 on success and -1 on failure.
 */
static int ssl_pick_cert( mbedtls_ssl_context *ssl,
                          const mbedtls_ssl_ciphersuite_t * ciphersuite_info )
{
    mbedtls_ssl_key_cert *cur, *list, *fallback = NULL;
    mbedtls_pk_type_t pk_alg = mbedtls_ssl_get_ciphersuite_sig_pk_alg( ciphersuite_info );
    uint32_t flags;

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    if( ssl->handshake->sni_key_cert != NULL )
        list = ssl->handshake->sni_key_cert;
    else
#endif
        list = ssl->conf->key_cert;

    if( pk_alg == MBEDTLS_PK_NONE )
        return( 0 );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite requires certificate" ) );

    if( list == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "server has no certificate" ) );
        return( -1 );
    }

    for( cur = list; cur != NULL; cur = cur->next )
    {
        MBEDTLS_SSL_DEBUG_CRT( 3, "candidate certificate chain, certificate",
                          cur->cert );

        if( ! mbedtls_pk_can_do( cur->key, pk_alg ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: key type" ) );
            continue;
        }

        /*
         * This avoids sending the client a cert it'll reject based on
         * keyUsage or other extensions.
         *
         * It also allows the user to provision different certificates for
         * different uses based on keyUsage, eg if they want to avoid signing
         * and decrypting with the same RSA key.
         */
        if( mbedtls_ssl_check_cert_usage( cur->cert, ciphersuite_info,
                                  MBEDTLS_SSL_IS_SERVER, &flags ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: "
                                "(extended) key usage extension" ) );
            continue;
        }

#if defined(MBEDTLS_ECDSA_C)
        if( pk_alg == MBEDTLS_PK_ECDSA &&
            ssl_check_key_curve( cur->key, ssl->handshake->curves ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: elliptic curve" ) );
            continue;
        }
#endif

        /*
         * Try to select a SHA-1 certificate for pre-1.2 clients, but still
         * present them a SHA-higher cert rather than failing if it's the only
         * one we got that satisfies the other conditions.
         */
        if( ssl->minor_ver < MBEDTLS_SSL_MINOR_VERSION_3 &&
            cur->cert->sig_md != MBEDTLS_MD_SHA1 )
        {
            if( fallback == NULL )
                fallback = cur;
            {
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate not preferred: "
                                    "sha-2 with pre-TLS 1.2 client" ) );
            continue;
            }
        }

        /* If we get there, we got a winner */
        break;
    }

    if( cur == NULL )
        cur = fallback;

    /* Do not update ssl->handshake->key_cert unless there is a match */
    if( cur != NULL )
    {
        ssl->handshake->key_cert = cur;
        MBEDTLS_SSL_DEBUG_CRT( 3, "selected certificate chain, certificate",
                          ssl->handshake->key_cert->cert );
        return( 0 );
    }

    return( -1 );
}
#endif /* MBEDTLS_X509_CRT_PARSE_C */

/*
 * Check if a given ciphersuite is suitable for use with our config/keys/etc
 * Sets ciphersuite_info only if the suite matches.
 */
static int ssl_ciphersuite_match( mbedtls_ssl_context *ssl, int suite_id,
                                  const mbedtls_ssl_ciphersuite_t **ciphersuite_info )
{
    const mbedtls_ssl_ciphersuite_t *suite_info;

    suite_info = mbedtls_ssl_ciphersuite_from_id( suite_id );
    if( suite_info == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "trying ciphersuite: %s", suite_info->name ) );

    if( suite_info->min_minor_ver > ssl->minor_ver ||
        suite_info->max_minor_ver < ssl->minor_ver )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: version" ) );
        return( 0 );
    }

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ( suite_info->flags & MBEDTLS_CIPHERSUITE_NODTLS ) )
        return( 0 );
#endif

#if defined(MBEDTLS_ARC4_C)
    if( ssl->conf->arc4_disabled == MBEDTLS_SSL_ARC4_DISABLED &&
            suite_info->cipher == MBEDTLS_CIPHER_ARC4_128 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: rc4" ) );
        return( 0 );
    }
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    if( suite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE &&
        ( ssl->handshake->cli_exts & MBEDTLS_TLS_EXT_ECJPAKE_KKPP_OK ) == 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: ecjpake "
                                    "not configured or ext missing" ) );
        return( 0 );
    }
#endif


#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C)
    if( mbedtls_ssl_ciphersuite_uses_ec( suite_info ) &&
        ( ssl->handshake->curves == NULL ||
          ssl->handshake->curves[0] == NULL ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: "
                            "no common elliptic curve" ) );
        return( 0 );
    }
#endif

#if defined(MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
    /* If the ciphersuite requires a pre-shared key and we don't
     * have one, skip it now rather than failing later */
    if( mbedtls_ssl_ciphersuite_uses_psk( suite_info ) &&
        ssl->conf->f_psk == NULL &&
        ( ssl->conf->psk == NULL || ssl->conf->psk_identity == NULL ||
          ssl->conf->psk_identity_len == 0 || ssl->conf->psk_len == 0 ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: no pre-shared key" ) );
        return( 0 );
    }
#endif

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    /*
     * Final check: if ciphersuite requires us to have a
     * certificate/key of a particular type:
     * - select the appropriate certificate if we have one, or
     * - try the next ciphersuite if we don't
     * This must be done last since we modify the key_cert list.
     */
    if( ssl_pick_cert( ssl, suite_info ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: "
                            "no suitable certificate" ) );
        return( 0 );
    }
#endif

    *ciphersuite_info = suite_info;
    return( 0 );
}

#if defined(MBEDTLS_SSL_SRV_SUPPORT_SSLV2_CLIENT_HELLO)
static int ssl_parse_client_hello_v2( mbedtls_ssl_context *ssl )
{
    int ret, got_common_suite;
    unsigned int i, j;
    size_t n;
    unsigned int ciph_len, sess_len, chal_len;
    unsigned char *buf, *p;
    const int *ciphersuites;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse client hello v2" ) );

#if defined(MBEDTLS_SSL_RENEGOTIATION)
    if( ssl->renego_status != MBEDTLS_SSL_INITIAL_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "client hello v2 illegal for renegotiation" ) );

        if( ( ret = mbedtls_ssl_send_fatal_handshake_failure( ssl ) ) != 0 )
            return( ret );

        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }
#endif /* MBEDTLS_SSL_RENEGOTIATION */

    buf = ssl->in_hdr;

    MBEDTLS_SSL_DEBUG_BUF( 4, "record header", buf, 5 );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v2, message type: %d",
                   buf[2] ) );
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v2, message len.: %d",
                   ( ( buf[0] & 0x7F ) << 8 ) | buf[1] ) );
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v2, max. version: [%d:%d]",
                   buf[3], buf[4] ) );

    /*
     * SSLv2 Client Hello
     *
     * Record layer:
     *     0  .   1   message length
     *
     * SSL layer:
     *     2  .   2   message type
     *     3  .   4   protocol version
     */
    if( buf[2] != MBEDTLS_SSL_HS_CLIENT_HELLO ||
        buf[3] != MBEDTLS_SSL_MAJOR_VERSION_3 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    n = ( ( buf[0] << 8 ) | buf[1] ) & 0x7FFF;

    if( n < 17 || n > 512 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    ssl->major_ver = MBEDTLS_SSL_MAJOR_VERSION_3;
    ssl->minor_ver = ( buf[4] <= ssl->conf->max_minor_ver )
                     ? buf[4]  : ssl->conf->max_minor_ver;

    if( ssl->minor_ver < ssl->conf->min_minor_ver )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "client only supports ssl smaller than minimum"
                            " [%d:%d] < [%d:%d]",
                            ssl->major_ver, ssl->minor_ver,
                            ssl->conf->min_major_ver, ssl->conf->min_minor_ver ) );

        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                     MBEDTLS_SSL_ALERT_MSG_PROTOCOL_VERSION );
        return( MBEDTLS_ERR_SSL_BAD_HS_PROTOCOL_VERSION );
    }

    ssl->handshake->max_major_ver = buf[3];
    ssl->handshake->max_minor_ver = buf[4];

    if( ( ret = mbedtls_ssl_fetch_input( ssl, 2 + n ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_fetch_input", ret );
        return( ret );
    }

    ssl->handshake->update_checksum( ssl, buf + 2, n );

    buf = ssl->in_msg;
    n = ssl->in_left - 5;

    /*
     *    0  .   1   ciphersuitelist length
     *    2  .   3   session id length
     *    4  .   5   challenge length
     *    6  .  ..   ciphersuitelist
     *   ..  .  ..   session id
     *   ..  .  ..   challenge
     */
    MBEDTLS_SSL_DEBUG_BUF( 4, "record contents", buf, n );

    ciph_len = ( buf[0] << 8 ) | buf[1];
    sess_len = ( buf[2] << 8 ) | buf[3];
    chal_len = ( buf[4] << 8 ) | buf[5];

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciph_len: %d, sess_len: %d, chal_len: %d",
                   ciph_len, sess_len, chal_len ) );

    /*
     * Make sure each parameter length is valid
     */
    if( ciph_len < 3 || ( ciph_len % 3 ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    if( sess_len > 32 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    if( chal_len < 8 || chal_len > 32 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    if( n != 6 + ciph_len + sess_len + chal_len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, ciphersuitelist",
                   buf + 6, ciph_len );
    MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, session id",
                   buf + 6 + ciph_len, sess_len );
    MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, challenge",
                   buf + 6 + ciph_len + sess_len, chal_len );

    p = buf + 6 + ciph_len;
    ssl->session_negotiate->id_len = sess_len;
    memset( ssl->session_negotiate->id, 0,
            sizeof( ssl->session_negotiate->id ) );
    memcpy( ssl->session_negotiate->id, p, ssl->session_negotiate->id_len );

    p += sess_len;
    memset( ssl->handshake->randbytes, 0, 64 );
    memcpy( ssl->handshake->randbytes + 32 - chal_len, p, chal_len );

    /*
     * Check for TLS_EMPTY_RENEGOTIATION_INFO_SCSV
     */
    for( i = 0, p = buf + 6; i < ciph_len; i += 3, p += 3 )
    {
        if( p[0] == 0 && p[1] == 0 && p[2] == MBEDTLS_SSL_EMPTY_RENEGOTIATION_INFO )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "received TLS_EMPTY_RENEGOTIATION_INFO " ) );
#if defined(MBEDTLS_SSL_RENEGOTIATION)
            if( ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "received RENEGOTIATION SCSV "
                                    "during renegotiation" ) );

                if( ( ret = mbedtls_ssl_send_fatal_handshake_failure( ssl ) ) != 0 )
                    return( ret );

                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }
#endif /* MBEDTLS_SSL_RENEGOTIATION */
            ssl->secure_renegotiation = MBEDTLS_SSL_SECURE_RENEGOTIATION;
            break;
        }
    }

#if defined(MBEDTLS_SSL_FALLBACK_SCSV)
    for( i = 0, p = buf + 6; i < ciph_len; i += 3, p += 3 )
    {
        if( p[0] == 0 &&
            p[1] == (unsigned char)( ( MBEDTLS_SSL_FALLBACK_SCSV_VALUE >> 8 ) & 0xff ) &&
            p[2] == (unsigned char)( ( MBEDTLS_SSL_FALLBACK_SCSV_VALUE      ) & 0xff ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "received FALLBACK_SCSV" ) );

            if( ssl->minor_ver < ssl->conf->max_minor_ver )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "inapropriate fallback" ) );

                mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_INAPROPRIATE_FALLBACK );

                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }

            break;
        }
    }
#endif /* MBEDTLS_SSL_FALLBACK_SCSV */

    got_common_suite = 0;
    ciphersuites = ssl->conf->ciphersuite_list[ssl->minor_ver];
    ciphersuite_info = NULL;
#if defined(MBEDTLS_SSL_SRV_RESPECT_CLIENT_PREFERENCE)
    for( j = 0, p = buf + 6; j < ciph_len; j += 3, p += 3 )
    {
        for( i = 0; ciphersuites[i] != 0; i++ )
#else
    for( i = 0; ciphersuites[i] != 0; i++ )
    {
        for( j = 0, p = buf + 6; j < ciph_len; j += 3, p += 3 )
#endif
        {
            if( p[0] != 0 ||
                p[1] != ( ( ciphersuites[i] >> 8 ) & 0xFF ) ||
                p[2] != ( ( ciphersuites[i]      ) & 0xFF ) )
                continue;

            got_common_suite = 1;

            if( ( ret = ssl_ciphersuite_match( ssl, ciphersuites[i],
                                               &ciphersuite_info ) ) != 0 )
                return( ret );

            if( ciphersuite_info != NULL )
                goto have_ciphersuite_v2;
        }
    }

    if( got_common_suite )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "got ciphersuites in common, "
                            "but none of them usable" ) );
        return( MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE );
    }
    else
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "got no ciphersuites in common" ) );
        return( MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN );
    }

have_ciphersuite_v2:
    MBEDTLS_SSL_DEBUG_MSG( 2, ( "selected ciphersuite: %s", ciphersuite_info->name ) );

    ssl->session_negotiate->ciphersuite = ciphersuites[i];
    ssl->transform_negotiate->ciphersuite_info = ciphersuite_info;

    /*
     * SSLv2 Client Hello relevant renegotiation security checks
     */
    if( ssl->secure_renegotiation == MBEDTLS_SSL_LEGACY_RENEGOTIATION &&
        ssl->conf->allow_legacy_renegotiation == MBEDTLS_SSL_LEGACY_BREAK_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "legacy renegotiation, breaking off handshake" ) );

        if( ( ret = mbedtls_ssl_send_fatal_handshake_failure( ssl ) ) != 0 )
            return( ret );

        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    ssl->in_left = 0;
    ssl->state++;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse client hello v2" ) );

    return( 0 );
}
#endif /* MBEDTLS_SSL_SRV_SUPPORT_SSLV2_CLIENT_HELLO */

static int ssl_parse_client_hello( mbedtls_ssl_context *ssl )
{
    int ret, got_common_suite;
    size_t i, j;
    size_t ciph_offset, comp_offset, ext_offset;
    size_t msg_len, ciph_len, sess_len, comp_len, ext_len;
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    size_t cookie_offset, cookie_len;
#endif
    unsigned char *buf, *p, *ext;
#if defined(MBEDTLS_SSL_RENEGOTIATION)
    int renegotiation_info_seen = 0;
#endif
    int handshake_failure = 0;
    const int *ciphersuites;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info;
    int major, minor;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse client hello" ) );

#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)
read_record_header:
#endif
    /*
     * If renegotiating, then the input was read with mbedtls_ssl_read_record(),
     * otherwise read it ourselves manually in order to support SSLv2
     * ClientHello, which doesn't use the same record layer format.
     */
#if defined(MBEDTLS_SSL_RENEGOTIATION)
    if( ssl->renego_status == MBEDTLS_SSL_INITIAL_HANDSHAKE )
#endif
    {
        if( ( ret = mbedtls_ssl_fetch_input( ssl, 5 ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_fetch_input", ret );
            return( ret );
        }
    }

    buf = ssl->in_hdr;

#if defined(MBEDTLS_SSL_SRV_SUPPORT_SSLV2_CLIENT_HELLO)
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_STREAM )
#endif
        if( ( buf[0] & 0x80 ) != 0 )
            return ssl_parse_client_hello_v2( ssl );
#endif

    MBEDTLS_SSL_DEBUG_BUF( 4, "record header", buf, mbedtls_ssl_hdr_len( ssl ) );

    /*
     * SSLv3/TLS Client Hello
     *
     * Record layer:
     *     0  .   0   message type
     *     1  .   2   protocol version
     *     3  .   11  DTLS: epoch + record sequence number
     *     3  .   4   message length
     */
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, message type: %d",
                   buf[0] ) );

    if( buf[0] != MBEDTLS_SSL_MSG_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, message len.: %d",
                   ( ssl->in_len[0] << 8 ) | ssl->in_len[1] ) );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, protocol version: [%d:%d]",
                   buf[1], buf[2] ) );

    mbedtls_ssl_read_version( &major, &minor, ssl->conf->transport, buf + 1 );

    /* According to RFC 5246 Appendix E.1, the version here is typically
     * "{03,00}, the lowest version number supported by the client, [or] the
     * value of ClientHello.client_version", so the only meaningful check here
     * is the major version shouldn't be less than 3 */
    if( major < MBEDTLS_SSL_MAJOR_VERSION_3 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    /* For DTLS if this is the initial handshake, remember the client sequence
     * number to use it in our next message (RFC 6347 4.2.1) */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM
#if defined(MBEDTLS_SSL_RENEGOTIATION)
        && ssl->renego_status == MBEDTLS_SSL_INITIAL_HANDSHAKE
#endif
        )
    {
        /* Epoch should be 0 for initial handshakes */
        if( ssl->in_ctr[0] != 0 || ssl->in_ctr[1] != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
        }

        memcpy( ssl->out_ctr + 2, ssl->in_ctr + 2, 6 );

#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)
        if( mbedtls_ssl_dtls_replay_check( ssl ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "replayed record, discarding" ) );
            ssl->next_record_offset = 0;
            ssl->in_left = 0;
            goto read_record_header;
        }

        /* No MAC to check yet, so we can update right now */
        mbedtls_ssl_dtls_replay_update( ssl );
#endif
    }
#endif /* MBEDTLS_SSL_PROTO_DTLS */

    msg_len = ( ssl->in_len[0] << 8 ) | ssl->in_len[1];

#if defined(MBEDTLS_SSL_RENEGOTIATION)
    if( ssl->renego_status != MBEDTLS_SSL_INITIAL_HANDSHAKE )
    {
        /* Set by mbedtls_ssl_read_record() */
        msg_len = ssl->in_hslen;
    }
    else
#endif
    {
        if( msg_len > MBEDTLS_SSL_MAX_CONTENT_LEN )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
        }

        if( ( ret = mbedtls_ssl_fetch_input( ssl, mbedtls_ssl_hdr_len( ssl ) + msg_len ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_fetch_input", ret );
            return( ret );
        }

    /* Done reading this record, get ready for the next one */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
        if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
            ssl->next_record_offset = msg_len + mbedtls_ssl_hdr_len( ssl );
        else
#endif
            ssl->in_left = 0;
    }

    buf = ssl->in_msg;

    MBEDTLS_SSL_DEBUG_BUF( 4, "record contents", buf, msg_len );

    ssl->handshake->update_checksum( ssl, buf, msg_len );

    /*
     * Handshake layer:
     *     0  .   0   handshake type
     *     1  .   3   handshake length
     *     4  .   5   DTLS only: message seqence number
     *     6  .   8   DTLS only: fragment offset
     *     9  .  11   DTLS only: fragment length
     */
    if( msg_len < mbedtls_ssl_hs_hdr_len( ssl ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, handshake type: %d", buf[0] ) );

    if( buf[0] != MBEDTLS_SSL_HS_CLIENT_HELLO )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, handshake len.: %d",
                   ( buf[1] << 16 ) | ( buf[2] << 8 ) | buf[3] ) );

    /* We don't support fragmentation of ClientHello (yet?) */
    if( buf[1] != 0 ||
        msg_len != mbedtls_ssl_hs_hdr_len( ssl ) + ( ( buf[2] << 8 ) | buf[3] ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        /*
         * Copy the client's handshake message_seq on initial handshakes,
         * check sequence number on renego.
         */
#if defined(MBEDTLS_SSL_RENEGOTIATION)
        if( ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS )
        {
            /* This couldn't be done in ssl_prepare_handshake_record() */
            unsigned int cli_msg_seq = ( ssl->in_msg[4] << 8 ) |
                                         ssl->in_msg[5];

            if( cli_msg_seq != ssl->handshake->in_msg_seq )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message_seq: "
                                    "%d (expected %d)", cli_msg_seq,
                                    ssl->handshake->in_msg_seq ) );
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }

            ssl->handshake->in_msg_seq++;
        }
        else
#endif
        {
            unsigned int cli_msg_seq = ( ssl->in_msg[4] << 8 ) |
                                         ssl->in_msg[5];
            ssl->handshake->out_msg_seq = cli_msg_seq;
            ssl->handshake->in_msg_seq  = cli_msg_seq + 1;
        }

        /*
         * For now we don't support fragmentation, so make sure
         * fragment_offset == 0 and fragment_length == length
         */
        if( ssl->in_msg[6] != 0 || ssl->in_msg[7] != 0 || ssl->in_msg[8] != 0 ||
            memcmp( ssl->in_msg + 1, ssl->in_msg + 9, 3 ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "ClientHello fragmentation not supported" ) );
            return( MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE );
        }
    }
#endif /* MBEDTLS_SSL_PROTO_DTLS */

    buf += mbedtls_ssl_hs_hdr_len( ssl );
    msg_len -= mbedtls_ssl_hs_hdr_len( ssl );

    /*
     * ClientHello layer:
     *     0  .   1   protocol version
     *     2  .  33   random bytes (starting with 4 bytes of Unix time)
     *    34  .  35   session id length (1 byte)
     *    35  . 34+x  session id
     *   35+x . 35+x  DTLS only: cookie length (1 byte)
     *   36+x .  ..   DTLS only: cookie
     *    ..  .  ..   ciphersuite list length (2 bytes)
     *    ..  .  ..   ciphersuite list
     *    ..  .  ..   compression alg. list length (1 byte)
     *    ..  .  ..   compression alg. list
     *    ..  .  ..   extensions length (2 bytes, optional)
     *    ..  .  ..   extensions (optional)
     */

    /*
     * Minimal length (with everything empty and extensions ommitted) is
     * 2 + 32 + 1 + 2 + 1 = 38 bytes. Check that first, so that we can
     * read at least up to session id length without worrying.
     */
    if( msg_len < 38 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    /*
     * Check and save the protocol version
     */
    MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, version", buf, 2 );

    mbedtls_ssl_read_version( &ssl->major_ver, &ssl->minor_ver,
                      ssl->conf->transport, buf );

    ssl->handshake->max_major_ver = ssl->major_ver;
    ssl->handshake->max_minor_ver = ssl->minor_ver;

    if( ssl->major_ver < ssl->conf->min_major_ver ||
        ssl->minor_ver < ssl->conf->min_minor_ver )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "client only supports ssl smaller than minimum"
                            " [%d:%d] < [%d:%d]",
                            ssl->major_ver, ssl->minor_ver,
                            ssl->conf->min_major_ver, ssl->conf->min_minor_ver ) );

        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                     MBEDTLS_SSL_ALERT_MSG_PROTOCOL_VERSION );

        return( MBEDTLS_ERR_SSL_BAD_HS_PROTOCOL_VERSION );
    }

    if( ssl->major_ver > ssl->conf->max_major_ver )
    {
        ssl->major_ver = ssl->conf->max_major_ver;
        ssl->minor_ver = ssl->conf->max_minor_ver;
    }
    else if( ssl->minor_ver > ssl->conf->max_minor_ver )
        ssl->minor_ver = ssl->conf->max_minor_ver;

    /*
     * Save client random (inc. Unix time)
     */
    MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, random bytes", buf + 2, 32 );

    memcpy( ssl->handshake->randbytes, buf + 2, 32 );

    /*
     * Check the session ID length and save session ID
     */
    sess_len = buf[34];

    if( sess_len > sizeof( ssl->session_negotiate->id ) ||
        sess_len + 34 + 2 > msg_len ) /* 2 for cipherlist length field */
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, session id", buf + 35, sess_len );

    ssl->session_negotiate->id_len = sess_len;
    memset( ssl->session_negotiate->id, 0,
            sizeof( ssl->session_negotiate->id ) );
    memcpy( ssl->session_negotiate->id, buf + 35,
            ssl->session_negotiate->id_len );

    /*
     * Check the cookie length and content
     */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        cookie_offset = 35 + sess_len;
        cookie_len = buf[cookie_offset];

        if( cookie_offset + 1 + cookie_len + 2 > msg_len )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
        }

        MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, cookie",
                       buf + cookie_offset + 1, cookie_len );

#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY)
        if( ssl->conf->f_cookie_check != NULL
#if defined(MBEDTLS_SSL_RENEGOTIATION)
            && ssl->renego_status == MBEDTLS_SSL_INITIAL_HANDSHAKE
#endif
            )
        {
            if( ssl->conf->f_cookie_check( ssl->conf->p_cookie,
                                     buf + cookie_offset + 1, cookie_len,
                                     ssl->cli_id, ssl->cli_id_len ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 2, ( "cookie verification failed" ) );
                ssl->handshake->verify_cookie_len = 1;
            }
            else
            {
                MBEDTLS_SSL_DEBUG_MSG( 2, ( "cookie verification passed" ) );
                ssl->handshake->verify_cookie_len = 0;
            }
        }
        else
#endif /* MBEDTLS_SSL_DTLS_HELLO_VERIFY */
        {
            /* We know we didn't send a cookie, so it should be empty */
            if( cookie_len != 0 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }

            MBEDTLS_SSL_DEBUG_MSG( 2, ( "cookie verification skipped" ) );
        }

    /*
     * Check the ciphersuitelist length (will be parsed later)
     */
        ciph_offset = cookie_offset + 1 + cookie_len;
    }
    else
#endif /* MBEDTLS_SSL_PROTO_DTLS */
        ciph_offset = 35 + sess_len;

    ciph_len = ( buf[ciph_offset + 0] << 8 )
             | ( buf[ciph_offset + 1]      );

    if( ciph_len < 2 ||
        ciph_len + 2 + ciph_offset + 1 > msg_len || /* 1 for comp. alg. len */
        ( ciph_len % 2 ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, ciphersuitelist",
                   buf + ciph_offset + 2,  ciph_len );

    /*
     * Check the compression algorithms length and pick one
     */
    comp_offset = ciph_offset + 2 + ciph_len;

    comp_len = buf[comp_offset];

    if( comp_len < 1 ||
        comp_len > 16 ||
        comp_len + comp_offset + 1 > msg_len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    MBEDTLS_SSL_DEBUG_BUF( 3, "client hello, compression",
                      buf + comp_offset + 1, comp_len );

    ssl->session_negotiate->compression = MBEDTLS_SSL_COMPRESS_NULL;
#if defined(MBEDTLS_ZLIB_SUPPORT)
    for( i = 0; i < comp_len; ++i )
    {
        if( buf[comp_offset + 1 + i] == MBEDTLS_SSL_COMPRESS_DEFLATE )
        {
            ssl->session_negotiate->compression = MBEDTLS_SSL_COMPRESS_DEFLATE;
            break;
        }
    }
#endif

    /* See comments in ssl_write_client_hello() */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        ssl->session_negotiate->compression = MBEDTLS_SSL_COMPRESS_NULL;
#endif

    /* Do not parse the extensions if the protocol is SSLv3 */
#if defined(MBEDTLS_SSL_PROTO_SSL3)
    if( ( ssl->major_ver != 3 ) || ( ssl->minor_ver != 0 ) )
    {
#endif
        /*
         * Check the extension length
         */
        ext_offset = comp_offset + 1 + comp_len;
        if( msg_len > ext_offset )
        {
            if( msg_len < ext_offset + 2 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }

            ext_len = ( buf[ext_offset + 0] << 8 )
                    | ( buf[ext_offset + 1]      );

            if( ( ext_len > 0 && ext_len < 4 ) ||
                msg_len != ext_offset + 2 + ext_len )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }
        }
        else
            ext_len = 0;

        ext = buf + ext_offset + 2;
        MBEDTLS_SSL_DEBUG_BUF( 3, "client hello extensions", ext, ext_len );

        while( ext_len != 0 )
        {
            unsigned int ext_id   = ( ( ext[0] <<  8 )
                                    | ( ext[1]       ) );
            unsigned int ext_size = ( ( ext[2] <<  8 )
                                    | ( ext[3]       ) );

            if( ext_size + 4 > ext_len )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }
            switch( ext_id )
            {
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
            case MBEDTLS_TLS_EXT_SERVERNAME:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found ServerName extension" ) );
                if( ssl->conf->f_sni == NULL )
                    break;

                ret = ssl_parse_servername_ext( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */

            case MBEDTLS_TLS_EXT_RENEGOTIATION_INFO:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found renegotiation extension" ) );
#if defined(MBEDTLS_SSL_RENEGOTIATION)
                renegotiation_info_seen = 1;
#endif

                ret = ssl_parse_renegotiation_info( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
            case MBEDTLS_TLS_EXT_SIG_ALG:
                    MBEDTLS_SSL_DEBUG_MSG( 3, ( "found signature_algorithms extension" ) );
#if defined(MBEDTLS_SSL_RENEGOTIATION)
                if( ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS )
                    break;
#endif

                ret = ssl_parse_signature_algorithms_ext( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 &&
          MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED */

#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
            case MBEDTLS_TLS_EXT_SUPPORTED_ELLIPTIC_CURVES:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found supported elliptic curves extension" ) );

                ret = ssl_parse_supported_elliptic_curves( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;

            case MBEDTLS_TLS_EXT_SUPPORTED_POINT_FORMATS:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found supported point formats extension" ) );
                ssl->handshake->cli_exts |= MBEDTLS_TLS_EXT_SUPPORTED_POINT_FORMATS_PRESENT;

                ret = ssl_parse_supported_point_formats( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_ECDH_C || MBEDTLS_ECDSA_C ||
          MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
            case MBEDTLS_TLS_EXT_ECJPAKE_KKPP:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found ecjpake kkpp extension" ) );

                ret = ssl_parse_ecjpake_kkpp( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
            case MBEDTLS_TLS_EXT_MAX_FRAGMENT_LENGTH:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found max fragment length extension" ) );

                ret = ssl_parse_max_fragment_length_ext( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_SSL_MAX_FRAGMENT_LENGTH */

#if defined(MBEDTLS_SSL_TRUNCATED_HMAC)
            case MBEDTLS_TLS_EXT_TRUNCATED_HMAC:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found truncated hmac extension" ) );

                ret = ssl_parse_truncated_hmac_ext( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_SSL_TRUNCATED_HMAC */

#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
            case MBEDTLS_TLS_EXT_ENCRYPT_THEN_MAC:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found encrypt then mac extension" ) );

                ret = ssl_parse_encrypt_then_mac_ext( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_SSL_ENCRYPT_THEN_MAC */

#if defined(MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
            case MBEDTLS_TLS_EXT_EXTENDED_MASTER_SECRET:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found extended master secret extension" ) );

                ret = ssl_parse_extended_ms_ext( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_SSL_EXTENDED_MASTER_SECRET */

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
            case MBEDTLS_TLS_EXT_SESSION_TICKET:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found session ticket extension" ) );

                ret = ssl_parse_session_ticket_ext( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_SSL_SESSION_TICKETS */

#if defined(MBEDTLS_SSL_ALPN)
            case MBEDTLS_TLS_EXT_ALPN:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "found alpn extension" ) );

                ret = ssl_parse_alpn_ext( ssl, ext + 4, ext_size );
                if( ret != 0 )
                    return( ret );
                break;
#endif /* MBEDTLS_SSL_SESSION_TICKETS */

            default:
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "unknown extension found: %d (ignoring)",
                               ext_id ) );
            }

            ext_len -= 4 + ext_size;
            ext += 4 + ext_size;

            if( ext_len > 0 && ext_len < 4 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }
        }
#if defined(MBEDTLS_SSL_PROTO_SSL3)
    }
#endif

#if defined(MBEDTLS_SSL_FALLBACK_SCSV)
    for( i = 0, p = buf + 41 + sess_len; i < ciph_len; i += 2, p += 2 )
    {
        if( p[0] == (unsigned char)( ( MBEDTLS_SSL_FALLBACK_SCSV_VALUE >> 8 ) & 0xff ) &&
            p[1] == (unsigned char)( ( MBEDTLS_SSL_FALLBACK_SCSV_VALUE      ) & 0xff ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 2, ( "received FALLBACK_SCSV" ) );

            if( ssl->minor_ver < ssl->conf->max_minor_ver )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "inapropriate fallback" ) );

                mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_INAPROPRIATE_FALLBACK );

                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }

            break;
        }
    }
#endif /* MBEDTLS_SSL_FALLBACK_SCSV */

    /*
     * Check for TLS_EMPTY_RENEGOTIATION_INFO_SCSV
     */
    for( i = 0, p = buf + ciph_offset + 2; i < ciph_len; i += 2, p += 2 )
    {
        if( p[0] == 0 && p[1] == MBEDTLS_SSL_EMPTY_RENEGOTIATION_INFO )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "received TLS_EMPTY_RENEGOTIATION_INFO " ) );
#if defined(MBEDTLS_SSL_RENEGOTIATION)
            if( ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "received RENEGOTIATION SCSV during renegotiation" ) );

                if( ( ret = mbedtls_ssl_send_fatal_handshake_failure( ssl ) ) != 0 )
                    return( ret );

                return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
            }
#endif
            ssl->secure_renegotiation = MBEDTLS_SSL_SECURE_RENEGOTIATION;
            break;
        }
    }

    /*
     * Renegotiation security checks
     */
    if( ssl->secure_renegotiation != MBEDTLS_SSL_SECURE_RENEGOTIATION &&
        ssl->conf->allow_legacy_renegotiation == MBEDTLS_SSL_LEGACY_BREAK_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "legacy renegotiation, breaking off handshake" ) );
        handshake_failure = 1;
    }
#if defined(MBEDTLS_SSL_RENEGOTIATION)
    else if( ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS &&
             ssl->secure_renegotiation == MBEDTLS_SSL_SECURE_RENEGOTIATION &&
             renegotiation_info_seen == 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "renegotiation_info extension missing (secure)" ) );
        handshake_failure = 1;
    }
    else if( ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS &&
             ssl->secure_renegotiation == MBEDTLS_SSL_LEGACY_RENEGOTIATION &&
             ssl->conf->allow_legacy_renegotiation == MBEDTLS_SSL_LEGACY_NO_RENEGOTIATION )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "legacy renegotiation not allowed" ) );
        handshake_failure = 1;
    }
    else if( ssl->renego_status == MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS &&
             ssl->secure_renegotiation == MBEDTLS_SSL_LEGACY_RENEGOTIATION &&
             renegotiation_info_seen == 1 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "renegotiation_info extension present (legacy)" ) );
        handshake_failure = 1;
    }
#endif /* MBEDTLS_SSL_RENEGOTIATION */

    if( handshake_failure == 1 )
    {
        if( ( ret = mbedtls_ssl_send_fatal_handshake_failure( ssl ) ) != 0 )
            return( ret );

        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    /*
     * Search for a matching ciphersuite
     * (At the end because we need information from the EC-based extensions
     * and certificate from the SNI callback triggered by the SNI extension.)
     */
    got_common_suite = 0;
    ciphersuites = ssl->conf->ciphersuite_list[ssl->minor_ver];
    ciphersuite_info = NULL;
#if defined(MBEDTLS_SSL_SRV_RESPECT_CLIENT_PREFERENCE)
    for( j = 0, p = buf + ciph_offset + 2; j < ciph_len; j += 2, p += 2 )
    {
        for( i = 0; ciphersuites[i] != 0; i++ )
#else
    for( i = 0; ciphersuites[i] != 0; i++ )
    {
        for( j = 0, p = buf + ciph_offset + 2; j < ciph_len; j += 2, p += 2 )
#endif
        {
            if( p[0] != ( ( ciphersuites[i] >> 8 ) & 0xFF ) ||
                p[1] != ( ( ciphersuites[i]      ) & 0xFF ) )
                continue;

            got_common_suite = 1;

            if( ( ret = ssl_ciphersuite_match( ssl, ciphersuites[i],
                                               &ciphersuite_info ) ) != 0 )
                return( ret );

            if( ciphersuite_info != NULL )
                goto have_ciphersuite;
        }
    }

    if( got_common_suite )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "got ciphersuites in common, "
                            "but none of them usable" ) );
        mbedtls_ssl_send_fatal_handshake_failure( ssl );
        return( MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE );
    }
    else
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "got no ciphersuites in common" ) );
        mbedtls_ssl_send_fatal_handshake_failure( ssl );
        return( MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN );
    }

have_ciphersuite:
    MBEDTLS_SSL_DEBUG_MSG( 2, ( "selected ciphersuite: %s", ciphersuite_info->name ) );

    ssl->session_negotiate->ciphersuite = ciphersuites[i];
    ssl->transform_negotiate->ciphersuite_info = ciphersuite_info;

    ssl->state++;

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        mbedtls_ssl_recv_flight_completed( ssl );
#endif

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse client hello" ) );

    return( 0 );
}

#if defined(MBEDTLS_SSL_TRUNCATED_HMAC)
static void ssl_write_truncated_hmac_ext( mbedtls_ssl_context *ssl,
                                          unsigned char *buf,
                                          size_t *olen )
{
    unsigned char *p = buf;

    if( ssl->session_negotiate->trunc_hmac == MBEDTLS_SSL_TRUNC_HMAC_DISABLED )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, adding truncated hmac extension" ) );

    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_TRUNCATED_HMAC >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_TRUNCATED_HMAC      ) & 0xFF );

    *p++ = 0x00;
    *p++ = 0x00;

    *olen = 4;
}
#endif /* MBEDTLS_SSL_TRUNCATED_HMAC */

#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
static void ssl_write_encrypt_then_mac_ext( mbedtls_ssl_context *ssl,
                                            unsigned char *buf,
                                            size_t *olen )
{
    unsigned char *p = buf;
    const mbedtls_ssl_ciphersuite_t *suite = NULL;
    const mbedtls_cipher_info_t *cipher = NULL;

    if( ssl->session_negotiate->encrypt_then_mac == MBEDTLS_SSL_EXTENDED_MS_DISABLED ||
        ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_0 )
    {
        *olen = 0;
        return;
    }

    /*
     * RFC 7366: "If a server receives an encrypt-then-MAC request extension
     * from a client and then selects a stream or Authenticated Encryption
     * with Associated Data (AEAD) ciphersuite, it MUST NOT send an
     * encrypt-then-MAC response extension back to the client."
     */
    if( ( suite = mbedtls_ssl_ciphersuite_from_id(
                    ssl->session_negotiate->ciphersuite ) ) == NULL ||
        ( cipher = mbedtls_cipher_info_from_type( suite->cipher ) ) == NULL ||
        cipher->mode != MBEDTLS_MODE_CBC )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, adding encrypt then mac extension" ) );

    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_ENCRYPT_THEN_MAC >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_ENCRYPT_THEN_MAC      ) & 0xFF );

    *p++ = 0x00;
    *p++ = 0x00;

    *olen = 4;
}
#endif /* MBEDTLS_SSL_ENCRYPT_THEN_MAC */

#if defined(MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
static void ssl_write_extended_ms_ext( mbedtls_ssl_context *ssl,
                                       unsigned char *buf,
                                       size_t *olen )
{
    unsigned char *p = buf;

    if( ssl->handshake->extended_ms == MBEDTLS_SSL_EXTENDED_MS_DISABLED ||
        ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_0 )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, adding extended master secret "
                        "extension" ) );

    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_EXTENDED_MASTER_SECRET >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_EXTENDED_MASTER_SECRET      ) & 0xFF );

    *p++ = 0x00;
    *p++ = 0x00;

    *olen = 4;
}
#endif /* MBEDTLS_SSL_EXTENDED_MASTER_SECRET */

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
static void ssl_write_session_ticket_ext( mbedtls_ssl_context *ssl,
                                          unsigned char *buf,
                                          size_t *olen )
{
    unsigned char *p = buf;

    if( ssl->handshake->new_session_ticket == 0 )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, adding session ticket extension" ) );

    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_SESSION_TICKET >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_SESSION_TICKET      ) & 0xFF );

    *p++ = 0x00;
    *p++ = 0x00;

    *olen = 4;
}
#endif /* MBEDTLS_SSL_SESSION_TICKETS */

static void ssl_write_renegotiation_ext( mbedtls_ssl_context *ssl,
                                         unsigned char *buf,
                                         size_t *olen )
{
    unsigned char *p = buf;

    if( ssl->secure_renegotiation != MBEDTLS_SSL_SECURE_RENEGOTIATION )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, secure renegotiation extension" ) );

    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_RENEGOTIATION_INFO >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_RENEGOTIATION_INFO      ) & 0xFF );

#if defined(MBEDTLS_SSL_RENEGOTIATION)
    if( ssl->renego_status != MBEDTLS_SSL_INITIAL_HANDSHAKE )
    {
        *p++ = 0x00;
        *p++ = ( ssl->verify_data_len * 2 + 1 ) & 0xFF;
        *p++ = ssl->verify_data_len * 2 & 0xFF;

        memcpy( p, ssl->peer_verify_data, ssl->verify_data_len );
        p += ssl->verify_data_len;
        memcpy( p, ssl->own_verify_data, ssl->verify_data_len );
        p += ssl->verify_data_len;
    }
    else
#endif /* MBEDTLS_SSL_RENEGOTIATION */
    {
        *p++ = 0x00;
        *p++ = 0x01;
        *p++ = 0x00;
    }

    *olen = p - buf;
}

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
static void ssl_write_max_fragment_length_ext( mbedtls_ssl_context *ssl,
                                               unsigned char *buf,
                                               size_t *olen )
{
    unsigned char *p = buf;

    if( ssl->session_negotiate->mfl_code == MBEDTLS_SSL_MAX_FRAG_LEN_NONE )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, max_fragment_length extension" ) );

    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_MAX_FRAGMENT_LENGTH >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_MAX_FRAGMENT_LENGTH      ) & 0xFF );

    *p++ = 0x00;
    *p++ = 1;

    *p++ = ssl->session_negotiate->mfl_code;

    *olen = 5;
}
#endif /* MBEDTLS_SSL_MAX_FRAGMENT_LENGTH */

#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
static void ssl_write_supported_point_formats_ext( mbedtls_ssl_context *ssl,
                                                   unsigned char *buf,
                                                   size_t *olen )
{
    unsigned char *p = buf;
    ((void) ssl);

    if( ( ssl->handshake->cli_exts &
          MBEDTLS_TLS_EXT_SUPPORTED_POINT_FORMATS_PRESENT ) == 0 )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, supported_point_formats extension" ) );

    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_SUPPORTED_POINT_FORMATS >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_SUPPORTED_POINT_FORMATS      ) & 0xFF );

    *p++ = 0x00;
    *p++ = 2;

    *p++ = 1;
    *p++ = MBEDTLS_ECP_PF_UNCOMPRESSED;

    *olen = 6;
}
#endif /* MBEDTLS_ECDH_C || MBEDTLS_ECDSA_C || MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
static void ssl_write_ecjpake_kkpp_ext( mbedtls_ssl_context *ssl,
                                        unsigned char *buf,
                                        size_t *olen )
{
    int ret;
    unsigned char *p = buf;
    const unsigned char *end = ssl->out_msg + MBEDTLS_SSL_MAX_CONTENT_LEN;
    size_t kkpp_len;

    *olen = 0;

    /* Skip costly computation if not needed */
    if( ssl->transform_negotiate->ciphersuite_info->key_exchange !=
        MBEDTLS_KEY_EXCHANGE_ECJPAKE )
        return;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, ecjpake kkpp extension" ) );

    if( end - p < 4 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "buffer too small" ) );
        return;
    }

    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_ECJPAKE_KKPP >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_ECJPAKE_KKPP      ) & 0xFF );

    ret = mbedtls_ecjpake_write_round_one( &ssl->handshake->ecjpake_ctx,
                                        p + 2, end - p - 2, &kkpp_len,
                                        ssl->conf->f_rng, ssl->conf->p_rng );
    if( ret != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1 , "mbedtls_ecjpake_write_round_one", ret );
        return;
    }

    *p++ = (unsigned char)( ( kkpp_len >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( kkpp_len      ) & 0xFF );

    *olen = kkpp_len + 4;
}
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(MBEDTLS_SSL_ALPN )
static void ssl_write_alpn_ext( mbedtls_ssl_context *ssl,
                                unsigned char *buf, size_t *olen )
{
    if( ssl->alpn_chosen == NULL )
    {
        *olen = 0;
        return;
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, adding alpn extension" ) );

    /*
     * 0 . 1    ext identifier
     * 2 . 3    ext length
     * 4 . 5    protocol list length
     * 6 . 6    protocol name length
     * 7 . 7+n  protocol name
     */
    buf[0] = (unsigned char)( ( MBEDTLS_TLS_EXT_ALPN >> 8 ) & 0xFF );
    buf[1] = (unsigned char)( ( MBEDTLS_TLS_EXT_ALPN      ) & 0xFF );

    *olen = 7 + strlen( ssl->alpn_chosen );

    buf[2] = (unsigned char)( ( ( *olen - 4 ) >> 8 ) & 0xFF );
    buf[3] = (unsigned char)( ( ( *olen - 4 )      ) & 0xFF );

    buf[4] = (unsigned char)( ( ( *olen - 6 ) >> 8 ) & 0xFF );
    buf[5] = (unsigned char)( ( ( *olen - 6 )      ) & 0xFF );

    buf[6] = (unsigned char)( ( ( *olen - 7 )      ) & 0xFF );

    memcpy( buf + 7, ssl->alpn_chosen, *olen - 7 );
}
#endif /* MBEDTLS_ECDH_C || MBEDTLS_ECDSA_C */

#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY)
static int ssl_write_hello_verify_request( mbedtls_ssl_context *ssl )
{
    int ret;
    unsigned char *p = ssl->out_msg + 4;
    unsigned char *cookie_len_byte;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write hello verify request" ) );

    /*
     * struct {
     *   ProtocolVersion server_version;
     *   opaque cookie<0..2^8-1>;
     * } HelloVerifyRequest;
     */

    /* The RFC is not clear on this point, but sending the actual negotiated
     * version looks like the most interoperable thing to do. */
    mbedtls_ssl_write_version( ssl->major_ver, ssl->minor_ver,
                       ssl->conf->transport, p );
    MBEDTLS_SSL_DEBUG_BUF( 3, "server version", p, 2 );
    p += 2;

    /* If we get here, f_cookie_check is not null */
    if( ssl->conf->f_cookie_write == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "inconsistent cookie callbacks" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    /* Skip length byte until we know the length */
    cookie_len_byte = p++;

    if( ( ret = ssl->conf->f_cookie_write( ssl->conf->p_cookie,
                                     &p, ssl->out_buf + MBEDTLS_SSL_BUFFER_LEN,
                                     ssl->cli_id, ssl->cli_id_len ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "f_cookie_write", ret );
        return( ret );
    }

    *cookie_len_byte = (unsigned char)( p - ( cookie_len_byte + 1 ) );

    MBEDTLS_SSL_DEBUG_BUF( 3, "cookie sent", cookie_len_byte + 1, *cookie_len_byte );

    ssl->out_msglen  = p - ssl->out_msg;
    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_HELLO_VERIFY_REQUEST;

    ssl->state = MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT;

    if( ( ret = mbedtls_ssl_write_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_write_record", ret );
        return( ret );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write hello verify request" ) );

    return( 0 );
}
#endif /* MBEDTLS_SSL_DTLS_HELLO_VERIFY */

static int ssl_write_server_hello( mbedtls_ssl_context *ssl )
{
#if defined(MBEDTLS_HAVE_TIME)
    mbedtls_time_t t;
#endif
    int ret;
    size_t olen, ext_len = 0, n;
    unsigned char *buf, *p;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write server hello" ) );

#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake->verify_cookie_len != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "client hello was not authenticated" ) );
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write server hello" ) );

        return( ssl_write_hello_verify_request( ssl ) );
    }
#endif /* MBEDTLS_SSL_DTLS_HELLO_VERIFY */

    if( ssl->conf->f_rng == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "no RNG provided") );
        return( MBEDTLS_ERR_SSL_NO_RNG );
    }

    /*
     *     0  .   0   handshake type
     *     1  .   3   handshake length
     *     4  .   5   protocol version
     *     6  .   9   UNIX time()
     *    10  .  37   random bytes
     */
    buf = ssl->out_msg;
    p = buf + 4;

    mbedtls_ssl_write_version( ssl->major_ver, ssl->minor_ver,
                       ssl->conf->transport, p );
    p += 2;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, chosen version: [%d:%d]",
                        buf[4], buf[5] ) );

#if defined(MBEDTLS_HAVE_TIME)
    t = mbedtls_time( NULL );
    *p++ = (unsigned char)( t >> 24 );
    *p++ = (unsigned char)( t >> 16 );
    *p++ = (unsigned char)( t >>  8 );
    *p++ = (unsigned char)( t       );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, current time: %lu", t ) );
#else
    if( ( ret = ssl->conf->f_rng( ssl->conf->p_rng, p, 4 ) ) != 0 )
        return( ret );

    p += 4;
#endif /* MBEDTLS_HAVE_TIME */

    if( ( ret = ssl->conf->f_rng( ssl->conf->p_rng, p, 28 ) ) != 0 )
        return( ret );

    p += 28;

    memcpy( ssl->handshake->randbytes + 32, buf + 6, 32 );

    MBEDTLS_SSL_DEBUG_BUF( 3, "server hello, random bytes", buf + 6, 32 );

    /*
     * Resume is 0  by default, see ssl_handshake_init().
     * It may be already set to 1 by ssl_parse_session_ticket_ext().
     * If not, try looking up session ID in our cache.
     */
    if( ssl->handshake->resume == 0 &&
#if defined(MBEDTLS_SSL_RENEGOTIATION)
        ssl->renego_status == MBEDTLS_SSL_INITIAL_HANDSHAKE &&
#endif
        ssl->session_negotiate->id_len != 0 &&
        ssl->conf->f_get_cache != NULL &&
        ssl->conf->f_get_cache( ssl->conf->p_cache, ssl->session_negotiate ) == 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "session successfully restored from cache" ) );
        ssl->handshake->resume = 1;
    }

    if( ssl->handshake->resume == 0 )
    {
        /*
         * New session, create a new session id,
         * unless we're about to issue a session ticket
         */
        ssl->state++;

#if defined(MBEDTLS_HAVE_TIME)
        ssl->session_negotiate->start = mbedtls_time( NULL );
#endif

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
        if( ssl->handshake->new_session_ticket != 0 )
        {
            ssl->session_negotiate->id_len = n = 0;
            memset( ssl->session_negotiate->id, 0, 32 );
        }
        else
#endif /* MBEDTLS_SSL_SESSION_TICKETS */
        {
            ssl->session_negotiate->id_len = n = 32;
            if( ( ret = ssl->conf->f_rng( ssl->conf->p_rng, ssl->session_negotiate->id,
                                    n ) ) != 0 )
                return( ret );
        }
    }
    else
    {
        /*
         * Resuming a session
         */
        n = ssl->session_negotiate->id_len;
        ssl->state = MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC;

        if( ( ret = mbedtls_ssl_derive_keys( ssl ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_derive_keys", ret );
            return( ret );
        }
    }

    /*
     *    38  .  38     session id length
     *    39  . 38+n    session id
     *   39+n . 40+n    chosen ciphersuite
     *   41+n . 41+n    chosen compression alg.
     *   42+n . 43+n    extensions length
     *   44+n . 43+n+m  extensions
     */
    *p++ = (unsigned char) ssl->session_negotiate->id_len;
    memcpy( p, ssl->session_negotiate->id, ssl->session_negotiate->id_len );
    p += ssl->session_negotiate->id_len;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, session id len.: %d", n ) );
    MBEDTLS_SSL_DEBUG_BUF( 3,   "server hello, session id", buf + 39, n );
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "%s session has been resumed",
                   ssl->handshake->resume ? "a" : "no" ) );

    *p++ = (unsigned char)( ssl->session_negotiate->ciphersuite >> 8 );
    *p++ = (unsigned char)( ssl->session_negotiate->ciphersuite      );
    *p++ = (unsigned char)( ssl->session_negotiate->compression      );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, chosen ciphersuite: %s",
           mbedtls_ssl_get_ciphersuite_name( ssl->session_negotiate->ciphersuite ) ) );
    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, compress alg.: 0x%02X",
                   ssl->session_negotiate->compression ) );

    /* Do not write the extensions if the protocol is SSLv3 */
#if defined(MBEDTLS_SSL_PROTO_SSL3)
    if( ( ssl->major_ver != 3 ) || ( ssl->minor_ver != 0 ) )
    {
#endif

    /*
     *  First write extensions, then the total length
     */
    ssl_write_renegotiation_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
    ssl_write_max_fragment_length_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;
#endif

#if defined(MBEDTLS_SSL_TRUNCATED_HMAC)
    ssl_write_truncated_hmac_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;
#endif

#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
    ssl_write_encrypt_then_mac_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;
#endif

#if defined(MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
    ssl_write_extended_ms_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;
#endif

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
    ssl_write_session_ticket_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;
#endif

#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    ssl_write_supported_point_formats_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    ssl_write_ecjpake_kkpp_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;
#endif

#if defined(MBEDTLS_SSL_ALPN)
    ssl_write_alpn_ext( ssl, p + 2 + ext_len, &olen );
    ext_len += olen;
#endif

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "server hello, total extension length: %d", ext_len ) );

    if( ext_len > 0 )
    {
        *p++ = (unsigned char)( ( ext_len >> 8 ) & 0xFF );
        *p++ = (unsigned char)( ( ext_len      ) & 0xFF );
        p += ext_len;
    }

#if defined(MBEDTLS_SSL_PROTO_SSL3)
    }
#endif

    ssl->out_msglen  = p - buf;
    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_SERVER_HELLO;

    ret = mbedtls_ssl_write_record( ssl );

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write server hello" ) );

    return( ret );
}

#if !defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)       && \
    !defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)   && \
    !defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)  && \
    !defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) && \
    !defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)&& \
    !defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
static int ssl_write_certificate_request( mbedtls_ssl_context *ssl )
{
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info = ssl->transform_negotiate->ciphersuite_info;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write certificate request" ) );

    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip write certificate request" ) );
        ssl->state++;
        return( 0 );
    }

    MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
    return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
}
#else
static int ssl_write_certificate_request( mbedtls_ssl_context *ssl )
{
    int ret = MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info = ssl->transform_negotiate->ciphersuite_info;
    size_t dn_size, total_dn_size; /* excluding length bytes */
    size_t ct_len, sa_len; /* including length bytes */
    unsigned char *buf, *p;
    const unsigned char * const end = ssl->out_msg + MBEDTLS_SSL_MAX_CONTENT_LEN;
    const mbedtls_x509_crt *crt;
    int authmode;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write certificate request" ) );

    ssl->state++;

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    if( ssl->handshake->sni_authmode != MBEDTLS_SSL_VERIFY_UNSET )
        authmode = ssl->handshake->sni_authmode;
    else
#endif
        authmode = ssl->conf->authmode;

    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE ||
        authmode == MBEDTLS_SSL_VERIFY_NONE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip write certificate request" ) );
        return( 0 );
    }

    /*
     *     0  .   0   handshake type
     *     1  .   3   handshake length
     *     4  .   4   cert type count
     *     5  .. m-1  cert types
     *     m  .. m+1  sig alg length (TLS 1.2 only)
     *    m+1 .. n-1  SignatureAndHashAlgorithms (TLS 1.2 only)
     *     n  .. n+1  length of all DNs
     *    n+2 .. n+3  length of DN 1
     *    n+4 .. ...  Distinguished Name #1
     *    ... .. ...  length of DN 2, etc.
     */
    buf = ssl->out_msg;
    p = buf + 4;

    /*
     * Supported certificate types
     *
     *     ClientCertificateType certificate_types<1..2^8-1>;
     *     enum { (255) } ClientCertificateType;
     */
    ct_len = 0;

#if defined(MBEDTLS_RSA_C)
    p[1 + ct_len++] = MBEDTLS_SSL_CERT_TYPE_RSA_SIGN;
#endif
#if defined(MBEDTLS_ECDSA_C)
    p[1 + ct_len++] = MBEDTLS_SSL_CERT_TYPE_ECDSA_SIGN;
#endif

    p[0] = (unsigned char) ct_len++;
    p += ct_len;

    sa_len = 0;
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
    /*
     * Add signature_algorithms for verify (TLS 1.2)
     *
     *     SignatureAndHashAlgorithm supported_signature_algorithms<2..2^16-2>;
     *
     *     struct {
     *           HashAlgorithm hash;
     *           SignatureAlgorithm signature;
     *     } SignatureAndHashAlgorithm;
     *
     *     enum { (255) } HashAlgorithm;
     *     enum { (255) } SignatureAlgorithm;
     */
    if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
    {
        const int *cur;

        /*
         * Supported signature algorithms
         */
        for( cur = ssl->conf->sig_hashes; *cur != MBEDTLS_MD_NONE; cur++ )
        {
            unsigned char hash = mbedtls_ssl_hash_from_md_alg( *cur );

            if( MBEDTLS_SSL_HASH_NONE == hash || mbedtls_ssl_set_calc_verify_md( ssl, hash ) )
                continue;

#if defined(MBEDTLS_RSA_C)
            p[2 + sa_len++] = hash;
            p[2 + sa_len++] = MBEDTLS_SSL_SIG_RSA;
#endif
#if defined(MBEDTLS_ECDSA_C)
            p[2 + sa_len++] = hash;
            p[2 + sa_len++] = MBEDTLS_SSL_SIG_ECDSA;
#endif
        }

        p[0] = (unsigned char)( sa_len >> 8 );
        p[1] = (unsigned char)( sa_len      );
        sa_len += 2;
        p += sa_len;
    }
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */

    /*
     * DistinguishedName certificate_authorities<0..2^16-1>;
     * opaque DistinguishedName<1..2^16-1>;
     */
    p += 2;
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    if( ssl->handshake->sni_ca_chain != NULL )
        crt = ssl->handshake->sni_ca_chain;
    else
#endif
        crt = ssl->conf->ca_chain;

    total_dn_size = 0;
    while( crt != NULL && crt->version != 0 )
    {
        dn_size = crt->subject_raw.len;

        if( end < p ||
            (size_t)( end - p ) < dn_size ||
            (size_t)( end - p ) < 2 + dn_size )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "skipping CAs: buffer too short" ) );
            break;
        }

        *p++ = (unsigned char)( dn_size >> 8 );
        *p++ = (unsigned char)( dn_size      );
        memcpy( p, crt->subject_raw.p, dn_size );
        p += dn_size;

        MBEDTLS_SSL_DEBUG_BUF( 3, "requested DN", p - dn_size, dn_size );

        total_dn_size += 2 + dn_size;
        crt = crt->next;
    }

    ssl->out_msglen  = p - buf;
    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_CERTIFICATE_REQUEST;
    ssl->out_msg[4 + ct_len + sa_len] = (unsigned char)( total_dn_size  >> 8 );
    ssl->out_msg[5 + ct_len + sa_len] = (unsigned char)( total_dn_size       );

    ret = mbedtls_ssl_write_record( ssl );

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write certificate request" ) );

    return( ret );
}
#endif /* !MBEDTLS_KEY_EXCHANGE_RSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
static int ssl_get_ecdh_params_from_cert( mbedtls_ssl_context *ssl )
{
    int ret;

    if( ! mbedtls_pk_can_do( mbedtls_ssl_own_key( ssl ), MBEDTLS_PK_ECKEY ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "server key not ECDH capable" ) );
        return( MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH );
    }

    if( ( ret = mbedtls_ecdh_get_params( &ssl->handshake->ecdh_ctx,
                                 mbedtls_pk_ec( *mbedtls_ssl_own_key( ssl ) ),
                                 MBEDTLS_ECDH_OURS ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, ( "mbedtls_ecdh_get_params" ), ret );
        return( ret );
    }

    return( 0 );
}
#endif /* MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED) ||
          MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED */

static int ssl_write_server_key_exchange( mbedtls_ssl_context *ssl )
{
    int ret;
    size_t n = 0;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info =
                            ssl->transform_negotiate->ciphersuite_info;

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) ||                       \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED) ||                       \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) ||                     \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED) ||                     \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED) ||                   \
    defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    unsigned char *p = ssl->out_msg + 4;
    unsigned char *dig_signed = p;
    size_t dig_signed_len = 0, len;
    ((void) dig_signed);
    ((void) dig_signed_len);
    ((void) len);
#endif

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write server key exchange" ) );

#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED) ||                           \
    defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED) ||                           \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip write server key exchange" ) );
        ssl->state++;
        return( 0 );
    }
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDH_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA )
    {
        ssl_get_ecdh_params_from_cert( ssl );

        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip write server key exchange" ) );
        ssl->state++;
        return( 0 );
    }
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE )
    {
        size_t jlen;
        const unsigned char *end = ssl->out_msg + MBEDTLS_SSL_MAX_CONTENT_LEN;

        ret = mbedtls_ecjpake_write_round_two( &ssl->handshake->ecjpake_ctx,
                p, end - p, &jlen, ssl->conf->f_rng, ssl->conf->p_rng );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_write_round_two", ret );
            return( ret );
        }

        p += jlen;
        n += jlen;
    }
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED) ||                       \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK )
    {
        /* Note: we don't support identity hints, until someone asks
         * for them. */
        *(p++) = 0x00;
        *(p++) = 0x00;

        n += 2;
    }
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) ||                       \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK )
    {
        if( ssl->conf->dhm_P.p == NULL || ssl->conf->dhm_G.p == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "no DH parameters set" ) );
            return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
        }

        /*
         * Ephemeral DH parameters:
         *
         * struct {
         *     opaque dh_p<1..2^16-1>;
         *     opaque dh_g<1..2^16-1>;
         *     opaque dh_Ys<1..2^16-1>;
         * } ServerDHParams;
         */
        if( ( ret = mbedtls_mpi_copy( &ssl->handshake->dhm_ctx.P, &ssl->conf->dhm_P ) ) != 0 ||
            ( ret = mbedtls_mpi_copy( &ssl->handshake->dhm_ctx.G, &ssl->conf->dhm_G ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_mpi_copy", ret );
            return( ret );
        }

        if( ( ret = mbedtls_dhm_make_params( &ssl->handshake->dhm_ctx,
                        (int) mbedtls_mpi_size( &ssl->handshake->dhm_ctx.P ),
                        p, &len, ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_make_params", ret );
            return( ret );
        }

        dig_signed = p;
        dig_signed_len = len;

        p += len;
        n += len;

        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: X ", &ssl->handshake->dhm_ctx.X  );
        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: P ", &ssl->handshake->dhm_ctx.P  );
        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: G ", &ssl->handshake->dhm_ctx.G  );
        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: GX", &ssl->handshake->dhm_ctx.GX );
    }
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE__SOME__ECDHE_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK )
    {
        /*
         * Ephemeral ECDH parameters:
         *
         * struct {
         *     ECParameters curve_params;
         *     ECPoint      public;
         * } ServerECDHParams;
         */
        const mbedtls_ecp_curve_info **curve = NULL;
        const mbedtls_ecp_group_id *gid;

        /* Match our preference list against the offered curves */
        for( gid = ssl->conf->curve_list; *gid != MBEDTLS_ECP_DP_NONE; gid++ )
            for( curve = ssl->handshake->curves; *curve != NULL; curve++ )
                if( (*curve)->grp_id == *gid )
                    goto curve_matching_done;

curve_matching_done:
        if( curve == NULL || *curve == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "no matching curve for ECDHE" ) );
            return( MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN );
        }

        MBEDTLS_SSL_DEBUG_MSG( 2, ( "ECDHE curve: %s", (*curve)->name ) );

        if( ( ret = mbedtls_ecp_group_load( &ssl->handshake->ecdh_ctx.grp,
                                       (*curve)->grp_id ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecp_group_load", ret );
            return( ret );
        }

        if( ( ret = mbedtls_ecdh_make_params( &ssl->handshake->ecdh_ctx, &len,
                                      p, MBEDTLS_SSL_MAX_CONTENT_LEN - n,
                                      ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_make_params", ret );
            return( ret );
        }

        dig_signed = p;
        dig_signed_len = len;

        p += len;
        n += len;

        MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Q ", &ssl->handshake->ecdh_ctx.Q );
    }
#endif /* MBEDTLS_KEY_EXCHANGE__SOME__ECDHE_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) ||                       \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) ||                     \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA )
    {
        size_t signature_len = 0;
        unsigned int hashlen = 0;
        unsigned char hash[64];
        mbedtls_md_type_t md_alg = MBEDTLS_MD_NONE;

        /*
         * Choose hash algorithm. NONE means MD5 + SHA1 here.
         */
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
        {
            md_alg = mbedtls_ssl_md_alg_from_hash( ssl->handshake->sig_alg );

            if( md_alg == MBEDTLS_MD_NONE )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
                return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
            }
        }
        else
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
        if( ciphersuite_info->key_exchange ==
                  MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA )
        {
            md_alg = MBEDTLS_MD_SHA1;
        }
        else
#endif
        {
            md_alg = MBEDTLS_MD_NONE;
        }

        /*
         * Compute the hash to be signed
         */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
        if( md_alg == MBEDTLS_MD_NONE )
        {
            mbedtls_md5_context mbedtls_md5;
            mbedtls_sha1_context mbedtls_sha1;

            mbedtls_md5_init(  &mbedtls_md5  );
            mbedtls_sha1_init( &mbedtls_sha1 );

            /*
             * digitally-signed struct {
             *     opaque md5_hash[16];
             *     opaque sha_hash[20];
             * };
             *
             * md5_hash
             *     MD5(ClientHello.random + ServerHello.random
             *                            + ServerParams);
             * sha_hash
             *     SHA(ClientHello.random + ServerHello.random
             *                            + ServerParams);
             */
            mbedtls_md5_starts( &mbedtls_md5 );
            mbedtls_md5_update( &mbedtls_md5, ssl->handshake->randbytes,  64 );
            mbedtls_md5_update( &mbedtls_md5, dig_signed, dig_signed_len );
            mbedtls_md5_finish( &mbedtls_md5, hash );

            mbedtls_sha1_starts( &mbedtls_sha1 );
            mbedtls_sha1_update( &mbedtls_sha1, ssl->handshake->randbytes,  64 );
            mbedtls_sha1_update( &mbedtls_sha1, dig_signed, dig_signed_len );
            mbedtls_sha1_finish( &mbedtls_sha1, hash + 16 );

            hashlen = 36;

            mbedtls_md5_free(  &mbedtls_md5  );
            mbedtls_sha1_free( &mbedtls_sha1 );
        }
        else
#endif /* MBEDTLS_SSL_PROTO_SSL3 || MBEDTLS_SSL_PROTO_TLS1 || \
          MBEDTLS_SSL_PROTO_TLS1_1 */
#if defined(MBEDTLS_SSL_PROTO_TLS1) || defined(MBEDTLS_SSL_PROTO_TLS1_1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( md_alg != MBEDTLS_MD_NONE )
        {
            mbedtls_md_context_t ctx;
            const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type( md_alg );

            mbedtls_md_init( &ctx );

            /* Info from md_alg will be used instead */
            hashlen = 0;

            /*
             * digitally-signed struct {
             *     opaque client_random[32];
             *     opaque server_random[32];
             *     ServerDHParams params;
             * };
             */
            if( ( ret = mbedtls_md_setup( &ctx, md_info, 0 ) ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_md_setup", ret );
                return( ret );
            }

            mbedtls_md_starts( &ctx );
            mbedtls_md_update( &ctx, ssl->handshake->randbytes, 64 );
            mbedtls_md_update( &ctx, dig_signed, dig_signed_len );
            mbedtls_md_finish( &ctx, hash );
            mbedtls_md_free( &ctx );
        }
        else
#endif /* MBEDTLS_SSL_PROTO_TLS1 || MBEDTLS_SSL_PROTO_TLS1_1 || \
          MBEDTLS_SSL_PROTO_TLS1_2 */
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }

        MBEDTLS_SSL_DEBUG_BUF( 3, "parameters hash", hash, hashlen != 0 ? hashlen :
            (unsigned int) ( mbedtls_md_get_size( mbedtls_md_info_from_type( md_alg ) ) ) );

        /*
         * Make the signature
         */
        if( mbedtls_ssl_own_key( ssl ) == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "got no private key" ) );
            return( MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED );
        }

#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
        {
            *(p++) = ssl->handshake->sig_alg;
            *(p++) = mbedtls_ssl_sig_from_pk( mbedtls_ssl_own_key( ssl ) );

            n += 2;
        }
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */

        if( ( ret = mbedtls_pk_sign( mbedtls_ssl_own_key( ssl ), md_alg, hash, hashlen,
                        p + 2 , &signature_len,
                        ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_pk_sign", ret );
            return( ret );
        }

        *(p++) = (unsigned char)( signature_len >> 8 );
        *(p++) = (unsigned char)( signature_len      );
        n += 2;

        MBEDTLS_SSL_DEBUG_BUF( 3, "my signature", p, signature_len );

        n += signature_len;
    }
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED */

    ssl->out_msglen  = 4 + n;
    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_SERVER_KEY_EXCHANGE;

    ssl->state++;

    if( ( ret = mbedtls_ssl_write_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_write_record", ret );
        return( ret );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write server key exchange" ) );

    return( 0 );
}

static int ssl_write_server_hello_done( mbedtls_ssl_context *ssl )
{
    int ret;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write server hello done" ) );

    ssl->out_msglen  = 4;
    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_SERVER_HELLO_DONE;

    ssl->state++;

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        mbedtls_ssl_send_flight_completed( ssl );
#endif

    if( ( ret = mbedtls_ssl_write_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_write_record", ret );
        return( ret );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write server hello done" ) );

    return( 0 );
}

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) ||                       \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
static int ssl_parse_client_dh_public( mbedtls_ssl_context *ssl, unsigned char **p,
                                       const unsigned char *end )
{
    int ret = MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE;
    size_t n;

    /*
     * Receive G^Y mod P, premaster = (G^Y)^X mod P
     */
    if( *p + 2 > end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    n = ( (*p)[0] << 8 ) | (*p)[1];
    *p += 2;

    if( *p + n > end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    if( ( ret = mbedtls_dhm_read_public( &ssl->handshake->dhm_ctx, *p, n ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_read_public", ret );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP );
    }

    *p += n;

    MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: GY", &ssl->handshake->dhm_ctx.GY );

    return( ret );
}
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED) ||                           \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
static int ssl_parse_encrypted_pms( mbedtls_ssl_context *ssl,
                                    const unsigned char *p,
                                    const unsigned char *end,
                                    size_t pms_offset )
{
    int ret;
    size_t len = mbedtls_pk_get_len( mbedtls_ssl_own_key( ssl ) );
    unsigned char *pms = ssl->handshake->premaster + pms_offset;
    unsigned char ver[2];
    unsigned char fake_pms[48], peer_pms[48];
    unsigned char mask;
    size_t i, peer_pmslen;
    unsigned int diff;

    if( ! mbedtls_pk_can_do( mbedtls_ssl_own_key( ssl ), MBEDTLS_PK_RSA ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "got no RSA private key" ) );
        return( MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED );
    }

    /*
     * Decrypt the premaster using own private RSA key
     */
#if defined(MBEDTLS_SSL_PROTO_TLS1) || defined(MBEDTLS_SSL_PROTO_TLS1_1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_2)
    if( ssl->minor_ver != MBEDTLS_SSL_MINOR_VERSION_0 )
    {
        if( *p++ != ( ( len >> 8 ) & 0xFF ) ||
            *p++ != ( ( len      ) & 0xFF ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
        }
    }
#endif

    if( p + len != end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    mbedtls_ssl_write_version( ssl->handshake->max_major_ver,
                       ssl->handshake->max_minor_ver,
                       ssl->conf->transport, ver );

    /*
     * Protection against Bleichenbacher's attack: invalid PKCS#1 v1.5 padding
     * must not cause the connection to end immediately; instead, send a
     * bad_record_mac later in the handshake.
     * Also, avoid data-dependant branches here to protect against
     * timing-based variants.
     */
    ret = ssl->conf->f_rng( ssl->conf->p_rng, fake_pms, sizeof( fake_pms ) );
    if( ret != 0 )
        return( ret );

    ret = mbedtls_pk_decrypt( mbedtls_ssl_own_key( ssl ), p, len,
                      peer_pms, &peer_pmslen,
                      sizeof( peer_pms ),
                      ssl->conf->f_rng, ssl->conf->p_rng );

    diff  = (unsigned int) ret;
    diff |= peer_pmslen ^ 48;
    diff |= peer_pms[0] ^ ver[0];
    diff |= peer_pms[1] ^ ver[1];

#if defined(MBEDTLS_SSL_DEBUG_ALL)
    if( diff != 0 )
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
#endif

    if( sizeof( ssl->handshake->premaster ) < pms_offset ||
        sizeof( ssl->handshake->premaster ) - pms_offset < 48 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }
    ssl->handshake->pmslen = 48;

    /* mask = diff ? 0xff : 0x00 using bit operations to avoid branches */
    /* MSVC has a warning about unary minus on unsigned, but this is
     * well-defined and precisely what we want to do here */
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4146 )
#endif
    mask = - ( ( diff | - diff ) >> ( sizeof( unsigned int ) * 8 - 1 ) );
#if defined(_MSC_VER)
#pragma warning( pop )
#endif

    for( i = 0; i < ssl->handshake->pmslen; i++ )
        pms[i] = ( mask & fake_pms[i] ) | ( (~mask) & peer_pms[i] );

    return( 0 );
}
#endif /* MBEDTLS_KEY_EXCHANGE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
static int ssl_parse_client_psk_identity( mbedtls_ssl_context *ssl, unsigned char **p,
                                          const unsigned char *end )
{
    int ret = 0;
    size_t n;

    if( ssl->conf->f_psk == NULL &&
        ( ssl->conf->psk == NULL || ssl->conf->psk_identity == NULL ||
          ssl->conf->psk_identity_len == 0 || ssl->conf->psk_len == 0 ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "got no pre-shared key" ) );
        return( MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED );
    }

    /*
     * Receive client pre-shared key identity name
     */
    if( *p + 2 > end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    n = ( (*p)[0] << 8 ) | (*p)[1];
    *p += 2;

    if( n < 1 || n > 65535 || *p + n > end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    if( ssl->conf->f_psk != NULL )
    {
        if( ssl->conf->f_psk( ssl->conf->p_psk, ssl, *p, n ) != 0 )
            ret = MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY;
    }
    else
    {
        /* Identity is not a big secret since clients send it in the clear,
         * but treat it carefully anyway, just in case */
        if( n != ssl->conf->psk_identity_len ||
            mbedtls_ssl_safer_memcmp( ssl->conf->psk_identity, *p, n ) != 0 )
        {
            ret = MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY;
        }
    }

    if( ret == MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY )
    {
        MBEDTLS_SSL_DEBUG_BUF( 3, "Unknown PSK identity", *p, n );
        if( ( ret = mbedtls_ssl_send_alert_message( ssl,
                              MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                              MBEDTLS_SSL_ALERT_MSG_UNKNOWN_PSK_IDENTITY ) ) != 0 )
        {
            return( ret );
        }

        return( MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY );
    }

    *p += n;

    return( 0 );
}
#endif /* MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED */

static int ssl_parse_client_key_exchange( mbedtls_ssl_context *ssl )
{
    int ret;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info;
    unsigned char *p, *end;

    ciphersuite_info = ssl->transform_negotiate->ciphersuite_info;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse client key exchange" ) );

    if( ( ret = mbedtls_ssl_read_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_read_record", ret );
        return( ret );
    }

    p = ssl->in_msg + mbedtls_ssl_hs_hdr_len( ssl );
    end = ssl->in_msg + ssl->in_hslen;

    if( ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    if( ssl->in_msg[0] != MBEDTLS_SSL_HS_CLIENT_KEY_EXCHANGE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_RSA )
    {
        if( ( ret = ssl_parse_client_dh_public( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_dh_public" ), ret );
            return( ret );
        }

        if( p != end )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
        }

        if( ( ret = mbedtls_dhm_calc_secret( &ssl->handshake->dhm_ctx,
                                      ssl->handshake->premaster,
                                      MBEDTLS_PREMASTER_SIZE,
                                     &ssl->handshake->pmslen,
                                      ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_calc_secret", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS );
        }

        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: K ", &ssl->handshake->dhm_ctx.K  );
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) ||                     \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED) ||                   \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED) ||                      \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDH_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA )
    {
        if( ( ret = mbedtls_ecdh_read_public( &ssl->handshake->ecdh_ctx,
                                      p, end - p) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_read_public", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP );
        }

        MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Qp ", &ssl->handshake->ecdh_ctx.Qp );

        if( ( ret = mbedtls_ecdh_calc_secret( &ssl->handshake->ecdh_ctx,
                                      &ssl->handshake->pmslen,
                                       ssl->handshake->premaster,
                                       MBEDTLS_MPI_MAX_SIZE,
                                       ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_calc_secret", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS );
        }

        MBEDTLS_SSL_DEBUG_MPI( 3, "ECDH: z  ", &ssl->handshake->ecdh_ctx.z );
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK )
    {
        if( ( ret = ssl_parse_client_psk_identity( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_psk_identity" ), ret );
            return( ret );
        }

        if( p != end )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
        }

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK )
    {
        if( ( ret = ssl_parse_client_psk_identity( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_psk_identity" ), ret );
            return( ret );
        }

        if( ( ret = ssl_parse_encrypted_pms( ssl, p, end, 2 ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_encrypted_pms" ), ret );
            return( ret );
        }

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK )
    {
        if( ( ret = ssl_parse_client_psk_identity( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_psk_identity" ), ret );
            return( ret );
        }
        if( ( ret = ssl_parse_client_dh_public( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_dh_public" ), ret );
            return( ret );
        }

        if( p != end )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
        }

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK )
    {
        if( ( ret = ssl_parse_client_psk_identity( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_psk_identity" ), ret );
            return( ret );
        }

        if( ( ret = mbedtls_ecdh_read_public( &ssl->handshake->ecdh_ctx,
                                       p, end - p ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_read_public", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP );
        }

        MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Qp ", &ssl->handshake->ecdh_ctx.Qp );

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA )
    {
        if( ( ret = ssl_parse_encrypted_pms( ssl, p, end, 0 ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_parse_encrypted_pms_secret" ), ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_RSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE )
    {
        ret = mbedtls_ecjpake_read_round_two( &ssl->handshake->ecjpake_ctx,
                                              p, end - p );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_read_round_two", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
        }

        ret = mbedtls_ecjpake_derive_secret( &ssl->handshake->ecjpake_ctx,
                ssl->handshake->premaster, 32, &ssl->handshake->pmslen,
                ssl->conf->f_rng, ssl->conf->p_rng );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_derive_secret", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    if( ( ret = mbedtls_ssl_derive_keys( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_derive_keys", ret );
        return( ret );
    }

    ssl->state++;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse client key exchange" ) );

    return( 0 );
}

#if !defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)       && \
    !defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)   && \
    !defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)  && \
    !defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) && \
    !defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)&& \
    !defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
static int ssl_parse_certificate_verify( mbedtls_ssl_context *ssl )
{
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info = ssl->transform_negotiate->ciphersuite_info;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse certificate verify" ) );

    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip parse certificate verify" ) );
        ssl->state++;
        return( 0 );
    }

    MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
    return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
}
#else
static int ssl_parse_certificate_verify( mbedtls_ssl_context *ssl )
{
    int ret = MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE;
    size_t i, sig_len;
    unsigned char hash[48];
    unsigned char *hash_start = hash;
    size_t hashlen;
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
    mbedtls_pk_type_t pk_alg;
#endif
    mbedtls_md_type_t md_alg;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info = ssl->transform_negotiate->ciphersuite_info;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse certificate verify" ) );

    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE ||
        ssl->session_negotiate->peer_cert == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip parse certificate verify" ) );
        ssl->state++;
        return( 0 );
    }

    /* Read the message without adding it to the checksum */
    do {

        if( ( ret = mbedtls_ssl_read_record_layer( ssl ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "mbedtls_ssl_read_record_layer" ), ret );
            return( ret );
        }

        ret = mbedtls_ssl_handle_message_type( ssl );

    } while( MBEDTLS_ERR_SSL_NON_FATAL == ret );

    if( 0 != ret )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, ( "mbedtls_ssl_handle_message_type" ), ret );
        return( ret );
    }

    ssl->state++;

    /* Process the message contents */
    if( ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE ||
        ssl->in_msg[0] != MBEDTLS_SSL_HS_CERTIFICATE_VERIFY )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate verify message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
    }

    i = mbedtls_ssl_hs_hdr_len( ssl );

    /*
     *  struct {
     *     SignatureAndHashAlgorithm algorithm; -- TLS 1.2 only
     *     opaque signature<0..2^16-1>;
     *  } DigitallySigned;
     */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
    if( ssl->minor_ver != MBEDTLS_SSL_MINOR_VERSION_3 )
    {
        md_alg = MBEDTLS_MD_NONE;
        hashlen = 36;

        /* For ECDSA, use SHA-1, not MD-5 + SHA-1 */
        if( mbedtls_pk_can_do( &ssl->session_negotiate->peer_cert->pk,
                        MBEDTLS_PK_ECDSA ) )
        {
            hash_start += 16;
            hashlen -= 16;
            md_alg = MBEDTLS_MD_SHA1;
        }
    }
    else
#endif /* MBEDTLS_SSL_PROTO_SSL3 || MBEDTLS_SSL_PROTO_TLS1 ||
          MBEDTLS_SSL_PROTO_TLS1_1 */
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
    if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
    {
        if( i + 2 > ssl->in_hslen )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate verify message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
        }

        /*
         * Hash
         */
        md_alg = mbedtls_ssl_md_alg_from_hash( ssl->in_msg[i] );

        if( md_alg == MBEDTLS_MD_NONE || mbedtls_ssl_set_calc_verify_md( ssl, ssl->in_msg[i] ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "peer not adhering to requested sig_alg"
                                " for verify message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
        }

#if !defined(MBEDTLS_MD_SHA1)
        if( MBEDTLS_MD_SHA1 == md_alg )
            hash_start += 16;
#endif

        /* Info from md_alg will be used instead */
        hashlen = 0;

        i++;

        /*
         * Signature
         */
        if( ( pk_alg = mbedtls_ssl_pk_alg_from_sig( ssl->in_msg[i] ) )
                        == MBEDTLS_PK_NONE )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "peer not adhering to requested sig_alg"
                                " for verify message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
        }

        /*
         * Check the certificate's key type matches the signature alg
         */
        if( ! mbedtls_pk_can_do( &ssl->session_negotiate->peer_cert->pk, pk_alg ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "sig_alg doesn't match cert key" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
        }

        i++;
    }
    else
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    if( i + 2 > ssl->in_hslen )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate verify message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
    }

    sig_len = ( ssl->in_msg[i] << 8 ) | ssl->in_msg[i+1];
    i += 2;

    if( i + sig_len != ssl->in_hslen )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate verify message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
    }

    /* Calculate hash and verify signature */
    ssl->handshake->calc_verify( ssl, hash );

    if( ( ret = mbedtls_pk_verify( &ssl->session_negotiate->peer_cert->pk,
                           md_alg, hash_start, hashlen,
                           ssl->in_msg + i, sig_len ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_pk_verify", ret );
        return( ret );
    }

    mbedtls_ssl_update_handshake_status( ssl );

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse certificate verify" ) );

    return( ret );
}
#endif /* !MBEDTLS_KEY_EXCHANGE_RSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED &&
          !MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED */

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
static int ssl_write_new_session_ticket( mbedtls_ssl_context *ssl )
{
    int ret;
    size_t tlen;
    uint32_t lifetime;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write new session ticket" ) );

    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_NEW_SESSION_TICKET;

    /*
     * struct {
     *     uint32 ticket_lifetime_hint;
     *     opaque ticket<0..2^16-1>;
     * } NewSessionTicket;
     *
     * 4  .  7   ticket_lifetime_hint (0 = unspecified)
     * 8  .  9   ticket_len (n)
     * 10 .  9+n ticket content
     */

    if( ( ret = ssl->conf->f_ticket_write( ssl->conf->p_ticket,
                                ssl->session_negotiate,
                                ssl->out_msg + 10,
                                ssl->out_msg + MBEDTLS_SSL_MAX_CONTENT_LEN,
                                &tlen, &lifetime ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_ticket_write", ret );
        tlen = 0;
    }

    ssl->out_msg[4] = ( lifetime >> 24 ) & 0xFF;
    ssl->out_msg[5] = ( lifetime >> 16 ) & 0xFF;
    ssl->out_msg[6] = ( lifetime >>  8 ) & 0xFF;
    ssl->out_msg[7] = ( lifetime       ) & 0xFF;

    ssl->out_msg[8] = (unsigned char)( ( tlen >> 8 ) & 0xFF );
    ssl->out_msg[9] = (unsigned char)( ( tlen      ) & 0xFF );

    ssl->out_msglen = 10 + tlen;

    /*
     * Morally equivalent to updating ssl->state, but NewSessionTicket and
     * ChangeCipherSpec share the same state.
     */
    ssl->handshake->new_session_ticket = 0;

    if( ( ret = mbedtls_ssl_write_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_write_record", ret );
        return( ret );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write new session ticket" ) );

    return( 0 );
}
#endif /* MBEDTLS_SSL_SESSION_TICKETS */

/*
 * SSL handshake -- server side -- single step
 */
int mbedtls_ssl_handshake_server_step( mbedtls_ssl_context *ssl )
{
    int ret = 0;

    if( ssl->state == MBEDTLS_SSL_HANDSHAKE_OVER || ssl->handshake == NULL )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "server state: %d", ssl->state ) );

    if( ( ret = mbedtls_ssl_flush_output( ssl ) ) != 0 )
        return( ret );

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake->retransmit_state == MBEDTLS_SSL_RETRANS_SENDING )
    {
        if( ( ret = mbedtls_ssl_resend( ssl ) ) != 0 )
            return( ret );
    }
#endif

    switch( ssl->state )
    {
        case MBEDTLS_SSL_HELLO_REQUEST:
            ssl->state = MBEDTLS_SSL_CLIENT_HELLO;
            break;

        /*
         *  <==   ClientHello
         */
        case MBEDTLS_SSL_CLIENT_HELLO:
            ret = ssl_parse_client_hello( ssl );
            break;

#if defined(MBEDTLS_SSL_PROTO_DTLS)
        case MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT:
            return( MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED );
#endif

        /*
         *  ==>   ServerHello
         *        Certificate
         *      ( ServerKeyExchange  )
         *      ( CertificateRequest )
         *        ServerHelloDone
         */
        case MBEDTLS_SSL_SERVER_HELLO:
            ret = ssl_write_server_hello( ssl );
            break;

        case MBEDTLS_SSL_SERVER_CERTIFICATE:
            ret = mbedtls_ssl_write_certificate( ssl );
            break;

        case MBEDTLS_SSL_SERVER_KEY_EXCHANGE:
            ret = ssl_write_server_key_exchange( ssl );
            break;

        case MBEDTLS_SSL_CERTIFICATE_REQUEST:
            ret = ssl_write_certificate_request( ssl );
            break;

        case MBEDTLS_SSL_SERVER_HELLO_DONE:
            ret = ssl_write_server_hello_done( ssl );
            break;

        /*
         *  <== ( Certificate/Alert  )
         *        ClientKeyExchange
         *      ( CertificateVerify  )
         *        ChangeCipherSpec
         *        Finished
         */
        case MBEDTLS_SSL_CLIENT_CERTIFICATE:
            ret = mbedtls_ssl_parse_certificate( ssl );
            break;

        case MBEDTLS_SSL_CLIENT_KEY_EXCHANGE:
            ret = ssl_parse_client_key_exchange( ssl );
            break;

        case MBEDTLS_SSL_CERTIFICATE_VERIFY:
            ret = ssl_parse_certificate_verify( ssl );
            break;

        case MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC:
            ret = mbedtls_ssl_parse_change_cipher_spec( ssl );
            break;

        case MBEDTLS_SSL_CLIENT_FINISHED:
            ret = mbedtls_ssl_parse_finished( ssl );
            break;

        /*
         *  ==> ( NewSessionTicket )
         *        ChangeCipherSpec
         *        Finished
         */
        case MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC:
#if defined(MBEDTLS_SSL_SESSION_TICKETS)
            if( ssl->handshake->new_session_ticket != 0 )
                ret = ssl_write_new_session_ticket( ssl );
            else
#endif
                ret = mbedtls_ssl_write_change_cipher_spec( ssl );
            break;

        case MBEDTLS_SSL_SERVER_FINISHED:
            ret = mbedtls_ssl_write_finished( ssl );
            break;

        case MBEDTLS_SSL_FLUSH_BUFFERS:
            MBEDTLS_SSL_DEBUG_MSG( 2, ( "handshake: done" ) );
            ssl->state = MBEDTLS_SSL_HANDSHAKE_WRAPUP;
            break;

        case MBEDTLS_SSL_HANDSHAKE_WRAPUP:
            mbedtls_ssl_handshake_wrapup( ssl );
            break;

        default:
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "invalid state %d", ssl->state ) );
            return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
    }

    return( ret );
}
#endif /* MBEDTLS_SSL_SRV_C */
