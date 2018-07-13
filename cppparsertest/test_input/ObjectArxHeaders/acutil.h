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
//  acutil.h - General-purpose AcUtil functions
//
//
//
//  DESCRIPTION:
//
//  This header file contains declarations of general-purpose utility
//  functions provided with the AcUtil library and DLL.
//
#ifndef _ACUTIL_H
#define _ACUTIL_H

#include "acadstrc.h"

#pragma pack (push, 8)

bool              acutSplitString(
                      size_t &      numLeftBytes,
                      const ACHAR *& pRight,
                      const ACHAR  * source,
                      unsigned int  delimiter);

void              acutTrimWhiteSpace(ACHAR * pStr);

bool              acutWcMatchEx(
                      const ACHAR * string,
                      const ACHAR * pattern,
                      bool         ignoreCase);

size_t            acutXStrLength(const ACHAR * str);

Acad::ErrorStatus acutXStrNormalize(
                      ACHAR *& pStr,
                      bool preserveCase);

inline Acad::ErrorStatus
acutXStrUppercase(ACHAR *& pStr)
{ return acutXStrNormalize(pStr, false); }

#pragma pack (pop)
#endif // _ACUTIL_H
