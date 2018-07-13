//
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
//
//
//  DESCRIPTION
//
//  The template classes defined in this header file provide
//  ways to avoid open failures due to conflicts, as well as
//  automatically ensuring close operations that are symmetric
//  with the open operations that are performed.  Their
//  implementations work together to implement
//  AcDbSmartObjectPointer, which combines the ability to avoid
//  open conflicts with all the semantic capability of
//  AcDbObjectPointer.  The intent is to replace the implementation
//  of AcDbObjectPointer with AcDbSmartObjectPointer logic in
//  a future release.
//
//  Developers who are not already using any of the functions
//  and templates here are Strongly Encouraged to use only
//  AcDbSmartObjectPointer<ACDB_CLASS>
//
//  However, the ReadableAcDbObject and WritableAcDbObject templates
//  have been used internally for some time, so their definition
//  is also provided.
//


#ifndef AD_DBOBJPTR2_H
#define AD_DBOBJPTR2_H

// Include dbobjptr.h to get definition of DbObjPtr_Assert.  Otherwise
// it is completely independent.
#include "dbobjptr.h"

// Worker function used by the template function. For Internal Use Only
ACDBCORE2D_PORT Acad::ErrorStatus 
        accessAcDbObjectForRead(AcDbObject * & pObj,
                                AcDbObjectId id,
                                AcRxClass * (*pfDesc)(),
                                bool &bWasOpened,
                                bool bOpenErased);

// Template function, used by the smart pointer template. For Internal use Only.
template<class ACDB_CLASS> inline Acad::ErrorStatus
        accessAcDbObjectForRead(ACDB_CLASS * & pObj,
                                AcDbObjectId id,
                                bool &bWasOpened,
                                bool bOpenErased = false)
{
    return ::accessAcDbObjectForRead((AcDbObject * &)pObj,
                                     id,
                                     &ACDB_CLASS::desc,
                                     bWasOpened, bOpenErased);
};

// Specialization for the base class AcDbObject. Avoids isKindOf() overhead
template<> inline Acad::ErrorStatus
        accessAcDbObjectForRead<AcDbObject>(AcDbObject * & pObj,
                                AcDbObjectId id,
                                bool &bWasOpened,
                                bool bOpenErased)
{
    return ::accessAcDbObjectForRead(pObj, id, /*pfDesc*/nullptr,
                                     bWasOpened, bOpenErased);
}


template<class ACDB_CLASS> class AcDbSmartObjectPointer;

// ReadableAcDbObject:  For Internal Use Only
//
// This class manages calls to accessAcDbObjectForRead and
// then reverts the open state change, if any, from the destructor,
// unless the caller has explicitly closed it earlier.  
// enableNow can be used to defer read enabled status
//
// CAUTION: The fundamental requirement for using AcDbSmartObjectPointer,
//          ReadableAcDbObject and WritableAcDbObject is that the open
//          state cannot be different at the point when these classes initiate
//          access to the object and terminate the access, usually in the
//          constructors and destructors.   Intervening logic can
//          open the object, as long as it closes it also.  And
//          instances of AcDbSmartObjectPointer and/or ReadableAcDbObject
//          and WritableAcDbObject can be nested arbitrarily, as long as
//          the nested instances release the object before the outer
//          object does.  Failure to adhere to this requirement will
//          result in program error.  If used with a non database resident
//          object the destructor for this class will delete the object being held.
//
template<class ACDB_CLASS>
class ReadableAcDbObject {
public:
    ReadableAcDbObject()
    {
    }

    ReadableAcDbObject(ACDB_CLASS*& pObj, AcDbObjectId id,
                       bool bOpenErased, bool enableNow = true)
    {
        if (enableNow)
            enableRead(pObj, id, bOpenErased);
    }

    // Disallow copy ctor and asst oper
    ReadableAcDbObject (const ReadableAcDbObject &) = delete;
    ReadableAcDbObject & operator = (const ReadableAcDbObject &) = delete;

