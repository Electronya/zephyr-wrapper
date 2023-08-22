/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrCommon.h
 * @author    jbacon
 * @date      2023-05-06
 * @brief     Common Stuff Wrapper
 *
 *            This file is the declaration of the common stuff wrapper.
 *
 * @defgroup  zephyr-wrapper zephyr-wrapper
 * @brief     This module is the Electronya Zephyr RTOS wrapper.
 *            It exists mostly to simplify the testing of Electronya Zephyr RTOS
 *            firmware.
 * @{
 */

#ifndef COMMON_WRAPPER
#define COMMON_WRAPPER

#include <zephyr/kernel.h>

/**
 * @brief   The zephyr wrapper module name.
*/
#define ZEPHYR_WRAPPER_MODULE_NAME    zephyrWrapper

/**
 * @brief Zephyr command success.
 */
#define ZEPHYR_CMD_SUCCESS          0

/**
 * @brief Zephyr command error.
 */
#define ZEPHYR_CMD_ERROR            1

/**
 * @brief The time value for NO WAIT.
 */
#define ZEPHYR_TIME_NO_WAIT         UINT32_MAX

/**
 * @brief The time unit for FOREVER.
 */
#define ZEPHYR_TIME_FOREVER         (UINT32_MAX - 1)

/**
 * @brief The Zephyr time units.
 */
typedef enum
{
  NANO_SEC,                               /**< The nanosecond time unit. */
  MICRO_SEC,                              /**< The microsecond time unit. */
  MILLI_SEC,                              /**< The millisecond time unit. */
  SECONDS,                                /**< The second time unit. */
  MINUTES,                                /**< The minute time unit. */
  HOURS,                                  /**< The hour time unit. */
} ZephyrTimeUnit;

/**
 * @brief Process a Zephyr timeout.
 *
 * @param time          The time value.
 * @param unit          The time unit.
 *
 * @return              The processed Zephyr timeout.
 */
k_timeout_t zephyrCommonProcessTimeout(uint32_t time, ZephyrTimeUnit unit);

#endif    /* COMMON_WRAPPER */

/** @} */
