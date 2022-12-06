// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef F8A152FE_69F0_410B_B54E_2A4F85280520
#define F8A152FE_69F0_410B_B54E_2A4F85280520

#include "cppparser/cpp_type_tree.h"
#include "cppparser/cppparser.h"

#include <functional>
#include <map>
#include <set>
#include <vector>

namespace cppparser {

/**
 * @brief Represents an entire C++ program.
 */
class CppProgram
{
public:
  CppProgram(const std::vector<std::string>& files);

public:
  /**
   * Adds a new file AST to this program.
   * @warning It is a no-op if @a cppAst is not of CppCompoundType::FILE type.
   */
  void addCppFile(std::unique_ptr<cppast::CppCompound> cppAst);
  void addCompound(const cppast::CppCompound& compound, const cppast::CppCompound& parent);
  void addCompound(const cppast::CppCompound& compound, CppTypeTreeNode& parentTypeNode);

  /**
   * Finds the CppTypeTreeNode object corresponding to a given name.
   * @param name Name of type for which CppTypeTreeNode needs to be found.
   * @param beginFrom CppTypeTreeNode object from where the find should begin. It can be nullptr, in that case the
   * global space is looked for the name.
   * @return CppTypeTreeNode corresponding to given name.
   * @note Name can contain scope resolution operator(::).
   * @remarks
   *    1. The search moves upward. E.g. if @a beginFrom does not contain the type whose name is @a name then
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
   * @note Name should NOT contain scope resolution operator(::).
   * @remarks The search moves downward. E.g. if @a parentNode does not contain the type whose name is @a name then
   * it is searched in child nodes and keeps going downwards till a match is found or type-hierarchy ends without a
   * match.
   */
  const CppTypeTreeNode* searchTypeNode(const std::string& name, const CppTypeTreeNode* parentNode = nullptr) const;
  /**
   * @return CppTypeTreeNode for cppast::CppEntity.
   * @note Return value may be nullptr if cppast::CppEntity does not represent a valid type.
   */
  const CppTypeTreeNode* typeTreeNodeFromCppEntity(const cppast::CppEntity* cppEntity) const;
  /**
   * @return An array of cppast::CppCompound each element of which represents AST of a C++ file.
   */
  const std::vector<std::unique_ptr<cppast::CppCompound>>& getFileAsts() const;

private:
  void loadType(const cppast::CppCompound& cppCompound, CppTypeTreeNode& typeNode);

private:
  using CppEntityToTypeNodeMap = std::map<const cppast::CppEntity*, CppTypeTreeNode*>;

  std::vector<std::unique_ptr<cppast::CppCompound>> fileAsts_; ///< Array of all top level ASTs corresponding to files.
  CppTypeTreeNode        cppTypeTreeRoot_; ///< Repository of all compound objects arranged as type-tree.
  CppEntityToTypeNodeMap cppEntityToTypeNode_;
};

inline const std::vector<std::unique_ptr<cppast::CppCompound>>& CppProgram::getFileAsts() const
{
  return fileAsts_;
}

inline const CppTypeTreeNode* CppProgram::typeTreeNodeFromCppEntity(const cppast::CppEntity* cppEntity) const
{
  CppEntityToTypeNodeMap::const_iterator itr = cppEntityToTypeNode_.find(cppEntity);
  return itr == cppEntityToTypeNode_.end() ? nullptr : itr->second;
}

} // namespace cppparser

#endif /* F8A152FE_69F0_410B_B54E_2A4F85280520 */
