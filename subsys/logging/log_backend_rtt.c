/*
 * Copyright (c) 2018 omSquare s.r.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log_backend.h>
#include <logging/log_core.h>
#include <logging/log_msg.h>
#include <logging/log_output.h>
#include <rtt/SEGGER_RTT.h>


#if CONFIG_LOG_BACKEND_RTT_MODE_DROP

#define DROP_MESSAGE "\nmessages dropped: 99 \r"
#define DROP_MESSAGE_LEN (sizeof(DROP_MESSAGE) - 1)
static const char *drop_msg = DROP_MESSAGE;
static int drop_cnt = 0;
static int drop_warn = 0;

#else

#define DROP_MESSAGE_LEN 0

#endif /* CONFIG_LOG_BACKEND_RTT_MODE_DROP */

#if CONFIG_LOG_BACKEND_RTT_BUFFER > 0
static u8_t rtt_buf[CONFIG_LOG_BACKEND_RTT_BUFFER_SIZE];
#endif /* CONFIG_LOG_BACKEND_RTT_BUFFER > 0 */

static u8_t line_buf[CONFIG_LOG_BACKEND_RTT_MESSAGE_SIZE + DROP_MESSAGE_LEN];
static u8_t *line_pos;
static u8_t char_buf;
static int panic_mode;

static int msg_out(u8_t *data, size_t length, void *ctx);

static int line_out(u8_t data);

static void log_backend_rtt_flush(void);

static int log_backend_rtt_write(void);

static int log_backend_rtt_panic(u8_t *data, size_t length);

static int msg_out(u8_t *data, size_t length, void *ctx)
{
	(void) ctx;
	u8_t *pos;

	if (panic_mode) {
		return log_backend_rtt_panic(data, length);
	}

	for (pos = data; pos < data + length; pos++) {
		if (line_out(*pos)) {
			break;
		}
	}

	return (int) (pos - data);
}

static int line_out(u8_t data)
{
	if (data == '\r') {
		if (log_backend_rtt_write()) {
			return 1;
		}
		line_pos = line_buf;
		return 0;
	}

	if (line_pos < line_buf + sizeof(line_buf) - 1) {
		*line_pos++ = data;
	}

	/* not enough space in line buffer, we have to wait for EOL */
	return 0;
}

#if CONFIG_LOG_BACKEND_RTT_MODE_DROP

static int log_backend_rtt_write(void)
{
	*line_pos = '\r';

	if (drop_cnt > 0 && !drop_warn) {
		memmove(line_buf + DROP_MESSAGE_LEN, line_buf,
			line_pos - line_buf);
		memcpy(line_buf, drop_msg, DROP_MESSAGE_LEN);
		line_pos += DROP_MESSAGE_LEN;
		drop_warn = 1;
	}

	if (drop_warn) {
		int cnt = min(drop_cnt, 99);
		if (cnt < 10) {
			line_buf[DROP_MESSAGE_LEN - 2] = ' ';
			line_buf[DROP_MESSAGE_LEN - 3] = (u8_t) ('0' + cnt);
			line_buf[DROP_MESSAGE_LEN - 4] = ' ';
		} else {
			line_buf[DROP_MESSAGE_LEN - 2] = (u8_t) ('0' + cnt % 10);
			line_buf[DROP_MESSAGE_LEN - 3] = (u8_t) ('0' + cnt / 10);
			line_buf[DROP_MESSAGE_LEN - 4] = '>';
		}
	}

	int ret = SEGGER_RTT_WriteSkipNoLock(CONFIG_LOG_BACKEND_RTT_BUFFER,
					     line_buf, line_pos - line_buf + 1);

	if (!ret) {
		drop_cnt++;
		return 0;
	}

	drop_cnt = 0;
	drop_warn = 0;
	return 0;
}

#elif CONFIG_LOG_BACKEND_RTT_MODE_BLOCK

static int log_backend_rtt_write(void)
{
	*line_pos = '\r';
	if (SEGGER_RTT_WriteSkipNoLock(CONFIG_LOG_BACKEND_RTT_BUFFER, line_buf,
				       line_pos - line_buf + 1)) {
		log_backend_rtt_flush();
		return 0;
	}
	return 1;
}

#endif

static int log_backend_rtt_panic(u8_t *data, size_t length)
{
	unsigned int written;

	written = SEGGER_RTT_WriteNoLock(CONFIG_LOG_BACKEND_RTT_BUFFER, data,
					 length);
	log_backend_rtt_flush();
	return written;
}


LOG_OUTPUT_DEFINE(log_output, msg_out, &char_buf, 1);

static void put(const struct log_backend *const backend,
		struct log_msg *msg)
{
	log_msg_get(msg);

	u32_t flags = LOG_OUTPUT_FLAG_LEVEL | LOG_OUTPUT_FLAG_TIMESTAMP;

	if (IS_ENABLED(CONFIG_LOG_BACKEND_SHOW_COLOR)) {
		flags |= LOG_OUTPUT_FLAG_COLORS;
	}

	if (IS_ENABLED(CONFIG_LOG_BACKEND_FORMAT_TIMESTAMP)) {
		flags |= LOG_OUTPUT_FLAG_FORMAT_TIMESTAMP;
	}

	log_output_msg_process(&log_output, msg, flags);

	log_msg_put(msg);

}

static void log_backend_rtt_init(void)
{
	SEGGER_RTT_Init();
#if CONFIG_LOG_BACKEND_RTT_BUFFER > 0
	SEGGER_RTT_ConfigUpBuffer(CONFIG_LOG_BACKEND_RTT_BUFFER, "Logger",
				  rtt_buf, sizeof(rtt_buf),
				  SEGGER_RTT_MODE_NO_BLOCK_SKIP);
#endif
	panic_mode = 0;
	line_pos = line_buf;
}

static void panic(struct log_backend const *const backend)
{
	panic_mode = 1;
}

static void log_backend_rtt_flush(void)
{
	while (SEGGER_RTT_HasDataUp(CONFIG_LOG_BACKEND_RTT_BUFFER)) {
		/* pass */
	}
}

const struct log_backend_api log_backend_rtt_api = {
	.put = put,
	.panic = panic,
	.init = log_backend_rtt_init,
};

LOG_BACKEND_DEFINE(log_backend_rtt, log_backend_rtt_api, true);
