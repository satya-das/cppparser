#pragma once

#include <cstdint>
#include <ostream>

/**
* \brief Helper class to manage indentation.
*/
class CppIndent
{
public:
  enum Type { kTab, kSingleSpace, kDoubleSpace, kTripleSpace, kQuadSpace };

private:
  std::uint16_t	indentLevel_;
  std::uint16_t initialLevel_;
  Type		type_;

public:
  CppIndent(std::uint16_t initialLevel = 0, Type type = kTab)
    : indentLevel_(0)
    , initialLevel_(initialLevel)
    , type_(type)
  {}
  CppIndent& operator++()
  {
    ++indentLevel_;
    return *this;
  }
  CppIndent& operator--()
  {
    if (indentLevel_) --indentLevel_;
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
    if (indentLevel_) --indentLevel_;
    return ret;
  }

  void emit(std::ostream& stm) const
  {
    static const char* indent[] = { "\t", " ", "  ", "   ", "    " };
    for (std::uint16_t i = 0; i < initialLevel_ + indentLevel_; ++i)
    {
      stm << indent[type_];
    }
  }
};
