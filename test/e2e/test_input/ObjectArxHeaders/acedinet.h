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
// Name:    acedInet.h
//
// Remarks:	Miscellaneous functions to create and resolve Windows shell links
//          and MS Internet Explorer shortcuts.
//
//////////////////////////////////////////////////////////////////////////////
#include "acadapidef.h"

#if !defined(AFX_ACEDINET_H__2357B7CE_20CE_11d2_A981_0060B0CD39AD__INCLUDED_)
#define AFX_ACEDINET_H__2357B7CE_20CE_11d2_A981_0060B0CD39AD__INCLUDED_
#pragma pack (push, 8)


// FUNCTION       acedCreateShortcut()
//
// ARGUMENTS      pvHwndParent -- pointer to a window handle (of type HWND)
//                                that will be used as the parent window in
//                                case we need to display a message box or
//                                an animation dialog; this value should not
//                                be NULL
//                szLinkPath   -- full path to the .lnk file that will be
//                                created as the Windows-style shortcut;
//                                note that the ".lnk" extension is required
//                szObjectPath -- full path to the filesystem object which
//                                the shortcut will point to
//                szDesc       -- a descriptive string for the shortcut; can
//                                have any arbitrary value except NULL
//
// RETURN VALUE   Adesk::kTrue on success; Adesk::kFalse on failure
//
ACAD_PORT Adesk::Boolean
acedCreateShortcut(/*[in]*/void* pvHwndParent, /*[in]*/const ACHAR* szLinkPath, 
				   /*[in]*/const ACHAR* szObjectPath, /*[in]*/const ACHAR* szDesc);


// FUNCTION       acedResolveShortcut()
//
// ARGUMENTS      pvHwndParent -- pointer to a window handle (of type HWND)
//                                that will be used as the parent window in
//                                case we need to display a message box or
//                                an animation dialog; this value should not
//                                be NULL
//                szLinkPath   -- full path to the .lnk file that will be
//                                created as the Windows-style shortcut;
//                                note that the ".lnk" extension is required
//                szObjectPath -- an ACHAR buffer that receives the full path
//                                of the filesystem object which the shortcut
//                                points; it is the caller's responsibility
//                                to provide a sufficiently large buffer
//
// RETURN VALUE   Adesk::kTrue on success; Adesk::kFalse on failure
//
ACAD_PORT Adesk::Boolean
acedResolveShortcut(/*[in]*/void* pvHwndParent, /*[in]*/const ACHAR* szLinkPath, 
					/*[out]*/ACHAR* szObjectPath);


//
// FUNCTION       acedGetUserFavoritesDir()
//
// ARGUMENTS      szFavoritesDir -- a char buffer that receives the full path
//                                  to the Windows Favorites folder of the
//                                  currently logged-in user; it is the caller's
//                                  responsibility to provide a sufficiently
//                                  large buffer
//
// RETURN VALUE   Adesk::kTrue on success; Adesk::kFalse on failure
//
ACAD_PORT Adesk::Boolean
acedGetUserFavoritesDir(/*[out]*/ACHAR* szFavoritesDir);


// 'acedCreateInternetShortcut()' creates an MSIE-compatible Internet shortcut
// using the arguments passed to it. 'szURL' is the URL that the shortcut will
// "wrap" (point to), and 'szShortcutPath' is the filesystem path to the resulting
// shortcut.
//
// Note that 'szShortcutPath' should specify a path to a file that has the ".url"
// extension. In the absence of such an extension, the specified path will be
// considered invalid and Adesk::kFalse will be returned.
//
// RETURN VALUE   Adesk::kTrue on success; Adesk::kFalse on failure
//
ACAD_PORT Adesk::Boolean
acedCreateInternetShortcut(/*[in]*/const ACHAR* szURL, /*[in]*/const ACHAR* szShortcutPath);


// 'acedResolveInternetShortcut()' is the inverse of 'acedCreateInternetShortcut().'
// This function accepts a path to an (MSIE-compatible) Internet shortcut file and
// extracts the URL from it. The retrieved URL is returned via the parameter 'szURL.'
// It is the caller's responsibility to ensure that 'szURL' points to a sufficiently
// large buffer.
//
// RETURN VALUE   Adesk::kTrue on success; Adesk::kFalse on failure
//
ACAD_PORT Adesk::Boolean
acedResolveInternetShortcut(/*[in]*/const ACHAR* szLinkFile, /*[out]*/ACHAR* szUrl);



#pragma pack (pop)
#endif	// #define AFX_ACEDINET_H__2357B7CE_20CE_11d2_A981_0060B0CD39AD__INCLUDED_
