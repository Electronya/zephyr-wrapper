/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrCounter.c
 * @author    jbacon
 * @date      2023-07-23
 * @brief     Counter Wrapper
 *
 *            This file is the implementation of the Counter wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>

#include "zephyrCounter.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrCounterInit(ZephyrCounter_t *counter)
{
  if(!device_is_ready(counter->dev))
  {
    LOG_ERR("device counter %s not ready", counter->dev->name);
    return -ENXIO;
  }

  return 0;
}

bool zephyrCounterIsCountingUp(ZephyrCounter_t *counter)
{
  return counter_is_counting_up(counter->dev);
}

uint8_t zephyrCounterGetChannelCount(ZephyrCounter_t *counter)
{
  return counter_get_num_of_channels(counter->dev);
}

uint32_t zephyrCounterGetFreq(ZephyrCounter_t *counter)
{
  return counter_get_frequency(counter->dev);
}

uint32_t zephyrCounterUsToTicks(ZephyrCounter_t *counter, uint64_t usVal)
{
  return counter_us_to_ticks(counter->dev, usVal);
}

uint32_t zephyrCounterTicksToUs(ZephyrCounter_t *counter, uint32_t ticks)
{
  return counter_ticks_to_us(counter->dev, ticks);
}

uint32_t zephyrCounterGetMaxTop(ZephyrCounter_t *counter)
{
  return counter_get_max_top_value(counter->dev);
}

int zephyrCounterStart(ZephyrCounter_t *counter)
{
  return counter_start(counter->dev);
}

int zephyrCounterStop(ZephyrCounter_t *counter)
{
  return counter_stop(counter->dev);
}

int zephyrCounterGetTicks(ZephyrCounter_t *counter, uint32_t *ticks)
{
 return counter_get_value(counter->dev, ticks);
}

int zephyrCounterGetTicks64(ZephyrCounter_t *counter, uint64_t *ticks)
{
  return counter_get_value_64(counter->dev, ticks);
}

int zephyrCounterSetChannelAlarm(ZephyrCounter_t *counter, uint8_t channelId)
{
  return counter_set_channel_alarm(counter->dev, channelId,
    counter->alarmConfigs + channelId);
}

int zephyrCounterCancelChannelAlarm(ZephyrCounter_t *counter, uint8_t channelId)
{
  return counter_cancel_channel_alarm(counter->dev, channelId);
}

int zephyrCounterSetTop(ZephyrCounter_t *counter)
{
  return counter_set_top_value(counter->dev, &counter->topConfig);
}

int zephyrCounterGetPendingIrq(ZephyrCounter_t *counter)
{
  return counter_get_pending_int(counter->dev);
}

uint32_t zephyrCounterGetTop(ZephyrCounter_t *counter)
{
  return counter_get_top_value(counter->dev);
}

int zephyrCounterSetGuardPeriod(ZephyrCounter_t *counter,
                                uint32_t ticks, uint32_t flags)
{
  return counter_set_guard_period(counter->dev, ticks, flags);
}

uint32_t zephyrCounterGetGuardPeriod(ZephyrCounter_t *counter, uint32_t flags)
{
  return counter_get_guard_period(counter->dev, flags);
}

/** @} */
