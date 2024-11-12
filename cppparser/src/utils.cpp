// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "utils.h"
#include "cppparser/string-utils.h"

#include <filesystem>

#include <cassert>
#include <fstream>

namespace fs = std::filesystem;

static CppToken ClassNameFromTemplatedIdentifier(const CppToken& identifier)
{
  auto rbeg = std::reverse_iterator(identifier.sz + identifier.len);
  assert(*rbeg == '>');

  auto rend     = std::reverse_iterator(identifier.sz);
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

CppToken ClassNameFromIdentifier(const CppToken& identifier)
{
  if (identifier.sz == nullptr)
    return identifier;

  if (identifier.sz[identifier.len - 1] == '>')
    return ClassNameFromIdentifier(ClassNameFromTemplatedIdentifier(identifier));

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

std::string ReadFile(const std::string& filename)
{
  std::string   contents;
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    in.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(in.tellg());
    contents.resize(size + 3); // For adding last 2 nulls and a new line.
    in.seekg(0, std::ios::beg);
    in.read(contents.data(), size);
    in.close();
    auto len = StripChar(contents.data(), size, '\r');
    assert(len <= size);
    contents.resize(len + 3);
    contents[len]     = '\n';
    contents[len + 1] = '\0';
    contents[len + 2] = '\0';
  }
  return contents;
}

// void collectFiles(std::vector<std::string>& files, const fs::path& path, const CppProgFileSelecter& fileSelector)
// {
//   if (fs::is_regular_file(path))
//   {
//     auto file = path.string();
//     if (fileSelector(file))
//       files.push_back(std::move(file));
//   }
//   else if (fs::is_directory(path))
//   {
//     for (fs::directory_iterator dirItr(path); dirItr != fs::directory_iterator(); ++dirItr)
//     {
//       collectFiles(files, *dirItr, fileSelector);
//     }
//   }

//   if (!files.empty())
//     std::sort(files.begin(), files.end());
// }

std::vector<CppToken> Explode(CppToken token, const char* delim)
{
  auto const            delimLen = strlen(delim);
  std::vector<CppToken> elems;

  for (auto* p = token.sz; p < (token.sz + token.len);)
  {
    auto* q = strstr(p, delim);
    if (q != nullptr)
    {
      elems.push_back(CppToken {p, static_cast<size_t>(q - p)});
      p = q + delimLen;
    }
    else
    {
      elems.push_back(CppToken {p, static_cast<size_t>(token.sz + token.len - p)});
      break;
    }
  }

  return elems;
}

std::string PruneClassName(const CppToken& identifier)
{
  std::string ret;
  for (size_t i = 0; i < identifier.len; ++i)
  {
    if (isprint(identifier.sz[i]))
      ret += identifier.sz[i];
  }

  return ret;
}