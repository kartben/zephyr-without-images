/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef LWM2M_OBSERVATION_H
#define LWM2M_OBSERVATION_H
#include "lwm2m_object.h"

int lwm2m_notify_observer(uint16_t obj_id, uint16_t obj_inst_id, uint16_t res_id);
int lwm2m_notify_observer_path(struct lwm2m_obj_path *path);

#define MAX_TOKEN_LEN		8

struct observe_node {
	sys_snode_t node;
	sys_slist_t path_list;		/* List of Observation path */
	uint8_t token[MAX_TOKEN_LEN];	/* Observation Token */
	int64_t event_timestamp;	/* Timestamp for trig next Notify  */
	int64_t last_timestamp;		/* Timestamp from last Notify */
	uint32_t counter;
	uint16_t format;
	uint8_t  tkl;
	bool resource_update : 1;	/* Resource is updated */
	bool composite : 1;		/* Composite Observation */
	bool active_tx_operation : 1;	/* Active Notification  process ongoing */
};
/* Attribute handling. */

struct lwm2m_attr *lwm2m_engine_get_next_attr(const void *ref,
					      struct lwm2m_attr *prev);
const char *lwm2m_engine_get_attr_name(const struct lwm2m_attr *attr);

void clear_attrs(void *ref);

/**/

int64_t engine_observe_shedule_next_event(struct observe_node *obs, uint16_t srv_obj_inst,
						 const int64_t timestamp);

void remove_observer_from_list(struct lwm2m_ctx *ctx, sys_snode_t *prev_node,
				      struct observe_node *obs);

struct observe_node *engine_observe_node_discover(sys_slist_t *observe_node_list,
							sys_snode_t **prev_node,
							sys_slist_t *lwm2m_path_list,
							const uint8_t *token, uint8_t tkl);

int engine_remove_observer_by_token(struct lwm2m_ctx *ctx, const uint8_t *token, uint8_t tkl);

int lwm2m_write_attr_handler(struct lwm2m_engine_obj *obj,
				    struct lwm2m_message *msg);

int lwm2m_engine_observation_handler(struct lwm2m_message *msg, int observe, uint16_t accept,
					    bool composite);

void engine_remove_observer_by_id(uint16_t obj_id, int32_t obj_inst_id);

/* Resources */
sys_slist_t *lwm2m_obs_obj_path_list(void);

#endif /* LWM2M_OBSERVATION_H */
