cmake_minimum_required(VERSION 3.20)
project(NamedMessagePipeClient)

set(CMAKE_CXX_STANDARD 11)

add_executable(NamedMessagePipeClient NamedMessagePipeClient.cpp)
target_link_libraries(NamedMessagePipeClient PRIVATE NamedMessagePipe)

install(TARGETS NamedMessagePipeClient RUNTIME DESTINATION bin)