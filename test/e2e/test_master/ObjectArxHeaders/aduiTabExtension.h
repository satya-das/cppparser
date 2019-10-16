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
#  define _aduiTabExtension_h
#  pragma  pack (push, 8)
/////////////////////////////////////////////////////////////////////////////
class ADUI_PORT CAdUiTabExtensionManager
{
public:
  CAdUiTabExtensionManager();
  virtual ~CAdUiTabExtensionManager();
private:
  CString m_dlgName;
  CAdUiTabMainDialog* m_pDlg;
  CAdUiTab* m_pTabCtrl;
  BOOL AddApplicationTabs(LPCTSTR pszAppName);
public:
  int AddExtendedTabs();
  virtual BOOL AddTab(HINSTANCE hInstRes, UINT uTemplateID, LPCTSTR pszTabName, CAdUiTabChildDialog* pDialog);
  virtual LPCTSTR GetDialogName();
  void Initialize(CAdUiTab* pTabCtrl, CAdUiTabMainDialog* pDlg);
  CAdUiTab* GetTabControl() const
  {
    return m_pTabCtrl;
  }
};
/////////////////////////////////////////////////////////////////////////////
#  pragma  pack (pop)
#endif
/////////////////////////////////////////////////////////////////////////////
