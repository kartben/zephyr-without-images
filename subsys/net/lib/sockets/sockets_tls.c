/*
 * Copyright (c) 2018 Intel Corporation
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_NET_DEBUG_SOCKETS)
#define SYS_LOG_DOMAIN "net/tls"
#define NET_LOG_ENABLED 1
#endif

#include <stdbool.h>

#include <init.h>
#include <net/net_context.h>
#include <net/socket.h>

#if defined(CONFIG_MBEDTLS)
#if !defined(CONFIG_MBEDTLS_CFG_FILE)
#include "mbedtls/config.h"
#else
#include CONFIG_MBEDTLS_CFG_FILE
#endif /* CONFIG_MBEDTLS_CFG_FILE */

#include <mbedtls/ctr_drbg.h>
#include <mbedtls/net_sockets.h>
#include <mbedtls/x509.h>
#include <mbedtls/x509_crt.h>
#include <mbedtls/ssl.h>
#include <mbedtls/error.h>
#include <mbedtls/debug.h>
#endif /* CONFIG_MBEDTLS */

/** TLS context information. */
struct tls_context {
	/** Information whether TLS context is used. */
	bool is_used;

	/** Secure protocol version running on TLS context. */
	enum net_ip_protocol_secure tls_version;

	/** Socket flags passed to a socket call. */
	int flags;

#if defined(CONFIG_MBEDTLS)
	/** mbedTLS context. */
	mbedtls_ssl_context ssl;

	/** mbedTLS configuration. */
	mbedtls_ssl_config config;
#endif /* CONFIG_MBEDTLS */
};

static mbedtls_ctr_drbg_context tls_ctr_drbg;

/* A global pool of TLS contexts. */
static struct tls_context tls_contexts[CONFIG_NET_SOCKETS_TLS_MAX_CONTEXTS];

/* A mutex for protecting TLS context allocation. */
static struct k_mutex context_lock;

#if defined(MBEDTLS_DEBUG_C) && defined(CONFIG_NET_DEBUG_SOCKETS)
static void tls_debug(void *ctx, int level, const char *file,
		      int line, const char *str)
{
	const char *p, *basename;

	ARG_UNUSED(ctx);

	if (!file || !str) {
		return;
	}

	/* Extract basename from file */
	for (p = basename = file; *p != '\0'; p++) {
		if (*p == '/' || *p == '\\') {
			basename = p + 1;
		}
	}

	NET_DBG("%s:%04d: |%d| %s", basename, line, level, str);
}
#endif /* defined(MBEDTLS_DEBUG_C) && defined(CONFIG_NET_TLS_DEBUG) */

#if defined(CONFIG_ENTROPY_HAS_DRIVER)
static int tls_entropy_func(void *ctx, unsigned char *buf, size_t len)
{
	return entropy_get_entropy(ctx, buf, len);
}
#else
static int tls_entropy_func(void *ctx, unsigned char *buf, size_t len)
{
	ARG_UNUSED(ctx);

	size_t i = len / 4;
	u32_t val;

	while (i--) {
		val = sys_rand32_get();
		UNALIGNED_PUT(val, (u32_t *)buf);
		buf += 4;
	}

	i = len & 0x3;
	val = sys_rand32_get();
	while (i--) {
		*buf++ = val;
		val >>= 8;
	}

	return 0;
}
#endif /* defined(CONFIG_ENTROPY_HAS_DRIVER) */

/* Initialize TLS internals. */
static int tls_init(struct device *unused)
{
	ARG_UNUSED(unused);

	int ret;
	static const unsigned char drbg_seed[] = "zephyr";
	struct device *dev = NULL;

#if defined(CONFIG_ENTROPY_HAS_DRIVER)
	dev = device_get_binding(CONFIG_ENTROPY_NAME);

	if (!dev) {
		NET_ERR("Failed to obtain entropy device");
		return -ENODEV;
	}
#else
	NET_WARN("No entropy device on the system, "
		 "TLS communication may be insecure!");
#endif /* defined(CONFIG_ENTROPY_HAS_DRIVER) */

	memset(tls_contexts, 0, sizeof(tls_contexts));

	k_mutex_init(&context_lock);

	mbedtls_ctr_drbg_init(&tls_ctr_drbg);

	ret = mbedtls_ctr_drbg_seed(&tls_ctr_drbg, tls_entropy_func, dev,
				    drbg_seed, sizeof(drbg_seed));
	if (ret != 0) {
		mbedtls_ctr_drbg_free(&tls_ctr_drbg);
		NET_ERR("TLS entropy source initialization failed");
		return -EFAULT;
	}

#if defined(MBEDTLS_DEBUG_C) && defined(CONFIG_NET_DEBUG_SOCKETS)
	mbedtls_debug_set_threshold(CONFIG_MBEDTLS_DEBUG_LEVEL);
#endif

	return 0;
}

