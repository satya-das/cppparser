//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef __AXOBJREF_H_
#  define __AXOBJREF_H_
#  include "dbobjptr.h"
#  pragma  pack (push, 8)
#  pragma  warning (disable : 4786)
class AcAxObjectRef
{
public:
  AcAxObjectRef();
  AcAxObjectRef(AcDbObjectId objId);
  AcAxObjectRef(AcDbObject*& pObj);
  ~AcAxObjectRef();
  Acad::ErrorStatus acquire(AcDbObjectId objId);
  Acad::ErrorStatus acquire(AcDbObject*& pObj);
  Acad::ErrorStatus release(AcDbObjectId& objId, AcDbObject*& pObj);
  bool isNull();
  AcDbObjectId objectId();
private:
  AcAxObjectRef(AcAxObjectRef& ref);
  AcAxObjectRef& operator=(AcAxObjectRef& ref);
  void internalRelease();
  AcDbObjectId m_objId;
  AcDbObject* m_pObj;
};
inline AcAxObjectRef::AcAxObjectRef()
  : m_objId(NULL)
  , m_pObj(NULL)
{
}
inline AcAxObjectRef::AcAxObjectRef(AcDbObjectId objId)
  : m_objId(NULL)
  , m_pObj(NULL)
{
  acquire(objId);
}
inline AcAxObjectRef::AcAxObjectRef(AcDbObject*& pObj)
  : m_objId(NULL)
  , m_pObj(NULL)
{
  acquire(pObj);
}
inline AcAxObjectRef::~AcAxObjectRef()
{
  internalRelease();
}
inline Acad::ErrorStatus AcAxObjectRef::acquire(AcDbObjectId objId)
{
  if (objId.isNull())
  {
    return Acad::eNullObjectId;
  }
  internalRelease();
  m_objId = objId;
  return Acad::eOk;
}
inline Acad::ErrorStatus AcAxObjectRef::acquire(AcDbObject*& pObj)
{
  if (NULL == pObj)
  {
    return Acad::eNullObjectPointer;
  }
  if (!pObj->objectId().isNull())
  {
    return acquire(pObj->objectId());
  }
  internalRelease();
  m_pObj = pObj;
  pObj = NULL;
  return Acad::eOk;
}
inline Acad::ErrorStatus AcAxObjectRef::release(AcDbObjectId& objId, AcDbObject*& pObj)
{
  if (isNull())
  {
    return Acad::eNullObjectPointer;
  }
  pObj = m_pObj;
  objId = m_objId;
  m_pObj = NULL;
  m_objId.setNull();
  return Acad::eOk;
}
inline void AcAxObjectRef::internalRelease()
{
  if (NULL != m_pObj)
  {
    if (m_pObj->objectId().isNull())
    {
      delete m_pObj;
    }
    else 
    {
            //_ASSERTE(NULL == m_pObj && m_pObj->objectId().isNull());
    }
    m_pObj = NULL;
  }
  m_objId.setNull();
}
inline bool AcAxObjectRef::isNull()
{
  return (NULL == m_pObj && m_objId.isNull());
}
inline AcDbObjectId AcAxObjectRef::objectId()
{
  return m_objId;
}
template <typename T_OBJECT>
class AcAxObjectRefPtr : public AcDbObjectPointer<T_OBJECT>
{
public:
  AcAxObjectRefPtr();
  AcAxObjectRefPtr(AcAxObjectRef* const pRef, AcDb::OpenMode mode, bool openErased = false);
  ~AcAxObjectRefPtr();
private:
  AcAxObjectRefPtr(AcAxObjectRefPtr& pObj);
  AcAxObjectRefPtr& operator=(AcAxObjectRefPtr& pObj);
  AcAxObjectRef* const m_pRef;
};
template <typename T_OBJECT>
inline AcAxObjectRefPtr<T_OBJECT>::AcAxObjectRefPtr()
  : AcDbObjectPointer<T_OBJECT>()
  , m_pRef(NULL)
{
}
template <typename T_OBJECT>
inline AcAxObjectRefPtr<T_OBJECT>::AcAxObjectRefPtr(AcAxObjectRef* const pRef, AcDb::OpenMode mode, bool openErased)
  : m_pRef(pRef)
{
    //_ASSERTE(NULL != pRef);
  if (NULL == pRef)
  {
    this->m_status = Acad::eNullObjectPointer;
    return ;
  }
  AcDbObjectId objId = pRef->objectId();
  if (!objId.isNull())
  {
    this->m_status = acdbOpenObject(this->m_ptr, objId, mode, openErased);
  }
  else 
  {
    AcDbObject* pTmp = NULL;
    m_pRef->release(objId, pTmp);
    T_OBJECT* pTyped = T_OBJECT::cast(pTmp);
    if (NULL == pTyped)
    {
      this->m_ptr = NULL;
      m_pRef->acquire(pTmp);
      this->m_status = Acad::eNotThatKindOfClass;
    }
    else 
    {
      acquire(pTyped);
    }
  }
}
template <typename T_OBJECT>
inline AcAxObjectRefPtr<T_OBJECT>::~AcAxObjectRefPtr()
{
  if (NULL != this->m_ptr && this->m_ptr->objectId().isNull())
  {
    T_OBJECT* pTmp;
    release(pTmp);
    m_pRef->acquire(reinterpret_cast<AcDbObject*&>(pTmp));
  }
}
typedef AcAxObjectRefPtr<AcDbObject> AcDbObjectRefPtr;
typedef AcAxObjectRefPtr<AcDbEntity> AcDbEntityRefPtr;
#  pragma  pack (pop)
#endif
