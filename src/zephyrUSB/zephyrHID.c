/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrHID.c
 * @author    jbacon
 * @date      2023-09-18
 * @brief     USB HID Wrapper
 *
 *            This file is the implementation of the USB HID wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrHID.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrHidInit(ZephyrHID *hid, uint8_t *devLabel)
{
  int rc;

  hid->dev = device_get_binding(devLabel);
  if(!hid->dev)
  {
      LOG_ERR("device %s not found", devLabel);
      return -ENODEV;
  }

  usb_hid_register_device(hid->dev, hid->descriptor, sizeof(hid->descriptor),
    &hid->ops);

  rc = usb_hid_init(hid->dev);
  if(rc < 0)
    LOG_ERR("unable to initialize device %s", devLabel);

  return rc;
}

int zephyrHidWriteToEp(ZephyrHID *hid, uint8_t *data, size_t size,
                       size_t *byteCnt)
{
  return hid_int_ep_write(hid->dev, data, size, byteCnt);
}

int zephyrHidReadFromEp(ZephyrHID *hid, uint8_t *data, size_t size,
                        size_t *byteCnt)
{
  return hid_int_ep_read(hid->dev, data, size, byteCnt);
}

/** @} */
