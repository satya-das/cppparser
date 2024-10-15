// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A531EBC7_86A1_42D5_91DA_9257FBF65184
#define A531EBC7_86A1_42D5_91DA_9257FBF65184

#include "cpptoken.h"

#include <iterator>
#include <string>

template <class Iter>
inline std::reverse_iterator<Iter> rev(Iter i)
{
  return std::reverse_iterator<Iter>(i);
}

CppToken classNameFromIdentifier(const CppToken& identifier);

std::string pruneClassName(const CppToken& identifier);

std::string readFile(const std::string& filename);

std::vector<CppToken> explode(CppToken token, const char* delim);

#endif /* A531EBC7_86A1_42D5_91DA_9257FBF65184 */
