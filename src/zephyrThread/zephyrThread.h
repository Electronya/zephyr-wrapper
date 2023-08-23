/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrThread.h
 * @author    jbacon
 * @date      2023-08-22
 * @brief     Thread Wrapper
 *
 *            This file is the declaration of the thread wrapper.
 *
 * @ingroup  zephyr-wrapper zephyr-wrapper
 * @{
 */

#ifndef THREAD_WRAPPER
#define THREAD_WRAPPER

#include <zephyr/kernel.h>

#include "zephyrCommon.h"

/**
 * @brief   The Zephyr wrapper thread structure.
*/
typedef struct
{
  struct k_thread data;                     /**< The zephyr thread structure. */
  k_thread_stack_t *stack;                  /**< The zephyr stack structure. */
  size_t stackSize;                         /**< The stack size. */
  k_thread_entry_t entry;                   /**< The thread entrypoint. */
  void *p1;                                 /**< The entrypoint first parameter. */
  void *p2;                                 /**< The entrypoint second parameter. */
  void *p3;                                 /**< The entrypoint third parameter. */
  int priority;                             /**< The thread priority. */
  uint32_t options;                         /**< The thread options. */
} ZephyrThread;

/**
 * @brief   Create a thread.
 *
 * @param thread      The zephyr thread wrapper struct.
 * @param name        The thread name.
 * @param startDelay  The thread start delay.
 * @param timeUnit    The time unit of the start delay.
 */
void zephyrThreadCreate(ZephyrThread *thread, char *name,
                        uint32_t startDelay, ZephyrTimeUnit timeUnit);

/**
 * @brief   Abort a thread.
 *
 * @param thread  The thread to abort.
 */
void zephyrThreadAbort(ZephyrThread *thread);

/**
 * @brief   Start a thread.
 *
 * @param thread  The thread to start.
 */
void zephyrThreadStart(ZephyrThread *thread);

/**
 * @brief   Wake up a thread.
 *
 * @param thread  The thread to wake up.
 */
void zephyrThreadWakeUp(ZephyrThread *thread);

/**
 * @brief   Check if the current thread can yield.
 *
 * @return true if the current thread can yield, false otherwise.
 */
bool zephyrThreadCanYield(void);

/**
 * @brief   Make the current thread yield.
 */
void zephyrThreadYield(void);

/**
 * @brief   Make the current thread sleep for the provided amount of time.
 *
 * @param time  The sleeping time value.
 * @param unit  The sleeping time unit.
 *
 * @return  The number of milliseconds left to sleep when the thread wakes up.
 */
uint32_t zephyrThreadSleep(uint32_t time, ZephyrTimeUnit unit);

/**
 * @brief   Make the current thread sleep for the provided amount
 *          of milliseconds.
 *
 * @param ms  The amount of milliseconds to sleep for.
 *
 * @return  The number of milliseconds left to sleep when the thread wakes up.
 */
uint32_t zephyrThreadSleepMs(uint32_t ms);

/**
 * @brief   Make the current thread sleep for the provided amount
 *          of microseconds.
 *
 * @param us  The amount of microseconds to sleep for.
 *
 * @return  The number of microseconds left to sleep when the thread wakes up.
 */
uint32_t zephyrThreadSleepUs(uint32_t us);

void zephyrThread

#endif    /* THREAD_WRAPPER */

/** @} */
