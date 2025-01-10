// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B53E618A_F2E7_4C5F_A58E_4C1065A96113
#define B53E618A_F2E7_4C5F_A58E_4C1065A96113

#include "cppast/cpp_preprocessor.h"

namespace cppast {

/**
 * Any other C/C++ preprocessor for which there is no
 * class defined yet.
 */
class CppPreprocessorUnrecognized : public CppPreprocessor
{
public:
  CppPreprocessorUnrecognized(std::string name, std::string defn)
    : CppPreprocessor(CppPreprocessorType::UNRECOGNIZED)
    , name_(std::move(name))
    , defn_(std::move(defn))
  {
  }

public:
  const std::string& name() const
  {
    return name_;
  }

  const std::string& definition() const
  {
    return defn_;
  }

private:
  std::string name_;
  std::string defn_;
};

} // namespace cppast

#endif /* B53E618A_F2E7_4C5F_A58E_4C1065A96113 */
