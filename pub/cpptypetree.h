// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BEBA8047_52F7_451B_A20B_5C9717491FDD
#define BEBA8047_52F7_451B_A20B_5C9717491FDD

#include "cppast/cppast.h"

#include <map>
#include <set>

struct CppTypeTreeNode;
/**
 * @brief Represents the tree of types in a C++ program.
 *
 * All C++ types of a program can be arranged in form of a tree.
 * The root of the tree is the global namespace which contains other compound objects like namespace, class, struct,
 * etc. And each of those compound object can form another branch of tree.
 *
 * \note This tree has no relation with inheritance hierarchy.
 */
using CppTypeTree = std::map<std::string, CppTypeTreeNode>;

struct CppObjSetCmp
{
  bool operator()(const CppEntity* lhs, const CppEntity* rhs) const
  {
    if (lhs->objType_ < rhs->objType_)
      return true;
    if (lhs->objType_ > rhs->objType_)
      return false;
    return lhs < rhs;
  }
};

using CppObjSet = std::set<const CppEntity*, CppObjSetCmp>;
/**
 * @brief A node in a CppTypeTree.
 */
struct CppTypeTreeNode
{
  /**
   * This needs to be a set because same namespace can be defined multiple times.
   * But members of all those definition will belong to single namespace.
   * Also, a class can be forward declared before full definition.
   */
  CppObjSet        cppObjSet;
  CppTypeTree      children;
  CppTypeTreeNode* parent;

  CppTypeTreeNode()
    : parent(nullptr)
  {
  }

  bool has(const CppEntity* cppEntity) const
  {
    if (cppObjSet.count(cppEntity))
      return true;
    for (const auto child : children)
    {
      if (child.second.has(cppEntity))
        return true;
    }
    return false;
  }

  const CppEntity* getObjInSet(CppEntityType objType) const
  {
    for (const auto obj : cppObjSet)
    {
      if (obj->objType_ == objType)
        return obj;
    }

    return nullptr;
  }
};

#endif /* BEBA8047_52F7_451B_A20B_5C9717491FDD */
