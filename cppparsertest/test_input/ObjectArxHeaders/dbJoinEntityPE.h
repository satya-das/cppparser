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
// DESCRIPTION: AcDbJoinEntityPE Protocol extension abstract base class
//
#include "acdb.h"
#include "dbmain.h"

#pragma once
#pragma pack (push, 8)

class AcDbJoinEntityPE : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbJoinEntityPE);

    /// <summary>
    /// This method allows application to join secondary entity to the given primary entity.
    /// </summary>
    ///
    /// <param name="pPrimaryEntity">
    /// The primary entity, which is to be updated with the data of the secondary entity joined to it, if possible.
    /// </param>
    /// <param name="pSecondaryEntity">
    /// The secondary entity, which provides the data to be joined to the primary entity.
    /// </param>
    /// <param name="tol">
    /// Optional input tolerance.
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if successful; otherwise, Acad::eInvalidInput.
    /// </returns>
    ///
    /// <remarks>
    /// AcDbJoinEntityPE is the joinEntity protocol extension class. The methods of the class allow you
    /// to join an entity or entities in the given primary entity. The entities that support this protocol 
    /// extension include: AcDbLine, AcDbArc, AcDbPolyline, AcDb2dPolyline, AcDb3dPolyline, and AcDbSpline. 
    /// Applications can implement this protocol extension for other entity types.
    /// </remarks>
    /// 
    virtual Acad::ErrorStatus 
        joinEntity(AcDbEntity* pPrimaryEntity, 
            AcDbEntity* pSecondaryEntity,
            const AcGeTol& tol = AcGeContext::gTol) const = 0;

    /// <summary>
    /// This method allows application to join entities to the given primary entity.
    /// </summary>
    ///
    /// <param name="pPrimaryEntity">
    /// The primary entity, which is to be updated with the data of the secondary entity joined to it, if possible.
    /// </param>
    /// <param name="otherEntities">
    /// The other entities to be joined to the primary entity. Note, some implementations might require all of 
    /// these entities to be of the same time as the primary entity. 
    /// </param>
    /// <param name="joinedEntityIndices">
    /// An array of indices to the entities from the otherEntities array that were successfully joined.
    /// </param>
    /// <param name="tol">
    /// Optional input tolerance.
    /// </param>
    ///
    /// <returns>
    /// Acad::eOk if successful; otherwise, Acad::eInvalidInput.
    /// </returns>
    ///
    /// <remarks>
    /// AcDbJoinEntityPE is the joinEntity protocol extension class. The methods of the class allow you
    /// to join an entity or entities in the given primary entity. The entities that support this protocol 
    /// extension include: AcDbLine, AcDbArc, AcDbPolyline, AcDb2dPolyline, AcDb3dPolyline, and AcDbSpline. 
    /// Applications can implement this protocol extension for other entity types.
    /// </remarks>
    ///     
    virtual Acad::ErrorStatus 
        joinEntities(AcDbEntity* pPrimaryEntity, 
            const AcArray<AcDbEntity*>& otherEntities,
            AcGeIntArray& joinedEntityIndices,
            const AcGeTol& tol = AcGeContext::gTol) const = 0;
};

#pragma pack (pop)

//#endif

