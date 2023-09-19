/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrHID.h
 * @author    jbacon
 * @date      2023-09-18
 * @brief     USB HID Wrapper
 *
 *            This file is the declaration of the USB HID wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef USB_HID_WRAPPER
#define USB_HID_WRAPPER

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

/**
 * @brief The HID device data structure.
*/
typedef struct
{
  const struct device *dev;                         /**< The HID device. */
  uint8_t *descriptor;                              /**< The HID descriptor. */
  bool configured;                                  /**< The DC configured flag. */
  const struct hid_ops ops;                         /**< The HID operations. */
} ZephyrHID;

/**
 * @brief   Initialize the HID device.
 *
 * @param hid       The HID device.
 * @param devLabel  The HID device label as a C string.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrHidInit(ZephyrHID *hid, uint8_t *devLabel);

/**
 * @brief   Write to the EP buffer.
 *
 * @param hid       The HID device.
 * @param data      The data to write.
 * @param size      The size of the data.
 * @param byteCnt   The number of byte written to the buffer.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrHidWriteToEp(ZephyrHID *hid, uint8_t *data, size_t size,
                       uint8_t *byteCnt);

/**
 * @brief   Read from the EP buffer.
 *
 * @param hid       The HID device.
 * @param data      The output buffer.
 * @param size      The size of the output buffer.
 * @param byteCnt   The count of bytes read.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrHidReadFromEp(ZephyrHID *hid, uint8_t *data, size_t size,
                        uint8_t *byteCnt);

#endif    /* USB_HID_WRAPPER */

/** @} */
