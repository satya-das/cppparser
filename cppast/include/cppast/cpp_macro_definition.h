// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BE744AC2_52B3_46C4_A40D_9DB23E75A1F2
#define BE744AC2_52B3_46C4_A40D_9DB23E75A1F2

#include "cppast/cpp_entity.h"

namespace CppAst {

enum class CppMacroDefinitionType
{
  RENAME,
  NUMBER,
  STRING,
  CHARACTER,
  COMPLEX_DEFN,
};

/**
 * @brief A macro definition.
 */
class CppMacroDefinition : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::MACRO_DEFINITION;
  }

public:
  CppMacroDefinition(CppMacroDefinitionType defType, std::string name, std::string defn = std::string())
    : CppEntity(EntityType())
    , defType_(defType)
    , name_(std::move(name))
    , defn_(std::move(defn))
  {
  }

  CppMacroDefinitionType DefinitionType() const
  {
    return defType_;
  }

  const std::string& name() const
  {
    return name_;
  }

  const std::string& Definition() const
  {
    return defn_;
  }

private:
  const CppMacroDefinitionType defType_;
  const std::string            name_;
  const std::string            defn_; ///< This will contain everything after name.
};

} // namespace CppAst

#endif /* BE744AC2_52B3_46C4_A40D_9DB23E75A1F2 */
