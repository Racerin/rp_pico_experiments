# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

message("This is the pico-sdk path. $ENV{PICO_SDK_PATH}")

# Set name of project (as PROJECT_NAME) and C/C   standards
# project(blink C CXX ASM)
project(RP_Pico_Experiments C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(
    ${PROJECT_NAME} 
    # src/main.c
    src/hello_world.c
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(
    ${PROJECT_NAME}
    # hello_world
    )

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(
    ${PROJECT_NAME} 
    # hello_world
    pico_stdlib
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)