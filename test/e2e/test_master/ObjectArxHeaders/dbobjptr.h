//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBOBJPTR_H
#  define AD_DBOBJPTR_H
#  include <assert.h>
#  include "dbsymtb.h"
#  ifdef ASSERT
#    define DbObjPtr_Assert	ASSERT
#  elif  defined assert
#    define DbObjPtr_Assert	assert
#  elif  defined _ASSERTE
#    define DbObjPtr_Assert	_ASSERTE
#  else 
#    define DbObjPtr_Assert(T)
#  endif
#  pragma  pack (push, 8)
template <typename T_OBJECT>
class AcDbObjectPointerBase
{
public:
  AcDbObjectPointerBase();
  ~AcDbObjectPointerBase();
  const T_OBJECT* object() const;
  T_OBJECT* object();
  const T_OBJECT* operator->() const;
  T_OBJECT* operator->();
  operator const T_OBJECT*() const;
#  if  DBOBJPTR_EXPOSE_PTR_REF
  operator T_OBJECT*&();
#  else 
  operator T_OBJECT*();
#  endif
  Acad::ErrorStatus openStatus() const;
  Acad::ErrorStatus open(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);
  Acad::ErrorStatus acquire(T_OBJECT*& pObjToAcquire);
  Acad::ErrorStatus release(T_OBJECT*& pReleasedObj);
  Acad::ErrorStatus close();
  Acad::ErrorStatus create();
protected:
  AcDbObjectPointerBase(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased);
#  if  DBOBJPTR_EXPOSE_PTR_REF
  AcDbObjectPointerBase(T_OBJECT* pObject);
  void operator=(T_OBJECT* pObject);
#  endif
  T_OBJECT* m_ptr;
  Acad::ErrorStatus m_status;
private:
  AcDbObjectPointerBase(const AcDbObjectPointerBase&) = delete;
  AcDbObjectPointerBase& operator=(const AcDbObjectPointerBase&);
  Acad::ErrorStatus closeInternal();
};
template <typename T_OBJECT>
class AcDbObjectPointer : public AcDbObjectPointerBase<T_OBJECT>
{
public:
  AcDbObjectPointer();
  AcDbObjectPointer(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);
#  if  DBOBJPTR_EXPOSE_PTR_REF
  AcDbObjectPointer(T_OBJECT* pObject);
  void operator=(T_OBJECT* pObject);
#  endif
  Acad::ErrorStatus open(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);
private:
  AcDbObjectPointer(const AcDbObjectPointer&) = delete;
  AcDbObjectPointer& operator=(const AcDbObjectPointer&);
};
typedef AcDbObjectPointer<AcDbDictionary> AcDbDictionaryPointer;
typedef AcDbObjectPointer<AcDbEntity> AcDbEntityPointer;
template <typename T_OBJECT>
class AcDbSymbolTablePointer : public AcDbObjectPointerBase<T_OBJECT>
{
public:
  AcDbSymbolTablePointer();
  AcDbSymbolTablePointer(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead);
  AcDbSymbolTablePointer(AcDbDatabase* pDb, AcDb::OpenMode mode = AcDb::kForRead);
#  if  DBOBJPTR_EXPOSE_PTR_REF
  AcDbSymbolTablePointer(T_OBJECT* pObject);
  void operator=(T_OBJECT* pObject);
#  endif
  Acad::ErrorStatus open(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus open(AcDbDatabase* pDb, AcDb::OpenMode mode = AcDb::kForRead);
private:
  AcDbSymbolTablePointer(const AcDbSymbolTablePointer&) = delete;
  AcDbSymbolTablePointer& operator=(const AcDbSymbolTablePointer&);
  typedef typename T_OBJECT::RecordType T2;
};
typedef AcDbSymbolTablePointer<AcDbBlockTable> AcDbBlockTablePointer;
typedef AcDbSymbolTablePointer<AcDbDimStyleTable> AcDbDimStyleTablePointer;
typedef AcDbSymbolTablePointer<AcDbLayerTable> AcDbLayerTablePointer;
typedef AcDbSymbolTablePointer<AcDbLinetypeTable> AcDbLinetypeTablePointer;
typedef AcDbSymbolTablePointer<AcDbRegAppTable> AcDbRegAppTablePointer;
typedef AcDbSymbolTablePointer<AcDbTextStyleTable> AcDbTextStyleTablePointer;
typedef AcDbSymbolTablePointer<AcDbUCSTable> AcDbUCSTablePointer;
typedef AcDbSymbolTablePointer<AcDbViewTable> AcDbViewTablePointer;
typedef AcDbSymbolTablePointer<AcDbViewportTable> AcDbViewportTablePointer;
template <typename T_OBJECT>
class AcDbSymbolTableRecordPointer : public AcDbObjectPointerBase<T_OBJECT>
{
public:
  AcDbSymbolTableRecordPointer();
  AcDbSymbolTableRecordPointer(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);
  AcDbSymbolTableRecordPointer(const ACHAR* name, AcDbDatabase* pDb, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);
#  if  DBOBJPTR_EXPOSE_PTR_REF
  AcDbSymbolTableRecordPointer(T_OBJECT* pObject);
  void operator=(T_OBJECT* pObject);
#  endif
  Acad::ErrorStatus open(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);
  Acad::ErrorStatus open(const ACHAR* name, AcDbDatabase* pDb, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);
private:
  AcDbSymbolTableRecordPointer(const AcDbSymbolTableRecordPointer&) = delete;
  AcDbSymbolTableRecordPointer& operator=(const AcDbSymbolTableRecordPointer&);
  typedef typename T_OBJECT::TableType T2;
};
typedef AcDbSymbolTableRecordPointer<AcDbBlockTableRecord> AcDbBlockTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbDimStyleTableRecord> AcDbDimStyleTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbLayerTableRecord> AcDbLayerTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbLinetypeTableRecord> AcDbLinetypeTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbRegAppTableRecord> AcDbRegAppTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbTextStyleTableRecord> AcDbTextStyleTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbUCSTableRecord> AcDbUCSTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbViewTableRecord> AcDbViewTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbViewportTableRecord> AcDbViewportTableRecordPointer;
template <typename T_OBJECT>
inline AcDbObjectPointerBase<T_OBJECT>::AcDbObjectPointerBase()
  : m_ptr(NULL)
  , m_status(Acad::eNullObjectPointer)
{
}
template <typename T_OBJECT>
inline AcDbObjectPointerBase<T_OBJECT>::AcDbObjectPointerBase(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased)
  : m_ptr(NULL)
  , m_status(acdbOpenObject(m_ptr, objId, mode, openErased))
{
}
template <typename T_OBJECT>
inline AcDbObjectPointerBase<T_OBJECT>::~AcDbObjectPointerBase()
{
  if (m_ptr != NULL)
  {
    assert(m_status == Acad::eOk);
    Acad::ErrorStatus closeStatus = closeInternal();
    (void) closeStatus;
    assert(closeStatus == Acad::eOk);
  }
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbObjectPointerBase<T_OBJECT>::open(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased)
{
  if (m_ptr != NULL)
  {
    assert(m_status == Acad::eOk);
    Acad::ErrorStatus closeStatus = closeInternal();
    if (closeStatus != Acad::eOk)
    {
      return closeStatus;
    }
  }
  m_status = acdbOpenObject(m_ptr, objId, mode, openErased);
  return m_status;
}
template <typename T_OBJECT>
inline const T_OBJECT* AcDbObjectPointerBase<T_OBJECT>::object() const
{
  assert(m_status == Acad::eOk);
  assert(m_ptr != NULL);
  DbObjPtr_Assert(m_ptr == NULL || m_ptr->isReadEnabled());
  return m_ptr;
}
template <typename T_OBJECT>
inline T_OBJECT* AcDbObjectPointerBase<T_OBJECT>::object()
{
  assert(m_status == Acad::eOk);
  assert(m_ptr != NULL);
  DbObjPtr_Assert(m_ptr == NULL || m_ptr->isReadEnabled());
  return m_ptr;
}
template <typename T_OBJECT>
inline const T_OBJECT* AcDbObjectPointerBase<T_OBJECT>::operator->() const
{
  return object();
}
template <typename T_OBJECT>
inline T_OBJECT* AcDbObjectPointerBase<T_OBJECT>::operator->()
{
  return object();
}
template <typename T_OBJECT>
operator const T_OBJECT*() const
{
  return object();
}
#  if  DBOBJPTR_EXPOSE_PTR_REF
template <typename T_OBJECT>
operator T_OBJECT*&()
{
  return this->m_ptr;
}
#  else 
template <typename T_OBJECT>
operator T_OBJECT*()
{
  return object();
}
#  endif
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbObjectPointerBase<T_OBJECT>::openStatus() const
{
  return m_status;
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbObjectPointerBase<T_OBJECT>::acquire(T_OBJECT*& pObjToAcquire)
{
  if (pObjToAcquire == NULL)
  {
    return Acad::eNullObjectPointer;
  }
  if (m_ptr != NULL)
  {
    assert(m_status == Acad::eOk);
    Acad::ErrorStatus closeStatus = closeInternal();
    if (closeStatus != Acad::eOk)
    {
      return closeStatus;
    }
  }
  m_ptr = pObjToAcquire;
  m_status = Acad::eOk;
  pObjToAcquire = NULL;
  return Acad::eOk;
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbObjectPointerBase<T_OBJECT>::release(T_OBJECT*& pReleasedObj)
{
  if (m_ptr == NULL)
  {
    return Acad::eNullObjectPointer;
  }
  assert(m_status == Acad::eOk);
  pReleasedObj = m_ptr;
  m_ptr = NULL;
  m_status = Acad::eNullObjectPointer;
  return Acad::eOk;
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbObjectPointerBase<T_OBJECT>::close()
{
  if (m_ptr == NULL)
  {
    return Acad::eNullObjectPointer;
  }
  assert(m_status == Acad::eOk);
  Acad::ErrorStatus closeStatus = closeInternal();
  ADESK_UNREFED_PARAM(closeStatus);
  assert(closeStatus == Acad::eOk);
  return Acad::eOk;
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbObjectPointerBase<T_OBJECT>::create()
{
  T_OBJECT* pObject = new T_OBJECT;
  if (pObject == NULL)
  {
    return Acad::eNullObjectPointer;
  }
  if (m_ptr != NULL)
  {
    assert(m_status == Acad::eOk);
    Acad::ErrorStatus closeStatus = closeInternal();
    if (closeStatus != Acad::eOk)
    {
      delete pObject;
      return closeStatus;
    }
  }
  m_ptr = pObject;
  m_status = Acad::eOk;
  return Acad::eOk;
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbObjectPointerBase<T_OBJECT>::closeInternal()
{
  if (m_ptr == NULL)
  {
    return Acad::eOk;
  }
  Acad::ErrorStatus es = Acad::eOk;
  if (m_ptr->objectId().isNull())
  {
    delete m_ptr;
    es = Acad::eOk;
  }
  else 
  {
    es = m_ptr->close();
  }
  m_ptr = NULL;
  m_status = Acad::eNullObjectPointer;
  return es;
}
template <typename T_OBJECT>
inline AcDbObjectPointer<T_OBJECT>::AcDbObjectPointer()
  : AcDbObjectPointerBase<T_OBJECT>()
{
}
template <typename T_OBJECT>
inline AcDbObjectPointer<T_OBJECT>::AcDbObjectPointer(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased)
  : AcDbObjectPointerBase<T_OBJECT>(objId, mode, openErased)
{
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbObjectPointer<T_OBJECT>::open(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased)
{
  return AcDbObjectPointerBase<T_OBJECT>::open(objId, mode, openErased);
}
template <typename T_OBJECT>
inline AcDbSymbolTablePointer<T_OBJECT>::AcDbSymbolTablePointer()
  : AcDbObjectPointerBase<T_OBJECT>()
{
}
template <typename T_OBJECT>
inline AcDbSymbolTablePointer<T_OBJECT>::AcDbSymbolTablePointer(AcDbObjectId objId, AcDb::OpenMode mode)
  : AcDbObjectPointerBase<T_OBJECT>(objId, mode, false)
{
}
template <typename T_OBJECT>
inline AcDbSymbolTablePointer<T_OBJECT>::AcDbSymbolTablePointer(AcDbDatabase* pDb, AcDb::OpenMode mode)
  : AcDbObjectPointerBase<T_OBJECT>()
{
  this->m_status = (pDb == NULL) ? Acad::eNullObjectPointer : pDb->getSymbolTable(this->m_ptr, mode);
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbSymbolTablePointer<T_OBJECT>::open(AcDbObjectId objId, AcDb::OpenMode mode)
{
  return AcDbObjectPointerBase<T_OBJECT>::open(objId, mode, false);
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbSymbolTablePointer<T_OBJECT>::open(AcDbDatabase* pDb, AcDb::OpenMode mode)
{
  if (pDb == NULL)
  {
    return Acad::eInvalidInput;
  }
  Acad::ErrorStatus es = Acad::eOk;
  if (this->m_ptr != NULL)
  {
    es = this->close();
  }
  if (es == Acad::eOk)
  {
    es = pDb->getSymbolTable(this->m_ptr, mode);
    this->m_status = es;
  }
  return es;
}
template <typename T_OBJECT>
inline AcDbSymbolTableRecordPointer<T_OBJECT>::AcDbSymbolTableRecordPointer()
  : AcDbObjectPointerBase<T_OBJECT>()
{
}
template <typename T_OBJECT>
inline AcDbSymbolTableRecordPointer<T_OBJECT>::AcDbSymbolTableRecordPointer(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased)
  : AcDbObjectPointerBase<T_OBJECT>(objId, mode, openErased)
{
}
template <typename T_OBJECT>
inline AcDbSymbolTableRecordPointer<T_OBJECT>
    ::AcDbSymbolTableRecordPointer(const ACHAR* name, AcDbDatabase* pDb, AcDb::OpenMode mode, bool openErased)
  : AcDbObjectPointerBase<T_OBJECT>()
{
  if (name == NULL)
  {
    this->m_status = Acad::eInvalidInput;
  }
  else 
  {
    AcDbSymbolTablePointer<typename T_OBJECT::TableType> pTable(pDb, AcDb::kForRead);
    this->m_status = pTable.openStatus();
    if (this->m_status == Acad::eOk)
    {
      this->m_status = pTable->getAt(name, this->m_ptr, mode, openErased);
    }
  }
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbSymbolTableRecordPointer<T_OBJECT>::open(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased)
{
  return AcDbObjectPointerBase<T_OBJECT>::open(objId, mode, openErased);
}
template <typename T_OBJECT>
inline Acad::ErrorStatus AcDbSymbolTableRecordPointer<T_OBJECT>
    ::open(const ACHAR* name, AcDbDatabase* pDb, AcDb::OpenMode mode, bool openErased)
{
  if (name == NULL)
  {
    return Acad::eInvalidInput;
  }
  else 
  {
    AcDbSymbolTablePointer<typename T_OBJECT::TableType> pTable(pDb, AcDb::kForRead);
    Acad::ErrorStatus es = pTable.openStatus();
    if (es == Acad::eOk)
    {
      if (this->m_ptr != NULL)
      {
        es = this->close();
      }
      if (es == Acad::eOk)
      {
        es = pTable->getAt(name, this->m_ptr, mode, openErased);
        this->m_status = es;
      }
    }
    return es;
  }
}
#  if  DBOBJPTR_EXPOSE_PTR_REF
template <typename T_OBJECT>
inline AcDbObjectPointerBase<T_OBJECT>::AcDbObjectPointerBase(T_OBJECT* pObject)
  : m_ptr(NULL)
  , m_status(Acad::eNullObjectPointer)
{
  if (pObject != NULL)
  {
    this->acquire(pObject);
  }
}
template <typename T_OBJECT>
inline void AcDbObjectPointerBase<T_OBJECT>::operator=(T_OBJECT* pObject)
{
  if (pObject == NULL)
  {
    DbObjPtr_Assert(this->m_ptr == NULL);
  }
  else 
  {
    this->acquire(pObject);
  }
}
template <typename T_OBJECT>
inline AcDbObjectPointer<T_OBJECT>::AcDbObjectPointer(T_OBJECT* pObject)
  : AcDbObjectPointerBase<T_OBJECT>(pObject)
{
}
template <typename T_OBJECT>
inline AcDbSymbolTablePointer<T_OBJECT>::
        AcDbSymbolTablePointer(T_OBJECT* pObject)
  : AcDbObjectPointerBase<T_OBJECT>(pObject)
{
}
template <typename T_OBJECT>
inline AcDbSymbolTableRecordPointer<T_OBJECT>::
        AcDbSymbolTableRecordPointer(T_OBJECT* pObject)
  : AcDbObjectPointerBase<T_OBJECT>(pObject)
{
}
template <typename T_OBJECT>
inline void AcDbObjectPointer<T_OBJECT>::operator=(T_OBJECT* pObject)
{
  AcDbObjectPointerBase<T_OBJECT>::operator =(pObject);
}
template <typename T_OBJECT>
inline void AcDbSymbolTablePointer<T_OBJECT>::operator=(T_OBJECT* pObject)
{
  AcDbObjectPointerBase<T_OBJECT>::operator =(pObject);
}
template <typename T_OBJECT>
inline void AcDbSymbolTableRecordPointer<T_OBJECT>::operator=(T_OBJECT* pObject)
{
  AcDbObjectPointerBase<T_OBJECT>::operator =(pObject);
}
#  endif
#  pragma  pack (pop)
#endif
