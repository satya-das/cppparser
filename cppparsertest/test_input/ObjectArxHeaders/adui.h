//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _adui_h
#define _adui_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "adui_port.h"

class ADUI_PORT CAdUiThemeManager;    // INTERNAL USE ONLY

/////////////////////////////////////////////////////////////////////////////
// Initialize the extension DLL, register the classes, etc
// Call this exported function from your Dll or Executable once
// - an ideal location is the InitInstance() member function 

void ADUI_PORT InitAdUiDLL();

// This function shows an alert type dialog with three buttons. Caption
// string and text for each button are arguments along with a default button
// 0 based index. Returns 0 based button index or -1 on CANCEL. Button 2
// is always the CANCEL button.
int  ADUI_PORT AdUiAlertDialog (
    LPCTSTR captionText,
    LPCTSTR msg0Text,
    LPCTSTR button0Text,                      
    LPCTSTR button1Text,
    UINT defButton = 0          // Means first button is default.
);

int  ADUI_PORT AdUiDataValidationLevel ();      // INTERNAL USE ONLY

// Helper function to expand a help file name into a fully-qualified pathname.
BOOL ADUI_PORT AdUiFindContextHelpFullPath (
    LPCTSTR fileName, CString& fullPath
);

void ADUI_PORT AdUiSubstituteShellFont (CWnd& dlg, CFont& font);
CAdUiThemeManager ADUI_PORT * AdUiGetThemeManager();  // INTERNAL USE ONLY

// This function finds a suitable parent window for a dialog when none is
// explicitly supplied. The algorithm obtains the active window 
// (using GetActiveWindow) and the walks the parent hierarchy (using GetParent)
// A disabled window or the main window terminates the walk.
HWND ADUI_PORT AdUiGetSafeParentHwnd();
ADUI_PORT CWnd* AdUiGetSafeParentWnd();

// This function allows the client override the AutoCAD's default setting of
// dock bar's min width. It is related to the DID#1017779. In Spago, the default
// value is 40px and we change to 150px in Raptor which caused issues to the third
// party developer. The following API is for them to override AutoCAD default settings.
bool ADUI_PORT AdUiSetDockBarMinWidth(int width);

/////////////////////////////////////////////////////////////////////////////
// Class prototypes

class ADUI_PORT CAdUiBaseDialog;
class ADUI_PORT CAdUiComboBox;
class ADUI_PORT CAdUiDialog;
class ADUI_PORT CAdUiDialogBar;
class ADUI_PORT CAdUiFileDialog;
class ADUI_PORT CAdUiTab;
class ADUI_PORT CAdUiTabChildDialog;
class ADUI_PORT CAdUiTabExtensionManager;
class ADUI_PORT CAdUiTabMainDialog;
class ADUI_PORT CAdUiDialogWorksheet;  // INTERNAL USE ONLY
class ADUI_PORT CAdUiDropTarget;
class ADUI_PORT CAdUiTheme;            // INTERNAL USE ONLY
class ADUI_PORT CAdUiPalette;
class ADUI_PORT CAdUiPaletteSet;
class ADUI_PORT CAdUiThemeMgrReactor;  // INTERNAL USE ONLY
class ADUI_PORT CAduiLabelEdit;  // INTERNAL USE ONLY

/////////////////////////////////////////////////////////////////////////////

#define MOVEX               0x00001
#define MOVEY               0x00002
#define MOVEXY              0x00003
#define ELASTICX            0x00010
#define ELASTICY            0x00020
#define ELASTICXY           0x00030

#pragma pack (push, 8)
typedef struct _dlgControlTag {
    DWORD       id;
    DWORD       flags;
    DWORD       pct;
} DLGCTLINFO, *PDLGCTLINFO;
#pragma pack (pop)


// For Internal use
//
namespace AdUi
{
    enum AdUiIconMode{
        kSmall = 0,
        kLarge
    };

    enum AdUiImage
    {
        kImageSmall      = 1,
        kImageLarge      = 2,

        kImageEnable     = 4,
        kImageDisable    = 8,
    };

}; 



/////////////////////////////////////////////////////////////////////////////

// WINREG.H declares HKEY, needed by aduiRegistryAccess.h
#include <winreg.h>

//// AFXOLE.H declares COleDropTarget needed by aduiDropTarget.h
#include <afxole.h>

#include "aduiRegistryAccess.h"

#include "aduiMessage.h"
#include "aduiDropTarget.h"
#include "aduiTabExtension.h"
#include "aduiTextTip.h"

#include "aduiButton.h"
#include "aduiTabCtrl.h"
#include "aduiRichEditCtrl.h"

#include "aduiBaseDialog.h"
#include "aduiDialog.h"
#include "aduiDialogBar.h"
#include "aduiFileDialog.h"
#include "aduiTabChildDialog.h"
#include "aduiTabMainDialog.h"

#include "aduiEdit.h"
#include "aduiHeaderCtrl.h"
#include "aduiListBox.h"
#include "aduiListCtrl.h"
#include "aduiComboBox.h"

#include "aduiDock.h"

#include "aduiPathname.h"
#include "aduiPalette.h"
#include "aduiPaletteSet.h"

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif

//////////////////////////////////////////////////////////////////////////////
