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
// Name:            AcTcUiScheme.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUISCHEME_H__
#define __ACTCUISCHEME_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcTcUiToolPaletteSet.h"
#include "AcTcUi.h"

class AcTcUiSystemInternals;

class ACTCUI_PORT CAcTcUiScheme : public CObject
{
public:
    enum RefreshScope {
        kAllPalettes                    = (0x1 << 0),
        kRefreshEnabledPalettes         = (0x1 << 1),
        kAutoRefreshEnabledPalettes     = (0x1 << 2),
    };

    enum ShowOption {
        kShow                           = (0x1 << 0),
        kHide                           = (0x1 << 1),
		kSaveState						= (0x1 << 2),
        kRestoreState                   = (0x1 << 3),
    };

    CAcTcUiScheme(AcTcScheme* pScheme);
	virtual ~CAcTcUiScheme();

    BOOL                Load                (IUnknown* pUnknown);
    BOOL                Save                (IUnknown* pUnknown);
    BOOL                Unload              (void);
    CAcTcUiToolPaletteSet* CreatePaletteSet (LPCTSTR pszPalSetName);
    CAcTcUiToolPaletteSet* GetPaletteSet    (void);
    BOOL                FindPalette         (const AcTcCatalogItem* pItem, 
                                             CAcTcUiToolPalette** ppToolPalette) const;
    BOOL                FindPalette         (const AcTcCatalogItem* pItem, 
                                             CAcTcUiToolPalette** ppToolPalette,
                                             CAcTcUiToolPaletteSet** ppToolPaletteSet) const;
    BOOL                FindPalette         (const GUID& itemId,
                                             CAcTcUiToolPalette** ppToolPalette) const;
    BOOL                FindPalette         (const GUID& itemId,
                                             CAcTcUiToolPalette** ppToolPalette,
                                             CAcTcUiToolPaletteSet** ppToolPaletteSet) const;
    BOOL                Export              (LPCTSTR pszFile);
    BOOL                Export              (LPCTSTR pszFile,
                                             const AcTcUiToolPaletteArray* palettes);
    BOOL                Import              (LPCTSTR pszFile);
    BOOL                Refresh             (RefreshScope nScope);
    BOOL                Refresh             (RefreshScope nScope,
                                             DWORD dwRefreshFlag);
    BOOL                Show                (ShowOption nOption,
											 LONG_PTR lKey);

protected:
    void            *   mpImpObj;

private:
    friend class AcTcUiSystemInternals;
};


#endif //__ACTCUISCHEME_H__
