/**
 * Copyright (C) 2023 by Electronya
 *
 * @file      zephyrACM.c
 * @author    jbacon
 * @date      2023-08-25
 * @brief     USB ACM Wrapper
 *
 *            This file is the implementation of the USB ACM wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "zephyrACM.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrAcmInit(ZephyrACM *acm, size_t rxBufSize, size_t txBufsize)
{
  int rc;

  acm->dev = DEVICE_DT_GET_ONE(zephyr_cdc_acm_uart);
	if (!device_is_ready(acm->dev))
  {
		LOG_ERR("CDC ACM device not ready");
		return -ENODEV;
	}

  acm->rxBuffer = k_malloc(rxBufSize);
  if(!acm->rxBuffer)
  {
    LOG_ERR("unable to allocate Rx buffer");
    return -ENOSPC;
  }

  acm->txBuffer = k_malloc(txBufsize);
  if(!acm->txBuffer)
  {
    LOG_ERR("unable the allocate Tx buffer");
    k_free(acm->rxBuffer);
    return -ENOSPC;
  }

  ring_buf_init(&acm->rxRingBuf, rxBufSize, acm->rxBuffer);
  ring_buf_init(&acm->txRingBuf, txBufsize, acm->txBuffer);

  rc = uart_irq_callback_set(acm->dev, acm->cb);
  if(rc < 0)
    LOG_ERR("unable to set the IRQ callback");

  return rc;
}

int zephyrAcmGetCtrlLine(ZephyrACM *acm, ZephyrAcmCtrlLine ctrlLine,
                         uint32_t *lineVal)
{
  return uart_line_ctrl_get(acm->dev, ctrlLine, lineVal);
}

int zephyrAcmSetCtrlLine(ZephyrACM *acm, ZephyrAcmCtrlLine ctrlLine,
                         uint32_t lineVal)
{
  return uart_line_ctrl_set(acm->dev, ctrlLine, lineVal);
}

void zephyrAcmEnableTxIrq(ZephyrACM *acm)
{
  uart_irq_rx_enable(acm->dev);
}

void zephyrAcmDisableTxIrq(ZephyrACM *acm)
{
  uart_irq_rx_disable(acm->dev);
}

void zephyrAcmEnableRxIrq(ZephyrACM *acm)
{
  uart_irq_tx_enable(acm->dev);
}

void zephyrAcmDisableRxIrq(ZephyrACM *acm)
{
  uart_irq_tx_disable(acm->dev);
}

int zephyrAcmIrqUpdate(ZephyrACM *acm)
{
  return uart_irq_update(acm->dev);
}

int zephyrAcmIsIrqPending(ZephyrACM *acm)
{
  return uart_irq_is_pending(acm->dev);
}

int zephyrAcmIsRxIrqReady(ZephyrACM *acm)
{
  return uart_irq_rx_ready(acm->dev);
}

int zephyrAcmIsTxIrqREady(ZephyrACM *acm)
{
  return uart_irq_tx_ready(acm->dev);
}

int zephyrAcmReadFifo(ZephyrACM *acm)
{
  int rc;
  int rxByteCount;
  uint8_t *freeHead;
  size_t freeSpace;

  freeSpace = ring_buf_space_get(&acm->rxRingBuf);
  freeSpace = ring_buf_put_claim(&acm->rxRingBuf, &freeHead, freeSpace);

  rxByteCount = uart_fifo_read(acm->dev, freeHead, freeSpace);
  if(rxByteCount < 0)
  {
    LOG_ERR("unable to read form the fifo");
    rxByteCount = 0;
  }

  rc = ring_buf_put_finish(&acm->rxRingBuf, rxByteCount);
  if(rc < 0)
  {
    LOG_ERR("unable to transfer data from fifo to ring buffer");
    return rc;
  }

  return rxByteCount;
}

int zephyrAcmWriteFifo(ZephyrACM *acm)
{
  int rc;
  int txByteCount;
  uint8_t *head;
  size_t usedSpace;

  usedSpace = ring_buf_size_get(&acm->txRingBuf) -
    ring_buf_space_get(&acm->txRingBuf);
  usedSpace = ring_buf_get_claim(&acm->txRingBuf, &head, usedSpace);

  txByteCount = uart_fifo_fill(acm->dev, head, usedSpace);
  if(txByteCount < 0)
  {
    LOG_ERR("unable to write to the fifo");
    txByteCount = 0;
  }

  rc = ring_buf_get_finish(&acm->txRingBuf, txByteCount);
  if(rc < 0)
  {
    LOG_ERR("unable to transfer data from ring buffer to fifo");
    return rc;
  }

  return txByteCount;
}

int zephyrAcmReadRingBuffer(ZephyrACM *acm, uint8_t *dataBuf,
                            size_t dataBufSize)
{
  return ring_buf_get(&acm->rxRingBuf, dataBuf, dataBufSize);
}

int zephyrAcmWriteRingBuffer(ZephyrACM *acm, uint8_t *dataBuf,
                             size_t dataBufSize)
{
  return ring_buf_put(&acm->txRingBuf, dataBuf, dataBufSize);
}

/** @} */
