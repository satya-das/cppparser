// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BFF3C538_E8C8_40D9_8ADF_948EC6671390
#define BFF3C538_E8C8_40D9_8ADF_948EC6671390

#include "cppast/cpp_compound.h"
#include "cppast/cpp_entity.h"
#include "cppast/cpp_var_type.h"

#include <string>

namespace cppast {

struct CppCatchBlock
{
  std::unique_ptr<CppVarType>  exceptionType_;
  std::string                  exceptionName_;
  std::unique_ptr<CppCompound> catchStmt_;
};

using CppCatchBlockPtr = std::unique_ptr<CppCatchBlock>;
using CppCatchBlocks   = std::vector<CppCatchBlockPtr>;

class CppTryBlock : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::TRY_BLOCK;
  }

public:
  CppTryBlock(std::unique_ptr<CppCompound> tryStmt, std::unique_ptr<CppCatchBlock> firstCatchBlock)
    : CppEntity(EntityType())
    , tryStmt_(std::move(tryStmt))
  {
    catchBlocks_.push_back(std::move(firstCatchBlock));
  }

public:
  void addCatchBlock(std::unique_ptr<CppCatchBlock> catchBlock)
  {
    catchBlocks_.emplace_back(std::move(catchBlock));
  }

private:
  std::unique_ptr<CppCompound> tryStmt_;
  CppCatchBlocks                     catchBlocks_;
};

} // namespace cppast

#endif /* BFF3C538_E8C8_40D9_8ADF_948EC6671390 */
