set(DRIVER_NAME led)
add_library(${DRIVER_NAME} INTERFACE)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(${DRIVER_NAME} ${CMAKE_CURRENT_LIST_DIR}/pio/${DRIVER_NAME}.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/include/generated)

target_sources(${DRIVER_NAME} INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/${DRIVER_NAME}.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/color.cpp
)

target_include_directories(${DRIVER_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in pico libraries that we need
target_link_libraries(${DRIVER_NAME} INTERFACE pico_stdlib pico_sync hardware_pio hardware_dma hardware_irq)
