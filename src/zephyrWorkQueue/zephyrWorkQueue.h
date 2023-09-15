/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrWorkQueue.h
 * @author    jbacon
 * @date      2023-09-14
 * @brief     Work Queue Wrapper
 *
 *            This file is the declaration of the work queue wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef WORK_QUEUE_WRAPPER
#define WORK_QUEUE_WRAPPER

#include <zephyr/kernel.h>

/**
 * @brief The work queue data structure.
*/
typedef struct
{
  struct k_work_q data;                     /**< The work queue data. */
  k_thread_stack_t *stack;                  /**< The zephyr stack structure. */
  size_t stackSize;                         /**< The stack size. */
  int priority;                             /**< The thread priority. */
  struct k_work_queue_config config;        /**< The work queue configuration. */
} ZephyrWorkQueue;

/**
 * @brief   Initialize the work queue.
 *
 * @param queue   The work queue to initialize.
 */
void zephyrWorkQueueInit(ZephyrWorkQueue *queue);

/**
 * @brief   Start the work queue.
 *
 * @param queue   The work queue to start.
 */
void zephyrWorkerQueueStart(ZephyrWorkQueue *queue);

/**
 * @brief   Get the work queue thread.
 *
 * @param queue   The work queue.
 *
 * @return  The ID of the thread of the work queue.
 */
k_tid_t zephyrWorkQueueGetThread(ZephyrWorkQueue *queue);

/**
 * @brief   Wait until the work queue has drained (no more work).
 *
 * @param queue   The work queue.
 * @param usePlug The use plug flag.
 *
 * @return  1 if we had to wait, 0 if no wait was needed, the error
 *          code otherwise.
 */
int zephyrWorkQueueDrain(ZephyrWorkQueue *queue, bool usePlug);

/**
 * @brief   Unplug the work queue after draining it with the plug flag.
 *
 * @param queue   The work queue.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrWorkQueueUnplug(ZephyrWorkQueue *queue);

#endif    /* WORK_QUEUE_WRAPPER */

/** @} */
