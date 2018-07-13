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
// CREATED BY: Jiri Kripac                                 March 2007
//
// DESCRIPTION:
//
// AcDbAssocSingleEdgePersSubentId concrete derived class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "acarray.h"
#include "dbsubeid.h"
#include "AcDbAssocPersSubentId.h"
#pragma pack (push, 8)


/// <summary>
/// The concrete derived AcDbAssocPersSubentId class that identifies an edge
/// subentity if the entity has only a single edge subentity (such as in the 
/// case of curve entities).
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocSingleEdgePersSubentId : public AcDbAssocPersSubentId
{
public:

	ACRX_DECLARE_MEMBERS(AcDbAssocSingleEdgePersSubentId);

    /// <summary>
    /// Always returns number 1.
    /// </summary>
    /// <param  name="pEntity">   Not used. </param>
    /// <param  name="pDatabase"> Not used. </param>
    /// <returns> Always returns count 1. </returns>
    ///
    virtual int transientSubentCount(const AcDbEntity* pEntity, AcDbDatabase* pDatabase) const override {
        UNREFERENCED_PARAMETER(pEntity); 
        UNREFERENCED_PARAMETER(pDatabase);
        return 1; 
    }

    /// <summary> Always returns AcDb::kEdgeSubentType. </summary>
    /// <param  name="pEntity">   Not used. </param>
    /// <param  name="pDatabase"> Not used. </param>
    /// <returns> AcDb::kEdgeSubentType. </returns>
    ///
    virtual AcDb::SubentType subentType(const AcDbEntity* pEntity, AcDbDatabase* pDatabase) const override {
        UNREFERENCED_PARAMETER(pEntity);
        UNREFERENCED_PARAMETER(pDatabase);
        return AcDb::kEdgeSubentType;
    }

    /// <summary> 
    /// Always returns false because AcDbAssocSingleEdgePersSubentId always 
    /// identities the single edge of an entity.
    /// </summary>
    /// <returns> Always returns false. </returns>
    ///
    virtual bool isNull() const override { return false; }

    /// <summary>
    /// Returns true iff this and the other AcDbAssocSingleEdgePersSubentId 
    /// reference exactly the same subentity of the same entity. It returns true
    /// if both are of AcDbAssocSingleEdgePersSubentId type.
    /// </summary>
    /// <param name="pEntity">   Not used. </param>
    /// <param name="pDatabase"> Not used. </param>
    /// <param  name="pOther"> The other AcDbAssocSingleEdgePersSubentId. </param>
    /// <returns> True iff this and the other AcDbAssocSingleEdgePersSubentId are equal. </returns>
    ///
    virtual bool isEqualTo(const AcDbEntity* pEntity, AcDbDatabase* pDatabase, const AcDbAssocPersSubentId* pOther) const override;

}; // class AcDbAssocSingleEdgePersSubentId

#pragma pack (pop)


