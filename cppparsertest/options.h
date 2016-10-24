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

#pragma once

#include <iostream>

#include <boost/system/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;

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
