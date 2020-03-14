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

#include "cppconst.h"

#include <memory>

struct CppObj;

CppObjType objType(const CppObj* cppObj);

template <typename _TCppObj>
class CppEasyPtr
{
public:
  CppEasyPtr(_TCppObj* rawPtr)
    : ptr_(rawPtr)
  {
  }
  CppEasyPtr(const std::unique_ptr<_TCppObj>& ptr)
    : ptr_(ptr.get())
  {
  }

  template <typename = std::enable_if<!std::is_const<_TCppObj>::value>>
  CppEasyPtr(CppObj* rawPtr)
    : ptr_(nullptr)
  {
    if ((objType(rawPtr) == _TCppObj::kObjectType))
      ptr_ = static_cast<_TCppObj*>(rawPtr);
  }

  template <typename = std::enable_if<std::is_const<_TCppObj>::value>>
  CppEasyPtr(const CppObj* rawPtr)
    : ptr_(nullptr)
  {
    if ((objType(rawPtr) == _TCppObj::kObjectType))
      ptr_ = static_cast<_TCppObj*>(rawPtr);
  }

  template <typename _UCppObj>
  CppEasyPtr(const std::unique_ptr<_UCppObj>& ptr)
    : ptr_(nullptr)
  {
    if (ptr && (ptr->objType_ == _TCppObj::kObjectType))
      ptr_ = static_cast<_TCppObj*>(ptr.get());
  }

  _TCppObj* operator->() const
  {
    return ptr_;
  }

  operator bool() const
  {
    return ptr_ != nullptr;
  }

  operator _TCppObj*() const
  {
    return ptr_;
  }

  operator CppObj*() const
  {
    return ptr_;
  }

  operator const CppObj*() const
  {
    return ptr_;
  }

  template <typename _UCppObj>
  operator _UCppObj*() const
  {
    return _UCppObj::kObjectType == _TCppObj::kObjectType ? static_cast<_UCppObj*>(ptr_) : nullptr;
  }

  _TCppObj* get() const
  {
    return ptr_;
  }

private:
  _TCppObj* ptr_;
};
