/**
 * Copyright (C) 2023 by Electronya
 * 
 * @file      zephyrAdc.c
 * @author    jcharron
 * @date      2023-06-03
 * @brief     ADC of ZephyrWrapper module
 *
 *            This file is the implementation of the ADC wrapper
 * 
 * @ingroup  zephyr-wrapper
 * @{
 */


#include <zephyr/device.h>
#include <zephyr/logging/log.h>

#include "zephyrCommon.h"
#include "zephyrAdc.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

/**
 * @brief The ADC reference voltage.
 */
#define ADC_REF_VOLT              3300

/**
 * @brief The ADC data structure.
 */
typedef struct adcCtrlData
{
  const struct device *adc;                                 /**< The zephyr ADC device. */
  struct adc_channel_cfg chanCfgs[ADC_MAX_CHAN_CNT];        /**< The zephyr ADC channel configuration. */
  uint8_t chanUsedCnt;                                      /**< The number of ADC channel used. */
  struct adc_sequence seq;                                  /**< The zephyr ADC sequence. */
  uint32_t buffers[ADC_MAX_CHAN_CNT];                       /**< The ADC buffers. */
} AdcCtrlData;

/**
 * @brief The DAC data instance.
 */
AdcCtrlData adcCtrlData = {
  .adc = NULL,
  .chanUsedCnt = 0,
  .seq = {
    .buffer_size = sizeof(uint32_t),
  },
};

int zephyrAdcInitChannel(const AdcChanConfig *config)
{
  int rc = -ENXIO;

  adcCtrlData.chanCfgs[config->id].channel_id = config->id;
  adcCtrlData.chanCfgs[config->id].gain = config->gain;
  adcCtrlData.chanCfgs[config->id].acquisition_time =
    ADC_ACQ_TIME(ADC_ACQ_TIME_TICKS, config->acqTime);
  adcCtrlData.chanCfgs[config->id].reference = config->ref;

  rc = adc_channel_setup(adcCtrlData.adc, adcCtrlData.chanCfgs + config->id);
  if(rc < 0)
    LOG_ERR("ERR: %d - Unable to setup channel %d", rc, config->id);

  return rc;
}

int zephyrAdcInit(AdcRes resolution,
                  const AdcChanConfig configs[],
                  const uint8_t cfgCount)
{
  int rc = -ENXIO;

  LOG_INF("initializing ADC with %d channel(s)", cfgCount);
  if(cfgCount > ADC_MAX_CHAN_CNT)
  {
    LOG_ERR("ERR: %d - Configuring to much ADC channel.", rc);
    return rc;
  }

  adcCtrlData.adc = DEVICE_DT_GET(DT_ALIAS(adc));
  if(!adcCtrlData.adc)
  {
    LOG_ERR("ERR: %d - Unable to get ADC binding.", -ENXIO);
    return rc;
  }

  rc = 0;
  adcCtrlData.seq.resolution = resolution;
  adcCtrlData.chanUsedCnt = cfgCount;
  for(uint8_t i = 0; i < cfgCount && rc == 0; ++i)
  {
    rc = zephyrAdcInitChannel(configs + i);
  }

  LOG_INF("ADC initialization done");

  return rc;
}

int zephyrAdcSample(AdcChanId chan, uint32_t *value, flag Vref)
{
  int rc;

  adcCtrlData.seq.channels = BIT(chan);
  adcCtrlData.seq.buffer = (void *)(adcCtrlData.buffers + chan);

  rc = adc_read(adcCtrlData.adc, &(adcCtrlData.seq));
  if(rc)
  {
    LOG_ERR("ERR: %d - Unable to read ADC channel %d.", rc, chan);
    return rc;
  }

  rc = adc_raw_to_millivolts(ADC_REF_VOLT, adcCtrlData.chanCfgs[chan].gain,
      adcCtrlData.seq.resolution, adcCtrlData.buffers + chan);
  if(rc < 0)
  {
    LOG_ERR("ERR: %d - Unable to convert ADC sample of channel %d", rc, chan);
    return rc;
  }

  *value = adcCtrlData.buffers[chan];

  return rc;
}

int zephyrDieTempSample(uint32_t *value)
{
  int rc;

  adcCtrlData.seq.channels = BIT(ADC_DIE_TEMP);
  adcCtrlData.seq.buffer = (void *)(adcCtrlData.buffers + ADC_DIE_TEMP);

  rc = adc_read(adcCtrlData.adc, &(adcCtrlData.seq));
  if(rc)
  {
    LOG_ERR("ERR: %d - Unable to read ADC channel %d.", rc, ADC_DIE_TEMP);
    return rc;
  }

  rc = adc_raw_to_millivolts(ADC_REF_VOLT, adcCtrlData.chanCfgs[chan].gain,
      adcCtrlData.seq.resolution, adcCtrlData.buffers + chan);
  if(rc < 0)
  {
    LOG_ERR("ERR: %d - Unable to convert ADC sample of channel %d", rc, ADC_DIE_TEMP);
    return rc;
  }

  *value = adcCtrlData.buffers[chan];

  return rc;
}

/** @} */
