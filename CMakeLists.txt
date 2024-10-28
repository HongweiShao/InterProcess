cmake_minimum_required(VERSION 3.20)
project(InterProcess)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

add_subdirectory(NamedMessagePipe)
add_subdirectory(examples)
