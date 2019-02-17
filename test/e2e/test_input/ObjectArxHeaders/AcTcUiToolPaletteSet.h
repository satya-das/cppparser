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
// Name:            CAcTcUiToolPaletteSet.h
//
// Description:     Header for CAcTcUiToolPaletteSet class. This class 
//                  implements the tool palette window and derives from 
//                  CAdUiPalette. The tool palette window is embedded in 
//                  CAdUiToolPaletteSet window and embeds a tool tray 
//                  window CAcUiCatalogView.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUITOOLPALETTESET_H__
#define __ACTCUITOOLPALETTESET_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcTcUi.h"
#include "aduiPaletteSet.h"
#include "AcTcUiToolPalette.h"
#include "AcTcUiToolPaletteGroup.h"


class CAcTcUiImpToolPaletteSet;
class CAcTcUiScheme;
#ifndef _ADESK_MAC_
class ACTCUI_PORT CAcTcUiToolPaletteSet : public CAdUiPaletteSet
{
    friend CAcTcUiImpToolPaletteSet;

    DECLARE_DYNCREATE(CAcTcUiToolPaletteSet);

public:
    virtual ~CAcTcUiToolPaletteSet();

    virtual BOOL        Load                (IUnknown* pUnk);
    virtual BOOL        Save                (IUnknown* pUnk);
    virtual BOOL        Import              (IUnknown* pUnk, LPCTSTR pszRefPath);
    virtual BOOL        Export              (IUnknown* pUnk, LPCTSTR pszRefPath);
    virtual BOOL        HitTest             (CPoint pt, UINT& nFlag, 
                                             DWORD& dwData);
    int                 AddPalette          (CAdUiPalette* pPalette);
    int                 InsertPalette       (int iIndex, CAdUiPalette* pPalette);
    BOOL                RemovePalette       (CAdUiPalette* pPalette);
    BOOL                RemovePalette       (int iIndex);
#ifndef NEW_PALETTE
    virtual void        TitleBarLocationUpdated(AdUiTitleBarLocation newLoc);
#endif  // NEW_PALETTE
    CAcTcUiToolPaletteGroup* GetToolPaletteGroup(BOOL bCreate = FALSE);
    CAcTcUiToolPaletteGroup* GetAllPalettesGroup(void);
    CAcTcUiToolPaletteGroup* GetActivePaletteGroup(void);
    BOOL                GetActivePaletteGroup(LPTSTR pszGroup, 
                                              int cbSize) const;
    BOOL                SetActivePaletteGroup(CAcTcUiToolPaletteGroup* pGroup);
    BOOL                SetActivePaletteGroup(LPCTSTR pszGroup);
    CAcTcUiScheme*      GetScheme           (void) const;
    BOOL                Show                (void);
    BOOL                Show                (BOOL bShow);
    BOOL                SetActivePalette    (CAdUiPalette* pPalette);
    BOOL                SetActivePalette    (int nPaletteIndex);
    BOOL                SetActivePalette    (LPCTSTR pszPalName,
                                             BOOL bSearchOnlyCurrentGroup) const;
    CAcTcUiToolPalette* FindPalette         (LPCTSTR pszPalName,
                                             CAcTcUiToolPaletteGroup** ppGroup,
                                             BOOL bSearchOnlyCurrentGroup) const;

protected:
    // Protected constructor
    CAcTcUiToolPaletteSet();

protected:
    virtual BOOL        AddContextMenuItems (CMenu *pMenu, 
                                             int nHitFlag,
                                             int nRightClkTab = 0);
    /// <summary>
    /// Virtual method that receives the theme modification event.
    /// </summary>
    /// <param name="element">
    /// A index of the theme element that was modified.
    /// </param>
    /// <remarks>
    /// This method is also called when the theme uses the active theme colors
    /// and the active theme is changed.  In that case, element = kUnknownElements
    /// </remarks>        
    virtual void        ThemeModified       (AdUiThemeElement element);
    virtual void        OnTabDrag           (CPtrArray & arrayPalettes);
    virtual BOOL        OnBeginDrag         (COleDataSource* pDataSource,
                                             CPtrArray & arrayPalettes);
    virtual void        OnEndDrag           (DROPEFFECT dropEffect);
    virtual BOOL        OnBeginMove         (COleDataSource* pDataSource,
                                             CPtrArray & arrayPalettes);
    virtual void        OnEndMove           (DROPEFFECT dropEffect);
    virtual BOOL        OnRenderData        (LPFORMATETC lpFormatEtc,
                                             LPSTGMEDIUM lpStgMedium);
    virtual void        OnTearOff           (CAdUiPaletteSet* pSet);
    virtual void        DestroyStackedPaletteSet(void);

protected:
    //{{AFX_VIRTUAL(CAcTcUiToolPaletteSet)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
    afx_msg void OnRemovePaletteSet();
    afx_msg void OnRemoveActivePalette();
    afx_msg void OnRemovePalette();
    afx_msg void OnViewOptions();
    afx_msg void OnSelectPaletteGroup( UINT nID );
    afx_msg void OnShowCustomizeDialog();
    afx_msg void OnShowCustomizeDialogCUI();
    afx_msg void OnNewPalette();
    afx_msg void OnPaste();
    afx_msg void OnPaletteProperties();
    afx_msg void OnRefreshPaletteSet();
    afx_msg void OnRefreshActivePalette();
    afx_msg void OnClose();
    afx_msg void OnMoveUp();
    afx_msg void OnMoveDown();
    afx_msg void OnInvokeCommand(UINT nID);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcTcUiToolPaletteSet)
    //}}AFX_MSG
    afx_msg LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnRenderData(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;           // Imp object CAcTcUiImpToolPaletteSet

private:
    friend class AcTcUiSystemInternals;

};

#endif // Nodef _ADESK_MAC_
#endif //__ACTCUITOOLPALETTESET_H__
