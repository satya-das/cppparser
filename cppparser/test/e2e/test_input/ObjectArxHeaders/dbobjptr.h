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
//
//  DESCRIPTION
//
//  The template classes defined in this header file provide
//  simplified "management" (i.e., opening, closing, creating,
//  deleting) of AcDbObject's upon construction and destruction.
//  The constructor provides the necessary arguments to open the
//  object and the destructor closes the object.  During the
//  lifetime of the object, clients use operator->() to
//  manipulate the opened object.  These classes also simplify
//  creating and deletion of objects.
//  
//  One base class, AcDbObjectPointerBase provides the basic
//  services of opening and closing objects.  Derived classes
//  provide the real interface to open objects of various types
//  derived from AcDbObject.  They usually provide additional
//  constructors that know about the particular ways of opening
//  an object.  The following template classes are defined in
//  this header file.
//
//  AcDbObjectPointerBase<T_OBJECT>
//
//       This class provides the basic services and defines the
//       basic contracts for using the smart pointers derived
//       from it.  You normally don't use this class directly,
//       but may use it to define a derived class to add
//       constructors that know how to open an object derived
//       from AcDbObject in alternate forms.
//
//  AcDbObjectPointer<T_OBJECT>
//
//       This class allows you to access any AcDbObject-based
//       object given its object ID.  The following pre-defined
//       typedefs are available.
//
//       AcDbDictionaryPointer
//       AcDbEntityPointer
//
//  AcDbSymbolTablePointer<T_OBJECT>
//
//       This class allows you to access the symbol tables
//       associated with every AcDbDatabase.  You can specify
//       an object ID or a particular database.  The following
//       pre-defined typedefs are available for individual
//       symbol-table types.
//
//       AcDbBlockTablePointer
//       AcDbDimStyleTablePointer
//       AcDbLayerTablePointer
//       AcDbLinetypeTablePointer
//       AcDbRegAppTablePointer
//       AcDbTextStyleTablePointer
//       AcDbUCSTablePointer
//       AcDbViewTablePointer
//       AcDbViewportTablePointer
//
//       Note that to open a "plain" symbol table, you may use
//       AcDbObjectPointer<AcDbSymbolTable>.
//
//  AcDbSymbolTableRecordPointer<T_OBJECT>
//
//       This class allow you to access symbol-table records by
//       object ID or by name.  The following pre-defined
//       typedefs are available for individual symbol-table
//       record types.
//
//       AcDbBlockTableRecordPointer
//       AcDbDimStyleTableRecordPointer
//       AcDbLayerTableRecordPointer
//       AcDbLinetypeTableRecordPointer
//       AcDbRegAppTableRecordPointer
//       AcDbTextStyleTableRecordPointer
//       AcDbUCSTableRecordPointer
//       AcDbViewTableRecordPointer
//       AcDbViewportTableRecordPointer
//
//       Note that to open a "plain" symbol record, you may use
//       AcDbObjectPointer<AcDbSymbolTableRecord>.
//
// These classes are designed to be type-safe replacements for
// explicitly using acdbOpenObject(), acdbOpenAcDbObject(), and
// acdbOpenAcDbEntity().  Using these classes incur opening and
// close objects, which, under certain circumstances, may be
// better managed using transactions.

#ifndef AD_DBOBJPTR_H
#define AD_DBOBJPTR_H

#include <assert.h>
#include "dbsymtb.h"

#ifdef ASSERT
#define DbObjPtr_Assert ASSERT
#elif defined assert
#define DbObjPtr_Assert assert
#elif defined _ASSERTE
#define DbObjPtr_Assert _ASSERTE
#else
#define DbObjPtr_Assert(T)
#endif

#pragma pack (push, 8)

