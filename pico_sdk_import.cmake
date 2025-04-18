# pico_sdk_import.cmake

if(NOT DEFINED PICO_SDK_PATH)
    message(FATAL_ERROR "PICO_SDK_PATH is not set. Please specify it with -DPICO_SDK_PATH or set it as an environment variable.")
endif()

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
