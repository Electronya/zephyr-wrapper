/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrCounter.h
 * @author    jbacon
 * @date      2023-07-23
 * @brief     Counter Wrapper
 *
 *            This file is the declaration of the Counter wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef COUNTER_WRAPPER
#define COUNTER_WRAPPER

#include <zephyr/kernel.h>
#include <zephyr/drivers/counter.h>

#include "zephyrCommon.h"

/**
 * @brief   The Zephyr Counter.
*/
typedef struct
{
  const struct device *dev;                               /**< The counter device. */
  struct counter_config_info  counterConfig;              /**< The counter configuration. */
  struct counter_top_cfg topConfig;                       /**< The counter top (overflow) configuration. */
  struct counter_alarm_cfg *alarmConfigs;                 /**< The counter channel alarm configurations. */
} ZephyrCounter_t;

/**
 * @brief   Initialize the counter.
 *
 * @param counter       The counter.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterInit(ZephyrCounter_t *counter);

/**
 * @brief   Check if the counter is counting up.
 *
 * @param counter       The counter.
 *
 * @return              True if the counter is counting up,
 *                      false if counting down.
*/
bool zephyrCounterIsCountingUp(ZephyrCounter_t *counter);

/**
 * @brief   Get the counter number of channel.
 *
 * @param counter       The counter.
 *
 * @return              The number of channel of the counter.
*/
uint8_t zephyrCounterGetChannelCount(ZephyrCounter_t *counter);

/**
 * @brief   Get the counter frequency in Hz.
 *
 * @param counter       The counter.
 *
 * @return              The counter frequency in Hz. 0 if the counter does not
 *                      have a stable frequency.
*/
uint32_t zephyrCounterGetFreq(ZephyrCounter_t *counter);

/**
 * @brief   Convert the counter us to ticks.
 *
 * @param counter       The counter.
 * @param usVal         The us value to convert.
 *
 * @return              The converted value. Saturated if greater than 32 bits.
*/
uint32_t zephyrCounterUsToTicks(ZephyrCounter_t *counter, uint64_t usVal);

/**
 * @brief   Convert the counter ticks to us.
 *
 * @param counter       The counter.
 * @param ticks         The tick value to convert.
 *
 * @return              The converted us value.
*/
uint32_t zephyrCounterTicksToUs(ZephyrCounter_t *counter, uint32_t ticks);

/**
 * @brief   Get the counter max top (overflow) value.
 *
 * @param counter       The counter.
 *
 * @return              The maximal top (overflow) value.
*/
uint32_t zephyrCounterGetMaxTop(ZephyrCounter_t *counter);

/**
 * @brief   Start the counter.
 *
 * @param counter       The counter.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterStart(ZephyrCounter_t *counter);

/**
 * @brief   Stop the counter.
 *
 * @param counter       The counter.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterStop(ZephyrCounter_t *counter);

/**
 * @brief   Get the current counter tick count.
 *
 * @param counter       The counter.
 * @param ticks         The counter current tick count.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterGetTicks(ZephyrCounter_t *counter, uint32_t *ticks);

/**
 * @brief   Get the current counter tick count in 64 bits.
 *
 * @param counter       The counter.
 * @param ticks         The counter current tick count in 64 bits.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterGetTicks64(ZephyrCounter_t *counter, uint64_t *ticks);

/**
 * @brief   Set the desired channel alarm.
 *
 * @param counter       The counter.
 * @param channelId     The channel ID for which to configure the alarm.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterSetChannelAlarm(ZephyrCounter_t *counter, uint8_t channelId);

/**
 * @brief   Cancel the desired channel alarm.
 *
 * @param counter       The counter.
 * @param channelId     The channel ID for which to cancel the alarm.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterCancelChannelAlarm(ZephyrCounter_t *counter, uint8_t channelId);

/**
 * @brief   Set the counter top (overflow) value.
 *
 * @param counter       The counter.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterSetTop(ZephyrCounter_t *counter);

/**
 * @brief   Check if any interrupts are pending.
 *
 * @param counter       The counter.
 *
 * @return              1 if any interrupts are pending, 0 otherwise.
*/
int zephyrCounterGetPendingIrq(ZephyrCounter_t *counter);

/**
 * @brief   Get the current top (overflow) value.
 *
 * @param counter       The counter.
 *
 * @return              The current top (overflow) value.
*/
uint32_t zephyrCounterGetTop(ZephyrCounter_t *counter);

/**
 * @brief   Set the guard period.
 *
 * @param counter       The counter.
 * @param ticks         The tick count for the guard period.
 * @param flags         The guard period flags.
 *
 * @return              0 if successful, the error code otherwise.
*/
int zephyrCounterSetGuardPeriod(ZephyrCounter_t *counter, uint32_t ticks,
                                uint32_t flags);

/**
 * @brief   Get the guard period in counter ticks.
 *
 * @param counter       The counter.
 * @param flags         The guard period flags.
 *
 * @return              The guard period in counter ticks, 0 if the function of
 *                      flags are not supported.
*/
uint32_t zephyrCounterGetGuardPeriod(ZephyrCounter_t *counter, uint32_t flags);

#endif    /* COUNTER_WRAPPER */

/** @} */
