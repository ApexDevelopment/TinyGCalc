@echo off
setlocal

:: === Clean target ===
if /i "%1"=="clean" (
    echo [INFO] Cleaning build directory...
    rmdir /s /q build
    exit /b 0
)

:: === Default platform if not set ===
if not defined PLATFORM (
    set "PLATFORM=mock"
    echo [INFO] No PLATFORM specified. Defaulting to PLATFORM=mock
)

:: === Check for PICO_SDK_PATH only if needed ===
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
if /i "%PLATFORM%" NEQ "mock" (
    where arm-none-eabi-gcc >nul 2>nul
    if errorlevel 1 (
        echo [ERROR] arm-none-eabi-gcc not found in PATH.
        exit /b 1
    )
)

:: === Create and enter build directory ===
if not exist build mkdir build
cd build

:: === Use native toolchain if mock ===
set TOOLCHAIN_OPTION=
if /i "%PLATFORM%"=="mock" (
    set TOOLCHAIN_OPTION=-DCMAKE_TOOLCHAIN_FILE=../toolchain/native.cmake
)

:: === Run CMake and Make ===
cmake .. %TOOLCHAIN_OPTION% -DPICO_SDK_PATH=%PICO_SDK_PATH% -DPLATFORM=%PLATFORM% -G "MinGW Makefiles"
if errorlevel 1 exit /b 1

mingw32-make
if errorlevel 1 exit /b 1

echo [SUCCESS] Build complete.
cd ..
endlocal
