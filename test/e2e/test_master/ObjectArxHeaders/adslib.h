//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _adslib_h
#  define _adslib_h	1
#  ifdef _WINDOWS
#    define WIN	1
#  endif
#  ifdef WINVER
#    define WIN	1
#  endif
#  ifdef _MSC_VER
#    define MICROSOFT	1
#  endif
#  include "ads.h"
#  include "adscodes.h"
#  pragma  pack (push, 8)
#  ifdef __cplusplus
bool acrxUnlockApplication(void* appId);
bool acrxApplicationIsLocked(const ACHAR* modulename);
bool acrxLockApplication(void* appId);
#  endif
#  pragma  pack (pop)
#endif
