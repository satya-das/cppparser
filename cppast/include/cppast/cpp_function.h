// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef D6B4396A_776A_46E6_97BD_3EA2B04625F9
#define D6B4396A_776A_46E6_97BD_3EA2B04625F9

#include "cppast/cpp_compound.h"
#include "cppast/cpp_entity.h"
#include "cppast/cpp_expression.h"
#include "cppast/cpp_template_param.h"
#include "cppast/cpp_var_type.h"

#include <functional>
#include <list>

namespace cppast {

class CppExpr;
class CppBlob;

class CppFuncLikeBase : public CppEntity
{
public:
  const std::vector<std::string>& throwSpec() const
  {
    return throwSpec_;
  }
  void throwSpec(std::vector<std::string> _throwSpec)
  {
    throwSpec_ = std::move(_throwSpec);
  }

  const CppCompound* defn() const
  {
    return defn_.get();
  }
  void defn(std::unique_ptr<CppCompound> _defn)
  {
    defn_ = std::move(_defn);
  }

protected:
  CppFuncLikeBase(CppEntityType type)
    : CppEntity(type)
  {
  }

private:
  std::unique_ptr<CppCompound> defn_; // If it is nullptr then this object is just for declaration.
  std::vector<std::string>     throwSpec_;
};

/**
 * @brief Base class of constructor, destructor, and functions.
 */
class CppFunctionBase : public CppFuncLikeBase, public CppTemplatableEntity
{
public:
  const std::string& name() const
  {
    return name_;
  }

  std::uint32_t attr() const
  {
    return attr_;
  }
  void addAttr(std::uint32_t _attr)
  {
    attr_ |= _attr;
  }
  bool hasAttr(std::uint32_t _attr) const
  {
    return ((attr_ & _attr) == _attr);
  }

  const std::string& decor1() const
  {
    return decor1_;
  }
  void decor1(std::string _decor)
  {
    decor1_ = std::move(_decor);
  }

  const std::string& decor2() const
  {
    return decor2_;
  }
  void decor2(std::string _decor)
  {
    decor2_ = std::move(_decor);
  }

protected:
  CppFunctionBase(CppEntityType type, std::string name, std::uint32_t attr)
    : CppFuncLikeBase(type)
    , name_(std::move(name))
    , attr_(attr)
  {
  }

private:
  const std::string name_;
  std::uint32_t     attr_;   // e.g.: const, static, virtual, inline, constexpr, etc.
  std::string       decor1_; // e.g. __declspec(dllexport)
  std::string       decor2_; // e.g. __stdcall
};

class CppFuncCtorBase : public CppFunctionBase
{
public:
  bool hasParams() const
  {
    return !params_.empty();
  }

  bool visitParams(const std::function<bool(const CppEntity& param)>& callback) const
  {
    for (const auto& param : params_)
    {
      if (!callback(*param))
      {
        return false;
      }
    }

    return true;
  }

  void visitAllParams(const std::function<void(const CppEntity& param)>& callback) const
  {
    visitParams([&callback](auto& param) {
      callback(param);
      return true;
    });
  }

protected:
  CppFuncCtorBase(CppEntityType                           type,
                  std::string                             name,
                  std::vector<std::unique_ptr<CppEntity>> params,
                  std::uint32_t                           attr)
    : CppFunctionBase(type, std::move(name), attr)
    , params_(std::move(params))
  {
  }

protected:
  // FIXME: Not all CppEntity objects can be function parameters. Chose a more suitable type.
  const std::vector<std::unique_ptr<CppEntity>> params_;
};

class CppVarType;

class CppFunction : public CppFuncCtorBase
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::FUNCTION;
  }

public:
  CppFunction(std::string                             name,
              std::unique_ptr<CppVarType>             retType,
              std::vector<std::unique_ptr<CppEntity>> params,
              std::uint32_t                           attr)
    : CppFuncCtorBase(EntityType(), std::move(name), std::move(params), attr)
    , retType_(std::move(retType))
  {
  }

public:
  const CppVarType* returnType() const
  {
    return retType_.get();
  }

