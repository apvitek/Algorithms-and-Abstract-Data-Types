cmake_minimum_required(VERSION 3.6)
project(CMPS_101___Programming_Assignment_4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES FindPath.c Graph.c Graph.h List.c List.h GraphClient.c ListClient.c GraphTest.c)
add_executable(CMPS_101___Programming_Assignment_4 ${SOURCE_FILES})