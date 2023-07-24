/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrLedStrip.c
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
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrLedStrip.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

#define LED_STRIP_TIMING_TOLERANCE    150

/**
 * @brief   Calculate the timing counter ticks value.
 *
 * @param strip     The LED strip data structure.
 */
static void calculateTicks(ZephyrLedStrip *strip)
{
  uint16_t tmpTiming;
  uint32_t freq;
  uint32_t ticksPerTiming;
  uint32_t ticks;
  float period;

  freq = zephyrCounterGetFreq(&strip->timingCntr);
  period = (1 / ((float)freq)) * 1000000000;

  /* find the smallest timing */
  tmpTiming = strip->t0h < strip->t0l ? strip->t0h : strip->t0l;
  tmpTiming = tmpTiming < strip->t1h ? tmpTiming : strip->t1h;
  tmpTiming = tmpTiming < strip->t1l ? tmpTiming : strip->t1l;

  ticks = (uint32_t)(tmpTiming / period);

  /* validate the tick count */
  ticksPerTiming = strip->t0h / ticks;
  if((ticksPerTiming * strip->t0h) < strip->t0h - LED_STRIP_TIMING_TOLERANCE ||
     (ticksPerTiming * strip->t0h) > strip->t0h + LED_STRIP_TIMING_TOLERANCE)
  {
    return -EINVAL;
  }

  ticksPerTiming = strip->t0l / ticks;
  if((ticksPerTiming * strip->t0l) < strip->t0l - LED_STRIP_TIMING_TOLERANCE ||
     (ticksPerTiming * strip->t0l) > strip->t0l + LED_STRIP_TIMING_TOLERANCE)
  {
    return -EINVAL;
  }

  ticksPerTiming = strip->t1h / ticks;
  if((ticksPerTiming * strip->t1h) < strip->t1h - LED_STRIP_TIMING_TOLERANCE ||
     (ticksPerTiming * strip->t1h) > strip->t1h + LED_STRIP_TIMING_TOLERANCE)
  {
    return -EINVAL;
  }

  ticksPerTiming = strip->t1l / ticks;
  if((ticksPerTiming * strip->t1l) < strip->t1l - LED_STRIP_TIMING_TOLERANCE ||
     (ticksPerTiming * strip->t1l) > strip->t1l + LED_STRIP_TIMING_TOLERANCE)
  {
    return -EINVAL;
  }

  strip->tickPeriod = period * ticks;
  strip->timingCntr.topConfig.ticks = ticks;
}

/**
 * @brief   Process the the LED strip reset.
 *
 * @param strip   The LED strip.
 * @return        true if reset is finished, false otherwise.
 */
static bool processReset(ZephyrLedStrip *strip)
{
  int rc;
  bool isResetDone = true;
  uint16_t resetOverflow = strip->rst / strip->tickPeriod;

  if(strip->tickCntr < resetOverflow)
  {
    rc = zephyrGpioClear(&strip->dataLine);
    if(rc < 0)
      LOG_ERR("unable to clear the data line for reset");
    ++strip->tickCntr;
    isResetDone = false;
  }

  return isResetDone;
}

/**
 * @brief   Transmit a bit.
 *
 * @param strip   The LED strip.
 */
static void transmitBit(ZephyrLedStrip *strip)
{
  int rc;
  uint8_t txBit;
  uint16_t bitOverflow;
  uint16_t lvlOverflow;
  uint8_t *pixels = (uint8_t *)strip->pixels;

  /* get the bit to transmit */
  txBit = (pixels[strip->byteIdx] & (0x01 << strip->bitIdx)) >> strip->bitIdx;

  /* calculate the overflows */
  if(txBit)
  {
    bitOverflow = (strip->t1h + strip->t1l) / strip->tickPeriod;
    lvlOverflow = strip->t1h / strip->tickPeriod;
  }
  else
  {
    bitOverflow = (strip->t0h + strip->t0l) / strip->tickPeriod;
    lvlOverflow = strip->t0h / strip->tickPeriod;
  }

  if(strip->tickCntr < lvlOverflow)
  {
    rc = zephyrGpioSet(&strip->dataLine);
    if(rc < 0)
      LOG_ERR("unable to set the data line");
  }
  else if(strip->tickCntr < bitOverflow)
  {
    rc = zephyrGpioClear(&strip->dataLine);
    if(rc < 0)
      LOG_ERR("unable to clear the data line");
  }

  ++strip->tickCntr;
  if(strip->tickCntr == bitOverflow)
  {
    strip->tickCntr = 0;
    --strip->bitIdx;
    if(strip->bitIdx == 0)
    {
      strip->bitIdx = 8;
      ++strip->byteIdx;
    }
  }
}