protected:
  CppFunction(CppEntityType                           type,
              std::string                             name,
              std::unique_ptr<CppVarType>             retType,
              std::vector<std::unique_ptr<CppEntity>> params,
              std::uint32_t                           attr)
    : CppFuncCtorBase(type, std::move(name), std::move(params), attr)
    , retType_(std::move(retType))
  {
  }

private:
  const std::unique_ptr<CppVarType> retType_;
};

class CppLambda : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::LAMBDA;
  }

public:
  CppLambda(std::unique_ptr<CppExpr>                captures,
            std::vector<std::unique_ptr<CppEntity>> params,
            std::unique_ptr<CppCompound>            defn,
            std::unique_ptr<CppVarType>             retType = nullptr);

public:
  const CppExpr* captures() const
  {
    return captures_.get();
  }

  const std::vector<std::unique_ptr<CppEntity>>& params() const
  {
    return params_;
  }

  const CppVarType* returnType() const
  {
    return retType_.get();
  }

  const CppCompound* defn() const
  {
    return defn_.get();
  }

private:
  const std::unique_ptr<CppExpr>                captures_;
  const std::vector<std::unique_ptr<CppEntity>> params_;
  const std::unique_ptr<CppVarType>             retType_;
  const std::unique_ptr<CppCompound>            defn_;
};

/**
 * Function pointer type definition using typedef, e.g. 'typedef void (*funcPtr)(int);'

 * It has all the attributes of a function object and so it is simply derived from CppFunction.
 */
class CppFunctionPointer : public CppFunction
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::FUNCTION_PTR;
  }

public:
  CppFunctionPointer(std::string                             name,
                     std::unique_ptr<CppVarType>             retType,
                     std::vector<std::unique_ptr<CppEntity>> params,
                     std::uint32_t                           attr,
                     std::string                             ownerName = std::string())
    : CppFunction(EntityType(), std::move(name), std::move(retType), std::move(params), attr)
    , ownerName_(std::move(ownerName))
  {
  }

public:
  const std::string& ownerName() const
  {
    return ownerName_;
  }

private:
  const std::string ownerName_;
};

/**
 * Class data member initialization as part of
 * class constructor.
 */
struct CppMemberInit
{
  std::string              memberName;
  std::unique_ptr<CppExpr> memberInitExpr;
};

/**
 * Entire member initialization list.
 *
 * @note only one field is used at a time.
 */
struct CppMemberInits
{
  std::list<CppMemberInit> memInitList;
  /// If not null then the entire member initialization part of constructor is just a blob of code.
  std::unique_ptr<CppBlob> blob;
};

class CppConstructor : public CppFuncCtorBase
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::CONSTRUCTOR;
  }

public:
  CppConstructor(std::string                             name,
                 std::vector<std::unique_ptr<CppEntity>> params,
                 CppMemberInits                          memInitList,
                 std::uint32_t                           attr);
  ~CppConstructor() override;

public:
  bool hasMemberInitList() const
  {
    return !memInits_.memInitList.empty() || memInits_.blob.get();
  }

  void memberInits(CppMemberInits memInits)
  {
    memInits_ = std::move(memInits);
  }

  const CppMemberInits& memberInits() const
  {
    return memInits_;
  }

private:
  CppMemberInits memInits_;
};

class CppDestructor : public CppFunctionBase
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::DESTRUCTOR;
  }

public:
  CppDestructor(std::string name, std::uint32_t attr)
    : CppFunctionBase(EntityType(), name, attr)
  {
  }
};

class CppTypeConverter : public CppFunctionBase
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::TYPE_CONVERTER;
  }

public:
  CppTypeConverter(CppVarType* type, std::string name)
    : CppFunctionBase(EntityType(), std::move(name), 0)
    , targetType_(type)
  {
  }

public:
  const CppVarType* targetType() const
  {
    return targetType_.get();
  }

private:
  const std::unique_ptr<CppVarType> targetType_;
};

} // namespace cppast

#endif /* D6B4396A_776A_46E6_97BD_3EA2B04625F9 */
