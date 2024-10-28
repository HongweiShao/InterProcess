cmake_minimum_required(VERSION 3.20)
project(NamedMessagePipeServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(NamedMessagePipeServer NamedMessagePipeServer.cpp)
target_link_libraries(NamedMessagePipeServer PRIVATE NamedMessagePipe)

install(TARGETS NamedMessagePipeServer RUNTIME DESTINATION bin)