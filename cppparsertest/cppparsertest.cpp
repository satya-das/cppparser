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

namespace bfs = boost::filesystem;
namespace po = boost::program_options;

//////////////////////////////////////////////////////////////////////////

/**
 * Makes sure \a path uses preferred slash and it ends with slash
 */
inline void make_preferred_dir_format(boost::filesystem::path& path)
{
   path.make_preferred();
   if(path.native().back() != path.preferred_separator)
      path = path.native() + path.preferred_separator;
}

bool isSame(const bfs::path& path1, const bfs::path& path2)
{
	std::ifstream file1(path1.c_str(), std::ios_base::in);
	std::ifstream file2(path2.c_str(), std::ios_base::in);
	if(!file1.is_open())
	{
		std::cerr << "CppParserTest: Could not open file " << path1.string() << "\n";
		return false;
	}
	if(!file2.is_open())
	{
		std::cerr << "CppParserTest: Could not open file " << path2.string() << "\n";
		return false;
	}
	std::strstreambuf buf1;
	file1 >> &buf1;
	std::strstreambuf buf2;
	file2 >> &buf2;

	int r = 0; // Number of lines read.
	int c = 0; // Number of chars read in a line.
	for(size_t i = 0; i < buf1.pcount(); ++i)
	{
		if(i >= buf2.pcount())
		{
			std::cerr << "CppParserTest: File comparison failed: Prematurely reached end of file while comparing " << path1.string() << " and " << path2.string() << "\n";
			std::cerr << "CppParserTest: Error is around line#" << r << "column#" << c << " in file " << path1.string() << "\n";
			return false;
		}
		int ch1 = buf1.str()[i];
		int ch2 = buf2.str()[i];
		if(ch1 != ch2)
		{
			std::cerr << "CppParserTest: File comparison failed while comparing " << path1.string() << " and " << path2.string() << "\n";
			std::cerr << "CppParserTest: Error is around line#" << r << " and column#" << c << " in file " << path1.string() << "\n";
			return false;
		}

		if(ch1 == '\n')
		{
			++r;
			c = 0;
		}
		else
		{
			++c;
		}
	}

	if(buf1.pcount() != buf2.pcount())
	{
		std::cerr << "CppParserTest: File comparison failed while comparing " << path1.string() << " and " << path2.string() << "\n";
		std::cerr << "CppParserTest: File " << path1.string() << "has extra content.\n";
		return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	// Declare the supported options.
	po::options_description desc(
		"Automatic testing of CppParser by doing three steps:\n"
		"1) Parse each files in input folder.\n"
		"2) Emit C/C++ source from parsed data into output folder.\n"
		"3) Compare each files generated in step (2) with corresponding master file.\n"
		);
	desc.add_options()
		("help,h",					"produce help message")
		("input-folder,i",			po::value<std::string>(), "Input folder from where test files are picked.")
		("output-folder,o",			po::value<std::string>(), "Output folder for emitting files after parsing.")
		("master-files-folder,m",	po::value<std::string>(), "Folder where master files are kept that are used to compare with actuals.")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help"))
	{
		std::cerr << desc << "\n";
		return 1;
	}
	if(vm.count("input-folder") == 0)
	{
		std::cerr << "Error: Input folder not specified.\n\n" << desc << "\n";
		return 1;
	}
	if(vm.count("output-folder") == 0)
	{
		std::cerr << "Error: Output folder not specified.\n\n" << desc << "\n";
		return 1;
	}
	if(vm.count("master-files-folder") == 0)
	{
		std::cerr << "Error: Master-files folder not specified.\n\n" << desc << "\n";
		return 1;
	}

	bfs::path inputPath;
	bfs::path outputPath;
	bfs::path masterPath;

	if(vm.count("input-folder"))
		inputPath = vm["input-folder"].as<std::string>();
	if(vm.count("output-folder"))
		outputPath = vm["output-folder"].as<std::string>();
	if(vm.count("master-files-folder"))
		masterPath = vm["master-files-folder"].as<std::string>();

	if	(!bfs::is_directory(inputPath) ||
		(bfs::exists(outputPath) && !bfs::is_directory(outputPath)) ||
		(!bfs::is_directory(masterPath))
		)
		return -1;
	make_preferred_dir_format(inputPath);
	make_preferred_dir_format(outputPath);
	make_preferred_dir_format(masterPath);

	bfs::create_directories(outputPath);

	int numInputFiles = 0;
	int numPassed = 0;
	int numFailed = 0;

	CppWriter cppWriter;
	for(bfs::directory_iterator dirItr(inputPath); dirItr != bfs::directory_iterator(); ++dirItr)
	{
		bfs::path file = *dirItr;
		if(bfs::is_regular_file(file))
		{
			++numInputFiles;
			std::cout << "CppParserTest: Parsing " << file.string() << "...\n";
			CppCompound* progUnit = parseSingleFile(file.string().c_str());
			if(progUnit == NULL)
			{
				++numFailed;
				std::cerr << "Parsing failed for " << file.string() << "\n";
				continue;
			}

			bfs::path outfile = outputPath / file.filename();
			bfs::path masfile = masterPath / file.filename();
			std::ofstream stm(outfile.c_str());
			cppWriter.emit(progUnit, stm);
			stm.flush();
			stm.close();
			if(isSame(outfile, masfile))
				++numPassed;
			else
				++numFailed;
		}
	}

	if(numFailed)
	{
		std::cerr << "CppParserTest: " << numFailed << " tests failed out of " << numInputFiles << ".\n";
		return 1;
	}
	std::cout << "CppParserTest: All " << numInputFiles << " tests passed without error.\n";
	return 0; // All went well.
}
