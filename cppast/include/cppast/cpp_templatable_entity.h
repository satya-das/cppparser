// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef D94591D6_2473_4804_A403_3EF86D03DD28
#define D94591D6_2473_4804_A403_3EF86D03DD28

#include <optional>
#include <vector>

namespace cppast {

class CppTemplateParam;
using CppTemplateParams = std::vector<CppTemplateParam>;

/**
 * @brief A mixin class for templated C++ entities.
 */
class CppTemplatableEntity
{
public:
  bool isTemplated() const
  {
    return templateSpecification().has_value();
  }

  const std::optional<CppTemplateParams>& templateSpecification() const;
  void                                    templateSpecification(CppTemplateParams templateSpec);

private:
  std::optional<CppTemplateParams> templateSpec_;
};

} // namespace cppast

#include "cppast/cpp_template_param.h"

#endif /* D94591D6_2473_4804_A403_3EF86D03DD28 */
