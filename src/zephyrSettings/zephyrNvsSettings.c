/**
 * Copyright (C) 2024 by Electronya
 *
 * @file      zephyrNvsSettings.h
 * @author    jbacon
 * @date      2024-02-08
 * @brief     NVS Settings Wrapper
 *
 *            This file is the implementation of the NVS setting wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#include "zephyrNvsSettings.h"
#include "zephyrCommon.h"

LOG_MODULE_DECLARE(ZEPHYR_WRAPPER_MODULE_NAME);

int zephyrNvsSettingsRegister(ZephyrNvsSetting_t *setting)
{
  return 0;
}

int zephyrNvsSettingsLoad(void)
{
  return 0;
}

int zephyrNvsSettingsLoadSubtree(const char *subtree)
{
  return 0;
}

int zephyrNvsSettingsSave(void)
{
  return 0;
}

int zephyrNvsSettingsSaveOne(const char *name, const void *value, size_t size)
{
  return 0;
}

int zephyrNvsSettingsDelete(const char *name)
{
  return 0;
}

int zephyrNvsSettingsCommit(void)
{
  return 0;
}

int zephyrNvsSettingsCommitSubtree(const char *name)
{
  return 0;
}

/** @} */
