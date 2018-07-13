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
// DESCRIPTION:
// Provides an interface for additional overloads to the global new.
// Implemented in gegbl.cpp
//

#ifndef AC_GEGBLNEW_H
#define AC_GEGBLNEW_H

#ifdef GE_LOCATED_NEW

#include "gegblge.h"
#include "gegetmti.h"

GE_DLLEXPIMPORT
void* operator new ( size_t, enum AcGe::metaTypeIndex, const void* );

GE_DLLEXPIMPORT
void* operator new ( size_t, enum AcGe::metaTypeIndex, unsigned int, const void* );

#define GENEWLOC( T, ptr)  new (AcGeGetMetaTypeIndex<T >(), (ptr)) T
#define GENEWLOCVEC( T, count, ptr) new (AcGeGetMetaTypeIndex<T >(),(count),(ptr)) T [ (count) ]
#else   //#ifdef GE_LOCATED_NEW
#define GENEWLOC( T, ptr)  new T
#define GENEWLOCVEC( T, count, ptr) new T [ (count) ]
#endif


#endif  // AC_GEGBLNEW_H