# Electronya Zephyr Wrapper
# Copyright (C) 2023 by Electronya

if(CONFIG_ENYA_ZEPHYR_WRAPPER)
  zephyr_include_directories(
    ./src/zephyrCommon/
  )
  zephyr_library()

  # default wrapper utilities.
  zephyr_library_sources(
    ./src/zephyrCommon/zephyrCommon.c
    #./src/zephyrThread/zephyrThread.c
  )

  # LED strip wrapper.
  if(CONFIG_ENYA_LED_STRIP)
    zephyr_include_directories(./src/zephyrLedStrip/)
    if(NOT DEFINED CONFIG_ZTEST)
      zephyr_library_sources(./src/zephyrLedStrip/zephyrLedStrip.c)
    endif()
  endif()
endif()
