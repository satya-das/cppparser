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
// DESCRIPTION
//
//   Include file for classes dealing with extended tabs.
//                  
/////////////////////////////////////////////////////////////////////////////

#ifndef _aduiTabExtension_h
#define _aduiTabExtension_h
#pragma pack (push, 8)

/////////////////////////////////////////////////////////////////////////////
// This class manages extended tabs in a tab extensible dialog.
// A tab extensible dialog has one instance of this class in the
// dialog object which is initialized in the dialog's constructor.

class ADUI_PORT CAdUiTabExtensionManager {
public:
                CAdUiTabExtensionManager ();
virtual         ~CAdUiTabExtensionManager ();    

// Tab Extension Manager
private:
        CString m_dlgName;              // Buffer for GetDialogName().
        CAdUiTabMainDialog *m_pDlg;     // The tab extensible dialog.
        CAdUiTab *m_pTabCtrl;           // The tab control in the dialog.

        // Adds tabs to a dialog that have been registered by a particular application.
        BOOL    AddApplicationTabs (LPCTSTR pszAppName);
public:
        // This function in called in the OnInitDialog() of a tab extensible
        // dialog to add extended tabs to itself.
        int     AddExtendedTabs ();

        // Actually adds an extended tab.
virtual BOOL    AddTab (
                    HINSTANCE hInstRes,
                    UINT uTemplateID,
                    LPCTSTR pszTabName,         // since templates don't have captions...
                    CAdUiTabChildDialog *pDialog
                );

        // Return the dialog name used as a registry key for extended tabs.
virtual LPCTSTR GetDialogName ();
    
        // Initialize the manager.
        void    Initialize (CAdUiTab *pTabCtrl, CAdUiTabMainDialog *pDlg);

        CAdUiTab* GetTabControl() const {return m_pTabCtrl;}
};

/////////////////////////////////////////////////////////////////////////////

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
