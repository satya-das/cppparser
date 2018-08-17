/*
The MIT License (MIT)

Copyright (c) 2014

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/***************************************************************************************/


/**
 * @file Defines classes to represent C++ DOM objects, like expression, variable definition, class definition, etc.
 * The design principle is that the classes will have struct like syntax, i.e. mostly public members.
 * It is done for simplicity and no complex polymorphism is used.
 */

#ifndef __CPPPARSER_CPPDOM_H__
#define __CPPPARSER_CPPDOM_H__

#include "cppconst.h"

#include <boost/optional.hpp>

#include <cstdint>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

//////////////////////////////////////////////////////////////////////////

struct CppCompound;

/**
 * An abstract class that is used as base class of all other classes.
 */
struct CppObj
{
  enum Type : std::uint32_t
  {
    kUnknown			= 0x0000,
    kDocComment,

    kCPreProcessorTypeStarts,   // Any preprocessor type must come after this
    kHashIf,	                  // #if, #ifdef, #ifndef, #else, #elif.
    kHashInclude,		            // #include
    kHashDefine,		            // #define
    kHashUndef,			            // #undef
    kHashPragma,		            // #pragma
    kHashError,
    kUnRecogPrePro,		          // Any unrecognized pre-processor.
    kCPreProcessorTypeEnds,

    kCppStatementObjectTypeStarts,
    kVarType,			              // Just the type of variable.
    kVar,				                // A variable declaration.
    kVarList,			              // List of variables declared as comma separated identifiers.
    kTypedefName,
    kTypedefNameList,
    kUsingNamespaceDecl,
    kUsing,
    kEnum,
    kCompound,			            // file, namespace, class, struct, union, block.
    kFwdClsDecl,		            // Forward declaration of compound type.
    kFunction,
    kConstructor,
    kDestructor,
    kTypeConverter,
    kFunctionPtr,		            // Function proc declaration using typedef. e.g. typedef void (*fp) (void);
    kExpression,		            // A C++ expression
    kExpressionList,
    kFuncCall,			            // A function call expression
    kMacroCall,
    kBlob,				              // Some unparsed/unrecognized part of C++ source code.
    kCppStatementObjectTypeEnds,

    kCppControlStatementStarts,
    kIfBlock,
    kForBlock,
    kWhileBlock,
    kDoWhileBlock,
    kSwitchBlock,
    kCppControlStatementEnds,
  };

  const Type      objType_;
  CppCompound*    owner_;
  CppObjProtLevel prot_;	///< All objects do not need this but for simplicity we will have this in all objects.

  CppObj(Type type, CppObjProtLevel prot)
    : objType_	(type)
    , owner_	(nullptr)
    , prot_		(prot)
  {
  }

  virtual ~CppObj() {}

  /// @return true if object is a function-like type.
  bool isFunctionLike() const
  {
    return objType_ == kFunction || objType_ == kConstructor || objType_ == kDestructor;
  }
  bool isClassLike() const;
  bool isNamespaceLike() const;
  bool isPreProcessorType() const
  {
    return objType_ > kCPreProcessorTypeStarts && objType_ < kCPreProcessorTypeEnds;
  }
};

struct CppExpr;

typedef std::vector<CppObj*> CppObjArray;

struct CppDefine : public CppObj
{
  enum DefType
  {
    kRename,
    kConstNumDef,
    kConstStrDef,
    kConstCharDef,
    kComplexMacro,
  };
  DefType		defType_;
  std::string	name_;
  std::string	defn_; ///< This will contain everything after name.

  CppDefine(std::string name, std::string defn = std::string())
    : CppObj	(kHashDefine, kUnknownProt)
    , name_		(std::move(name))
    , defn_		(std::move(defn))
  {
  }
};

struct CppUndef : public CppObj
{
  std::string	name_;

  CppUndef(std::string name)
    : CppObj	(kHashUndef, kUnknownProt)
    , name_		(std::move(name))
  {
  }
};

struct CppInclude : public CppObj
{
  std::string	name_;

  CppInclude(std::string name)
    : CppObj	(kHashInclude, kUnknownProt)
    , name_		(std::move(name))
  {
  }
};

/**
 * \brief Represents all variants of #if preprocessors.
 * It includes #if, #ifdef, #ifndef.
 * It also includes #else, #elif, and #endif.
 */
