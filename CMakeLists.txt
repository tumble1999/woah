cmake_minimum_required(VERSION 3.18)
project(woah)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/dep")

add_subdirectory(dep)
add_subdirectory(src)
