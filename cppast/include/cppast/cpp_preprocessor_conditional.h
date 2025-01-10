// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A21B28DB_1536_49E8_B573_458C95560210
#define A21B28DB_1536_49E8_B573_458C95560210

#include "cppast/cpp_preprocessor.h"

namespace cppast {

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
class CppPreprocessorConditional : public CppPreprocessor
{
public:
  CppPreprocessorConditional(PreprocessorConditionalType condType, std::string cond = std::string())
    : CppPreprocessor(CppPreprocessorType::CONDITIONAL)
    , condType_(condType)
    , cond_(std::move(cond))
  {
  }

public:
  PreprocessorConditionalType conditionalType() const
  {
    return condType_;
  }

  const std::string& condition() const
  {
    return cond_;
  }

private:
  PreprocessorConditionalType condType_;
  std::string                 cond_;
};

} // namespace cppast

#endif /* A21B28DB_1536_49E8_B573_458C95560210 */