struct CppHashIf : public CppObj
{
  enum CondType
  {
    kIf, kElse, kIfDef, kIfNDef, kElIf, kEndIf
  };

  CondType	condType_;
  std::string	cond_;

  CppHashIf(CondType condType, std::string cond = std::string())
    : CppObj	(kHashIf, kUnknownProt)
    , condType_	(condType)
    , cond_		(std::move(cond))
  {
  }
};

struct CppPragma : public CppObj
{
  std::string defn_;

  CppPragma(std::string defn)
    : CppObj(CppObj::kHashPragma, kUnknownProt)
    , defn_(std::move(defn))
  {
  }
};

struct CppHashError : public CppObj
{
  std::string err_;

  CppHashError(std::string err)
    : CppObj(CppObj::kHashError, kUnknownProt)
    , err_(std::move(err))
    {
    }
};

/**
 * Any other C/C++ preprocessor for which there is no class defined.
 */
struct CppUnRecogPrePro : public CppObj
{
  std::string name_;
  std::string	defn_;

  CppUnRecogPrePro(std::string name, std::string defn)
    : CppObj(CppObj::kUnRecogPrePro, kUnknownProt)
    , name_	(std::move(name))
    , defn_	(std::move(defn))
  {
  }
};

struct CppExpr;

struct CppTypeModifier
{
  CppRefType		refType_;
  std::uint8_t  ptrLevel_; // Pointer level. e.g. int** ppi has pointer level of 2.
  // Stores bits as per location of const in a var definition.
  // Below table clarifies the value of const-bits:
  // --------------------------------------------------
  // | DEFINITION                             | VALUE |
  // | ------------------------------------------------
  // | int const * pi                         | 0b100 |
  // | int const i                            | 0b100 |
  // | int * const pi                         | 0b100 |
  // | int * const * const ppi                | 0b110 |
  // | int **const ppi                        | 0b001 |
  // | int const * const * const ppi          | 0b111 |
  // | ------------------------------------------------
  //
  // It is 8 bit unsigned integer which is enough to store info for pointers of 8 level deep.
  std::uint8_t  constBits_;
};

inline CppTypeModifier  makeCppTypeModifier(CppRefType refType, std::uint8_t ptrLevel, std::uint8_t constBits)
{
  return CppTypeModifier{refType, ptrLevel, constBits};
}

struct CppVarType : public CppObj
{
  std::string		  baseType_; // This is the basic data type of var e.g. for 'const int*& pi' base-type is int.
  std::uint32_t	  typeAttr_; // Attribute associated with type, e.g. static, extern, extern "C", const, volatile.
  CppTypeModifier typeModifier_;

  CppVarType(std::string baseType, CppTypeModifier modifier = CppTypeModifier())
    : CppVarType(kUnknownProt, baseType, modifier)
  {
  }

  CppVarType(CppObjProtLevel prot, std::string baseType, CppTypeModifier modifier)
    : CppVarType(CppObj::kVarType, prot, baseType, 0, modifier)
  {
  }

  bool isVoid() const
  {
    if (typeAttr_ != 0 || typeModifier_.ptrLevel_ != 0 || typeModifier_.refType_ != kNoRef)
      return false;
    return (baseType_.compare("void") == 0);
  }

  bool isByRef() const
  {
    return (typeAttr_ & kByRef) == kByRef;
  }

  bool isByRValueRef() const
  {
    return (typeAttr_ & kRValRef) == kRValRef;
  }

  bool isConst() const
  {
    return (typeAttr_ & kConst) == kConst;
  }

  bool isByValue() const
  {
    return (typeModifier_.refType_ == kNoRef) && (typeModifier_.ptrLevel_ == 0);
  }

protected:
  CppVarType(CppObj::Type type, CppObjProtLevel prot, std::string baseType, std::uint32_t typeAttr, CppTypeModifier modifier)
    : CppObj(type, prot)
    , typeModifier_(modifier)
    , baseType_(std::move(baseType))
    , typeAttr_(typeAttr)
  {
  }
};

struct CppExpr;
using CppExprPtr = std::unique_ptr<CppExpr>;
using CppArraySizes = std::vector<CppExprPtr>;
using CppObjPtr = std::unique_ptr<CppObj>;

struct CppVarDecl
{
  std::string		name_;
  CppObjPtr     assign_;    // Value assigned at declaration.
  CppExprPtr    bitField_;
  CppArraySizes arraySizes_;

