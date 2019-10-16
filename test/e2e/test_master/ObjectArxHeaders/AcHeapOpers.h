//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "adesk.h"
#include "acheapmanager.h"
class AcHeapOperators
{
#undef new
#undef delete
public:
  static void* operator new(size_t size)
  {
    void* p = ::acHeapAlloc(nullptr, size);
    if (p)
    {
      return p;
    }
    ADESK_UNREACHABLE;
  }
  static void* operator new[](size_t size)
  {
    void* p = ::acHeapAlloc(nullptr, size);
    if (p)
    {
      return p;
    }
    ADESK_UNREACHABLE;
  }
  static void* operator new(size_t size, const char*, int)
  {
    void* p = ::acHeapAlloc(nullptr, size);
    if (p)
    {
      return p;
    }
    ADESK_UNREACHABLE;
  }
  static void* operator new[](size_t size, const char*, int)
  {
    void* p = ::acHeapAlloc(nullptr, size);
    if (p)
    {
      return p;
    }
    ADESK_UNREACHABLE;
  }
  static void operator delete(void* p)
  {
    if (p != NULL)
    {
      ::acHeapFree(nullptr, p);
    }
  }
  static void operator delete[](void* p)
  {
    if (p != NULL)
    {
      ::acHeapFree(nullptr, p);
    }
  }
  static void operator delete(void* p, const char*, int)
  {
    if (p != NULL)
    {
      ::acHeapFree(nullptr, p);
    }
  }
  static void operator delete[](void* p, const char*, int)
  {
    if (p != NULL)
    {
      ::acHeapFree(nullptr, p);
    }
  }
};
