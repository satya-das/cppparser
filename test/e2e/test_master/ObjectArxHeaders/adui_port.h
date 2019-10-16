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
/////////////////////////////////////////////////////////////////////////////
#ifdef _ADUI_BUILD
#  define ADUI_PORT	__declspec(dllexport)
#else 
#  define ADUI_PORT
#endif
#ifdef ADESK_NO_VTABLE
#  define ADUI_NO_VTABLE	ADESK_NO_VTABLE
#else 
#  ifdef _MSC_VER
#    define ADUI_NO_VTABLE	__declspec(novtable)
#  else 
#    define ADUI_NO_VTABLE
#  endif
#endif
