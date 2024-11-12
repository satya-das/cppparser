// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E1C8E022_9208_4EA2_BF0E_482C7ABD2C72
#define E1C8E022_9208_4EA2_BF0E_482C7ABD2C72

#include "cppast/cpp_compound.h"
#include "cppast/cppconst.h"
#include "cppast/cpputil.h"
#include "cppast/helper/cpp_entity_ptr.h"

namespace cppast {

inline bool IsFunction(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::FUNCTION;
}

inline bool IsFunction(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsFunction(*cppEntity);
}

inline bool IsFunctionPtr(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::FUNCTION_PTR;
}

inline bool IsFunctionPtr(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsFunctionPtr(*cppEntity);
}

inline bool IsFunctionLike(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::FUNCTION || cppEntity.entityType() == CppEntityType::CONSTRUCTOR
         || cppEntity.entityType() == CppEntityType::DESTRUCTOR
         || cppEntity.entityType() == CppEntityType::TYPE_CONVERTER;
}

inline bool IsFunctionLike(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsFunctionLike(*cppEntity);
}

inline bool IsDestructor(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::DESTRUCTOR;
}

inline bool IsDestructor(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsDestructor(*cppEntity);
}

inline bool IsEnum(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::ENUM;
}

inline bool IsEnum(const std::unique_ptr<CppEntity> cppEntity)
{
  return IsEnum(*cppEntity);
}

inline bool IsTypedefName(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::TYPEDEF_DECL;
}

inline bool IsTypedefName(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsTypedefName(*cppEntity);
}

inline bool IsUsingDecl(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::USING_DECL;
}

inline bool IsUsingDecl(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsUsingDecl(*cppEntity);
}

inline bool IsCompound(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::COMPOUND;
}

inline bool IsCompound(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsCompound(*cppEntity);
}

inline bool IsFwdClsDecl(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::FORWARD_CLASS_DECL;
}

inline bool IsFwdClsDecl(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsFwdClsDecl(*cppEntity);
}

inline bool IsNamespaceLike(const CppEntity& cppEntity)
{
  const helper::CppEntityPtr<const CppCompound> compound = &cppEntity;
  if (!compound)
  {
    return false;
  }

  return (compound->compoundType() >= CppCompoundType::NAMESPACE)
         && (compound->compoundType() <= CppCompoundType::UNION);
}

inline bool IsNamespaceLike(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsNamespaceLike(*cppEntity);
}

bool IsClassLike(const CppEntity& cppEntity);

inline bool IsClassLike(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsClassLike(*cppEntity);
}

inline bool IsTypedefLike(const CppEntity& cppEntity)
{
  return (cppEntity.entityType() == CppEntityType::TYPEDEF_DECL)
         || (cppEntity.entityType() == CppEntityType::USING_DECL);
}

inline bool IsTypedefLike(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsTypedefLike(*cppEntity);
}

inline bool IsPreProcessorType(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::PREPROCESSOR;
}

inline bool IsPreProcessorType(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsPreProcessorType(*cppEntity);
}

inline bool IsVar(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::VAR;
}

inline bool IsVar(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsVar(*cppEntity);
}

inline bool IsVarList(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::VAR_LIST;
}

inline bool IsVarList(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsVarList(*cppEntity);
}

inline bool IsExpr(const CppEntity& cppEntity)
{
  return cppEntity.entityType() == CppEntityType::EXPRESSION;
}

inline bool IsExpr(const std::unique_ptr<CppEntity>& cppEntity)
{
  return IsExpr(*cppEntity);
}

inline CppCompound* Root(const CppEntity& cppEntity)
{
  if (cppEntity.owner() == nullptr)
    return IsCompound(cppEntity) ? const_cast<CppCompound*>(static_cast<const CppCompound*>(&cppEntity)) : nullptr;
  return Root(*cppEntity.owner());
}

} // namespace cppast

#endif /* E1C8E022_9208_4EA2_BF0E_482C7ABD2C72 */
