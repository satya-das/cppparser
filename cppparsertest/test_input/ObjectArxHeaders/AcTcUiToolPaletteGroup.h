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
// Name:            AcTcUiToolPaletteGroup.h
//
// Description:     Header for CAcTcUiToolPaletteGroup class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcTcUiToolPalette.h"


class CAcTcUiImpToolPaletteGroup;
class CAcTcUiImpToolPaletteSet;


class ACTCUI_PORT CAcTcUiToolPaletteGroup : public CObject
{
    DECLARE_DYNAMIC(CAcTcUiToolPaletteGroup);

public:
    CAcTcUiToolPaletteGroup();
    virtual ~CAcTcUiToolPaletteGroup();

    BOOL            Reset                   (void);
    CString         GetName                 (void) const;
    BOOL            SetName                 (LPCTSTR pszName);
    CString         GetDescription          (void) const;
    BOOL            SetDescription          (LPCTSTR pszDesc);
    BOOL            IsItemPalette           (int iIndex) const;
    int             AddItem                 (CAcTcUiToolPalette* pPalette);
    int             AddItem                 (CAcTcUiToolPaletteGroup* pGroup);
    int             InsertItem              (int iIndex, 
                                             CAcTcUiToolPalette* pPalette);
    int             InsertItem              (int iIndex, 
                                             CAcTcUiToolPaletteGroup* pGroup);
    int             GetItemCount            (void) const;
    BOOL            GetItem                 (int iIndex, 
                                             CAcTcUiToolPalette*& pPalette) const;
    BOOL            GetItem                 (int iIndex, 
                                             CAcTcUiToolPaletteGroup*& pGroup) const;
    BOOL            DeleteItem              (CAcTcUiToolPalette* pPalette, 
                                             BOOL bRecursive = FALSE);
    BOOL            DeleteItem              (CAcTcUiToolPaletteGroup* pGroup);
    BOOL            RemoveItem              (CAcTcUiToolPalette* pPalette, 
                                             BOOL bRecursive = FALSE);
    BOOL            RemoveItem              (CAcTcUiToolPaletteGroup* pGroup);
    BOOL            DeleteAllPalettes       (void);
    BOOL            DeleteAllItems          (void);
    int             GetActivePalette        (void) const;
    BOOL            SetActivePalette        (int nIndex);
    BOOL            GetCustomData           (IUnknown** ppUnknown);
    virtual BOOL    Load                    (IUnknown* pUnk);
    virtual BOOL    Save                    (IUnknown* pUnk);
    virtual BOOL    Clone                   (CAcTcUiToolPaletteGroup*& pClone);
    CAcTcUiToolPaletteGroup* FindGroup      (LPCTSTR pszGroup, 
                                             BOOL bRecursive = TRUE);
    CAcTcUiToolPalette* FindPalette         (LPCTSTR pszPalName, 
                                             CAcTcUiToolPaletteGroup** ppGroup, 
                                             BOOL bRecursive = TRUE) const;

protected:
    void            *   mpImpObj;

private:
    friend class AcTcUiSystemInternals;
};

