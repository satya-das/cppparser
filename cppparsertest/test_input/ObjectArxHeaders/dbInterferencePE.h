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
// dbInterferencePE.H
//
// DESCRIPTION: AcDbInterferencePE Protocol extension abstract base class
//
#include "acdb.h"
#include "dbmain.h"

#pragma once
#pragma pack (push, 8)

//
//  AcDbInterferencePE Protocol extension abstract base class. 
//
class AcDbInterferencePE : public AcRxObject
{
public:
    enum Flags {
        kDefault     = 0x00,
    };

    ACRX_DECLARE_MEMBERS(AcDbInterferencePE);

    // Contract:
    // Implementer is expected to create new AcDbEntity instance(s), based 
    // on interference between the two provided entities, and append the
    // new ents to the provided array. The caller will either post the new 
    // ents to the db or delete them. 
    //  If the implementer does not know how to generate interference
    // between the provided entities, they should return "eNotApplicable" 
    // or "eNotImplementedYet".
    // If the provided objects do not intersect, return "eNoIntersections".
    virtual Acad::ErrorStatus 
        createInterferenceObjects(  AcArray<AcDbEntity*>& interferenceObjects,
                                    AcDbEntity* pEnt1, 
                                    AcDbEntity* pEnt2,
                                    unsigned int flags ) const = 0;
};

#pragma pack (pop)

//#endif

