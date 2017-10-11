#include "cppobjfactory.h"

CppCompound* CppObjFactory::CreateCompound(std::string name, CppObjProtLevel prot, CppCompoundType type) const
{
  return new CppCompound(name, prot, type);
}

CppCompound* CppObjFactory::CreateCompound(CppObjProtLevel prot, CppCompoundType type) const
{
  return new CppCompound(prot, type);
}

CppCompound* CppObjFactory::CreateCompound(std::string name, CppCompoundType type) const
{
  return new CppCompound(name, type);
}

CppCompound* CppObjFactory::CreateCompound(CppCompoundType type) const
{
  return new CppCompound(type);
}

CppFunction* CppObjFactory::CreateFunction(CppObjProtLevel prot, std::string name, CppVarType* retType, CppParamList* params, unsigned int attr) const
{
  return new CppFunction(prot, name, retType, params, attr);
}