/**
 * @brief   The LED strip timing counter callback.
 *
 * @param dev       The counter device.
 * @param userData  The user data.
 */
static void counterCallback(const struct device *dev, void *userData)
{
  int rc;
  ZephyrLedStrip *strip = (ZephyrLedStrip *)userData;

  /* check if resetting */
  if(strip->byteIdx == strip->pixelCount * strip->pixelSize)
  {
    if(processReset(strip))
    {
      rc = zephyrCounterStop(&strip->timingCntr);
      if(rc < 0)
        LOG_ERR("unable to stop the LED strip timer.");
    }
  }
  else
  {
    transmitBit(strip);
  }
}

/**
 * @brief   Initialize the LED strip timing counter.
 *
 * @param timingCntr  The timing counter.
 * @param txData     The LED strip txData.
 *
 * @return            0 if successful, the error code otherwise.
 */
static int zephyrLedStripInitTimingCntr(ZephyrLedStrip *strip)
{
  int rc;
  uint32_t ticks;

  rc = zephyrCounterInit(&strip->timingCntr);
  if(rc < 0)
    return rc;

  calculateTicks(strip);
  strip->timingCntr.topConfig.callback = counterCallback;
  strip->timingCntr.topConfig.user_data = strip;

  rc = zephyrCounterSetTop(&strip->timingCntr);
  if(rc < 0)
    LOG_ERR("unable to set the timing counter top configuration");

  return rc;
}

int zephyrLedStripInit(ZephyrLedStrip *strip, ZephyrLedStripClrFmt colorFmt,
                       uint32_t pixelCnt)
{
  int rc;

  strip->pixels = NULL;
  strip->tickCntr = 0;
  strip->colorFmt = colorFmt;
  strip->pixelCount = pixelCnt;

  rc = zephyrLedStripInitTimingCntr(strip);
  if(rc < 0)
    return rc;

  rc = zephyrGpioInit(&strip->dataLine, GPIO_OUT_CLR);
  if(rc < 0)
    return rc;

  switch(strip->colorFmt)
  {
    case LED_STRIP_COLOR_RGB:
    case LED_STRIP_COLOR_GRB:
      strip->pixelSize = sizeof(ZephyrRgbPixel);
      break;
    case LED_STRIP_COLOR_RGBW:
      strip->pixelSize = sizeof(ZephyrRgbwPixel);
      break;
    default:
      LOG_ERR("unsupported color format");
      return -EINVAL;
      break;
  }

  strip->pixels = k_malloc(strip->pixelSize * strip->pixelCount);
  if(!strip->pixels)
  {
    LOG_ERR("unable to allocate the pixel buffer");
    rc = -ENOSPC;
  }

  return rc;
}

uint32_t zephyrLedStripGetPixelCnt(ZephyrLedStrip *strip)
{
  return strip->pixelCount;
}

