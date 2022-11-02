// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef AC0E36D5_D135_4787_BB9B_F3FB72DF023D
#define AC0E36D5_D135_4787_BB9B_F3FB72DF023D

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppPreprocessorImport : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_IMPORT;
  }

public:
  CppPreprocessorImport(std::string name)
    : CppEntity(EntityType())
    , name_(std::move(name))
  {
  }

  const std::string& name() const
  {
    return name_;
  }

private:
  const std::string name_;
};

} // namespace CppAst

#endif /* AC0E36D5_D135_4787_BB9B_F3FB72DF023D */
