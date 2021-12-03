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

#include "cppobjfactory.h"

#include <functional>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Parses C++ source and generates an AST.
 *
 * @warning Although its a class it is not reentrant because underlying btyacc is not reentrant.
 * So, any change done through this class is global and affects the result of other instances too.
 */
class CppParser
{
public:
  using ErrorHandler =
    std::function<void(const char* errLineText, size_t lineNum, size_t errorStartPos, int lexerContext)>;

public:
  CppParser(CppObjFactoryPtr objFactory = nullptr);
  CppParser(CppParser&& rhs)
    : objFactory_(std::move(rhs.objFactory_))
  {
  }

public:
  void addKnownMacro(std::string knownMacro);
  void addKnownMacros(const std::vector<std::string>& knownMacros);

  void addDefinedName(std::string definedName, int value = 0);

  void addUndefinedName(std::string undefinedName);
  void addUndefinedNames(const std::vector<std::string>& undefinedNames);

  void addIgnorableMacro(std::string ignorableMacro);
  void addIgnorableMacros(const std::vector<std::string>& ignorableMacros);

  void addKnownApiDecor(std::string knownApiDecor);
  void addKnownApiDecors(const std::vector<std::string>& knownApiDecor);

  bool addRenamedKeyword(const std::string& keyword, std::string renamedKeyword);

  void parseEnumBodyAsBlob();
  void parseFunctionBodyAsBlob(bool asBlob);

public:
  CppCompoundPtr parseFile(const std::string& filename);
  CppCompoundPtr parseStream(char* stm, size_t stmSize);

  void setErrorHandler(ErrorHandler errorHandler);
  void resetErrorHandler();

private:
  CppObjFactoryPtr objFactory_;
};
