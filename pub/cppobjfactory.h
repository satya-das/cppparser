#pragma once

#include "cppdom.h"

/*!
 * \brief Factory class to create various CppObj instances.
 * Ideally this factory class should be used to create any CppObj object
 * instead of directly calling new. At present creation of only CppCompound and CppFunction
 * are added. That's because CIB needs only these. :)
 */
class CppObjFactory
{
public:
  virtual CppCompound* CreateCompound(std::string name, CppObjProtLevel prot, CppCompoundType type) const;
  virtual CppCompound* CreateCompound(CppObjProtLevel prot, CppCompoundType type = kUnknownCompound) const;
  virtual CppCompound* CreateCompound(std::string name, CppCompoundType type) const;
  virtual CppCompound* CreateCompound(CppCompoundType type) const;

  virtual CppFunction* CreateFunction(CppObjProtLevel prot, std::string name, CppVarType* retType, CppParamList* params, unsigned int attr) const;
};