// --------- AcDbObjectPointerBase<T_OBJECT> ---------
//
// This class provides the basic services for opening and
// closing objects given its object ID.  It is meant to be a
// base class from which derived classes may specialize on how
// objects may be opened.  Template argument T_OBJECT should
// be AcDbObject or a class derived from AcDbObject that you
// can open via acdbOpenObject().
//
// Contracts:
//
// All derived classes must abide by and enforce the following contracts.
//
// 1. Copying and assignment are prohibited.  Derived classes
//    must also prohibit copying and assigment by declaring those
//    functions private.  These classes contain a pointer to
//    the real object, so the default constructors provided by
//    the compiler must not be used.  Copying and assigment do
//    not have obvious semantics of whether you own the object
//    or just the pointer.  You can pass AcDbObjectId's and
//    use these classes to simplify opening the objects by
//    their ID.
//
// 2. Clients must not close the objects themselves by using
//    the close() member function.  The destructor will close
//    the object.  These pointer classes are meant to keep the
//    object open for the lifetime of the pointer object.
//    Note that an upgradeOpen() may fail, but is compatible
//    with the semantics of the pointer classes.  A failure to
//    upgrade will leave the object opened in it's original
//    mode.
//
//    A consequence of this contract means that passing the
//    pointers returned by operator->() or object() to other
//    functions may lead to unexpected problems if the other
//    functions close the object through the pointer.
//
// 3. Derived classes should provide the following constructors.
//
//    A. A constructor that opens the object by its ID.  This
//       consistency promotes the use of object IDs and
//       ensures the "basic" service of opening objects by ID
//       when using these object-pointer classes.
//
//    B. A default constructor, which is mainly needed when
//       clients wish to use the acquire() member function.
//
// 4. All clients will call the openStatus() member function
//    to determine if the object was successfully opened before
//    using operator->().
//
//    The default constructor provided by AcDbObjectPointerBase<T_OBJECT>
//    sets the open status to Acad::eNullObjectPointer.
//

// Enable DBOBJPTR_EXPOSE_PTR_REF in order to allow direct access to the
// pointer member.  This lets you pass the smart pointer to functions
// like getAt(), deepClone() and acdbOpenAcDbObject(), which need a
// reference to an AcDbObject pointer, so they can modify it.
//
// Note that this allows the pointer member to be updated externally, so
// that previously open objects may be left open, creating a "leak".
//
// Also, the openStatus() method may not reflect the correct status
// after an external operation modified the pointer member.
//
// This also enables constructors and assignment operators which allow
// you to directly assign conventional pointers to the smart pointer.
//
// Use at your own risk!
//
// #define DBOBJPTR_EXPOSE_PTR_REF 1

template<class T_OBJECT>
class AcDbObjectPointerBase
{
public:
    AcDbObjectPointerBase();
    ~AcDbObjectPointerBase();   // no other methods are virtual, so neither is this

    const T_OBJECT *  object() const;
    T_OBJECT *        object();

    const T_OBJECT *  operator->() const;
    T_OBJECT *        operator->();
                      operator const T_OBJECT*() const;
#if DBOBJPTR_EXPOSE_PTR_REF
                      operator T_OBJECT* &();
#else
                      operator T_OBJECT*();
#endif

    Acad::ErrorStatus openStatus() const;

    Acad::ErrorStatus open(AcDbObjectId   objId,
                           AcDb::OpenMode mode = AcDb::kForRead,
                           bool           openErased = false);

    Acad::ErrorStatus acquire(T_OBJECT *& pObjToAcquire);
    Acad::ErrorStatus release(T_OBJECT *& pReleasedObj);
    Acad::ErrorStatus close();

    Acad::ErrorStatus create();

protected:
    AcDbObjectPointerBase(AcDbObjectId   objId,
                          AcDb::OpenMode mode,
                          bool           openErased);

#if DBOBJPTR_EXPOSE_PTR_REF
    AcDbObjectPointerBase(T_OBJECT * pObject);
    void operator=(T_OBJECT *pObject);
#endif

    T_OBJECT *        m_ptr;
    Acad::ErrorStatus m_status;

private:
    // Copy and assignment prohibited.
    AcDbObjectPointerBase(const AcDbObjectPointerBase &) = delete;
    AcDbObjectPointerBase& operator=(const AcDbObjectPointerBase &) = delete;

