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

enum CppCompoundType
{
  kUnknownCompound	= 0x00,
  kCppFile			= 0x01,
  kNamespace			= 0x02,
  kClass				= 0x04 | kNamespace,
  kStruct				= 0x08 | kClass,
  kUnion				= 0x10 | kClass,
  kBlock				= 0x20,
  kExternCBlock		= 0x40,
};

enum CppObjProtLevel
{
  kUnknownProt,
  kPublic,
  kPrivate,
  kProtected
};

enum CppOperType
{
  kNone,

  kUnariOperatorStart = 1,
  kUnaryMinus,	// -
  kBitToggle,		// ~
  kLogNot,		// ! (Logical not)
  kDerefer,		// *
  kRefer,			// & as in &x;

  kBinaryOperatorStart = 50,
  kDot,			// .
  kArrow,			// ->
  kPlus,			// +
  kMinus,			// -
  kMul,			// *
  kDiv,			// /
  kEqual,			// =
  kCmpEqual,		// ==
  kLeftShift, // <<
  kRightShift, // >>
  kBitAnd,		// &
  kBitOr,			// |

  kSpecialOperations = 100,
  kFunctionCall,
  kArrayElem,		// x[5]
};

/**
 * State of variable or function.
 */
enum CppIdentifierAttrib
{
  kFuncParam			= 0x001, // If the identifier is actually function parameter.
  kConst              = 0x002,
  kStatic             = 0x004,
  kExtern             = 0x008,
  kInline             = 0x010,
  kVirtual            = 0x020,
  kPureVirtual        = 0x040 | kVirtual,
  kOverride           = 0x080 | kVirtual,
  kExplicit           = 0x100,
  kFriend				= 0x200,
  kTypedef			= 0x400, // Function pointer is used in typedef.
  kArray				= 0x800, // Identifier is an array.
  kConstExpr			= 0x1000,
};

/**
 * Type of references a variable can have in a C++ program.
 */
enum CppRefType
{
  kNoRef, // No reference.
  kByRef, // Simple reference, e.g. int& x.
  kRValRef // R-value reference, e.g. in move constructor.
};

/// Miscellaneous constants for readability of code
enum
{
  kNoPtr		= 0,
  kPtr		= 1,
  kDblPtr		= 2,
  kNoVarAttr	= 0,
  kNoTypeAttr	= 0,
  kNoAttr		= 0,
};

#endif //__CPP_CONST_H__
