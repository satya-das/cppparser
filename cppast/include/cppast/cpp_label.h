// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E30E46D8_977F_4095_AFE4_B7D72CFA8703
#define E30E46D8_977F_4095_AFE4_B7D72CFA8703

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppLabel : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::LABEL;
  }

public:
  CppLabel(std::string label)
    : CppEntity(EntityType())
    , label_(std::move(label))
  {
  }

public:
  const std::string& Label() const
  {
    return label_;
  }

private:
  const std::string label_;
};

} // namespace CppAst

#endif /* E30E46D8_977F_4095_AFE4_B7D72CFA8703 */
