# Electronya Zephyr Wrapper
# Copyright (C) 2023 by Electronya

if(ENYA_ZEPHYR_WRAPPER)
  zephyr_include_directories(src)
  zephyr_library()

  # default wrapper utilities.
  zephyr_library_sources(
    src/zephyrCommon/zephyrCommon.c
    #src/zephyrThread/zephyrThread.c
  )

  # LED strip wrapper.
  if(ENYA_LED_STRIP)
    zephyr_library_sources(src/zephyrLedStrip/zephyrLedStrip.c)
  endif()
endif()
