// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DB1B2C8A_BCA8_4701_A6B5_A7E02B37D32C
#define DB1B2C8A_BCA8_4701_A6B5_A7E02B37D32C

#include "cppast/cpp_entity.h"

namespace cppast {

class CppPreprocessorWarning : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_WARNING;
  }

public:
  CppPreprocessorWarning(std::string warningStr)
    : CppEntity(EntityType())
    , warning_(std::move(warningStr))
  {
  }

public:
  const std::string& warning() const
  {
    return warning_;
  }

private:
  const std::string warning_;
};

} // namespace cppast

#endif /* DB1B2C8A_BCA8_4701_A6B5_A7E02B37D32C */
