// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C3CE34A1_F1C2_4151_A68B_02D7B83E467E
#define C3CE34A1_F1C2_4151_A68B_02D7B83E467E

#include "cppast/cpp_entity.h"
#include "cppast/cpp_templatable_entity.h"
#include "cppast/cpp_var_decl.h"

namespace cppast {

/**
 * Represents C++ variable definition.
 * A variable can be global, local or member of a class, namespace, or union.
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

  void initialize(CppVarInitInfo initInfo)
  {
    varDecl_.initialize(std::move(initInfo));
  }

  const CppVarType& varType() const
  {
    return *varType_;
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

  bool isInitialized() const
  {
    return varDecl_.isInitialized();
  }

  std::optional<CppVarInitializeType> initializeType() const
  {
    return varDecl_.initializeType();
  }

  /**
   * @brief Gets the value assigned to variable.
   *
   * @return value assigned to variable.
   * @note The returned value can be nullptr.
   */
  const CppExpression* assignValue() const
  {
    return varDecl_.assignValue();
  }

  const CppExpression* bitField() const
  {
    return varDecl_.bitField();
  }
  void bitField(std::unique_ptr<const CppExpression> bitFieldArg)
  {
    varDecl_.bitField(std::move(bitFieldArg));
  }

  const CppArraySizes& arraySizes() const
  {
    return varDecl_.arraySizes();
  }
  void addArraySize(CppExpression* arraySize)
  {
    varDecl_.addArraySize(arraySize);
  }

  const std::string& apidecor() const
  {
    return apidecor_;
  }
  void apidecor(std::string apidecorArg)
  {
    apidecor_ = std::move(apidecorArg);
  }

private:
  std::unique_ptr<CppVarType> varType_;
  CppVarDecl                  varDecl_;
  std::string                 apidecor_; // It holds things like WINAPI, __declspec(dllexport), etc.
};

} // namespace cppast

#endif /* C3CE34A1_F1C2_4151_A68B_02D7B83E467E */
