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

int zephyrMsgQueueInit(ZephyrMsgQueue_t *queue, size_t msgSize, size_t maxMsgCnt)
{
  queue->buffer = k_malloc(msgSize * maxMsgCnt);
  if(!queue->buffer)
    return -ENOSPC;

  k_msgq_init(&queue->msgq, queue->buffer, msgSize, maxMsgCnt);

  return 0;
}

int zephyrMsgQueuePush(ZephyrMsgQueue_t *queue, const void *msg,
                       uint32_t timeout, ZephyrTimeUnit_t timeUnit)
{
  return k_msgq_put(&queue->msgq, msg,
    zephyrCommonProcessTimeout(timeout, timeUnit));
}

int zephyrMsgQueuePop(ZephyrMsgQueue_t *queue, void *msg,
                      uint32_t timeout, ZephyrTimeUnit_t timeUnit)
{
  return k_msgq_get(&queue->msgq, msg,
    zephyrCommonProcessTimeout(timeout, timeUnit));
}

int zephyrMsgQueuePeek(ZephyrMsgQueue_t *queue, void *msg)
{
  return k_msgq_peek(&queue->msgq, msg);
}

void zephyrMsgQueuePurge(ZephyrMsgQueue_t *queue)
{
  k_msgq_purge(&queue->msgq);
}

size_t zephyrMsgQueueGetFreeSpace(ZephyrMsgQueue_t *queue)
{
  return k_msgq_num_free_get(&queue->msgq);
}

size_t zephyrMsgQueueGetMsgCount(ZephyrMsgQueue_t *queue)
{
  return k_msgq_num_used_get(&queue->msgq);
}


/** @} */
