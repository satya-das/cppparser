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

#include <map>
#include <set>

struct CppTypeTreeNode;
/**
 * \brief Represents the tree of types in a C++ program.
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
  bool operator()(const CppObj* lhs, const CppObj* rhs) const
  {
    if (lhs->objType_ < rhs->objType_)
      return true;
    if (lhs->objType_ > rhs->objType_)
      return false;
    return lhs < rhs;
  }
};

using CppObjSet = std::set<const CppObj*, CppObjSetCmp>;
/**
 * \brief A node in a CppTypeTree.
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

  bool has(const CppObj* cppObj) const
  {
    if (cppObjSet.count(cppObj))
      return true;
    for (const auto child : children)
    {
      if (child.second.has(cppObj))
        return true;
    }
    return false;
  }
};
