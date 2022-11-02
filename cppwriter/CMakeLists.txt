cmake_minimum_required(VERSION 3.4)

project(CppWriter)

set(CMAKE_CXX_STANDARD 17)

#############################################
## cppwriter

set(CPP_WRITER_SOURCES
  src/cppwriter.cpp
)

add_library(cppwriter STATIC ${CPP_WRITER_SOURCES})

target_include_directories(cppwriter
	PUBLIC
		include
)
target_link_libraries(cppwriter
  PUBLIC
    cppast
)
