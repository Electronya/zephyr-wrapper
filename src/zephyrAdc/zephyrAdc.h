/**
 * Copyright (C) 2023 by Electronya
 * 
 * @file      zephyrAdc.h
 * @author    jlcharron
 * @date      2023-06-03
 * @brief     ADC of ZephyrWrapper module
 * 
 *            This file is the declaration of the ADC wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef ADC_WRAPPER
#define ADC_WRAPPER

#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>

/**
 * @brief ADC channel ID.
 */
typedef enum
{
  ADC_CHAN_0 = 0,                   /**< The ADC channel 0. */
  ADC_CHAN_1 = 1,                   /**< The ADC channel 1. */
  ADC_CHAN_2 = 2,                   /**< The ADC channel 2. */
  ADC_CHAN_3 = 3,                   /**< The ADC channel 3. */
  ADC_CHAN_4 = 4,                   /**< The ADC channel 4. */
  ADC_CHAN_5 = 5,                   /**< The ADC channel 5. */
  ADC_CHAN_6 = 6,                   /**< The ADC channel 6. */
  ADC_CHAN_7 = 7,                   /**< The ADC channel 7. */
  ADC_CHAN_8 = 8,                   /**< The ADC channel 8. */
  ADC_CHAN_9 = 9,                   /**< The ADC channel 9. */
  ADC_CHAN_10 = 10,                 /**< The ADC channel 10. */
  ADC_CHAN_11 = 11,                 /**< The ADC channel 11. */
  ADC_CHAN_12 = 12,                 /**< The ADC channel 12. */
  ADC_CHAN_13 = 13,                 /**< The ADC channel 13. */
  ADC_CHAN_14 = 14,                 /**< The ADC channel 14. */
  ADC_CHAN_15 = 15,                 /**< The ADC channel 15. */
  ADC_MAX_CHAN_CNT,                 /**< The ADC maximal channel count. */
  ADC_DIE_TEMP,                     /**< The die temperature ADC channel. */
  ADC_VREF,                         /**< The Vref ADC channel*/
} AdcChanId;

/**
 * @brief ADC channel gains.
 */
typedef enum
{
  ADC_UNIT_GAIN = ADC_GAIN_1,       /**< The ADC 0 gain level. */
} AdcChanGain;

/**
 * @brief ADC channel reference.
 */
typedef enum
{
  ADC_INT_REF = ADC_REF_INTERNAL,   /**< The ADC channel internal reference. */
} AdcChanRef;

/**
 * @brief ADC channel acquisition time.
 */
typedef enum
{
  ADC_ACQ_2_CYCLES = 2,             /**< The ADC channel 2 cycles acquisition time. */
  ADC_ACQ_8_CYCLES = 8,             /**< The ADC channel 8 cycles acquisition time. */
  ADC_ACQ_14_CYCLES = 14,           /**< The ADC channel 14 cycles acquisition time. */
  ADC_ACQ_29_CYCLES = 29,           /**< The ADC channel 29 cycles acquisition time. */
  ADC_ACQ_42_CYCLES = 42,           /**< The ADC channel 42 cycles acquisition time. */
  ADC_ACQ_56_CYCLES = 56,           /**< The ADC channel 56 cycles acquisition time. */
  ADC_ACQ_72_CYCLES = 72,           /**< The ADC channel 72 cycles acquisition time. */
  ADC_ACQ_240_CYCLES = 240,         /**< The ADC channel 240 cycles acquisition time. */
} AdcChanAcqTime;

/**
 * @brief ADC channel configuration.
 */
typedef struct adcChanConfig
{
  AdcChanId id;                     /**< The ADC channel ID. */
  AdcChanGain gain;                 /**< The ADC channel gain. */
  AdcChanRef ref;                   /**< The ADC channel reference. */
  AdcChanAcqTime acqTime;           /**< The ADC channel acquisition time. */
} AdcChanConfig;

/**
 * @brief ADC resolution.
 */
typedef enum
{
  ADC_6BITS_RES = 6,                /**< The ADC 6 bits resolution. */
  ADC_8BITS_RES = 8,                /**< The ADC 8 bits resolution. */
  ADC_10BITS_RES = 10,              /**< The ADC 10 bits resolution. */
  ADC_12BITS_RES = 12,              /**< The ADC 12 bits resolution. */
} AdcRes;

/**
 * @brief Initialize ADC.
 *
 * @param resolution    The ADC resolution.
 * @param configs       The ADC channel configurations.
 * @param cfgCount      The ADC channel configuration count.
 *
 * @return              0 if successful, the error code otherwise.
 */
int zephyrAdcInit(AdcRes resolution,
                  const AdcChanConfig configs[],
                  const uint8_t cfgCount);

/**
 * @brief Sample an ADC channel.
 *
 * @param chan      The channel to update.
 * @param value     The sampled value in mV.
 *
 * @return          0 if successful, the error code otherwise.
 */
int zephyrAdcSample(AdcChanId chan, uint32_t *value);

/**
 * @brief Sample the die temperature ADC channel.
 *
 * @param value     The sampled value in degree C.
 *
 * @return          0 if successful, the error code otherwise.
 */
int zephyrDieTempSample(uint32_t *value);

#endif      /* ADC_WRAPPER */

/** @} */
