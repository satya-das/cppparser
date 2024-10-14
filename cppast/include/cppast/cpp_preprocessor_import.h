// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef AC0E36D5_D135_4787_BB9B_F3FB72DF023D
#define AC0E36D5_D135_4787_BB9B_F3FB72DF023D

#include "cppast/cpp_preprocessor.h"

namespace cppast {

class CppPreprocessorImport : public CppPreprocessor
{
public:
  CppPreprocessorImport(std::string name)
    : CppPreprocessor(CppPreprocessorType::IMPORT)
    , name_(std::move(name))
  {
  }

public:
  const std::string& name() const
  {
    return name_;
  }

private:
  const std::string name_;
};

} // namespace cppast

#endif /* AC0E36D5_D135_4787_BB9B_F3FB72DF023D */
