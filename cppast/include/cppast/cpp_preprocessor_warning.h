// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DB1B2C8A_BCA8_4701_A6B5_A7E02B37D32C
#define DB1B2C8A_BCA8_4701_A6B5_A7E02B37D32C

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppPreprocessorWarning : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_WARNING;
  }

public:
  const std::string err_;

  CppPreprocessorWarning(std::string err)
    : CppEntity(EntityType())
    , err_(std::move(err))
  {
  }
};

} // namespace CppAst

#endif /* DB1B2C8A_BCA8_4701_A6B5_A7E02B37D32C */
