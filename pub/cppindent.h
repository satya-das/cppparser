/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

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

#pragma once

#include <cstdint>
#include <ostream>

/**
 * \brief Helper class to manage indentation.
 */
class CppIndent
{
public:
  enum Type
  {
    kTab,
    kSingleSpace,
    kDoubleSpace,
    kTripleSpace,
    kQuadSpace
  };

private:
  std::uint16_t       indentLevel_;
  const std::uint16_t initialLevel_;
  Type                type_;

public:
  CppIndent(std::uint16_t initialLevel = 0, Type type = kDoubleSpace)
    : indentLevel_(0)
    , initialLevel_(initialLevel)
    , type_(type)
  {
  }
  std::uint16_t depth() const
  {
    return indentLevel_ + initialLevel_;
  }
  CppIndent& operator++()
  {
    ++indentLevel_;
    return *this;
  }
  CppIndent& operator--()
  {
    if (indentLevel_)
      --indentLevel_;
    return *this;
  }
  CppIndent operator++(int)
  {
    CppIndent ret = *this;
    ++indentLevel_;
    return ret;
  }
  CppIndent operator--(int)
  {
    CppIndent ret = *this;
    if (indentLevel_)
      --indentLevel_;
    return ret;
  }

  const char* indentStr() const
  {
    static const char* indent[] = {"\t", " ", "  ", "   ", "    "};
    return indent[type_];
  }
  std::string toString() const
  {
    std::string ret;
    for (std::uint16_t i = 0; i < initialLevel_ + indentLevel_; ++i)
    {
      ret += indentStr();
    }

    return ret;
  }
  void emit(std::ostream& stm) const
  {
    for (std::uint16_t i = 0; i < initialLevel_ + indentLevel_; ++i)
    {
      stm << indentStr();
    }
  }
};
