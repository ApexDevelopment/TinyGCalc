cmake_minimum_required(VERSION 3.13)

# Choose the target platform (must be set before project())
set(PLATFORM "mock" CACHE STRING "Platform implementation (mock, pico, stm32)")

# Default to Pico 1
if(PLATFORM STREQUAL "pico" AND NOT DEFINED PICO_BOARD_TYPE)
	set(PICO_BOARD_TYPE "pico")
	message(STATUS "PICO_BOARD_TYPE unspecified, defaulting to 'pico'")
endif()

# Disallow bad combinations
if(NOT PLATFORM STREQUAL "pico" AND NOT "${PICO_BOARD_TYPE}" STREQUAL "")
	message(FATAL_ERROR "PICO_BOARD_TYPE should only be set when PLATFORM=pico")
endif()

# Block native.cmake for embedded platforms
if ((NOT PLATFORM STREQUAL "mock") AND (CMAKE_TOOLCHAIN_FILE MATCHES "native.cmake"))
	message(FATAL_ERROR
		"The 'native.cmake' toolchain is only valid for PLATFORM=mock.\n"
		"Please remove -DCMAKE_TOOLCHAIN_FILE or use the correct embedded toolchain.")
endif()

# Automatically selects native toolchain for mock builds.
# Do NOT set CMAKE_TOOLCHAIN_FILE manually from the build script.
if(PLATFORM STREQUAL "mock")
	if(NOT DEFINED CMAKE_TOOLCHAIN_FILE OR CMAKE_TOOLCHAIN_FILE STREQUAL "")
		message(STATUS "Using native toolchain for mock platform")
		set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain/native.cmake" CACHE FILEPATH "Toolchain file for mock" FORCE)
	endif()
endif()

# Only include Pico SDK if platform is Pico
if(PLATFORM STREQUAL "pico")
	if(NOT DEFINED PICO_SDK_PATH)
		message(FATAL_ERROR "PICO_SDK_PATH is not set.")
	endif()

	include(pico_sdk_import.cmake)
endif()

project(TinyGCalc C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Target platform: ${PLATFORM}")
if(PLATFORM STREQUAL "pico")
	message(STATUS "Pico board type: ${PICO_BOARD_TYPE}")
endif()

# Core application sources
set(SRC_FILES
	src/main.c
	src/core/eqlist.c
	src/core/font6x8.c
	src/core/plotter.c
	src/core/repl.c
	src/core/ui_eqedit.c
	src/core/ui_graph.c
	src/core/ui_text.c
	src/core/utils/display.c
	src/core/utils/graph.c
	lib/tinyexpr/tinyexpr.c
)

# Platform-specific sources and config
if(PLATFORM STREQUAL "pico")
	set(PICO_BOARD ${PICO_BOARD_TYPE})
	set(PICO_DEFAULT_BOOT_STAGE2_FILE "${PICO_SDK_PATH}/src/rp2040/boot_stage2/boot2_w25q080.S")

	pico_sdk_init()

	list(APPEND SRC_FILES
		#src/platform/pico/hal_display_st7789.c
		src/platform/pico/hal_display_sh1106.c
		src/platform/pico/hal_input.c
		src/platform/pico/hal_time.c
		src/platform/pico/hal_serial.c
	)
elseif(PLATFORM STREQUAL "stm32")
	list(APPEND SRC_FILES
		src/platform/stm32/hal_display.c
	)
elseif(PLATFORM STREQUAL "mock")
	list(APPEND SRC_FILES
		src/platform/mock/hal_display.c
		src/platform/mock/hal_input.c
		src/platform/mock/hal_time.c
		src/platform/mock/hal_serial.c
	)

	set(SDL2_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2")
	list(APPEND EXTRA_LIBS SDL2)
else()
	message(FATAL_ERROR "Unknown platform: ${PLATFORM}")
endif()

# Define the target
add_executable(tinygcalc ${SRC_FILES})

# Stop shortening enums on the mock platform so SDL2 doesn't break
if(PLATFORM STREQUAL "mock")
	target_compile_options(tinygcalc PRIVATE
		$<$<STREQUAL:${PLATFORM},mock>:-fno-short-enums>
	)
endif()

# Target-specific includes
target_include_directories(tinygcalc PRIVATE
	src
	src/core
	src/hal
	lib/tinyexpr
	src/platform/${PLATFORM}
)

# Link platform-specific libraries
if(PLATFORM STREQUAL "pico")
	target_link_libraries(tinygcalc
		pico_stdlib
		pico_time
		pico_stdio_usb
		# pico_stdio_uart
		hardware_spi
		hardware_i2c
		hardware_gpio
		hardware_dma
	)
	pico_add_extra_outputs(tinygcalc)
elseif(DEFINED EXTRA_LIBS)
	target_include_directories(tinygcalc PRIVATE "${SDL2_ROOT}/include")
	target_link_directories(tinygcalc PRIVATE "${SDL2_ROOT}/lib")
	target_link_libraries(tinygcalc ${EXTRA_LIBS})
endif()
