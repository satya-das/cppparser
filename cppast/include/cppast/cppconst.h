// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B4E3E2F0_32A5_4467_9B89_34E1B7EE51AD
#define B4E3E2F0_32A5_4467_9B89_34E1B7EE51AD

#include <cstdint>

namespace cppast {

/**
 * State of variable or function.
 */
enum /*class*/ CppIdentifierAttrib : std::uint32_t
{
  FUNC_PARAM      = 0x000001, // If the identifier is actually function parameter.
  CONST           = 0x000002,
  STATIC          = 0x000004,
  EXTERN          = 0x000008,
  INLINE          = 0x000010,
  VIRTUAL         = 0x000020,
  PURE_VIRTUAL    = 0x000040 | VIRTUAL,
  OVERRIDE        = 0x000080 | VIRTUAL,
  EXPLICIT        = 0x000100,
  FRIEND          = 0x000200,
  TYPEDEF         = 0x000400, // Function pointer is used in typedef.
  CONST_EXPR      = 0x001000,
  VOLATILE        = 0x002000,
  FINAL           = 0x004000 | VIRTUAL,
  DEFAULT         = 0x008000,
  DELETE          = 0x010000,
  NO_EXCEPT       = 0x020000,
  EXTERN_C        = 0x040000,
  TRAILING_RETURN = 0x080000,
  MUTABLE         = 0x100000,
  NO_EXCEPT_FALSE = 0x200000,
};

} // namespace cppast

#endif /* B4E3E2F0_32A5_4467_9B89_34E1B7EE51AD */
