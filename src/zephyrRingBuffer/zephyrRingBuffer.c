/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrRingBuffer.c
 * @author    jbacon
 * @date      2023-08-30
 * @brief     Ring Buffer Wrapper
 *
 *            This file is the implementation of the ring buffer wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrRingBuffer.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

void zephyrRingBufInit(ZephyrRingBuffer_t *buffer, size_t size, uint8_t *data)
{
  ring_buf_init(buffer, size, data);
}

bool zephyrRingBufIsEmpty(ZephyrRingBuffer_t *buffer)
{
  return ring_buf_is_empty(buffer);
}

void zephyrRingBufReset(ZephyrRingBuffer_t *buffer)
{
  ring_buf_reset(buffer);
}

size_t zephyrRingBufGetFreeSpace(ZephyrRingBuffer_t *buffer)
{
  return ring_buf_space_get(buffer);
}

size_t zephyrRingBufGetSize(ZephyrRingBuffer_t *buffer)
{
  return ring_buf_capacity_get(buffer);
}

size_t zephyrRingBufGetUsedSpace(ZephyrRingBuffer_t *buffer)
{
  return ring_buf_size_get(buffer);
}

size_t zephyrRingBufClaimPutting(ZephyrRingBuffer_t *buffer, uint8_t **data,
                                    size_t size)
{
  return ring_buf_put_claim(buffer, data, size);
}

int zephyrRingBufFinishPutting(ZephyrRingBuffer_t *buffer, size_t size)
{
  return ring_buf_put_finish(buffer, size);
}

size_t zephyrRingBufPut(ZephyrRingBuffer_t *buffer, uint8_t *data, size_t size)
{
  return ring_buf_put(buffer, data, size);
}

size_t zephyrRingBufClaimGetting(ZephyrRingBuffer_t *buffer, uint8_t **data,
                                 size_t size)
{
  return ring_buf_get_claim(buffer, data, size);
}

int zephyrRingBufFinishGetting(ZephyrRingBuffer_t *buffer, size_t size)
{
  return ring_buf_get_finish(buffer, size);
}

size_t zephyrRingBufGet(ZephyrRingBuffer_t *buffer, uint8_t *data, size_t size)
{
  return ring_buf_get(buffer, data, size);
}

size_t zephyrRingBufPeek(ZephyrRingBuffer_t *buffer, uint8_t *data, size_t size)
{
  return ring_buf_peek(buffer, data, size);
}

/** @} */
