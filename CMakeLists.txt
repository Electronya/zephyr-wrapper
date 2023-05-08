# Electronya Zephyr Wrapper
# Copyright (C) 2023 by Electronya

zephyr_include_directories(src)

# default wrapper utilities.
add_subdirectory(src/zephyrCommon)
# add_subdirectory(src/zephyrThread)

# LED strip wrapper.
if(ENYA_LED_STRIP)
  add_subdirectory(src/zephyrLedStrip)
endif()
