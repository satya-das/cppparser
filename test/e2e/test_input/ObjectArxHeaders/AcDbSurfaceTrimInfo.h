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
// CREATED BY: Pei Zhan                                 August 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocEdgeActionParam.h"
#include "AcDbCompoundObjectId.h"
#pragma pack (push, 8)

class ENTITY;

/// <summary>
/// AcDbSurfaceTrimInfo describes how a (blank) surface will be trimmed: the 
/// information about trimming (tool) surface and trimming curve (if it is a 
/// trimming curve, a projection vector should be provided so the curve will 
/// be projected on to the blank surface). 
/// Also necessary is the topological information between 
/// the trimmed (blank) surface and trimming(tool) surface/curve - if the area
/// intended to be trimmed is inside or outside of the trimming curve/surface
/// </summary>
///

class ACDB_PORT AcDbSurfaceTrimInfo
{
public:

    /// <summary>
    /// This enum is type of relation betweem tool and trimmed area.
    /// </summary>
    ///
    enum TrimRelation {
        /// <summary>
        /// Trimmed area is outside the tool.
        /// </summary>
        ///
        outside_tool,
        /// <summary>
        /// Trimmed area is inside the tool.
        /// </summary>
        ///
        inside_tool,
    };

    /// <summary> Default constructor. </summary>
    ///
    AcDbSurfaceTrimInfo();

    /// <summary> Default destructor. </summary>
    ///
    virtual ~AcDbSurfaceTrimInfo();

    /// <summary>
    /// set the information about tool if it is an object of AcDbCurve
    /// </summary>
    /// <param name="curveId">
    /// object id of the AcDbCurve
    /// </param>
    /// <param name="projVector">
    /// the vector that specifies how the curve will be projected onto the blank surface
    /// </param>
    /// <param name="relation">
    /// the relation between tool and trimmed area on blank - inside the tool or outside
    /// </param>
    void setTrimInfo( const AcDbCompoundObjectId& curveId, const AcGeVector3d & projVector, TrimRelation relation );

    /// <summary>
    /// set the information about tool if it is a wire body generated from a curve
    /// </summary>
    /// <param name="pWireBody">
    /// ASM wire body of the curve
    /// </param>
    /// <param name="projVector">
    /// the vector that specifies how the curve will be projected onto the blank surface
    /// </param>
    /// <param name="relation">
    /// the relation between tool and trimmed area on blank - inside the tool or outside
    /// </param>
    void setTrimInfo( ENTITY *pWireBody, const AcGeVector3d& projVector, TrimRelation relation);

    /// <summary>
    /// set the information about tool if it is an object of AcDbSurface/AcDbRegion
    /// </summary>
    /// <param name="surfaceId">
    /// id of the AcDbSurface/AcDbRegion object
    /// </param>
    /// <param name="relation">
    /// the relation between tool and trimmed area on blank - inside the tool or outside
    /// </param>
    /// <param name="subentId">
    /// face subentity id that will be used for trimming if the surface has more than one faces
    /// </param>
    void setTrimInfo( const AcDbCompoundObjectId &surfaceId, TrimRelation relation, const AcDbSubentId& subentId);

    /// <summary>
    /// set the information about tool if it is an ASM body from an AcDbSurface/AcDbRegion object
    /// </summary>
    /// <param name="pAsmBody">
    /// ASM body from the AcDbSurface/AcDbRegion object
    /// </param>
    /// <param name="relation">
    /// the relation between tool and trimmed area on blank - inside the tool or outside
    /// </param>
    /// <param name="subentId">
    /// face subentity id that will be used for trimming if the surface has more than one faces
    /// </param>
    void setTrimInfo( ENTITY *pAsmBody, TrimRelation relation, const AcDbSubentId& subentId );

    /// <summary>
    /// if the tool is a curve (either an object of AcDbCurve or a wire body in ASM)
    /// </summary> 
    ///
    bool isCurve() const;

    /// <summary>
    /// For Autodesk Internal Use only.
    /// the ASM body of the tool.
    /// </summary> 
    ///
    ENTITY *toolBody() const;

    /// <summary>
    /// For Autodesk Internal Use only.
    /// set the ASM body of the tool, the tool is represented as either an ASM body or AcDbCompoundObjectId
    /// if this method is called, the ASM body will be stored in the class and no AcDbCompoundObjectId
    /// will be used
    /// </summary> 
    ///
    void setToolBody(ENTITY *pEntity);

    /// <summary>
    /// returns the AcDbCompoundObjectId of the tool, if an ASM body is used, it will return 
    /// AcDbCompoundObjectId::nullId()
    /// </summary> 
    ///
    AcDbCompoundObjectId toolBodyId() const;

    /// <summary>
    /// sets the AcDbCompoundObjectId of the tool, the tool is represented as either an ASM body 
    /// or AcDbCompoundObjectId if this method is called, the AcDbCompoundObjectId will be stored 
    /// and any ASM data that is previously set will be cleared
    /// </summary> 
    ///
    void setToolBodyId( const AcDbCompoundObjectId &toolId );

    /// <summary>
    /// returns the TrimRelation between the tool and trimmed area on the blank
    /// </summary> 
    ///
    TrimRelation relation() const;

    /// <summary>
    /// sets the TrimRelation between the tool and trimmed area on the blank
    /// </summary> 
    ///
    void setRelation( TrimRelation relation );

    /// <summary>
    /// returns the projection vector if the tool is a curve. it is meaningless if 
    /// the tool is a surface/region
    /// </summary> 
    ///
    AcGeVector3d projVector() const;

    /// <summary>
    /// sets the projection vector if the tool is a curve. it shouldn't be called and 
    /// has no effect if the tool is a surface/region
    /// </summary> 
    ///
    void setProjVector(const AcGeVector3d& projVector);

    /// <summary>
    /// returns the subentity id of the face that is used to trim the blank, if
    /// the tool is a surface/region. Returns kNullSubentId if the tool is a curve
    /// </summary> 
    ///
    AcDbSubentId faceSubentId() const;
private:
    bool mbCurve;

    // the projection vector that a curve uses to project onto the blank
    AcGeVector3d mProjVector;

    // tool can be either an AcDbCompoundObjectId (db-resident) or 
    // an ENTITY pointer (non-database resident), they are mutual exclusive
    AcDbCompoundObjectId mToolBodyId;

    // optional face subentity id, if the tool has more than one faces
    AcDbSubentId mToolFaceSubentId;

    mutable ENTITY *mToolBody;

    // the relation between the tool and the trimmed piece (outside or inside)
    TrimRelation mRelation;
};

#pragma pack (pop)