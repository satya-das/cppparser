// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C3CE34A1_F1C2_4151_A68B_02D7B83E467E
#define C3CE34A1_F1C2_4151_A68B_02D7B83E467E

#include "cppast/cpp_entity.h"
#include "cppast/cpp_templatable_entity.h"
#include "cppast/cpp_var_decl.h"

namespace CppAst {

/**
 * Class to represent C++ variable definition.
 * A variable can be global, local or member of a class, class, namespace, or union.
 * It can also be a function parameter.
 */
class CppVar : public CppEntity, public CppTemplatableEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::VAR;
  }

public:
  CppVar(CppVarType* varType, CppVarDecl varDecl)
    : CppEntity(EntityType())
    , varType_(varType)
    , varDecl_(std::move(varDecl))
  {
  }

  CppVar(std::unique_ptr<CppVarType> varType, CppVarDecl varDecl)
    : CppEntity(EntityType())
    , varType_(std::move(varType))
    , varDecl_(std::move(varDecl))
  {
  }

  CppVar(CppFunctionPointer* fptr, CppTypeModifier modifier)
    : CppEntity(EntityType())
    , varType_(new CppVarType(fptr, modifier))
    , varDecl_(std::string())
  {
  }

  const CppVarType& varType() const
  {
    return *varType_;
  }
  // TODO: Do we need it?
  void varType(std::unique_ptr<CppVarType> _varType)
  {
    varType_ = std::move(_varType);
  }

  const std::string& name() const
  {
    return varDecl_.name();
  }

  std::uint32_t typeAttr() const
  {
    return varType_->typeAttr();
  }
  void addAttr(std::uint32_t attr)
  {
    varType_->addAttr(attr);
  }

  const CppVarDecl& varDecl() const
  {
    return varDecl_;
  }

  const CppExpr* assignValue() const
  {
    return varDecl_.assignValue();
  }
  AssignType assignType() const
  {
    return varDecl_.assignType();
  }
  void assign(CppExpr* assignVal, AssignType assignType)
  {
    varDecl_.assign(assignVal, assignType);
  }

  const CppExpr* bitField() const
  {
    return varDecl_.bitField();
  }
  void bitField(CppExpr* _bitField)
  {
    varDecl_.bitField(_bitField);
  }

  const CppArraySizes& arraySizes() const
  {
    return varDecl_.arraySizes();
  }
  void addArraySize(CppExpr* arraySize)
  {
    varDecl_.addArraySize(arraySize);
  }

  const std::string& apidecor() const
  {
    return apidecor_;
  }
  void apidecor(std::string _apidecor)
  {
    apidecor_ = std::move(_apidecor);
  }

private:
  std::unique_ptr<CppVarType> varType_;
  CppVarDecl                  varDecl_;
  std::string                 apidecor_; // It holds things like WINAPI, __declspec(dllexport), etc.
};

} // namespace CppAst

#endif /* C3CE34A1_F1C2_4151_A68B_02D7B83E467E */
