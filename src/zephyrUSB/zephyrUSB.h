/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrUSB.h
 * @author    jbacon
 * @date      2023-08-25
 * @brief     USB Wrapper
 *
 *            This file is the declaration of the USB wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef USB_WRAPPER
#define USB_WRAPPER

#include <zephyr/usb/usb_device.h>

/**
 * @brief   Enable the USB subsystem.
 * @note    This functions needs to called after all the USB classes have
 *          been initialize to ensure that communication is properly processed.
 *
 * @param statusCb  The status callback.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrUsbEnable(usb_dc_status_callback statusCb);

#endif    /* USB_WRAPPER */

/** @} */
