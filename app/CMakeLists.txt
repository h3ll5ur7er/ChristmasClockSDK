
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

pico_add_extra_outputs(${OUTPUT_NAME})
