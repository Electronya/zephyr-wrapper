/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrCommon.c
 * @author    jbacon
 * @date      2023-05-06
 * @brief     Common Stuff Wrapper
 *
 *            This file is the implementation of the common stuff wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>

#include "zephyrCommon.h"

LOG_MODULE_REGISTER(ZEPHYR_WRAPPER_MODULE_NAME);

k_timeout_t zephyrCommonProcessTimeout(uint32_t time, ZephyrTimeUnit unit)
{
  k_timeout_t zephyrTimeout;

  if(time == ZEPHYR_TIME_FOREVER)
    zephyrTimeout = K_FOREVER;
  else if(time == ZEPHYR_TIME_NO_WAIT)
    zephyrTimeout = K_NO_WAIT;
  else
    switch(unit)
    {
      case NANO_SEC:
        zephyrTimeout = K_NSEC(time);
        break;
      case MICRO_SEC:
        zephyrTimeout = K_USEC(time);
        break;
      case MILLI_SEC:
        zephyrTimeout = K_MSEC(time);
        break;
      case SECONDS:
        zephyrTimeout = K_SECONDS(time);
        break;
      case MINUTES:
        zephyrTimeout = K_MINUTES(time);
        break;
      case HOURS:
        zephyrTimeout = K_HOURS(time);
        break;
      default:
        zephyrTimeout = K_MSEC(time);
        break;
    }

  return zephyrTimeout;
}

/** @} */
