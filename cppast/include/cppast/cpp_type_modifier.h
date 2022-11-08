// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A61F2B78_EEC4_4755_98E4_AE767CD5DBC5
#define A61F2B78_EEC4_4755_98E4_AE767CD5DBC5

#include "cppast/cpp_ref_type.h"

#include <cstdint>

namespace cppast {

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
  std::uint32_t constBits_;
};

} // namespace cppast

#endif /* A61F2B78_EEC4_4755_98E4_AE767CD5DBC5 */
