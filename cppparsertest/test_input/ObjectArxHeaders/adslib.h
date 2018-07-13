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
//   DESCRIPTION:
//   ADS definitions and system dependent controls.
//   This also contains a substitute for stdlib.h on some systems.
//   If we know the system has stdlib.h, just include it.

#ifndef _adslib_h
#define _adslib_h 1

// Not clear that WIN needs to be defined anymore.
// Let's remove it next release.
//
#ifdef _WINDOWS
#define WIN 1
#endif

#ifdef WINVER
#define WIN 1
#endif

#ifdef _MSC_VER
#define MICROSOFT 1
#endif

#include "ads.h"
#include "adscodes.h"
#pragma pack (push, 8)

// The bool type isn't known in .c files.
#ifdef __cplusplus


/* Unlocks an application to enable it from being unloaded in mid-session.
   The default is that applications are locked, and hence unloadable in
   mid-session. The appId argument is the Id passed in as a void* during
   the AcRx::kInitAppMsg call back when the application is loaded. Return
   of non-zero means success.
*/
bool acrxUnlockApplication(void* appId);

/* Returns non-zero if the specified app is locked.
 */
bool acrxApplicationIsLocked(const ACHAR* modulename);

/* Symmetric to acrxUnlockApplication. Locks it, and hence prevents it from
   being unloaded in mid-session. Return of non-zero means success.
 */
bool acrxLockApplication(void* appId);


#endif // __cplusplus

#pragma pack (pop)

#endif // ndef _adslib_h

