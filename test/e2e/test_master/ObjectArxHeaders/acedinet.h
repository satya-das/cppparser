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
#if  !defined(AFX_ACEDINET_H__2357B7CE_20CE_11d2_A981_0060B0CD39AD__INCLUDED_)
#  define AFX_ACEDINET_H__2357B7CE_20CE_11d2_A981_0060B0CD39AD__INCLUDED_
#  pragma  pack (push, 8)
ACAD_PORT Adesk::Boolean acedCreateShortcut(void* pvHwndParent, const ACHAR* szLinkPath, const ACHAR* szObjectPath, const ACHAR* szDesc);
ACAD_PORT Adesk::Boolean acedResolveShortcut(void* pvHwndParent, const ACHAR* szLinkPath, ACHAR* szObjectPath);
ACAD_PORT Adesk::Boolean acedGetUserFavoritesDir(ACHAR* szFavoritesDir);
ACAD_PORT Adesk::Boolean acedCreateInternetShortcut(const ACHAR* szURL, const ACHAR* szShortcutPath);
ACAD_PORT Adesk::Boolean acedResolveInternetShortcut(const ACHAR* szLinkFile, ACHAR* szUrl);
#  pragma  pack (pop)
#endif