SYS_INIT(tls_init, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);

/* Allocate TLS context. */
static struct tls_context *tls_alloc(void)
{
	int i;
	struct tls_context *tls = NULL;

	k_mutex_lock(&context_lock, K_FOREVER);

	for (i = 0; i < ARRAY_SIZE(tls_contexts); i++) {
		if (!tls_contexts[i].is_used) {
			tls = &tls_contexts[i];
			memset(tls, 0, sizeof(*tls));
			tls->is_used = true;

			NET_DBG("Allocated TLS context, %p", tls);
			break;
		}
	}

	k_mutex_unlock(&context_lock);

	if (tls) {
		mbedtls_ssl_init(&tls->ssl);
		mbedtls_ssl_config_init(&tls->config);

#if defined(MBEDTLS_DEBUG_C) && defined(CONFIG_NET_DEBUG_SOCKETS)
		mbedtls_ssl_conf_dbg(&tls->config, tls_debug, NULL);
#endif
	} else {
		NET_WARN("Failed to allocate TLS context");
	}

	return tls;
}

/* Allocate new TLS context and copy the content from the source context. */
static struct tls_context *tls_clone(struct tls_context *source_tls)
{
	struct tls_context *target_tls;

	target_tls = tls_alloc();
	if (!target_tls) {
		return NULL;
	}

	target_tls->tls_version = source_tls->tls_version;

	return target_tls;
}

/* Release TLS context. */
static int tls_release(struct tls_context *tls)
{
	if (!PART_OF_ARRAY(tls_contexts, tls)) {
		NET_ERR("Invalid TLS context");
		return -EBADF;
	}

	if (!tls->is_used) {
		NET_ERR("Deallocating unused TLS context");
		return -EBADF;
	}

	mbedtls_ssl_config_free(&tls->config);
	mbedtls_ssl_free(&tls->ssl);

	tls->is_used = false;

	return 0;
}

static int tls_tx(void *ctx, const unsigned char *buf, size_t len)
{
	int sock = POINTER_TO_INT(ctx);
	ssize_t sent;

	sent = zsock_sendto(sock, buf, len,
			    ((struct net_context *)ctx)->tls->flags,
			    NULL, 0);
	if (sent < 0) {
		if (errno == EAGAIN) {
			return MBEDTLS_ERR_SSL_WANT_WRITE;
		}

		return MBEDTLS_ERR_NET_SEND_FAILED;
	}

	return sent;
}

static int tls_rx(void *ctx, unsigned char *buf, size_t len)
{
	int sock = POINTER_TO_INT(ctx);
	ssize_t received;

	received = zsock_recvfrom(sock, buf, len,
				  ((struct net_context *)ctx)->tls->flags,
				  NULL, 0);
	if (received < 0) {
		if (errno == EAGAIN) {
			return MBEDTLS_ERR_SSL_WANT_READ;
		}

		return MBEDTLS_ERR_NET_RECV_FAILED;
	}

	return received;
}

static int tls_mbedtls_set_credentials(struct tls_context *tls)
{
	/* TODO Temporary solution to verify communication */
	mbedtls_ssl_conf_authmode(&tls->config, MBEDTLS_SSL_VERIFY_NONE);

	return 0;
}

static int tls_mbedtls_handshake(struct net_context *context)
{
	int ret;

	/* We do not want to use any socket flags during the handshake. */
	context->tls->flags = 0;

	/* TODO For simplicity, TLS handshake blocks the socket even for
	 * non-blocking socket. Non-blocking behavior for handshake can
	 * be implemented later.
	 */
	while ((ret = mbedtls_ssl_handshake(&context->tls->ssl)) != 0) {
		if (ret == MBEDTLS_ERR_SSL_WANT_READ ||
		    ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
			continue;
		}

		NET_ERR("TLS handshake error: -%x", -ret);
		ret = -ECONNABORTED;
		break;
	}

	return ret;
}

