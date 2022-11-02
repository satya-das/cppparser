// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DC791634_A5B8_43D9_AEAB_43092F1830EE
#define DC791634_A5B8_43D9_AEAB_43092F1830EE

#include "cppast/cpp_entity.h"

namespace CppAst {

class CppPreprocessorError : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_ERROR;
  }

public:
  CppPreprocessorError(std::string err)
    : CppEntity(EntityType())
    , err_(std::move(err))
  {
  }

  const std::string& Error() const
  {
    return err_;
  }

private:
  const std::string err_;
};

} // namespace CppAst

#endif /* DC791634_A5B8_43D9_AEAB_43092F1830EE */
