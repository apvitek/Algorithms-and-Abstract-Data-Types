cmake_minimum_required(VERSION 3.6)
project(CMPS_101___Programming_Assignment_5)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES FindComponents.c Graph.c Graph.h List.c List.h GraphTest.c)
add_executable(CMPS_101___Programming_Assignment_5 ${SOURCE_FILES})