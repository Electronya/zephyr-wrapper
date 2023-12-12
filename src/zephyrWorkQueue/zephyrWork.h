/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrWork.h
 * @author    jbacon
 * @date      2023-09-15
 * @brief     Work Wrapper
 *
 *            This file is the declaration of the work wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef WORK_WRAPPER
#define WORK_WRAPPER

#include <zephyr/kernel.h>

#include "zephyrWorkQueue.h"
#include "zephyrCommon.h"

/**
 * @brief The work data structure.
*/
typedef struct
{
  struct k_work data;                           /**< The work data. */
  k_work_handler_t handler;                     /**< The work handler. */
  struct k_work_sync sync;                      /**< The work sync data. */
} ZephyrWork_t;

/**
 * @brief The delayed work data structure.
*/
typedef struct
{
  struct k_work_delayable data;                 /**< The delayed work data. */
  k_work_handler_t handler;                     /**< The delayed work handler. */
  struct k_work_sync sync;                      /**< The work sync data. */
} ZephyrDelayedWork_t;

/**
 * @brief   Initialize the work.
 *
 * @param work  The work to initialize.
 */
void zephyrWorkInit(ZephyrWork_t *work);

/**
 * @brief   Get the busy state of the work.
 *
 * @param work  The work.
 *
 * @return  The work busy flags.
 */
int zephyrWorkGetBusy(ZephyrWork_t *work);

/**
 * @brief   Check if the work is pending.
 *
 * @param work  The work.
 *
 * @return  True if the work is pending, false otherwise.
 */
bool zephyrWorkIsPending(ZephyrWork_t *work);

/**
 * @brief   Submit the work to a specific queue.
 *
 * @param queue   The work queue.
 * @param work    The work.
 *
 * @return  - 0 if work was already submitted,
 *          - 1 if work was queued,
 *          - 2 if work is running and have been resubmitted,
 *          - the error code otherwise.
 */
int zephyrWorkSubmitToQueue(ZephyrWorkQueue_t *queue, ZephyrWork_t *work);

/**
 * @brief   Submit the work to the system queue.
 *
 * @param work    The work.
 *
 * @return  - 0 if work was already submitted,
 *          - 1 if work was queued,
 *          - 2 if work is running and have been resubmitted,
 *          - the error code otherwise.
 */
int zephyrWorkSubmit(ZephyrWork_t *work);

/**
 * @brief   Wait for the work to be flushed (to have been executed).
 *
 * @param work  The work.
 *
 * @return  True if we had to wait, false otherwise.
 */
bool zephyrWorkFlush(ZephyrWork_t *work);

/**
 * @brief   Cancel the work.
 *
 * @param work  The work.
 *
 * @return  The work busy flags.
 */
int zephyrWorkCancel(ZephyrWork_t *work);

/**
 * @brief   Cancel the work and wait for it to complete.
 *
 * @param work  The work.
 *
 * @return  True if work was pending, false otherwise
 */
bool zephyrWorkCancelSync(ZephyrWork_t *work);

/**
 * @brief   Initialize the delayed work.
 *
 * @param work  The delayed work to initialize.
 */
void zephyrDelayedWorkInit(ZephyrDelayedWork_t *work);

/**
 * @brief   Get the busy state of the delayed work.
 *
 * @param work  The delayed work.
 *
 * @return  The work busy flags.
 */
int zephyrDelayedWorkGetBusy(ZephyrDelayedWork_t *work);

/**
 * @brief   Check if the delayed work is pending.
 *
 * @param work  The delayed work.
 *
 * @return  True if the work is pending, false otherwise.
 */
bool zephyrDelayedWorkIsPending(ZephyrDelayedWork_t *work);

/**
 * @brief   Get the absolute tick count until the delayed work expires
 *          (will be submitted).
 *
 * @param work  The delayed work.
 *
 * @return  The absolute tick count until expiration.
 */
k_ticks_t zephyrDelayedWorkGetExpire(ZephyrDelayedWork_t *work);

/**
 * @brief   Get the remaining tick count until the delayed work expires
 *          (will be submitted).
 *
 * @param work  The delayed work.
 *
 * @return  The remaining tick count until expiration.
 */
k_ticks_t zephyrDelayedWorkGetRemaining(ZephyrDelayedWork_t *work);

/**
 * @brief   Schedule the delayed work to a specific queue.
 *
 * @param queue   The work queue.
 * @param work    The delayed work.
 * @param delay   The delay time value.
 * @param unit    The delay time unit.
 *
 * @return  - 0 if work was already scheduled,
 *          - 1 if work was scheduled,
 *          - the error code otherwise.
 */
int zephyrDelayedWorkScheduleToQueue(ZephyrWorkQueue_t *queue,
                                     ZephyrDelayedWork_t *work, uint32_t delay,
                                     ZephyrTimeUnit_t unit);

/**
 * @brief   Schedule the delayed work to the system queue.
 *
 * @param work    The delayed work.
 * @param delay   The delay time value.
 * @param unit    The delay time unit.
 *
 * @return  - 0 if work was already scheduled,
 *          - 1 if work was scheduled,
 *          - the error code otherwise.
 */
int zephyrDelayedWorkSchedule(ZephyrDelayedWork_t *work, uint32_t delay,
                              ZephyrTimeUnit_t unit);

/**
 * @brief   Reschedule the delayed work to a specific queue.
 *
 * @param queue   The work queue.
 * @param work    The delayed work.
 * @param delay   The delay time value.
 * @param unit    The delay time unit.
 *
 * @return  - 0 if work was already scheduled and no wait delay for reschedule,
 *          - 1 if work was rescheduled,
 *          - 2 if work is running and have been rescheduled,
 *          - the error code otherwise.
 */
int zephyrDelayedWorkRescheduleToQueue(ZephyrWorkQueue_t *queue,
                                       ZephyrDelayedWork_t *work, uint32_t delay,
                                       ZephyrTimeUnit_t unit);

/**
 * @brief   Reschedule the delayed work to the system queue.
 *
 * @param work    The delayed work.
 * @param delay   The delay time value.
 * @param unit    The delay time unit.
 *
 * @return  - 0 if work was already submitted and no wait delay for reschedule,
 *          - 1 if work was rescheduled,
 *          - 2 if work is running and have been rescheduled,
 *          - the error code otherwise.
 */
int zephyrDelayedWorkReschedule(ZephyrDelayedWork_t *work, uint32_t delay,
                                ZephyrTimeUnit_t unit);

/**
 * @brief   Wait for the delayed work to be flushed (to have been executed).
 *
 * @param work  The delayed work.
 *
 * @return  True if we had to wait, false otherwise.
 */
bool zephyrDelayedWorkFlush(ZephyrDelayedWork_t *work);

/**
 * @brief   Cancel the delayed work.
 *
 * @param work  The delayed work.
 *
 * @return  The work busy flags.
 */
int zephyrDelayedWorkCancel(ZephyrDelayedWork_t *work);

/**
 * @brief   Cancel the delayed work and wait for it to complete.
 *
 * @param work  The delayed work.
 *
 * @return  True if work was pending, false otherwise
 */
bool zephyrDelayedWorkCancelSync(ZephyrDelayedWork_t *work);

#endif    /* WORK_WRAPPER */

/** @} */
