/**
 * @file      zephyrGpio.h
 * @author    jbacon
 * @date      2021-02-14
 * @brief     GPIO of ZephyrWrapper module
 * 
 *            This file is the declaration or the GPIO wrapper.
 *
 * @defgroup  zephyr-wrapper zephyr-wrapper
 * @brief     The ZephyrWrapper module implements the a wrapper around
 *            Zephyr hardware access.
 * @{
 */

#ifndef GPIO_WRAPPER
#define GPIO_WRAPPER

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/**
 * @brief The GPIO data structure.
 */
typedef struct zephyrGpio
{
  const char *label;                /**< The GPIO label. */
  const struct gpio_dt_spec dev;    /**< The GPIO device. */
  struct gpio_callback cbStruct;    /**< The callback structure. */
} ZephyrGpio;

/**
 * @brief The zephyr GPIO directions.
*/
typedef enum
{
  GPIO_IN         = GPIO_INPUT,           /**< The GPIO INPUT direction. */
  GPIO_OUT        = GPIO_OUTPUT,          /**< The GPIO OUTPUT direction, */
  GPIO_OUT_INACT  = GPIO_OUTPUT_INACTIVE, /**< The GPIO OUTPUT direction initialized as inactive. */
  GPIO_OUT_ACT    = GPIO_OUTPUT_ACTIVE,   /**< The GPIO OUTPUT direction initialized as active. */
} ZephyrGpioDir;

/**
 * @brief The zephyr GPIO interrupt triggers.
*/
typedef enum
{
  GPIO_IRQ_EDGE_RISING  = GPIO_INT_EDGE_RISING,       /**< The GPIO interrupt rising edge trigger. */
  GPIO_IRQ_EDGE_FALLING = GPIO_INT_EDGE_FALLING,      /**< The GPIO interrupt falling edge trigger. */
  GPIO_IRQ_EDGE_BOTH    = GPIO_INT_EDGE_BOTH,         /**< The GPIO interrupt both edge trigger. */
  GPIO_IRQ_EDGE_INACT   = GPIO_INT_EDGE_TO_INACTIVE,  /**< The GPIO interrupt edge to inactive level trigger. */
  GPIO_IRQ_EDGE_ACT     = GPIO_INT_EDGE_TO_ACTIVE,    /**< The GPIO interrupt edge to active level trigger. */
  GPIO_IRQ_INACT        = GPIO_INT_LEVEL_INACTIVE,    /**< The GPIO interrupt inactive level trigger. */
  GPIO_IRQ_ACT          = GPIO_INT_LEVEL_ACTIVE,      /**< The GPIO interrupt active level trigger. */
} ZephyrGpioIrqTrig;

/**
 * @brief The GPIO IRQ callback function.
 */
typedef gpio_callback_handler_t ZephyrGpioIrqCb;

/**
 * @brief The Zephyr GPIO states.
 */
typedef enum
{
  GPIO_OFF = 0,                     /**< The GPIO OFF state. */
  GPIO_ON = 1,                      /**< The GPIO ON state. */
} ZephyrGpioState;

/**
 * @brief Initialize GPIO.
 *
 * @param gpio    The data structure of the GPIO to initialize.
 * @param dir     The GPIO direction flag.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioInit(ZephyrGpio *gpio, ZephyrGpioDir dir);

/**
 * @brief Enable the GPIO interrupt.
 *
 * @param gpio    The data structure of the GPIO.
 * @param trigger The GPIO IRQ trigger.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioEnableIrq(ZephyrGpio *gpio, ZephyrGpioIrqTrig trigger);

/**
 * @brief Disable the GPIO interrupt.
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
*/
int zephyrGpioDisableIrq(ZephyrGpio *gpio);

/**
 * @brief Add an IRQ callback.
 *
 * @param gpio    The data structure of the GPIO.
 * @param irqCb   The IRQ callback.
 *
 * @return        0 if successful, the error code otherwise.
*/
int zephyrGpioAddIrqCallback(ZephyrGpio *gpio, ZephyrGpioIrqCb irqCb);

/**
 * @brief Remove an IRQ callback.
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
*/
int zephyrGpioRemoveIrqCallback(ZephyrGpio *gpio);

/**
 * @brief Write GPIO state.
 *
 * @param gpio    The data structure of the GPIO.
 * @param state   The new GPIO state.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioWrite(ZephyrGpio *gpio, ZephyrGpioState state);

/**
 * @brief Read the state of the GPIO.
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        The GPIO state (0 or 1) if successful,
 *                the error code otherwise.
 */
int zephyrGpioRead(ZephyrGpio *gpio);

/**
 * @brief Set the GPIO (set state to ON).
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioSet(ZephyrGpio *gpio);

/**
 * @brief Clear the GPIO (set state to OFF).
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioClear(ZephyrGpio *gpio);

/**
 * @brief Toggle the GPIO (flip the state).
 *
 * @param gpio    The data structure of the GPIO.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioToggle(ZephyrGpio *gpio);

/**
 * @brief Pulse the GPIO (two toggle separated by X time).
 *
 * @param gpio    The data structure of the GPIO.
 * @param width   The width of the desired pulse in us.
 *
 * @return        0 if successful, the error code otherwise.
 */
int zephyrGpioPulse(ZephyrGpio *gpio, uint32_t width);

#endif      /* GPIO_WRAPPER */

/** @} */
