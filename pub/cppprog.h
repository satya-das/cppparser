// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef D8B20A09_BD42_492D_8308_D43A463BD5C2
#define D8B20A09_BD42_492D_8308_D43A463BD5C2

#include "cppast/cppast.h"
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

using CppCompoundArray    = std::vector<std::unique_ptr<CppCompound>>;
using CppProgFileSelecter = std::function<bool(const std::string&)>;

/**
 * @brief Represents an entire C++ program.
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
   * @return CppTypeTreeNode for CppEntity.
   * \note Return value may be nullptr if CppEntity does not represent a valid type.
   */
  const CppTypeTreeNode* typeTreeNodeFromCppObj(const CppEntity* cppEntity) const;
  /**
   * @return An array of CppCompound each element of which represents AST of a C++ file.
   */
  const CppCompoundArray& getFileAsts() const;

public:
  /**
   * Adds a new file AST to this program.
   * \warning It is a no-op if \a cppAst is not of CppCompoundType::FILE type.
   */
  void addCppAst(std::unique_ptr<CppCompound> cppAst);
  void addCompound(const CppCompound* compound, const CppCompound* parent);
  void addCompound(const CppCompound* compound, CppTypeTreeNode* parentTypeNode);

private:
  void loadType(const CppCompound* cppCompound, CppTypeTreeNode* typeNode);

private:
  using CppObjToTypeNodeMap = std::map<const CppEntity*, CppTypeTreeNode*>;

  CppCompoundArray    fileAsts_;        ///< Array of all top level ASTs corresponding to files.
  CppTypeTreeNode     cppTypeTreeRoot_; ///< Repository of all compound objects arranged as type-tree.
  CppObjToTypeNodeMap cppObjToTypeNode_;
};

inline const CppCompoundArray& CppProgram::getFileAsts() const
{
  return fileAsts_;
}

inline const CppTypeTreeNode* CppProgram::typeTreeNodeFromCppObj(const CppEntity* cppEntity) const
{
  CppObjToTypeNodeMap::const_iterator itr = cppObjToTypeNode_.find(cppEntity);
  return itr == cppObjToTypeNode_.end() ? nullptr : itr->second;
}

#endif /* D8B20A09_BD42_492D_8308_D43A463BD5C2 */
