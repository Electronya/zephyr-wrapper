/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrUSB.c
 * @author    jbacon
 * @date      2023-08-25
 * @brief     USB Wrapper
 *
 *            This file is the implementation of the USB wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>

#include "zephyrUSB.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrUsbEnable(usb_dc_status_callback statusCb)
{
  return usb_enable(statusCb);
}

/** @} */
