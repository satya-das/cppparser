/*
   The MIT License (MIT)

   Copyright (c) 2014

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */

#include "cppprog.h"

//////////////////////////////////////////////////////////////////////////

void CppProgram::addCppDom(CppCompound* cppDom)
{
  if (cppDom->compoundType_ != kCppFile)
    return;
  loadType(cppDom, &cppTypeTreeRoot_);
  fileDoms_.push_back(cppDom);
}

void CppProgram::loadType(CppCompound* cppCompound, CppTypeTreeNode* typeNode)
{
  if (cppCompound == NULL)
    return;
  if (cppCompound->isCppFile()) // Type node for file object should be the root itself.
  {
    cppObjToTypeNode_[cppCompound] = typeNode;
    typeNode->cppObjSet.insert(cppCompound);
  }
  for (CppObjArray::const_iterator itr = cppCompound->members_.begin(); itr != cppCompound->members_.end(); ++itr)
  {
    CppObj* mem = *itr;
    if (mem->objType_ == CppObj::kCompound)
    {
      CppTypeTreeNode& childNode = typeNode->children[((CppCompound*) mem)->name_];
      childNode.cppObjSet.insert(mem);
      childNode.parent       = typeNode;
      cppObjToTypeNode_[mem] = &childNode;
      loadType((CppCompound*) mem, &childNode);
    }
    else if (mem->objType_ == CppObj::kEnum)
    {
      CppTypeTreeNode& childNode = typeNode->children[((CppEnum*) mem)->name_];
      childNode.cppObjSet.insert(mem);
      childNode.parent       = typeNode;
      cppObjToTypeNode_[mem] = &childNode;
    }
    else if (mem->objType_ == CppObj::kTypedefName)
    {
      auto*            typedefName = static_cast<CppTypedefName*>(mem);
      CppTypeTreeNode& childNode   = typeNode->children[typedefName->var_->name()];
      childNode.cppObjSet.insert(mem);
      childNode.parent       = typeNode;
      cppObjToTypeNode_[mem] = &childNode;
    }
    else if (mem->objType_ == CppObj::kFunctionPtr)
    {
      CppTypeTreeNode& childNode = typeNode->children[((CppFunctionPtr*) mem)->name_];
      childNode.cppObjSet.insert(mem);
      childNode.parent       = typeNode;
      cppObjToTypeNode_[mem] = &childNode;
    }
  }
}

const CppTypeTreeNode* CppProgram::findTypeNode(const std::string& name, const CppTypeTreeNode* typeNode) const
{
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
