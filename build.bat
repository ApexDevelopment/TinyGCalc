@echo off
setlocal ENABLEDELAYEDEXPANSION

:: === Default to mock if no args ===
set "TARGET=%1"
if "%1"=="" (
    set "TARGET=mock"
)

:: === Clean entire build tree ===
if /i "%TARGET%"=="clean" (
    echo [INFO] Cleaning all build directories...
    rmdir /s /q build
    exit /b 0
)

:: === Determine PLATFORM and BOARD based on TARGET ===
set "PLATFORM="
set "PICO_BOARD_TYPE="

if /i "%TARGET%"=="mock" (
    set "PLATFORM=mock"
) else if /i "%TARGET%"=="pico" (
    set "PLATFORM=pico"
    set "PICO_BOARD_TYPE=pico"
) else if /i "%TARGET%"=="picow" (
    set "PLATFORM=pico"
    set "PICO_BOARD_TYPE=pico_w"
) else (
    echo [ERROR] Unknown target: %TARGET%
    echo Usage:
    echo   build [mock ^| pico ^| picow] [clean]
    exit /b 1
)

if /i "%2"=="clean" (
    echo [INFO] Cleaning build directory for platform: %TARGET% ...
    rmdir /s /q build\%TARGET%
    exit /b 0
)

:: === Check for PICO_SDK_PATH if needed ===
if /i "%PLATFORM%"=="pico" (
    if not defined PICO_SDK_PATH (
        echo [ERROR] PICO_SDK_PATH is not set.
        echo Set it using:
        echo   set PICO_SDK_PATH=C:\path\to\pico-sdk
        exit /b 1
    )
    if not exist "%PICO_SDK_PATH%\pico_sdk_init.cmake" (
        echo [ERROR] pico_sdk_init.cmake not found in %PICO_SDK_PATH%
        exit /b 1
    )
)

:: === Check for arm-none-eabi-gcc only for embedded targets ===
if /i not "%PLATFORM%"=="mock" (
    where arm-none-eabi-gcc >nul 2>nul
    if errorlevel 1 (
        echo [ERROR] arm-none-eabi-gcc not found in PATH.
        exit /b 1
    )
)

:: === Set build folder per target ===
set "BUILD_DIR=build\%TARGET%"
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
cd %BUILD_DIR%

:: === Configure CMake ===
cmake ../.. -DPICO_SDK_PATH=%PICO_SDK_PATH% -DPLATFORM=%PLATFORM% -DPICO_BOARD_TYPE=%PICO_BOARD_TYPE% -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
if errorlevel 1 exit /b 1

:: === Build ===
mingw32-make
if errorlevel 1 exit /b 1

echo [SUCCESS] Build complete for target: %TARGET%
cd ../..
endlocal
