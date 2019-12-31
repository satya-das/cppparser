/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "cppconst.h"

struct CppTypeModifier
{
  CppRefType   refType_;
  std::uint8_t ptrLevel_; // Pointer level. e.g. int** ppi has pointer level of 2.

  // Stores bits as per location of const in a var definition.
  // Below table clarifies the value of const-bits:
  // --------------------------------------------------
  // | DEFINITION                             | VALUE |
  // | ------------------------------------------------
  // | int const * pi                         | 0b001 |
  // | int const i                            | 0b001 |
  // | int * const pi                         | 0b010 |
  // | int * const * const ppi                | 0b110 |
  // | int **const ppi                        | 0b100 |
  // | int const * const * const ppi          | 0b111 |
  // | ------------------------------------------------
  //
  // It is 8 bit unsigned integer which is enough to store info for pointers of 8 level deep.
  std::uint32_t constBits_;
};

inline CppTypeModifier makeCppTypeModifier(CppRefType refType, std::uint8_t ptrLevel, std::uint8_t constBits)
{
  return CppTypeModifier {refType, ptrLevel, constBits};
}