  CppVarDecl(std::string name)
    : name_(std::move(name))
  {
  }

  CppVarDecl(std::string name, CppExpr* assign);
};

/**
 * Class to represent C++ variable definition.
 * A variable can be global, local or member of a struct, class, namespace, or union.
 * It can also be a function parameter.
 */
struct CppVar : public CppObj
{
  union {
    CppVarType* varType_ {nullptr};
    CppCompound* compound_;
  };
  CppVarDecl  varDecl_;
  std::string	apidecor_;  // It holds things like WINAPI, __declspec(dllexport), etc.

  CppVar(CppVarType* varType, CppVarDecl varDecl)
    : CppVar(CppObj::kVar, varType, std::move(varDecl))
  {
  }

  CppVar(CppCompound* compound, CppVarDecl varDecl);

protected:
  CppVar(CppObj::Type objType, CppVarType* varType, CppVarDecl varDecl)
    : CppObj(objType, varType->prot_)
    , varType_(varType)
    , varDecl_(std::move(varDecl))
  {
  }
};

struct CppVarDeclInList : public CppTypeModifier, public CppVarDecl
{
  CppVarDeclInList(CppTypeModifier modifier, CppVarDecl varDecl)
    : CppTypeModifier(modifier)
    , CppVarDecl(std::move(varDecl))
  {
  }
};

using CppVarDeclList = std::vector<CppVarDeclInList>;

/**
 * \brief List of variables declared in a line without repeating its type, e.g. int i, j; is a var-list.
 */
struct CppVarList : public CppObj
{
  std::string		  baseType_; // This is the basic data type of var e.g. for 'const int*& pi' base-type is int.
  std::uint32_t	  typeAttr_ {0}; // Attribute associated with type, e.g. static, extern, extern "C", const, volatile.
  CppVarDeclList  varDeclList_;

  CppVarList(std::string baseType, CppObjProtLevel prot = kUnknownProt)
    : CppVarList(CppObj::kVarList, std::move(baseType), prot)
  {
  }

  void addVarDecl(CppVarDeclInList varDecl)
  {
    varDeclList_.push_back(std::move(varDecl));
  }

protected:
  CppVarList(CppObj::Type objType, std::string baseType, CppObjProtLevel prot = kUnknownProt)
    : CppObj(objType, prot)
    , baseType_(std::move(baseType))
  {
  }
};

struct CppTypedefName : public CppObj
{
  CppVar* const var_;

  CppTypedefName(CppVar* var)
    : CppObj(CppObj::kTypedefName, var->prot_)
    , var_(var)
  {
  }
};

struct CppTypedefList : public CppObj
{
  CppVarList* const varList_;

  CppTypedefList(CppVarList* varList)
    : CppObj(CppObj::kTypedefNameList, varList->prot_)
    , varList_(varList)
  {
  }
};

struct CppMacroCall : CppObj
{
  std::string macroCall_;

  CppMacroCall(std::string macroCall)
    : CppObj(CppObj::kMacroCall, kUnknownProt)
    , macroCall_(std::move(macroCall))
  {
  }
};

//////////////////////////////////////////////////////////////////////////

struct CppEnumItem
{
  union
  {
    CppExpr* val_;
    CppObj* anyItem_;
  };
  std::string name_;

  CppEnumItem(std::string name, CppExpr* val=nullptr)
    : name_(std::move(name))
    , val_(val)
  {
  }

  CppEnumItem(CppObj* anyItem)
    : anyItem_(anyItem)
  {
  }
};

typedef std::list<CppEnumItem*> CppEnumItemList;
struct CppEnum : public CppObj
{
  std::string			  name_;      // Can be empty for anonymous enum.
  CppEnumItemList*	itemList_;  // Can be nullptr for forward declared enum.
  bool              isClass_;
  std::string       underlyingType_;

  CppEnum(CppObjProtLevel prot, std::string name, CppEnumItemList* itemList, bool isClass = false, std::string underlyingType = std::string())
    : CppObj          (kEnum, prot)
    , name_           (std::move(name))
    , itemList_       (itemList)
    , isClass_        (isClass)
    , underlyingType_ (std::move(underlyingType))
  {
  }
};

//////////////////////////////////////////////////////////////////////////

