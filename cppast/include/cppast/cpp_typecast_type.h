// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BCBB7E53_C4E3_46CF_8E7A_45E1309F97C1
#define BCBB7E53_C4E3_46CF_8E7A_45E1309F97C1

#include <cstdint>

namespace cppast {

enum class CppTypecastType : std::uint8_t
{
  C_STYLE_CAST,
  FUNCTION_STYLE_CAST,
  STATIC_CAST,
  CONST_CAST,
  DYNAMIC_CAST,
  REINTERPRET_CAST,
};

}

#endif /* BCBB7E53_C4E3_46CF_8E7A_45E1309F97C1 */
