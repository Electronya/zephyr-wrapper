# Electronya Zephyr Wrapper
# Copyright (C) 2023 by Electronya

if(CONFIG_ENYA_ZEPHYR_WRAPPER)
  zephyr_include_directories(
    ./src/zephyrCommon/
    ./src/zephyrThread/
  )
  zephyr_library()

  # default wrapper utilities.
  if(NOT DEFINED CONFIG_ZTEST)
    zephyr_library_sources(
      ./src/zephyrCommon/zephyrCommon.c
      ./src/zephyrThread/zephyrThread.c
    )
  endif()

  # GPIO wrapper.
  if(CONFIG_ENYA_GPIO)
    zephyr_include_directories(./src/zephyrGpio/)
    if(NOT DEFINED CONFIG_ZTEST)
      zephyr_library_sources(./src/zephyrGpio/zephyrGpio.c)
    endif()
  endif()

  # Counter wrapper.
  if(CONFIG_ENYA_COUNTER)
    zephyr_include_directories(./src/zephyrCounter/)
    if(NOT DEFINED CONFIG_ZTEST)
      zephyr_library_sources(./src/zephyrCounter/zephyrCounter.c)
    endif()
  endif()

  # LED strip wrapper.
  if(CONFIG_ENYA_LED_STRIP)
    zephyr_include_directories(./src/zephyrLedStrip/)
    if(NOT DEFINED CONFIG_ZTEST)
      zephyr_library_sources(./src/zephyrLedStrip/zephyrLedStrip.c)
    endif()
  endif()
endif()

# USB stuff.
if(CONFIG_ENYA_USB)
  zephyr_include_directories(./src/zephyrUSB/)
  if(NOT DEFINED CONFIG_ZTEST)
    zephyr_library_sources(./src/zephyrUSB/zephyrUSB.c)
  endif()
  # USB CDC ACM
  if(CONFIG_ENYA_USB_ACM AND NOT DEFINED CONFIG_ZTEST)
    zephyr_library_sources(./src/zephyrUSB/zephyrACM.c)
  endif()
endif()
