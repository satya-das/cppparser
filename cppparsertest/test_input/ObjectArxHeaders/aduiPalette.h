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
// Purpose:
//
// Palette is a borderless window which holds the actual contents of a 
// palette. The palette can be tool palette, property palette, command line 
// palette, etc. The palette is always embedded as a child window in the 
// client area of a palette set and it is never displayed alone. This class 
// implements the basic functions of a palette and serves as the base class 
// for specific palettes. The specific palettes should derive from this 
// class and implement the required functionality.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _ADUI_PALETTE_H_
#define _ADUI_PALETTE_H_

#include "aduiDropTarget.h"

class CAdUiPaletteSet;


// Palette Styles
#define PS_EDIT_NAME           0x00000001 // Support editing of palette set name through in-place editing


/////////////////////////////////////////////////////////////////////////////
//
// class CAdUiPalette
//
#ifndef _ADESK_MAC_
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiPalette : public CWnd
{
    DECLARE_DYNAMIC(CAdUiPalette)

public:
    CAdUiPalette();
    virtual ~CAdUiPalette();

    // Creates the palette window
    BOOL Create(DWORD dwStyle, LPCTSTR pszName, CAdUiPaletteSet* pParent,
                DWORD dwPaletteStyle = 0);

    // Virtual method for "On demand" creation of palette windows.  Return TRUE for
    // successful creation.
    virtual BOOL Create(CAdUiPaletteSet* pParent);

    // Returns the palette style
    DWORD GetPaletteStyle();
    // Sets the palette style.
    void SetPaletteStyle(DWORD dwStyle);

    // Style access methods
    BOOL EditNameStyle()
        { return m_dwStyle & PS_EDIT_NAME; }

    // Load the data from xml.
    virtual BOOL Load(IUnknown* pUnk);
    // Save the data to xml.
    virtual BOOL Save(IUnknown* pUnk);

    // Returns the palette set back pointer.
    CAdUiPaletteSet* GetPaletteSet() { return m_pPaletteSet; };
    // Sets the palette set back pointer.
    void SetPaletteSet(CAdUiPaletteSet* pSet);

    // Called by the palette set when the palette is made active
    virtual void OnSetActive();
    // Called by the palette set when this palette loses its current 
    // palette state and some other palette is going to be current 
    // palette. Override this member function to perform tasks when 
    // a palette is de-activated. The override of this member function 
    // should call the base class version before any other processing 
    // is done.
    virtual BOOL OnKillActive();

    __declspec(deprecated) virtual CString GetClassNameW();
    
    // Returns the name of the palette.
    CString GetName();

    // Sets the name of the palette.
    void SetName(CString strName);
    
    // Gets the minimum size of the palette in the palette set
    virtual BOOL GetMinimumSize(CSize& size);
    // Gets the maximum size of the palette in the palette set
    virtual BOOL GetMaximumSize(CSize& size);

    // Return false to indicate that the palette should not give up focus,
    // true to indicate that the palette doesn't need focus.
    virtual bool CanFrameworkTakeFocus();

    // In-place editing of palette name at a specified location
    virtual void EditName(CPoint & ptLoc);

    // In-place editing of palette name centered on the palette's tab.  Intended for use
    // only in cases where the palette has a visible tab in it's containing palette set.
    virtual void EditName();

    // Called when the editing of the palette name using in-place editing is completed
    // Return of TRUE means the name is valid.
    virtual BOOL NameEditValidation(CEdit* pEdit);

    // derived palette can override this method to do any theme initialization either
    // when the palette is created or its parent palette set forces an theme update
    // of its contained palettes.
    virtual void InitPaletteTheme() {}

    static bool PaletteNameEditInProgress();


protected:
    // Specialized background erasing
    afx_msg BOOL    OnEraseBkgnd(CDC *pdc);  // INTERNAL USE ONLY

    // Default "SetCursor" implementation
    afx_msg BOOL    OnSetCursor(CWnd *pwnd, UINT nHitTest, UINT msg);

    afx_msg void    OnLButtonDown(UINT nFlags, CPoint pt);

    afx_msg LRESULT OnBeginNameEdit(WPARAM, LPARAM);  // INTERNAL USE ONLY
    afx_msg LRESULT OnEndNameEdit(WPARAM, LPARAM);  // INTERNAL USE ONLY

    DECLARE_MESSAGE_MAP()

private:
    CString                 m_sName;
    CAdUiPaletteSet *       m_pPaletteSet;
    CObArray                m_arrayColors;
    DWORD                   m_dwStyle;
    static UINT             m_nNextPaletteId;
    CEdit *                 m_pLabelEdit;
    static bool             m_bPaletteNameEditInProgress;
};
#pragma warning(pop)
#endif // Nodef _ADESK_MAC_
#endif // _ADUI_PALETTE_H_
