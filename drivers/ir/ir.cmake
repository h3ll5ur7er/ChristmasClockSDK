set(DRIVER_NAME ir)
add_library(${DRIVER_NAME} INTERFACE)

pico_generate_pio_header(${DRIVER_NAME} ${CMAKE_CURRENT_LIST_DIR}/pio/transmit.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/include/generated)

target_sources(${DRIVER_NAME} INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/receiver.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/sender.cpp
)

target_include_directories(${DRIVER_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in pico libraries that we need
target_link_libraries(${DRIVER_NAME} INTERFACE pico_stdlib)