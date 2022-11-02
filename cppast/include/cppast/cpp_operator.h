// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E96F855A_0EF2_4779_9DE7_52A363D667ED
#define E96F855A_0EF2_4779_9DE7_52A363D667ED

#include <cstdint>

namespace CppAst {

// TODO: adhere to new coding style
enum /*class*/ CppOperator : std::uint8_t
{
  kNone,

  kUnariPrefixOperatorStart,
  kUnaryMinus,   // -
  kBitToggle,    // ~
  kLogNot,       // ! (Logical not)
  kDerefer,      // *
  kRefer,        // & as in &x;
  kPreIncrement, // ++i
  kPreDecrement, // --i

  kUnariSufixOperatorStart,
  kPostIncrement, // i++
  kPostDecrement, // i--

  kBinaryOperatorStart,
  kPlus,  // +
  kMinus, // -
  kMul,   // *
  kDiv,   // /
  kPercent,
  kAnd,
  kOr,
  kBitAnd, // &
  kBitOr,  // |
  kXor,
  kEqual,   // =
  kLess,    // <
  kGreater, // >
  kPlusEqual,
  kMinusEqual,
  kMulEqual,
  kDivEqual,
  kPerEqual,
  kXorEqual,
  kAndEqual,
  kOrEqual,
  kLeftShift, // <<
  kInsertion = kLeftShift,
  kRightShift, // >>
  kExtraction = kRightShift,
  kLShiftEqual, // <<=
  kRShiftEqual, // >>=
  kCmpEqual,    // ==
  kNotEqual,    // ==
  kLessEqual,   // <=
  kGreaterEqual,
  k3WayCmp,
  kComma,
  kBinaryOperatorEnd,

  kDerefOperatorStart,
  kDot,   // .
  kArrow, // ->
  kArrowStar,

  kSpecialOperations = 100,
  kFunctionCall,
  kUniformInitCall,
  kArrayElem, // x[5]
  kCStyleCast,
  kFunctionStyleCast,
  kConstCast,
  kStaticCast,
  kDynamicCast,
  kReinterpretCast,
  kPlacementNew,

  kTertiaryOperator,
};

} // namespace CppAst

#endif /* E96F855A_0EF2_4779_9DE7_52A363D667ED */
