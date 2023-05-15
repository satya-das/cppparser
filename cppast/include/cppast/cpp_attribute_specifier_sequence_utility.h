// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef CBA4D49F_F734_48F4_AF04_F92825C255F4
#define CBA4D49F_F734_48F4_AF04_F92825C255F4

#include "cppast/cpp_attribute_specifier_sequence_container.h"

#include <vector>

namespace cppast {

class CppExpression;

inline std::vector<const CppExpression*> GetAllAttributeSpecifiers(
  const CppAttributeSpecifierSequenceContainer& attribSpecifierSequenceContainer)
{
  std::vector<const CppExpression*> result;
  attribSpecifierSequenceContainer.visitAll(
    [&result](const CppExpression& attributeSpecifier) { result.push_back(&attributeSpecifier); });

  return result;
}

} // namespace cppast

#endif /* CBA4D49F_F734_48F4_AF04_F92825C255F4 */
