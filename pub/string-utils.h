#pragma once

#include <algorithm>
#include <string>
#include <cstring>

inline size_t stripChar(char* s, size_t len, char c)
{
  auto* end = std::remove(s, s+len, c);
  return end - s;
}

inline void stripChar(std::string& s, char c)
{
  auto len = stripChar(&s[0], s.length(), c);
  s.resize(len);
}

//! strips new-line char and collapses multiple white chars.
inline std::string& cleanseIdentifier(std::string& id)
{
  stripChar(id, '\n');
  auto end = std::unique(id.begin(), id.end(), [](char c1, char c2) {
    return ((c1 == ' ' && c2 == ' ') || (c1 == '\t' && c2 == '\t') || (c1 == ' ' && c2 == '\t') || (c1 == '\t' && c2 == ' '));
  });
  id.resize(end - id.begin());
  std::replace(id.begin(), id.end(), '\t', ' ');

  return id;
}
