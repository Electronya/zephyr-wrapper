/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrGpio.h
 * @author    jbacon
 * @date      2023-07-23
 * @brief     GPIO Wrapper
 *
 *            This file is the declaration of the GPIO wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef GPIO_WRAPPER
#define GPIO_WRAPPER

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/**
 * @brief   The GPIO data structure.
 */
typedef struct zephyrGpio
{
  const struct gpio_dt_spec dev;                      /**< The GPIO device. */
  struct gpio_callback cbStruct;                      /**< The callback structure. */
} ZephyrGpio_t;

/**
 * @brief   The zephyr GPIO directions.
*/
typedef enum
{
  GPIO_IN         = GPIO_INPUT,                       /**< The GPIO INPUT direction. */
  GPIO_OUT        = GPIO_OUTPUT,                      /**< The GPIO OUTPUT direction, */
  GPIO_OUT_CLR    = GPIO_OUTPUT_INACTIVE,             /**< The GPIO OUTPUT direction initialized as cleared. */
  GPIO_OUT_SET    = GPIO_OUTPUT_ACTIVE,               /**< The GPIO OUTPUT direction initialized as set. */
} ZephyrGpioDir_t;

/**
 * @brief   The zephyr GPIO interrupt triggers.
*/
typedef enum
{
  GPIO_IRQ_EDGE_RISING  = GPIO_INT_EDGE_RISING,       /**< The GPIO interrupt rising edge trigger. */
  GPIO_IRQ_EDGE_FALLING = GPIO_INT_EDGE_FALLING,      /**< The GPIO interrupt falling edge trigger. */
  GPIO_IRQ_EDGE_BOTH    = GPIO_INT_EDGE_BOTH,         /**< The GPIO interrupt both edge trigger. */
  GPIO_IRQ_EDGE_CLR     = GPIO_INT_EDGE_TO_INACTIVE,  /**< The GPIO interrupt edge to clear state trigger. */
  GPIO_IRQ_EDGE_SET     = GPIO_INT_EDGE_TO_ACTIVE,    /**< The GPIO interrupt edge to set state trigger. */
  GPIO_IRQ_CLR          = GPIO_INT_LEVEL_INACTIVE,    /**< The GPIO interrupt clear state trigger. */
  GPIO_IRQ_SET          = GPIO_INT_LEVEL_ACTIVE,      /**< The GPIO interrupt set state trigger. */
} ZephyrGpioIrqTrig_t;

/**
 * @brief   The GPIO IRQ callback function.
 */
typedef gpio_callback_handler_t ZephyrGpioIrqCb_t;

/**
 * @brief   The Zephyr GPIO states.
 */
typedef enum
{
  GPIO_CLR = 0,                                       /**< The GPIO clear state. */
  GPIO_SET = 1,                                       /**< The GPIO set state. */
} ZephyrGpioState_t;

/**
 * @brief   Initialize GPIO.
 *
 * @param gpio    The data structure of the GPIO to initialize.
 * @param dir     The GPIO direction flag.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioInit(ZephyrGpio_t *gpio, ZephyrGpioDir_t dir);

/**
 * @brief   Enable the GPIO interrupt.
 *
 * @param gpio    The data structure of the GPIO.
 * @param trigger The GPIO IRQ trigger.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioEnableIrq(ZephyrGpio_t *gpio, ZephyrGpioIrqTrig_t trigger);

/**
 * @brief   Disable the GPIO interrupt.
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
*/
int zephyrGpioDisableIrq(ZephyrGpio_t *gpio);

/**
 * @brief   Add an IRQ callback.
 *
 * @param gpio    The data structure of the GPIO.
 * @param irqCb   The IRQ callback.
 *
 * @return        0 if successful, the error code otherwise.
*/
int zephyrGpioAddIrqCallback(ZephyrGpio_t *gpio, ZephyrGpioIrqCb_t irqCb);

/**
 * @brief   Remove an IRQ callback.
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
*/
int zephyrGpioRemoveIrqCallback(ZephyrGpio_t *gpio);

/**
 * @brief   Write GPIO state.
 *
 * @param gpio    The data structure of the GPIO.
 * @param state   The new GPIO state.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioWrite(ZephyrGpio_t *gpio, ZephyrGpioState_t state);

/**
 * @brief   Read the state of the GPIO.
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        The GPIO state (0 or 1) if successful,
 *                the error code otherwise.
 */
int zephyrGpioRead(ZephyrGpio_t *gpio);

/**
 * @brief   Set the GPIO (set state to ON).
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioSet(ZephyrGpio_t *gpio);

/**
 * @brief   Clear the GPIO (set state to OFF).
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioClear(ZephyrGpio_t *gpio);

/**
 * @brief   Toggle the GPIO (flip the state).
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioToggle(ZephyrGpio_t *gpio);

/**
 * @brief   Pulse the GPIO (two toggle separated by X time).
 *
 * @param gpio    The data structure of the GPIO.
 * @param width   The width of the desired pulse in us.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioPulse(ZephyrGpio_t *gpio, uint32_t width);

#endif    /* GPIO_WRAPPER */

/** @} */
