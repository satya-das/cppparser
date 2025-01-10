// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B9206103_B378_465F_A068_6881180E9E14
#define B9206103_B378_465F_A068_6881180E9E14

#include "cppast/cpp_entity.h"

namespace cppast {

class CppMacroCall : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::MACRO_CALL;
  }

public:
  CppMacroCall(std::string macroCall)
    : CppEntity(EntityType())
    , macroCall_(std::move(macroCall))
  {
  }

public:
  const std::string& macroCall() const
  {
    return macroCall_;
  }

private:
  std::string macroCall_;
};

} // namespace cppast

#endif /* B9206103_B378_465F_A068_6881180E9E14 */
