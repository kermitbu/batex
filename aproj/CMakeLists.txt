cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-Wall -O0 -g -std=c++11 -fno-access-control" )  

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/asio)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/spdlog/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

link_libraries(pthread)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/.libs)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(aproj ${SRC_LIST})

# add_library(cflask SHARED  ${SRC_LIST})

# add_library(cflask_static ${SRC_LIST})

# set_target_properties(cflask PROPERTIES VERSION 1.0 SOVERSION 1)
