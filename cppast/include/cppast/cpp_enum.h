// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef F8BEE2E4_A22C_446D_9225_A5B383798075
#define F8BEE2E4_A22C_446D_9225_A5B383798075

#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression.h"

#include <list>
#include <memory>
#include <string>

namespace CppAst {

class CppEntity;
class CppExpr;

// TODO: make it private nested
/**
 * @brief Anything that appears inside enum declaration.
 */
class CppEnumItem
{
public:
  CppEnumItem(std::string name, std::unique_ptr<CppExpr> val = nullptr);
  CppEnumItem(std::unique_ptr<CppEntity> anyItem);

public:
  const std::string& name() const
  {
    return name_;
  }

  const CppEntity* val() const
  {
    return val_.get();
  }

  /**
   * @return true iif the enum item is the definition of a constant.
   */
  bool isConstEnumItem() const
  {
    return !name().empty();
  }

private:
  const std::string                name_;
  const std::unique_ptr<CppEntity> val_;
};

class CppEnum : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::ENUM;
  }

public:
  CppEnum(std::string            name,
          std::list<CppEnumItem> itemList,
          bool                   isClass        = false,
          std::string            underlyingType = std::string())
    : CppEntity(EntityType())
    , name_(std::move(name))
    , itemList_(std::move(itemList))
    , isClass_(isClass)
    , underlyingType_(std::move(underlyingType))
  {
  }

public:
  const std::string& name() const
  {
    return name_;
  }

  const std::list<CppEnumItem>& itemList() const
  {
    return itemList_;
  }

  bool isClass() const
  {
    return isClass_;
  }

  const std::string& underlyingType() const
  {
    return underlyingType_;
  }

private:
  const std::string            name_;     // Can be empty for anonymous enum.
  const std::list<CppEnumItem> itemList_; // Can be nullptr for forward declared enum.
  const bool                   isClass_;
  const std::string            underlyingType_;
};

} // namespace CppAst

#endif /* F8BEE2E4_A22C_446D_9225_A5B383798075 */
