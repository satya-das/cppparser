//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEDLL_H
#  define AC_GEDLL_H
#  include "adesk.h"
#  if  defined(_MSC_VER)
#    pragma  warning(disable:4251)
#    pragma  warning(disable:4273)
#    pragma  warning(disable:4275)
#  endif
#  ifdef ACGE_INTERNAL
#    define GE_DLLEXPIMPORT	__declspec(dllexport)
#    define GE_DLLDATAEXIMP	__declspec(dllexport)
#  else 
#    define GE_DLLEXPIMPORT
#    define GE_DLLDATAEXIMP	__declspec(dllimport)
#  endif
#  ifdef ACGX_INTERNAL
#    define GX_DLLEXPIMPORT	__declspec(dllexport)
#  else 
#    define GX_DLLEXPIMPORT
#  endif
#endif
