/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrLedStrip.h
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

#include "zephyrThread.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

void zephyrThreadCreate(ZephyrThread_t *thread, char *name,
                        uint32_t startDelay, ZephyrTimeUnit_t timeUnit)
{
  k_thread_create(&thread->data, thread->stack, thread->stackSize,
    thread->entry, thread->p1, thread->p2, thread->p3, thread->priority,
    thread->options, zephyrCommonProcessTimeout(startDelay, timeUnit));
  k_thread_name_set(&thread->data, name);
}

void zephyrThreadAbort(ZephyrThread_t *thread)
{
  k_thread_abort(&thread->data);
}

void zephyrThreadStart(ZephyrThread_t *thread)
{
  k_thread_start(&thread->data);
}

void zephyrThreadWakeUp(ZephyrThread_t *thread)
{
  k_wakeup(&thread->data);
}

bool zephyrThreadCanYield(void)
{
  return k_can_yield();
}

void zephyrThreadYield(void)
{
  k_yield();
}

uint32_t zephyrThreadSleep(uint32_t time, ZephyrTimeUnit_t unit)
{
  return k_sleep(zephyrCommonProcessTimeout(time, unit));
}

uint32_t zephyrThreadSleepMs(uint32_t ms)
{
  return k_msleep(ms);
}

uint32_t zephyrThreadSleepUs(uint32_t us)
{
  return k_usleep(us);
}

void zephyrThreadJoin(ZephyrThread_t *thread, uint32_t timeout,
                      ZephyrTimeUnit_t timeoutUnit)
{
  k_thread_join(&thread->data, zephyrCommonProcessTimeout(timeout, timeoutUnit));
}

/** @} */
