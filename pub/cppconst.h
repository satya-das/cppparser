// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

// TODO: Get rid of this whole file

#ifndef B151CBFF_0671_4D68_BB20_9910FD995AC2
#define B151CBFF_0671_4D68_BB20_9910FD995AC2

#include <cstdint>

// TODO: Get rid of this
enum class TriStateBool : std::int8_t
{
  Unknown = -1,
  False   = 0,
  True    = 1
};

enum class CppAccessType : std::uint8_t
{
  kUnknown,
  PUBLIC,
  PRIVATE,
  PROTECTED
};

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

/**
 * State of variable or function.
 */
enum /*class*/ CppIdentifierAttrib : std::uint32_t
{
  kFuncParam     = 0x000001, // If the identifier is actually function parameter.
  kConst         = 0x000002,
  kStatic        = 0x000004,
  kExtern        = 0x000008,
  kInline        = 0x000010,
  kVirtual       = 0x000020,
  kPureVirtual   = 0x000040 | kVirtual,
  kOverride      = 0x000080 | kVirtual,
  kExplicit      = 0x000100,
  kFriend        = 0x000200,
  kTypedef       = 0x000400, // Function pointer is used in typedef.
  kConstExpr     = 0x001000,
  kVolatile      = 0x002000,
  kFinal         = 0x004000 | kVirtual,
  kDefault       = 0x008000,
  kDelete        = 0x010000,
  kNoExcept      = 0x020000,
  kExternC       = 0x040000,
  kTrailingRet   = 0x080000,
  kMutable       = 0x100000,
  kNoExceptFalse = 0x200000,
};

/**
 * Type of references a variable can have in a C++ program.
 */
enum class CppRefType : std::uint8_t
{
  NONE,    // No reference.
  BY_REF,  // Simple reference, e.g. int& x.
  RVAL_REF // R-value reference, e.g. in move constructor.
};

#endif /* B151CBFF_0671_4D68_BB20_9910FD995AC2 */
