cmake_minimum_required(VERSION 3.5)
enable_testing()

project(cppparser VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
set(CLANG_TIDY_COMMAND "clang-tidy" "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
set(export_config_name ${PROJECT_NAME})

if(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd\"4996\"")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd\"4996\"")
endif()

option(CPPPARSER_BUILD_TESTS "Build tests" OFF)

add_subdirectory(cppast)
add_subdirectory(cppparser)
add_subdirectory(cppwriter)

find_program(
	MARKDOWN_PP
	"markdown-pp"
	PATHS ENV PATH
)

if(NOT ${MARKDOWN_PP} MATCHES "MARKDOWN_PP-NOTFOUND")
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/README.md
		COMMAND ${MARKDOWN_PP} ${CMAKE_CURRENT_SOURCE_DIR}/cppparser/src/README.mdpp -o ${CMAKE_CURRENT_SOURCE_DIR}/README.md
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cppparser/src/README.mdpp ${RESPATHS} ${EXAMPLE_HEADERS}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	add_custom_target(
		ReadMe ALL
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
else()
  message("Markdown-pp NOT FOUND: README cannot be updated.")
endif()

install(
	TARGETS cppast cppparser_lex_and_yacc cppparser cppwriter
	EXPORT ${export_config_name}Targets
	ARCHIVE DESTINATION "lib" COMPONENT Development
	LIBRARY DESTINATION "lib" COMPONENT RuntimeLibraries
	LIBRARY DESTINATION "bin" COMPONENT RuntimeLibraries
)

if(NOT DEFINED CPPPARSER_INSTALL_CONFIG_DIR)
  set(CPPPARSER_INSTALL_CONFIG_DIR lib/cmake/${export_config_name})
endif()

#------------------------------------------------------------------------------
# Configure <export_config_name>ConfigVersion.cmake common to build and install tree
include(CMakePackageConfigHelpers)
set(config_version_file ${PROJECT_BINARY_DIR}/${export_config_name}ConfigVersion.cmake)
write_basic_package_version_file(
	${config_version_file}
	VERSION "${CPPPARSER_VERSION}"
	COMPATIBILITY ExactVersion
)

#------------------------------------------------------------------------------
# Export '<export_config_name>Targets.cmake' for a build tree
export(
	EXPORT ${PROJECT_NAME}Targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/${export_config_name}Targets.cmake"
)

# Configure '<export_config_name>Config.cmake' for a build tree
set(build_config ${CMAKE_BINARY_DIR}/${export_config_name}Config.cmake)
configure_package_config_file(
	${export_config_name}Config.cmake.in
	${build_config}
	INSTALL_DESTINATION "${PROJECT_BINARY_DIR}"
)

#------------------------------------------------------------------------------
# Export '<export_config_name>Targets.cmake' for an install tree
install(
	EXPORT ${export_config_name}Targets
	FILE ${export_config_name}Targets.cmake
	DESTINATION ${CPPPARSER_INSTALL_CONFIG_DIR}
)

set(install_config ${PROJECT_BINARY_DIR}/CMakeFiles/${export_config_name}Config.cmake)
configure_package_config_file(
	${export_config_name}Config.cmake.in
	${install_config}
	INSTALL_DESTINATION ${CPPPARSER_INSTALL_CONFIG_DIR}
)

# Install config files
install(
	FILES ${config_version_file} ${install_config}
	DESTINATION "${CPPPARSER_INSTALL_CONFIG_DIR}"
)
