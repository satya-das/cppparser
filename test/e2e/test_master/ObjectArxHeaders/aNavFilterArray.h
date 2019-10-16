//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ANavFilterArray_h
#  define _ANavFilterArray_h
#  if  _MSC_VER >= 1000
#    pragma  once
#  endif
/////////////////////////////////////////////////////////////////////////////
#  pragma  warning(push)
#  pragma  warning(disable : 4275)
class ANAV_PORT CNavFilterArray : public CNavArray<CNavFilter>
{
public:
  CNavFilterArray();
  virtual ~CNavFilterArray();
  void SetFrom(LPCTSTR str, BOOL bUseFullDescrition = FALSE);
  int Find(LPCTSTR str);
  int FindExact(LPCTSTR str);
};
#  pragma  warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif
