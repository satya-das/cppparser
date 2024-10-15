// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef F8BEE2E4_A22C_446D_9225_A5B383798075
#define F8BEE2E4_A22C_446D_9225_A5B383798075

#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression.h"

#include <list>
#include <memory>
#include <string>

namespace cppast {

class CppEntity;
class CppExpression;

/**
 * @brief Anything that appears inside enum declaration.
 *
 * Inside an enum definition there can also be enitities other than constant definitions, e.g. comments, and
 * proprocessors.
 */
class CppEnumItem
{
public:
  CppEnumItem(std::string name, std::unique_ptr<CppExpression> val = nullptr);
  CppEnumItem(std::unique_ptr<CppEntity> nonConstEntity);

public:
  const std::string& name() const
  {
    return name_;
  }

  /**
   * @brief Value of the enum constant.
   *
   * @return nullptr iff the value of the constant is not set.
   */
  const CppExpression* val() const
  {
    return val_.get();
  }

  /**
   * @brief Non const enum item entity.
   *
   * @return nullptr iff the enum item is a constant definition.
   */
  const CppEntity* nonConstEntity() const
  {
    return nonConstEntity_.get();
  }

  /**
   * @return true iif the enum item is the definition of a constant.
   */
  bool isNonConstEntity() const
  {
    return nonConstEntity_ != nullptr;
  }

private:
  std::string                name_;
  std::unique_ptr<CppExpression>   val_;
  std::unique_ptr<CppEntity> nonConstEntity_;
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

} // namespace cppast

#endif /* F8BEE2E4_A22C_446D_9225_A5B383798075 */
