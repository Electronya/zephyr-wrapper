/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrWorkQueue.c
 * @author    jbacon
 * @date      2023-09-14
 * @brief     Work Queue Wrapper
 *
 *            This file is the implementation of the work queue wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrWorkQueue.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

void zephyrWorkQueueInit(ZephyrWorkQueue_t *queue)
{
  k_work_queue_init(&queue->data);
}

void zephyrWorkerQueueStart(ZephyrWorkQueue_t *queue)
{
  k_work_queue_start(&queue->data, queue->stack, queue->stackSize,
    queue->priority, &queue->config);
}

k_tid_t zephyrWorkQueueGetThread(ZephyrWorkQueue_t *queue)
{
  return k_work_queue_thread_get(&queue->data);
}

int zephyrWorkQueueDrain(ZephyrWorkQueue_t *queue, bool usePlug)
{
  return k_work_queue_drain(&queue->data, usePlug);
}

int zephyrWorkQueueUnplug(ZephyrWorkQueue_t *queue)
{
  return k_work_queue_unplug(&queue->data);
}

/** @} */
