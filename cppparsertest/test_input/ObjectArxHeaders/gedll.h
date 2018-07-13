//
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
//
// This module controls the exporting of symbols for the AcGe Dll.
// 

#ifndef AC_GEDLL_H
#define AC_GEDLL_H

#include "adesk.h"
#if defined(_MSC_VER)
#pragma warning(disable:4251)
#pragma warning(disable:4273)
#pragma warning(disable:4275)
#endif

#ifdef  ACGE_INTERNAL
#define GE_DLLEXPIMPORT __declspec(dllexport)
#define GE_DLLDATAEXIMP __declspec(dllexport)
#else
//don't use __declspec(dllimport) so that we can use the .objs with both static and dynamc linking
#define GE_DLLEXPIMPORT
//data must use __declspec(dllimport) but it causes no name mangling issues
#define GE_DLLDATAEXIMP __declspec(dllimport)
#endif

#ifdef  ACGX_INTERNAL
#define GX_DLLEXPIMPORT __declspec(dllexport)
#else
//don't use __declspec(dllimport) so that we can use the .objs with both static and dynamc linking
#define GX_DLLEXPIMPORT
#endif


#endif // AC_GEDLL_H
