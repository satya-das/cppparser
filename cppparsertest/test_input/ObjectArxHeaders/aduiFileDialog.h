//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _aduiFileDialog_h
#define _aduiFileDialog_h
#pragma pack (push, 8)

#pragma once

#ifndef kDialogOptionNone
#define kDialogOptionNone       0
#endif

#ifndef kDialogOptionUseTips
#define kDialogOptionUseTips       1
#endif

#ifndef kDialogOptionUseTipsForContextHelp
#define kDialogOptionUseTipsForContextHelp       2
#endif

#ifndef _ADESK_MAC_

//////////////////////////////////////////////////////////////////////////////
// Common File Dialog
//
// Essentialy a straight port of CAdUiBaseDialog, except for the constructor.
#pragma warning(push)
#pragma warning(disable : 4275)

class ADUI_PORT CAdUiFileDialog : public CFileDialog {
    DECLARE_DYNAMIC(CAdUiFileDialog);

public:
                CAdUiFileDialog (
                    BOOL bOpenFileDialog,
                    LPCTSTR lpszDefExt=NULL,
                    LPCTSTR lpszFileName=NULL,
                    DWORD dwFlags=OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                    LPCTSTR lpszFilter=NULL,
                    CWnd *pParentWnd=NULL,
                    HINSTANCE hDialogResource=NULL                     
                );
virtual         ~CAdUiFileDialog ();

// AdUi message handlers
protected:
virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual ADUI_REPLY OnNotifyControlChange (UINT controlId, LPARAM lParam);
virtual ADUI_REPLY OnNotifyControlValid (UINT controlId, BOOL isValid);
virtual ADUI_REPLY OnNotifyGeneric (UINT controlId, LPARAM lParam);
virtual ADUI_REPLY OnNotifyUpdateTip (CWnd *control);

// Drawing Editor Interaction
private:
        HINSTANCE m_commandResourceInstance;
        BOOL    m_commandWindowWasEnabled;
        HWND    m_commandWindowWithFocus;
        
protected:
        ADUI_COMMAND_STATE m_commandState;

        void    BeginEditorCommand ();
        void    CancelEditorCommand ();
        void    CompleteEditorCommand (BOOL restoreDialogs=TRUE);
        void    MakeDialogsVisible (BOOL visible);
public:
        BOOL    EditorCommandCancelled ();

// Context help
protected:
        CString m_contextHelpFileName;
        CString m_contextHelpFullPathName;
        CString m_contextHelpPrefix;    // Must be 4 ASCII characters.

virtual BOOL    FindContextHelpFullPath (LPCTSTR fileName, CString& fullPath);
public:
        LPCTSTR GetContextHelpFileName ();    
        void    SetContextHelpFileName (LPCTSTR pFileName);
        LPCTSTR GetContextHelpFullPathName ();    
        void    SetContextHelpFullPathName (LPCTSTR pFullPathName);
        LPCTSTR GetContextHelpPrefix ();    
        void    SetContextHelpPrefix (LPCTSTR pPrefix);
        void    SetDialogName (LPCTSTR name);
        void    SetDialogHelpTag (LPCTSTR tag) {m_dlgHelpTag = tag;}
        void    GetDialogName (CString& name) {name = m_dlgName;}
        void    GetDialogHelpTag (CString& tag) {tag = m_dlgHelpTag;}   
    
// Misc.
private:
        HINSTANCE m_hDialogResourceSaved;
        CString m_dlgHelpTag;       // The help string tag for this dialog.
        CString m_dlgName;          // The name of our dialog        
        CImageList *m_pNavButtonImageList;

protected:
        int    m_bUseTips;
        HINSTANCE m_hDialogResource;
        HICON   m_hIcon;
        CAdUiTextTip *m_pTextTip;
        CToolTipCtrl *m_pToolTip;
        CString m_rootKey;
        CWnd* m_pParent;

virtual void    OnInitDialogBegin ();
virtual void    OnInitDialogFinish ();
public:
virtual CWnd    *AppMainWindow ();
virtual HINSTANCE AppResourceInstance ();
virtual LPCTSTR AppRootKey ();
virtual void    EnableFloatingWindows (BOOL allow);
        int    GetUseTips ();
        void    SetUseTips (int useTips);
        HICON   GetDialogIcon();
        void    SetDialogIcon(HICON hIcon);        
virtual void OnDialogHelp();    // Override this to provide dialog help.        
virtual BOOL DoDialogHelp();
    void AutoHiDPIScaleNavButtons();


// ClassWizard-controlled
public:
    //{{AFX_DATA(CAdUiFileDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAdUiFileDialog)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual INT_PTR DoModal();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void PostNcDestroy();
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiFileDialog)
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg BOOL OnHelpInfo(HELPINFO* lpHelpInfo);    
    //}}AFX_MSG
    afx_msg BOOL OnNotify_ToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)

#endif //_ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
