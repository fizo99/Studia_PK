cmake_minimum_required(VERSION 2.8.9)
project (HRMS)
set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE) #build type
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=lstdc++")	#compiler flags
#set (CMAKE_C_COMPILER clang)					#set compiler for C
#set (CMAKE_CXX_COMPILER clang++)				#set compiler for C++
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)	#set destination of .exe files

file(GLOB SRC
	"./src/*.c"
	"./src/*.cpp"
	"./src/*.hpp"
	"./src/*.h"
)

add_executable(HRMS ${SRC})
include_directories( ./include/HRMS )


