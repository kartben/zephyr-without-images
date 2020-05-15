/*
 * Copyright (c) 2020 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_REGISTER(net_txtime_sample, LOG_LEVEL_DBG);

#include <zephyr.h>
#include <errno.h>
#include <stdio.h>
#include <inttypes.h>
#include <ptp_clock.h>
#include <shell/shell.h>

#include <net/net_mgmt.h>
#include <net/net_event.h>
#include <net/net_conn_mgr.h>

#include <net/socket.h>
#include <net/ethernet.h>

#define APP_BANNER "Run SO_TXTIME client"

#define DHCPV4_MASK (NET_EVENT_IPV4_DHCP_BOUND | \
		     NET_EVENT_IPV4_DHCP_STOP)
#define EVENT_MASK (NET_EVENT_L4_CONNECTED | \
		    NET_EVENT_L4_DISCONNECTED)

#define STACK_SIZE 2048
#define THREAD_PRIORITY K_PRIO_COOP(8)
#define WAIT_PERIOD (1 * MSEC_PER_SEC)
#define MAX_MSG_LEN 64

static char txtime_str[MAX_MSG_LEN];

static struct k_sem quit_lock;
static struct net_mgmt_event_callback mgmt_cb;
static struct net_mgmt_event_callback dhcpv4_cb;

struct app_data {
	const struct device *clk;
	struct sockaddr peer;
	socklen_t peer_addr_len;
	int sock;
};

static struct app_data data = {
	.sock = -1,
};

static k_tid_t tx_tid;
static K_THREAD_STACK_DEFINE(tx_stack, STACK_SIZE);
static struct k_thread tx_thread;

static k_tid_t rx_tid;
static K_THREAD_STACK_DEFINE(rx_stack, STACK_SIZE);
static struct k_thread rx_thread;

K_SEM_DEFINE(run_app, 0, 1);
static bool want_to_quit;
static bool connected;

extern int init_vlan(void);

static void quit(void)
{
	k_sem_give(&quit_lock);
}

static void event_handler(struct net_mgmt_event_callback *cb,
			  uint32_t mgmt_event, struct net_if *iface)
{
	static bool dhcpv4_done;

	if (want_to_quit) {
		k_sem_give(&run_app);
		want_to_quit = false;
	}

	if (IS_ENABLED(CONFIG_NET_DHCPV4)) {
		if (mgmt_event == NET_EVENT_IPV4_DHCP_BOUND) {
			LOG_INF("DHCPv4 bound");
			dhcpv4_done = true;

			if (connected) {
				k_sem_give(&run_app);
			}

			return;
		}

		if (mgmt_event == NET_EVENT_IPV4_DHCP_STOP) {
			dhcpv4_done = false;
			return;
		}
	}

	if (mgmt_event == NET_EVENT_L4_CONNECTED) {
		if (!connected) {
			LOG_INF("Network connected");
		}

		connected = true;

		/* Go to connected state only after DHCPv4 is done */
		if (!IS_ENABLED(CONFIG_NET_DHCPV4) || dhcpv4_done) {
			k_sem_give(&run_app);
		}

		return;
	}

	if (mgmt_event == NET_EVENT_L4_DISCONNECTED) {
		if (connected == false) {
			LOG_INF("Waiting network to be connected");
		} else {
			LOG_INF("Network disconnected");
			connected = false;
		}

		k_sem_reset(&run_app);

		return;
	}
}

static void rx(struct app_data *data)
{
	static uint8_t recv_buf[sizeof(txtime_str)];
	struct sockaddr src;
	socklen_t addr_len;
	ssize_t len = 0;

	while (true) {
		len += recvfrom(data->sock, recv_buf, sizeof(recv_buf), 0,
				&src, &addr_len);
		if (!(len % (100 * 1024))) {
			LOG_DBG("Received %zd kb data", len / 1024);
		}
	}
}

