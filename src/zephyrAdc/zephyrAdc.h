/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrAdc.h
 * @author    jbacon
 * @date      2023-09-21
 * @brief     ADC Wrapper
 *
 *            This file is the declaration of the ADC wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef ZEPHYR_ADC_WRAPPER
#define ZEPHYR_ADC_WRAPPER

#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>

/**
 * @brief ADC channel ID. These channel are based on the STM32 devices.
 */
typedef enum
{
  ADC_CHAN_0 = 0,                   /**< The ADC channel 0. */
  ADC_CHAN_1,                       /**< The ADC channel 1. */
  ADC_CHAN_2,                       /**< The ADC channel 2. */
  ADC_CHAN_3,                       /**< The ADC channel 3. */
  ADC_CHAN_4,                       /**< The ADC channel 4. */
  ADC_CHAN_5,                       /**< The ADC channel 5. */
  ADC_CHAN_6,                       /**< The ADC channel 6. */
  ADC_CHAN_7,                       /**< The ADC channel 7. */
  ADC_CHAN_8,                       /**< The ADC channel 8. */
  ADC_CHAN_9,                       /**< The ADC channel 9. */
  ADC_CHAN_10,                      /**< The ADC channel 10. */
  ADC_CHAN_11,                      /**< The ADC channel 11. */
  ADC_CHAN_12,                      /**< The ADC channel 12. */
  ADC_CHAN_13,                      /**< The ADC channel 13. */
  ADC_CHAN_14,                      /**< The ADC channel 14. */
  ADC_CHAN_15,                      /**< The ADC channel 15. */
  ADC_DIE_TEMP,                     /**< The die temperature ADC channel. */
  ADC_VREF,                         /**< The Vref ADC channel*/
  ADC_MAX_CHAN_CNT,                 /**< The ADC maximal channel count. */
} ZephyrAdcChanId;
#endif    /* ZEPHYR_ADC_WRAPPER */

/**
 * @brief ADC channel gains.
 */
typedef enum
{
  ADC_UNIT_GAIN = ADC_GAIN_1,       /**< The ADC 0 gain level. */
} ZephyrAdcChanGain;

/**
 * @brief ADC channel reference.
 */
typedef enum
{
  ADC_VDD_REF = ADC_REF_VDD_1,            /**< VDD. */
	ACD_VDD_1_2_REF = ADC_REF_VDD_1_2,      /**< VDD/2. */
	ADC_VDD_1_3_REF = ADC_REF_VDD_1_3,      /**< VDD/3. */
	ADC_VDD_1_4_REF = ADC_REF_VDD_1_4,      /**< VDD/4. */
  ADC_INT_REF = ADC_REF_INTERNAL,         /**< The ADC channel internal reference. */
  ADC_EXT0_REF = ADC_REF_EXTERNAL0,       /**< External, input 0. */
	ADC_EXT1_REF = ADC_REF_EXTERNAL1,       /**< External, input 1. */
} ZephyrAdcChanRef;

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
} ZephyrAdcChanAcqTime;

/**
 * @brief ADC resolution.
 */
typedef enum
{
  ADC_6BITS_RES = 6,                /**< The ADC 6 bits resolution. */
  ADC_8BITS_RES = 8,                /**< The ADC 8 bits resolution. */
  ADC_10BITS_RES = 10,              /**< The ADC 10 bits resolution. */
  ADC_12BITS_RES = 12,              /**< The ADC 12 bits resolution. */
} ZephyrAdcRes;

/**
 * @brief ADC channel configuration.
 */
typedef struct adcChanConfig
{
  ZephyrAdcChanId id;               /**< The ADC channel ID. */
  ZephyrAdcChanGain gain;           /**< The ADC channel gain. */
  ZephyrAdcChanRef ref;             /**< The ADC channel reference. */
  ZephyrAdcChanAcqTime acqTime;     /**< The ADC channel acquisition time. */
} ZephyrAdcChanConfig;

/**
 * @brief   Initialize the ADC.
 *
 * @param configs     The ADC channel configuration.
 * @param chanCount   The number of ADC channel configuration.
 * @param res         The ADC resolution.
 * @param vdd         The VDD reference voltage in mV.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrAdcInit(ZephyrAdcChanConfig *configs, size_t chanCount,
                  ZephyrAdcRes res, uint32_t vdd);

/**
 * @brief   Get an ADC sample from the specified channel.
 *
 * @param id          The ADC channel ID.
 * @param sample      The sample.
 *
 * @return  0 fi successful, the error code otherwise.
 */
int zephyrAdcGetSample(ZephyrAdcChanId id, uint32_t *sample);

/** @} */
