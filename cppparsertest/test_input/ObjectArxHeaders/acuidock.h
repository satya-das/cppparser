//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _acuiDock_h
#define _acuiDock_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAcUiDockFrame window - INTERNAL USE ONLY

class ACUI_PORT CAcUiDockFrame : public CAdUiDockFrame {
    DECLARE_DYNCREATE(CAcUiDockFrame);

public:
	            CAcUiDockFrame ();
virtual         ~CAcUiDockFrame ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiDockFrame)
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiDockFrame)
    afx_msg LRESULT OnACADKeepFocus (WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAcUiDockControlBar window

class ACUI_PORT CAcUiDockControlBar : public CAdUiDockControlBar {
    DECLARE_DYNCREATE(CAcUiDockControlBar);

public:
    CAcUiDockControlBar () {}

protected:
    virtual bool CanFrameworkTakeFocus ();
};

#ifndef NEW_PALETTE
/////////////////////////////////////////////////////////////////////////////
// CAcUiPaletteSetDockFrame window - INTERNAL USE ONLY

class ACUI_PORT CAcUiPaletteSetDockFrame : public CAdUiPaletteSetDockFrame {
    DECLARE_DYNCREATE(CAcUiPaletteSetDockFrame);

public:
	            CAcUiPaletteSetDockFrame ();
virtual         ~CAcUiPaletteSetDockFrame ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CAcUiPaletteSetDockFrame)
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiPaletteSetDockFrame)
    afx_msg LRESULT OnACADKeepFocus (WPARAM wParam, LPARAM lParam);
    afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};
#endif // NEW_PALETTE

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
