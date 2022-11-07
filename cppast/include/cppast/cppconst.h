// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

// TODO: Get rid of this whole file

#ifndef B4E3E2F0_32A5_4467_9B89_34E1B7EE51AD
#define B4E3E2F0_32A5_4467_9B89_34E1B7EE51AD

#include <cstdint>

namespace cppast {

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

} // namespace cppast

#endif /* B4E3E2F0_32A5_4467_9B89_34E1B7EE51AD */
