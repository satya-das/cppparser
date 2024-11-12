// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef EFE82EA4_B16D_4385_B226_FC106C3F2839
#define EFE82EA4_B16D_4385_B226_FC106C3F2839

#include "cppast/cpp_entity.h"

#include <string>

namespace cppast {

class CppAsmBlock : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::ASM_BLOCK;
  }

public:
  CppAsmBlock(std::string asmBlock)
    : CppEntity(EntityType())
    , asm_(std::move(asmBlock))
  {
  }

public:
  /**
   * @brief The ASM code block.
   *
   * @return Entire asm block including keyword asm.
   */
  const std::string& code() const
  {
    return asm_;
  }

private:
  const std::string asm_;
};

} // namespace cppast

#endif /* EFE82EA4_B16D_4385_B226_FC106C3F2839 */
