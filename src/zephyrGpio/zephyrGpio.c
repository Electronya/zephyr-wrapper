/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrGpio.c
 * @author    jbacon
 * @date      2023-07-23
 * @brief     GPIO Wrapper
 *
 *            This file is the implementation of the GPIO wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrGpio.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrGpioInit(ZephyrGpio_t *gpio, ZephyrGpioDir_t dir)
{
  int rc = -ENXIO;

  if(!device_is_ready(gpio->dev.port))
  {
    rc = -ENODEV;
    LOG_ERR("gpio %s device not ready", gpio->dev.port->name);
    return rc;
  }

  rc = gpio_pin_configure_dt(&(gpio->dev), dir);
  if(rc < 0)
    LOG_ERR("unable to configure gpio %s", gpio->dev.port->name);

  return rc;
}

int zephyrGpioEnableIrq(ZephyrGpio_t *gpio, ZephyrGpioIrqTrig_t trigger)
{
  int rc;

  rc = gpio_pin_interrupt_configure_dt(&(gpio->dev), trigger);
  if(rc < 0)
    LOG_ERR("unable to enable gpio %s interrupt", gpio->dev.port->name);

  return rc;
}

int zephyrGpioDisableIrq(ZephyrGpio_t *gpio)
{
  int rc;

  rc = gpio_pin_interrupt_configure_dt(&(gpio->dev), GPIO_INT_DISABLE);
  if(rc < 0)
    LOG_ERR("unable to disable gpio %s interrupt", gpio->dev.port->name);

  return rc;
}

int zephyrGpioAddIrqCallback(ZephyrGpio_t *gpio, ZephyrGpioIrqCb_t irqCb)
{
  int rc;

  gpio_init_callback(&(gpio->cbStruct), irqCb, BIT(gpio->dev.pin));
  rc = gpio_add_callback(gpio->dev.port, &(gpio->cbStruct));
  if(rc < 0)
    LOG_ERR("unable to add gpio %s interrupt callback.", gpio->dev.port->name);

  return rc;
}

int zephyrGpioRemoveIrqCallback(ZephyrGpio_t *gpio)
{
  return gpio_remove_callback(gpio->dev.port, &(gpio->cbStruct));
}

int zephyrGpioWrite(ZephyrGpio_t *gpio, ZephyrGpioState_t state)
{
  return gpio_pin_set_dt(&(gpio->dev), state);
}

int zephyrGpioRead(ZephyrGpio_t *gpio)
{
  return gpio_pin_get_dt(&(gpio->dev));
}

int zephyrGpioSet(ZephyrGpio_t *gpio)
{
  return gpio_pin_set_dt(&(gpio->dev), GPIO_SET);
}

int zephyrGpioClear(ZephyrGpio_t *gpio)
{
  return gpio_pin_set_dt(&(gpio->dev), GPIO_CLR);
}

int zephyrGpioToggle(ZephyrGpio_t *gpio)
{
  return gpio_pin_toggle_dt(&(gpio->dev));
}

int zephyrGpioPulse(ZephyrGpio_t *gpio, uint32_t width)
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
