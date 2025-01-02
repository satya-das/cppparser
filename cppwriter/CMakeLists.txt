set(CPP_WRITER_SOURCES
  src/cppwriter.cpp
)

add_library(cppwriter STATIC ${CPP_WRITER_SOURCES})

target_include_directories(cppwriter
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(cppwriter
  PUBLIC
    cppast
)
set_target_properties(cppwriter PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

install(DIRECTORY "include/cppwriter" DESTINATION "include")
