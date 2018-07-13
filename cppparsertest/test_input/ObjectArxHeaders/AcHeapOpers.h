//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// AcHeapOpers.h - Provides the AcHeapOperators base class.  Use this
//              base class as a simple way to give your class local
//              new and delete operators.  It guarantees that the
//              objects will be created and destroyed on the same
//              heap (the acad heap) at all times.
//
#pragma once
#include "adesk.h"
#include "acheapmanager.h"

class AcHeapOperators {
    public:

#undef new
#undef delete
        static void* operator new(size_t size) {
            void *p = ::acHeapAlloc(nullptr,size);
            if (p)
                return p;
            ADESK_UNREACHABLE;
        }

        static void* operator new[](size_t size) {
            void *p = ::acHeapAlloc(nullptr, size);
            if (p)
                return p;
            ADESK_UNREACHABLE;
        }

        static void* operator new(size_t size, const char *,
                                  int)
        {
            void * p = ::acHeapAlloc(nullptr, size);
            if (p)
                return p;
            ADESK_UNREACHABLE;
        }

        static void* operator new[](size_t size,
                                    const char *, int )
        {
            void *p = ::acHeapAlloc(nullptr, size);
            if (p)
                return p;
            ADESK_UNREACHABLE;
        }

        static void operator delete(void *p) {   
            if(p != NULL)
                ::acHeapFree(nullptr, p);
        }

        static void operator delete[](void *p) {   
            if(p != NULL)
                ::acHeapFree(nullptr, p);
        }

        // Unicode: leaving pFName as char for now
        static void operator delete(void *p, const char *,
                                    int )
        {
            if (p != NULL)
                ::acHeapFree(nullptr, p);
        }

        static void operator delete[](void *p,
                                      const char *, int )
        {
            if (p != NULL)
                ::acHeapFree(nullptr, p );
        }

};  // AcHeapOperators