static int tls_mbedtls_init(struct net_context *context, bool is_server)
{
	int role, type, ret;

	role = is_server ? MBEDTLS_SSL_IS_SERVER : MBEDTLS_SSL_IS_CLIENT;

	type = (net_context_get_type(context) == SOCK_STREAM) ?
		MBEDTLS_SSL_TRANSPORT_STREAM :
		MBEDTLS_SSL_TRANSPORT_DATAGRAM;

	mbedtls_ssl_set_bio(&context->tls->ssl, context, tls_tx, tls_rx, NULL);

	ret = mbedtls_ssl_config_defaults(&context->tls->config, role, type,
					  MBEDTLS_SSL_PRESET_DEFAULT);
	if (ret != 0) {
		/* According to mbedTLS API documentation,
		 * mbedtls_ssl_config_defaults can fail due to memory
		 * allocation failure
		 */
		return -ENOMEM;
	}

	mbedtls_ssl_conf_rng(&context->tls->config,
			     mbedtls_ctr_drbg_random,
			     &tls_ctr_drbg);

	ret = tls_mbedtls_set_credentials(context->tls);
	if (ret != 0) {
		return ret;
	}

	ret = mbedtls_ssl_setup(&context->tls->ssl,
				&context->tls->config);
	if (ret != 0) {
		/* According to mbedTLS API documentation,
		 * mbedtls_ssl_setup can fail due to memory allocation failure
		 */
		return -ENOMEM;
	}

	return 0;
}

int ztls_socket(int family, int type, int proto)
{
	enum net_ip_protocol_secure tls_proto = 0;
	int sock, ret, err;

	if (proto  >= IPPROTO_TLS_1_0 && proto <= IPPROTO_TLS_1_2) {
		/* Currently DTLS is not supported,
		 * so do not allow to create datagram socket
		 */
		if (type == SOCK_DGRAM) {
			errno = ENOTSUP;
			return -1;
		}

		tls_proto = proto;
		proto = (type == SOCK_STREAM) ? IPPROTO_TCP : IPPROTO_UDP;
	}

	sock = zsock_socket(family, type, proto);
	if (sock < 0) {
		/* errno will be propagated */
		return -1;
	}

	if (tls_proto != 0) {
		/* If TLS protocol is used, allocate TLS context */
		struct net_context *context = INT_TO_POINTER(sock);

		context->tls = tls_alloc();

		if (!context->tls) {
			ret = -ENOMEM;
			goto error;
		}

		context->tls->tls_version = tls_proto;
	}

	return sock;

error:
	err = zsock_close(sock);
	__ASSERT(err == 0, "Socket close failed");

	errno = -ret;
	return -1;
}

int ztls_close(int sock)
{
	struct net_context *context = INT_TO_POINTER(sock);
	int ret, err = 0;

	if (context->tls) {
		/* Try to send close notification. */
		context->tls->flags = 0;
		(void)mbedtls_ssl_close_notify(&context->tls->ssl);

		err = tls_release(context->tls);
	}

	ret = zsock_close(sock);

	/* In case zsock_close fails, we propagate errno value set by
	 * zsock_close.
	 * In case zsock_close succeeds, but tls_release fails, set errno
	 * according to tls_release return value.
	 */
	if (ret == 0 && err < 0) {
		errno = -err;
		ret = -1;
	}

	return ret;
}

int ztls_bind(int sock, const struct sockaddr *addr, socklen_t addrlen)
{
	/* No extra action needed here. */
	return zsock_bind(sock, addr, addrlen);
}

int ztls_connect(int sock, const struct sockaddr *addr, socklen_t addrlen)
{
	int ret;
	struct net_context *context = INT_TO_POINTER(sock);

	ret = zsock_connect(sock, addr, addrlen);
	if (ret < 0) {
		/* errno will be propagated */
		return -1;
	}

	if (context->tls) {
		ret = tls_mbedtls_init(context, false);
		if (ret < 0) {
			goto error;
		}

		ret = tls_mbedtls_handshake(context);
		if (ret < 0) {
			goto error;
		}
	}

	return 0;

error:
	errno = -ret;
	return -1;
}

int ztls_listen(int sock, int backlog)
{
	/* No extra action needed here. */
	return zsock_listen(sock, backlog);
}

int ztls_accept(int sock, struct sockaddr *addr, socklen_t *addrlen)
{
	int child_sock, ret, err;
	struct net_context *parent_context = INT_TO_POINTER(sock);
	struct net_context *child_context = NULL;

	child_sock = zsock_accept(sock, addr, addrlen);
	if (child_sock < 0) {
		/* errno will be propagated */
		return -1;
	}

	if (parent_context->tls) {
		child_context = INT_TO_POINTER(child_sock);

		child_context->tls = tls_clone(parent_context->tls);
		if (!child_context->tls) {
			ret = -ENOMEM;
			goto error;
		}

		ret = tls_mbedtls_init(child_context, true);
		if (ret < 0) {
			goto error;
		}

		ret = tls_mbedtls_handshake(child_context);
		if (ret < 0) {
			goto error;
		}
	}

	return child_sock;

error:
	if (child_context && child_context->tls) {
		err = tls_release(child_context->tls);
		__ASSERT(err == 0, "TLS context release failed");
	}

	err = zsock_close(child_sock);
	__ASSERT(err == 0, "Child socket close failed");

	errno = -ret;
	return -1;
}

