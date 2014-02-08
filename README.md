# CppParser #

A library to parse C/C++ source.
It does not do pre-processing and also tries not to ignore comments.
The result of parsing is the DOM structure where each elements of a file are arranged in a DOM tree.
The parsing is extremely lenient and it is expected that only valid C/C++ file is given as input to CppParser.

## Motivation ##
CppParser can be used to build tools that need parsing of C/C++ files.
