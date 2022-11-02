// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef CAFF3DFE_BB8D_47DB_A353_C7D49275CEC6
#define CAFF3DFE_BB8D_47DB_A353_C7D49275CEC6

#include "cppast/cpp_access_type.h"
#include "cppast/cpp_blob.h"
#include "cppast/cpp_entity.h"
#include "cppast/cpp_templatable_entity.h"
#include "cppast/defs.h"

#include <cassert>
#include <functional>
#include <list>
#include <memory>
#include <type_traits>
#include <vector>

namespace CppAst {

enum class CppCompoundType
{
  UNKNOWN,
  FILE,
  NAMESPACE,
  CLASS,
  STRUCT,
  UNION,
  BLOCK,
  EXTERN_C_BLOCK,
};

struct CppInheritanceInfo
{
  const std::string   baseName;
  const CppAccessType inhType;
  const bool          isVirtual {false};

  // TODO: Maybe we don't need this ctor
  CppInheritanceInfo(std::string _baseName, CppAccessType _inhType, bool virtualInheritance = false)
    : baseName(std::move(_baseName))
    , inhType(_inhType)
    , isVirtual(virtualInheritance)
  {
  }
};

/**
 * @brief A compound C++ entity.

 * All classes, structs, unions, and namespaces can be classified as a Compound object.
 * Besides that followings too are compound objects:
 *  - An entire C/C++ source file.
 *  - A block of statements inside { }.
 *  - body of function definition.
 *
 * FIXME: Separate out different class for File, Namespace, Class-like, and the rest.
 */
class CppCompound : public CppEntity, public CppTemplatableEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::COMPOUND;
  }

public:
  CppCompound(std::string name, CppCompoundType type);
  CppCompound(CppCompoundType type = CppCompoundType::UNKNOWN);

public:
  CppCompoundType compoundType() const
  {
    return compoundType_;
  }

  void compoundType(CppCompoundType compoundType)
  {
    // Change of compound type is largely not allowed.
    // Although while parsing 'extern "C"' the inner part may be first parsed as block
    // which gets promoted as extern-c-block.
    assert((compoundType_ == CppCompoundType::UNKNOWN) || (compoundType_ == CppCompoundType::BLOCK));
    compoundType_ = compoundType;
  }

  void add(std::unique_ptr<CppEntity> entity)
  {
    entities_.push_back(std::move(entity));
    entities_.back()->owner(*this);
  }

  void addAtFront(std::unique_ptr<CppEntity> entity)
  {
    entities_.insert(entities_.begin(), std::move(entity));
    entities_.front()->owner(*this);
  }

  bool visitAll(const Visitor<const CppEntity&>& callback) const;

  template <typename _EntityClass>
  bool visit(const Visitor<const _EntityClass&>& callback) const
  {
    return visitAll([&callback](const CppEntity& entity) {
      return (entity.entityType() != _EntityClass::EntityType()) || callback(static_cast<const _EntityClass&>(entity));
    });
  }

  const std::string& name() const
  {
    return name_;
  }
  void name(std::string _name)
  {
    name_ = std::move(_name);
  }

  const std::string& apidecor() const
  {
    return apidecor_;
  }
  void apidecor(std::string apidecor)
  {
    apidecor_ = std::move(apidecor);
  }

  const std::list<CppInheritanceInfo>& inheritanceList() const
  {
    return inheritanceList_;
  }
  void inheritanceList(std::list<CppInheritanceInfo> _inheritanceList)
  {
    inheritanceList_ = std::move(_inheritanceList);
  }

  void addAttr(std::uint32_t _attr)
  {
    attr_ |= _attr;
  }

  bool hasAttr(std::uint32_t _attr) const
  {
    return (attr_ & _attr) == _attr;
  }

private:
  std::vector<std::unique_ptr<CppEntity>> entities_;
  std::string                             name_;
  CppCompoundType                         compoundType_;
  std::list<CppInheritanceInfo>           inheritanceList_;
  std::string                             apidecor_;
  std::uint32_t                           attr_ {0}; // e.g. final
};

} // namespace CppAst

#endif /* CAFF3DFE_BB8D_47DB_A353_C7D49275CEC6 */
