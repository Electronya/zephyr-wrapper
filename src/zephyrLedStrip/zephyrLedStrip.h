/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrLedStrip.h
 * @author    jbacon
 * @date      2023-05-06
 * @brief     LED Strip Wrapper
 *
 *            This file is the declaration of the LED strip wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef LED_STRIP_WRAPPER
#define LED_STRIP_WRAPPER

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>

/**
 * @brief   The pixel color format.
*/
typedef enum
{
  LED_STRIP_COLOR_RGB,              /**< The RGB color format. */
  LED_STRIP_COLOR_RGBW,             /**< The RGBW color format. */
  LED_STRIP_COLOR_CNT               /**< The number of color format. */
} ZephyrLedStripClrFmt;

/**
 * @brief   The RGBW Led structure.
*/
struct led_rgbw
{
  uint8_t r;                        /**< Red color. */
  uint8_t g;                        /**< Green color. */
  uint8_t b;                        /**< Blue color. */
  uint8_t w;                        /**< White color. */
};

/**
 * @brief   The LED strip data structure.
*/
typedef struct
{
  const struct device *dev;         /**< The Zephyr device of the led strip. */
  uint32_t pixelCount;              /**< The pixel count in the led strip. */
  ZephyrLedStripClrFmt colorFmt;    /**< The pixel color format. */
  struct led_rgb *rgbPixels;        /**< The array of RGB pixel of the strip. */
  struct led_rgbw *rgbwPixels;      /**< The array of RGBW pixel of the strip. */
} ZephyrLedStrip;

/**
 * @brief   Initialize the LED strip.
 *
 * @param strip     The LED strip data structure to initialize.
 * @param colorFmt  The color format of the strip.
 * @param pixelCnt  The pixel count of the strip.
 *
 * @return          0 if successful, the error code otherwise.
 */
int zephyrLedStripInit(ZephyrLedStrip *strip, ZephyrLedStripClrFmt colorFmt,
                       uint32_t pixelCnt);

#endif    /* LED_STRIP_WRAPPER */

/** @} */