int zephyrLedStripSetRgbPixel(ZephyrLedStrip *strip, uint32_t pixelIdx,
                              const ZephyrRgbPixel *pixel)
{
  if(!strip->pixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  if(strip->colorFmt != LED_STRIP_COLOR_RGB &&
     strip->colorFmt != LED_STRIP_COLOR_GRB)
  {
    LOG_ERR("LED strip of bad color format");
    return -EINVAL;
  }

  if(pixelIdx > strip->pixelCount)
  {
    LOG_ERR("the given pixel index (%d) is out of range (%d)", pixelIdx,
      strip->pixelCount);
    return -EINVAL;
  }

  bytecpy((uint8_t *)strip->pixels + pixelIdx, pixel, sizeof(ZephyrRgbPixel));

  return 0;
}

int zephyrLedStripSetRgbPixels(ZephyrLedStrip *strip, uint32_t start,
                               uint32_t end, const ZephyrRgbPixel *pixels)
{
  uint32_t pixelCount;

  if(!strip->pixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  if(strip->colorFmt != LED_STRIP_COLOR_RGBW)
  {
    LOG_ERR("LED strip of bad color format");
    return -EINVAL;
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
  bytecpy((uint8_t *)strip->pixels + start, pixels,
    pixelCount * sizeof(ZephyrRgbPixel));

  return 0;
}

int zephyrLedStripSetGrbPixel(ZephyrLedStrip *strip, uint32_t pixelIdx,
                              const ZephyrGrbPixel *pixel)
{
  if(!strip->pixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  if(strip->colorFmt != LED_STRIP_COLOR_GRB)
  {
    LOG_ERR("LED strip of bad color format");
    return -EINVAL;
  }

  if(pixelIdx > strip->pixelCount)
  {
    LOG_ERR("the given pixel index (%d) is out of range (%d)", pixelIdx,
      strip->pixelCount);
    return -EINVAL;
  }

  bytecpy((uint8_t *)strip->pixels + pixelIdx, pixel, sizeof(ZephyrGrbPixel));

  return 0;
}

int zephyrLedStripSetGrbPixels(ZephyrLedStrip *strip, uint32_t start,
                               uint32_t end, const ZephyrGrbPixel *pixels)
{
  uint32_t pixelCount;

  if(!strip->pixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  if(strip->colorFmt != LED_STRIP_COLOR_RGBW)
  {
    LOG_ERR("LED strip of bad color format");
    return -EINVAL;
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
  bytecpy((uint8_t *)strip->pixels + start, pixels,
    pixelCount * sizeof(ZephyrGrbPixel));

  return 0;
}

int zephyrLedStripSetRgbwPixel(ZephyrLedStrip *strip, uint32_t pixelIdx,
                               const ZephyrRgbwPixel *pixel)
{
  if(!strip->pixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  if(strip->colorFmt != LED_STRIP_COLOR_RGBW)
  {
    LOG_ERR("LED strip of bad color format");
    return -EINVAL;
  }

  if(pixelIdx > strip->pixelCount)
  {
    LOG_ERR("the given pixel index (%d) is out of range (%d)", pixelIdx,
      strip->pixelCount);
    return -EINVAL;
  }

  bytecpy((uint8_t *)strip->pixels + pixelIdx, pixel, sizeof(ZephyrRgbwPixel));

  return 0;
}

int zephyrLedStripSetRgbwPixels(ZephyrLedStrip *strip, uint32_t start,
                                uint32_t end, const ZephyrRgbwPixel *pixels)
{
  uint32_t pixelCount;

  if(!strip->pixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  if(strip->colorFmt != LED_STRIP_COLOR_RGBW)
  {
    LOG_ERR("LED strip of bad color format");
    return -EINVAL;
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
  bytecpy((uint8_t *)strip->pixels + start, pixels,
    pixelCount * sizeof(ZephyrRgbwPixel));

  return 0;
}

int zephyrLedStripUpdate(ZephyrLedStrip *strip)
{
  int rc;

  if(!strip->pixels)
  {
    LOG_ERR("LED strip not yet initialized");
    return -ENODEV;
  }

  strip->bitIdx = 8;
  strip->byteIdx = 0;
  strip->tickCntr = 0;

  rc = zephyrCounterStart(&strip->timingCntr);
  if(rc < 0)
    LOG_ERR("unable to start the LED strip timing counter");

  return rc;
}

/** @} */
