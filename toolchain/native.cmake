# toolchain/native.cmake
# Use the actual host system name for native builds

# Query the host OS and set the system name accordingly
if(NOT DEFINED CMAKE_SYSTEM_NAME)
    string(TOLOWER "${CMAKE_HOST_SYSTEM_NAME}" _host_os)

    if(_host_os MATCHES "linux")
        set(CMAKE_SYSTEM_NAME Linux)
    elseif(_host_os MATCHES "darwin")
        set(CMAKE_SYSTEM_NAME Darwin)
    elseif(_host_os MATCHES "windows")
        set(CMAKE_SYSTEM_NAME Windows)
    else()
        message(FATAL_ERROR
            "Unsupported host OS: ${CMAKE_HOST_SYSTEM_NAME}\n"
            "You can override the system name manually by setting:\n"
            "    -DCMAKE_SYSTEM_NAME=<YourSystem>"
        )
    endif()
endif()
