# Electronya Zephyr Wrapper
# Copyright (C) 2023 by Electronya

if(CONFIG_ENYA_ZEPHYR_WRAPPER)
  message("RPOUT")
  zephyr_include_directories(./src/)
  zephyr_library()

  # default wrapper utilities.
  zephyr_library_sources(
    src/zephyrCommon/zephyrCommon.c
    #src/zephyrThread/zephyrThread.c
  )

  # LED strip wrapper.
  zephyr_library_sources_ifdef(CONFIG_ENYA_LED_STRIP src/zephyrLedStrip/zephyrLedStrip.c)
endif()
