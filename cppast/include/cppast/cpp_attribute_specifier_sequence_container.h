// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef AE601D96_EAA0_4A9D_BE7C_7370B42C091B
#define AE601D96_EAA0_4A9D_BE7C_7370B42C091B

#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace cppast {

class CppExpression;

using CppAttributeSpecifierSequence = std::vector<std::unique_ptr<const CppExpression>>;

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
  void attribSpecifierSequence(CppAttributeSpecifierSequence attribSpecifierSequence);
  /**
   * @brief Visits all attribute specifiers.
   *
   * @param callback The callback that is invoked once for each attribute specifier.
   */
  void visitAll(const std::function<void(const CppExpression& attributeSpecifier)>& callback) const;

  /**
   * @brief Similar to visitAll() but interuptible.
   *
   * @param callback If the \a callback returns false then the visit is interrupted.
   * @return true If all attribute specifiers were visited without interruption.
   * @return false If the visit was interrupted.
   */
  bool visit(const std::function<bool(const CppExpression& attributeSpecifier)>& callback) const;

private:
  CppAttributeSpecifierSequence attribSpecifierSequence_;
};

} // namespace cppast

#endif /* AE601D96_EAA0_4A9D_BE7C_7370B42C091B */
