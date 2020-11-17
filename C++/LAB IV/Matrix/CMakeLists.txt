cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project (MATRIX)

add_executable(MATRIX ./src/main.cpp ./src/Matrix.cpp)

include_directories(./include/Matrix)
