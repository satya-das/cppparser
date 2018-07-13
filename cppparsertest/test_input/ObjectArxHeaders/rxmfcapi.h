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
// Name:    rxmfcapi.h
//
// Remarks: This module contains the implementation for ARXMFC API.
//          You need to include windows and/or ole header files
//
//////////////////////////////////////////////////////////////////////////////
#include "adesk.h"
#include "AdAChar.h"
#include "AcStatusBar.h"
#include "core_rxmfcapi.h"

#ifndef AD_RXMFCAPI_H
#define AD_RXMFCAPI_H 1
#pragma pack (push, 8)

// AutoCAD WM_ACAD_KEEPFOCUS
// Create custom window message.  This message is used by the OnIdle
// handler to test if a top-level window will relinquish focus.  If
// a window handles this message and does not want to lose focus then
// it should return a TRUE result.
//   lParam & wParam not used
//   Return 1 to maintain focus else 0 if focus can be shifted.
#ifndef WM_ACAD_KEEPFOCUS
#define WM_ACAD_KEEPFOCUS  (WM_USER+0x6D01)
#endif // WM_ACAD_KEEPFOCUS

class AcDbDatabase;
class CDialogBar;
class AdApplicationFrame;

#ifdef _ADESK_WINDOWS_
//////////////////////////
// AutoCAD Window pointers
//////////////////////////
// The pointer to a window or a frame should be used only when the
// ARX apps share the SAME MFC DLL with AutoCAD.
// In some cases, when using static MFC or different MFC DLL,
// the window handle should be used instead.
//  instead of using
//      acedGetAcadDwgView()->UpdateWindow();
//      CMyDialog Mydia(acedGetAcadFrame());
//  use
//      ::UpdateWindow(acedGetAcadDwgView()->m_hWnd);
//      CMyDialog Mydia(CWnd::FromHandle(acedGetAcadFrame()->m_hWnd));
        
/* acedGetAcadWinApp
 * Returns the pointer to AutoCAD CWinApp object.
 */
CWinApp* acedGetAcadWinApp();

/* acedGetAcadDoc
 * Returns the pointer to AutoCAD CDocument object
 * There's only one document in AutoCAD.
 */
CDocument* acedGetAcadDoc();

/* acedGetAcadDwgView
 * Returns the pointer to AutoCAD CView object
 * There's only one Dwg view in AutoCAD.
 */
CView* acedGetAcadDwgView();

/* acedGetAcadFrame
 * Returns the pointer to AutoCAD CMDIFrameWnd object
 */
CMDIFrameWnd* acedGetAcadFrame();

/* acedGetAcadDockCmdLine
 * Returns the pointer to AutoCAD command line window
 */
CWnd* acedGetAcadDockCmdLine();

/* acedGetAcadTextCmdLine
 * Returns the pointer to AutoCAD Text window.
 */
CWnd* acedGetAcadTextCmdLine();
#endif // _ADESK_WINDOWS_

/* acedGetAcadBrandingResourceInstance()
 * Returns the Instance of AutoCAD's Branding resource
 * e.g. splash screen, about box, mainframe icon
 */
HINSTANCE acedGetAcadBrandingResourceInstance();

#ifdef _ADESK_WINDOWS_
// AutoCAD MDI Child Window Frame settings
typedef struct tagChildFrmSettings {
    // More to come later
    AcColorSettings m_ColorSettings;
    bool m_bShowLayoutBar;
    bool m_bShowScrollBar;
    CDialogBar *m_pDialogBar;
    bool m_bIsBedit;
} AcChildFrmSettings;

BOOL acedGetChildFrameSettings(AcChildFrmSettings* pChildFrmSettings,
    CMDIChildWnd *pWnd);
BOOL acedSetChildFrameSettings(AcChildFrmSettings* pChildFrmSettings,
    CMDIChildWnd *pWnd);
#endif


#ifdef _ADESK_WINDOWS_
// Custom Drag and Drop
// In order to enable custom drag&drop, you have to 
// #define _ARX_CUSTOM_DRAG_N_DROP_
// before including this header file, and you need to include <afxole.h> also.
#ifdef _ARX_CUSTOM_DRAG_N_DROP_
/* acedRegisterCustomDropTarget
 * Registers a new IDroptarget to the AutoCAD's drawing window. 
 * Only one IDropTarget can be registered at one moment.
 * AutoCAD's default Drag & Drop handling capabilities are not available 
 * until the IDroptarget is revoke.
 * This is replaced by acedStartOverrideDropTarget(). It will be removed
 * in next release.
 */
