// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E6050C6F_BFEC_4B71_9B13_0EFF19B45EB4
#define E6050C6F_BFEC_4B71_9B13_0EFF19B45EB4

#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/program_options.hpp>
#include <filesystem>

namespace fs  = std::filesystem;
namespace bpo = boost::program_options;

template <typename _Itr1, typename _Itr2, typename _Pr>
inline std::pair<_Itr1, _Itr2>
compare_ranges(_Itr1 firstRangeStart, _Itr1 firstRangeEnd, _Itr2 secondRangeStart, _Itr2 secondRangeEnd, _Pr pred)
{
  auto i1 = firstRangeStart;
  auto i2 = secondRangeStart;
  for (; i1 != firstRangeEnd && i2 != secondRangeEnd; ++i1, ++i2)
    if (!pred(*i1, *i2))
      break;
  return std::make_pair(i1, i2);
}

inline std::pair<int, int> compareContents(const std::string& buf1, const std::string& buf2)
{
  int  r        = 0; // Number of lines read.
  int  c        = 0; // Number of chars read in a line.
  auto b1       = buf1.begin();
  auto e1       = buf1.end();
  auto b2       = buf2.begin();
  auto e2       = buf2.end();
  auto diffInfo = compare_ranges(b1, e1, b2, e2, [&r, &c](auto c1, auto c2) -> bool {
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
  return matched ? std::make_pair(-1, -1) : std::make_pair(r + 1, c + 1);
}

inline std::pair<int, int> compareFiles(std::ifstream& file1, std::ifstream& file2)
{
  std::stringbuf buf1;
  file1 >> &buf1;
  std::stringbuf buf2;
  file2 >> &buf2;

  return compareContents(buf1.str(), buf2.str());
}

enum FileCompareResult
{
  kSameFiles,
  kFailedToOpen1stFile,
  kFailedToOpen2ndFile,
  kDifferentFiles
};

inline FileCompareResult compareFiles(const fs::path& path1, const fs::path& path2, std::pair<int, int>& diffStartsAt)
{
  std::ifstream file1(path1.string(), std::ios_base::in);
  std::ifstream file2(path2.string(), std::ios_base::in);
  if (!file1.is_open())
    return kFailedToOpen1stFile;
  if (!file2.is_open())
    return kFailedToOpen2ndFile;

  diffStartsAt = compareFiles(file1, file2);
  if (diffStartsAt != std::make_pair(-1, -1))
    return kDifferentFiles;
  return kSameFiles;
}

inline void reportFileComparisonError(FileCompareResult    result,
                                      const fs::path&      path1,
                                      const fs::path&      path2,
                                      std::pair<int, int>& diffStartsAt)
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
    std::cerr << "CppParserTest: File comparison failed while comparing " << path1.string() << " " << path2.string()
              << "\n";
    std::cerr << "CppParserTest: Error is around line#" << r << " and column#" << c << " in file " << path1.string()
              << "\n";
  }
}

#endif /* E6050C6F_BFEC_4B71_9B13_0EFF19B45EB4 */
