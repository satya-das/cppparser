// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef FD4A67B1_0F80_450C_810E_38D081BF552B
#define FD4A67B1_0F80_450C_810E_38D081BF552B

#include "cppast/cppast.h"
#include "cppconst.h"

#include <cstdint>

// TODO: Get rid of this file.

/*!
 * @brief Factory class to create various CppEntity instances.
 *
 * Ideally this factory class should be used to create any CppEntity object so that clients of CppParser can supply its
 * own type. At present creation of only few are added as per the requirement of CIB, https://github.com/satya-das/cib.
 */
class CppObjFactory
{
public:
  virtual CppAst::CppCompound* CreateCompound(std::string name, CppAst::CppCompoundType type) const;
  virtual CppAst::CppCompound* CreateCompound(CppAst::CppCompoundType type = CppAst::CppCompoundType::UNKNOWN) const;

  virtual CppAst::CppConstructor*   CreateConstructor(std::string                              name,
                                                      std::vector<std::unique_ptr<CppEntity>>* params,
                                                      CppAst::CppMemInits                      memInits,
                                                      unsigned int                             attr) const;
  virtual CppAst::CppDestructor*    CreateDestructor(std::string name, std::uint32_t attr) const;
  virtual CppAst::CppFunction*      CreateFunction(std::string                              name,
                                                   CppAst::CppVarType*                      retType,
                                                   std::vector<std::unique_ptr<CppEntity>>* params,
                                                   unsigned int                             attr) const;
  virtual CppAst::CppTypeConverter* CreateTypeConverter(CppAst::CppVarType* type, std::string name) const;
};

using CppObjFactoryPtr = std::unique_ptr<CppObjFactory>;

#endif /* FD4A67B1_0F80_450C_810E_38D081BF552B */
