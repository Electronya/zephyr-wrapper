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

#include "zephyrCounter.h"
#include "zephyrGpio.h"

/**
 * @brief   The RGB color sequence constructor.
*/
#define RGB(_r, _g, _b)         { .r = (_r), .g = (_g), .b = (_b) }

/**
 * @brief   The RGBW color sequence constructor.
*/
#define RGPW(_r, _g, _b, _w)    { .r = (_r), .g = (_g), .b = (_b), .w = (_w) };

/**
 * @brief   The pixel color format.
*/
typedef enum
{
  LED_STRIP_COLOR_RGB,              /**< The RGB color format. */
  LED_STRIP_COLOR_GRB,              /**< The GRB color format. */
  LED_STRIP_COLOR_RGBW,             /**< The RGBW color format. */
  LED_STRIP_COLOR_CNT               /**< The number of color format. */
} ZephyrLedStripClrFmt;

/**
 * @brief   The RGB LED structure.
*/
typedef struct
{
  uint8_t r;                        /** The red color component. */
  uint8_t g;                        /** The green color component. */
  uint8_t b;                        /** The blue color component. */
} ZephyrRgbPixel;

/**
 * @brief   The GRB LED structure.
*/
typedef struct
{
  uint8_t g;                        /** The green color component. */
  uint8_t r;                        /** The red color component. */
  uint8_t b;                        /** The blue color component. */
} ZephyrGrbPixel;

/**
 * @brief   The RGBW LED structure.
*/
typedef struct
{
  uint8_t r;                        /** The red color component. */
  uint8_t g;                        /** The green color component. */
  uint8_t b;                        /** The blue color component. */
  uint8_t w;                        /** The white color component. */
} ZephyrRgbwPixel;

/**
 * @brief   The LED strip data structure.
*/
typedef struct
{
  ZephyrCounter timingCntr;         /**< The bit timing counter. */
  uint32_t byteIdx;                 /**< The current Tx byte index. */
  uint8_t bitIdx;                   /**< The bit index. */
  uint16_t tickPeriod;              /**< The tick period (ns). */
  uint32_t tickCntr;                /**< The tick counter. */
  uint16_t t0h;                     /**< The 0 bit high timing value (ns).*/
  uint16_t t0l;                     /**< The 0 bit low timing value (ns).*/
  uint16_t t1h;                     /**< The 1 bit high timing value (ns). */
  uint16_t t1l;                     /**< The 1 bit low timing value (ns). */
  uint16_t rst;                     /**< The reset timing value (ns). */
  ZephyrGpio dataLine;              /**< The data line. */
  uint32_t pixelCount;              /**< The pixel count in the led strip. */
  ZephyrLedStripClrFmt colorFmt;    /**< The pixel color format. */
  size_t pixelSize;                 /**< The pixel size. */
  void *pixels;                     /**< The array of pixel of the strip. */
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
                       const uint32_t pixelCnt);

/**
 * @brief   Get the pixel count of the LED strip.
 *
 * @param strip     The LED strip.
 * @return          The count of pixel in the LED strip.
 */
uint32_t zephyrLedStripGetPixelCnt(ZephyrLedStrip *strip);

/**
 * @brief   Set the desired RGB pixel.
 *
 * @param strip     The LED strip data structure to set.
 * @param pixelIdx  The index of the pixel to set the color.
 * @param pixel     The pixel new RGB color.
 *
 * @return          0 if successful, the error code otherwise.
*/
int zephyrLedStripSetRgbPixel(ZephyrLedStrip *strip, uint32_t pixelIdx,
                              const ZephyrRgbPixel *pixel);

/**
 * @brief   Set the RGB pixels included between the start and end.
 *
 * @param strip     The LED strip data structure to set.
 * @param start     The index of the starting pixel.
 * @param end       The index of the ending pixel.
 * @param pixels    The pixels new RGB color.
 *
 * @return          0 if successful, the error code otherwise.
 */
int zephyrLedStripSetRgbPixels(ZephyrLedStrip *strip, uint32_t start,
                               uint32_t end, const ZephyrRgbPixel *pixels);

/**
 * @brief   Set the desired GRB pixel.
 *
 * @param strip     The LED strip data structure to set.
 * @param pixelIdx  The index of the pixel to set the color.
 * @param pixel     The pixel new GRB color.
 *
 * @return          0 if successful, the error code otherwise.
*/
int zephyrLedStripSetGrbPixel(ZephyrLedStrip *strip, uint32_t pixelIdx,
                              const ZephyrGrbPixel *pixel);

/**
 * @brief   Set the GRB pixels included between the start and end.
 *
 * @param strip     The LED strip data structure to set.
 * @param start     The index of the starting pixel.
 * @param end       The index of the ending pixel.
 * @param pixels    The pixels new GRB color.
 *
 * @return          0 if successful, the error code otherwise.
 */
int zephyrLedStripSetGrbPixels(ZephyrLedStrip *strip, uint32_t start,
                               uint32_t end, const ZephyrGrbPixel *pixels);

/**
 * @brief   Set the desired RGBW pixel.
 *
 * @param strip     The LED strip data structure to set.
 * @param pixelIdx  The index of the pixel to set the color.
 * @param pixel     The pixel new RGBW color.
 *
 * @return          0 if successful, the error code otherwise.
*/
int zephyrLedStripSetRgbwPixel(ZephyrLedStrip *strip, uint32_t pixelIdx,
                               const ZephyrRgbwPixel *pixel);

/**
 * @brief   Set the RGBW pixels included between the start and end.
 *
 * @param strip     The LED strip data structure to set.
 * @param start     The index of the starting pixel.
 * @param end       The index of the ending pixel.
 * @param pixels    The pixels new RGBW color.
 *
 * @return          0 if successful, the error code otherwise.
 */
int zephyrLedStripSetRgbwPixels(ZephyrLedStrip *strip, uint32_t start,
                                uint32_t end, const ZephyrRgbwPixel *pixels);

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
