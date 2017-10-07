/*
The MIT License (MIT)

Copyright (c) 2014

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

#ifndef __CPPPROG_H__
#define __CPPPROG_H__

#include "cppdom.h"

#include <map>
#include <vector>
#include <set>

///////////////////////////////////////////////////////////////////////////////////////////////////


struct CppTypeTreeNode;
/**
 * \brief Represents the tree of C++ types.
 * All C++ types of a program can be arranged in a form of tree.
 * The root of the tree is the global namespace which contains other compound objects like namespace, class, struct, etc.
 * And each of those compound object can form another branch of tree.
 * \note This tree has no relation with inheritance hierarchy.
 */
typedef std::map<std::string, CppTypeTreeNode> CppTypeTree;

typedef std::set<CppObj*> CppObjSet;
/**
 * \brief A node in a CppTypeTree.
 */
struct CppTypeTreeNode
{
  /**
   * This needs to be a set because same namespace can be defined multiple times.
   * But members of all those definition will belong to single namespace.
   */
  CppObjSet           cppObjSet;
  CppTypeTree         children;
  CppTypeTreeNode*    parent;

  CppTypeTreeNode() : parent(NULL) {}
};

typedef std::vector<CppCompound*> CppCompoundArray;

/**
 * \brief Represents an entire C++ program.
 */
class CppProgram
{
public:
  CppProgram();
  CppProgram(const char* szInputPath);

public:
  /**
   * Loads C++ program from source and header files.
   * @param inputPath Folder where the C++ files are present.
   */
  void loadProgram(const char* szInputPath);
  /**
   * Adds a new file DOM to this program.
   * \warning It is a no-op if \a cppDom is not of kCppFile type.
   */
  void addCppDom(CppCompound* cppDom);
  /**
   * Finds the CppTypeTreeNode object corresponding to a given name.
   * @param name Name of type for which CppTypeTreeNode needs to be found.
   * @param beginFrom CppTypeTreeNode object from where the search should begin.
   * @return CppTypeTreeNode corresponding to given name.
   * \note Name can contain scope resolution operator(::).
  * \remarks The search moves upward. E.g. if \a beginFrom does not contain the type whose name is \a name then
  * it is searched in parent node and keeps moving upward till a match is found or type-hierarchy ends without a match.
   */
  const CppTypeTreeNode* findTypeNode(const std::string& name, const CppTypeTreeNode* beginFrom) const;
  /**
   * @return CppTypeTreeNode for CppObj.
   * \note Return value may be NULL if CppObj does not represent a valid type.
   */
  const CppTypeTreeNode* typeTreeNodeFromCppObj(const CppObj* cppObj) const;
  /**
   * @return An array of CppCompoundObj each element of which represents DOM of a C++ file.
   */
  const CppCompoundArray& getFileDOMs() const;

protected:
  /**
   * Parses all CPP files and creates CPPDOM for all of them.
   */
  void loadCppDom(const char* szInputPath);
  void loadType(CppCompound* cppCompound, CppTypeTreeNode* typeNode);

protected:
  typedef std::map<const CppObj*, const CppTypeTreeNode*> CppObjToTypeNodeMap;

  CppCompoundArray		fileDoms_;              ///< Array of all top level DOMs corresponding to files.
  CppTypeTreeNode         cppTypeTreeRoot_;       ///< Repository of all compound objects arranged as type-tree.
  mutable CppObjToTypeNodeMap     cppObjToTypeNode_;
};

inline CppProgram::CppProgram()
{
  cppObjToTypeNode_[NULL] = &cppTypeTreeRoot_;
}

inline CppProgram::CppProgram(const char* szInputPath)
{
  cppObjToTypeNode_[NULL] = &cppTypeTreeRoot_;
  loadProgram(szInputPath);
}

inline const CppCompoundArray& CppProgram::getFileDOMs() const
{
  return fileDoms_;
}

inline const CppTypeTreeNode* CppProgram::typeTreeNodeFromCppObj(const CppObj* cppObj) const
{
  CppObjToTypeNodeMap::const_iterator itr = cppObjToTypeNode_.find(cppObj);
  return itr == cppObjToTypeNode_.end() ? NULL : itr->second;
}

#endif //__CPPPROG_H__