struct CppFwdClsDecl : public CppObj
{
  CppCompoundType cmpType_;
  std::string		name_;
  std::uint32_t attr_ {0};

  CppFwdClsDecl(CppObjProtLevel prot, std::string name, CppCompoundType cmpType = kNoCompound)
    : CppObj	(CppObj::kFwdClsDecl, prot)
    , cmpType_(cmpType)
    , name_		(std::move(name))
    , attr_   (0)
  {
  }
};

struct CppInheritInfo
{
  std::string baseName;
  CppObjProtLevel inhType;

  CppInheritInfo(std::string _baseName, CppObjProtLevel _inhType)
    : baseName(std::move(_baseName))
    , inhType(_inhType)
  {
  }
};

struct CppParamList;
using CppTemplateParamList = CppParamList;

typedef std::list<CppInheritInfo> CppInheritanceList;

/**
 * All classes, structs, unions, and namespaces can be classified as a Compound object.
 * An entire C/C++ source file too is a compound object. A block of statements inside { } is also a compound object.
 */
struct CppCompound : public CppObj
{
private:
  mutable boost::optional<bool> hasVirtual_;
  mutable boost::optional<bool> isAbstract_;

public:
  std::string			name_;
  CppObjArray			members_;	// Objects arranged in sequential order from top to bottom.
  CppCompoundType		compoundType_;
  CppInheritanceList*	inheritList_;
  std::string			apidecor_;
  CppTemplateParamList* templSpec_ {nullptr};

  CppCompound(std::string name, CppObjProtLevel prot, CppCompoundType type)
    : CppObj(CppObj::kCompound, prot)
    , compoundType_(type)
    , name_(std::move(name))
    , inheritList_(nullptr)
  {
  }

  CppCompound(CppObjProtLevel prot, CppCompoundType type = kUnknownCompound)
    : CppCompound(std::string(), prot, type)
  {
  }

  CppCompound(std::string name, CppCompoundType type)
    : CppCompound(name, kUnknownProt, type)
  {
  }

  CppCompound(CppCompoundType type)
    : CppCompound(std::string(), type)
  {
  }

  ~CppCompound() override
  {
    delete inheritList_;
    for (CppObjArray::iterator itr = members_.begin(); itr != members_.end(); ++itr)
      delete *itr;
  }

  void setCompoundType(CppCompoundType compoundType)
  {
    if (compoundType_ == kUnknownCompound)
      compoundType_ = compoundType;
  }
  bool traverse(std::function<bool(const CppObj*)> visitor) const {
    for (auto mem : members_) {
      if (mem->isNamespaceLike() && static_cast<const CppCompound*>(mem)->traverse(visitor))
        return true;
      if (visitor(mem))
        return true;
    }
    return false;
  }
  bool traversePreorder(std::function<bool(const CppObj*)> visitor) const {
    for (auto mem : members_) {
      if (visitor(mem))
        return true;
      if (mem->isNamespaceLike() && static_cast<const CppCompound*>(mem)->traversePreorder(visitor))
        return true;
    }
    return false;
  }
  bool isNamespace() const
  {
    return compoundType_ == kNamespace;
  }
  bool isClass	() const
  {
    return compoundType_ == kClass;
  }
  bool isStruct	() const
  {
    return compoundType_ == kStruct;
  }
  bool isUnion	() const
  {
    return compoundType_ == kUnion;
  }
  bool isCppFile	() const
  {
    return compoundType_	== kCppFile;
  }
  bool isBlock	() const
  {
    return compoundType_ == kBlock;
  }

  bool isClassLike() const
  {
    return (compoundType_&kClass) == kClass;
  }
  bool isNamespaceLike() const
  {
    return (compoundType_&kNamespace) == kNamespace;
  }
  /// @return full name of this class.
  std::string fullName() const
  {
    if (!isNamespaceLike())
      return name_;
    if (owner_ && owner_->isNamespaceLike())
      return owner_->fullName() + "::" + name_;
    else
      return name_;
  }

  void addMember	(CppObj* mem)
  {
    members_.push_back(mem);
  }
  CppObjProtLevel defaultProtLevel() const
  {
    return isClass() ? kPrivate : kPublic;
  }
  void addBaseClass(std::string baseName, CppObjProtLevel inheritType)
  {
    if (inheritList_ == nullptr)
      inheritList_ = new CppInheritanceList;
    inheritList_->push_back(CppInheritInfo(baseName, inheritType));
  }
  bool hasVirtualMethod() const;
  bool isAbstract() const;
};

