//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiTabMainDialog_h
#define _aduiTabMainDialog_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////

class ADUI_PORT CAdUiTabMainDialog : public CAdUiDialog {
friend class CAdUiTab;

    DECLARE_DYNAMIC(CAdUiTabMainDialog);

public:
  	            CAdUiTabMainDialog (
                    UINT idd,
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );

// Tab Dialog
private:
        // This member variable holds the ID of the button which is meant
        // to be the default button in cases where no other button needs to
        // be the default button, that is, it holds the default "default button".
        int m_idDefaultButton;

        CAdUiTab *m_pAcadTab;

        // The initial tab index as a string. Empty if not set.
        CString m_strTabIndex;

        BOOL    TranslateTabKey ();
protected:
        void    SetAcadTabPointer (CAdUiTab *pAcadTab);

public:
        // A tab extensible dialog calls this to add extended tabs.
        int     AddExtendedTabs ();    

        // Function to provide outside access to the default "default button".
        int     GetDefaultButton ();

        CAdUiTab *GetTabControl ();

        // Function to specify the default "default button".  This MUST be set
        // by the derived class, probably in its dialog initialization function.
        void    SetDefaultButton (int nIdDefaultButton);

        // Function to make sure the correct button is made the default button.
        void    UpdateDefaultButton (HWND hFocusBefore, HWND hFocusAfter);

        void    SetInitialTabIndex(LPCTSTR strTabIndex) {m_strTabIndex = strTabIndex;}
        LPCTSTR GetInitialTabIndex() {return m_strTabIndex;}
        int     GetInitialRequestedTabIndex();
        
// Elasticity
protected:
virtual void    OnInitDialogBegin ();
virtual void    OnInitDialogFinish ();

// Tab Extensions
protected:
        CAdUiTabExtensionManager m_xtabManager;

public:
virtual BOOL    AddApplicationTabs (LPCTSTR pszAppName);
        CAdUiTabExtensionManager *GetXtabPointer ();

// Tab Removal and Restoration
public:
        BOOL    AddTab (
                    int iPos, LPCTSTR tabName,
                    UINT uTemplateID, CAdUiTabChildDialog *pDialog
                );
        BOOL    AddTab (
                    int iPos, UINT uTabStringID,
                    UINT uTemplateID, CAdUiTabChildDialog *pDialog
                );
        int     GetTabIndex (CAdUiTabChildDialog *pDialog);
        BOOL    RemoveTab (int iPos);

// ClassWizard-controlled
public:
	//{{AFX_DATA(CAdUiTabMainDialog)
	enum { IDD = 0 };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAdUiTabMainDialog)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);        // INTERNAL USE ONLY
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnCancel();
    virtual void OnOK();
    void RaiseApplyEvent();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAdUiTabMainDialog)
    afx_msg void OnSize(UINT nType, int cx, int cy);    // INTERNAL USE ONLY
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

#endif //_ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
