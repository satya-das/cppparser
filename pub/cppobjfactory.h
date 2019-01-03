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

  virtual CppConstructor* CreateConstructor(CppObjProtLevel prot,
                                            std::string     name,
                                            CppParamList*   params,
                                            CppMemInitList* memInitList,
                                            unsigned int    attr) const;
  virtual CppDestructor*  CreateDestructor(CppObjProtLevel prot, std::string name, unsigned int attr) const;
  virtual CppFunction*    CreateFunction(CppObjProtLevel prot,
                                         std::string     name,
                                         CppVarType*     retType,
                                         CppParamList*   params,
                                         unsigned int    attr) const;
  virtual CppTypeConverter* CreateTypeConverter(CppVarType* type, std::string name) const;
};
