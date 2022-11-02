// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_templatable_entity.h"

namespace CppAst {

const std::optional<CppTemplateParams>& CppTemplatableEntity::templateSpecification() const
{
  return templateSpec_;
}

void CppTemplatableEntity::templateSpecification(CppTemplateParams templateSpec)
{
  templateSpec_ = std::move(templateSpec);
}

} // namespace CppAst
