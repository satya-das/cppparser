// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef B09C29E3_A08A_413A_9D05_260FA9E0C1F0
#define B09C29E3_A08A_413A_9D05_260FA9E0C1F0

#include <algorithm>
#include <cstring>
#include <string>

inline size_t stripChar(char* s, size_t len, char c)
{
  auto* end = std::remove(s, s + len, c);
  return end - s;
}

inline void stripChar(std::string& s, char c)
{
  auto len = stripChar(&s[0], s.length(), c);
  s.resize(len);
}

inline std::string& trimBlob(std::string& s)
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

//! strips new-line char and collapses multiple white chars.
inline std::string& cleanseIdentifier(std::string& id)
{
  stripChar(id, '\n');
  auto end = std::unique(id.begin(), id.end(), [](char c1, char c2) {
    return ((c1 == ' ' && c2 == ' ') || (c1 == '\t' && c2 == '\t') || (c1 == ' ' && c2 == '\t')
            || (c1 == '\t' && c2 == ' '));
  });
  id.resize(end - id.begin());
  std::replace(id.begin(), id.end(), '\t', ' ');

  return id;
}

#endif /* B09C29E3_A08A_413A_9D05_260FA9E0C1F0 */
