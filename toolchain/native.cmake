# toolchain/native.cmake
# Force CMake to use the native host compiler (e.g. MinGW on Windows)

set(CMAKE_SYSTEM_NAME Windows)  # Or Linux/macOS as needed

# Optional: force preferred compilers if needed
# set(CMAKE_C_COMPILER gcc)
# set(CMAKE_CXX_COMPILER g++)
