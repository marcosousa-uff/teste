cmake_minimum_required(VERSION 3.7)
project(teste)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c grafo.c grafo.h)
add_executable(teste ${SOURCE_FILES})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
