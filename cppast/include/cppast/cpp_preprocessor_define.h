// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BE744AC2_52B3_46C4_A40D_9DB23E75A1F2
#define BE744AC2_52B3_46C4_A40D_9DB23E75A1F2

#include "cppast/cpp_preprocessor.h"

#include <string>

namespace cppast {

enum class CppPreprocessorDefineType
{
  RENAME,
  NUMBER,
  STRING,
  CHARACTER,
  COMPLEX_DEFN,
};

/**
 * @brief A macro definition.
 */
class CppPreprocessorDefine : public CppPreprocessor
{
public:
  CppPreprocessorDefine(CppPreprocessorDefineType defType, std::string name, std::string defn = std::string())
    : CppPreprocessor(CppPreprocessorType::DEFINE)
    , defType_(defType)
    , name_(std::move(name))
    , defn_(std::move(defn))
  {
  }

  CppPreprocessorDefineType definitionType() const
  {
    return defType_;
  }

  const std::string& name() const
  {
    return name_;
  }

  const std::string& definition() const
  {
    return defn_;
  }

private:
  const CppPreprocessorDefineType defType_;
  const std::string               name_;
  const std::string               defn_; ///< This will contain everything after name.
};

} // namespace cppast

#endif /* BE744AC2_52B3_46C4_A40D_9DB23E75A1F2 */
