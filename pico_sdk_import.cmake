# pico_sdk_import.cmake

if(NOT DEFINED PICO_SDK_PATH)
    message(FATAL_ERROR "PICO_SDK_PATH is not set. Please specify it with -DPICO_SDK_PATH or set it as an environment variable.")
endif()

find_program(PICOTOOL_EXECUTABLE picotool)

# Check if picotool is installed
if (PICOTOOL_EXECUTABLE)
	message(STATUS "Using system-installed picotool.")
	set(PICO_NO_PICOTOOL 1 CACHE INTERNAL "Skip building SDK picotool if system version is present")
else()
	message(STATUS "No system picotool found; using bundled version")
endif()

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
