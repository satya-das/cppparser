// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BC97BFFF_ABE6_4D65_BB85_0BFE81A98146
#define BC97BFFF_ABE6_4D65_BB85_0BFE81A98146

#include "cppast/cpp_preprocessor.h"

namespace cppast {

class CppPreprocessorInclude : public CppPreprocessor
{
public:
  CppPreprocessorInclude(std::string name)
    : CppPreprocessor(CppPreprocessorType::INCLUDE)
    , name_(std::move(name))
  {
  }

public:
  const std::string& name() const
  {
    return name_;
  }

private:
  std::string name_;
};

} // namespace cppast

#endif /* BC97BFFF_ABE6_4D65_BB85_0BFE81A98146 */
