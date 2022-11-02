// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef FF2B85CA_C19B_482E_9B0F_5F098BF974A1
#define FF2B85CA_C19B_482E_9B0F_5F098BF974A1

#include <boost/filesystem.hpp>

#include "cppast/cppast.h"
#include "cppconst.h"

namespace fs = boost::filesystem;

using CppProgFileSelecter = std::function<bool(const std::string&)>;

void collectFiles(std::vector<std::string>& files, const fs::path& path, const CppProgFileSelecter& fileSelector);

inline std::vector<std::string> collectFiles(const std::string& folder, const CppProgFileSelecter& fileSelector)
{
  std::vector<std::string> files;
  collectFiles(files, folder, fileSelector);

  return files;
}

inline CppAst::CppAccessType defaultAccessType(CppAst::CppCompoundType type)
{
  return (type == CppAst::CppCompoundType::CLASS) ? CppAst::CppAccessType::PRIVATE : CppAst::CppAccessType::PUBLIC;
}

inline CppAst::CppAccessType effectiveAccessType(CppAst::CppAccessType objAccessType, CppAst::CppCompoundType ownerType)
{
  return (objAccessType != CppAst::CppAccessType::UNSPECIFIED) ? objAccessType : defaultAccessType(ownerType);
}

inline CppAst::CppAccessType resolveInheritanceType(CppAst::CppAccessType inheritanceType, CppAst::CppCompoundType type)
{
  return (inheritanceType != CppAst::CppAccessType::UNSPECIFIED) ? inheritanceType : defaultAccessType(type);
}

#endif /* FF2B85CA_C19B_482E_9B0F_5F098BF974A1 */
