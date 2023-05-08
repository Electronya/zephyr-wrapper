/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrLedStrip.h
 * @author    jbacon
 * @date      2023-05-06
 * @brief     LED Strip Wrapper
 *
 *            This file is the implementation of the LED strip wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrLedStrip.h"

/**
 * @brief   The RGB color sequence constructor.
*/
#define RGB(_r, _g, _b)         { .r = (_r), .g = (_g), .b = (_b) }

/**
 * @brief   The RGBW color sequence constructor.
*/
#define RGBW(_r, _g, _b, _w)    { .r = (_r), .g = (_g), .b = (_b), .w = (_w) }

LOG_MODULE_DECLARE(zephyrWrapper);

int zephyrLedStripInit(ZephyrLedStrip *strip, ZephyrLedStripClrFmt colorFmt,
                       uint32_t pixelCnt)
{
  int rc = 0;

  strip->rgbPixels = NULL;
  strip->rgbwPixels = NULL;

  if(device_is_ready(strip->dev))
    LOG_DBG("initializing strip %s with %d pixels of %d color format",
      strip->dev->name, pixelCnt, colorFmt);
  else
  {
    LOG_ERR("strip device %s not ready", strip->dev->name);
    return -ENODEV;
  }

  switch(colorFmt)
  {
    case LED_STRIP_COLOR_RGB:
      strip->rgbPixels = k_malloc(pixelCnt * sizeof(struct led_rgb));
      if(!strip->rgbPixels)
      {
        LOG_ERR("unable to allocate memory for %d X RGB pixel", pixelCnt);
        return -ENOSPC;
      }
      break;
    case LED_STRIP_COLOR_RGBW:
      strip->rgbwPixels = k_malloc(pixelCnt * sizeof(struct led_rgbw));
      if(!strip->rgbwPixels)
      {
        LOG_ERR("unable to allocate memory for %d X RGB pixel", pixelCnt);
        return -ENOSPC;
      }
      break;
    default:
      LOG_ERR("color format %d is not supported", colorFmt);
      return -EINVAL;
  }

  strip->colorFmt = colorFmt;
  strip->pixelCnt = pixelCnt;

  return rc;
}

/** @} */
