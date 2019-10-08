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
#include "compare.h"
#include "cppwriter.h"
#include "options.h"

#include <fstream>
#include <iostream>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/system/config.hpp>

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

//////////////////////////////////////////////////////////////////////////

static bool parseAndEmitFormatted(CppParser&       parser,
                                  const bfs::path& inputFilePath,
                                  const bfs::path& outputFilePath,
                                  const CppWriter& cppWriter)
{
  auto progUnit = parser.parseFile(inputFilePath.string().c_str());
  if (!progUnit)
    return false;
  bfs::create_directories(outputFilePath.parent_path());
  std::ofstream stm(outputFilePath.string());
  cppWriter.emit(progUnit.get(), stm);

  return true;
}

static bool performParsing(CppParser& parser, const std::string& inputPath)
{
  auto progUnit = parser.parseFile(inputPath.c_str());
  if (!progUnit)
    return false;

  return true;
}

static std::pair<size_t, size_t> performTest(CppParser& parser, const TestParam& params)
{
  size_t numInputFiles = 0;
  size_t numFailed     = 0;

  CppWriter                cppWriter;
  auto                     inputPathLen = params.inputPath.string().length();
  std::vector<std::string> failedFiles;
  for (bfs::recursive_directory_iterator dirItr(params.inputPath); dirItr != bfs::recursive_directory_iterator();
       ++dirItr)
  {
    bfs::path file = *dirItr;
    if (bfs::is_regular_file(file))
    {
      ++numInputFiles;
      std::cout << "CppParserTest: Parsing " << file.string() << "...\n";
      auto      fileRelPath = file.string().substr(inputPathLen);
      bfs::path outfile     = params.outputPath / fileRelPath;
      bfs::remove(outfile);
      if (parseAndEmitFormatted(parser, file, outfile, cppWriter) && bfs::exists(outfile))
      {
        bfs::path           masfile = params.masterPath / fileRelPath;
        std::pair<int, int> diffStartInfo;
        auto                rez = compareFiles(outfile, masfile, diffStartInfo);
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
    std::cerr << "\n\n";
    std::cerr << "Parsing failure summary.\n------------------------\n";
    for (const auto& s : failedFiles)
    {
      std::cerr << s << '\n';
    }
    std::cerr << "Parsing failed for " << failedFiles.size() << " files.\n\n";
  }

  return std::make_pair(numInputFiles, numFailed);
}

CppParser constructCppParserForTest()
{
  CppParser parser;
  parser.addKnownApiDecors({"ODRX_ABSTRACT",
                            "FIRSTDLL_EXPORT",
                            "GE_DLLEXPIMPORT",
                            "ADESK_NO_VTABLE",
                            "ACDBCORE2D_PORT",
                            "ACBASE_PORT",
                            "ACCORE_PORT",
                            "ACDB_PORT",
                            "ACPAL_PORT",
                            "ACAD_PORT",
                            });

  parser.addKnownMacros({"DECLARE_MESSAGE_MAP",
                         "DECLARE_DYNAMIC",
                         "ACPL_DECLARE_MEMBERS",
                         "DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION",
                         "DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION",
                         "DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION",
                         "ACRX_DECLARE_MEMBERS_EXPIMP",
                         "ACRX_DECLARE_MEMBERS_ACBASE_PORT_EXPIMP",
                         "ACRX_DECLARE_MEMBERS",
                         
                         "SkDEBUGCODE"
                         });

  parser.addRenamedKeyword("virtual", "ADESK_SEALED_VIRTUAL");
  parser.addRenamedKeyword("final", "ADESK_SEALED");
  parser.addRenamedKeyword("override", "ADESK_OVERRIDE");

  return std::move(parser);
}

int main(int argc, char** argv)
{
  CppParser parser = constructCppParserForTest();

  ArgParser argParser;
  auto      optionParseResult = argParser.parse(argc, argv);
  if (optionParseResult == ArgParser::kParsingError)
  {
    argParser.emitError();
    return -1;
  }
  else if (optionParseResult == ArgParser::kParseSingleFile)
  {
    auto filePath = argParser.extractSingleFilePath();
    performParsing(parser, filePath);
  }
  else
  {
    auto params = argParser.extractParamsForFullTest();
    auto result = performTest(parser, params);
    if (result.second)
    {
      std::cerr << "CppParserTest: " << result.second << " tests failed out of " << result.first << ".\n";
      return 1;
    }
    std::cout << "CppParserTest: All " << result.first << " tests passed without error.\n";
  }
  return 0; // All went well.
}
