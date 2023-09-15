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
#include "zephyrCommon.h"
#include "zephyrWorkQueue.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

void zephyrWorkInit(ZephyrWork *work)
{
  k_work_init(&work->data, work->handler);
}

int zephyrWorkGetBusy(ZephyrWork *work)
{
  return k_work_busy_get(&work->data);
}

bool zephyrWorkIsPending(ZephyrWork *work)
{
  return k_work_is_pending(&work->data);
}

int zephyrWorkSubmitToQueue(ZephyrWorkQueue *queue, ZephyrWork *work)
{
  return k_work_submit_to_queue(&queue->data, &work->data);
}

int zephyrWorkSubmit(ZephyrWork *work)
{
  return k_work_submit(&work->data);
}

bool zephyrWorkFlush(ZephyrWork *work)
{
  return k_work_flush(&work->data, &work->sync);
}

int zephyrWorkCancel(ZephyrWork *work)
{
  return k_work_cancel(&work->data);
}

bool zephyrWorkCancelSync(ZephyrWork *work)
{
  return k_work_cancel_sync(&work->data, &work->sync);
}

void zephyrDelayedWorkInit(ZephyrDelayedWork *work)
{
  k_work_init_delayable(&work->data);
}

int zephyrDelayedWorkGetBusy(ZephyrDelayedWork *work)
{
  return k_work_delayable_busy_get(&work->data);
}

bool zephyrDelayedWorkIsPending(ZephyrDelayedWork *work)
{
  return k_work_delayable_is_pending(&work->data);
}

k_ticks_t zephyrDelayedWorkGetExpire(ZephyrDelayedWork *work)
{
  return k_work_delayable_expires_get(&work->data);
}

k_ticks_t zephyrDelayedWorkGetRemaining(ZephyrDelayedWork *work)
{
  return k_work_delayable_remaining_get(&work->data);
}

int zephyrDelayedWorkScheduleToQueue(ZephyrWorkQueue *queue,
                                     ZephyrDelayedWork *work, uint32_t delay,
                                     ZephyrTimeUnit unit)
{
  return k_work_schedule_for_queue(&queue->data, &work->data,
    zephyrCommonProcessTimeout(delay, unit));
}

int zephyrDelayedWorkSchedule(ZephyrDelayedWork *work, uint32_t delay,
                              ZephyrTimeUnit unit)
{
  return k_work_schedule(&work->data, zephyrCommonProcessTimeout(delay, unit));
}

int zephyrDelayedWorkRescheduleToQueue(ZephyrWorkQueue *queue,
                                       ZephyrDelayedWork *work, uint32_t delay,
                                       ZephyrTimeUnit unit)
{
  return k_work_reschedule_for_queue(&queue->data, &work->data,
    zephyrCommonProcessTimeout(delay, unit));
}

int zephyrDelayedWorkReschedule(ZephyrDelayedWork *work, uint32_t delay,
                                ZephyrTimeUnit unit)
{
  return k_work_reschedule(&work->data,
    zephyrCommonProcessTimeout(delay, unit));
}

bool zephyrDelayedWorkFlush(ZephyrDelayedWork *work)
{
  return k_work_flush_delayable(&work->data, &work->sync);
}

int zephyrDelayedWorkCancel(ZephyrDelayedWork *work)
{
  return k_work_cancel_delayable(&work->data);
}

bool zephyrDelayedWorkCancelSync(ZephyrDelayedWork *work)
{
  return k_work_cancel_delayable_sync(&work->data, &work->sync);
}

/** @} */