static void tx(struct app_data *data)
{
	struct net_ptp_time time;
	struct msghdr msg;
	struct cmsghdr *cmsg;
	struct iovec io_vector[1];
	union {
		struct cmsghdr hdr;
		unsigned char  buf[CMSG_SPACE(sizeof(uint64_t))];
	} cmsgbuf;
	uint64_t txtime, delay, interval;
	int ret;
	int print_offset;

	print_offset = IS_ENABLED(CONFIG_NET_SAMPLE_PACKET_SOCKET) ?
		sizeof(struct net_eth_hdr) : 0;

	interval = CONFIG_NET_SAMPLE_PACKET_INTERVAL * NSEC_PER_USEC *
							USEC_PER_MSEC;
	delay = CONFIG_NET_SAMPLE_PACKET_TXTIME * NSEC_PER_USEC;

	io_vector[0].iov_base = (void *)txtime_str;

	memset(&msg, 0, sizeof(msg));
	msg.msg_control = &cmsgbuf.buf;
	msg.msg_controllen = sizeof(cmsgbuf.buf);
	msg.msg_iov = io_vector;
	msg.msg_iovlen = 1;
	msg.msg_name = &data->peer;
	msg.msg_namelen = data->peer_addr_len;

	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_len = CMSG_LEN(sizeof(txtime));
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_TXTIME;

	LOG_DBG("Sending network packets with SO_TXTIME");

	ptp_clock_get(data->clk, &time);
	txtime = (time.second * NSEC_PER_SEC) + time.nanosecond;

	snprintk(txtime_str + print_offset,
		 sizeof(txtime_str) - print_offset, "%"PRIx64, txtime);
	io_vector[0].iov_len = sizeof(txtime_str);

	while (1) {
		*(uint64_t *)CMSG_DATA(cmsg) = txtime + delay;

		ret = sendmsg(data->sock, &msg, 0);
		if (ret < 0) {
			if (errno != ENOMEM) {
				LOG_DBG("Message send failed (%d)", -errno);
				quit();
				break;
			}
		}

		txtime += interval;
		snprintk(txtime_str + print_offset,
			 sizeof(txtime_str) - print_offset, "%"PRIx64, txtime);

		k_sleep(K_NSEC(interval));
	}
}

static int get_local_ipv6(struct net_if *iface, struct sockaddr *peer,
			  struct sockaddr *local, socklen_t *addrlen)
{
	const struct in6_addr *addr;

	if (peer->sa_family != AF_INET6) {
		return 0;
	}

	addr = net_if_ipv6_select_src_addr(iface, &net_sin6(peer)->sin6_addr);
	if (!addr) {
		LOG_ERR("Cannot get local %s address", "IPv6");
		return -EINVAL;
	}

	memcpy(&net_sin6(local)->sin6_addr, addr, sizeof(*addr));
	local->sa_family = AF_INET6;
	*addrlen = sizeof(struct sockaddr_in6);

	return 0;
}

static int get_local_ipv4(struct net_if *iface, struct sockaddr *peer,
			  struct sockaddr *local, socklen_t *addrlen)
{
	const struct in_addr *addr;

	if (peer->sa_family != AF_INET) {
		return 0;
	}

	addr = net_if_ipv4_select_src_addr(iface, &net_sin(peer)->sin_addr);
	if (!addr) {
		LOG_ERR("Cannot get local %s address", "IPv4");
		return -EINVAL;
	}

	memcpy(&net_sin(local)->sin_addr, addr, sizeof(*addr));
	local->sa_family = AF_INET;
	*addrlen = sizeof(struct sockaddr_in);

	return 0;
}