struct CppFunctionPtr;

/**
 * At some place either a var-type or function pointer is expected
 * For example typedef and function parameter.
 */
union CppVarOrFuncPtrType
{
  CppObj*			cppObj; ///< This should be used just for type checking.
  CppVar*			varObj;
  CppFunctionPtr*	funcPtr;
  CppObj* operator = (CppObj* rhs)
  {
    cppObj = rhs;
    return cppObj;
  }

};

inline bool operator == (const CppVarOrFuncPtrType& lhs, const CppVarOrFuncPtrType& rhs)
{
  return lhs.cppObj == rhs.cppObj;
}

inline bool operator != (const CppVarOrFuncPtrType& lhs, const CppVarOrFuncPtrType& rhs)
{
  return lhs.cppObj != rhs.cppObj;
}

/**
 * A function parameter object.
 */
typedef CppVarOrFuncPtrType	CppParam;

struct CppParamList : private std::list<CppParam>
{
  typedef std::list<CppParam> BaseType;
  using BaseType::iterator;
  using BaseType::const_iterator;
  using BaseType::BaseType;
  using BaseType::push_back;
  using BaseType::size;
  using BaseType::front;
  using BaseType::empty;
  using BaseType::begin;
  using BaseType::end;

  ~CppParamList()
  {
    for (iterator itr = begin(); itr != end(); ++itr)
      delete itr->cppObj;
  }
};

using CppIdentifierList = std::vector<std::string>;
using CppFuncThrowSpec = CppIdentifierList;

/**
 * \brief Base class of constructor, destructor, and functions.
 */
struct CppFunctionBase : public CppObj
{
  std::string		name_;
  std::uint32_t	attr_; // e.g.: const, static, virtual, inline, constexpr, etc.
  CppCompound*	defn_; // If it is nullptr then this object is just for declaration.
  std::string		docer1_; // e.g. __declspec(dllexport)
  std::string		docer2_; // e.g. __stdcall
  CppTemplateParamList* templSpec_ {nullptr};
  CppFuncThrowSpec* throwSpec_ {nullptr};

  bool isConst() const
  {
    return (attr_ & kConst) == kConst;
  }
  bool isVirtual() const
  {
    return (attr_ & kVirtual) == kVirtual;
  }
  bool isPureVirtual() const
  {
    return (attr_ & kPureVirtual) == kPureVirtual;
  }
  bool isStatic() const
  {
    return (attr_ & kStatic) == kStatic;
  }
  bool isInline() const
  {
    return (attr_ & kInline) == kInline;
  }
  bool isOverride() const
  {
    return (attr_ & kOverride) == kOverride;
  }

protected:
  CppFunctionBase(CppObj::Type type, CppObjProtLevel prot, std::string name, std::uint32_t attr)
    : CppObj(type, prot)
    , name_(std::move(name))
    , attr_(attr)
    , defn_(nullptr)
  {
  }

  ~CppFunctionBase() override
  {
    delete defn_;
  }
};

struct CppFuncCtorBase : public CppFunctionBase
{
  CppParamList*	params_;

  bool hasParams() const
  {
    return params_ && !params_->empty();
  }

protected:
  CppFuncCtorBase(CppObj::Type type, CppObjProtLevel prot, std::string name, CppParamList* params, std::uint32_t attr)
    : CppFunctionBase(type, prot, std::move(name), attr)
    , params_(params)
  {
  }
  ~CppFuncCtorBase() override
  {
    delete params_;
  }
};

struct CppFunction : public CppFuncCtorBase
{
  CppVarType*		retType_;

  CppFunction(CppObjProtLevel prot, std::string name, CppVarType* retType, CppParamList* params, std::uint32_t attr)
    : CppFuncCtorBase(CppObj::kFunction, prot, std::move(name), params, attr)
    , retType_(retType)
  {}

  ~CppFunction() override
  {
    delete retType_;
  }
  bool isMethod() const
  {
    return owner_ && owner_->isClassLike();
  }

protected:
  CppFunction(CppObj::Type type, CppObjProtLevel prot, std::string name, CppVarType* retType, CppParamList* params, std::uint32_t attr)
    : CppFuncCtorBase(type, prot, std::move(name), params, attr)
    , retType_(retType)
  {}
};

