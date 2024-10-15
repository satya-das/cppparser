// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B40BB001_B9E3_4D83_8F99_6BD123813A0F
#define B40BB001_B9E3_4D83_8F99_6BD123813A0F

#include "cppast/cpp_entity.h"

namespace cppast {

enum class CppPreprocessorType
{
  DEFINE,
  UNDEF,
  CONDITIONAL,
  INCLUDE,
  IMPORT,
  WARNING,
  ERROR,
  LINE,
  PRAGMA,
  UNRECOGNIZED,
};

/**
 * @brief Base class for all preprocessor directives.
 */
class CppPreprocessor : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR;
  }

public:
  CppPreprocessorType preprocessorType() const
  {
    return preprocessorType_;
  }

protected:
  CppPreprocessor(CppPreprocessorType preprocessorType)
    : CppEntity(EntityType())
    , preprocessorType_(preprocessorType)
  {
  }

private:
  const CppPreprocessorType preprocessorType_;
};

} // namespace cppast

#endif /* B40BB001_B9E3_4D83_8F99_6BD123813A0F */
