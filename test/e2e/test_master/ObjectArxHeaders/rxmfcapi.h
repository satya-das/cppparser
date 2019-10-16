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
#  define AD_RXMFCAPI_H	1
#  pragma  pack (push, 8)
#  ifndef WM_ACAD_KEEPFOCUS
#    define WM_ACAD_KEEPFOCUS	(WM_USER+0x6D01)
#  endif
class AcDbDatabase;
class CDialogBar;
class AdApplicationFrame;
#  ifdef _ADESK_WINDOWS_
//////////////////////////
// AutoCAD Window pointers
//////////////////////////
CWinApp* acedGetAcadWinApp();
CDocument* acedGetAcadDoc();
CView* acedGetAcadDwgView();
CMDIFrameWnd* acedGetAcadFrame();
CWnd* acedGetAcadDockCmdLine();
CWnd* acedGetAcadTextCmdLine();
#  endif
HINSTANCE acedGetAcadBrandingResourceInstance();
#  ifdef _ADESK_WINDOWS_
typedef struct tagChildFrmSettings
{
  AcColorSettings m_ColorSettings;
  bool m_bShowLayoutBar;
  bool m_bShowScrollBar;
  CDialogBar* m_pDialogBar;
  bool m_bIsBedit;
} AcChildFrmSettings;
BOOL acedGetChildFrameSettings(AcChildFrmSettings* pChildFrmSettings, CMDIChildWnd* pWnd);
BOOL acedSetChildFrameSettings(AcChildFrmSettings* pChildFrmSettings, CMDIChildWnd* pWnd);
#  endif
#  ifdef _ADESK_WINDOWS_
#    ifdef _ARX_CUSTOM_DRAG_N_DROP_
BOOL acedRegisterCustomDropTarget(IDropTarget* pItarget);
BOOL acedStartOverrideDropTarget(COleDropTarget* pTarget);
BOOL acedRevokeCustomDropTarget();
BOOL acedEndOverrideDropTarget(COleDropTarget* pTarget);
BOOL acedAddDropTarget(COleDropTarget* pTarget);
BOOL acedRemoveDropTarget(COleDropTarget* pTarget);
#    endif
#  endif
#  ifdef _ADESK_WINDOWS_
AcDbDatabase* AcApGetDatabase(CView* pView);
#  endif
const CString& acedGetRegistryCompany();
BOOL acedRegisterExtendedTab(const wchar_t* szAppName, const wchar_t* szDialogName);
HMENU acedGetMenu(const wchar_t* pszAlias);
BOOL acedSetIUnknownForCurrentCommand(const LPUNKNOWN);
BOOL acedGetIUnknownForCurrentCommand(LPUNKNOWN& pUnk);
BOOL acedShowDrawingStatusBars(BOOL bShow = TRUE);
#  ifdef _ADESK_WINDOWS_
BOOL acedRegisterStatusBarMenuItem(AcStatusBarMenuItem* pItem, AcStatusBarMenuItem::AcStatusBarType nType);
BOOL acedUnregisterStatusBarMenuItem(AcStatusBarMenuItem* pItem, AcStatusBarMenuItem::AcStatusBarType nType);
BOOL acedSetStatusBarPaneID(AcPane* pPane, AcStatusBarMenuItem::AcStatusBarType nType, int nID);
#  endif
void acedSuppressFileMRU(bool bSuppress);
AdApplicationFrame* acedGetApplicationFrame();
typedef BOOL (*AcedPreTranslateMsgFn) (MSG*);
BOOL acedRegisterMainFramePreTranslateObserver(const AcedPreTranslateMsgFn pfn);
BOOL acedRemoveMainFramePreTranslateObserver(const AcedPreTranslateMsgFn pfn);
#  pragma  pack (pop)
#endif
