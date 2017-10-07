cmake_minimum_required(VERSION 3.4)

if (CMAKE_BUILD_TYPE MATCHES Release)
	set(TARGET_SUBDIR Release)
else()
	set(TARGET_SUBDIR Debug)
endif()

set(BASEOUTDIR ${CMAKE_CURRENT_LIST_DIR}/../../../build_results/${TARGET_SUBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BASEOUTDIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BASEOUTDIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASEOUTDIR}/bin)
set(CMAKE_OBJFILE_OUTPUT_DIRECTORY ${BASEOUTDIR}/obj)
set(CMAKE_CURRENT_BINARY_DIR, ${CMAKE_OBJFILE_OUTPUT_DIRECTORY})

project(btyacc)

file(GLOB BTYACC_SOURCES
	btyacc/*.c
)

add_executable(btyacc ${BTYACC_SOURCES})
target_include_directories(btyacc PRIVATE btyacc/hack)
