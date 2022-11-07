// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef AB11A5E0_FDCE_4B20_B3D4_8B8B91501356
#define AB11A5E0_FDCE_4B20_B3D4_8B8B91501356

#include "cppast/cpp_entity.h"
#include "cppast/cpp_templatable_entity.h"
#include "cppast/cpp_var_list.h"

namespace cppast {

class CppTypedefName : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::TYPEDEF_DECL;
  }

public:
  CppTypedefName(std::unique_ptr<CppVar> var)
    : CppEntity(EntityType())
    , var_(std::move(var))
  {
  }

public:
  const CppVar* var() const
  {
    return var_.get();
  }

private:
  const std::unique_ptr<CppVar> var_;
};

class CppTypedefList : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::TYPEDEF_DECL_LIST;
  }

public:
  CppTypedefList(std::unique_ptr<CppVarList> varList)
    : CppEntity(EntityType())
    , varList_(std::move(varList))
  {
  }

public:
  const CppVarList& varList() const
  {
    return *varList_;
  }

private:
  const std::unique_ptr<CppVarList> varList_;
};

class CppUsingDecl : public CppEntity, public CppTemplatableEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::USING_DECL;
  }

public:
  CppUsingDecl(std::string name, std::unique_ptr<CppVarType> varType)
    : CppEntity(EntityType())
    , name_(std::move(name))
    , cppEntity_(std::move(varType))
  {
  }

  CppUsingDecl(std::string name, std::unique_ptr<CppFunctionPointer> fptr)
    : CppEntity(EntityType())
    , name_(std::move(name))
    , cppEntity_(std::move(fptr))
  {
  }

  CppUsingDecl(std::string name, std::unique_ptr<CppCompound> compound)
    : CppEntity(EntityType())
    , name_(std::move(name))
    , cppEntity_(std::move(compound))
  {
  }

  CppUsingDecl(std::string name)
    : CppEntity(EntityType())
    , name_(std::move(name))
  {
  }

public:
  const std::string& name() const
  {
    return name_;
  }

  const CppEntity* definition() const
  {
    return cppEntity_.get();
  }

private:
  const std::string                name_;
  const std::unique_ptr<CppEntity> cppEntity_;
};

} // namespace cppast

#endif /* AB11A5E0_FDCE_4B20_B3D4_8B8B91501356 */
