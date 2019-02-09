cmake_minimum_required(VERSION 3.4)

project(btyacc)

file(GLOB BTYACC_SOURCES
	btyacc/*.c
)

add_executable(btyacc ${BTYACC_SOURCES})
target_include_directories(btyacc PRIVATE btyacc/hack)
