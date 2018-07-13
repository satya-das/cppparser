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
// CREATED BY: - Randy Kintzley 10/16/2008
//
// DESCRIPTION:
//
// AcDbAssocEdgePersSubentId concrete derived class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "acarray.h"
#include "dbsubeid.h"
#include "AcDbAssocPersSubentId.h"
#pragma pack (push, 8)


/// <summary>
/// Concrete derived AcDbAssocPersSubentId class that is used to identify edge 
/// subentities by indices of its two end vertices, or generally, by two arbitrary
/// index identifiers.
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocEdgePersSubentId : public AcDbAssocPersSubentId
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocEdgePersSubentId);

    AcDbAssocEdgePersSubentId();

    /// <summary> 
    /// Constructor that creates an AcDbAssocEdgePersSubentId and initializes it 
    /// by indices of the two edge vertices, or generally, by two arbitrary index
    /// identifiers. 
    /// If either index is 0, it means "no index". Otherwise it is up to the 
    /// client code to interpret the meaning of these two index identifiers.
    ///
    /// Polyline vertex subentities are identified by vertexIdentifier2 being 0.
    /// Polyline segment midpoint and segment arc center vertex subentities are
    /// identified by both vertexIdentifier1/2 being not 0 and by a special flag.
    /// </summary>
    /// <param  name="vertexIdentifier1"> Identifier of the start vertex of the edge. </param>
    /// <param  name="vertexIdentifier2"> Identifier of the end vertex of the edge. </param>
    ///
    explicit AcDbAssocEdgePersSubentId(int vertexIdentifier1,
                                       int vertexIdentifier2);

    explicit AcDbAssocEdgePersSubentId(int vertexIdentifier1,
                                       int vertexIdentifier2,
                                       bool isSegArcCenter,
                                       bool isSegMidpoint);

    /// <summary>
    /// Returns number 1 if not null or 0 if null.
    /// </summary>
    /// <param  name="pEntity">   Not used. </param>
    /// <param  name="pDatabase"> Not used. </param>
    /// <returns> Returns count 1 or 0. </returns>
    ///
    virtual int transientSubentCount(const AcDbEntity* pEntity, AcDbDatabase* pDatabase) const override {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(pDatabase);
        return !isNull() ? 1 : 0;
    }

    /// <summary> Returns AcDb::kEdgeSubentType or AcDb::kVertexSubentType. </summary>
    /// <param  name="pEntity">   Not used. </param>
    /// <param  name="pDatabase"> Not used. </param>
    /// <returns> AcDb::kEdgeSubentType or AcDb::kVertexSubentType. </returns>
    ///
    virtual AcDb::SubentType subentType(const AcDbEntity* pEntity, AcDbDatabase* pDatabase) const override;

    /// <summary> 
    /// Returns true iff the AcDbAssocEdgePersSubentId does not identify any subentity.
    /// </summary>
    /// <returns> True iff the AcDbAssocEdgePersSubentId does not identify any subentity. </returns>
    ///
    virtual bool isNull() const override { return mIndex1 == 0; }

    /// <summary>
    /// Returns true iff this and the other AcDbAssocEdgePersSubentId reference
    /// exactly the same subentity of the same entity. It simply compares the 
    /// stored indices.
    /// </summary>
    /// <param name="pEntity">   Not used. </param>
    /// <param name="pDatabase"> Not used. </param>
    /// <param  name="pOther"> The other AcDbAssocEdgePersSubentId. </param>
    /// <returns> True iff this and the other AcDbAssocEdgePersSubentId are equal. </returns>
    ///
    virtual bool isEqualTo(const AcDbEntity* pEntity, AcDbDatabase* pDatabase, const AcDbAssocPersSubentId* pOther) const override;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to read the object data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to read the object data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;

    /// <summary> The standard protocol. </summary>
    /// <param  name="pAuditInfo"> See the AcDbAuditInfo documentation. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo) override;

    /// <summary> Returns the value of the internal index1 data member. </summary>
    /// <returns> Value of the internal index1 data member. </returns>
    ///
    int index1() const;

    /// <summary> Returns the value of the internal index2 data member. </summary>
    /// <returns> Value of the internal index2 data member. </returns>
    ///
    int index2() const;

    /// <summary> 
    /// Returns true if the AcDbAssocEdgePersSubentId identifies a vertex subentity 
    /// that is the center of an arc polyline segment. 
    /// </summary>
    ///
    bool isSegmentArcCenter() const;

    /// <summary> 
    /// Returns true if the AcDbAssocEdgePersSubentId identifies a vertex subentity
    /// that is the midpoint of a polyline segment. 
    /// </summary>
    ///
    bool isSegmentMidpoint () const;

private:
    int mIndex1; // vertex 1
    int mIndex2; // vertex 2

}; // class AcDbAssocEdgePersSubentId

#pragma pack (pop)


