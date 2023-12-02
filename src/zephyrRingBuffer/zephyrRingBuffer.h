/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrRingBuffer.h
 * @author    jbacon
 * @date      2023-08-30
 * @brief     Ring Buffer Wrapper
 *
 *            This file is the declaration of the ring buffer wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef RING_BUFFER_WRAPPER
#define RING_BUFFER_WRAPPER

#include <zephyr/sys/ring_buffer.h>

/**
 * @brief The ring buffer type.
*/
typedef struct ring_buf ZephyrRingBuffer_t;

/**
 * @brief   Initialize a byte ring buffer.
 *
 * @param buffer  The ring buffer structure.
 * @param size    The size of the ring buffer in bytes.
 * @param data    The data area of the ring buffer.
 */
void zephyrRingBufInit(ZephyrRingBuffer_t *buffer, size_t size, uint8_t *data);

/**
 * @brief   Check if a ring buffer is empty.
 *
 * @param buffer  The ring buffer.
 *
 * @return  true if the ring buffer is empty, false otherwise.
 */
bool zephyrRingBufIsEmpty(ZephyrRingBuffer_t *buffer);

/**
 * @brief   Reset a ring buffer.
 *
 * @param buffer  The ring buffer.
 */
void zephyrRingBufReset(ZephyrRingBuffer_t *buffer);

/**
 * @brief   Get the free space of a byte ring buffer.
 *
 * @param buffer  The ring buffer.
 *
 * @return  The free space in bytes.
 */
size_t zephyrRingBufGetFreeSpace(ZephyrRingBuffer_t *buffer);

/**
 * @brief   Get a rig buffer total size.
 *
 * @param buffer  The ring buffer.
 *
 * @return  The size in bytes.
 */
size_t zephyrRingBufGetSize(ZephyrRingBuffer_t *buffer);

/**
 * @brief   Get a ring buffer used space.
 *
 * @param buffer  The ring buffer.
 *
 * @return  The size in bytes.
 */
size_t zephyrRingBufGetUsedSpace(ZephyrRingBuffer_t *buffer);

/**
 * @brief   Claim a ring buffer for putting.
 *
 * @param buffer  The ring buffer.
 * @param data    The pointer to the data area claimed.
 * @param size    The size of the data area to claim.
 *
 * @return  The size of the claimed area, which may be smaller than the
 *          requested one.
 */
size_t zephyrRingBufClaimPutting(ZephyrRingBuffer_t *buffer, uint8_t **data,
                                 size_t size);

/**
 * @brief   Signal that the putting operation is done. This needs to be called
 *          after a claim putting operation.
 *
 * @param buffer  The ring buffer.
 * @param size    The size of the data that was put in the ring buffer.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrRingBufFinishPutting(ZephyrRingBuffer_t *buffer, size_t size);

/**
 * @brief   Put data in a ring buffer.
 *
 * @param buffer  The ring buffer.
 * @param data    The data.
 * @param size    The size of the data.
 *
 * @return  The size of the data that was really put in the buffer. Which can
 *          be smaller than the size of the data.
 */
size_t zephyrRingBufPut(ZephyrRingBuffer_t *buffer, uint8_t *data, size_t size);

/**
 * @brief   Claim a ring buffer for getting data.
 *
 * @param buffer  The ring buffer.
 * @param data    The pointer to the data area claimed.
 * @param size    The size of the data area to claim.
 *
 * @return  The actual size of the data area claimed. Which may differ from
 *          the size requested.
 */
size_t zephyrRingBufClaimGetting(ZephyrRingBuffer_t *buffer, uint8_t **data,
                                 size_t size);

/**
 * @brief   Signal that the getting operation is done. This needs to be called
 *          after the claim getting operation.
 *
 * @param buffer
 * @param size
 * @return int
 */
int zephyrRingBufFinishGetting(ZephyrRingBuffer_t *buffer, size_t size);

/**
 * @brief   Get data from a ring buffer.
 *
 * @param buffer  The ring buffer.
 * @param data    The output buffer.
 * @param size    The size of the output buffer.
 *
 * @return  The actual data that was get from the ring buffer. Which may differ
 *          from the requested size.
 */
size_t zephyrRingBufGet(ZephyrRingBuffer_t *buffer, uint8_t *data, size_t size);

/**
 * @brief   Peek into a ring buffer. Peeking allows to read data from a ring
 *          buffer without removing the data from it.
 *
 * @param buffer  The ring buffer.
 * @param data    The output buffer.
 * @param size    The size of the output buffer.
 *
 * @return  The size of the data peeked from the buffer. Which can differ from
 *          the requested size.
 */
size_t zephyrRingBufPeek(ZephyrRingBuffer_t *buffer, uint8_t *data, size_t size);

#endif    /* RING_BUFFER_WRAPPER */

/** @} */
