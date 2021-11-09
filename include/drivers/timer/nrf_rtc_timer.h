/*
 * Copyright (c) 2016-2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_TIMER_NRF_RTC_TIMER_H
#define ZEPHYR_INCLUDE_DRIVERS_TIMER_NRF_RTC_TIMER_H

#include <sys_clock.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Maximum allowed time span that is considered to be in the future.
 */
#define NRF_RTC_TIMER_MAX_SCHEDULE_SPAN BIT(23)

/** @brief RTC timer compare event handler.
 *
 * Called from RTC ISR context when processing a compare event.
 *
 * @param id Compare channel ID.
 *
 * @param expire_time An actual absolute expiration time set for a compare
 *		      channel. It can differ from the requested target time
 *		      and the difference can be used to determine whether the
 *		      time set was delayed.
 *
 * @param user_data Pointer to a user context data.
 */
typedef void (*z_nrf_rtc_timer_compare_handler_t)(int32_t id,
						uint64_t expire_time,
						void *user_data);

/** @brief Allocate RTC compare channel.
 *
 * Channel 0 is used for the system clock.
 *
 * @retval Non-negative indicates allocated channel ID.
 * @retval -ENOMEM if channel cannot be allocated.
 */
int32_t z_nrf_rtc_timer_chan_alloc(void);

/** @brief Free RTC compare channel.
 *
 * @param chan Previously allocated channel ID.
 */
void z_nrf_rtc_timer_chan_free(int32_t chan);

/** @brief Read current absolute time.
 *
 * @return Current absolute time.
 */
uint64_t z_nrf_rtc_timer_read(void);

/** @brief Get COMPARE event register address.
 *
 * Address can be used for (D)PPI.
 *
 * @param chan Channel ID between 0 and CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT.
 *
 * @return Register address.
 */
uint32_t z_nrf_rtc_timer_compare_evt_address_get(int32_t chan);

/** @brief Safely disable compare event interrupt.
 *
 * Function returns key indicating whether interrupt was already disabled.
 *
 * @param chan Channel ID between 1 and CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT.
 *
 * @return key passed to @ref z_nrf_rtc_timer_compare_int_unlock.
 */
bool z_nrf_rtc_timer_compare_int_lock(int32_t chan);

/** @brief Safely enable compare event interrupt.
 *
 * Event interrupt is conditionally enabled based on @p key.
 *
 * @param chan Channel ID between 1 and CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT.
 *
 * @param key Key returned by @ref z_nrf_rtc_timer_compare_int_lock.
 */
void z_nrf_rtc_timer_compare_int_unlock(int32_t chan, bool key);

/** @brief Read compare register value.
 *
 * @param chan Channel ID between 0 and CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT.
 *
 * @return Value set in the compare register.
 */
uint32_t z_nrf_rtc_timer_compare_read(int32_t chan);

/** @brief  Try to set compare channel to given value.
 *
 * Provided value is absolute and cannot be further in the future than
 * @c NRF_RTC_TIMER_MAX_SCHEDULE_SPAN. If given value is in the past then an RTC
 * interrupt is triggered immediately. Otherwise function continuously retries
 * to set compare register until value that is written is far enough in the
 * future and will generate an event. Because of that, compare register value
 * may be different than the one requested. During this operation interrupt
 * from that compare channel is disabled. Other interrupts are not locked during
 * this operation.
 *
 * @param chan Channel ID between 1 and CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT.
 *
 * @param target_time Absolute target time in ticks.
 *
 * @param handler User function called in the context of the RTC interrupt.
 *
 * @param user_data Data passed to the handler.
 *
 * @retval 0 if the compare channel was set successfully.
 * @retval -EINVAL if provided target time was further than
 *         @c NRF_RTC_TIMER_MAX_SCHEDULE_SPAN ticks in the future.
 */
int z_nrf_rtc_timer_set(int32_t chan, uint64_t target_time,
			 z_nrf_rtc_timer_compare_handler_t handler,
			 void *user_data);

/** @brief Abort a timer requested with @ref z_nrf_rtc_timer_set.
 *
 * If an abort operation is performed too late it is still possible for an event
 * to fire. The user can detect a spurious event by comparing absolute time
 * provided in callback and a result of @ref z_nrf_rtc_timer_read. During this
 * operation interrupt from that compare channel is disabled. Other interrupts
 * are not locked during this operation.
 *
 * @param chan Channel ID between 1 and CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT.
 */
void z_nrf_rtc_timer_abort(int32_t chan);

/** @brief Convert system clock time to RTC ticks.
 *
 * @p t can be absolute or relative. @p t cannot be further into the future
 * from now than the RTC range (e.g. 512 seconds if RTC is running at 32768 Hz).
 *
 * @retval Positive value represents @p t in RTC tick value.
 * @retval -EINVAL if @p t is out of range.
 */
uint64_t z_nrf_rtc_timer_get_ticks(k_timeout_t t);

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_TIMER_NRF_RTC_TIMER_H */
