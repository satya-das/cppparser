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
#include "cppwriter.h"
#include "compare.h"
#include "options.h"

#include <fstream>
#include <iostream>
#include <utility>

#include <boost/system/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

//////////////////////////////////////////////////////////////////////////

static bool parseAndEmitFormatted(const bfs::path& inputFilePath, const bfs::path& outputFilePath, const CppWriter& cppWriter)
{
  CppCompound* progUnit = parseSingleFile(inputFilePath.string().c_str());
  if (progUnit == NULL)
    return false;
  std::ofstream stm(outputFilePath.c_str());
  cppWriter.emit(progUnit, stm);
  delete progUnit;

  return true;
}

static std::pair<size_t, size_t> performTest(const TestParam& params)
{
  size_t numInputFiles = 0;
  size_t numFailed = 0;

  CppWriter cppWriter;
  for (bfs::directory_iterator dirItr(params.inputPath); dirItr != bfs::directory_iterator(); ++dirItr)
  {
    bfs::path file = *dirItr;
    if (bfs::is_regular_file(file))
    {
      ++numInputFiles;
      std::cout << "CppParserTest: Parsing " << file.string() << "...\n";
      bfs::path outfile = params.outputPath / file.filename();
      bfs::remove(outfile);
      if (parseAndEmitFormatted(file, outfile, cppWriter) && bfs::exists(outfile))
      {
        bfs::path masfile = params.masterPath / file.filename();
        std::pair<int, int> diffStartInfo;
        auto rez = compareFiles(outfile, masfile, diffStartInfo);
        if (rez == kSameFiles)
          continue;
        reportFileComparisonError(rez, outfile, masfile, diffStartInfo);
      }
      else
      {
        std::cerr << "Parsing failed for " << file.string() << "\n";
      }
      ++numFailed;
    }
  }

  return std::make_pair(numInputFiles, numFailed);
}

int main(int argc, char** argv)
{
  ArgParser argParser;
  if (argParser.parse(argc, argv) != ArgParser::kSuccess)
  {
    argParser.emitError();
    return -1;
  }

  auto params = argParser.extractParams();
  auto result = performTest(params);
  if (result.second)
  {
    std::cerr << "CppParserTest: " << result.second << " tests failed out of " << result.first << ".\n";
    return 1;
  }
  std::cout << "CppParserTest: All " << result.first << " tests passed without error.\n";
  return 0; // All went well.
}
