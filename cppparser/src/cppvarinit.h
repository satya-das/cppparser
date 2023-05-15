// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef EF1FCFF7_1437_44C2_B658_F93FD13357A5
#define EF1FCFF7_1437_44C2_B658_F93FD13357A5

#include "cppast/cppast.h"
#include "cppast/cppconst.h"

struct CppVarAssign
{
  cppast::CppExpression* assignValue_; // Value assigned at declaration.
  cppast::AssignType     assignType_;
};

#endif /* EF1FCFF7_1437_44C2_B658_F93FD13357A5 */
