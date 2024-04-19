/*
 * Copyright (c) 2023 Nordic Semiconductor ASA.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(wifi_nm, CONFIG_WIFI_NM_LOG_LEVEL);

#include <zephyr/kernel.h>
#include <zephyr/net/wifi_nm.h>

/* Used to protect nm data */
static K_MUTEX_DEFINE(wifi_nm_lock);

struct wifi_nm_instance *wifi_nm_get_instance(const char *name)
{
	STRUCT_SECTION_FOREACH(wifi_nm_instance, nm) {
		if (!strcmp(nm->name, name)) {
			return nm;
		}
	}

	return NULL;
}

struct wifi_nm_instance *wifi_nm_get_instance_iface(struct net_if *iface)
{
	if (!iface || !net_if_is_wifi(iface)) {
		return false;
	}

	k_mutex_lock(&wifi_nm_lock, K_FOREVER);
	STRUCT_SECTION_FOREACH(wifi_nm_instance, nm) {
		for (int i = 0; i < CONFIG_WIFI_NM_MAX_MANAGED_INTERFACES; i++) {
			if (nm->mgd_ifaces[i] == iface) {
				k_mutex_unlock(&wifi_nm_lock);
				return nm;
			}
		}
	}
	k_mutex_unlock(&wifi_nm_lock);

	return NULL;
}

int wifi_nm_register_mgd_iface(struct wifi_nm_instance *nm, struct net_if *iface)
{
	if (!nm || !iface) {
		return -EINVAL;
	}

	if (!net_if_is_wifi(iface)) {
		return -ENOTSUP;
	}

	k_mutex_lock(&wifi_nm_lock, K_FOREVER);
	for (int i = 0; i < CONFIG_WIFI_NM_MAX_MANAGED_INTERFACES; i++) {
		if (!nm->mgd_ifaces[i]) {
			nm->mgd_ifaces[i] = iface;
			k_mutex_unlock(&wifi_nm_lock);
			return 0;
		}
	}
	k_mutex_unlock(&wifi_nm_lock);

	return -ENOMEM;
}

int wifi_nm_unregister_mgd_iface(struct wifi_nm_instance *nm, struct net_if *iface)
{
	if (!nm || !iface) {
		return -EINVAL;
	}

	k_mutex_lock(&wifi_nm_lock, K_FOREVER);
	for (int i = 0; i < CONFIG_WIFI_NM_MAX_MANAGED_INTERFACES; i++) {
		if (nm->mgd_ifaces[i] == iface) {
			nm->mgd_ifaces[i] = NULL;
			k_mutex_unlock(&wifi_nm_lock);
			return 0;
		}
	}
	k_mutex_unlock(&wifi_nm_lock);

	return -ENOENT;
}
