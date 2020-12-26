//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ANavArray_h
#  define _ANavArray_h
#  pragma  once
#  include "afxtempl.h"
/////////////////////////////////////////////////////////////////////////////
// File Navigation Array
template <typename T>
class CNavArray : public CTypedPtrArray<CObArray, T*>
{
public:
  CNavArray();
  virtual ~CNavArray();
// Data management
protected:
  virtual T* NewData();
public:
  T* AddData();
  int GetCount();
  T* GetData(INT_PTR index);
  BOOL IsIndexValid(INT_PTR index);
  void RemoveData(INT_PTR index);
  void RemoveAllData();
};
/////////////////////////////////////////////////////////////////////////////
// File Navigation Array - implementation
template <typename T>
CNavArray<T>::CNavArray()
  : 
    CTypedPtrArray<CObArray, T*>()

  {

  }
template <typename T>
CNavArray<T>::~CNavArray()
{

    RemoveAllData();
}
//----------------
// Data management
template <typename T>
T* CNavArray<T>::AddData()
{
    T    *d = NewData();

    ASSERT(d != NULL);
    if (d != NULL)
        this->Add(d);
    return d;
}
template <typename T>
int CNavArray<T>::GetCount()
{
    const size_t nCount = this->GetUpperBound() + 1;
    ASSERT(nCount < 0x1000000);   // 16M sanity check
    return (int)nCount;
}
template <typename T>
T* CNavArray<T>::GetData(INT_PTR index)
{
    T    *d = NULL;

    if (IsIndexValid(index))
        d = this->GetAt(index);
    return d;
}
template <typename T>
BOOL CNavArray<T>::IsIndexValid(INT_PTR index)
{
    return ((index >= 0) && (index <= this->GetUpperBound()));
}
template <typename T>
T* CNavArray<T>::NewData()
{
    return new T;
}
template <typename T>
void CNavArray<T>::RemoveData(INT_PTR index)
{
    T    *d;

    if (IsIndexValid(index)) {
        d = this->GetAt(index);
        this->RemoveAt(index);
        delete d;
    }
}
template <typename T>
void CNavArray<T>::RemoveAllData()
{
    const int  n = this->GetCount();

    for (int i = 0; i < n; i++) {
        T *d = this->GetAt(i);
        delete d;
    }
    this->RemoveAll();
#ifndef _ADESK_MAC_
    this->FreeExtra();
#endif //_ADESK_MAC_
}
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
#endif
