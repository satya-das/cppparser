/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

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

#pragma once

#include "cppast.h"
#include "cppobjfactory.h"
#include "cpptoken.h"

#include <iterator>
#include <vector>

extern CppObjFactory* gObjFactory;

template <typename... Params>
CppCompound* newCompound(Params... params)
{
  return gObjFactory->CreateCompound(params...);
}

template <typename... Params>
CppConstructor* newConstructor(Params... params)
{
  return gObjFactory->CreateConstructor(params...);
}

template <typename... Params>
CppDestructor* newDestructor(Params... params)
{
  return gObjFactory->CreateDestructor(params...);
}

template <typename... Params>
CppFunction* newFunction(Params... params)
{
  return gObjFactory->CreateFunction(params...);
}

template <typename... Params>
CppTypeConverter* newTypeConverter(Params... params)
{
  return gObjFactory->CreateTypeConverter(params...);
}

template <class Iter>
inline std::reverse_iterator<Iter> rev(Iter i)
{
  return std::reverse_iterator<Iter>(i);
}

CppToken classNameFromIdentifier(const CppToken& identifier);

std::vector<char> readFile(const std::string& filename);

using CppProgFileSelecter = std::function<bool(const std::string&)>;
std::vector<std::string> collectFiles(const std::string& folder, const CppProgFileSelecter& fileSelector);
