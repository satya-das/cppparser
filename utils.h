#pragma once

#include "cppobjfactory.h"
#include "cpptoken.h"
#include "cppdom.h"

#include <iterator>

extern CppObjFactory*               gObjFactory;

template<typename... Params>
CppCompound* newCompound(Params... params)
{
  return gObjFactory->CreateCompound(params...);
}

template<typename... Params>
CppConstructor* newConstructor(Params... params)
{
  return gObjFactory->CreateConstructor(params...);
}

template<typename... Params>
CppDestructor* newDestructor(Params... params)
{
  return gObjFactory->CreateDestructor(params...);
}

template<typename... Params>
CppFunction* newFunction(Params... params)
{
  return gObjFactory->CreateFunction(params...);
}

template<class Iter>
inline std::reverse_iterator<Iter> rev(Iter i)
{
  return std::reverse_iterator<Iter>(i);
}

inline CppToken classNameFromIdentifier(const CppToken& identifier)
{
  if (identifier.sz == nullptr)
    return identifier;

  auto rbeg = rev(identifier.sz + identifier.len);
  if (*rbeg != '>')
    return identifier;
  auto rend = rev(identifier.sz);
  int numTempl = 1;
  for (++rbeg; rbeg != rend; ++rbeg)
  {
    if (*rbeg == '<')
    {
      --numTempl;
      if (numTempl == 0)
      {
        CppToken clsName{identifier.sz, static_cast<size_t>(std::distance(rbeg, rend)) - 1};
        return clsName;
      }
    }
    else if (*rbeg == '>')
    {
      ++numTempl;
    }
  }

  return CppToken{nullptr, 0U};
}
