/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrMsgQueue.h
 * @author    jbacon
 * @date      2023-11-28
 * @brief     Message Queue Wrapper
 *
 *            This file is the declaration of the message queue wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef MESSAGE_QUEUE_WRAPPER
#define MESSAGE_QUEUE_WRAPPER

#include <zephyr/kernel.h>

#include "zephyrCommon.h"

/**
 * Zephyr message queue data structure.
 */
typedef struct zephyrMsgQueue
{
  struct k_msgq msgq;               /**< The zephyr message queue structure. */
  char *buffer;                     /**< The message queue buffer. */
} ZephyrMsgQueue;

/**
 * @brief   Initialize a zephyr message queue.
 *
 * @param queue         The message queue data structure.
 * @param msgSize       The message size of the queue.
 * @param maxMsgCount   The maximum message count in the queue.
 *
 * @return              0 if successful, the error code otherwise.
 */
int zephyrMsgQueueInit(ZephyrMsgQueue *queue, size_t msgSize,
                       uint32_t maxMsgCount);

/**
 * @brief   Push a message to a queue.
 *
 * @param queue       The zephyr message queue.
 * @param msg         The message to push.
 * @param timeout     The waiting period if the queue is full.
 * @param timeUnit    The time unit of the timeout.
 *
 * @return            0 if successful, the error code otherwise.
 */
int zephyrMsgQueuePush(ZephyrMsgQueue *queue, const void *msg,
                       uint32_t timeout, ZephyrTimeUnit timeUnit);

/**
 * @brief   Pop a message from a queue.
 *
 * @param queue       The zephyr message queue.
 * @param msg         The popped message.
 * @param timeout     The waiting period (ms) if the queue is empty.
 * @param timeUnit    The time unit of the timeout.
 *
 * @return            0 if successful, the error code otherwise.
 */
int zephyrMsgQueuePop(ZephyrMsgQueue *queue, void *msg,
                      uint32_t timeout, ZephyrTimeUnit timeUnit);

/**
 * @brief   Peek a queue for the next message.
 *
 * @param queue       The zephyr message queue.
 * @param msg         The peeked message.
 *
 * @return            0 if successful, the error code otherwise.
 */
int zephyrMsgQueuePeek(ZephyrMsgQueue *queue, void *msg);

/**
 * @brief   Purge a queue of its messages.
 *
 * @param queue       The zephyr message queue.
 */
void zephyrMsgQueuePurge(ZephyrMsgQueue *queue);

/**
 * @brief   Get the available free space in the queue.
 *
 * @param queue       The zephyr message queue.
 *
 * @return            The number of empty message slots.
 */
size_t zephyrMsgQueueGetFreeSpace(ZephyrMsgQueue *queue);

/**
 * @brief   Get the number of messages in the queue.
 *
 * @param queue       The zephyr message queue.
 *
 * @return            The number of messages in the queue.
 */
size_t zephyrMsgQueueGetMsgCount(ZephyrMsgQueue *queue);


#endif    /* MESSAGE_QUEUE_WRAPPER */

/** @} */
