// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef D8D07072_99E2_4590_8529_DC100184F9BB
#define D8D07072_99E2_4590_8529_DC100184F9BB

#include <algorithm>
#include <cstring>
#include <string>

inline size_t StripChar(char* s, size_t len, char c)
{
  auto* end = std::remove(s, s + len, c);
  return end - s;
}

inline void StripChar(std::string& s, char c)
{
  auto len = StripChar(&s[0], s.length(), c);
  s.resize(len);
}

inline std::string& TrimBlob(std::string& s)
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
inline std::string& CleanseIdentifier(std::string& id)
{
  StripChar(id, '\n');
  auto end = std::unique(id.begin(), id.end(), [](char c1, char c2) {
    return ((c1 == ' ' && c2 == ' ') || (c1 == '\t' && c2 == '\t') || (c1 == ' ' && c2 == '\t')
            || (c1 == '\t' && c2 == ' '));
  });
  id.resize(end - id.begin());
  std::replace(id.begin(), id.end(), '\t', ' ');

  return id;
}

#endif /* D8D07072_99E2_4590_8529_DC100184F9BB */
