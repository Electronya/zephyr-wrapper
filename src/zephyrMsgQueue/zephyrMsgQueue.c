/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrMsgQueue.c
 * @author    jbacon
 * @date      2023-11-28
 * @brief     Message Queue Wrapper
 *
 *            This file is the implementation of the message queue wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrMsgQueue.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrMsgQueueInit(ZephyrMsgQueue *queue, size_t msgSize,
                       uint32_t maxMsgCount)
{
  queue->buffer = k_malloc(msgSize * maxMsgCount);
  if(!queue->buffer)
    return -ENOSPC;

  k_msgq_init(&queue->msgq, queue->buffer, msgSize, maxMsgCount);

  return 0;
}

int zephyrMsgQueuePush(ZephyrMsgQueue *queue, const void *msg,
                       uint32_t timeout, ZephyrTimeUnit timeUnit)
{
  return k_msgq_put(&queue->msgq, msg,
    zephyrCommonProcessTimeout(timeout, timeUnit));
}

int zephyrMsgQueuePop(ZephyrMsgQueue *queue, void *msg,
                      uint32_t timeout, ZephyrTimeUnit timeUnit)
{
  return k_msgq_get(&queue->msgq, msg,
    zephyrCommonProcessTimeout(timeout, timeUnit));
}

int zephyrMsgQueuePeek(ZephyrMsgQueue *queue, void *msg)
{
  return k_msgq_peek(&queue->msgq, msg);
}

void zephyrMsgQueuePurge(ZephyrMsgQueue *queue)
{
  k_msgq_purge(&queue->msgq);
}

size_t zephyrMsgQueueGetFreeSpace(ZephyrMsgQueue *queue)
{
  return k_msgq_num_free_get(&queue->msgq);
}

size_t zephyrMsgQueueGetMsgCount(ZephyrMsgQueue *queue)
{
  return k_msgq_num_used_get(&queue->msgq);
}


/** @} */
