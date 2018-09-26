/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

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
