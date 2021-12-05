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

#include "cppast.h"
#include "cppparser.h"
#include "cpptypetree.h"

#include <functional>
#include <map>
#include <set>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////

inline bool selectAllFiles(const std::string& file)
{
  return true;
}

inline bool selectHeadersOnly(const std::string& file)
{
  const auto dotPos           = file.rfind('.');
  const auto dotNotFound      = (dotPos == file.npos);
  const auto dotIsTheLastChar = (dotPos == (file.length() - 1));
  if (dotNotFound || dotIsTheLastChar)
    return false;
  return file[dotPos + 1] == 'h';
}

using CppCompoundArray    = std::vector<CppCompoundPtr>;
using CppProgFileSelecter = std::function<bool(const std::string&)>;

/**
 * \brief Represents an entire C++ program.
 */
class CppProgram
{
public:
  CppProgram(const std::string&         folder,
             CppParser                  parser       = CppParser(),
             const CppProgFileSelecter& fileSelector = selectHeadersOnly);
  CppProgram(const std::vector<std::string>& files, CppParser parser = CppParser());

public:
  /**
   * Finds the CppTypeTreeNode object corresponding to a given name.
   * @param name Name of type for which CppTypeTreeNode needs to be found.
   * @param beginFrom CppTypeTreeNode object from where the find should begin. It can be nullptr, in that case the
   * global space is looked for the name.
   * @return CppTypeTreeNode corresponding to given name.
   * \note Name can contain scope resolution operator(::).
   * \remarks
   *    1. The search moves upward. E.g. if \a beginFrom does not contain the type whose name is \a name then
   * it is searched in parent node and keeps moving upward till a match is found or type-hierarchy ends without a match.
   *    2. It is supposed to work exactly like how compiler looks for name.
   */
  const CppTypeTreeNode* nameLookup(const std::string& name, const CppTypeTreeNode* beginFrom = nullptr) const;
  /**
   * Searches down (in breadth first manner) the CppTypeTreeNode object corresponding to a given name.
   * @param name Name of type for which CppTypeTreeNode needs to be found.
   * @param parentNode CppTypeTreeNode object from where the search should begin. It can be nullptr, in that case search
   * starts from the top.
   * @return CppTypeTreeNode corresponding to given name.
   * \note Name should NOT contain scope resolution operator(::).
   * \remarks The search moves downward. E.g. if \a parentNode does not contain the type whose name is \a name then
   * it is searched in child nodes and keeps going downwards till a match is found or type-hierarchy ends without a
   * match.
   */
  const CppTypeTreeNode* searchTypeNode(const std::string& name, const CppTypeTreeNode* parentNode = nullptr) const;
  /**
   * @return CppTypeTreeNode for CppObj.
   * \note Return value may be nullptr if CppObj does not represent a valid type.
   */
  const CppTypeTreeNode* typeTreeNodeFromCppObj(const CppObj* cppObj) const;
  /**
   * @return An array of CppCompound each element of which represents AST of a C++ file.
   */
  const CppCompoundArray& getFileAsts() const;

public:
  /**
   * Adds a new file AST to this program.
   * \warning It is a no-op if \a cppAst is not of CppCompoundType::kCppFile type.
   */
  void addCppAst(CppCompoundPtr cppAst);
  void addCompound(const CppCompound* compound, const CppCompound* parent);
  void addCompound(const CppCompound* compound, CppTypeTreeNode* parentTypeNode);

private:
  void loadType(const CppCompound* cppCompound, CppTypeTreeNode* typeNode);

private:
  using CppObjToTypeNodeMap = std::map<const CppObj*, CppTypeTreeNode*>;

  CppCompoundArray    fileAsts_;        ///< Array of all top level ASTs corresponding to files.
  CppTypeTreeNode     cppTypeTreeRoot_; ///< Repository of all compound objects arranged as type-tree.
  CppObjToTypeNodeMap cppObjToTypeNode_;
  CppParser           parser_;
};

inline const CppCompoundArray& CppProgram::getFileAsts() const
{
  return fileAsts_;
}

inline const CppTypeTreeNode* CppProgram::typeTreeNodeFromCppObj(const CppObj* cppObj) const
{
  CppObjToTypeNodeMap::const_iterator itr = cppObjToTypeNode_.find(cppObj);
  return itr == cppObjToTypeNode_.end() ? nullptr : itr->second;
}
