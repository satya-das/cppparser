// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BC27B3FD_816E_47DE_BCA2_0692BAE4F6DE
#define BC27B3FD_816E_47DE_BCA2_0692BAE4F6DE

#include "cppast/cpp_entity.h"

#include <map>
#include <set>
#include <string>

namespace cppparser {

struct CppTypeTreeNode;
/**
 * @brief Represents the tree of types in a C++ program.
 *
 * All C++ types of a program can be arranged in form of a tree.
 * The root of the tree is the global namespace which contains other compound objects like namespace, class, struct,
 * etc. And each of those compound object can form another branch of tree.
 *
 * @note This tree has no relation with inheritance hierarchy.
 */
using CppTypeTree = std::map<std::string, CppTypeTreeNode>;

struct CppEntityCmp
{
  bool operator()(const cppast::CppEntity* lhs, const cppast::CppEntity* rhs) const
  {
    if (lhs->entityType() < rhs->entityType())
      return true;
    if (lhs->entityType() > rhs->entityType())
      return false;
    return lhs < rhs;
  }
};

using CppEntitySet = std::set<const cppast::CppEntity*, CppEntityCmp>;

/**
 * @brief A node in a CppTypeTree.
 */
struct CppTypeTreeNode
{
  /**
   * @brief Set of all entities that have same name in the same scope.
   *
   * This needs to be a set because same namespace can be defined multiple times.
   * But members of all those definition will belong to single namespace.
   * Also, a class can be forward declared before full definition.
   */
  CppEntitySet     cppEntitySet;
  CppTypeTree      children;
  CppTypeTreeNode* parent;

  CppTypeTreeNode()
    : parent(nullptr)
  {
  }

  bool has(const cppast::CppEntity* cppEntity) const
  {
    if (cppEntitySet.count(cppEntity))
      return true;
    for (const auto child : children)
    {
      if (child.second.has(cppEntity))
        return true;
    }
    return false;
  }

  const cppast::CppEntity* getObjInSet(cppast::CppEntityType objType) const
  {
    for (const auto cppEntity : cppEntitySet)
    {
      if (cppEntity->entityType() == objType)
        return cppEntity;
    }

    return nullptr;
  }
};

} // namespace cppparser

#endif /* BC27B3FD_816E_47DE_BCA2_0692BAE4F6DE */
