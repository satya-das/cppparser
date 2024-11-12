// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A531EBC7_86A1_42D5_91DA_9257FBF65184
#define A531EBC7_86A1_42D5_91DA_9257FBF65184

#include "cpptoken.h"

#include <iterator>
#include <string>

CppToken ClassNameFromIdentifier(const CppToken& identifier);

std::string PruneClassName(const CppToken& identifier);

std::string ReadFile(const std::string& filename);

std::vector<CppToken> Explode(CppToken token, const char* delim);

#endif /* A531EBC7_86A1_42D5_91DA_9257FBF65184 */
