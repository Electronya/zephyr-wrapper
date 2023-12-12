/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrAdc.c
 * @author    jbacon
 * @date      2023-09-21
 * @brief     ADC Wrapper
 *
 *            This file is the implementation of the ADC wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrAdc.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

typedef struct adcCtrlData
{
  const struct device *adc;           /**< The zephyr ADC device. */
  struct adc_channel_cfg *chanCfgs;   /**< The zephyr ADC channel configuration. */
  uint32_t *buffers;                  /**< The ADC buffers. */
  uint8_t chanUsedCnt;                /**< The number of ADC channel used. */
  struct adc_sequence seq;            /**< The zephyr ADC sequence. */
  uint32_t vdd;                       /**< The VDD value in mV. */
} AdcCtrlData;

/**
 * @brief The ADC control data.
*/
static AdcCtrlData adcCtrlData;

/**
 * @brief   Initialize an ADC channel.
 *
 * @param config  The ADC channel configuration.
 *
 * @return  0 if successful, the error code otherwise.
 */
int initAdcChannel(ZephyrAdcChanConfig_t *config)
{
  int rc;

  adcCtrlData.chanCfgs[config->id].channel_id = config->id;
  adcCtrlData.chanCfgs[config->id].gain = config->gain;
  adcCtrlData.chanCfgs[config->id].acquisition_time =
    ADC_ACQ_TIME(ADC_ACQ_TIME_TICKS, config->acqTime);
  adcCtrlData.chanCfgs[config->id].reference = config->ref;

  rc = adc_channel_setup(adcCtrlData.adc, adcCtrlData.chanCfgs + config->id);
  if(rc < 0)
    LOG_ERR("unable to setup channel %d: %d", config->id, rc);

  return rc;
}

int zephyrAdcInit(ZephyrAdcChanConfig_t *configs, size_t chanCount,
                  ZephyrAdcRes_t res, uint32_t vdd)
{
  int rc = 0;

  adcCtrlData.adc = DEVICE_DT_GET(DT_ALIAS(adc));
  if(!adcCtrlData.adc)
  {
    LOG_ERR("unable to get ADC device");
    return -ENODEV;
  }

  adcCtrlData.vdd = vdd;
  adcCtrlData.seq.resolution = res;
  adcCtrlData.chanUsedCnt = chanCount;
  adcCtrlData.chanCfgs = k_malloc(sizeof(ZephyrAdcChanConfig_t) * chanCount);
  if(!adcCtrlData.chanCfgs)
  {
    LOG_ERR("unable to allocate all the ADC channel config");
    return -ENOSPC;
  }

  for(uint32_t i = 0; i < chanCount && rc == 0; ++i)
  {
    rc = initAdcChannel(configs + i);
  }

  if(rc < 0)
    k_free(adcCtrlData.chanCfgs);

  return rc;
}

int zephyrAdcGetSample(uint32_t configIdx, uint32_t *sample)
{
  int rc;

  if(configIdx > adcCtrlData.chanUsedCnt || configIdx == 0)
    return -EINVAL;

  adcCtrlData.seq.channels = BIT(adcCtrlData.chanCfgs[configIdx].channel_id);
  adcCtrlData.seq.buffer = (void *)sample;

  rc = adc_read(adcCtrlData.adc, &adcCtrlData.seq);
  if(rc < 0)
  {
    LOG_ERR("unable to sample ADC channel %d: %d",
      adcCtrlData.chanCfgs[configIdx].channel_id, rc);
    return rc;
  }

  rc = adc_raw_to_millivolts(adcCtrlData.vdd,
    adcCtrlData.chanCfgs[configIdx].gain, adcCtrlData.seq.resolution, sample);
  if(rc < 0)
    LOG_ERR("unable to convert ADC raw data to mV of channel %d: %d",
      adcCtrlData.chanCfgs[configIdx].channel_id, rc);

  return rc;
}

/** @} */
