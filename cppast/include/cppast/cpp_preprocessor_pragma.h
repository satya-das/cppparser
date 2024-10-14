// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C10B82DE_558A_4D4C_B66A_2881DCFFCD3F
#define C10B82DE_558A_4D4C_B66A_2881DCFFCD3F

#include "cppast/cpp_preprocessor.h"

namespace cppast {

class CppPreprocessorPragma : public CppPreprocessor
{
public:
  CppPreprocessorPragma(std::string defn)
    : CppPreprocessor(CppPreprocessorType::PRAGMA)
    , defn_(std::move(defn))
  {
  }

public:
  const std::string& definition() const
  {
    return defn_;
  }

private:
  const std::string defn_;
};

} // namespace cppast

#endif /* C10B82DE_558A_4D4C_B66A_2881DCFFCD3F */
