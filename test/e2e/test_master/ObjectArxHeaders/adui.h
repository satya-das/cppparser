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
#  define _adui_h
#  if  _MSC_VER >= 1000
#    pragma  once
#  endif
#  include "adui_port.h"
class ADUI_PORT CAdUiThemeManager;
/////////////////////////////////////////////////////////////////////////////
void ADUI_PORT InitAdUiDLL();
int ADUI_PORT AdUiAlertDialog(LPCTSTR captionText, LPCTSTR msg0Text, LPCTSTR button0Text, LPCTSTR button1Text, UINT defButton = 0);
int ADUI_PORT AdUiDataValidationLevel();
BOOL ADUI_PORT AdUiFindContextHelpFullPath(LPCTSTR fileName, CString& fullPath);
void ADUI_PORT AdUiSubstituteShellFont(CWnd& dlg, CFont& font);
CAdUiThemeManager ADUI_PORT* AdUiGetThemeManager();
HWND ADUI_PORT AdUiGetSafeParentHwnd();
ADUI_PORT CWnd* AdUiGetSafeParentWnd();
bool ADUI_PORT AdUiSetDockBarMinWidth(int width);
/////////////////////////////////////////////////////////////////////////////
class ADUI_PORT CAdUiBaseDialog;
class ADUI_PORT CAdUiComboBox;
class ADUI_PORT CAdUiDialog;
class ADUI_PORT CAdUiDialogBar;
class ADUI_PORT CAdUiFileDialog;
class ADUI_PORT CAdUiTab;
class ADUI_PORT CAdUiTabChildDialog;
class ADUI_PORT CAdUiTabExtensionManager;
class ADUI_PORT CAdUiTabMainDialog;
class ADUI_PORT CAdUiDialogWorksheet;
class ADUI_PORT CAdUiDropTarget;
class ADUI_PORT CAdUiTheme;
class ADUI_PORT CAdUiPalette;
class ADUI_PORT CAdUiPaletteSet;
class ADUI_PORT CAdUiThemeMgrReactor;
class ADUI_PORT CAduiLabelEdit;
/////////////////////////////////////////////////////////////////////////////
#  define MOVEX	0x00001
#  define MOVEY	0x00002
#  define MOVEXY	0x00003
#  define ELASTICX	0x00010
#  define ELASTICY	0x00020
#  define ELASTICXY	0x00030
#  pragma  pack (push, 8)
struct _dlgControlTag
{
  DWORD id;
  DWORD flags;
  DWORD pct;
};
typedef _dlgControlTag DLGCTLINFO;
typedef _dlgControlTag* PDLGCTLINFO;
#  pragma  pack (pop)
namespace AdUi
{
  enum AdUiIconMode
  {
    kSmall = 0,
    kLarge
  };
  enum AdUiImage
  {
    kImageSmall = 1,
    kImageLarge = 2,
    kImageEnable = 4,
    kImageDisable = 8
  };
}
/////////////////////////////////////////////////////////////////////////////
#  include <winreg.h>
//// AFXOLE.H declares COleDropTarget needed by aduiDropTarget.h
#  include <afxole.h>
#  include "aduiRegistryAccess.h"
#  include "aduiMessage.h"
#  include "aduiDropTarget.h"
#  include "aduiTabExtension.h"
#  include "aduiTextTip.h"
#  include "aduiButton.h"
#  include "aduiTabCtrl.h"
#  include "aduiRichEditCtrl.h"
#  include "aduiBaseDialog.h"
#  include "aduiDialog.h"
#  include "aduiDialogBar.h"
#  include "aduiFileDialog.h"
#  include "aduiTabChildDialog.h"
#  include "aduiTabMainDialog.h"
#  include "aduiEdit.h"
#  include "aduiHeaderCtrl.h"
#  include "aduiListBox.h"
#  include "aduiListCtrl.h"
#  include "aduiComboBox.h"
#  include "aduiDock.h"
#  include "aduiPathname.h"
#  include "aduiPalette.h"
#  include "aduiPaletteSet.h"
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif
//////////////////////////////////////////////////////////////////////////////
