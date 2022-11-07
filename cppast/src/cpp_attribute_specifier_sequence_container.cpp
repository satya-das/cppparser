// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_attribute_specifier_sequence_container.h"
#include "cppast/cpp_expression.h"

namespace cppast {

void CppAttributeSpecifierSequenceContainer::attribSpecifierSequence(
  CppAttributeSpecifierSequence attribSpecifierSequence)
{
  attribSpecifierSequence_ = std::move(attribSpecifierSequence);
}

const CppAttributeSpecifierSequence& CppAttributeSpecifierSequenceContainer::attribSpecifierSequence() const
{
  return attribSpecifierSequence_;
}

} // namespace cppast
