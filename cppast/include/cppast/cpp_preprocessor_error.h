// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DC791634_A5B8_43D9_AEAB_43092F1830EE
#define DC791634_A5B8_43D9_AEAB_43092F1830EE

#include "cppast/cpp_preprocessor.h"

namespace cppast {

class CppPreprocessorError : public CppPreprocessor
{
public:
  CppPreprocessorError(std::string err)
    : CppPreprocessor(CppPreprocessorType::ERROR)
    , err_(std::move(err))
  {
  }

public:
  const std::string& error() const
  {
    return err_;
  }

private:
  std::string err_;
};

} // namespace cppast

#endif /* DC791634_A5B8_43D9_AEAB_43092F1830EE */
