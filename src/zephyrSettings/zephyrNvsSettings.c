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

int zephyrNvsSettingsInit(void)
{
  int rc;

  rc = settings_subsys_init();
  if(rc < 0)
    LOG_ERR("unable to initialize the setting subsystem");

  return rc;
}

int zephyrNvsSettingsRegister(ZephyrNvsSetting_t *setting)
{
  int rc;

  rc = settings_register(setting);
  if(rc < 0)
    LOG_ERR("unable to register setting: %s", setting->name);

  return rc;
}

int zephyrNvsSettingsLoad(void)
{
  int rc;

  rc = settings_load();
  if(rc < 0)
    LOG_ERR("unable to load the settings");

  return rc;
}

int zephyrNvsSettingsLoadSubtree(const char *subtree)
{
  int rc;

  rc = settings_load_subtree(subtree);
  if(rc < 0)
    LOG_ERR("unable to load subtree: %s", subtree);

  return rc;
}

int zephyrNvsSettingsSave(void)
{
  int rc;

  rc = settings_save();
  if(rc < 0)
    LOG_ERR("unable to save the settings");

  return rc;
}

int zephyrNvsSettingsSaveOne(const char *name, const void *value, size_t size)
{
  int rc;

  rc = settings_save_one(name, value, size);
  if(rc < 0)
    LOG_ERR("unable to save setting: %s", name);

  return rc;
}

int zephyrNvsSettingsDelete(const char *name)
{
  int rc;

  rc = settings_delete(name);
  if(rc < 0)
    LOG_ERR("unable to delete setting: %s", name);

  return rc;
}

int zephyrNvsSettingsCommit(void)
{
  int rc;

  rc = settings_commit();
  if(rc < 0)
    LOG_ERR("unable to commit settings");

  return rc;
}

int zephyrNvsSettingsCommitSubtree(const char *subtree)
{
  int rc;

  rc = settings_commit_subtree(subtree);
  if(rc < 0)
    LOG_ERR("unable to commit subtree: %s", subtree);

  return rc;
}

/** @} */
