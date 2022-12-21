
set(OUTPUT_NAME ChristmasClock)

set (INCLUDE_DIRS "")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h*")
file(GLOB_RECURSE SRC "src/*.c*")


foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES INCLUDE_DIRS)

add_executable(
    ${OUTPUT_NAME}
    ${SRC}
)

target_link_libraries(${OUTPUT_NAME} pico_stdlib ir led lna power touch)

target_include_directories(${OUTPUT_NAME} PRIVATE ${INCLUDE_DIRS})

# Enable serial connection over USB
pico_enable_stdio_usb(${OUTPUT_NAME} 1)

# Disable serial connection over UART
pico_enable_stdio_uart(${OUTPUT_NAME} 0)

pico_add_extra_outputs(${OUTPUT_NAME})