    void enableRead(ACDB_CLASS*& pObj,
                    AcDbObjectId id,
                    bool bOpenErased)
    {
        revertRead();
        pObj = NULL;
        if (Acad::eNotOpenForRead == mEs) {
            mEs = accessAcDbObjectForRead(pObj,
                                          id,
                                          mbWasOpened,
                                          bOpenErased);
            DbObjPtr_Assert((Acad::eOk == mEs) == (NULL != pObj));
            DbObjPtr_Assert((NULL != pObj) ? pObj->isReadEnabled() : true);
            mpObj = pObj;
        }
    };

    void revertRead()
    {
        if (mpObj) {
            if (mpObj->objectId().isNull()) {
                delete mpObj;
            }
            else if ((Acad::eOk == mEs) && mbWasOpened)
            {
                mEs = mpObj->close();
            }
            mpObj = NULL;
        }
        mEs = Acad::eNotOpenForRead;
    };

    ~ReadableAcDbObject()
    {
        revertRead();
    };

    bool isReadable() const
    {
        return ((NULL != mpObj) && mpObj->isReadEnabled());
    };

    const ACDB_CLASS* object() const
    {
        return Acad::eOk == mEs ? mpObj : NULL; // Warning: this can be NULL
    };

    // Support non-const access of readable object to
    // support AcDbSmartObjectPointer::acquire and
    // DBOBJPTR_EXPOSE_PTR_REF actions.
    ACDB_CLASS*       object()
    {
        return Acad::eOk == mEs ? mpObj : NULL; // Warning: this can be NULL
    };

    Acad::ErrorStatus statusCode() const
    {
        return mEs;
    };
private:
    ACDB_CLASS*       mpObj {nullptr};
    Acad::ErrorStatus mEs {Acad::eNotOpenForRead};
    bool              mbWasOpened {false};

    // Provide a way to support AcDbObjectPointer::acquire-based
    // functionality, and DBOBJPTR_EXPOSE_PTR_REF capability.
    // These calls completely disable ReadableAcDbObject and
    // WritableAcDbObject's benefits.   In one case, we don't
    // even close the old object, hence the "forget".
    // Then we accept the new object as having been opened, but
    // we don't know how.  The contract is that it will be
    // closed once by the pointer, unless it is also forgotten.
    friend class AcDbSmartObjectPointer<ACDB_CLASS>;
    
    ReadableAcDbObject(AcDbObjectId id,
                       bool bOpenErased, bool enableNow = true)
    :  mpObj(NULL),
    mEs(Acad::eNotOpenForRead)
    {
        if (enableNow)
            enableRead(mpObj, id, bOpenErased);
    }
    
    void forgetCurrentAndAcceptNewAsIs(ACDB_CLASS* pNewObj)
    {
        if (mpObj != pNewObj) {
            mpObj = pNewObj;
            mEs = (NULL == mpObj) ? Acad::eNotOpenForRead : Acad::eOk;
            mbWasOpened = (NULL != mpObj);
        }
    };
};


// accessAcDbObjectForWrite:  For Internal Use Only
//
// CAUTION:  if the return status is Acad::eOk, then one *SHOULD* call
//           revertAcDbObjectForWrite with all the returned parameter values
//           to ensure proper reversal of the changed open.
// HINT:     Use AcDbSmartObjectPointer or at least WritableAcDbObject
//           rather than using these functions directly.
//
ACDBCORE2D_PORT Acad::ErrorStatus
accessAcDbObjectForWrite(AcDbObject *pObj,
                         bool &bWasNotifyEnabled,
                         bool &bWasWriteEnabled,
                         int  &readCountClosed,
                         bool openOnLockedLayer);



