cmake_minimum_required(VERSION 3.4)

project(CppAst)

set(CMAKE_CXX_STANDARD 17)

#############################################
## cppast

set(CPP_AST_SOURCES
  src/cppast.cpp
  src/cpp_attribute_specifier_sequence_container.cpp
  src/cpp_blob.cpp
  src/cpp_compound.cpp
  src/cpp_control_blocks.cpp
  src/cpp_entity_info_accessor.cpp
  src/cpp_enum.cpp
  src/cpp_expression.cpp
  src/cpp_function.cpp
  src/cpp_lambda.cpp
  src/cpp_templatable_entity.cpp
  src/cpp_template_param.cpp
  src/cpp_var_type.cpp
)

add_library(cppast STATIC ${CPP_AST_SOURCES})
target_include_directories(cppast
	PUBLIC
		include
)
