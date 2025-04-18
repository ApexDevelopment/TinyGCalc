cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

# Choose the target platform (must be set before project())
set(PLATFORM "mock" CACHE STRING "Target platform (pico, stm32, mock)")

# Automatically use native.cmake only when building for 'mock'
if(NOT CMAKE_TOOLCHAIN_FILE AND PLATFORM STREQUAL "mock")
	set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/toolchain/native.cmake" CACHE FILEPATH "Toolchain file")
endif()

# Block native.cmake for embedded platforms
if ((NOT PLATFORM STREQUAL "mock") AND (CMAKE_TOOLCHAIN_FILE MATCHES "native.cmake"))
	message(FATAL_ERROR
		"The 'native.cmake' toolchain is only valid for PLATFORM=mock.\n"
		"Please remove -DCMAKE_TOOLCHAIN_FILE or use the correct embedded toolchain.")
endif()

project(TinyGCalc C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Core application sources
set(SRC_FILES
	src/main.c
	src/core/plotter.c
	lib/tinyexpr/tinyexpr.c
)

# Platform-specific sources and config
if(PLATFORM STREQUAL "pico")
	if(NOT DEFINED PICO_SDK_PATH)
		message(FATAL_ERROR "PICO_SDK_PATH is not set.")
	endif()

	set(PICO_BOARD pico)
	set(PICO_BOOT_STAGE2_IMPLEMENTATION "${PICO_SDK_PATH}/src/rp2_common/boot_stage2/boot2_w25q080.c")

	include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
	pico_sdk_init()

	list(APPEND SRC_FILES
		src/platform/pico/hal_display.c
		src/platform/pico/hal_input.c
		src/platform/pico/hal_time.c
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
	)

	set(SDL2_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2")
	list(APPEND EXTRA_LIBS SDL2)
else()
	message(FATAL_ERROR "Unknown platform: ${PLATFORM}")
endif()

# Define the target
add_executable(tinygcalc ${SRC_FILES})

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
	target_link_libraries(tinygcalc pico_stdlib pico_time)
	pico_add_extra_outputs(tinygcalc)
elseif(DEFINED EXTRA_LIBS)
	target_include_directories(tinygcalc PRIVATE "${SDL2_ROOT}/include")
	target_link_directories(tinygcalc PRIVATE "${SDL2_ROOT}/lib")
	target_link_libraries(tinygcalc ${EXTRA_LIBS})
endif()
