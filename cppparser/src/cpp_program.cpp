// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppparser/cpp_program.h"
#include "cppast/cppconst.h"

#include "utils.h"

#include <iostream>

namespace cppparser {

CppProgram::CppProgram(const std::vector<std::string>& files)
{
  cppEntityToTypeNode_[nullptr] = &cppTypeTreeRoot_;

  CppParser parser;
  for (const auto& f : files)
  {
    std::cout << "INFO\t Parsing '" << f << "'\n";
    auto cppAst = parser.parseFile(f.c_str());
    if (cppAst)
      addCppFile(std::move(cppAst));
  }
}

void CppProgram::addCompound(const cppast::CppCompound& compound, CppTypeTreeNode& parentTypeNode)
{
  if (compound.name().empty())
    return;
  auto& childNode = parentTypeNode.children[compound.name()];
  childNode.cppEntitySet.insert(&compound);
  childNode.parent                = &parentTypeNode;
  cppEntityToTypeNode_[&compound] = &childNode;
  loadType(compound, childNode);
}

void CppProgram::addCompound(const cppast::CppCompound& compound, const cppast::CppCompound& parent)
{
  auto itr = cppEntityToTypeNode_.find(&parent);
  if (itr != cppEntityToTypeNode_.end())
    addCompound(compound, *(itr->second));
}

void CppProgram::loadType(const cppast::CppCompound& cppCompound, CppTypeTreeNode& typeNode)
{
  if (IsCppFile(cppCompound)) // Type node for file object should be the root itself.
  {
    cppEntityToTypeNode_[&cppCompound] = &typeNode;
    typeNode.cppEntitySet.insert(&cppCompound);
  }
  cppCompound.visitAll([&](const cppast::CppEntity& mem) {
    if (IsCompound(mem))
    {
      addCompound(*static_cast<const cppast::CppCompound*>(&mem), typeNode);
    }
    else if (IsEnum(mem))
    {
      CppTypeTreeNode& childNode = typeNode.children[((cppast::CppEnum&) mem).name()];
      childNode.cppEntitySet.insert(&mem);
      childNode.parent           = &typeNode;
      cppEntityToTypeNode_[&mem] = &childNode;
    }
    else if (IsTypedefName(mem))
    {
      const auto&      typedefName = static_cast<const cppast::CppTypedefName&>(mem);
      CppTypeTreeNode& childNode   = typeNode.children[typedefName.var()->name()];
      childNode.cppEntitySet.insert(&mem);
      childNode.parent           = &typeNode;
      cppEntityToTypeNode_[&mem] = &childNode;
    }
    else if (IsUsingDecl(mem))
    {
      const auto&      usingDecl = static_cast<const cppast::CppUsingDecl&>(mem);
      CppTypeTreeNode& childNode = typeNode.children[usingDecl.name()];
      childNode.cppEntitySet.insert(&mem);
      childNode.parent           = &typeNode;
      cppEntityToTypeNode_[&mem] = &childNode;
    }
    else if (IsFunctionPtr(mem))
    {
      CppTypeTreeNode& childNode = typeNode.children[((const cppast::CppFunctionPointer&) mem).name()];
      childNode.cppEntitySet.insert(&mem);
      childNode.parent           = &typeNode;
      cppEntityToTypeNode_[&mem] = &childNode;
    }
    else if (IsFwdClsDecl(mem))
    {
      const auto& fwdCls = static_cast<const cppast::CppForwardClassDecl&>(mem);
      if (!(fwdCls.attr() & cppast::CppIdentifierAttrib::FRIEND))
      {
        CppTypeTreeNode& childNode = typeNode.children[fwdCls.name()];
        childNode.cppEntitySet.insert(&mem);
        childNode.parent           = &typeNode;
        cppEntityToTypeNode_[&mem] = &childNode;
      }
    }

    return false;
  });
}

const CppTypeTreeNode* CppProgram::nameLookup(const std::string& name, const CppTypeTreeNode* beginFrom) const
{
  if (name.empty())
    return &cppTypeTreeRoot_;
  auto*  typeNode   = beginFrom ? beginFrom : &cppTypeTreeRoot_;
  size_t nameBegPos = 0;
  size_t nameEndPos = name.find("::", nameBegPos);
  if (nameEndPos == std::string::npos)
  {
    for (; typeNode != nullptr; typeNode = typeNode->parent)
    {
      CppTypeTree::const_iterator itr = typeNode->children.find(name);
      if (itr != typeNode->children.end())
        return &itr->second;
    }
    return nullptr;
  }
  else
  {
    auto nameToLookFor = name.substr(nameBegPos, nameEndPos - nameBegPos);
    typeNode           = nameLookup(nameToLookFor, typeNode);
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

const CppTypeTreeNode* CppProgram::searchTypeNode(const std::string& name, const CppTypeTreeNode* parentNode) const
{
  std::vector<const CppTypeTreeNode*> nextLevelNodes(1, parentNode ? parentNode : &cppTypeTreeRoot_);

  do
  {
    std::vector<const CppTypeTreeNode*> currentLevelNodes;
    currentLevelNodes.swap(nextLevelNodes);
    assert(nextLevelNodes.empty());
    for (const auto* node : currentLevelNodes)
    {
      for (const auto& child : node->children)
      {
        if (child.first == name)
          return &(child.second);
        nextLevelNodes.push_back(&(child.second));
      }
    }
  } while (!nextLevelNodes.empty());

  return nullptr;
}

} // namespace cppparser
