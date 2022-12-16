cmake_minimum_required(VERSION 3.13)

include(pico_sdk.cmake)


project(ChristmasClock C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(drivers)
add_subdirectory(app)
pico_enable_stdio_usb(ChristmasClock 1)
