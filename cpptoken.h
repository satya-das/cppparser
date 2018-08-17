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

#ifndef __CPPTOKEN_H__
#define __CPPTOKEN_H__

#include <string>
#include <cstring>

//////////////////////////////////////////////////////////////////////////

// For holding tokens
struct CppToken
{
  const char* sz;
  size_t len;

  bool operator == (const CppToken& rhs) const
  {
    if (len != rhs.len) return false;
    return (sz == rhs.sz) || (std::strncmp(sz, rhs.sz, len) == 0);
  }

  bool operator != (const CppToken& rhs) const
  {
    if (len != rhs.len) return true;
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
  makeCppToken(beg, end-beg);
}

inline CppToken mergeCppToken(const CppToken& token1, const CppToken& token2)
{
  return makeCppToken(token1.sz, token2.sz+token2.len-token1.sz);
}

struct CppExprList;

/* Non-terminal for member initalizer */
struct CppNtMemInit
{
  CppToken      mem;
  CppExprList*  init;
};

#endif //__CPPTOKEN_H__
