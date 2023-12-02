/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrACM.h
 * @author    jbacon
 * @date      2023-08-25
 * @brief     USB ACM Wrapper
 *
 *            This file is the declaration of the USB ACM wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef USB_ACM_WRAPPER
#define USB_ACM_WRAPPER

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/ring_buffer.h>

/**
 * @brief   The ACM data struct.
*/
typedef struct
{
  const struct device *dev;                 /**< The ACM device. */
  struct ring_buf rxRingBuf;                /**< The ACM Rx ring buffer. */
  uint8_t *rxBuffer;                        /**< The ACM Rx buffer. */
  struct ring_buf txRingBuf;                /**< The ACM Tx ring buffer. */
  uint8_t *txBuffer;                        /**< The ACM Tx buffer. */
  uart_irq_callback_user_data_t cb;         /**< The ACM interrupt callback. */
} ZephyrACM_t;

/**
 * @brief   The ACM control lines.
*/
typedef enum
{
  ACM_BAUD_CTRL = UART_LINE_CTRL_BAUD_RATE,   /**< The ACM baud rate control line. */
  ACM_RTS = UART_LINE_CTRL_RTS,               /**< The ACM RTS control line. */
  ACM_DTR = UART_LINE_CTRL_DTR,               /**< The ACM DTR control line. */
  ACM_DCD = UART_LINE_CTRL_DCD,               /**< The ACM DCD control line. */
  ACM_DSR = UART_LINE_CTRL_DSR,               /**< The ACM DSR control line. */
} ZephyrAcmCtrlLine_t;

/**
 * @brief   Initialize the ACM.
 *
 * @param acm       The ACM device to initialize.
 * @param rxBufSize The ACM Rx buffer size.
 * @param txBufSize The ACM Tx buffer size.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrAcmInit(ZephyrACM_t *acm, size_t rxBufSize, size_t txBufsize);

/**
 * @brief   Get the state of a control line.
 *
 * @param acm       The ACM device.
 * @param ctrlLine  The control line ID.
 * @param lineVal   the returned line value.
 * @return  0 if successful, the error code otherwise.
 */
int zephyrAcmGetCtrlLine(ZephyrACM_t *acm, ZephyrAcmCtrlLine_t ctrlLine,
                         uint32_t *lineVal);

/**
 * @brief   Set the state of a control line.
 *
 * @param acm       The ACM device.
 * @param ctrlLine  The control line ID.
 * @param lineVal   the line value.
 * @return  0 if successful, the error code otherwise.
 */
int zephyrAcmSetCtrlLine(ZephyrACM_t *acm, ZephyrAcmCtrlLine_t ctrlLine,
                         uint32_t lineVal);

/**
 * @brief   Enable the Tx interrupt.
 *
 * @param acm   The ACM device.
 */
void zephyrAcmEnableTxIrq(ZephyrACM_t *acm);

/**
 * @brief   Disable the Tx interrupt.
 *
 * @param acm   The ACM device.
 */
void zephyrAcmDisableTxIrq(ZephyrACM_t *acm);

/**
 * @brief   Enable the Rx interrupt.
 *
 * @param acm   The ACM device.
 */
void zephyrAcmEnableRxIrq(ZephyrACM_t *acm);

/**
 * @brief   Disable the Rx interrupt.
 *
 * @param acm   The ACM device.
 */
void zephyrAcmDisableRxIrq(ZephyrACM_t *acm);

/**
 * @brief   Start processing ACM interrupt.
 *
 * @param acm   The ACM device.
 *
 * @return  1 if successful, the error code otherwise.
 */
int zephyrAcmIrqUpdate(ZephyrACM_t *acm);

/**
 * @brief   Check if their is an IRQ pending.
 *
 * @param acm   The ACM device.
 *
 * @return  1 if an IRQ is pending, the error code otherwise.
 */
int zephyrAcmIsIrqPending(ZephyrACM_t *acm);

/**
 * @brief   Check if there is data in the Rx FIFO.
 *
 * @param acm   The ACM device.
 *
 * @return  1 if there is data in the FIFO, 0 if the FIFO is empty, the error
 *          error code otherwise.
 */
int zephyrAcmIsRxIrqReady(ZephyrACM_t *acm);

/**
 * @brief   Check if the Tx FIFO is ready to be written in.
 *
 * @param acm   The ACM device.
 *
 * @return  1 if the FIFO is ready t be written in, 0 if the FIFO is full, the
 *          error code otherwise.
 */
int zephyrAcmIsTxIrqReady(ZephyrACM_t *acm);

/**
 * @brief   Read from the Rx fifo.
 *
 * @param acm   The ACM device.
 *
 * @return  The number of byte read if successful, the error code otherwise.
 */
int zephyrAcmReadFifo(ZephyrACM_t *acm);

/**
 * @brief   Write to the Tx fifo.
 *
 * @param acm   The ACM device.
 *
 * @return  The number of byte written if successful, the error code otherwise.
 */
int zephyrAcmWriteFifo(ZephyrACM_t *acm);

/**
 * @brief   Read from the Rx ring buffer.
 *
 * @param acm         The ACM device.
 * @param dataBuf     The data buffer.
 * @param dataBufSize The data buffer size.
 *
 * @return  The number of byte read if successful, the error code otherwise.
 */
int zephyrAcmReadRingBuffer(ZephyrACM_t *acm, uint8_t *dataBuf,
                            size_t dataBufSize);

/**
 * @brief   Write to the Tx ring buffer.
 *
 * @param acm         The ACM device.
 * @param dataBuf     The data buffer.
 * @param dataBufSize The data budder size.
 *
 * @return  The number of byte written if successful, the error code otherwise.
 */
int zephyrAcmWriteRingBuffer(ZephyrACM_t *acm, uint8_t *dataBuf,
                             size_t dataBufSize);

#endif    /* USB_ACM_WRAPPER */

/** @} */
