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

#include "cppprog.h"
#include "cpputil.h"
#include "utils.h"

#include "cppcompound-accessor.h"
#include "cppfunc-accessor.h"
#include "cppobj-accessor.h"
#include "cppvar-accessor.h"

//////////////////////////////////////////////////////////////////////////

CppProgram::CppProgram(const std::string& folder, CppParser parser)
  : parser_(std::move(parser))
{
  cppObjToTypeNode_[nullptr] = &cppTypeTreeRoot_;

  auto files = collectFiles(folder);
  for (const auto& f : files)
  {
    auto cppAst = parser_.parseFile(f.c_str());
    if (cppAst)
      addCppAst(std::move(cppAst));
  }
}

void CppProgram::addCppAst(CppCompoundPtr cppAst)
{
  if (!isCppFile(cppAst.get()))
    return;
  loadType(cppAst.get(), &cppTypeTreeRoot_);
  fileAsts_.emplace_back(std::move(cppAst));
}

void CppProgram::addCompound(const CppCompound* compound, CppTypeTreeNode* parentTypeNode)
{
  if (compound->name().empty())
    return;
  auto& childNode = parentTypeNode->children[compound->name()];
  childNode.cppObjSet.insert(compound);
  childNode.parent            = parentTypeNode;
  cppObjToTypeNode_[compound] = &childNode;
  loadType(compound, &childNode);
}

void CppProgram::addCompound(const CppCompound* compound, const CppCompound* parent)
{
  auto itr = cppObjToTypeNode_.find(parent);
  if (itr != cppObjToTypeNode_.end())
    addCompound(compound, itr->second);
}

void CppProgram::loadType(const CppCompound* cppCompound, CppTypeTreeNode* typeNode)
{
  if (cppCompound == NULL)
    return;
  if (isCppFile(cppCompound)) // Type node for file object should be the root itself.
  {
    cppObjToTypeNode_[cppCompound] = typeNode;
    typeNode->cppObjSet.insert(cppCompound);
  }
  forEachMember(cppCompound, [&](const CppObj* mem) {
    if (isCompound(mem))
    {
      addCompound((CppCompound*) mem, typeNode);
    }
    else if (isEnum(mem))
    {
      CppTypeTreeNode& childNode = typeNode->children[((CppEnum*) mem)->name_];
      childNode.cppObjSet.insert(mem);
      childNode.parent       = typeNode;
      cppObjToTypeNode_[mem] = &childNode;
    }
    else if (isTypedefName(mem))
    {
      auto*            typedefName = static_cast<const CppTypedefName*>(mem);
      CppTypeTreeNode& childNode   = typeNode->children[typedefName->var_->name()];
      childNode.cppObjSet.insert(mem);
      childNode.parent       = typeNode;
      cppObjToTypeNode_[mem] = &childNode;
    }
    else if (isFunctionPtr(mem))
    {
      CppTypeTreeNode& childNode = typeNode->children[((CppFunctionPtr*) mem)->name_];
      childNode.cppObjSet.insert(mem);
      childNode.parent       = typeNode;
      cppObjToTypeNode_[mem] = &childNode;
    }
    else if (isFwdClsDecl(mem))
    {
      auto* fwdCls = static_cast<const CppFwdClsDecl*>(mem);
      if (!(fwdCls->attr() & kFriend))
      {
        CppTypeTreeNode& childNode = typeNode->children[((CppFwdClsDecl*) mem)->name_];
        childNode.cppObjSet.insert(mem);
        childNode.parent       = typeNode;
        cppObjToTypeNode_[mem] = &childNode;
      }
    }

    return false;
  });
}

const CppTypeTreeNode* CppProgram::findTypeNode(const std::string& name, const CppTypeTreeNode* typeNode) const
{
  if (name.empty())
    return &cppTypeTreeRoot_;
  size_t nameBegPos = 0;
  size_t nameEndPos = name.find("::", nameBegPos);
  if (nameEndPos == std::string::npos)
  {
    for (; typeNode != NULL; typeNode = typeNode->parent)
    {
      CppTypeTree::const_iterator itr = typeNode->children.find(name);
      if (itr != typeNode->children.end())
        return &itr->second;
    }
    return NULL;
  }
  else
  {
    auto nameToLookFor = name.substr(nameBegPos, nameEndPos - nameBegPos);
    typeNode           = findTypeNode(nameToLookFor, typeNode);
    if (!typeNode)
      return nullptr;
    do
    {
      nameBegPos = nameEndPos + 2;
      nameEndPos = name.find("::", nameBegPos);
      if (nameEndPos == std::string::npos)
        nameEndPos = name.length();
      nameToLookFor = name.substr(nameBegPos, nameEndPos - nameBegPos);
      auto itr      = typeNode->children.find(nameToLookFor);
      if (itr == typeNode->children.end())
        return nullptr;
      typeNode = &itr->second;
    } while (nameEndPos < name.length());
  }
  return typeNode;
}