// revertAcDbObjectFromWrite:  For Internal Use Only
//
// Reverses the actions performed in accessAcDbObjectForWrite
// The like-named parameters should have the values returned by
// accessAcDbObjectForWrite.  accessStatus should have the status
// returned by accessAcDbObjectForWrite.
// HINT:     Use AcDbSmartObjectPointer or at least WritableAcDbObject
//           rather than using these functions directly.
//
ACDBCORE2D_PORT Acad::ErrorStatus
revertAcDbObjectFromWrite(AcDbObject *pObj,
                          Acad::ErrorStatus accessStatus,
                          bool bWasNotifyEnabled,
                          bool bWasWriteEnabled,
                          int  readCountClosed);


// WritableAcDbObject:  For Internal Use Only
//
// This class organizes matching calls to accessAcDbObjectForWrite and
// revertAcDbObjectFromWrite to ease their use.  All the caller
// supplies is a reference to an AcDbObject pointer.  If the pointer is
// non-null after
// the constructor, then it can be used for writing, and the
// object open state is reverted is closed when the instance destructor
// is invoked.  enableNow can be used to defer write enabled status
//
// CAUTION: The fundamental requirement for using AcDbSmartObjectPointer,
//          ReadableAcDbObject and WritableAcDbObject is that the open
//          state cannot be different at the point when these classes initiate
//          access to the object and terminate the access, usually in the
//          constructors and destructors.   Intervening logic can
//          open the object, as long as it closes it also.  And
//          instances of AcDbSmartObjectPointer and/or ReadableAcDbObject
//          and WritableAcDbObject can be nested arbitrarily, as long as
//          the nested instances release the object before the outer
//          object does.  Failure to adhere to this requirement will
//          result in program error.
//
class WritableAcDbObject {
public:
    WritableAcDbObject()
        :  mbOpenOnLockedLayer(false)
    {
    }

    WritableAcDbObject(AcDbObject* pObj, bool enableNow = true, bool openOnLockedLayer = false)
        : mbOpenOnLockedLayer(openOnLockedLayer)
    {
        replaceObject(pObj, enableNow);
    }

    // Disallow copy ctor and asst oper
    WritableAcDbObject(const WritableAcDbObject &) = delete;
    WritableAcDbObject operator = (const WritableAcDbObject &) = delete;

    void replaceObject(AcDbObject* pObj, bool enableNow = true)
    {
        revertWrite();
        mpObj = pObj;
        if (NULL == pObj) {
            mEs = Acad::eNullObjectPointer;
            return;
        }
        mEs = Acad::eNotOpenForWrite;
        if (enableNow)
            enableWrite();
    }

    bool enableWrite() {
        if (isWritable())
            return true;
        if (NULL == mpObj)
            return false;
        mEs = accessAcDbObjectForWrite(mpObj,
                                       mbWasNotifyEnabled,
                                       mbWasWriteEnabled,
                                       mReadCountClosed,
                                       mbOpenOnLockedLayer);
        return isWritable();
    };

    void revertWrite()
    {
        if ((NULL != mpObj) && !mpObj->objectId().isNull())
            mEs = revertAcDbObjectFromWrite(mpObj,
                                            mEs,
                                            mbWasNotifyEnabled,
                                            mbWasWriteEnabled,
                                            mReadCountClosed);
        forget();
    };

    ~WritableAcDbObject()
    {
        revertWrite();
    };

    bool isWritable() const
    {
        return (Acad::eOk == mEs);
    };

    Acad::ErrorStatus statusCode() const
    {
        return mEs;
    };

    void forget()
    {
        mpObj = NULL;
        mEs = Acad::eNullObjectPointer;
    };

    void setOpenOnLockedLayer(bool openOnLockedLayer)
    {
        mbOpenOnLockedLayer = openOnLockedLayer;
    }

private:
    AcDbObject*       mpObj {nullptr};
    Acad::ErrorStatus mEs {Acad::eNullObjectPointer};
    bool              mbWasNotifyEnabled = false;
    bool              mbWasWriteEnabled = false;
    bool              mbOpenOnLockedLayer;  // initialized by constructor
    int               mReadCountClosed {0};
};



#pragma pack (push, 8)

// --------- AcDbSmartObjectPointer<ACDB_CLASS> ---------
//

