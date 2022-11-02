// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A21B28DB_1536_49E8_B573_458C95560210
#define A21B28DB_1536_49E8_B573_458C95560210

#include "cppast/cpp_entity.h"

namespace CppAst {

enum class PreprocessorConditionalType
{
  IF,
  IFDEF,
  IFNDEF,
  ELSE,
  ELIF,
  ENDIF,
};

/**
 * @brief Represents all variants of #if preprocessors.
 *
 * It includes #if, #ifdef, #ifndef.
 * It also includes #else, #elif, and #endif.
 */
class CppPreprocessorConditional : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::PREPROCESSOR_CONDITIONAL;
  }

public:
  CppPreprocessorConditional(PreprocessorConditionalType condType, std::string cond)
    : CppEntity(EntityType())
    , condType_(condType)
    , cond_(std::move(cond))
  {
  }

  PreprocessorConditionalType ConditionalType() const
  {
    return condType_;
  }

  const std::string& condition() const
  {
    return cond_;
  }

private:
  const PreprocessorConditionalType condType_;
  const std::string                 cond_;
};

} // namespace CppAst

#endif /* A21B28DB_1536_49E8_B573_458C95560210 */
