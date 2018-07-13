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

#ifndef OLEAUTO_H
#define OLEAUTO_H
#include "adesk.h"
#include "acdbport.h"
#ifdef _ADESK_WINDOWS_
#include "dbmain.h"
#pragma pack (push, 8)

//
// AcAxOleLinkManager is used to maintain the link between an ARX
// objects and their respective COM wrapper.
//
class ADESK_NO_VTABLE AcAxOleLinkManager
{
public:
    
    // Given a pointer to a database resident object, return
    // the IUnknown of the COM wrapper. NULL is returned if
    // no wrapper is found.
    virtual IUnknown* GetIUnknown(AcDbObject* pObject) = 0;

    // Set the link between a database resident object and a 
    // COM wrapper. If the IUnknown is NULL, then the link is removed.
    virtual Adesk::Boolean SetIUnknown(AcDbObject* pObject, IUnknown* pUnknown) = 0;

    // Given a pointer to a database object, return
    // the IUnknown of the COM wrapper. NULL is returned if
    // no wrapper is found.
    virtual IUnknown* GetIUnknown(AcDbDatabase* pDatabase) = 0;

    // Set the link between a database object and a COM wrapper. 
    // If the IUnknown is NULL, then the link is removed.
    virtual Adesk::Boolean SetIUnknown(AcDbDatabase* pDatabase, IUnknown* pUnknown) = 0;

    // Given a pointer to a database object, return the
    // IDispatch of then document object. NULL is returned if
    // the database does not belong to a particular document.
    virtual IDispatch* GetDocIDispatch(AcDbDatabase* pDatabase) = 0;

    // Set the link between a database object and the IDispatch
    // of the document it belongs to. If the IDispatch is NULL, then 
    // the link is removed.
    virtual Adesk::Boolean SetDocIDispatch(AcDbDatabase* pDatabase, IDispatch* pDispatch) = 0;

    // Given a pointer to a database resident object and a subentID, return
    // the IUnknown of the COM wrapper. NULL is returned if
    // no wrapper is found.
    virtual IUnknown* GetIUnknown(AcDbObject* pObject,
        const AcDbSubentId &id) = 0;

    // Set the link between a database resident object, a subentID and a 
    // COM wrapper. If the IUnknown is NULL, then the link is removed.
    virtual Adesk::Boolean SetIUnknown(AcDbObject* pObject,
        const AcDbSubentId &id, IUnknown* pUnknown) = 0;
};

ACDB_PORT AcAxOleLinkManager* AcAxGetOleLinkManager();

#pragma pack (pop)

#endif //_ADESK_WINDOWS_
#endif // OLEAUTO_H
