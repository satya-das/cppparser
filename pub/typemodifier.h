// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef D76E3254_72DF_4931_B97F_CF8471C4A47D
#define D76E3254_72DF_4931_B97F_CF8471C4A47D

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

#endif /* D76E3254_72DF_4931_B97F_CF8471C4A47D */
