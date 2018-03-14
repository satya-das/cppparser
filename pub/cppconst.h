/*
The MIT License (MIT)

Copyright (c) 2014

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

#ifndef __CPP_CONST_H__
#define __CPP_CONST_H__

#include <cstdint>

enum CppCompoundType
{
  kUnknownCompound  = 0x00,
  kCppFile          = 0x01,
  kNamespace        = 0x02,
  kClass            = 0x04 | kNamespace,
  kStruct           = 0x08 | kClass,
  kUnion            = 0x10 | kClass,
  kBlock            = 0x20,
  kExternCBlock     = 0x40,
};

enum CppObjProtLevel : std::uint8_t
{
  kUnknownProt,
  kPublic,
  kPrivate,
  kProtected
};

enum CppOperType
{
  kNone,

  kUnariPrefixOperatorStart,
  kUnaryMinus,    // -
  kBitToggle,     // ~
  kLogNot,        // ! (Logical not)
  kDerefer,       // *
  kRefer,         // & as in &x;
  kPreIncrement,  // ++i
  kPreDecrement,  // --i

  kUnariSufixOperatorStart,
  kPostIncrement, // i++
  kPostDecrement, // i--

  kBinaryOperatorStart,
  kPlus,        // +
  kMinus,       // -
  kMul,         // *
  kDiv,         // /
  kPercent,
  kAnd,
  kOr,
  kBitAnd,      // &
  kBitOr,       // |
  kXor,
  kEqual,       // =
  kLess,        // <
  kGreater,     // >
  kPlusEqual,
  kMinusEqual,
  kMulEqual,
  kDivEqual,
  kPerEqual,
  kXorEqual,
  kAndEqual,
  kOrEqual,
  kLeftShift,   // <<
  kRightShift,  // >>
  kLShiftEqual,   // <<
  kRShiftEqual,  // >>
  kCmpEqual,    // ==
  kNotEqual,    // ==
  kLessEqual, // <=
  kGreaterEqual,
  k3WayCmp,
  kComma,

  kDerefOperatorStart,
  kDot,         // .
  kArrow,       // ->
  kArrowStar,

  kSpecialOperations = 100,
  kFunctionCall,
  kArrayElem,   // x[5]
  kCStyleCast,
  kConstCast,
  kStaticCast,
  kDynamicCast,
  kReinterpretCast,
};

/**
 * State of variable or function.
 */
enum CppIdentifierAttrib
{
  kFuncParam    = 0x0001, // If the identifier is actually function parameter.
  kConst        = 0x0002,
  kStatic       = 0x0004,
  kExtern       = 0x0008,
  kInline       = 0x0010,
  kVirtual      = 0x0020,
  kPureVirtual  = 0x0040 | kVirtual,
  kOverride     = 0x0080 | kVirtual,
  kExplicit     = 0x0100,
  kFriend       = 0x0200,
  kTypedef      = 0x0400, // Function pointer is used in typedef.
  kArray        = 0x0800, // Identifier is an array.
  kConstExpr    = 0x1000,
  kVolatile     = 0x2000,
};

/**
 * Type of references a variable can have in a C++ program.
 */
enum CppRefType
{
  kNoRef,   // No reference.
  kByRef,   // Simple reference, e.g. int& x.
  kRValRef  // R-value reference, e.g. in move constructor.
};

/// Miscellaneous constants for readability of code
enum
{
  kNoPtr      = 0,
  kPtr        = 1,
  kDblPtr     = 2,
  kNoVarAttr  = 0,
  kNoTypeAttr = 0,
  kNoAttr     = 0,
};

#endif //__CPP_CONST_H__
