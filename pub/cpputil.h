/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

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

#include <filesystem>
#include <functional>

#include "cppast.h"
#include "cppconst.h"

namespace fs = std::filesystem;

using CppProgFileSelecter = std::function<bool(const std::string&)>;

void collectFiles(std::vector<std::string>& files, const fs::path& path, const CppProgFileSelecter& fileSelector);

inline std::vector<std::string> collectFiles(const std::string& folder, const CppProgFileSelecter& fileSelector)
{
  std::vector<std::string> files;
  collectFiles(files, folder, fileSelector);

  return files;
}

inline CppAccessType defaultAccessType(CppCompoundType type)
{
  return (type == CppCompoundType::kClass) ? CppAccessType::kPrivate : CppAccessType::kPublic;
}

inline CppAccessType effectiveAccessType(CppAccessType objAccessType, CppCompoundType ownerType)
{
  return (objAccessType != CppAccessType::kUnknown) ? objAccessType : defaultAccessType(ownerType);
}

inline CppAccessType resolveInheritanceType(CppAccessType inheritanceType, CppCompoundType type)
{
  return (inheritanceType != CppAccessType::kUnknown) ? inheritanceType : defaultAccessType(type);
}