static int create_socket(struct net_if *iface, struct sockaddr *peer)
{
	struct sockaddr local;
	socklen_t addrlen;
	bool optval;
	uint8_t priority;
	int sock;
	int ret;

	memset(&local, 0, sizeof(local));

	if (IS_ENABLED(CONFIG_NET_SAMPLE_PACKET_SOCKET)) {
		struct sockaddr_ll *addr;

		sock = socket(AF_PACKET, SOCK_RAW, ETH_P_ALL);
		if (sock < 0) {
			LOG_ERR("Cannot create %s socket (%d)", "packet",
				-errno);
			return -errno;
		}

		addr = (struct sockaddr_ll *)&local;
		addr->sll_ifindex = net_if_get_by_iface(net_if_get_default());
		addr->sll_family = AF_PACKET;
		addrlen = sizeof(struct sockaddr_ll);

		LOG_DBG("Binding to interface %d (%p)", addr->sll_ifindex,
			net_if_get_by_index(addr->sll_ifindex));
	}

	if (IS_ENABLED(CONFIG_NET_SAMPLE_UDP_SOCKET)) {
		char addr_str[INET6_ADDRSTRLEN];

		sock = socket(peer->sa_family, SOCK_DGRAM, IPPROTO_UDP);
		if (sock < 0) {
			LOG_ERR("Cannot create %s socket (%d)", "UDP", -errno);
			return -errno;
		}

		if (IS_ENABLED(CONFIG_NET_IPV6) &&
		    peer->sa_family == AF_INET6) {
			ret = get_local_ipv6(iface, peer, &local, &addrlen);
			if (ret < 0) {
				return ret;
			}

			net_addr_ntop(AF_INET6, &net_sin6(&local)->sin6_addr,
				      addr_str, sizeof(addr_str));
		} else if (IS_ENABLED(CONFIG_NET_IPV4) &&
			   peer->sa_family == AF_INET) {
			ret = get_local_ipv4(iface, peer, &local, &addrlen);
			if (ret < 0) {
				return ret;
			}

			net_addr_ntop(AF_INET, &net_sin(&local)->sin_addr,
				      addr_str, sizeof(addr_str));
		} else {
			LOG_ERR("Invalid socket family %d", peer->sa_family);
			return -EINVAL;
		}

		LOG_DBG("Binding to %s", log_strdup(addr_str));
	}

	ret = bind(sock, &local, addrlen);
	if (ret < 0) {
		LOG_ERR("Cannot bind socket (%d)", -errno);
		return -errno;
	}

	optval = true;
	ret = setsockopt(sock, SOL_SOCKET, SO_TXTIME, &optval, sizeof(optval));
	if (ret < 0) {
		LOG_ERR("Cannot set SO_TXTIME (%d)", -errno);
		return -errno;
	}

	priority = NET_PRIORITY_CA;
	ret = setsockopt(sock, SOL_SOCKET, SO_PRIORITY, &priority,
			 sizeof(priority));
	if (ret < 0) {
		LOG_ERR("Cannot set SO_PRIORITY (%d)", -errno);
		return -errno;
	}

	return sock;
}

static int get_peer_address(struct net_if **iface, char *addr_str,
			    int addr_str_len)
{
	int ret;

	ret = net_ipaddr_parse(CONFIG_NET_SAMPLE_PEER,
			       strlen(CONFIG_NET_SAMPLE_PEER),
			       &data.peer);
	if (!ret) {
		LOG_ERR("Cannot parse '%s'", CONFIG_NET_SAMPLE_PEER);
		return -EINVAL;
	}

	if (net_sin(&data.peer)->sin_port == 0) {
		net_sin(&data.peer)->sin_port = htons(4242);
	}

	if (IS_ENABLED(CONFIG_NET_IPV6) &&
					data.peer.sa_family == AF_INET6) {
		*iface = net_if_ipv6_select_src_iface(
					&net_sin6(&data.peer)->sin6_addr);

		net_addr_ntop(data.peer.sa_family,
			      &net_sin6(&data.peer)->sin6_addr, addr_str,
			      addr_str_len);
		data.peer_addr_len = sizeof(struct sockaddr_in6);

	} else if (IS_ENABLED(CONFIG_NET_IPV4) &&
					data.peer.sa_family == AF_INET) {
		*iface = net_if_ipv4_select_src_iface(
					&net_sin(&data.peer)->sin_addr);

		net_addr_ntop(data.peer.sa_family,
			      &net_sin(&data.peer)->sin_addr, addr_str,
			      addr_str_len);
		data.peer_addr_len = sizeof(struct sockaddr_in);
	}

	return 0;
}

static int cmd_sample_quit(const struct shell *shell,
			  size_t argc, char *argv[])
{
	want_to_quit = true;

	quit();

	net_conn_mgr_resend_status();

	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sample_commands,
	SHELL_CMD(quit, NULL,
		  "Quit the sample application\n",
		  cmd_sample_quit),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sample, &sample_commands,
		   "Sample application commands", NULL);

