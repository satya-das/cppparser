# Input variable:
#   None.
# Output variables:
#   DOT_PATH: The path of `dot` executable.

find_program(DOT_PATH dot PATH_SUFFIXES graphviz/bin)
if(NOT DOT_PATH)
    message(FATAL_ERROR "Looking for GraphWiz dot executable - not found.")
else()
    message(STATUS "Found GraphWiz dot executable at ${DOT_PATH}")
endif()