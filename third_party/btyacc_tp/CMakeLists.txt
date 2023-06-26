project(btyacc)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd\"4996\"")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd\"4996\"")
endif()

file(GLOB BTYACC_SOURCES
	btyacc/*.c
)

add_executable(btyacc ${BTYACC_SOURCES})
target_include_directories(btyacc PRIVATE btyacc/hack)

if(NOT MSVC)
	target_compile_options(btyacc
		PRIVATE
			-Wno-implicit-function-declaration
	)
endif()
