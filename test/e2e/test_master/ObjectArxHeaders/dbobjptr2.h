//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// dbobjptr2.h
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBOBJPTR2_H
#  define AD_DBOBJPTR2_H
#  include "dbobjptr.h"
ACDBCORE2D_PORT Acad::ErrorStatus accessAcDbObjectForRead(AcDbObject*& pObj, AcDbObjectId id, AcRxClass* (*pfDesc) (), bool& bWasOpened, bool bOpenErased);
template <typename ACDB_CLASS>
inline Acad::ErrorStatus accessAcDbObjectForRead(ACDB_CLASS*& pObj, AcDbObjectId id, bool& bWasOpened, bool bOpenErased = false)
{
  return ::accessAcDbObjectForRead((AcDbObject*&) pObj, id, &ACDB_CLASS::desc, bWasOpened, bOpenErased);
}
template <>
inline Acad::ErrorStatus accessAcDbObjectForRead<AcDbObject>(AcDbObject*& pObj, AcDbObjectId id, bool& bWasOpened, bool bOpenErased)
{
  return ::accessAcDbObjectForRead(pObj, id, nullptr, bWasOpened, bOpenErased);
}
template <typename ACDB_CLASS>
class AcDbSmartObjectPointer;
template <typename ACDB_CLASS>
class ReadableAcDbObject
{
public:
  ReadableAcDbObject()
  {
  }
  ReadableAcDbObject(ACDB_CLASS*& pObj, AcDbObjectId id, bool bOpenErased, bool enableNow = true)
  {
    if (enableNow)
    {
      enableRead(pObj, id, bOpenErased);
    }
  }
  ReadableAcDbObject(const ReadableAcDbObject&) = delete;
  ReadableAcDbObject& operator =(const ReadableAcDbObject&);
  void enableRead(ACDB_CLASS*& pObj, AcDbObjectId id, bool bOpenErased)
  {
    revertRead();
    pObj = NULL;
    if (Acad::eNotOpenForRead == mEs)
    {
      mEs = accessAcDbObjectForRead(pObj, id, mbWasOpened, bOpenErased);
      DbObjPtr_Assert((Acad::eOk == mEs) == (NULL != pObj));
      DbObjPtr_Assert((NULL != pObj) ? pObj->isReadEnabled() : true);
      mpObj = pObj;
    }
  }
  void revertRead()
  {
    if (mpObj)
    {
      if (mpObj->objectId().isNull())
      {
        delete mpObj;
      }
      else 
      {
        if ((Acad::eOk == mEs) && mbWasOpened)
        {
          mEs = mpObj->close();
        }
      }
      mpObj = NULL;
    }
    mEs = Acad::eNotOpenForRead;
  }
  ~ReadableAcDbObject()
  {
    revertRead();
  }
  bool isReadable() const
  {
    return ((NULL != mpObj) && mpObj->isReadEnabled());
  }
  const ACDB_CLASS* object() const
  {
    return Acad::eOk == mEs ? mpObj : NULL;
  }
  ACDB_CLASS* object()
  {
    return Acad::eOk == mEs ? mpObj : NULL;
  }
  Acad::ErrorStatus statusCode() const
  {
    return mEs;
  }
private:
  ACDB_CLASS* mpObj{nullptr};
  Acad::ErrorStatus mEs{Acad::eNotOpenForRead};
  bool mbWasOpened{false};
  friend class AcDbSmartObjectPointer<ACDB_CLASS>;
  ReadableAcDbObject(AcDbObjectId id, bool bOpenErased, bool enableNow = true)
    : mpObj(NULL)
    , mEs(Acad::eNotOpenForRead)
  {
    if (enableNow)
    {
      enableRead(mpObj, id, bOpenErased);
    }
  }
  void forgetCurrentAndAcceptNewAsIs(ACDB_CLASS* pNewObj)
  {
    if (mpObj != pNewObj)
    {
      mpObj = pNewObj;
      mEs = (NULL == mpObj) ? Acad::eNotOpenForRead : Acad::eOk;
      mbWasOpened = (NULL != mpObj);
    }
  }
};
ACDBCORE2D_PORT Acad::ErrorStatus accessAcDbObjectForWrite(AcDbObject* pObj, bool& bWasNotifyEnabled, bool& bWasWriteEnabled, int& readCountClosed, bool openOnLockedLayer);
ACDBCORE2D_PORT Acad::ErrorStatus revertAcDbObjectFromWrite(AcDbObject* pObj, Acad::ErrorStatus accessStatus, bool bWasNotifyEnabled, bool bWasWriteEnabled, int readCountClosed);
class WritableAcDbObject
{
public:
  WritableAcDbObject()
    : mbOpenOnLockedLayer(false)
  {
  }
  WritableAcDbObject(AcDbObject* pObj, bool enableNow = true, bool openOnLockedLayer = false)
    : mbOpenOnLockedLayer(openOnLockedLayer)
  {
    replaceObject(pObj, enableNow);
  }
  WritableAcDbObject(const WritableAcDbObject&) = delete;
  WritableAcDbObject operator =(const WritableAcDbObject&);
  void replaceObject(AcDbObject* pObj, bool enableNow = true)
  {
    revertWrite();
    mpObj = pObj;
    if (NULL == pObj)
    {
      mEs = Acad::eNullObjectPointer;
      return ;
    }
    mEs = Acad::eNotOpenForWrite;
    if (enableNow)
    {
      enableWrite();
    }
  }
  bool enableWrite()
  {
    if (isWritable())
    {
      return true;
    }
    if (NULL == mpObj)
    {
      return false;
    }
    mEs = accessAcDbObjectForWrite(mpObj, mbWasNotifyEnabled, mbWasWriteEnabled, mReadCountClosed, mbOpenOnLockedLayer);
    return isWritable();
  }
  void revertWrite()
  {
    if ((NULL != mpObj) && !mpObj->objectId().isNull())
    {
      mEs = revertAcDbObjectFromWrite(mpObj, mEs, mbWasNotifyEnabled, mbWasWriteEnabled, mReadCountClosed);
    }
    forget();
  }
  ~WritableAcDbObject()
  {
    revertWrite();
  }
  bool isWritable() const
  {
    return (Acad::eOk == mEs);
  }
  Acad::ErrorStatus statusCode() const
  {
    return mEs;
  }
  void forget()
  {
    mpObj = NULL;
    mEs = Acad::eNullObjectPointer;
  }
  void setOpenOnLockedLayer(bool openOnLockedLayer)
  {
    mbOpenOnLockedLayer = openOnLockedLayer;
  }
private:
  AcDbObject* mpObj{nullptr};
  Acad::ErrorStatus mEs{Acad::eNullObjectPointer};
  bool mbWasNotifyEnabled = false;
  bool mbWasWriteEnabled = false;
  bool mbOpenOnLockedLayer;
  int mReadCountClosed{0};
};
#  pragma  pack (push, 8)
template <typename ACDB_CLASS>
class AcDbSmartObjectPointer
{
public:
  AcDbSmartObjectPointer();
  AcDbSmartObjectPointer(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false, bool openOnLockedLayer = false);
  ~AcDbSmartObjectPointer();
  AcDbSmartObjectPointer(const AcDbSmartObjectPointer&) = delete;
  AcDbSmartObjectPointer& operator =(const AcDbSmartObjectPointer&);
  const ACDB_CLASS* object() const;
  ACDB_CLASS* object();
  const ACDB_CLASS* operator->() const;
  ACDB_CLASS* operator->();
  operator const ACDB_CLASS*() const;
#  if  DBOBJPTR_EXPOSE_PTR_REF
  AcDbSmartObjectPointer(ACDB_CLASS* pObject);
  operator ACDB_CLASS*&();
  void operator=(ACDB_CLASS* pObject);
#  else 
  operator ACDB_CLASS*();
#  endif
  Acad::ErrorStatus openStatus() const;
  Acad::ErrorStatus open(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false, bool openOnLockedLayer = false);
  Acad::ErrorStatus acquire(ACDB_CLASS*& pObjToAcquire);
  Acad::ErrorStatus release(ACDB_CLASS*& pReleasedObj);
  Acad::ErrorStatus close();
  Acad::ErrorStatus create();
protected:
  ReadableAcDbObject<ACDB_CLASS> mReadable;
  WritableAcDbObject mWritable;
private:
  Acad::ErrorStatus closeInternal();
  ACDB_CLASS* mpObj{nullptr};
};
template <typename ACDB_CLASS>
inline AcDbSmartObjectPointer<ACDB_CLASS>::AcDbSmartObjectPointer()
  : mReadable()
  , mWritable()
{
}
template <typename ACDB_CLASS>
inline AcDbSmartObjectPointer<ACDB_CLASS>::AcDbSmartObjectPointer(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased, bool openOnLockedLayer)
  : mReadable(objId, openErased)
  , mWritable(mReadable.object(), AcDb::kForWrite == mode, openOnLockedLayer)
{
}
template <typename ACDB_CLASS>
inline AcDbSmartObjectPointer<ACDB_CLASS>::~AcDbSmartObjectPointer()
{
  mpObj = NULL;
}
template <typename ACDB_CLASS>
inline Acad::ErrorStatus AcDbSmartObjectPointer<ACDB_CLASS>::open(AcDbObjectId objId, AcDb::OpenMode mode, bool openErased, bool openOnLockedLayer)
{
  if (mReadable.isReadable())
  {
    Acad::ErrorStatus closeStatus = closeInternal();
    if (closeStatus != Acad::eOk)
    {
      return closeStatus;
    }
  }
  mReadable.enableRead(mReadable.mpObj, objId, openErased);
  if (mReadable.isReadable())
  {
    mWritable.setOpenOnLockedLayer(openOnLockedLayer);
    mWritable.replaceObject(mReadable.object(), (AcDb::kForWrite == mode));
  }
  return openStatus();
}
template <typename ACDB_CLASS>
inline const ACDB_CLASS* AcDbSmartObjectPointer<ACDB_CLASS>::object() const
{
  DbObjPtr_Assert(mReadable.object() == NULL || mReadable.isReadable());
  return mReadable.object();
}
template <typename ACDB_CLASS>
inline ACDB_CLASS* AcDbSmartObjectPointer<ACDB_CLASS>::object()
{
  DbObjPtr_Assert(mReadable.object() == NULL || mReadable.isReadable());
  return mReadable.object();
}
template <typename ACDB_CLASS>
inline const ACDB_CLASS* AcDbSmartObjectPointer<ACDB_CLASS>::operator->() const
{
  return object();
}
template <typename ACDB_CLASS>
inline ACDB_CLASS* AcDbSmartObjectPointer<ACDB_CLASS>::operator->()
{
  return object();
}
template <typename ACDB_CLASS>
operator const ACDB_CLASS*() const
{
  return object();
}
#  if  DBOBJPTR_EXPOSE_PTR_REF
template <typename ACDB_CLASS>
operator ACDB_CLASS*&()
{
  mWritable.forget();
  mReadable.forgetCurrentAndAcceptNewAsIs(mReadable.object());
  return mReadable.mpObj;
}
#  else 
template <typename ACDB_CLASS>
operator ACDB_CLASS*()
{
  return object();
}
#  endif
template <typename ACDB_CLASS>
inline Acad::ErrorStatus AcDbSmartObjectPointer<ACDB_CLASS>::openStatus() const
{
  return (mWritable.isWritable() || ((mWritable.statusCode() != Acad::eNullObjectPointer) && (mWritable.statusCode() != Acad::eNotOpenForWrite))) ? mWritable.statusCode() : mReadable.statusCode();
}
template <typename ACDB_CLASS>
inline Acad::ErrorStatus AcDbSmartObjectPointer<ACDB_CLASS>::acquire(ACDB_CLASS*& pObjToAcquire)
{
  closeInternal();
  mReadable.forgetCurrentAndAcceptNewAsIs(pObjToAcquire);
  pObjToAcquire = NULL;
  return Acad::eOk;
}
template <typename ACDB_CLASS>
inline Acad::ErrorStatus AcDbSmartObjectPointer<ACDB_CLASS>::release(ACDB_CLASS*& pReleasedObj)
{
  pReleasedObj = mReadable.object();
  mWritable.forget();
  mReadable.forgetCurrentAndAcceptNewAsIs(NULL);
  return Acad::eOk;
}
template <typename ACDB_CLASS>
inline Acad::ErrorStatus AcDbSmartObjectPointer<ACDB_CLASS>::close()
{
  closeInternal();
  return Acad::eOk;
}
template <typename ACDB_CLASS>
inline Acad::ErrorStatus AcDbSmartObjectPointer<ACDB_CLASS>::create()
{
  ACDB_CLASS* pObject = new ACDB_CLASS;
  if (pObject == NULL)
  {
    return Acad::eNullObjectPointer;
  }
  closeInternal();
  mReadable.forgetCurrentAndAcceptNewAsIs(pObject);
  return Acad::eOk;
}
template <typename ACDB_CLASS>
inline Acad::ErrorStatus AcDbSmartObjectPointer<ACDB_CLASS>::closeInternal()
{
  mWritable.revertWrite();
  mReadable.revertRead();
  return Acad::eOk;
}
#  if  DBOBJPTR_EXPOSE_PTR_REF
template <typename ACDB_CLASS>
inline AcDbSmartObjectPointer<ACDB_CLASS>::AcDbSmartObjectPointer(ACDB_CLASS* pObject)
{
  acquire(pObject);
}
template <typename ACDB_CLASS>
inline void AcDbSmartObjectPointer<ACDB_CLASS>::operator=(ACDB_CLASS* pObject)
{
  acquire(pObject);
}
#  endif
#  pragma  pack (pop)
#endif
