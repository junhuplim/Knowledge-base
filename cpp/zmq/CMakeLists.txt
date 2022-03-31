cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 17)
add_executable(frontend client.cpp)
add_executable(backend worker.cpp)
add_executable(broker broker.cpp)

find_library(ZMQ_LIB zmq REQUIRED)
set(ZMQ_LIB_INCLUDE_DIR /usr/local/include)

include_directories(${ZMQ_LIB_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(frontend ${ZMQ_LIB})
target_link_libraries(backend ${ZMQ_LIB})
target_link_libraries(broker ${ZMQ_LIB})

