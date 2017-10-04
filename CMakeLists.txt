project(cppparser)

cmake_minimum_required(VERSION 3.4)

if (CMAKE_BUILD_TYPE MATCHES Release)
	set(TARGET_SUBDIR Release)
else()
	set(TARGET_SUBDIR Debug)
endif()

if(MSVC)
	SET(CMAKE_CXX_FLAGS "/EHsc")
endif(MSVC)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
set(BASEOUTDIR ${ROOT_DIR}/build_results/${TARGET_SUBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BASEOUTDIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BASEOUTDIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASEOUTDIR}/bin)
set(CMAKE_OBJFILE_OUTPUT_DIRECTORY ${BASEOUTDIR}/obj)

add_subdirectory(third_party/btyacc_tp)

add_definitions(-DBOOST_AUTO_LINK_NOMANGLE)

add_subdirectory(${ROOT_DIR}/common/third_party/boost_tp/cmake  ${CMAKE_OBJFILE_OUTPUT_DIRECTORY}/boost)

#############################################
## CppParser

add_custom_command(
	OUTPUT parser.lex.cpp
	COMMAND flex -o parser.lex.cpp parser.l
)
add_custom_command(
	OUTPUT y_tab.c y_tab.h
	COMMAND {CMAKE_RUNTIME_OUTPUT_DIRECTORY}/btyacc -d parser.y
)
configure_file(y_tab.c parser.tab.cpp COPYONLY)
configure_file(y_tab.h parser.tab.h COPYONLY)

file(GLOB CPPPARSER_SOURCES
	*.cpp
)
add_library(cppparser STATIC ${CPPPARSER_SOURCES})
add_dependencies(cppparser btyacc boost_filesystem boost_program_options)
target_include_directories(
	cppparser
	PUBLIC
		pub
		${ROOT_DIR}/common/third_party/boost_tp
	PRIVATE
		hack
)

#############################################
## CppParserTest
file( GLOB CPPPARSERTEST_SOURCES
	cppparsertest/*.cpp
)
add_executable(cppparsertest ${CPPPARSERTEST_SOURCES})
target_link_libraries(cppparsertest
	PRIVATE
		cppparser
		boost_filesystem
		boost_program_options
		boost_system
)
enable_testing()
set(CPPPARSERTEST_DIR ${CMAKE_CURRENT_LIST_DIR}/cppparsertest)
set(CTEST_OUTPUT_ON_FAILURE 1)
add_test(
	NAME ParserTest
	COMMAND cppparsertest --input-folder=${CPPPARSERTEST_DIR}/test_input
		--output-folder=${CPPPARSERTEST_DIR}/test_output
		--master-files-folder=${CPPPARSERTEST_DIR}/test_master
)
