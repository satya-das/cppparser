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
  CppParser parser;
  CppCompound* progUnit = parser.parseFile(inputFilePath.string().c_str());
  if (progUnit == NULL)
    return false;
  bfs::create_directories(outputFilePath.parent_path());
  std::ofstream stm(outputFilePath.string());
  cppWriter.emit(progUnit, stm);
  delete progUnit;

  return true;
}

static bool performParsing(const std::string& inputPath)
{
  CppParser parser;
  CppCompound* progUnit = parser.parseFile(inputPath.c_str());
  if (progUnit == nullptr)
    return false;
  delete progUnit;

  return true;
}

static std::pair<size_t, size_t> performTest(const TestParam& params)
{
  size_t numInputFiles = 0;
  size_t numFailed = 0;

  CppWriter cppWriter;
  auto inputPathLen = params.inputPath.string().length();
  std::vector<std::string> failedFiles;
  for (bfs::recursive_directory_iterator dirItr(params.inputPath); dirItr != bfs::recursive_directory_iterator(); ++dirItr)
  {
    bfs::path file = *dirItr;
    if (bfs::is_regular_file(file))
    {
      ++numInputFiles;
      std::cout << "CppParserTest: Parsing " << file.string() << "...\n";
      auto fileRelPath = file.string().substr(inputPathLen);
      bfs::path outfile = params.outputPath / fileRelPath;
      bfs::remove(outfile);
      if (parseAndEmitFormatted(file, outfile, cppWriter) && bfs::exists(outfile))
      {
        bfs::path masfile = params.masterPath / fileRelPath;
        std::pair<int, int> diffStartInfo;
        auto rez = compareFiles(outfile, masfile, diffStartInfo);
        if (rez == kSameFiles)
          continue;
        reportFileComparisonError(rez, outfile, masfile, diffStartInfo);
      }
      else
      {
        auto filePathStr = file.string();
        std::cerr << "Parsing failed for " << filePathStr << "\n";
        failedFiles.push_back(filePathStr);
      }
      ++numFailed;
    }
  }
  if (!failedFiles.empty())
  {
    std::cerr <<"\n\n";
    std::cerr << "Parsing failire summary.\n------------------------\n";
    std::cerr << "Parsing failed for following files:\n";
    for (const auto& s : failedFiles)
    {
      std::cerr << s << '\n';
    }
  }

  return std::make_pair(numInputFiles, numFailed);
}

int main(int argc, char** argv)
{
  ArgParser argParser;
  auto optionParseResult = argParser.parse(argc, argv);
  if (optionParseResult == ArgParser::kParsingError)
  {
    argParser.emitError();
    return -1;
  }
  else if (optionParseResult == ArgParser::kParseSingleFile)
  {
      auto filePath = argParser.extractSingleFilePath();
      performParsing(filePath);
  }
  else
  {
    auto params = argParser.extractParamsForFullTest();
    auto result = performTest(params);
    if (result.second)
    {
      std::cerr << "CppParserTest: " << result.second << " tests failed out of " << result.first << ".\n";
      return 1;
    }
    std::cout << "CppParserTest: All " << result.first << " tests passed without error.\n";
  }
  return 0; // All went well.
}