ssize_t ztls_send(int sock, const void *buf, size_t len, int flags)
{
	return ztls_sendto(sock, buf, len, flags, NULL, 0);
}

ssize_t ztls_recv(int sock, void *buf, size_t max_len, int flags)
{
	return ztls_recvfrom(sock, buf, max_len, flags, NULL, 0);
}

ssize_t ztls_sendto(int sock, const void *buf, size_t len, int flags,
		    const struct sockaddr *dest_addr, socklen_t addrlen)
{
	struct net_context *context = INT_TO_POINTER(sock);
	int ret;

	if (!context->tls) {
		return zsock_sendto(sock, buf, len, flags, dest_addr, addrlen);
	}

	context->tls->flags = flags;

	ret = mbedtls_ssl_write(&context->tls->ssl, buf, len);
	if (ret >= 0) {
		return ret;
	}

	if (ret == MBEDTLS_ERR_SSL_WANT_READ ||
	    ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
		errno = EAGAIN;
		return -1;
	}

	errno = EIO;
	return -1;
}

ssize_t ztls_recvfrom(int sock, void *buf, size_t max_len, int flags,
		      struct sockaddr *src_addr, socklen_t *addrlen)
{
	struct net_context *context = INT_TO_POINTER(sock);
	int ret;

	if (!context->tls) {
		return zsock_recvfrom(sock, buf, max_len, flags,
				      src_addr, addrlen);
	}

	if (flags & ZSOCK_MSG_PEEK) {
		/* TODO mbedTLS does not support 'peeking' This could be
		 * bypassed by having intermediate buffer for peeking
		 */
		errno = ENOTSUP;
		return -1;
	}

	context->tls->flags = flags;

	ret = mbedtls_ssl_read(&context->tls->ssl, buf, max_len);
	if (ret >= 0) {
		return ret;
	}

	if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
		/* Peer notified that it's closing the connection. */
		return 0;
	}

	if (ret == MBEDTLS_ERR_SSL_CLIENT_RECONNECT) {
		/* Client reconnect on the same socket is not
		 * supported. See mbedtls_ssl_read API documentation.
		 */
		return 0;
	}

	if (ret == MBEDTLS_ERR_SSL_WANT_READ ||
	    ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
		errno = EAGAIN;
		return -1;
	}

	errno = EIO;
	return -1;
}

int ztls_fcntl(int sock, int cmd, int flags)
{
	/* No extra action needed here. */
	return zsock_fcntl(sock, cmd, flags);
}

int ztls_poll(struct zsock_pollfd *fds, int nfds, int timeout)
{
	bool has_mbedtls_data = false;
	struct zsock_pollfd *pfd;
	struct net_context *context;
	int i, ret;

	/* There might be some decrypted but unread data pending on mbedTLS,
	 * check for that.
	 */
	for (pfd = fds, i = nfds; i--; pfd++) {
		/* Per POSIX, negative fd's are just ignored */
		if (pfd->fd < 0) {
			continue;
		}

		if (pfd->events & ZSOCK_POLLIN) {
			context = INT_TO_POINTER(pfd->fd);
			if (!context->tls) {
				continue;
			}

			if (mbedtls_ssl_get_bytes_avail(
					&context->tls->ssl) > 0) {
				has_mbedtls_data = true;
				break;
			}
		}
	}

	/* If there is no data waiting on any of mbedTLS contexts,
	 * just do regular poll.
	 */
	if (!has_mbedtls_data) {
		return zsock_poll(fds, nfds, timeout);
	}

	/* Otherwise, poll with no timeout, and update respective revents. */
	ret = zsock_poll(fds, nfds, K_NO_WAIT);
	if (ret < 0) {
		/* errno will be propagated */
		return -1;
	}

	/* Another pass, this time updating revents. */
	for (pfd = fds, i = nfds; i--; pfd++) {
		/* Per POSIX, negative fd's are just ignored */
		if (pfd->fd < 0) {
			continue;
		}

		if (pfd->events & ZSOCK_POLLIN) {
			context = INT_TO_POINTER(pfd->fd);
			if (!context->tls) {
				continue;
			}

			if (mbedtls_ssl_get_bytes_avail(
					&context->tls->ssl) > 0) {
				if (pfd->revents == 0) {
					ret++;
				}

				pfd->revents |= ZSOCK_POLLIN;
			}
		}
	}

	return ret;
}