// AcDbSmartObjectPointer
//
// This class is protocol-compatible with AcDbObjectPointer
// and has the added capability to avoid open conflicts to
// access an object when given an object id, in addition to
// the longstanding capability to always "close" an object
// or at least revert it to the open state it was in prior
// to being assigned to the pointer.
//
// The intent is to replace the implementation
// of AcDbObjectPointer with AcDbSmartObjectPointer logic in
// a future release.
//
// AcDbSmartObjectPointer works by NOT opening an object
// at all if it's open state is already what was requested, or
// even closing an object multiple times before opening in the
// desired manner.  It also treats kForNotify and kForRead
// in the same manner, which is effectively kForRead.
//
// CAUTION: The fundamental requirement for using AcDbSmartObjectPointer,
//          ReadableAcDbObject and WritableAcDbObject is that the open
//          state cannot be different at the point when these classes initiate
//          access to the object and terminate the access, usually in the
//          constructors and destructors.   Intervening logic can
//          open the object, as long as it closes it also.  And
//          instances of AcDbSmartObjectPointer and/or ReadableAcDbObject
//          and WritableAcDbObject can be nested arbitrarily, as long as
//          the nested instances release the object before the outer
//          object does.  Failure to adhere to this requirement will
//          result in program error.
//
// While this doesn't make the class foolproof, it does eliminate
// open conflicts cause of failure to obtain access to objects.
//
// Some of the remaining conditions that can still cause failure to
// open are as follows, indicated by the associated error Status:
//  - eNotThatKindOfClass: when the specified object id points
//                         to an object that is not the specified
//                         class.
//  - ePermanentlyErased:  when the specified object id has no
//                         underlying object, whether due to
//                         undo of creation or erase/delete.
//  - eObjectWasErased:    if the object is erased and the
//                         openErased flag is false.
//  - eOnLockedLayer:      if the entity is on a locked layer, and
//                         the openOnLockedLayer flag last used is
//                         false.  Override with caution, locked
//                         layers symbolize an intent to deter modification.
//                         undo/redo filing and audit fixup are examples
//                         of where you may want to bypass the locked
//                         layer mechanism, also internal changes on private
//                         data.
//  - eNullObjectId:       when the input object id is null.
//  - eWasNotifying:       when the specified object is currently
//                         closing from kForWrite mode, is
//                         sending notification and kForWrite mode
//                         is requested again.  At that point,
//                         undo recording has been done, and
//                         all reactors get to see the same object
//                         state.  The workaround for this status
//                         is to record that the notification happened
//                         then wait until the
//                         AcDbObject::objectClosed(AcDbObjectId)
//                         callback is made, at which point the
//                         object can be opened for write.
//
// Like AcDbObjectPointer, this template can also "acquire"
// non-database-resident (NDBR) objects and
// previously open objects, which it will close just once.
//
// If the DBOBJPTR_EXPOSE_PTR_REF option is enabled, then
// accessing the object pointer member disables the template's
// ability to symmetrically close or revert the object.  Instead
// it is closed once, and the caller is responsible for it
// afterwards.
//


template<class ACDB_CLASS>
class AcDbSmartObjectPointer
{
public:
    AcDbSmartObjectPointer();
    AcDbSmartObjectPointer(AcDbObjectId   objId,
                           AcDb::OpenMode mode = AcDb::kForRead,
                           bool           openErased = false,
                           bool           openOnLockedLayer = false);
    ~AcDbSmartObjectPointer();  // no other methods are virtual, so this isn't either
    // Disallow copy ctor and asst oper
    AcDbSmartObjectPointer(const AcDbSmartObjectPointer &) = delete;
    AcDbSmartObjectPointer & operator = (const AcDbSmartObjectPointer &) = delete;

    const ACDB_CLASS* object() const;
    ACDB_CLASS*       object();

