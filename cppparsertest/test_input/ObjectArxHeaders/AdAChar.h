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
//              AdAChar.h
//
// Define the ACHAR type and ACRX_T() macro for use in ARX/DBX headers.
//
#pragma once

// The API is always Unicode now, so we always define AD_UNICODE
#define AD_UNICODE 1

// Acad APIs expect clients to be building with "native" wchar_t type.
#if defined(__cplusplus) && defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)
#error Please use native wchar_t type (/Zc:wchar_t)
#endif

typedef wchar_t ACHAR;

// Same mechanism as tchar.h's ACRX_T() macro.  We redirect this to a
// second macro, so that other macros can be passed as the x arg,
// as in ACRX_T(__FILE__)
//
#define _ACRX_T(x)      L ## x
#define ACRX_T(x)      _ACRX_T(x)

