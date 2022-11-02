// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C5550546_B6DB_4E84_BDAF_2F464ECB56A2
#define C5550546_B6DB_4E84_BDAF_2F464ECB56A2

#include "cppast/cpp_entity.h"

namespace CppAst {

/**
 * @brief A stream of text that represents some content in a C++ program.
 */
class CppBlob : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::BLOB;
  }

public:
  CppBlob(std::string blob);

public:
  const std::string& Blob() const
  {
    return blob_;
  }

private:
  std::string blob_;
};

} // namespace CppAst

#endif /* C5550546_B6DB_4E84_BDAF_2F464ECB56A2 */
