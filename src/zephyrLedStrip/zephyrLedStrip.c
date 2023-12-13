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

int zephyrLedStripInit(ZephyrLedStrip_t *strip, uint32_t pixelCnt)
{
  strip->rgbPixels = NULL;

  if(device_is_ready(strip->dev))
    LOG_DBG("initializing strip %s with %d pixels", strip->dev->name, pixelCnt);
  else
  {
    LOG_ERR("strip device %s not ready", strip->dev->name);
    return -ENODEV;
  }

  strip->rgbPixels = k_malloc(pixelCnt * sizeof(ZephyrRgbPixel_t));
  if(!strip->rgbPixels)
  {
    LOG_ERR("unable to allocate memory for %d X RGB pixel", pixelCnt);
    return -ENOSPC;
  }
  memset(strip->rgbPixels, 0x00, pixelCnt * sizeof(ZephyrRgbPixel_t));

  strip->pixelCount = pixelCnt;

  return 0;
}

uint32_t zephyrLedStripGetPixelCnt(ZephyrLedStrip_t *strip)
{
  return strip->pixelCount;
}

int zephyrLedStripSetPixel(ZephyrLedStrip_t *strip, uint32_t pixelIdx,
                           const ZephyrRgbPixel_t *rgbPixel)
{
  if(!strip->dev || !strip->rgbPixels)
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

  memset(strip->rgbPixels + pixelIdx, 0x00, sizeof(ZephyrRgbPixel_t));
  memcpy(strip->rgbPixels + pixelIdx, rgbPixel, sizeof(ZephyrRgbPixel_t));

  return 0;
}

int zephyrLedStripSetPixels(ZephyrLedStrip_t *strip, uint32_t start,
                            uint32_t end, const ZephyrRgbPixel_t *rgbPixels)
{
  uint32_t pixelCount;

  if(!strip->dev || !strip->rgbPixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  if(start > end)
  {
    LOG_ERR("the given start index (%d) is larger than the given end index (%d)",
      start, end);
    return -EINVAL;
  }

  if(start > strip->pixelCount)
  {
    LOG_ERR("the given start index (%d) is out of range (%d)", start,
      strip->pixelCount);
    return -EDOM;
  }

  if(end > strip->pixelCount)
  {
    LOG_ERR("the given end index (%d) is out of range (%d)", end,
      strip->pixelCount);
    return -EDOM;
  }

  pixelCount = end - start;
  memset(strip->rgbPixels + start, 0x00, pixelCount * sizeof(ZephyrRgbPixel_t));
  memcpy(strip->rgbPixels + start, rgbPixels,
    pixelCount * sizeof(ZephyrRgbPixel_t));

  return 0;
}

int zephyrLedStripUpdate(ZephyrLedStrip_t *strip)
{
  int rc;

  if(!strip->dev || !strip->rgbPixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  rc = led_strip_update_rgb(strip->dev, strip->rgbPixels, strip->pixelCount);

  return rc;
}

/** @} */
