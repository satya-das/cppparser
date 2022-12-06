enable_testing()

add_executable(cppasttest
	main.cpp
	cpp_entity_cast_test.cpp
)
target_include_directories(cppasttest
	PUBLIC
		../../../common/third_party
)
target_link_libraries(cppasttest
	PRIVATE
		cppast
)
add_test(
	NAME CppAstTest
	COMMAND cppasttest
)
