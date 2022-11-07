set(CPP_WRITER_SOURCES
  src/cppwriter.cpp
)

add_library(cppwriter STATIC ${CPP_WRITER_SOURCES})

target_include_directories(cppwriter
	PUBLIC
		include
)
target_link_libraries(cppwriter
  PUBLIC
    cppast
)
