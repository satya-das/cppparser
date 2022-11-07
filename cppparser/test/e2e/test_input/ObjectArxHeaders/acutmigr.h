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
//  DESCRIPTION:
//
//  This header file provides inline functions, macros, etc. to
//  assist migration to the new AcUtil functions.  This header file
//  may not be available in a subsequent release of ObjectARX.

#ifndef _ACUTMIGR_H
#define _ACUTMIGR_H

#include "acutmem.h"

#pragma pack (push, 8)

// Unicode: leaving newBuffer and delBuffer pointer args as char *.
//
inline Acad::ErrorStatus newBuffer(char *&pOutput, size_t size)
{
    return ::acutNewBuffer(pOutput, size);
}

inline Acad::ErrorStatus newString(const ACHAR* pInput, ACHAR*& pOutput)
{
    return ::acutNewString(pInput, pOutput);
}

inline Acad::ErrorStatus newString(ACHAR*& pOutput, int nNumChars)
{
    return ::acutNewString(pOutput, nNumChars);
}

inline Acad::ErrorStatus updString(const ACHAR* pInput, ACHAR*& pOutput)
{
    return ::acutUpdString(pInput, pOutput);
}

inline void delString(ACHAR*& pString)
{
    ::acutDelString(pString);
}

inline void delBuffer(char*& pString)
{
    ::acutDelString(pString);
}

#pragma pack (pop)
#endif // _ACUTMGR_H

