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

#include "utils.h"

#include <fstream>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

static CppToken classNameFromTemplatedIdentifier(const CppToken& identifier)
{
  auto rbeg = rev(identifier.sz + identifier.len);
  assert(*rbeg == '>');

  auto rend     = rev(identifier.sz);
  int  numTempl = 1;
  for (++rbeg; rbeg != rend; ++rbeg)
  {
    if (*rbeg == '<')
    {
      --numTempl;
      if (numTempl == 0)
      {
        CppToken clsName {identifier.sz, static_cast<size_t>(std::distance(rbeg, rend)) - 1};
        return clsName;
      }
    }
    else if (*rbeg == '>')
    {
      ++numTempl;
    }
  }

  return CppToken {nullptr, 0U};
}

CppToken classNameFromIdentifier(const CppToken& identifier)
{
  if (identifier.sz == nullptr)
    return identifier;

  if (identifier.sz[identifier.len - 1] == '>')
    return classNameFromTemplatedIdentifier(identifier);

  const char* scopeResolutor = "::";
  const char* end            = identifier.sz + identifier.len;
  auto        itr            = std::find_end(identifier.sz, end, scopeResolutor, scopeResolutor + 2);
  if (itr == end)
    return identifier;
  // skip white chars
  for (itr = itr + 2; (itr != end) && !isprint(*itr); ++itr)
    ;
  const auto clsNameLen = static_cast<size_t>(end - itr);
  return CppToken {itr, clsNameLen};
}

std::vector<char> readFile(const std::string& filename)
{
  std::vector<char> contents;
  std::ifstream     in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    in.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(in.tellg());
    contents.resize(size + 3); // For adding last 2 nulls and a new line.
    in.seekg(0, std::ios::beg);
    in.read(contents.data(), size);
    in.close();
    auto len = stripChar(contents.data(), size, '\r');
    assert(len <= size);
    contents.resize(len + 3);
    contents[len]     = '\n';
    contents[len + 1] = '\0';
    contents[len + 2] = '\0';
  }
  return contents;
}

void collectFiles(const fs::path& path, std::vector<std::string>& files, const CppProgFileSelecter& fileSelector)
{
  if (fs::is_regular_file(path))
  {
    auto file = path.string();
    if (fileSelector(file))
      files.push_back(std::move(file));
  }
  else if (fs::is_directory(path))
  {
    for (fs::directory_iterator dirItr(path); dirItr != fs::directory_iterator(); ++dirItr)
    {
      collectFiles(*dirItr, files, fileSelector);
    }
  }
}

std::vector<std::string> collectFiles(const std::string& folder, const CppProgFileSelecter& fileSelector)
{
  std::vector<std::string> files;
  collectFiles(folder, files, fileSelector);
  if (!files.empty())
    std::sort(files.begin(), files.end());

  return files;
}
