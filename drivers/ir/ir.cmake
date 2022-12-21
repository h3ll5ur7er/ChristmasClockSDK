set(DRIVER_NAME ir)
add_library(${DRIVER_NAME} INTERFACE)

# invoke pio_asm to assemble the state machine program
pico_generate_pio_header(${DRIVER_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/nec_receive.pio)

target_sources(${DRIVER_NAME} INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/receiver.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/sender.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/nec_message.cpp
)

# Pull in pico libraries that we need
target_link_libraries(${DRIVER_NAME} INTERFACE
  pico_stdlib
  hardware_pio
  )

target_include_directories(${DRIVER_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
