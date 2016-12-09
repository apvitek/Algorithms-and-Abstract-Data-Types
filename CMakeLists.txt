cmake_minimum_required(VERSION 3.6)
project(Programming_Assignment_2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES Lex.c List.c ListClient.c input.txt output.txt)
add_executable(Programming_Assignment_2 ${SOURCE_FILES})