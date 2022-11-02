// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef AE601D96_EAA0_4A9D_BE7C_7370B42C091B
#define AE601D96_EAA0_4A9D_BE7C_7370B42C091B

#include <memory>
#include <utility>
#include <vector>

namespace CppAst {

class CppExpr;

using CppAttributeSpecifierSequence = std::vector<std::unique_ptr<CppExpr>>;

/**
 * @brief A mixin class to allow objects to have attribute specifier sequence
 * as described at https://en.cppreference.com/w/cpp/language/attributes.
 */
class CppAttributeSpecifierSequenceContainer
{
public:
  CppAttributeSpecifierSequenceContainer();
  ~CppAttributeSpecifierSequenceContainer();

public:
  void                                 attribSpecifierSequence(CppAttributeSpecifierSequence attribSpecifierSequence);
  const CppAttributeSpecifierSequence& attribSpecifierSequence() const;

private:
  CppAttributeSpecifierSequence attribSpecifierSequence_;
};

} // namespace CppAst

#endif /* AE601D96_EAA0_4A9D_BE7C_7370B42C091B */
