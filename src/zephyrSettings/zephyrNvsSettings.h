/**
 * Copyright (C) 2024 by Electronya
 *
 * @file      zephyrNvsSettings.h
 * @author    jbacon
 * @date      2024-02-08
 * @brief     NVS Settings Wrapper
 *
 *            This file is the declaration of the NVS settings wrapper.
 *
 * @ingroup  zephyr-wrapper
 * @{
 */

#ifndef NVS_SETTINGS_WRAPPER
#define NVS_SETTINGS_WRAPPER

#include <zephyr/kernel.h>
#include <zephyr/settings/settings.h>

/**
 * @brief The setting handler structure.
*/
typedef struct settings_handler ZephyrNvsSetting_t;

/**
 * @brief   Initalize the settings subsystem.
 *
 * @return  o if successful, the error code otherwise.
 */
int zephyrNvsSettingsInit(void);

/**
 * @brief   Register a setting.
 *
 * @param setting   The setting structure.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrNvsSettingsRegister(ZephyrNvsSetting_t *setting);

/**
 * @brief   Load the settings full tree.
 *
 * @return  0 if successful, the error code othrwise.
 */
int zephyrNvsSettingsLoad(void);

/**
 * @brief   Load the specified subtree of settings
 *
 * @param subtree   The subtree name.
 *
 * @return  0 if successful, the error otherwise.
 */
int zephyrNvsSettingsLoadSubtree(const char *subtree);

/**
 * @brief   Save the settings full tree.
 *
 * @return  0if successful, the error code otherwise.
 */
int zephyrNvsSettingsSave(void);

/**
 * @brief   Save a single setting.
 *
 * @param name      The setting name.
 * @param value     The setting value.
 * @param size      The setting value size.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrNvsSettingsSaveOne(const char *name, const void *value, size_t size);

/**
 * @brief   Delete a particular setting.
 *
 * @param name      The setting name.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrNvsSettingsDelete(const char *name);

/**
 * @brief   Commit the settings full tree.
 *
 * @return 0 if successful, the error code otherwise.
 */
int zephyrNvsSettingsCommit(void);

/**
 * @brief   Commit a subtree of settings.
 *
 * @param name      The settings subtree name.
 *
 * @return  0 if successful, the error code otherwise.
 */
int zephyrNvsSettingsCommitSubtree(const char *name);

#endif    /* NVS_SETTINGS_WRAPPER */

/** @} */