/**
 * Function pointer type definition using typedef, e.g. 'typedef void (*funcPtr)(int);'

 * It has all the attributes of a function object and so it is simply derived from CppFunction.
 */
struct CppFunctionPtr : public CppFunction
{
  std::string   ownerName_;
  std::uint8_t  ptrLevel_ {0};

  CppFunctionPtr(CppObjProtLevel prot, std::string name, CppVarType* retType, CppParamList* args, std::uint32_t attr)
    : CppFunction(CppObj::kFunctionPtr, prot, std::move(name), retType, args, attr)
  {
  }
};

struct CppExprList;
/**
 * Class data member initialization as part of class constructor.
 */
typedef std::pair<std::string, CppExprList*>	CppMemInit;
/**
 * Entire member initialization list.
 */
typedef std::list<CppMemInit>				CppMemInitList;

struct CppConstructor : public CppFuncCtorBase
{
  CppMemInitList* memInitList_;

  CppConstructor(CppObjProtLevel prot, std::string name, CppParamList* params, CppMemInitList* memInitList, std::uint32_t attr)
    : CppFuncCtorBase(kConstructor, prot, name, params, attr)
    , memInitList_(nullptr)
  {
  }

  ~CppConstructor() override
  {
    delete memInitList_;
  }

  bool isCopyConstructor() const;
  bool isMoveConstructor() const;

private:
  mutable boost::optional<bool> isCopyConstructor_;
  mutable boost::optional<bool> isMoveConstructor_;
};

struct CppDestructor : public CppFunctionBase
{
  CppDestructor(CppObjProtLevel prot, std::string name, std::uint32_t attr)
    : CppFunctionBase(CppObj::kDestructor, prot, name, attr)
  {
  }
};

struct CppTypeCoverter : CppObj
{
  std::string name_; // Name may be empty if defined inside class definition.
  CppVarType* to_ {nullptr};
  CppCompound* defn_ {nullptr};
  std::uint32_t attr_ {0};
  std::string apidecor_;
  CppTemplateParamList* templSpec_ {nullptr};

  CppTypeCoverter(CppVarType* type, std::string name)
    : CppObj(CppObj::kTypeConverter, type->prot_)
    , name_(std::move(name))
    , to_(type)
  {}
};

struct CppUsingNamespaceDecl : public CppObj
{
  std::string name_;

  CppUsingNamespaceDecl(std::string name)
    : CppObj(CppObj::kUsingNamespaceDecl, kUnknownProt)
    , name_(std::move(name))
  {
  }
};

struct CppUsingDecl : public CppObj
{
  std::string name_;
  union {
    CppVarType*       varType_;
    CppFunctionPtr*   fptr_;
    CppCompound*      compound_;
  };

  CppUsingDecl(std::string name, CppVarType* varType)
    : CppObj(CppObj::kUsing, kUnknownProt)
    , name_(std::move(name))
    , varType_(varType)
  {
  }

  CppUsingDecl(std::string name, CppFunctionPtr* fptr)
    : CppObj(CppObj::kUsing, kUnknownProt)
    , name_(std::move(name))
    , fptr_(fptr)
  {
  }

  CppUsingDecl(std::string name, CppCompound* compound)
    : CppObj(CppObj::kUsing, kUnknownProt)
    , name_(std::move(name))
    , compound_(compound)
  {
  }
};

struct CppDocComment : public CppObj
{
  std::string	doc_; ///< Entire comment text

  CppDocComment(std::string doc, CppObjProtLevel protLevel = kUnknownProt)
    : CppObj(CppObj::kDocComment, protLevel)
    , doc_(std::move(doc))
  {
  }
};

struct CppExprAtom;
struct CppExpr;
/**
 * \brief Represents a list of expressions.
 *
 * It is mainly used for:
 * - function call, in that case the expression list is enclosed inside ().
 * - and array/struct initialization, in such case expression list is enclosed inside {}.
 * \see CppExpr.
 */
struct CppExprList : public CppObj, private std::list<CppExpr*>
{
  typedef std::list<CppExpr*> BaseType;
  using BaseType::iterator;
  using BaseType::const_iterator;
  using BaseType::BaseType;
  using BaseType::push_back;
  using BaseType::size;
  using BaseType::front;
  using BaseType::empty;
  using BaseType::begin;
  using BaseType::end;

