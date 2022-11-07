// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef CBCC354D_B949_4767_8FE6_6EA7C16BDF99
#define CBCC354D_B949_4767_8FE6_6EA7C16BDF99

#include <cstring>
#include <memory>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////

// For holding tokens
struct CppToken
{
  const char* sz;
  size_t      len;

  bool operator==(const CppToken& rhs) const
  {
    if (len != rhs.len)
      return false;
    return (sz == rhs.sz) || (std::strncmp(sz, rhs.sz, len) == 0);
  }

  bool operator!=(const CppToken& rhs) const
  {
    if (len != rhs.len)
      return true;
    return std::strncmp(sz, rhs.sz, len) != 0;
  }

  operator std::string() const
  {
    return toString();
  }

  std::string toString() const
  {
    return sz ? std::string(sz, len) : std::string();
  }
};

/**
 * Since CppToken cannot have ctor (because it is intended to be used inside union).
 */
inline CppToken makeCppToken(const char* sz, size_t len)
{
  CppToken tkn = {sz, len};
  return tkn;
}

inline CppToken makeCppToken(const char* beg, const char* end)
{
  return makeCppToken(beg, end - beg);
}

inline CppToken mergeCppToken(const CppToken& token1, const CppToken& token2)
{
  if (token1.sz == nullptr)
    return token2;
  else if (token2.sz == nullptr)
    return token1;
  return makeCppToken(token1.sz, token2.sz + token2.len - token1.sz);
}

template <typename _ST>
inline _ST& operator<<(_ST& stm, const CppToken& token)
{
  for (size_t i = 0; i < token.len; ++i)
    stm << token.sz[i];
  return stm;
}

#endif /* CBCC354D_B949_4767_8FE6_6EA7C16BDF99 */
