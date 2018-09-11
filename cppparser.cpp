/*
   The MIT License (MIT)

   Copyright (c) 2014

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
#include "cppobjfactory.h"
#include "cppdom.h"
#include "string-utils.h"

#include <algorithm>
#include <fstream>
#include <vector>

extern CppCompound* parseStream(char* stm, size_t stmSize);
CppObjFactory* gObjFactory = nullptr;

CppParser::CppParser(CppObjFactory* objFactory)
  : objFactory_(objFactory)
{
  if (objFactory_ == nullptr)
    objFactory_ = new CppObjFactory;
}

CppCompound* CppParser::parseFile(const char* filename)
{
  auto stm = readFile(filename);
  CppCompound* cppCompound = parseStream(stm.data(), stm.size());
  if (cppCompound == NULL)
    return cppCompound;
  cppCompound->name_ = filename;
  return cppCompound;
}

CppCompound* CppParser::parseStream(char* stm, size_t stmSize)
{
  if (stm == nullptr || stmSize == 0)
    return nullptr;
  gObjFactory = objFactory_;
  return ::parseStream(stm, stmSize);
}

CppProgram* CppParser::loadProgram(const char* szInputPath)
{
  auto program = new CppProgram;
  loadProgram(szInputPath, *program);
  return program;
}

static void collectFiles(const bfs::path& path, std::vector<std::string>& files)
{
  if (bfs::is_regular_file(path))
  {
    files.push_back(path.string());
  }
  else if (bfs::is_directory(path))
  {
    for (bfs::directory_iterator dirItr(path); dirItr != bfs::directory_iterator(); ++dirItr)
    {
      collectFiles(*dirItr, files);
    }
  }
}

static std::vector<std::string> collectFiles(const bfs::path& path)
{
  std::vector<std::string> files;
  collectFiles(path, files);
  if (!files.empty())
    std::sort(files.begin(), files.end());

  return files;
}

void CppParser::loadProgram(const bfs::path& path, CppProgram& program)
{
  auto files = collectFiles(path);
  for (const auto& f : files)
  {
    auto cppDom = parseFile(f.c_str());
    if (cppDom)
      program.addCppDom(cppDom);
  }
}

CppParser::ByteArray CppParser::readFile(const char* filename)
{
  ByteArray contents;
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    contents.resize(size+3); // For adding last 2 nulls and a new line.
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], size);
    in.close();
    auto len = stripChar(contents.data(), size, '\r');
    assert(len <= size);
    contents.resize(len+3);
    contents[len] = '\n';
    contents[len+1] = '\0';
    contents[len+2] = '\0';
  }
  return(contents);
}
