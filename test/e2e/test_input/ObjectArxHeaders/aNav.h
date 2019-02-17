//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _ANav_h
#define _ANav_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// ANAV_PORT is defined to export classes and functions when building the DLL.

#ifndef ANAV_PORT
#  define   ANAV_PORT
#endif

/////////////////////////////////////////////////////////////////////////////
// File Navigation prototypes

#include <adui.h>
#include <afxole.h>
#include <AnavListCtrl.h>
#include <ANavData.h>
#include <ANavFilter.h>
#include <ANavArray.h>
#include <ANavDataArray.h>
#include <ANavFilterArray.h>
#include <ANavDialog.h>


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
