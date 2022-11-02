// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E17B1CB3_AE84_40A6_840A_3ACF197478E9
#define E17B1CB3_AE84_40A6_840A_3ACF197478E9

#include <cstdint>

namespace CppAst {
/**
 * Type of references a variable can have in a C++ program.
 */
enum class CppRefType : std::uint8_t
{
  NONE,    // No reference.
  BY_REF,  // Simple reference, e.g. int& x.
  RVAL_REF // R-value reference, e.g. in move constructor.
};

} // namespace CppAst

#endif /* E17B1CB3_AE84_40A6_840A_3ACF197478E9 */
