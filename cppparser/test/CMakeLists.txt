enable_testing()

if(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd\"4996\"")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd\"4996\"")
endif()

add_definitions(-DBOOST_AUTO_LINK_NOMANGLE)

include_directories(../../../common/third_party)

add_executable(cppparsertest
	app/cppparsertest.cpp
)

target_link_libraries(cppparsertest
	PRIVATE
		cppparser
		cppwriter
		boost_filesystem
		boost_program_options
		boost_system
)

set(E2E_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/e2e)
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
	${CMAKE_CURRENT_LIST_DIR}/unit/attribute-specifier-sequence.cpp
	${CMAKE_CURRENT_LIST_DIR}/unit/disabled-code-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/unit/error-handler-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/unit/expr-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/unit/namespace-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/unit/template-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/unit/uniform-init-test.cpp
	${CMAKE_CURRENT_LIST_DIR}/unit/vardecl-test.cpp
)

add_executable(cppparserunittest
	${CMAKE_CURRENT_LIST_DIR}/unit/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/unit/test-hello-world.cpp

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
set(UNIT_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/unit)
add_test(
	NAME ParserUnitTest
	COMMAND cppparserunittest
)

# cppparserembeddedsnippetvalidity is just to ensure that the embedded
# code snippets used in unit tests are valid C/C++ code.
# So, the goal is to test if the embedded test snippets compile without error.
add_executable(cppparserembeddedsnippetvalidity
	${CMAKE_CURRENT_LIST_DIR}/unit/main.cpp

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
