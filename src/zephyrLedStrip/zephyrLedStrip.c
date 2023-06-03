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
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrLedStripInit(ZephyrLedStrip *strip, ZephyrLedStripClrFmt colorFmt,
                       uint32_t pixelCnt)
{
  strip->rgbPixels = NULL;

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
      strip->rgbPixels = k_malloc(pixelCnt * sizeof(ZephyrRgbLed));
      if(!strip->rgbPixels)
      {
        LOG_ERR("unable to allocate memory for %d X RGB pixel", pixelCnt);
        return -ENOSPC;
      }
      memset(strip->rgbPixels, 0x00, sizeof(ZephyrRgbLed * (strip->pixelCount)));
      break;
    default:
      LOG_ERR("color format %d is not supported", colorFmt);
      return -EINVAL;
  }

  strip->colorFmt = colorFmt;
  strip->pixelCount = pixelCnt;

  return 0;
}

int zephyrLedStripSetRgbColor(ZephyrLedStrip *strip, uint32_t pixelIdx,
                              const ZephyrRgbLed *rgbColor)
{
  if(!strip->dev || strip->rgbPixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  if(pixelIdx > strip->pixelCount)
  {
    LOG_ERR("the given pixel index (%d) is out of range (%d)", pixelIdx,
      strip->pixelCount);
    return -EDOM;
  }

  memset(strip->rgbPixels + pixelIdx, 0x00, sizeof(ZephyrRgbLed));
  memcpy(strip->rgbPixels + pixelIdx, rgbColor, sizeof(ZephyrRgbLed));

  return 0;
}

int zephyrLedStripUpdate(ZephyrLedStrip *strip)
{
  int rc;

  switch(strip->colorFmt)
  {
    case LED_STRIP_COLOR_RGB:
      rc = led_strip_update_rgb(strip->dev, strip->rgbPixels,
        strip->pixelCount);
      break;
    default:
      LOG_ERR("color format %d is not supported", strip->colorFmt);
      rc = -EINVAL;
  }

  return rc;
}

/** @} */
