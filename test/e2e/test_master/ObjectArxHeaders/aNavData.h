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
// DESCRIPTION:
//      The CNavData object is used to return the results from a file
//      navigation dialog modal session.
/////////////////////////////////////////////////////////////////////////////
#ifndef _ANavData_h
#  define _ANavData_h
#  if  _MSC_VER >= 1000
#    pragma  once
#  endif
/////////////////////////////////////////////////////////////////////////////
class CNavPathname;
enum NAV_DATA_TYPE
{
  kNavUnknown,
  kNavShellItem,
  kNavURL,
  kNavUNC,
  kNavExtension,
  kNavWebFolders
};
#  pragma  warning(push)
#  pragma  warning(disable : 4275)
class ANAV_PORT CNavData : public CObject
{
public:
  CNavData();
  virtual ~CNavData();
protected:
  NAV_DATA_TYPE m_dataType;
  LPITEMIDLIST m_id;
  CString m_text;
  CString m_textInFolder;
  CNavPathname* m_pathname;
  CString m_userName;
  CString m_password;
  CString m_extensionName;
public:
  NAV_DATA_TYPE GetDataType();
  void SetDataType(NAV_DATA_TYPE dataType);
  LPITEMIDLIST GetID();
  void SetID(LPITEMIDLIST id);
  LPCTSTR GetText();
  void SetText(LPCTSTR text);
  LPCTSTR GetTextInFolder();
  void SetTextInFolder(LPCTSTR text);
  CNavPathname* GetPathname();
  void SetPathname(CNavPathname* pathname);
  LPCTSTR GetUserName();
  void SetUserName(LPCTSTR name);
  LPCTSTR GetPassword();
  void SetPassword(LPCTSTR password);
  BOOL IsRemote();
  BOOL IsExtension();
  LPCTSTR GetExtensionName();
  void SetExtensionName(LPCTSTR name);
  BOOL GetURL(CString& strURL);
protected:
  void* m_userData;
public:
  void* GetUserData();
  void* SetUserData(void* data);
};
#  pragma  warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif
