#ifndef E7E01B9C_F9F8_41CC_947E_80D6A1262373
#define E7E01B9C_F9F8_41CC_947E_80D6A1262373

#include "cppast/cppast.h"
#include "cpptoken.h"

////////////////////////////////////////////////////////////////////////////////////////////////

struct CppExpr;

/* Non-terminal for member initializer */
struct CppMemberInitBuilder
{
  CppToken         mem;
  cppast::CppExpr* init;
};

////////////////////////////////////////////////////////////////////////////////////////////////

class CppEntity;

struct CppFunctionBuilder
{
  CppToken                                         funcName;
  std::vector<std::unique_ptr<cppast::CppEntity>>* paramList;
  unsigned int                                     funcAttr;
};

////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* E7E01B9C_F9F8_41CC_947E_80D6A1262373 */
