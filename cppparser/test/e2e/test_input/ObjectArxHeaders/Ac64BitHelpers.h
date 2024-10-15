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
#pragma once

// replace _tcslen and wcslen with ac_wcslen, which returns unsigned
#include "ac_tcslen.h"
#include "adesk.h"
#include <cwchar>

#define Ac64Assert AcTcsLen_Assert


// The msvc definition of this in windef.h is bad in both 32-bit and
// 64-bit builds, triggering a Runtime Check assert.
// #define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))
#ifdef  HIBYTE
#undef HIBYTE
#endif
#define HIBYTE(w)           LOBYTE((Adesk::UIntPtr)(w) >> 8)

#pragma warning(push)
#pragma warning(disable:4100)//disable unreferenced formal parameter warning
inline int AcIntPtrToInt(Adesk::LongPtr nVal, Adesk::LongPtr nLimit = /*16M*/0x1000000)
{
    Ac64Assert(nVal < nLimit);
    Ac64Assert(nVal > -nLimit);   // it's a signed value, so assert at both ends of the range
    const int nRet = static_cast<int>(nVal);
    Ac64Assert(nRet == nVal);    // a little redundant, but make sure no bits are lost
    return nRet;
}

inline unsigned int AcUIntPtrToUInt(Adesk::ULongPtr nVal, Adesk::ULongPtr nLimit = /*16M*/0x1000000)
{
    Ac64Assert(nVal < nLimit);
    const unsigned int nRet = static_cast<unsigned int>(nVal);
    Ac64Assert(nRet == nVal);    // a little redundant, but make sure no bits are lost
    return nRet;
}
#pragma warning(pop)


// provide a polymophic function to parse INT_PTR string.
inline Adesk::LongPtr ADESK_STDCALL AcStrToIntPtr(const wchar_t * s)
{
#if defined(_WIN64) || defined(_AC64)
    return std::wcstoll(s, nullptr, 10);
#else
    return std::wcstol(s, nullptr, 10);
#endif
}