    Acad::ErrorStatus closeInternal();
};

// --------- AcDbObjectPointer<T_OBJECT> ---------

// This class allows you to open any AcDbObject given its object ID.
// The single form of construction is:
//
// (AcDbObjectId objId, AcDb::OpenMode mode, bool openErased)
//
// These arguments have the same meaning as acdbOpenObject().
//
template<class T_OBJECT>
class AcDbObjectPointer : public AcDbObjectPointerBase<T_OBJECT>
{
public:
    AcDbObjectPointer();
    AcDbObjectPointer(AcDbObjectId   objId,
                      AcDb::OpenMode mode = AcDb::kForRead,
                      bool           openErased = false);
    
#if DBOBJPTR_EXPOSE_PTR_REF
    AcDbObjectPointer(T_OBJECT * pObject);
    void operator=(T_OBJECT *pObject);
#endif

    Acad::ErrorStatus open(AcDbObjectId objId,
                      AcDb::OpenMode    mode = AcDb::kForRead,
                      bool              openErased = false);

private:
    // Copy and assignment prohibited.
    AcDbObjectPointer(const AcDbObjectPointer &) = delete;
    AcDbObjectPointer& operator=(const AcDbObjectPointer &) = delete;
};

typedef AcDbObjectPointer<AcDbDictionary> AcDbDictionaryPointer;
typedef AcDbObjectPointer<AcDbEntity>     AcDbEntityPointer;

// --------- AcDbSymbolTablePointer<T_OBJECT> ---------

// This class allows you to open any AcDbSymbolTable or
// AcDbSymbolTable-derived object given its object ID or
// a pointer to the database containing the symbol table.
// The different forms of construction are:
//
// (AcDbObjectId objId, AcDb::OpenMode mode)
// (AcDbDatabase * pDb, AcDb::OpenMode mode)
//
// The object ID and open modes have the same meaning as those of
// AcDbObjectPointer<T_OBJECT>.  If the database pointer is NULL, the
// open status after construction is eNullObjectPointer.
//
template<class T_OBJECT>
class AcDbSymbolTablePointer : public AcDbObjectPointerBase<T_OBJECT>
{
public:
    AcDbSymbolTablePointer();
    AcDbSymbolTablePointer(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead);
    AcDbSymbolTablePointer(AcDbDatabase * pDb, AcDb::OpenMode mode = AcDb::kForRead);
#if DBOBJPTR_EXPOSE_PTR_REF
    AcDbSymbolTablePointer(T_OBJECT * pObject);
    void operator=(T_OBJECT *pObject);
#endif

    Acad::ErrorStatus open(AcDbObjectId objId, AcDb::OpenMode mode = AcDb::kForRead);
    Acad::ErrorStatus open(AcDbDatabase* pDb, AcDb::OpenMode mode = AcDb::kForRead);

private:
    // Copy and assignment prohibited.
    AcDbSymbolTablePointer(const AcDbSymbolTablePointer &) = delete;
    AcDbSymbolTablePointer& operator=(const AcDbSymbolTablePointer &) = delete;

    // Restrict T_OBJECT to AcDbSymbolTable and derived classes.
    typedef typename T_OBJECT::RecordType T2;
};

typedef AcDbSymbolTablePointer<AcDbBlockTable>     AcDbBlockTablePointer;
typedef AcDbSymbolTablePointer<AcDbDimStyleTable>  AcDbDimStyleTablePointer;
typedef AcDbSymbolTablePointer<AcDbLayerTable>     AcDbLayerTablePointer;
typedef AcDbSymbolTablePointer<AcDbLinetypeTable>  AcDbLinetypeTablePointer;
typedef AcDbSymbolTablePointer<AcDbRegAppTable>    AcDbRegAppTablePointer;
typedef AcDbSymbolTablePointer<AcDbTextStyleTable> AcDbTextStyleTablePointer;
typedef AcDbSymbolTablePointer<AcDbUCSTable>       AcDbUCSTablePointer;
typedef AcDbSymbolTablePointer<AcDbViewTable>      AcDbViewTablePointer;
typedef AcDbSymbolTablePointer<AcDbViewportTable>  AcDbViewportTablePointer;

