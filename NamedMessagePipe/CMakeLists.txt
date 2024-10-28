cmake_minimum_required(VERSION 3.20)
project(NamedMessagePipe)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE lib_src_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
source_group("Source Files" FILES ${lib_src_files})

file(GLOB_RECURSE lib_header_files ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
source_group("Header Files" FILES ${lib_header_files})

# 为Windows下的构建添加版本信息
set(LIB_VERSION_MAJOR 1)
set(LIB_VERSION_MINOR 0)
set(LIB_VERSION_BUILD 0)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/version.rc @ONLY)

# 添加项目的头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(NamedMessagePipe SHARED ${lib_src_files} ${lib_header_files} ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
# 设置导出符号
set_target_properties(NamedMessagePipe PROPERTIES DEFINE_SYMBOL "NAMEDMSGPIPELIB_EXPORTS")
# 设置版本号(Windows无效)
# set_target_properties(NamedMessagePipe PROPERTIES VERSION 1.0.0 SOVERSION 1)
# 让依赖此库的目标知道头文件目录
target_include_directories(NamedMessagePipe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 安装库文件和头文件
install(TARGETS NamedMessagePipe
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
install(FILES ${lib_header_files} DESTINATION include)