// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E1C8E022_9208_4EA2_BF0E_482C7ABD2C72
#define E1C8E022_9208_4EA2_BF0E_482C7ABD2C72

#include "cppast/cpp_compound.h"
#include "cppast/cppconst.h"
#include "cppast/cpputil.h"
#include "cppast/helper/cpp_entity_ptr.h"

namespace cppast {

inline bool isFunction(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::FUNCTION;
}

inline bool isFunction(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isFunction(*cppEntity);
}

inline bool isFunctionPtr(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::FUNCTION_PTR;
}

inline bool isFunctionPtr(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isFunctionPtr(*cppEntity);
}

inline bool isFunctionLike(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::FUNCTION || cppEntity.entityType() == CppEntityType::CONSTRUCTOR
         || cppEntity.entityType() == CppEntityType::DESTRUCTOR
         || cppEntity.entityType() == CppEntityType::TYPE_CONVERTER;
}

inline bool isFunctionLike(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isFunctionLike(*cppEntity);
}

inline bool isDestructor(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::DESTRUCTOR;
}

inline bool isDestructor(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isDestructor(*cppEntity);
}

inline bool isEnum(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::ENUM;
}

inline bool isEnum(const std::unique_ptr<CppEntity> cppEntity)
{
  return isEnum(*cppEntity);
}

inline bool isTypedefName(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::TYPEDEF_DECL;
}

inline bool isTypedefName(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isTypedefName(*cppEntity);
}

inline bool isUsingDecl(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::USING_DECL;
}

inline bool isUsingDecl(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isUsingDecl(*cppEntity);
}

inline bool isCompound(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::COMPOUND;
}

inline bool isCompound(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isCompound(*cppEntity);
}

inline bool isFwdClsDecl(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::FORWARD_CLASS_DECL;
}

inline bool isFwdClsDecl(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isFwdClsDecl(*cppEntity);
}

inline bool isNamespaceLike(const CppEntity& cppEntity)
{
  const helper::CppEntityPtr<const CppCompound> compound = &cppEntity;
  if (!compound)
  {
    return false;
  }

  return (compound->compoundType() >= CppCompoundType::NAMESPACE)
         && (compound->compoundType() <= CppCompoundType::UNION);
}

inline bool isNamespaceLike(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isNamespaceLike(*cppEntity);
}

bool isClassLike(const CppEntity& cppEntity);

inline bool isClassLike(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isClassLike(*cppEntity);
}

inline bool isTypedefLike(const CppEntity& cppEntity)
{
  return (cppEntity.entityType() == CppEntityType::TYPEDEF_DECL)
         || (cppEntity.entityType() == CppEntityType::USING_DECL);
}

inline bool isTypedefLike(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isTypedefLike(*cppEntity);
}

inline bool isPreProcessorType(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::PREPROCESSOR;
}

inline bool isPreProcessorType(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isPreProcessorType(*cppEntity);
}

inline bool isVar(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::VAR;
}

inline bool isVar(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isVar(*cppEntity);
}

inline bool isVarList(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::VAR_LIST;
}

inline bool isVarList(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isVarList(*cppEntity);
}

inline bool isExpr(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::EXPRESSION;
}

inline bool isExpr(const std::unique_ptr<CppEntity>& cppEntity)
{
  return isExpr(*cppEntity);
}

inline CppCompound* root(const CppEntity& cppEntity)
{
  if (cppEntity.owner() == nullptr)
    return isCompound(cppEntity) ? const_cast<CppCompound*>(static_cast<const CppCompound*>(&cppEntity)) : nullptr;
  return root(*cppEntity.owner());
}

} // namespace cppast

#endif /* E1C8E022_9208_4EA2_BF0E_482C7ABD2C72 */
