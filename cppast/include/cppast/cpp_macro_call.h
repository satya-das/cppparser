// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B9206103_B378_465F_A068_6881180E9E14
#define B9206103_B378_465F_A068_6881180E9E14

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppMacroCall : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::MACRO_CALL;
  }

public:
  const std::string macroCall_;

  CppMacroCall(std::string macroCall)
    : CppEntity(EntityType())
    , macroCall_(std::move(macroCall))
  {
  }
};

} // namespace CppAst

#endif /* B9206103_B378_465F_A068_6881180E9E14 */
