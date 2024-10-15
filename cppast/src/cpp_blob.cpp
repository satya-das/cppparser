// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppast/cpp_blob.h"

namespace cppast {

namespace {

/**
 * @brief Trims traling spaces and leading empty lines.
 */
std::string& trimBlob(std::string& s)
{
  auto len = s.size();

  for (; len > 0; --len)
  {
    if (!isspace(s[len - 1]))
      break;
  }
  s.resize(len);

  size_t start = 0;
  for (size_t i = 0; i < s.size(); ++i)
  {
    if (!isspace(s[i]))
      break;
    if (s[i] == '\n')
      start = i + 1;
  }

  if (start > 0)
    s = s.substr(start);
  return s;
}

} // namespace

CppBlob::CppBlob(std::string blob)
  : CppEntity(EntityType())
  , blob_(std::move(trimBlob(blob)))
{
}

} // namespace cppast
