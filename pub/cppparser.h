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

#ifndef __CPPPARSER_H__
#define __CPPPARSER_H__

#include "cppdom.h"
#include "cppprog.h"

#include <boost/filesystem.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace bfs = boost::filesystem;

class CppObjFactory;

class CppParser
{
public:
  CppParser(CppObjFactory *objFactory = nullptr);

  void addKnownMacro(std::string knownMacro);
  void addKnownMacros(const std::vector<std::string> &knownMacros);

  void addKnownApiDecor(std::string knownApiDecor);
  void addKnownApiDecors(const std::vector<std::string> &knownApiDecor);

public:
  CppCompound *parseFile(const char *filename);
  CppCompound *parseStream(char *stm, size_t stmSize);
  /*!
   * Loads C++ program from source and header files.
   * @param inputPath Folder where the C++ files are present.
   */
  CppProgram *loadProgram(const char *szInputPath);

protected:
  void loadProgram(const bfs::path &path, CppProgram &program);

private:
  using ByteArray = std::vector<char>;
  static ByteArray readFile(const char *filename);

private:
  CppObjFactory *objFactory_;
};

#endif //__CPPPARSER_H__
