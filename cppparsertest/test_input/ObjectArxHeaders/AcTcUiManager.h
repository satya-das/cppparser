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
// Name:            AcTcUiManager.h
//
// Description:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUIMANAGER_H__
#define __ACTCUIMANAGER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gepnt3d.h"
#include "AcTcUiToolPaletteSet.h"
#include "AcTcUi.h"

class AcTcUiSystemInternals;
#ifndef _ADESK_MAC_
class ACTCUI_PORT CAcTcUiManager  
{
public:
    CAcTcUiManager();
	virtual ~CAcTcUiManager();
    CAcTcUiToolPaletteSet* GetToolPaletteWindow(void);
    BOOL                Load                (IUnknown* pUnknown);
    BOOL                Save                (IUnknown* pUnknown);
    BOOL                SetApplicationWindow(HWND hWndApp);
    HWND                GetApplicationWindow(void);
    COleDropTarget*     GetDropTarget       (void);
    CAcTcUiToolPalette* CreatePalette       (LPCTSTR pszPalName = NULL,
                                             DWORD dwFlags = 0);
    BOOL                Export              (LPCTSTR pszFile,
                                            const AcTcUiToolPaletteArray* palettes = NULL);
    BOOL                Import              (LPCTSTR pszFile);
    BOOL                FindPalette         (const AcTcCatalogItem* pItem,
                                             CAcTcUiToolPalette** ppToolPalette) const;
    BOOL                FindPalette         (const GUID& itemId,
                                             CAcTcUiToolPalette** ppToolPalette) const;
    BOOL                ShowToolPaletteWindow(BOOL bShow = TRUE);
    BOOL                IsToolPaletteWindowVisible(void) const;
    int                 GetToolFilterCount  (void) const;
    int                 AddToolFilter       (LPCTSTR pszProductName,
                                             int nMajorVersion,
                                             int nMinorVersion,
                                             DWORD dwLocaleId);
    BOOL                GetToolFilter       (int iIndex, 
                                             LPTSTR pszProductName,
                                             int* pMajorVersion,
                                             int* pMinorVersion,
                                             DWORD* pLocaleId) const;
    BOOL                DeleteToolFilter    (int iIndex);
    CAcTcUiScheme*      GetScheme           (LPCTSTR pszName) const;
    CAcTcUiScheme*      GetScheme           (int nIndex);
    int                 GetSchemeCount      (void);
    int                 AddScheme           (CAcTcUiScheme* pUiScheme);
    BOOL                RemoveScheme        (CAcTcUiScheme* pUiScheme);
    void                NotifyDropPoint     (const AcGePoint3d& point);

    /// <summary>For Autodesk internal use only.</summary>
    /// <param name="ADUI_DRAGDATA*">For Autodesk internal use only.</param>
    BOOL                ExecuteTool         (ADUI_DRAGDATA* pDragData);

    /// <summary>For Autodesk internal use only.</summary>
    /// <param name="ADUI_DRAGDATA*">For Autodesk internal use only.</param>
    void                CreatePalette       (ADUI_DRAGDATA* pDragData);

protected:
    void            *   mpImpObj;

private:
    friend class AcTcUiSystemInternals;
};

#endif // Nodef _ADESK_MAC_
#endif //__ACTCUIMANAGER_H__
