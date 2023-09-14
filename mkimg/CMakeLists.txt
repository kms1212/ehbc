cmake_minimum_required(VERSION 3.12)

include(ExternalProject)

project("mkimg")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

configure_file(deps/cJSON.cmake.in ${CMAKE_BINARY_DIR}/deps/cJSON_cmake/CMakeLists.txt)
execute_process(
    COMMAND             ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY   ${CMAKE_BINARY_DIR}/deps/cJSON_cmake)
execute_process(
    COMMAND             ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY   ${CMAKE_BINARY_DIR}/deps/cJSON_cmake)
execute_process(
    COMMAND             ${CMAKE_COMMAND} --install .
    WORKING_DIRECTORY   ${CMAKE_BINARY_DIR}/deps/cJSON_cmake)

file(GLOB SOURCE_LIST "${CMAKE_SOURCE_DIR}/src/*")
add_executable(mkimg ${SOURCE_LIST})

include_directories(mkimg "${CMAKE_SOURCE_DIR}/include")
include_directories(mkimg "${CMAKE_BINARY_DIR}/deps/output/include")
target_link_libraries(mkimg PUBLIC -L${CMAKE_BINARY_DIR}/deps/output/lib/)
