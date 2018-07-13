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

#pragma once

#include "rxobject.h"
#include "rxboiler.h"
#include "acbasedefs.h" // ACBASE_PORT

#pragma pack(push, 8)

///////////////////////////////////////////////////////////////////////////////
// class AcRxCopyOnWriteObject
//
class AcRxCopyOnWriteObject : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxCopyOnWriteObject, ACBASE_PORT);

    ACBASE_PORT AcRxCopyOnWriteObject(AcRxObject* pData);
    ACBASE_PORT AcRxCopyOnWriteObject(const AcRxCopyOnWriteObject& other);
    ACBASE_PORT ~AcRxCopyOnWriteObject();
    ACBASE_PORT const AcRxCopyOnWriteObject& operator=(const AcRxCopyOnWriteObject& other);

protected:
    ACBASE_PORT AcRxObject* write();
    ACBASE_PORT const AcRxObject* read() const;
    ACBASE_PORT void unshare();

private:
    void* m_pData;
};

///////////////////////////////////////////////////////////////////////////////
// Definition of helper macros
///////////////////////////////////////////////////////////////////////////////

#define ACRX_DECLARE_MEMBERS_READWRITE(CLASS_NAME, DATA_NAME)   \
    ACRX_DECLARE_MEMBERS(CLASS_NAME);                           \
    DATA_NAME* write()                                          \
    {                                                           \
        return (DATA_NAME*)AcRxCopyOnWriteObject::write();      \
    }                                                           \
    const DATA_NAME* read() const                               \
    {                                                           \
        return (const DATA_NAME*)AcRxCopyOnWriteObject::read(); \
    }

#pragma pack(pop)
