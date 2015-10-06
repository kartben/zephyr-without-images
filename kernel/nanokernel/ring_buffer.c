/* ring_buffer.c: Simple ring buffer API */

/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <misc/ring_buffer.h>

/**
 * Internal data structure for a buffer header.
 *
 * We want all of this to fit in a single uint32_t. Every item stored in the
 * ring buffer will be one of these headers plus any extra data supplied
 */
struct ring_element {
	uint32_t  type   :16; /**< Application-specific */
	uint32_t  length :8;  /**< length in 32-bit chunks */
	uint32_t  value  :8;  /**< Room for small integral values */
};

int sys_ring_buf_put(struct ring_buf *buf, uint16_t type, uint8_t value,
		     uint32_t *data, uint8_t size32)
{
	uint32_t i, space, index, rc;

	space = sys_ring_buf_space_get(buf);
	if (space >= (size32 + 1)) {
		struct ring_element *header =
				(struct ring_element *)&buf->buf[buf->tail];
		header->type = type;
		header->length = size32;
		header->value = value;

		if (likely(buf->mask)) {
			for (i=0; i < size32; ++i) {
				index = (i + buf->tail + 1) & buf->mask;
				buf->buf[index] = data[i];
			}
			buf->tail = (buf->tail + size32 + 1) & buf->mask;
		} else {
			for (i=0; i < size32; ++i) {
				index = (i + buf->tail + 1) % buf->size;
				buf->buf[index] = data[i];
			}
			buf->tail = (buf->tail + size32 + 1) % buf->size;
		}
		rc = 0;
	} else {
		buf->dropped_put_count++;
		rc = -EMSGSIZE;
	}

	return rc;
}

int sys_ring_buf_get(struct ring_buf *buf, uint16_t *type, uint8_t *value,
		     uint32_t *data, uint8_t *size32)
{
	struct ring_element *header;
	uint32_t i, index;

	if (sys_ring_buf_is_empty(buf)) {
		return -EAGAIN;
	}

	header = (struct ring_element *) &buf->buf[buf->head];

	if (header->length > *size32) {
		*size32 = header->length;
		return -EMSGSIZE;
	}

	*size32 = header->length;
	*type = header->type;
	*value = header->value;

	if (likely(buf->mask)) {
		for (i = 0; i < header->length; ++i) {
			index = (i + buf->head + 1) & buf->mask;
			data[i] = buf->buf[index];
		}
		buf->head = (buf->head + header->length + 1) & buf->mask;
	} else {
		for (i = 0; i < header->length; ++i) {
			index = (i + buf->head + 1) % buf->size;
			data[i] = buf->buf[index];
		}
		buf->head = (buf->head + header->length + 1) % buf->size;
	}

	return 0;
}