    const ACDB_CLASS* operator->() const;
    ACDB_CLASS*       operator->();
                      operator const ACDB_CLASS*() const;
#if DBOBJPTR_EXPOSE_PTR_REF
                      AcDbSmartObjectPointer(ACDB_CLASS *pObject);
                      operator ACDB_CLASS* &();
    void              operator=(ACDB_CLASS *pObject);
#else
                      operator ACDB_CLASS*();
#endif

    Acad::ErrorStatus openStatus() const;

    Acad::ErrorStatus open(AcDbObjectId   objId,
                           AcDb::OpenMode mode = AcDb::kForRead,
                           bool           openErased = false,
                           bool           openOnLockedLayer = false);

    Acad::ErrorStatus acquire(ACDB_CLASS *& pObjToAcquire);
    Acad::ErrorStatus release(ACDB_CLASS *& pReleasedObj);
    Acad::ErrorStatus close();

    Acad::ErrorStatus create();
protected:
    ReadableAcDbObject<ACDB_CLASS> mReadable;
    WritableAcDbObject             mWritable;

private:
    Acad::ErrorStatus closeInternal();
    
    ACDB_CLASS* mpObj {nullptr};
};

// --------- Inline definitions ---------

template<class ACDB_CLASS> inline
AcDbSmartObjectPointer<ACDB_CLASS>::AcDbSmartObjectPointer()
    : mReadable(),
      mWritable()
{
    // mReadable and mWritable constructors do all the work.
}

template<class ACDB_CLASS> inline
AcDbSmartObjectPointer<ACDB_CLASS>::AcDbSmartObjectPointer(
    AcDbObjectId   objId,
    AcDb::OpenMode mode,
    bool           openErased,
    bool           openOnLockedLayer)
    : mReadable(objId, openErased),
      mWritable(mReadable.object(), AcDb::kForWrite == mode, openOnLockedLayer)
{
    // Explanation of the preceding constructor calls:
    // mReadable obtains the object, and as of yet, has no
    // outside pointer to set, so we feed its own member to its constructor.
    // then, mWritable takes an object that is open in some way.
}

template<class ACDB_CLASS> inline
AcDbSmartObjectPointer<ACDB_CLASS>::~AcDbSmartObjectPointer()
{
    // mReadable and mWritable destructors do all the work.
    mpObj = NULL;
}

template<class ACDB_CLASS> inline Acad::ErrorStatus 
AcDbSmartObjectPointer<ACDB_CLASS>::open(
    AcDbObjectId   objId,
    AcDb::OpenMode mode,
    bool           openErased,
    bool           openOnLockedLayer)
{
    if (mReadable.isReadable()) {
        Acad::ErrorStatus closeStatus = closeInternal();
        if (closeStatus != Acad::eOk)
            return closeStatus;
    }
    mReadable.enableRead(mReadable.mpObj, objId, openErased);
    if (mReadable.isReadable()) {
        mWritable.setOpenOnLockedLayer(openOnLockedLayer);
        mWritable.replaceObject(mReadable.object(), (AcDb::kForWrite == mode));
    }
    return openStatus();
}

template<class ACDB_CLASS> inline const ACDB_CLASS *
AcDbSmartObjectPointer<ACDB_CLASS>::object() const
{
    DbObjPtr_Assert(mReadable.object() == NULL || mReadable.isReadable());
    return mReadable.object();
}

// This function does not modify the object, but the caller is
// allowed to.
template<class ACDB_CLASS> inline ACDB_CLASS *
AcDbSmartObjectPointer<ACDB_CLASS>::object()
{
    // It would be more theoretically pure to return the mWritable,
    // pointer, but after acquire, or DBOBJPTR_EXPOSE_PTR_REF,
    // the mWritable object is shut down, so instead we just
    // keep using mReadable.object(), which is not a const member.
    DbObjPtr_Assert(mReadable.object() == NULL || mReadable.isReadable());
    return mReadable.object();
}

template<class ACDB_CLASS> inline const ACDB_CLASS *
AcDbSmartObjectPointer<ACDB_CLASS>::operator->() const
{
    return object();
}

