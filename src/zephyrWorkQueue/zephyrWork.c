/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrWork.c
 * @author    jbacon
 * @date      2023-09-15
 * @brief     Work Wrapper
 *
 *            This file is the implementation of the work wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrWork.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

void zephyrWorkInit(ZephyrWork_t *work)
{
  k_work_init(&work->data, work->handler);
}

int zephyrWorkGetBusy(ZephyrWork_t *work)
{
  return k_work_busy_get(&work->data);
}

bool zephyrWorkIsPending(ZephyrWork_t *work)
{
  return k_work_is_pending(&work->data);
}

int zephyrWorkSubmitToQueue(ZephyrWorkQueue_t *queue, ZephyrWork_t *work)
{
  return k_work_submit_to_queue(&queue->data, &work->data);
}

int zephyrWorkSubmit(ZephyrWork_t *work)
{
  return k_work_submit(&work->data);
}

bool zephyrWorkFlush(ZephyrWork_t *work)
{
  return k_work_flush(&work->data, &work->sync);
}

int zephyrWorkCancel(ZephyrWork_t *work)
{
  return k_work_cancel(&work->data);
}

bool zephyrWorkCancelSync(ZephyrWork_t *work)
{
  return k_work_cancel_sync(&work->data, &work->sync);
}

void zephyrDelayedWorkInit(ZephyrDelayedWork_t *work)
{
  k_work_init_delayable(&work->data, work->handler);
}

int zephyrDelayedWorkGetBusy(ZephyrDelayedWork_t *work)
{
  return k_work_delayable_busy_get(&work->data);
}

bool zephyrDelayedWorkIsPending(ZephyrDelayedWork_t *work)
{
  return k_work_delayable_is_pending(&work->data);
}

k_ticks_t zephyrDelayedWorkGetExpire(ZephyrDelayedWork_t *work)
{
  return k_work_delayable_expires_get(&work->data);
}

k_ticks_t zephyrDelayedWorkGetRemaining(ZephyrDelayedWork_t *work)
{
  return k_work_delayable_remaining_get(&work->data);
}

int zephyrDelayedWorkScheduleToQueue(ZephyrWorkQueue_t *queue,
                                     ZephyrDelayedWork_t *work, uint32_t delay,
                                     ZephyrTimeUnit_t unit)
{
  return k_work_schedule_for_queue(&queue->data, &work->data,
    zephyrCommonProcessTimeout(delay, unit));
}

int zephyrDelayedWorkSchedule(ZephyrDelayedWork_t *work, uint32_t delay,
                              ZephyrTimeUnit_t unit)
{
  return k_work_schedule(&work->data, zephyrCommonProcessTimeout(delay, unit));
}

int zephyrDelayedWorkRescheduleToQueue(ZephyrWorkQueue_t *queue,
                                       ZephyrDelayedWork_t *work, uint32_t delay,
                                       ZephyrTimeUnit_t unit)
{
  return k_work_reschedule_for_queue(&queue->data, &work->data,
    zephyrCommonProcessTimeout(delay, unit));
}

int zephyrDelayedWorkReschedule(ZephyrDelayedWork_t *work, uint32_t delay,
                                ZephyrTimeUnit_t unit)
{
  return k_work_reschedule(&work->data,
    zephyrCommonProcessTimeout(delay, unit));
}

bool zephyrDelayedWorkFlush(ZephyrDelayedWork_t *work)
{
  return k_work_flush_delayable(&work->data, &work->sync);
}

int zephyrDelayedWorkCancel(ZephyrDelayedWork_t *work)
{
  return k_work_cancel_delayable(&work->data);
}

bool zephyrDelayedWorkCancelSync(ZephyrDelayedWork_t *work)
{
  return k_work_cancel_delayable_sync(&work->data, &work->sync);
}

/** @} */
