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
#define AD_UNICODE	1
#if  defined(__cplusplus) && defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)
#endif
typedef wchar_t ACHAR;
#define _ACRX_T(x)	      L ## x
#define ACRX_T(x)	      _ACRX_T(x)
