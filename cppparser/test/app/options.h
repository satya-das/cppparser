// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E0EDF449_CFC3_4AC1_89F6_4D2C8F039011
#define E0EDF449_CFC3_4AC1_89F6_4D2C8F039011

#include <iostream>

#include <boost/program_options.hpp>
#include <filesystem>

namespace fs  = std::filesystem;
namespace bpo = boost::program_options;

struct TestParam
{
  fs::path inputPath;
  fs::path outputPath;
  fs::path masterPath;

  bool isValid() const
  {
    if (!fs::is_directory(inputPath) || (fs::exists(outputPath) && !fs::is_directory(outputPath))
        || (!fs::is_directory(masterPath)))
      return false;
    return true;
  }

  void setup()
  {
    inputPath.make_preferred();
    outputPath.make_preferred();
    masterPath.make_preferred();

    std::cout << outputPath.string() << std::endl;

    fs::create_directories(outputPath);
  }
};

class ArgParser
{
  bpo::options_description desc_;
  bpo::variables_map       vm_;

public:
  enum ParseResult
  {
    kHelpSought,
    kParseSingleFile,
    kParseAndCompare,
    kParseAndCompareUsingDefaultPaths = kParseAndCompare,
    kParsingError
  };

public:
  ArgParser()
    : desc_("Automatic testing of CppParser by doing three steps:\n"
            "1) Parse each files in input folder.\n"
            "2) Emit C/C++ source from parsed data into output folder.\n"
            "3) Compare each files generated in step (2) with corresponding master file.\n")
  {
    desc_.add_options()("help,h", "produce help message")(
      "input-folder,i", bpo::value<std::string>(), "Input folder from where test files are picked.")(
      "output-folder,o", bpo::value<std::string>(), "Output folder for emitting files after parsing.")(
      "master-files-folder,m",
      bpo::value<std::string>(),
      "Folder where master files are kept that are used to compare with actuals.")(
      "parse-file,p", bpo::value<std::string>(), "To test parsing of single file.");
  }

  ParseResult parse(int argc, char** argv)
  {
    bpo::store(bpo::parse_command_line(argc, argv, desc_), vm_);
    bpo::notify(vm_);
    if (vm_.count("help"))
    {
      std::cout << desc_ << "\n";
      exit(0);
      return kHelpSought;
    }

    if (vm_.count("parse-file") != 0)
      return kParseSingleFile;
    if ((vm_.count("input-folder") == 0) && (vm_.count("output-folder") == 0)
        && (vm_.count("master-files-folder") == 0))
      return kParseAndCompareUsingDefaultPaths;
    if ((vm_.count("input-folder") != 0) && (vm_.count("output-folder") != 0)
        && (vm_.count("master-files-folder") != 0))
      return kParseAndCompare;

    return kParsingError;
  }

  TestParam extractParamsForFullTest() const
  {
    TestParam param;
    auto      defaultTestFolderParent = fs::path(__FILE__).parent_path().parent_path() / "e2e";
    if (vm_.count("input-folder"))
      param.inputPath = vm_["input-folder"].as<std::string>();
    else
      param.inputPath = defaultTestFolderParent / "test_input";
    if (vm_.count("output-folder"))
      param.outputPath = vm_["output-folder"].as<std::string>();
    else
      param.outputPath = defaultTestFolderParent / "test_output";
    if (vm_.count("master-files-folder"))
      param.masterPath = vm_["master-files-folder"].as<std::string>();
    else
      param.masterPath = defaultTestFolderParent / "test_master";

    param.setup();
    return param;
  }

  std::string extractSingleFilePath() const
  {
    return vm_["parse-file"].as<std::string>();
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

#endif /* E0EDF449_CFC3_4AC1_89F6_4D2C8F039011 */
