#include "cppobjfactory.h"

CppCompound* CppObjFactory::CreateCompound(std::string name, CppObjProtLevel prot, CppCompoundType type) const
{
  return new CppCompound(std::move(name), prot, type);
}

CppCompound* CppObjFactory::CreateCompound(CppObjProtLevel prot, CppCompoundType type) const
{
  return new CppCompound(prot, type);
}

CppCompound* CppObjFactory::CreateCompound(std::string name, CppCompoundType type) const
{
  return new CppCompound(std::move(name), type);
}

CppCompound* CppObjFactory::CreateCompound(CppCompoundType type) const
{
  return new CppCompound(type);
}

CppFunction* CppObjFactory::CreateFunction(CppObjProtLevel prot, std::string name, CppVarType* retType, CppParamList* params, unsigned int attr) const
{
  return new CppFunction(prot, std::move(name), retType, params, attr);
}
