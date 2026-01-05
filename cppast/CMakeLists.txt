add_library(cppast STATIC
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
  src/cppast.cpp
)
target_include_directories(cppast
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CPPPARSER_INSTALL_INCLUDE_DIR}>
)
set_target_properties(cppast PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

if (CPPPARSER_BUILD_TESTS)
  add_subdirectory(test)
endif()

install(DIRECTORY "include/cppast" DESTINATION "include")