// --------- AcDbSymbolTableRecordPointer<T_OBJECT> ---------

// This class allows you to open any AcDbSymbolTableRecord or
// AcDbSymbolTableRecord-derived object given its object ID or
// its name and containing database.  The different forms of
// construction are:
//
// (AcDbObjectId objId, AcDb::OpenMode mode, bool openErased)
// (const ACHAR * name, AcDbDatabase * pDb,
//  AcDb::OpenMode mode, bool openErased)
//
// The object ID, open mode, and open-erased arguments have the
// same meaning as those for AcDbObjectPointer<T_OBJECT>.  If
// the name is a null pointer, the open status after
// construction is eInvalidInput.  If the database pointer is a
// null pointer, then the open status after construction is
// eNullObjectPointer.

template<class T_OBJECT>
class AcDbSymbolTableRecordPointer : public AcDbObjectPointerBase<T_OBJECT>
{
public:
    AcDbSymbolTableRecordPointer();
    AcDbSymbolTableRecordPointer(AcDbObjectId   objId,
                                 AcDb::OpenMode mode = AcDb::kForRead,
                                 bool           openErased = false);
    AcDbSymbolTableRecordPointer(const ACHAR *   name,
                                 AcDbDatabase * pDb,
                                 AcDb::OpenMode mode = AcDb::kForRead,
                                 bool           openErased = false);

#if DBOBJPTR_EXPOSE_PTR_REF
    AcDbSymbolTableRecordPointer(T_OBJECT * pObject);
    void operator=(T_OBJECT *pObject);
#endif

    Acad::ErrorStatus open(AcDbObjectId   objId,
                           AcDb::OpenMode mode = AcDb::kForRead,
                           bool           openErased = false);
    Acad::ErrorStatus open(const ACHAR *   name,
                           AcDbDatabase * pDb,
                           AcDb::OpenMode mode = AcDb::kForRead,
                           bool           openErased = false);

private:
    // Copy and assignment prohibited.
    AcDbSymbolTableRecordPointer(const AcDbSymbolTableRecordPointer &) = delete;
    AcDbSymbolTableRecordPointer& operator=(const AcDbSymbolTableRecordPointer &) = delete;

    // Restrict T_OBJECT to AcDbSymbolTableRecord and derived classes.
    typedef typename T_OBJECT::TableType T2;
};

typedef AcDbSymbolTableRecordPointer<AcDbBlockTableRecord>
                                     AcDbBlockTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbDimStyleTableRecord>
                                     AcDbDimStyleTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbLayerTableRecord>
                                     AcDbLayerTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbLinetypeTableRecord>
                                     AcDbLinetypeTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbRegAppTableRecord>
                                     AcDbRegAppTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbTextStyleTableRecord>
                                     AcDbTextStyleTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbUCSTableRecord>
                                     AcDbUCSTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbViewTableRecord>
                                     AcDbViewTableRecordPointer;
typedef AcDbSymbolTableRecordPointer<AcDbViewportTableRecord>
                                     AcDbViewportTableRecordPointer;

// --------- Inline definitions ---------

template<class T_OBJECT> inline
AcDbObjectPointerBase<T_OBJECT>::AcDbObjectPointerBase()
    : m_ptr(NULL),
      m_status(Acad::eNullObjectPointer)
{
}

template<class T_OBJECT> inline
AcDbObjectPointerBase<T_OBJECT>::AcDbObjectPointerBase(
    AcDbObjectId   objId,
    AcDb::OpenMode mode,
    bool           openErased)
    : m_ptr(NULL),
      m_status(acdbOpenObject(m_ptr, objId, mode, openErased))
{
}

template<class T_OBJECT> inline
AcDbObjectPointerBase<T_OBJECT>::~AcDbObjectPointerBase()
{
    if (m_ptr != NULL) {
        assert(m_status == Acad::eOk);
        Acad::ErrorStatus closeStatus = closeInternal();
        (void)closeStatus;
        assert(closeStatus == Acad::eOk);
    }
}

template<class T_OBJECT> inline Acad::ErrorStatus 
AcDbObjectPointerBase<T_OBJECT>::open(
    AcDbObjectId   objId,
    AcDb::OpenMode mode,
    bool           openErased)
{
    if (m_ptr != NULL) {
        assert(m_status == Acad::eOk);
        Acad::ErrorStatus closeStatus = closeInternal();
        if (closeStatus != Acad::eOk)
            return closeStatus;
    }
    m_status = acdbOpenObject(m_ptr, objId, mode, openErased);
    return m_status;
}

template<class T_OBJECT> inline const T_OBJECT *
AcDbObjectPointerBase<T_OBJECT>::object() const
{
    assert(m_status == Acad::eOk);
    assert(m_ptr != NULL);
    DbObjPtr_Assert(m_ptr == NULL || m_ptr->isReadEnabled());
    return m_ptr;
}

// This function does not modify the object, but we may not make
// it const.  Doing so will overload it with the const operator->()
// function above, which is not allowed (we're overloading on
// const-ness).
template<class T_OBJECT> inline T_OBJECT *
AcDbObjectPointerBase<T_OBJECT>::object()
{
    assert(m_status == Acad::eOk);
    assert(m_ptr != NULL);
    DbObjPtr_Assert(m_ptr == NULL || m_ptr->isReadEnabled());
    return m_ptr;
}

template<class T_OBJECT> inline const T_OBJECT *
AcDbObjectPointerBase<T_OBJECT>::operator->() const
{
    return object();
}

template<class T_OBJECT> inline T_OBJECT *
AcDbObjectPointerBase<T_OBJECT>::operator->()
{
    return object();
}

template<class T_OBJECT> inline 
AcDbObjectPointerBase<T_OBJECT>::operator const T_OBJECT*() const
{
    return object();
}

#if DBOBJPTR_EXPOSE_PTR_REF
template<class T_OBJECT> inline 
AcDbObjectPointerBase<T_OBJECT>::operator T_OBJECT* &()
{
    // Allows direct modification of the pointer member
    return this->m_ptr;
}
#else
template<class T_OBJECT> inline 
AcDbObjectPointerBase<T_OBJECT>::operator T_OBJECT*()
{
    return object();
}
#endif

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbObjectPointerBase<T_OBJECT>::openStatus() const
{
    return m_status;
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbObjectPointerBase<T_OBJECT>::acquire(T_OBJECT *& pObjToAcquire)
{
    if (pObjToAcquire == NULL)
        return Acad::eNullObjectPointer;
    if (m_ptr != NULL) {
        assert(m_status == Acad::eOk);
        Acad::ErrorStatus closeStatus = closeInternal();
        if (closeStatus != Acad::eOk)
            return closeStatus;
    }
    m_ptr = pObjToAcquire;
    m_status = Acad::eOk;
    pObjToAcquire = NULL;
    return Acad::eOk;
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbObjectPointerBase<T_OBJECT>::release(T_OBJECT *& pReleasedObj)
{
    if (m_ptr == NULL)
        return Acad::eNullObjectPointer;
    assert(m_status == Acad::eOk);
    pReleasedObj = m_ptr;
    m_ptr    = NULL;
    m_status = Acad::eNullObjectPointer;
    return Acad::eOk;
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbObjectPointerBase<T_OBJECT>::close()
{
    if (m_ptr == NULL)
        return Acad::eNullObjectPointer;
    assert(m_status == Acad::eOk);
    Acad::ErrorStatus closeStatus = closeInternal();
    ADESK_UNREFED_PARAM(closeStatus);
    assert(closeStatus == Acad::eOk);
    return Acad::eOk;
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbObjectPointerBase<T_OBJECT>::create()
{
    T_OBJECT * pObject = new T_OBJECT;
    if (pObject == NULL)
        return Acad::eNullObjectPointer;
    if (m_ptr != NULL) {
        assert(m_status == Acad::eOk);
        Acad::ErrorStatus closeStatus = closeInternal();
        if (closeStatus != Acad::eOk) {
            delete pObject;
            return closeStatus;
        }
    }
    m_ptr = pObject;
    m_status = Acad::eOk;
    return Acad::eOk;
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbObjectPointerBase<T_OBJECT>::closeInternal()
{
    if (m_ptr == NULL)
        return Acad::eOk;
    Acad::ErrorStatus es = Acad::eOk;
    if (m_ptr->objectId().isNull()) {
        delete m_ptr;
        es = Acad::eOk;
    } else {
        es = m_ptr->close();
    }
    m_ptr       = NULL;
    m_status    = Acad::eNullObjectPointer;
    return es;
}

template<class T_OBJECT> inline
AcDbObjectPointer<T_OBJECT>::AcDbObjectPointer()
    : AcDbObjectPointerBase<T_OBJECT>()
{
}

template<class T_OBJECT> inline
AcDbObjectPointer<T_OBJECT>::AcDbObjectPointer(
    AcDbObjectId   objId,
    AcDb::OpenMode mode,
    bool           openErased)
    : AcDbObjectPointerBase<T_OBJECT>(objId, mode, openErased)
{
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbObjectPointer<T_OBJECT>::open(
    AcDbObjectId   objId,
    AcDb::OpenMode mode,
    bool           openErased)
{
    return AcDbObjectPointerBase<T_OBJECT>::open(objId, mode, openErased);
}

template<class T_OBJECT> inline
AcDbSymbolTablePointer<T_OBJECT>::AcDbSymbolTablePointer()
    : AcDbObjectPointerBase<T_OBJECT>()
{
}

template<class T_OBJECT> inline
AcDbSymbolTablePointer<T_OBJECT>::AcDbSymbolTablePointer(
    AcDbObjectId   objId,
    AcDb::OpenMode mode)
    : AcDbObjectPointerBase<T_OBJECT>(objId, mode, false)
{
}

template<class T_OBJECT> inline
AcDbSymbolTablePointer<T_OBJECT>::AcDbSymbolTablePointer(
    AcDbDatabase * pDb,
    AcDb::OpenMode mode)
    : AcDbObjectPointerBase<T_OBJECT>()
{
    this->m_status = (pDb == NULL) ? Acad::eNullObjectPointer
                             : pDb->getSymbolTable(this->m_ptr, mode);
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbSymbolTablePointer<T_OBJECT>::open(
    AcDbObjectId   objId,
    AcDb::OpenMode mode)
{
    return AcDbObjectPointerBase<T_OBJECT>::open(objId, mode, false);
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbSymbolTablePointer<T_OBJECT>::open(
    AcDbDatabase* pDb,
    AcDb::OpenMode mode)
{
    if (pDb == NULL)
        return Acad::eInvalidInput;
    Acad::ErrorStatus es = Acad::eOk;
    if (this->m_ptr != NULL)
        es = this->close();
    if (es == Acad::eOk) {
        es = pDb->getSymbolTable(this->m_ptr, mode);
        this->m_status = es;
    }
    return es;
}

template<class T_OBJECT> inline
AcDbSymbolTableRecordPointer<T_OBJECT>::AcDbSymbolTableRecordPointer()
    : AcDbObjectPointerBase<T_OBJECT>()
{
}

template<class T_OBJECT> inline
AcDbSymbolTableRecordPointer<T_OBJECT>::AcDbSymbolTableRecordPointer(
    AcDbObjectId   objId,
    AcDb::OpenMode mode,
    bool           openErased)
    : AcDbObjectPointerBase<T_OBJECT>(objId, mode, openErased)
{
}

template<class T_OBJECT> inline
AcDbSymbolTableRecordPointer<T_OBJECT>
    ::AcDbSymbolTableRecordPointer(
    const ACHAR *   name,
    AcDbDatabase * pDb,
    AcDb::OpenMode mode,
    bool           openErased)
    : AcDbObjectPointerBase<T_OBJECT>()
{
    if (name == NULL)
        this->m_status = Acad::eInvalidInput;
    else {
        AcDbSymbolTablePointer<typename T_OBJECT::TableType>
            pTable(pDb, AcDb::kForRead);
        this->m_status = pTable.openStatus();
        if (this->m_status == Acad::eOk)
            this->m_status = pTable->getAt(name, this->m_ptr, mode, openErased);
    }
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbSymbolTableRecordPointer<T_OBJECT>::open(
    AcDbObjectId   objId,
    AcDb::OpenMode mode,
    bool           openErased)
{
    return AcDbObjectPointerBase<T_OBJECT>::open(objId, mode, openErased);
}

template<class T_OBJECT> inline Acad::ErrorStatus
AcDbSymbolTableRecordPointer<T_OBJECT>
    ::open(const ACHAR *   name,
           AcDbDatabase * pDb,
           AcDb::OpenMode mode,
           bool           openErased)
{
    if (name == NULL)
        return Acad::eInvalidInput;
    else {
        AcDbSymbolTablePointer<typename T_OBJECT::TableType>
            pTable(pDb, AcDb::kForRead);
        Acad::ErrorStatus es = pTable.openStatus();
        if (es == Acad::eOk) {
            if (this->m_ptr != NULL)
                es = this->close();
            if (es == Acad::eOk) {
                es = pTable->getAt(name, this->m_ptr, mode, openErased);
                this->m_status = es;
            }
        }
        return es;
    }
}

#if DBOBJPTR_EXPOSE_PTR_REF

template<class T_OBJECT> inline
AcDbObjectPointerBase<T_OBJECT>::AcDbObjectPointerBase(T_OBJECT *pObject)
    : m_ptr(NULL),
      m_status(Acad::eNullObjectPointer)
{
    if (pObject != NULL)
        this->acquire(pObject);
}

template<class T_OBJECT> inline void
AcDbObjectPointerBase<T_OBJECT>::operator=(T_OBJECT *pObject)
{
    if (pObject == NULL) {
        DbObjPtr_Assert(this->m_ptr == NULL);
    }
    else
        this->acquire(pObject);
}

template<class T_OBJECT> inline
AcDbObjectPointer<T_OBJECT>::AcDbObjectPointer(T_OBJECT *pObject)
                : AcDbObjectPointerBase<T_OBJECT>(pObject)
{
}

template<class T_OBJECT> inline AcDbSymbolTablePointer<T_OBJECT>::
        AcDbSymbolTablePointer(T_OBJECT *pObject)
                : AcDbObjectPointerBase<T_OBJECT>(pObject)
{
}

template<class T_OBJECT> inline AcDbSymbolTableRecordPointer<T_OBJECT>::
        AcDbSymbolTableRecordPointer(T_OBJECT *pObject)
                : AcDbObjectPointerBase<T_OBJECT>(pObject)
{
}

template<class T_OBJECT> inline void
AcDbObjectPointer<T_OBJECT>::operator=(T_OBJECT *pObject)
{
    AcDbObjectPointerBase<T_OBJECT>::operator =(pObject);
}

template<class T_OBJECT> inline void
AcDbSymbolTablePointer<T_OBJECT>::operator=(T_OBJECT *pObject)
{
    AcDbObjectPointerBase<T_OBJECT>::operator =(pObject);
}

template<class T_OBJECT> inline void
AcDbSymbolTableRecordPointer<T_OBJECT>::operator=(T_OBJECT *pObject)
{
    AcDbObjectPointerBase<T_OBJECT>::operator =(pObject);
}

#endif  // DBOBJPTR_EXPOSE_PTR_REF

#pragma pack (pop)

#endif // AD_DBOBJPTR_H
