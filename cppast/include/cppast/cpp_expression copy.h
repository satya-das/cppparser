// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E47B8BEB_F06F_4220_B0F3_383195EA0E24
#define E47B8BEB_F06F_4220_B0F3_383195EA0E24

#include "cppast/cpp_entity.h"
#include "cppast/cpp_operator.h"
#include "cppast/cpp_var_type.h"

// TODO: Remodel C++ expressions and improve this file.

namespace cppast {

class CppExpr;
class CppLambda;
class CppVarType;

/**
 * An individual expression.
 */
class CppExprAtom
{
public:
  union
  {
    std::string* atom;
    CppExpr*     expr;
    CppLambda*   lambda;
    CppVarType*  varType; //!< For type cast, and sizeof expression.
  };

  enum
  {
    kInvalid,
    kAtom,
    kExpr,
    kLambda,
    VAR_TYPE
  } type;

  bool isExpr() const
  {
    return (type & kExpr) == kExpr;
  }

  bool isValid() const
  {
    return (type != kInvalid) && (expr != nullptr);
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
  CppExprAtom(CppLambda* l)
    : lambda(l)
    , type(kLambda)
  {
  }
  CppExprAtom(CppVarType* vType)
    : varType(vType)
    , type(VAR_TYPE)
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
  void destroy() const;
};

/**
 * @brief An expression in a C/C++ program.
 *
 * In C/C++ an expression is a complicated beast that needs to be tamed to parse it correctly.
 * An expression can be as simple as a word, e.g. x, 5 are valid expressions.
 * It can be a function call.
 * It can be an initialization list for an array or class. e.g. POINT pt = {100, 500};
 *
 * }
 * It can be a list of expressions used to call a function e.g. gcd(36, 42);
 * new/delete statements are also expressions.
 * It can be any of the arithmetic expression, e.g. a+b.
 * To make things simple we treat a return statement as an expression.
 *
 * structs CppExprAtom, and CppExpr are required to tame this difficult beast called expression in C/C++.
 */
class CppExpr : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::EXPRESSION;
  }

public:
  enum Flag
  {
    kReturn = 0x01,
    kNew    = 0x02,
    // kNewArray		= 0x04, // This is not needed.
    kDelete       = 0x08,
    kDeleteArray  = 0x10,
    kBracketed    = 0x20,
    kInitializer  = 0x40,
    kThrow        = 0x80,
    kSizeOf       = 0x100,
    kVariadicPack = 0x200,
    kGoto         = 0x400,
  };

  const CppExprAtom expr1_ {(CppExpr*) (nullptr)};

  const CppExprAtom expr2_ {(CppExpr*) (nullptr)};
  const CppExprAtom expr3_ {(CppExpr*) (nullptr)};
  const CppOperator oper_;
  short             flags_; // ORed combination of Flag constants.

  CppExpr(CppExprAtom e1, CppOperator op, CppExprAtom e2 = CppExprAtom())
    : CppExpr(e1, op, e2, 0)
  {
  }

  CppExpr(CppExprAtom e1, short flags)
    : CppExpr(e1, kNone, CppExprAtom(), flags)
  {
  }

  // CppExpr(CppExprAtom e1, CppOperator op, short flags)
  //   : CppExpr(e1, op, CppExprAtom(), flags)
  // {
  // }

  CppExpr(CppExprAtom e1, CppOperator op, CppExprAtom e2, short flags)
    : CppEntity(EntityType())
    , expr1_(e1)
    , expr2_(e2)
    , oper_(op)
    , flags_(flags)
  {
  }

  CppExpr(CppExprAtom e1, CppExprAtom e2, CppExprAtom e3)
    : CppEntity(EntityType())
    , expr1_(e1)
    , expr2_(e2)
    , expr3_(e3)
    , oper_(kTertiaryOperator)
    , flags_(0)
  {
  }

  explicit CppExpr(std::string name)
    : CppExpr(CppExprAtom(std::move(name)), CppOperator::kNone)
  {
  }

  explicit CppExpr(CppLambda* l)
    : CppEntity(EntityType())
    , expr1_(l)
    , oper_(kNone)
    , flags_(0)
  {
  }

  ~CppExpr() override
  {
    expr1_.destroy();
    expr2_.destroy();
    expr3_.destroy();
  }
};

bool operator==(const CppExpr& expr1, const CppExpr& expr2);

inline bool operator!=(const CppExpr& expr1, const CppExpr& expr2)
{
  return !(expr1 == expr2);
}

} // namespace cppast

#endif /* E47B8BEB_F06F_4220_B0F3_383195EA0E24 */
