// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B53E618A_F2E7_4C5F_A58E_4C1065A96113
#define B53E618A_F2E7_4C5F_A58E_4C1065A96113

#include "cppast/cpp_entity.h"

namespace CppAst {

/**
 * Any other C/C++ preprocessor for which there is no
 * class defined yet.
 */
class CppPreprocessorUnrecognized : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_UNRECOGNIZED;
  }

public:
  CppPreprocessorUnrecognized(std::string name, std::string defn)
    : CppEntity(EntityType())
    , name_(std::move(name))
    , defn_(std::move(defn))
  {
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
  const std::string name_;
  const std::string defn_;
};

} // namespace CppAst

#endif /* B53E618A_F2E7_4C5F_A58E_4C1065A96113 */
