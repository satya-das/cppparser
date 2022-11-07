// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_enum.h"

namespace cppast {

CppEnumItem::CppEnumItem(std::string name, std::unique_ptr<CppExpr> val)
  : name_(std::move(name))
  , val_(std::move(val))
{
}

CppEnumItem::CppEnumItem(std::unique_ptr<CppEntity> anyItem)
  : val_(std::move(anyItem))
{
}

} // namespace cppast
