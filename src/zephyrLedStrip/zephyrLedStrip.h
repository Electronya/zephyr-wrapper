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
 * @brief   The RGB color sequence constructor.
*/
#define RGB(_r, _g, _b)         { .r = (_r), .g = (_g), .b = (_b) }

/**
 * @brief   The RGB LED structure.
*/
typedef struct led_rgb ZephyrRgbLed;

/**
 * @brief   The LED strip data structure.
*/
typedef struct
{
  const struct device *dev;         /**< The Zephyr device of the led strip. */
  uint32_t pixelCount;              /**< The pixel count in the led strip. */
  ZephyrRgbLed *rgbPixels;          /**< The array of RGB pixel of the strip. */
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
int zephyrLedStripInit(ZephyrLedStrip *strip, const uint32_t pixelCnt);

/**
 * @brief   Get the pixel count of the LED strip.
 *
 * @param strip     The LED strip.
 * @return          The count of pixel in the LED strip.
 */
uint32_t zephyrLedStripGetPixelCnt(ZephyrLedStrip *strip);

/**
 * @brief   Set the desired pixel RGB color.
 *
 * @param strip     The LED strip data structure to set.
 * @param pixelIdx  The index of the pixel to set the color.
 * @param rgbPixel  The pixel new RGB color.
 *
 * @return          0 if successful, the error code otherwise.
*/
int zephyrLedStripSetPixel(ZephyrLedStrip *strip, uint32_t pixelIdx,
                           const ZephyrRgbLed *rgbPixel);

/**
 * @brief   Set the pixels included between the start and
 *
 * @param strip     The LED strip data structure to set.
 * @param start     The index of the starting pixel.
 * @param end       The index of the ending pixel.
 * @param rgbPixels The pixels new RGB color.
 *
 * @return          0 if successful, the error code otherwise.
 */
int zephyrLedStripSetPixels(ZephyrLedStrip *strip, uint32_t start,
                            uint32_t end, const ZephyrRgbLed *rgbPixels);

/**
 * @brief   Update the strip pixels.
 *
 * @param strip     The LED strip data structure to update.
 *
 * @return          0 if successful, the error code otherwise.
*/
int zephyrLedStripUpdate(ZephyrLedStrip *strip);

#endif    /* LED_STRIP_WRAPPER */

/** @} */
