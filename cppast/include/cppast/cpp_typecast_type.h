// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BCBB7E53_C4E3_46CF_8E7A_45E1309F97C1
#define BCBB7E53_C4E3_46CF_8E7A_45E1309F97C1

#include <cstdint>

namespace cppast {

enum class CppTypecastType : std::uint8_t
{
  C_STYLE,
  FUNCTION_STYLE,
  STATIC,
  CONST,
  DYNAMIC,
  REINTERPRET,
};

}

#endif /* BCBB7E53_C4E3_46CF_8E7A_45E1309F97C1 */
