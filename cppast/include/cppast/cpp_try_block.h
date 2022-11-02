// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BFF3C538_E8C8_40D9_8ADF_948EC6671390
#define BFF3C538_E8C8_40D9_8ADF_948EC6671390

#include "cppast/cpp_compound.h"
#include "cppast/cpp_entity.h"
#include "cppast/cpp_var_type.h"

#include <string>

namespace CppAst {

struct CppCatchBlock
{
  const std::unique_ptr<CppVarType>  exceptionType_;
  const std::string                  exceptionName_;
  const std::unique_ptr<CppCompound> catchStmt_;
};

using CppCatchBlockPtr = std::unique_ptr<CppCatchBlock>;

using CppCatchBlocks = std::vector<CppCatchBlockPtr>;

class CppTryBlock : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::TRY_BLOCK;
  }

  const std::unique_ptr<CppCompound> tryStmt_;

public:
  CppTryBlock(CppCompound* tryStmt, CppCatchBlock* firstCatchBlock)
    : CppEntity(EntityType())
    , tryStmt_(tryStmt)
  {
    catchBlocks_.emplace_back(firstCatchBlock);
  }

  void addCatchBlock(CppCatchBlock* catchBlock)
  {
    catchBlocks_.emplace_back(catchBlock);
  }

private:
  CppCatchBlocks catchBlocks_;
};

} // namespace CppAst

#endif /* BFF3C538_E8C8_40D9_8ADF_948EC6671390 */
