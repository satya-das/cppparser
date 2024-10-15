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
// Name:            AcTcUiToolPalette.h
//
// Description:     Header for CAcTcUiToolPalette class. This class 
//                  implements the tool palette window and derives from 
//                  CAdUiPalette. The tool palette window is embedded in 
//                  CAdUiToolPaletteSet window and embeds a tool tray 
//                  window CAcUiCatalogView.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUITOOLPALETTE_H__
#define __ACTCUITOOLPALETTE_H__


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcTcUi.h"
#include "aduiPalette.h"
#include "AcTcUiPaletteView.h"

class CAcTcUiImpToolPalette;
class AcTcUiSystemInternals;
class CAcTcUiScheme;
#ifndef _ADESK_MAC_
class ACTCUI_PORT CAcTcUiToolPalette : public CAdUiPalette
{
    friend CAcTcUiImpToolPalette;

    DECLARE_DYNCREATE(CAcTcUiToolPalette);

public:
    CAcTcUiToolPalette();
    virtual ~CAcTcUiToolPalette();
    
    CAcTcUiPaletteView* GetView             (void);

public:
    // Base class overrides
    virtual BOOL        Create              (CAdUiPaletteSet* pParent);
    BOOL                Create              (DWORD dwStyle, 
                                             LPCTSTR pszName, 
                                             CAdUiPaletteSet* pParent,
                                             DWORD dwPaletteStyle = 0);
    virtual BOOL        Load                (IUnknown* pUnk);
    virtual bool        CanFrameworkTakeFocus();
    virtual BOOL        Save                (IUnknown* pUnk);
    virtual BOOL        Import              (IUnknown* pUnk, LPCTSTR pszRefPath);
    virtual BOOL        Export              (IUnknown* pUnk, LPCTSTR pszRefPath);
    virtual BOOL        OnKillActive        (void);
    virtual BOOL        GetMinimumSize      (CSize& size);
    virtual void        OnSetActive         (void);
    virtual BOOL        NameEditValidation  (CEdit* pEdit);
    virtual BOOL        Paste               (IDataObject* pDataObject, 
                                             int iIndex = -1,
                                             AcTcCatalogItemArray* pNewTools = NULL);
    virtual BOOL        CanPaste            (IDataObject* pDataObject);
    BOOL                SetView             (CAcTcUiPaletteView* pView);
    CAcTcUiScheme*      GetScheme           (void) const;

protected:
    //{{AFX_VIRTUAL(CAcTcUiToolPalette)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcTcUiToolPalette)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    afx_msg LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnEndNameEdit(WPARAM, LPARAM);
    DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;           // Imp object CAcTcUiImpToolPalette

private:
    friend class AcTcUiSystemInternals;
};

#endif // Nodef _ADESK_MAC_
#endif //__ACTCUITOOLPALETTE_H__
