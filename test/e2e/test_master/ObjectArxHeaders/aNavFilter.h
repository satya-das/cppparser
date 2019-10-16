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
//      A CNavFilter is a CStringArray corresponding to a single
//      entry in the "files of type" combobox. It is seen by the user as,
//      for example, "Image Files(*.bmp,*.jpg)". Each extension is a string in
//      the array.
/////////////////////////////////////////////////////////////////////////////
#ifndef _ANavFilter_h
#  define _ANavFilter_h
#  pragma  once
/////////////////////////////////////////////////////////////////////////////
#  pragma  warning(push)
#  pragma  warning(disable : 4275)
class ANAV_PORT CNavFilter : public CStringArray
{
public:
  CNavFilter();
  virtual ~CNavFilter();
private:
  BOOL m_bFullDescription;
protected:
  CString m_description;
  INT_PTR m_tagIndex;
public:
  LPCTSTR GetDescription();
  void SetDescription(LPCTSTR desc);
  void GetFullDescription(CString& desc);
  void SetFullDescription(LPCTSTR desc);
  INT_PTR GetTagIndex();
  void SetTagIndex(INT_PTR tagIndex);
  int Find(LPCTSTR str);
  int GetCount();
  BOOL IsAllowed(LPCTSTR fileName);
  LPTSTR SetFrom(LPTSTR str, BOOL bUseFullDescrition = FALSE);
  BOOL GetMultiSelectAllowed();
  void SetMultiSelectAllowed(BOOL bMultiSelection);
};
#  pragma  warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif
