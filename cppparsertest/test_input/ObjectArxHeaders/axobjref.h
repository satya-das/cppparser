//
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
// AXOBJREF.H
//
// Object reference proxy and smart pointer template classes
//

#ifndef __AXOBJREF_H_
#define __AXOBJREF_H_

#include "dbobjptr.h"
#pragma pack (push, 8)

#pragma warning (disable : 4786)

//
// ---- AcAxObjectRef Class ----
//
// This class provides an abstract packaging of a reference to an AcDbObject,
// that is represented either as an AcDbObjectId or as an AcDbObject pointer.
// This packaging allows other classes to encapsulate an AcAxObjectRef instance
// instead of separate AcDbObjectId and pointer references, and to pass the
// reference around as a parameter without advance knowledge of the actual
// reference type. 
//
// The following special behaviors apply to this implementation:
//
//      1. The AcAxObjectRef owns any pointers that it may encapsulate. Callers
//      should not cache any object pointers managed by an AcAxObjectRef. The
//      AcAxObjectRef destructor deletes objects it has pointers for if they
//      are not database resident.
//
//      2. The AcAxObjectRef does not manage the lifetime (i.e. does not own)
//      any AcDbObjectIds that it may encapsulate. The lifetime of the objects
//      referenced by AcDbObjectIds is not bound by the lifetime of the
//      AcAxObjectRef.
//
//      3. The AcAxObjectRef only encapsulates an AcDbObject pointer or an
//      AcDbObjectId at any given time.  Placing an AcDbObjectId into an
//      AcAxObjectRef which already encapsulates an AcDbObject pointer causes
//      the object to be deleted if it is not database resident.
//
//      3. Copy and assignment operations are prohibited, they would violate
//      the "ownership" aspect of the class.  Derived classes should override
//      copy and constructor members and declare them private.
//
//      4. Callers use the acquire() and release() methods to manage the
//      objects encapsulated by an AcAxObjectRef. There are no accessor methods
//      the encapsulated references. Callers must use the release() method to
//      obtain references to the encapsulated pointer or objectId, which
//      "detaches" the AcAxObjectRef from the references.

class AcAxObjectRef
{
public:
    AcAxObjectRef();
    AcAxObjectRef(AcDbObjectId objId);
    AcAxObjectRef(AcDbObject *&  pObj); 
    ~AcAxObjectRef();
    
    Acad::ErrorStatus acquire(AcDbObjectId objId);
    Acad::ErrorStatus acquire(AcDbObject *& pObj);

    Acad::ErrorStatus release(AcDbObjectId& objId, AcDbObject *& pObj);
    
    bool isNull();
    AcDbObjectId objectId();

private:
    // Disallow copy constructor and assignment
    AcAxObjectRef(AcAxObjectRef & ref);
    AcAxObjectRef& operator=(AcAxObjectRef & ref);

    void internalRelease();
    // Object references
    AcDbObjectId m_objId;
    AcDbObject *   m_pObj;
};

inline
AcAxObjectRef::AcAxObjectRef()
    : m_objId(NULL),
      m_pObj(NULL)
{
}

inline
AcAxObjectRef::AcAxObjectRef(AcDbObjectId objId)
    : m_objId(NULL),
      m_pObj(NULL)
{   
    acquire(objId);
}

inline
AcAxObjectRef::AcAxObjectRef(AcDbObject *& pObj)
    : m_objId(NULL),
      m_pObj(NULL)
{
    acquire(pObj);
}

inline
AcAxObjectRef::~AcAxObjectRef()
{
    internalRelease();
}
    
inline Acad::ErrorStatus
AcAxObjectRef::acquire(AcDbObjectId objId)
{
    if (objId.isNull())
        return Acad::eNullObjectId;// VC8:Removed extra qualifier
    
    internalRelease();
    
    m_objId = objId;
    return Acad::eOk;// VC8:Removed extra qualifier
}

inline Acad::ErrorStatus
AcAxObjectRef::acquire(AcDbObject *& pObj)
{
    if (NULL == pObj)
        return Acad::eNullObjectPointer;

    if (!pObj->objectId().isNull())
        return acquire(pObj->objectId());
    
    internalRelease();

    m_pObj = pObj;
    pObj = NULL;
    
    return Acad::eOk;
}
    
inline Acad::ErrorStatus
AcAxObjectRef::release(AcDbObjectId& objId, AcDbObject *& pObj)
{
    if (isNull())
        return Acad::eNullObjectPointer;

    pObj = m_pObj;
    objId = m_objId;

    m_pObj = NULL;
    m_objId.setNull();
    
    return Acad::eOk;
}

inline void
AcAxObjectRef::internalRelease()
{
    if (NULL != m_pObj) 
    {
        if (m_pObj->objectId().isNull())
            delete m_pObj;
    
        else 
        {
            // Somebody forgot to get back the pointer to close
            // the object
            //_ASSERTE(NULL == m_pObj && m_pObj->objectId().isNull());
        }
        m_pObj = NULL;
    }
    m_objId.setNull();
}

inline bool
AcAxObjectRef::isNull()
{
    return (NULL == m_pObj && m_objId.isNull());
}

inline AcDbObjectId
AcAxObjectRef::objectId()
{
    return m_objId;
}
        
// ---- Class AcAxObjectRefPtr ----
//
// This class provides "smart pointer" behavior for AcAxObjectRef instances,
// similar to the behavior provided by the AcDbObjectPointer template class for
// AcDbObjectIds. Unlike the AcDbObjectPointer class handling of non-database
// resident objects, the lifetime of the referenced object is not bound to the
// lifetime of the AcAxObjectRefPtr, only the open/closed state is managed by
// the AcAxObjectRefPtr class.
// 
// The following special behaviors apply to this implementation:
//
//      1. The object references used by the AcAxObjectRefPtr class are "owned"
//      by the AcAxObjectRefPtr instance for the duration of its lifetime. When
//      constructed the AcAxObjectRefPtr releases the AcAxObjectRef of it's
//      object references.  As it is destroyed the AcAxObjectRefPtr returns the
//      ownership of these references to the AcAxObjectRef.
//
//      2. The objects managed by an AcAxObjectRefPtr are maintained in an
//      "open" state for as long as the objects are managed by the pointer
//      class. Open object references are "closed" when the AcAxObjectRefPtr
//      object is destroyed.
//
//      3. All of the caveats and usage notes mentioned for
//      AcDbObjectPointerBase in dbobjptr.h apply to this class as well.
//

template<class T_OBJECT>
class AcAxObjectRefPtr : public AcDbObjectPointer<T_OBJECT>
{
public:
    AcAxObjectRefPtr();
    AcAxObjectRefPtr(AcAxObjectRef* const pRef,
                     AcDb::OpenMode mode,
                     bool           openErased = false);
    ~AcAxObjectRefPtr();

private:
    // Disallow copy constructor, assignment operator
    AcAxObjectRefPtr(AcAxObjectRefPtr & pObj);
    AcAxObjectRefPtr& operator=(AcAxObjectRefPtr & pObj);

    AcAxObjectRef* const m_pRef;
};

template<class T_OBJECT> inline
AcAxObjectRefPtr<T_OBJECT>::AcAxObjectRefPtr()
    : AcDbObjectPointer<T_OBJECT>(),
      m_pRef(NULL)
{}

template<class T_OBJECT> inline 
AcAxObjectRefPtr<T_OBJECT>::AcAxObjectRefPtr(AcAxObjectRef* const pRef, AcDb::OpenMode mode, bool openErased)
    : m_pRef(pRef)
{
    //_ASSERTE(NULL != pRef);
    if (NULL == pRef)
    {
        this->m_status = Acad::eNullObjectPointer;// VC8:Removed extra qualifier
        return;
    }

    // Acquire the reference as either an objectId or pointer
    AcDbObjectId objId = pRef->objectId();
    
    // If it is a non-null objectId just open it
    if (!objId.isNull()) 
        this->m_status = acdbOpenObject(this->m_ptr, objId, mode, openErased);
    // If it is a null objectId we will need to acquire the 
    // pointer from the AcAxObjectRef
    else 
    {
        AcDbObject* pTmp = NULL;
        m_pRef->release(objId, pTmp);

        // Check for downcast of AcDbObject pointer to T_OBJECT
        // Restore object reference if this cast fails
        T_OBJECT* pTyped= T_OBJECT::cast(pTmp);
        if (NULL == pTyped) {
            this->m_ptr = NULL;
            m_pRef->acquire(pTmp);
            this->m_status = Acad::eNotThatKindOfClass;
        }
        else
            acquire(pTyped);
    }
}
    
template<class T_OBJECT> inline
AcAxObjectRefPtr<T_OBJECT>::~AcAxObjectRefPtr()
{
    // If the objectid is null we need to release
    // our reference and store it on the AcAxObjectRef.
    if (NULL != this->m_ptr && this->m_ptr->objectId().isNull()) {
        T_OBJECT* pTmp;
        release(pTmp);
        m_pRef->acquire(reinterpret_cast<AcDbObject*&>(pTmp));
    }
}

typedef AcAxObjectRefPtr<AcDbObject> AcDbObjectRefPtr;
typedef AcAxObjectRefPtr<AcDbEntity> AcDbEntityRefPtr;

#pragma pack (pop)
#endif
