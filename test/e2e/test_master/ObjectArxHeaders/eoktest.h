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
#include "acadstrc.h"
#include "acestext.h"
#include "acutasrt.h"
#ifdef NDEBUG
#  define eOkTest(x)	 ((x) == Acad::eOk)
#  define eOkCheck(x)	 (x)
#  define eOkVerify(x)	 ((x) == Acad::eOk)
#else 
inline Acad::ErrorStatus eOkCheck_imp(const ACHAR* condition, const ACHAR* fname, int lineno, Acad::ErrorStatus es)
{
  if (es != Acad::eOk)
  {
    acutAssertMessage(condition, fname, lineno, acadErrorStatusText(es));
  }
  return es;
}
/// <summary>
/// Evaluates to true if value is Acad::eOk, otherwise evaluates to false.
/// </summary>
#  define eOkTest(x)	 ((x) == Acad::eOk)
/// <summary>
/// Asserts if value is not Acad::eOk.  Evaluates to the value.
/// </summary>
#  define eOkCheck(x)	 eOkCheck_imp(ACRX_T(# x), ACRX_T(__FILE__), __LINE__, (x))
/// <summary>
/// Asserts if value is not Acad::eOk.  Evaluates to true if value is Acad::eOk
/// otherwise evalutes to false.
/// </summary>
#  define eOkVerify(x)	 (eOkCheck(x) == Acad::eOk)
#endif
