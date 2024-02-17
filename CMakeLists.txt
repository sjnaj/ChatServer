cmake_minimum_required(VERSION 3.0)
project(chatserver LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release)#默认release
endif()


set(CMAKE_VERBOSE_MAKEFILE ON)#详细打印

#头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include)


add_subdirectory(src)
add_subdirectory(test/muduotest)
add_subdirectory(test/jsontest)



