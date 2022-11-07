// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C10B82DE_558A_4D4C_B66A_2881DCFFCD3F
#define C10B82DE_558A_4D4C_B66A_2881DCFFCD3F

#include "cppast/cpp_entity.h"

namespace cppast {

class CppPreprocessorPragma : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_PRAGMA;
  }

public:
  CppPreprocessorPragma(std::string defn)
    : CppEntity(EntityType())
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
