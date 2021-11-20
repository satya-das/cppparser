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

#include "cppparser.h"
#include "cppast.h"
#include "cppobjfactory.h"
#include "parser.h"
#include "string-utils.h"
#include "utils.h"

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

// Unfortunately parser is not reentrant and has no way as of now to inject parameters.
// So, we need globals.

// Globals to help parse when preprocessors are used
std::set<std::string>      gMacroNames;
std::set<std::string>      gKnownApiDecorNames;
std::map<std::string, int> gDefinedNames;
std::set<std::string>      gUndefinedNames;
std::set<std::string>      gIgnorableMacroNames;
std::map<std::string, int> gRenamedKeywords;

bool gParseEnumBodyAsBlob     = false;
bool gParseFunctionBodyAsBlob = false;

CppObjFactory* gObjFactory = nullptr;

CppParser::CppParser(CppObjFactoryPtr objFactory)
  : objFactory_(std::move(objFactory))
{
  if (!objFactory_)
    objFactory_.reset(new CppObjFactory);
}

void CppParser::addKnownMacro(std::string knownMacro)
{
  gMacroNames.insert(std::move(knownMacro));
}

void CppParser::addKnownMacros(const std::vector<std::string>& knownMacros)
{
  for (auto& macro : knownMacros)
    gMacroNames.insert(macro);
}

void CppParser::addDefinedName(std::string definedName, int value)
{
  gDefinedNames[std::move(definedName)] = value;
}

void CppParser::addUndefinedName(std::string undefinedName)
{
  gUndefinedNames.insert(std::move(undefinedName));
}

void CppParser::addUndefinedNames(const std::vector<std::string>& undefinedNames)
{
  for (auto& macro : undefinedNames)
    gUndefinedNames.insert(macro);
}

void CppParser::addIgnorableMacro(std::string ignorableMacro)
{
  gIgnorableMacroNames.insert(std::move(ignorableMacro));
}

void CppParser::addIgnorableMacros(const std::vector<std::string>& ignorableMacros)
{
  for (auto& macro : ignorableMacros)
    gIgnorableMacroNames.insert(macro);
}

void CppParser::addKnownApiDecor(std::string knownApiDecor)
{
  gKnownApiDecorNames.insert(std::move(knownApiDecor));
}

void CppParser::addKnownApiDecors(const std::vector<std::string>& knownApiDecor)
{
  for (auto& apiDecor : knownApiDecor)
    gKnownApiDecorNames.insert(apiDecor);
}

bool CppParser::addRenamedKeyword(const std::string& keyword, std::string renamedKeyword)
{
  extern int GetKeywordId(const std::string& keyword);
  auto       id = GetKeywordId(keyword);
  if (id == -1)
    return false;
  gRenamedKeywords.emplace(std::make_pair(std::move(renamedKeyword), id));

  return true;
}

void CppParser::parseEnumBodyAsBlob()
{
  gParseEnumBodyAsBlob = true;
}

void CppParser::parseFunctionBodyAsBlob(bool asBlob)
{
  gParseFunctionBodyAsBlob = asBlob;
}

CppCompoundPtr CppParser::parseFile(const std::string& filename)
{
  auto stm         = readFile(filename);
  auto cppCompound = parseStream(stm.data(), stm.size());
  if (!cppCompound)
    return cppCompound;
  cppCompound->name(filename);
  return cppCompound;
}

CppCompoundPtr CppParser::parseStream(char* stm, size_t stmSize)
{
  if (stm == nullptr || stmSize == 0)
    return nullptr;
  gObjFactory = objFactory_.get();
  return ::parseStream(stm, stmSize);
}

void CppParser::setErrorHandler(ErrorHandler errorHandler)
{
  ::setErrorHandler(errorHandler);
}

void CppParser::resetErrorHandler()
{
  ::resetErrorHandler();
}
