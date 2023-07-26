/*
 * Copyright (c) 2023, Meta
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "_main.h"

#undef read
#define read(fd, buf, len) zsock_recv(fd, buf, len, 0)

#undef write
#define write(fd, buf, len) zsock_send(fd, buf, len, 0)

ZTEST(net_socketpair, test_ioctl_fionread)
{
	int sv[2];
	int avail;
	uint8_t byte;

	zassert_ok(socketpair(AF_UNIX, SOCK_STREAM, 0, sv));

	/* both ends should have zero bytes available after being newly created */
	for (int i = 0; i < 2; ++i) {
		avail = 42;
		zassert_ok(ioctl(sv[i], ZFD_IOCTL_FIONREAD, &avail));
		zassert_equal(avail, 0);
	}

	/* write something to one end, check availability from the other end */
	for (int i = 0; i < 2; ++i) {
		int j = (i + 1) % 2;

		zassert_equal(1, write(sv[i], "\x42", 1));
		zassert_ok(ioctl(sv[j], ZFD_IOCTL_FIONREAD, &avail));
		zassert_equal(avail, 1);
	}

	/* read the other end, ensure availability is zero again */
	for (int i = 0; i < 2; ++i) {
		zassert_equal(1, read(sv[i], &byte, 1));
		zassert_ok(ioctl(sv[i], ZFD_IOCTL_FIONREAD, &avail));
		zassert_equal(avail, 0);
	}

	close(sv[0]);
	close(sv[1]);
}
