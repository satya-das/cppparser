cmake_minimum_required(VERSION 3.4)

project(cppparser)

enable_testing()

include("../common/cmake/conf.cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd\"4996\"")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd\"4996\"")
endif()

add_subdirectory(cppast)
add_subdirectory(cppwriter)

add_subdirectory(third_party/btyacc_tp)

add_definitions(-DBOOST_AUTO_LINK_NOMANGLE)

add_subdirectory(../common/third_party/boost_tp/cmake  ${CMAKE_BINARY_DIR}/boost)

include_directories(../common/third_party)

#############################################
## CppParser

find_program(
	FLEX
	"flex"
	# Assuming for Linux and OSX flex is already available
	# Only for Windows the flex will be used from the repository
	PATHS ENV PATH "third_party/flex_tp"
)
if(${FLEX} MATCHES "FLEX-NOTFOUND")
	message(FATAL_ERROR "'flex' not found")
else()
	message(STATUS "Found 'flex' as ${FLEX}")
endif()

set_source_files_properties(src/parser.tab.cpp GENERATED)
set_source_files_properties(src/parser.lex.cpp GENERATED)
set_source_files_properties(src/parser.tab.h GENERATED)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.tab.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.tab.h
	COMMAND $<TARGET_FILE:btyacc> -v -b parser -d ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y
#	COMMAND ${CMAKE_COMMAND} -E copy y_tab.c ${CMAKE_CURRENT_SOURCE_DIR}/parser.tab.cpp
#	COMMAND ${CMAKE_COMMAND} -E copy y_tab.h ${CMAKE_CURRENT_SOURCE_DIR}/parser.tab.h
	COMMAND ${CMAKE_COMMAND} -E copy parser.tab.c ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.tab.cpp
	COMMAND ${CMAKE_COMMAND} -E copy parser.tab.h ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.tab.h
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.lex.cpp
	COMMAND ${FLEX} -o${CMAKE_CURRENT_SOURCE_DIR}/src/parser.lex.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.l
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.l ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.tab.h
)

set(CPPPARSER_SOURCES
	src/cppparser.cpp
	src/cppprog.cpp
	src/cppobjfactory.cpp
	src/lexer-helper.cpp
	src/parser.l
	src/parser.y
	src/parser.lex.cpp
	src/parser.tab.cpp
	src/utils.cpp
)

add_library(cppparser STATIC ${CPPPARSER_SOURCES})
add_dependencies(cppparser btyacc boost_filesystem boost_program_options)
target_link_libraries(cppparser
	PUBLIC
		cppast
		boost_filesystem
		boost_program_options
		boost_system
)
target_include_directories(
	cppparser
	PUBLIC
		pub
		./
		../common/third_party/boost_tp
	PRIVATE
		hack
)
target_compile_definitions(
	cppparser
	PRIVATE
		YY_NO_UNPUT
)

#############################################
## CppParserTest

add_executable(cppparsertest
	test/app/cppparsertest.cpp
)

target_link_libraries(cppparsertest
	PRIVATE
		cppparser
		boost_filesystem
		boost_program_options
		boost_system
)

set(E2E_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test/e2e)
set(CTEST_OUTPUT_ON_FAILURE 1)
add_test(
	NAME ParserTest
	COMMAND cppparsertest --input-folder=${E2E_TEST_DIR}/test_input
		--output-folder=${E2E_TEST_DIR}/test_output
		--master-files-folder=${E2E_TEST_DIR}/test_master
)

#############################################
## Unit Test

set(TEST_SNIPPET_EMBEDDED_TESTS
	${CMAKE_CURRENT_LIST_DIR}/test/unit/attribute-specifier-sequence.cpp
	${CMAKE_CURRENT_LIST_DIR}/test/unit/disabled-code-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/test/unit/error-handler-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/test/unit/expr-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/test/unit/namespace-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/test/unit/template-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/test/unit/uniform-init-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/test/unit/vardecl-test.cpp
)

add_executable(cppparserunittest
	${CMAKE_CURRENT_LIST_DIR}/test/unit/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/test/unit/test-hello-world.cpp

	${TEST_SNIPPET_EMBEDDED_TESTS}
)
target_include_directories(cppparserunittest
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src
)

target_link_libraries(cppparserunittest
	PRIVATE
		cppparser
		boost_filesystem
		boost_program_options
		boost_system
)
set(UNIT_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test/unit)
add_test(
	NAME ParserUnitTest
	COMMAND cppparserunittest
)

# cppparserembeddedsnippetvalidity is just to ensure that the embedded
# code snippets used in unit tests are valid C/C++ code.
# So, the goal is to test if the embedded test snippets compile without error.
add_executable(cppparserembeddedsnippetvalidity
	${CMAKE_CURRENT_LIST_DIR}/test/unit/main.cpp

	${TEST_SNIPPET_EMBEDDED_TESTS}
)
target_include_directories(cppparserembeddedsnippetvalidity
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src
)
target_compile_definitions(cppparserembeddedsnippetvalidity
  PRIVATE
		"TEST_CASE_SNIPPET_STARTS_FROM_NEXT_LINE=1"
		"CPPPARSER_TEST_DEFINED_MACRO=1"
)
target_link_libraries(cppparserembeddedsnippetvalidity
	PRIVATE
		cppparser
		boost_filesystem
		boost_program_options
		boost_system
)

if(NOT MSVC)
	target_compile_options(cppparserembeddedsnippetvalidity
		PRIVATE
			-Wno-unused-variable
			-Wno-attributes
			-Wno-unused-value
			-Wno-uninitialized
			-Wno-unused-but-set-variable
	)
endif()

find_program(
	MARKDOWN_PP
	"markdown-pp"
	PATHS ENV PATH
)

if(NOT ${MARKDOWN_PP} MATCHES "MARKDOWN_PP-NOTFOUND")
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/README.md
		COMMAND ${MARKDOWN_PP} ${CMAKE_CURRENT_SOURCE_DIR}/src/README.mdpp -o ${CMAKE_CURRENT_SOURCE_DIR}/README.md
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/README.mdpp ${RESPATHS} ${EXAMPLE_HEADERS}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	add_custom_target(
		ReadMe ALL
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
else()
  message("Markdown-pp NOT FOUND: README cannot be updated.")
endif()
