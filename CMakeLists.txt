cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(TinyGCalc C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Choose the target platform
set(PLATFORM "mock" CACHE STRING "Target platform (pico, stm32, mock)")

# Core application sources
set(SRC_FILES
    src/main.c
    src/core/plotter.c
    lib/tinyexpr/tinyexpr.c
)

# Platform-specific logic
if(PLATFORM STREQUAL "pico")
    # Ensure Pico SDK path is set
    if(NOT DEFINED PICO_SDK_PATH)
        message(FATAL_ERROR "PICO_SDK_PATH is not set. Please define it via -DPICO_SDK_PATH or environment variable.")
    endif()

    # Initialize Pico SDK
    include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
    pico_sdk_init()

    list(APPEND SRC_FILES
        src/platform/pico/hal_display.c
    )
    include_directories(src/platform/pico)
elseif(PLATFORM STREQUAL "stm32")
    list(APPEND SRC_FILES
        src/platform/stm32/hal_display.c
    )
    include_directories(src/platform/stm32)
elseif(PLATFORM STREQUAL "mock")
    list(APPEND SRC_FILES
        src/platform/mock/hal_display.c
        src/platform/mock/hal_input.c
    )
    include_directories(src/platform/mock)

    add_compile_options(-fno-short-enums)

    # Assume SDL2 was extracted to lib/SDL2 for portability
    set(SDL2_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2")
    include_directories("${SDL2_ROOT}/include")
    link_directories("${SDL2_ROOT}/lib")
    list(APPEND EXTRA_LIBS SDL2)
else()
    message(FATAL_ERROR "Unknown platform: ${PLATFORM}")
endif()

add_executable(tinygcalc ${SRC_FILES})

target_include_directories(tinygcalc PRIVATE
    src
    src/core
    src/hal
    lib/tinyexpr
)

# Link platform-specific libraries
if(PLATFORM STREQUAL "pico")
    target_link_libraries(tinygcalc pico_stdlib)
    pico_add_extra_outputs(tinygcalc)
elseif(DEFINED EXTRA_LIBS)
    target_link_libraries(tinygcalc ${EXTRA_LIBS})
endif()
