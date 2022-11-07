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
// DESCRIPTION:
// The AcDbBody class is the interface class for representing
// general ACIS bodies inside AutoCAD.  All the functionality
// supported through this class is implemented in the class
// AcDbImpBody and its base classes.

#ifndef GEOMENT_DBBODY_H
#define GEOMENT_DBBODY_H

#include "dbmain.h"
#include "dbsubeid.h"

#pragma pack (push, 8)

class AcDbBody: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBody);
             AcDbBody();
    virtual ~AcDbBody();

    virtual Adesk::Boolean    isNull       () const;
    
    ACDB_PORT virtual void dragStatus(const AcDb::DragStat) override;

    virtual void*             ASMBodyCopy(bool bDeepCopy = false) const;  // INTERNAL USE ONLY
    virtual void const *      getLockedASMBody();                         // INTERNAL USE ONLY
    virtual void              unlockASMBody();                            // INTERNAL USE ONLY
    virtual void*             getLockedWritableASMBody();                 // INTERNAL USE ONLY
    virtual void              commitWritableASMBody();                    // INTERNAL USE ONLY
    virtual Acad::ErrorStatus setASMBody      (const void* modelerBody);  // INTERNAL USE ONLY

    virtual AcDbSubentId    internalSubentId (void*) const;                   // INTERNAL USE ONLY
    virtual void*           internalSubentPtr(const AcDbSubentId& id) const;  // INTERNAL USE ONLY

    static  Acad::ErrorStatus acisOut      (const ACHAR* fileName,
                                            const AcDbVoidPtrArray&);
    static  Acad::ErrorStatus acisIn       (const ACHAR* fileName,
                                            AcDbVoidPtrArray&);
 
    virtual Adesk::UInt32 numChanges() const;

    ACDB_PORT virtual bool usesGraphicsCache();
    
    void invalidateCachedBodySubentIds(); // INTERNAL USE ONLY
};

#pragma pack (pop)

#endif