template<class ACDB_CLASS> inline ACDB_CLASS *
AcDbSmartObjectPointer<ACDB_CLASS>::operator->()
{
    return object();
}

template<class ACDB_CLASS> inline 
AcDbSmartObjectPointer<ACDB_CLASS>::operator const ACDB_CLASS*() const
{
    return object();
}

#if DBOBJPTR_EXPOSE_PTR_REF
template<class ACDB_CLASS> inline 
AcDbSmartObjectPointer<ACDB_CLASS>::operator ACDB_CLASS* &()
{
    // Allows direct modification of the pointer member
    // so if this is called, we disavow any knowledge of
    // how to close the object, but whatever is put in its place
    // will be closed once if it is non-null and database-resident.
    mWritable.forget();
    mReadable.forgetCurrentAndAcceptNewAsIs(mReadable.object());
    return mReadable.mpObj;
}
#else
template<class ACDB_CLASS> inline 
AcDbSmartObjectPointer<ACDB_CLASS>::operator ACDB_CLASS*()
{
    return object();
}
#endif

template<class ACDB_CLASS> inline Acad::ErrorStatus
AcDbSmartObjectPointer<ACDB_CLASS>::openStatus() const
{
    // In English:  If object was requested to open for write, return the write
    //              status, else return the read status.
    return (mWritable.isWritable() ||
            ((mWritable.statusCode() != Acad::eNullObjectPointer) &&
             (mWritable.statusCode() != Acad::eNotOpenForWrite)))
                                  ? mWritable.statusCode()
                                  : mReadable.statusCode();
}

template<class ACDB_CLASS> inline Acad::ErrorStatus
AcDbSmartObjectPointer<ACDB_CLASS>::acquire(ACDB_CLASS *& pObjToAcquire)
{
    // Semantic Change Alert: unlike AcDbObjectPointer, this class
    // accepts null object pointers.  The required closes will be
    // performed on the prior object and now this will point to a
    // null object.
    closeInternal();
    mReadable.forgetCurrentAndAcceptNewAsIs(pObjToAcquire);
    pObjToAcquire = NULL;
    return Acad::eOk;
}

template<class ACDB_CLASS> inline Acad::ErrorStatus
AcDbSmartObjectPointer<ACDB_CLASS>::release(ACDB_CLASS *& pReleasedObj)
{
    pReleasedObj = mReadable.object();
    mWritable.forget();
    mReadable.forgetCurrentAndAcceptNewAsIs(NULL);
    return Acad::eOk;
}

template<class ACDB_CLASS> inline Acad::ErrorStatus
AcDbSmartObjectPointer<ACDB_CLASS>::close()
{
    closeInternal();
    return Acad::eOk;
}

template<class ACDB_CLASS> inline Acad::ErrorStatus
AcDbSmartObjectPointer<ACDB_CLASS>::create()
{
    ACDB_CLASS * pObject = new ACDB_CLASS;
    if (pObject == NULL)
        return Acad::eNullObjectPointer;
    closeInternal();
    mReadable.forgetCurrentAndAcceptNewAsIs(pObject);
    return Acad::eOk;
}

template<class ACDB_CLASS> inline Acad::ErrorStatus
AcDbSmartObjectPointer<ACDB_CLASS>::closeInternal()
{
    mWritable.revertWrite();
    mReadable.revertRead();

    return Acad::eOk;
}

#if DBOBJPTR_EXPOSE_PTR_REF

template<class ACDB_CLASS> inline
AcDbSmartObjectPointer<ACDB_CLASS>::AcDbSmartObjectPointer(ACDB_CLASS *pObject)
{
    acquire(pObject);
}

template<class ACDB_CLASS> inline void
AcDbSmartObjectPointer<ACDB_CLASS>::operator=(ACDB_CLASS *pObject)
{
    acquire(pObject);
}

#endif  // DBOBJPTR_EXPOSE_PTR_REF

#pragma pack (pop)

#endif // AD_DBOBJPTR2_H
