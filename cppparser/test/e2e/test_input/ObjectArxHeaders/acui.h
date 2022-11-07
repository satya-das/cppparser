//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _acui_h
#define _acui_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// Note: _ACUI_BUILD should be defined only when building the DLL.

#ifdef  _ACUI_BUILD
#  define   ACUI_PORT  __declspec(dllexport)
#else
#  define   ACUI_PORT
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialize the extension DLL, register the classes, etc
// Call this exported function from your Dll or Executable once
// - an ideal location is the InitInstance() member function 

ACUI_PORT void InitAcUiDLL();

/////////////////////////////////////////////////////////////////////////////

ACUI_PORT HINSTANCE AcUiAppResourceInstance ();
ACUI_PORT HINSTANCE AcUiAppBrandingResourceInstance ();
ACUI_PORT LPCTSTR AcUiContextHelpFileName();
ACUI_PORT BOOL AcUiEnableToolTips ();
ACUI_PORT BOOL AcUiFindContextHelpFullPath (
    LPCTSTR fileName, CString& fullPath
);
ACUI_PORT BOOL AcUiIsInputPending ();
ACUI_PORT CWnd * AcUiMainWindow ();
ACUI_PORT void AcUiRootKey (CString& rootKey);


typedef CAdUiRegistryAccess         CAcUiRegistryAccess;
typedef CAdUiRegistryDeleteAccess   CAcUiRegistryDeleteAccess;
typedef CAdUiRegistryWriteAccess    CAcUiRegistryWriteAccess;


#ifdef _ADESK_WINDOWS_

#include "acuiButton.h"
#include "acuiDialogWorksheet.h"
#include "acuiDialog.h"
#include "acuiTabCtrl.h"

typedef CAcUiTabChildDialog         CAcUiTabExtension;
/////////////////////////////////////////////////////////////////////////////

#include "aced.h"

#include "acuiDock.h"
#include "acuiEdit.h"
#include "acuiHeaderCtrl.h"
#include "acuiListBox.h"
#include "acuiListCtrl.h"
#include "acuiComboBox.h"
#include "acuiPathname.h"
#include "acuiNavDialog.h"
#endif // _ADESK_WINDOWS_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif

//////////////////////////////////////////////////////////////////////////////
