// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B9B4B822_F222_4FB9_98EC_C3C7C3B922EA
#define B9B4B822_F222_4FB9_98EC_C3C7C3B922EA

#include <cstdint>
#include <ostream>

namespace cppcodegen {

/**
 * @brief Helper class to manage indentation while writing C++ file from AST.
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

  CppIndent resetted() const
  {
    CppIndent newIndent(0, type_);

    return newIndent;
  }
};

} // namespace cppcodegen

#endif /* B9B4B822_F222_4FB9_98EC_C3C7C3B922EA */