  CppExprList()
    : CppObj(CppObj::kExpressionList, kUnknownProt)
    {}
  CppExprList(const CppExprAtom& e1);
  CppExprList(const CppExprAtom& e1, const CppExprAtom& e2);
  CppExprList(const CppExprAtom& e1, const CppExprAtom& e2, const CppExprAtom& e3);

  void push(const CppExprAtom& e);

  ~CppExprList(); // Need this to delete list items
};

struct CppExpr;
/**
 * An individual expression.
 */
struct  CppExprAtom
{
  enum
  {
    kInvalid, kAtom, kExpr, kExprList, kVarType
  }	type;
  union
  {
    std::string*		atom;
    CppExpr*			  expr;
    CppExprList*		list;
    CppVarType*     varType; //!< For type cast expression.
  };

  bool isExpr() const
  {
    return (type&kExpr) == kExpr;
  }

  CppExprAtom(const char* sz, size_t l)
    : atom(new std::string(sz, l))
    , type(kAtom)
  {
  }
  CppExprAtom(const char* sz)
    : atom(new std::string(sz))
    , type(kAtom)
  {
  }
  CppExprAtom(std::string tok)
    : atom(new std::string(std::move(tok)))
    , type(kAtom)
  {
  }
  CppExprAtom(CppExpr* e)
    : expr(e)
    , type(kExpr)
  {
  }
  CppExprAtom(CppExprList* l)
    : list(l)
    , type(kExprList)
  {
  }
  CppExprAtom(CppVarType* vType)
    : varType(vType)
    , type(kVarType)
  {
  }
  CppExprAtom()
    : atom(nullptr)
    , type(kInvalid)
  {
  }
  /**
   * It is expected to be called explicitly to destroy an CppExprAtom object.
   */
  void destroy();
};

/**
 * \brief An expression in a C/C++ program.
 *
 * In C/C++ an expression is a complicated beast that needs to be tamed to parse it correctly.
 * An expression can be as simple as a word, e.g. x, 5 are valid expressions.
 * It can be a function call.
 * It can be an initialization list for an array or struct. e.g. POINT pt = {100, 500};
 * It can be a list of expressions used to call a function e.g. gcd(36, 42);
 * new/delete statements are also expressions.
 * It can be any of the arithmetic expression, e.g. a+b.
 * To make things simple we treat a return statement as an expression.
 *
 * structs CppExprAtom, CppExpr, and CppExprList are required to tame this difficult beast called expression in C/C++.
 */
struct CppExpr : public CppObj
{
  enum Flag
  {
    kReturn			= 0x01,
    kNew			= 0x02,
    //kNewArray		= 0x04, // This is not needed.
    kDelete			= 0x08,
    kDeleteArray	= 0x10,
    kBracketed		= 0x20,
    kInitializer	= 0x40,
    kThrow        = 0x80,
  };
  CppExprAtom expr1_ {(CppExpr*)(nullptr)};
  CppExprAtom expr2_ {(CppExpr*)(nullptr)};
  CppExprAtom expr3_ {(CppExpr*)(nullptr)};
  CppOperType oper_;
  short		flags_; // ORed combination of Flag constants.

  CppExpr(CppExprAtom e1, CppOperType op, CppExprAtom e2 = CppExprAtom())
    : CppExpr(e1, op, e2, 0)
  {}

  CppExpr(CppExprAtom e1, short flags)
    : CppExpr(e1, kNone, CppExprAtom(), flags)
  {}

  CppExpr(CppExprAtom e1, CppOperType op, CppExprAtom e2, short flags)
    : CppObj(CppObj::kExpression, kUnknownProt)
    , expr1_(e1)
    , oper_(op)
    , expr2_(e2)
    , flags_(flags)
  {
  }

  CppExpr(CppExprAtom e1, CppExprAtom e2, CppExprAtom e3)
    : CppObj(CppObj::kExpression, kUnknownProt)
    , expr1_(e1)
    , expr2_(e2)
    , expr3_(e3)
    , oper_(kTertiaryOperator)
    , flags_(0)
  {
  }

  ~CppExpr() override
  {
    expr1_.destroy();
    expr2_.destroy();
  }
};