void main(void)
{
	struct net_if *iface = NULL;
	char addr_str[INET6_ADDRSTRLEN];
	enum ethernet_hw_caps caps;
	int ret, if_index;

	LOG_INF(APP_BANNER);

	k_sem_init(&quit_lock, 0, UINT_MAX);

	if (IS_ENABLED(CONFIG_NET_CONNECTION_MANAGER)) {
		net_mgmt_init_event_callback(&mgmt_cb,
					     event_handler, EVENT_MASK);
		net_mgmt_add_event_callback(&mgmt_cb);

		if (IS_ENABLED(CONFIG_NET_DHCPV4)) {
			net_mgmt_init_event_callback(&dhcpv4_cb,
						     event_handler,
						     DHCPV4_MASK);
			net_mgmt_add_event_callback(&dhcpv4_cb);
		}

		net_conn_mgr_resend_status();
	}

	/* The VLAN in this example is created for demonstration purposes.
	 */
	if (IS_ENABLED(CONFIG_NET_VLAN)) {
		ret = init_vlan();
		if (ret < 0) {
			LOG_WRN("Cannot setup VLAN (%d)", ret);
		}
	}

	/* Wait for the connection. */
	k_sem_take(&run_app, K_FOREVER);

	if (IS_ENABLED(CONFIG_NET_SAMPLE_UDP_SOCKET)) {
		ret = get_peer_address(&iface, addr_str, sizeof(addr_str));
		if (ret < 0) {
			return;
		}
	} else {
		struct sockaddr_ll *addr = (struct sockaddr_ll *)&data.peer;

		addr->sll_ifindex = net_if_get_by_iface(net_if_get_default());
		addr->sll_family = AF_PACKET;
		data.peer_addr_len = sizeof(struct sockaddr_ll);
		iface = net_if_get_by_index(addr->sll_ifindex);
	}

	if (!iface) {
		LOG_ERR("Cannot get local network interface!");
		return;
	}

	if_index = net_if_get_by_iface(iface);

	caps = net_eth_get_hw_capabilities(iface);
	if (!(caps & ETHERNET_PTP)) {
		LOG_ERR("Interface %p does not support %s", iface, "PTP");
		return;
	}

	data.clk = net_eth_get_ptp_clock_by_index(if_index);
	if (!data.clk) {
		LOG_ERR("Interface %p does not support %s", iface,
			"PTP clock");
		return;
	}

	if (IS_ENABLED(CONFIG_NET_SAMPLE_UDP_SOCKET)) {
		LOG_INF("Socket SO_TXTIME sample to %s port %d using "
			"interface %d (%p) and PTP clock %p",
			log_strdup(addr_str),
			ntohs(net_sin(&data.peer)->sin_port),
			if_index, iface, data.clk);
	}

	if (IS_ENABLED(CONFIG_NET_SAMPLE_PACKET_SOCKET)) {
		LOG_INF("Socket SO_TXTIME sample using AF_PACKET and "
			"interface %d (%p) and PTP clock %p",
			if_index, iface, data.clk);
	}

	data.sock = create_socket(iface, &data.peer);
	if (data.sock < 0) {
		LOG_ERR("Cannot create socket (%d)", data.sock);
		return;
	}

	tx_tid = k_thread_create(&tx_thread, tx_stack,
				 K_THREAD_STACK_SIZEOF(tx_stack),
				 (k_thread_entry_t)tx, &data,
				 NULL, NULL, THREAD_PRIORITY, 0,
				 K_FOREVER);
	if (!tx_tid) {
		LOG_ERR("Cannot create TX thread!");
		return;
	}

	k_thread_name_set(tx_tid, "TX");

	rx_tid = k_thread_create(&rx_thread, rx_stack,
				 K_THREAD_STACK_SIZEOF(rx_stack),
				 (k_thread_entry_t)rx, &data,
				 NULL, NULL, THREAD_PRIORITY, 0,
				 K_FOREVER);
	if (!rx_tid) {
		LOG_ERR("Cannot create RX thread!");
		return;
	}

	k_thread_name_set(rx_tid, "RX");

	k_thread_start(rx_tid);
	k_thread_start(tx_tid);

	k_sem_take(&quit_lock, K_FOREVER);

	LOG_INF("Stopping...");

	k_thread_abort(tx_tid);
	k_thread_abort(rx_tid);

	if (data.sock >= 0) {
		(void)close(data.sock);
	}
}
