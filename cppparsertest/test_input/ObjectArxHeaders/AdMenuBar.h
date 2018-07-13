/////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2009-2011 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AdMenuBar.h
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AdExportDef.h"

class AdImpMenuBar;

/// <summary>
/// LPFNADMENUCALLBACK is a callback for Menu.
/// </summary>
typedef bool (CALLBACK *LPFNADMENUCALLBACK)(unsigned int nItemId);

//////////////////////////////////////////////////////////////////
// MenuBar

/// <summary>
/// The application frame menu bar. 
/// </summary>                      
class ADAF_PORT AdMenuBar
{
    friend class AdApplicationFrame;

public:
    virtual ~AdMenuBar();

    bool GetMenuItemHelpString(UINT nItemID, const wchar_t **wszHelpString);
    bool RemoveMenuItem(HMENU hMenu, UINT nMenuItemId);
    bool AddMenuItem(HMENU hMenu, UINT nPos, const MENUITEMINFO& menuItem, 
        LPFNADMENUCALLBACK pfnCallback, const wchar_t *wszHelpString);
    bool SetMenuHandle(HMENU hMenu);
    void UpdateMenu();
    HMENU GetMenuHandle();
    bool TrackingPopup();
    void SetChildWindowMenuPopup(bool bShow);
    bool GetChildWindowMenuPopup(void);

private:
    AdMenuBar(AdImpMenuBar* pImpMenuBar);
    AdMenuBar();

    /// <summary>
    /// Member pointer to the implementation class of the class
    /// AdMenuBar. 
    /// </summary>                                             
    AdImpMenuBar *mpImpMenuBar;
};