BOOL acedRegisterCustomDropTarget(IDropTarget* pItarget);
BOOL acedStartOverrideDropTarget(COleDropTarget* pTarget);

/* acedRevokeCustomDropTarget
 * Revokes the previously set IDroptarget. 
 * The default AutoCAD's handling of Drag&Drop event is restored.
 * This is replaced by acedRemoveDropTarget(). It will be removed
 * in next release.
 */
BOOL acedRevokeCustomDropTarget();
BOOL acedEndOverrideDropTarget(COleDropTarget* pTarget);

/* acedAddDropTarget
 * Add a hook to participate in DragDrop Event started not from
 * 3rd party ARX app.
 */
BOOL acedAddDropTarget(COleDropTarget* pTarget);

/* acedRemoveDropTarget
 * Remove the hook to AutoCAD DragDrop event.
 */
BOOL acedRemoveDropTarget(COleDropTarget* pTarget);

#endif // _ARX_CUSTOM_DRAG_N_DROP_
#endif // _ADESK_WINDOWS_

#ifdef _ADESK_WINDOWS_
// Get Database correpont to on AutoCAD Drawing Window.
AcDbDatabase* AcApGetDatabase(CView *pView);
#endif


// AutoCAD company name for registry access.  For all except AutoCAD
// OEM, this will return "Autodesk".  For AutoCAD OEM, it is at the
// discretion of the AutoCAD OEM developer, via an entry in aoemres2.rc,
// to specify the company name for use in registry accesses.
const CString& acedGetRegistryCompany();

// Register the fact that the application with name "szAppName"
// may want to add a tab to the tabbed dialog named "szDialogName".
// This function creates the key necessary to register the added
// tab(s) if it is not there. Returns TRUE on success.
BOOL acedRegisterExtendedTab(const wchar_t* szAppName, const wchar_t* szDialogName);

// Return an HMENU given a .MNU file alias.
HMENU acedGetMenu(const wchar_t* pszAlias);

BOOL acedSetIUnknownForCurrentCommand(const LPUNKNOWN);
BOOL acedGetIUnknownForCurrentCommand(LPUNKNOWN &pUnk);

/* acedShowDrawingStatusBars
 * Shows or hides the drawing status bars.
 */
BOOL acedShowDrawingStatusBars(BOOL bShow = TRUE);

#ifdef _ADESK_WINDOWS_
/* acedRegisterStatusBarMenuItem
 * Returns TRUE if the status bar item is successfully
 * registered in AutoCAD, otherwise FALSE.
 */
BOOL acedRegisterStatusBarMenuItem(AcStatusBarMenuItem* pItem,
                                   AcStatusBarMenuItem::AcStatusBarType nType);

/* acedUnregisterStatusBarMenuItem
 * Returns TRUE if the status bar item is successfully
 * unregistered in AutoCAD, otherwise FALSE.
 */
BOOL acedUnregisterStatusBarMenuItem(AcStatusBarMenuItem* pItem,
                                     AcStatusBarMenuItem::AcStatusBarType nType);

/* acedSetStatusBarPaneId
 * Sets the id of the given status bar pane.  Returns TRUE if
 * successful, otherwise FALSE.
 */
BOOL acedSetStatusBarPaneID(AcPane* pPane,
                            AcStatusBarMenuItem::AcStatusBarType nType,
                            int nID);
#endif // _ADESK_WINDOWS_

// Controls whether or not file open adds the filename to the 'File' MRU list.
void acedSuppressFileMRU(bool bSuppress);

// acedGetApplicationFrame
// Returns the pointer to AutoCAD Application Frame.
AdApplicationFrame* acedGetApplicationFrame();

// Define callback function for apps that want windows messages
typedef BOOL (* AcedPreTranslateMsgFn)(MSG*);

// acedRegisterMainFramePretranslateObserver
/* Register a filter message hook into AutoCAD's main frame message pre-translator.
 * The message passed to your application can be changed and can be blocked out.
 * If the function returns TRUE, the message WON'T be passed the message handlers
 * of AutoCAD. The message is terminated.
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
BOOL acedRegisterMainFramePreTranslateObserver(const AcedPreTranslateMsgFn pfn);

/* acedRemoveMainFramePretranslateObserver
 * Takes a message hook function pointer and remove it 
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
BOOL acedRemoveMainFramePreTranslateObserver(const AcedPreTranslateMsgFn pfn); 

#pragma pack (pop)
#endif // AD_RXMFCAPI_H
