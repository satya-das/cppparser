// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E6097D4F_30B2_4DBB_BD3D_0FAE0F8AD156
#define E6097D4F_30B2_4DBB_BD3D_0FAE0F8AD156

#include "cppast/cpp_entity.h"

namespace cppast {

/**
 * @brief A documentation comment is any comment that stands all alone in one or multiple lines.
 */
class CppDocumentationComment : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::DOCUMENTATION_COMMENT;
  }

public:
  CppDocumentationComment(std::string doc)
    : CppEntity(EntityType())
    , doc_(std::move(doc))
  {
  }

public:
  const std::string& str() const
  {
    return doc_;
  }

private:
  const std::string doc_; ///< Entire comment text
};

} // namespace cppast

#endif /* E6097D4F_30B2_4DBB_BD3D_0FAE0F8AD156 */
