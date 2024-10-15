cmake_minimum_required(VERSION 3.2)

project(btyacc C)

# ---- btyacc executable ----

set(src "${PROJECT_SOURCE_DIR}")
set(bin "${PROJECT_BINARY_DIR}")
add_custom_command(
    OUTPUT skeleton.c
    COMMAND "${CMAKE_COMMAND}"
    "-Dinput=${src}/btyaccpa.ske"
    "-Doutput=${bin}/skeleton.c.tmp"
    -P "${src}/cmake/skel2c.cmake"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
    "${bin}/skeleton.c.tmp"
    "${bin}/skeleton.c"
    COMMAND "${CMAKE_COMMAND}" -E remove "${bin}/skeleton.c.tmp"
    MAIN_DEPENDENCY btyaccpa.ske
    DEPENDS cmake/skel2c.cmake
    COMMENT "skel2c [btyaccpa.ske -> skeleton.c]"
    VERBATIM
)

add_executable(
    btyacc
    closure.c
    dtor.c
    error.c
    lalr.c
    lr0.c
    main.c
    mkpar.c
    output.c
    mstring.c
    reader.c
    readskel.c
    skeleton.c
    symtab.c
    verbose.c
    warshall.c
    "${bin}/skeleton.c"
)

target_include_directories(btyacc PRIVATE "${src}")

# ---- Install rules ----

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()

include(GNUInstallDirs)

install(
    TARGETS btyacc
    EXPORT btyaccTargets
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT btyacc_Runtime
)

set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME btyacc_Development)

set(
    btyacc_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/btyacc"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(btyacc_INSTALL_CMAKEDIR)

install(
    EXPORT btyaccTargets
    NAMESPACE btyacc::
    DESTINATION "${btyacc_INSTALL_CMAKEDIR}"
)

if(CMAKE_VERSION VERSION_LESS "3.14")
  set(maybe_exe btyacc)
  if(WIN32)
    set(maybe_exe btyacc.exe)
  endif()
  set(btyacc_EXECUTABLE_NAME "${maybe_exe}" CACHE STRING "Executable name")
else()
  cmake_policy(SET CMP0087 NEW)
  set(btyacc_EXECUTABLE_NAME "$<TARGET_FILE_NAME:btyacc>")
endif()
install(CODE "set(btyacc_NAME [[${btyacc_EXECUTABLE_NAME}]])")

install(CODE "set(btyacc_INSTALL_CMAKEDIR [[${btyacc_INSTALL_CMAKEDIR}]])")
install(CODE "set(CMAKE_INSTALL_BINDIR [[${CMAKE_INSTALL_BINDIR}]])")

install(SCRIPT cmake/install.cmake)
