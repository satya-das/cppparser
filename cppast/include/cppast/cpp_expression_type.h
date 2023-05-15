// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B2C1931F_6AC0_4C54_8AF3_8FA48AF79344
#define B2C1931F_6AC0_4C54_8AF3_8FA48AF79344

#include <cstdint>

namespace cppast {

enum class CppExpressionType : std::uint8_t
{
  ATOMIC,
  MONOMIAL,
  BINOMIAL,
  TRINOMIAL, // The only example is ternary operator.
  FUNCTION_CALL,
  UNIFORM_INITIALIZER,
  INITIALIZER_LIST,
  TYPECAST,
};

}

#endif /* B2C1931F_6AC0_4C54_8AF3_8FA48AF79344 */
