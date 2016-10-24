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

#include <boost/system/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <fstream>
#include <strstream>
#include <iostream>
#include <utility>

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

//////////////////////////////////////////////////////////////////////////

template<typename _Itr1, typename _Itr2, typename _Pr>
inline std::pair<_Itr1, _Itr2> compare_ranges(_Itr1 firstRangeStart, _Itr1 firstRangeEnd, _Itr2 secondRangeStart, _Itr2 secondRangeEnd, _Pr pred)
{
	auto i1 = firstRangeStart;
	auto i2 = secondRangeStart;
	for (; i1 != firstRangeEnd && i2 != secondRangeEnd; ++i1, ++i2)
		if (!pred(*i1, *i2))
			break;
	return std::make_pair(i1, i2);
}

std::pair<int, int> compareContents(/*const*/ std::strstreambuf& buf1, /*const*/ std::strstreambuf& buf2)
{
	int r = 0; // Number of lines read.
	int c = 0; // Number of chars read in a line.
	auto b1 = buf1.str();
	auto e1 = b1 + buf1.pcount();
	auto b2 = buf2.str();
	auto e2 = b2 + buf2.pcount();
	auto diffInfo = compare_ranges(b1, e1, b2, e2, [&r, &c](auto c1, auto c2)->bool {
		if (c1 != c2)
			return false;
		if (c1 == '\n')
		{
			++r;
			c = 0;
		}
		else
		{
			++c;
		}
		return true;
	});

	bool matched = diffInfo.first == e1 && diffInfo.second == e2;
	return matched ? std::make_pair(-1, -1) : std::make_pair(r+1, c+1);
}

std::pair<int, int> compareFiles(std::ifstream& file1, std::ifstream& file2)
{
	std::strstreambuf buf1;
	file1 >> &buf1;
	std::strstreambuf buf2;
	file2 >> &buf2;

	return compareContents(buf1, buf2);
}

enum FileCompareResult
{
	kSameFiles,
	kFailedToOpen1stFile,
	kFailedToOpen2ndFile,
	kDifferentFiles
};

FileCompareResult compareFiles(const bfs::path& path1, const bfs::path& path2, std::pair<int, int>& diffStartsAt)
{
	std::ifstream file1(path1.c_str(), std::ios_base::in);
	std::ifstream file2(path2.c_str(), std::ios_base::in);
	if (!file1.is_open())
		return kFailedToOpen1stFile;
	if (!file2.is_open())
		return kFailedToOpen2ndFile;

	diffStartsAt = compareFiles(file1, file2);
	if (diffStartsAt != std::make_pair(-1, -1))
		return kDifferentFiles;
	return kSameFiles;
}

void reportFileComparisonError(FileCompareResult result, const bfs::path& path1, const bfs::path& path2, std::pair<int, int>& diffStartsAt)
{
	if (result == kFailedToOpen1stFile)
	{
		std::cerr << "CppParserTest: Could not open file " << path1.string() << "\n";
	}
	else if (result == kFailedToOpen2ndFile)
	{
		std::cerr << "CppParserTest: Could not open file " << path2.string() << "\n";
	}
	else if (result == kDifferentFiles)
	{
		int r, c;
		std::tie(r, c) = diffStartsAt;
		std::cerr << "CppParserTest: File comparison failed while comparing " << path1.string() << " and " << path2.string() << "\n";
		std::cerr << "CppParserTest: Error is around line#" << r << " and column#" << c << " in file " << path1.string() << "\n";
	}
}

struct TestParam
{
	bfs::path inputPath;
	bfs::path outputPath;
	bfs::path masterPath;

	bool isValid() const {
		if (!bfs::is_directory(inputPath) ||
			(bfs::exists(outputPath) && !bfs::is_directory(outputPath)) ||
			(!bfs::is_directory(masterPath))
			)
			return false;
		return true;
	}

	void setup() {
		inputPath.make_preferred();
		outputPath.make_preferred();
		masterPath.make_preferred();

		bfs::create_directories(outputPath);
	}
};

class ArgParser
{
	bpo::options_description desc_;
	bpo::variables_map vm_;

public:
	enum ParseResult {
		kSuccess,
		kHelpSought,
		kRequiredArgMissing,
		kWrongParamValue
	};

public:
	ArgParser()
		: desc_(
			"Automatic testing of CppParser by doing three steps:\n"
			"1) Parse each files in input folder.\n"
			"2) Emit C/C++ source from parsed data into output folder.\n"
			"3) Compare each files generated in step (2) with corresponding master file.\n"
			)
	{
		desc_.add_options()
			("help,h", "produce help message")
			("input-folder,i", bpo::value<std::string>(), "Input folder from where test files are picked.")
			("output-folder,o", bpo::value<std::string>(), "Output folder for emitting files after parsing.")
			("master-files-folder,m", bpo::value<std::string>(), "Folder where master files are kept that are used to compare with actuals.")
			;
	}

	ParseResult parse(int argc, char** argv)
	{
		bpo::store(bpo::parse_command_line(argc, argv, desc_), vm_);
		bpo::notify(vm_);
		if (vm_.count("help"))
			return kHelpSought;
		else if (vm_.count("input-folder") == 0)
			return kRequiredArgMissing;
		else if (vm_.count("output-folder") == 0)
			return kRequiredArgMissing;
		else if (vm_.count("master-files-folder") == 0)
			return kRequiredArgMissing;

		return kSuccess;
	}

	TestParam extractParams() const
	{
		TestParam param;
		if (vm_.count("input-folder"))
			param.inputPath = vm_["input-folder"].as<std::string>();
		if (vm_.count("output-folder"))
			param.outputPath = vm_["output-folder"].as<std::string>();
		if (vm_.count("master-files-folder"))
			param.masterPath = vm_["master-files-folder"].as<std::string>();
		param.setup();
		return param;
	}

	void emitError() const
	{
		if (vm_.count("help"))
		{
			std::cerr << desc_ << "\n";
			exit(-1);
		}
		if (vm_.count("input-folder") == 0)
		{
			std::cerr << "Error: Input folder not specified.\n\n" << desc_ << "\n";
			exit(-2);
		}
		if (vm_.count("output-folder") == 0)
		{
			std::cerr << "Error: Output folder not specified.\n\n" << desc_ << "\n";
			exit(-3);
		}
		if (vm_.count("master-files-folder") == 0)
		{
			std::cerr << "Error: Master-files folder not specified.\n\n" << desc_ << "\n";
			exit(-4);
		}
	}
};

bool parseAndEmitFormatted(const bfs::path& inputFilePath, const bfs::path& outputFilePath, const CppWriter& cppWriter)
{
	CppCompound* progUnit = parseSingleFile(inputFilePath.string().c_str());
	if (progUnit == NULL)
		return false;
	std::ofstream stm(outputFilePath.c_str());
	cppWriter.emit(progUnit, stm);
//	delete progUnit;

	return true;
}

std::pair<size_t, size_t> performTest(const TestParam& params)
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
