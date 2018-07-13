//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _aduiTabChildDialog_h
#define _aduiTabChildDialog_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _ADESK_MAC_
//////////////////////////////////////////////////////////////////////////////

class ADUI_PORT CAdUiTabChildDialog : public CAdUiDialog {
friend class CAdUiTab;

    DECLARE_DYNAMIC(CAdUiTabChildDialog);

public:
                CAdUiTabChildDialog (
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );

// Tab Child Dialog
private:
        BOOL    m_bDirty;
        HWND    m_hWndFocus;
        CAdUiTab *m_pAcadTab;

        void    SetAcadTabPointer (CAdUiTab *pAcadTab);
        BOOL    TranslateTabKey ();
public:
        CAdUiTab *GetAcadTabPointer ();
        CAdUiTabMainDialog *GetMainDialog ();
        int     GetTabIndex ();
        BOOL    IsDirty ();
virtual void    OnTabActivation (BOOL bActivate);
virtual BOOL    OnTabChanging ();
        void    SetAcadTabChildFocus (HWND hWndFocus);

        // Call this if you've changed your contents and might need saving...
        void    SetDirty (BOOL bDirty=TRUE);

        void    SetValidationInfo (CDataExchange *pDX);

// Elasticity
protected:
virtual void    OnInitDialogBegin ();
virtual void    OnInitDialogFinish ();

// ClassWizard-controlled
public:
    //{{AFX_DATA(CAdUiTabChildDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAdUiTabChildDialog)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual void OnMainDialogCancel();
    virtual void OnMainDialogOK();
    virtual BOOL OnMainDialogHelp();     
    virtual void OnMainDialogApply();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiTabChildDialog)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    afx_msg LRESULT OnResizePage(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

#endif //_ADESK_MAC_
//////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
