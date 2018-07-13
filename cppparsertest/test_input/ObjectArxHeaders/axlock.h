//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _AXLOCK_H
#define _AXLOCK_H

#include "acadstrc.h"
#include "AcDbCore2dDefs.h"

#pragma pack (push, 8)

class AcDbDatabase;
class AcDbObjectId;

class AcAxDocLock
{
public:

    // When appending entities to a database from the session context, 
    // AutoCAD requires the following be true to properly append and
    // display the entities:
    //
    // 1. The document is locked
    // 2. The document context is current
    //
    // The document for a database needs to be locked before any write 
    // operation is performed. Since, AutoCAD has graphics information
    // in a per document basis. The document context for the database
    // must be current during the creation of any new entities. This 
    // will guarantee the graphics are updated correctly.
    //
    // Document activation is disabled to deal with the possibility that 
    // a user could attempt to activate another document while a local 
    // COM client is in the process of appending a new entity.

    enum DocLockType
    {
        kNormal         = 0,    // Locking to allow write operations
        kCurDocSwitch   = 1     // Locking + switch the doc context;
                                //  document activation is disabled in
                                //  this mode.
    };
    
    // Constructors are responsible for performing all necessary
    // operations and keeping track of what must be undone in
    // the destructor.
    AcAxDocLock();    // locks the current document w/ normal lock type
    AcAxDocLock(const AcDbObjectId& objectId, DocLockType = kNormal);
    AcAxDocLock(AcDbDatabase * pDatabase, DocLockType = kNormal);

    // Destructor is responsible for reseting everything to its prior
    // state. This is done using information cached during construction.
    ~AcAxDocLock();

    // Return lock status to caller. Use this function after construction
    // to determine whether the locking succeeded or not.
    ACDBCORE2D_PORT Acad::ErrorStatus lockStatus() const;

    // Return the pointer of document which has been successfully locked. 
    ACDBCORE2D_PORT void* document() const;
private:

    void lockDocument(AcDbDatabase* pDatabase, DocLockType lockType = kNormal);
    void initialize();

    Acad::ErrorStatus   m_lockStatus;
    void*               m_pDocToUnlock;
    void*               m_pCurDocToRestore;
    bool                m_restoreActivation;
};

#pragma pack (pop)

#endif      // _AXLOCK_H