/// Some blocks have common structure like if, while, and do-while.
/// They all contain a body and an expression of condition.
template <CppObj::Type type>
struct CppCommonBlock : public CppObj
{
  CppCommonBlock(CppExpr* cond)
    : CppObj(type, kUnknownProt)
    , cond_(cond)
    , body_(nullptr)
  {
  }

  CppExpr* cond_;
  CppObj* body_;
};

struct CppIfBlock : public CppCommonBlock<CppObj::kIfBlock>
{
  CppObj* else_{nullptr};

  CppIfBlock(CppExpr* cond)
    : CppCommonBlock(cond)
    , else_ {nullptr}
  {
  }
};

using CppWhileBlock = CppCommonBlock<CppObj::kWhileBlock>;

using CppDoWhileBlock = CppCommonBlock<CppObj::kDoWhileBlock>;

struct CppForBlock : public CppObj
{
  CppForBlock(CppObj* start, CppExpr* stop, CppExpr* step, CppObj* body)
    : CppObj(kForBlock, kUnknownProt)
    , startObj_(start)
    , stop_(stop)
    , step_(step)
    , body_(body)
  {
  }

  union {
    CppObj*  startObj_ {nullptr};
    CppExpr* startExpr_;
    CppVar*  startVar_;
  };
  CppExpr* stop_ {nullptr};
  CppExpr* step_ {nullptr};
  CppObj*  body_ {nullptr};
};

struct CppCase
{
  CppCase(CppExpr* cond, CppCompound* body)
    : case_(cond)
    , body_(body)
  {
  }

  CppExpr*      case_ {nullptr};
  CppCompound*  body_ {nullptr};
};

using CppSwitchBody = std::vector<CppCase>;

struct CppSwitchBlock : public CppObj
{
  CppExpr*       cond_ {nullptr};
  CppSwitchBody* body_ {nullptr};

  CppSwitchBlock(CppExpr* cond, CppSwitchBody* body)
    : CppObj(kSwitchBlock, kUnknownProt)
    , cond_ (cond)
    , body_ (body)
  {
  }
};

/**
 * \brief A stream of text that represents some content in a C++ program.

 * It is basically a quick way to create C++ content while generating source programatically.
 */
struct CppBlob : public CppObj
{
  std::string blob_;

  CppBlob(std::string blob)
    : CppObj(CppObj::kBlob, kUnknownProt)
    , blob_(std::move(blob))
  {
  }
};

//////////////////////////////////////////////////////////////////////////

inline bool CppObj::isClassLike() const
{
  return objType_ == kCompound && ((CppCompound*) this)->isClassLike();
}

inline bool CppObj::isNamespaceLike() const
{
  return objType_ == kCompound && ((CppCompound*) this)->isNamespaceLike();
}

inline void CppExprList::push(const CppExprAtom& e)
{
  if (e.isExpr()) push_back(e.expr);
  else push_back(new CppExpr(e, kNone));
}

inline CppExprList::CppExprList(const CppExprAtom& e1)
  : CppObj(CppObj::kExpressionList, kUnknownProt)
{
  push(e1);
}
inline CppExprList::CppExprList(const CppExprAtom& e1, const CppExprAtom& e2)
  : CppObj(CppObj::kExpressionList, kUnknownProt)
{
  push(e1);
  push(e2);
}
inline CppExprList::CppExprList(const CppExprAtom& e1, const CppExprAtom& e2, const CppExprAtom& e3)
  : CppObj(CppObj::kExpressionList, kUnknownProt)
{
  push(e1);
  push(e2);
  push(e3);
}

inline CppExprList::~CppExprList()
{
  for (iterator i = begin(); i != end(); ++i)
    delete *i;
}


inline void CppExprAtom::destroy()
{
  switch (type)
  {
  case CppExprAtom::kAtom:
    delete atom;
    break;
  case CppExprAtom::kExpr:
    delete expr;
    break;
  case CppExprAtom::kExprList:
    delete list;
    break;
  case CppExprAtom::kVarType:
    delete varType;
    break;
  }
}

inline CppVar::CppVar(CppCompound* compound, CppVarDecl varDecl)
    : CppObj(CppObj::kVar, compound->prot_)
    , compound_(compound)
    , varDecl_(std::move(varDecl))
{
}

inline CppVarDecl::CppVarDecl(std::string name, CppExpr* assign)
  : name_(std::move(name))
{
  assign_.reset(assign);
}

#endif //__CPPPARSER_CPPDOM_H__
