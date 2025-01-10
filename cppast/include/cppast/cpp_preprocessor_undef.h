// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef E208389D_3833_42AC_97DA_384BF200EE7F
#define E208389D_3833_42AC_97DA_384BF200EE7F

#include "cppast/cpp_preprocessor.h"

namespace cppast {

class CppPreprocessorUndef : public CppPreprocessor
{
public:
  CppPreprocessorUndef(std::string name)
    : CppPreprocessor(CppPreprocessorType::UNDEF)
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

#endif /* E208389D_3833_42AC_97DA_384BF200EE7F */
