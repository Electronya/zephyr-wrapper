/**
 * Copyright (C) 2023 by Electronya
 * 
 * @file      zephyrGpio.c
 * @author    jlcharron
 * @date      2023-06-03
 * @brief     GPIO of ZephyrWrapper module
 *
 *            This file is the implementation of the GPIO wrapper.
 * 
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyrGpio.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrCommon.h"

LOG_MODULE_REGISTER(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrGpioInit(ZephyrGpio *gpio, ZephyrGpioDir dir)
{
  int rc = -ENXIO;

  if(!device_is_ready(gpio->dev.port))
  {
    rc = -ENODEV;
    LOG_ERR("ERR: %d - Unable to get %s gpio device.", rc, gpio->label);
    return rc;
  }

  rc = gpio_pin_configure_dt(&(gpio->dev), dir);
  if(rc < 0)
    LOG_ERR("ERR: %d - Unable to configure %s gpio.", rc, gpio->label);

  return rc;
}

int zephyrGpioEnableIrq(ZephyrGpio *gpio, ZephyrGpioIrqTrig trigger)
{
  int rc;

  rc = gpio_pin_interrupt_configure_dt(&(gpio->dev), trigger);
  if(rc < 0)
    LOG_ERR("ERR: %d - Unable to enable %s interrupt.", rc, gpio->label);

  return rc;
}

int zephyrGpioDisableIrq(ZephyrGpio *gpio)
{
  int rc;

  rc = gpio_pin_interrupt_configure_dt(&(gpio->dev), GPIO_INT_DISABLE);
  if(rc < 0)
    LOG_ERR("ERR: %d - Unable to disable the %s interrupt.", rc, gpio->label);

  return rc;
}

int zephyrGpioAddIrqCallback(ZephyrGpio *gpio, ZephyrGpioIrqCb irqCb)
{
  int rc;

  gpio_init_callback(&(gpio->cbStruct), irqCb, BIT(gpio->dev.pin));
  rc = gpio_add_callback(gpio->dev.port, &(gpio->cbStruct));
  if(rc < 0)
    LOG_ERR("ERR: %d - Unable to add %s callback.", rc, gpio->label);

  return rc;
}

int zephyrGpioRemoveIrqCallback(ZephyrGpio *gpio)
{
  return gpio_remove_callback(gpio->dev.port, &(gpio->cbStruct));
}

int zephyrGpioWrite(ZephyrGpio *gpio, ZephyrGpioState state)
{
  return gpio_pin_set_dt(&(gpio->dev), state);
}

int zephyrGpioRead(ZephyrGpio *gpio)
{
  return gpio_pin_get_dt(&(gpio->dev));
}

int zephyrGpioSet(ZephyrGpio *gpio)
{
  return gpio_pin_set_dt(&(gpio->dev), GPIO_ON);
}

int zephyrGpioClear(ZephyrGpio *gpio)
{
  return gpio_pin_set_dt(&(gpio->dev), GPIO_OFF);
}

int zephyrGpioToggle(ZephyrGpio *gpio)
{
  return gpio_pin_toggle_dt(&(gpio->dev));
}

int zephyrGpioPulse(ZephyrGpio *gpio, uint32_t width)
{
  int rc;

  rc = gpio_pin_toggle_dt(&(gpio->dev));
  if(rc < 0)
    return rc;

  k_usleep(width);

  rc = gpio_pin_toggle_dt(&(gpio->dev));
  return rc;
}

/** @} */
