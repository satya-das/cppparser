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
// DESCRIPTION:
//
// The AcDb3dSolid class is the interface class for representing B-REP solids.
//

#pragma once
#ifndef GEOMENT_DBSOL3D_H
#define GEOMENT_DBSOL3D_H

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "acarray.h"
#include "dbsurf.h"
#include "db3dProfile.h"
#include "geintarr.h"

#pragma pack(push, 8)

class AcDb3dSolid: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDb3dSolid);
    AcDb3dSolid();
    virtual ~AcDb3dSolid();

    virtual Acad::ErrorStatus createBox(double xLen, double yLen, double zLen);
    virtual Acad::ErrorStatus createFrustum(double height, double xRadius,
        double yRadius, double topXRadius);
    virtual Acad::ErrorStatus createSphere(double radius);
    virtual Acad::ErrorStatus createTorus(double majorRadius, double minorRadius);
    virtual Acad::ErrorStatus createPyramid(double height, int sides, 
        double radius, double topRadius = 0.0 );
    virtual Acad::ErrorStatus createWedge(double xLen, double yLen, double zLen);
    virtual Acad::ErrorStatus extrude(const AcDbRegion* region, double height,
        double taperAngle = 0.0);
    virtual Acad::ErrorStatus extrudeAlongPath(const AcDbRegion* region,
        const AcDbCurve* path, double taperAngle = 0.0);

    // Calls to this function should be replaced with calls to createRevolvedSolid.
    virtual Acad::ErrorStatus revolve(const AcDbRegion* region,
        const AcGePoint3d& axisPoint, const AcGeVector3d& axisDir,
        double angleOfRevolution);

    // Create revolved solid by revolving an entity or face.
    virtual Acad::ErrorStatus createRevolvedSolid ( AcDbEntity* pRevEnt,
                                                    const AcGePoint3d& axisPnt,
                                                    const AcGeVector3d& axisDir,
                                                    double revAngle, double startAngle,
                                                    AcDbRevolveOptions& revolveOptions );
    virtual Acad::ErrorStatus createRevolvedSolid ( AcDbEntity* pRevEnt,
                                                    const AcDbSubentId& faceSubentId,
                                                    const AcGePoint3d& axisPnt,
                                                    const AcGeVector3d& axisDir,
                                                    double revAngle, double startAngle,
                                                    AcDbRevolveOptions& revolveOptions );

    // Create swept solid by sweeping an entity or face along a path.
    virtual Acad::ErrorStatus createSweptSolid ( AcDbEntity* pSweepEnt,
                                                 AcDbEntity* pPathEnt,
                                                 AcDbSweepOptions& sweepOptions );
    virtual Acad::ErrorStatus createSweptSolid ( AcDbEntity *pSweepEnt,
                                                 const AcDbSubentId& faceSubentId,
                                                 AcDbEntity* pPathEnt,
                                                 AcDbSweepOptions& sweepOptions );

    // Create extruded solid by extruding an entity or face.
    virtual Acad::ErrorStatus createExtrudedSolid ( AcDbEntity* pSweepEnt,
                                                    const AcGeVector3d& directionVec,
                                                    AcDbSweepOptions& sweepOptions );
    virtual Acad::ErrorStatus createExtrudedSolid ( AcDbEntity* pSweepEnt,
                                                    const AcDbSubentId& faceSubentId,
                                                    const AcGeVector3d& directionVec, 
                                                    AcDbSweepOptions& sweepOptions );
    virtual Acad::ErrorStatus createExtrudedSolid ( AcDbEntity* pSweepEnt,
                                                    const AcDbSubentId& faceSubentId,
                                                    double height, 
                                                    AcDbSweepOptions& sweepOptions );
    
    // Create lofted solid.
    virtual Acad::ErrorStatus createLoftedSolid (
        AcArray<AcDbEntity*>& crossSectionCurves,
        AcArray<AcDbEntity*>& guideCurves,
        AcDbEntity* pPathCurve, AcDbLoftOptions& loftOptions );

    /// <summary> 
    /// Creates a lofted solid from the given profiles using the specified options.
    /// The cross sections, guides, and path curve may be entities such as curves or
    /// points.  Edges are not currently allowed for cross sections of a solid.
    /// Only the first and last cross sections may be a point entity.  All other
    /// cross sections must be a closed curve or a surface or region.
    /// Each profile in the guides list must intersect each of the cross-section profiles,
    /// so the guides form a net-like structure with the cross-sections. Both the
    /// cross-section profiles and the guide profiles will lie on the resulting surface.
    /// If any guide profiles are passed in this list, then pPath should be null.
    /// If pPath is non-null, then the resulting surface will follow the shape of this
    /// profile as much as possible. This profile does not need to intersect the
    /// cross-section profiles and does not even need to be near the cross sections.
    /// If this parameter is non-null, then guides should be an empty list. 
    /// </summary>
    /// <param name="crossSections"> 
    /// Input array of profiles to be used as cross sections for the lofting operation. 
    /// </param>
    /// <param name="guides"> 
    /// Input optional array of guide profiles. 
    /// </param>
    /// <param name="pPath"> 
    /// Input optional path profile. 
    /// </param>
    /// <param name="loftOptions"> 
    /// Input loft options. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ACDB_PORT Acad::ErrorStatus createLoftedSolid (
        const AcArray<AcDbLoftProfile*>& crossSections,
        const AcArray<AcDbLoftProfile*>& guides,
        AcDbLoftProfile *pPath, AcDbLoftOptions& loftOptions );

    virtual Acad::ErrorStatus createFrom(const AcDbEntity* pFromEntity);

    virtual  Acad::ErrorStatus getArea(double& area) const;

    ACDB_PORT virtual void dragStatus(const AcDb::DragStat) override;

    virtual void* ASMBodyCopy(bool bDeepCopy = false) const;        // INTERNAL USE ONLY
    virtual void const * getLockedASMBody();                        // INTERNAL USE ONLY
    virtual void unlockASMBody();                                   // INTERNAL USE ONLY
    virtual void*             getLockedWritableASMBody();           // INTERNAL USE ONLY
    virtual void              commitWritableASMBody();              // INTERNAL USE ONLY
    virtual Acad::ErrorStatus setASMBody(const void* modelerBody);  // INTERNAL USE ONLY

    virtual Acad::ErrorStatus checkInterference(const AcDb3dSolid* otherSolid,
        Adesk::Boolean createNewSolid, Adesk::Boolean& solidsInterfere,
        AcDb3dSolid*& commonVolumeSolid)const;

    virtual Acad::ErrorStatus getMassProp(double& volume,
        AcGePoint3d& centroid, double momInertia[3], double prodInertia[3],
        double prinMoments[3], AcGeVector3d prinAxes[3], 
        double radiiGyration[3], AcDbExtents& extents) const;

    virtual Adesk::Boolean isNull() const;

    virtual Acad::ErrorStatus getSection(const AcGePlane& plane,
        AcDbRegion*& sectionRegion) const;

    ACDB_PORT virtual Acad::ErrorStatus stlOut(const ACHAR* fileName, 
        Adesk::Boolean asciiFormat, double maxSurfaceDeviation = 0.0 /*use default*/) const;

    virtual AcDbSubentId internalSubentId(void* ent) const;          // INTERNAL USE ONLY
    virtual void* internalSubentPtr(const AcDbSubentId& id) const;   // INTERNAL USE ONLY

    // Subentity acquisition.
    //
    virtual Acad::ErrorStatus booleanOper(AcDb::BoolOperType operation,
        AcDb3dSolid* solid);

    virtual Acad::ErrorStatus getSlice(const AcGePlane& plane,
        Adesk::Boolean getNegHalfToo, AcDb3dSolid*& negHalfSolid);
    virtual Acad::ErrorStatus getSlice(AcDbSurface* pSurface,
        bool bGetNegHalfToo, AcDb3dSolid*& pNegHalfSolid);
    
    virtual Adesk::UInt32 numChanges() const;

    virtual Acad::ErrorStatus copyEdge(const AcDbSubentId &subentId,
        AcDbEntity *&newEntity);
    virtual Acad::ErrorStatus copyFace(const AcDbSubentId &subentId,
        AcDbEntity *&newEntity);
    virtual Acad::ErrorStatus extrudeFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds, double height, 
        double taper);
    virtual Acad::ErrorStatus extrudeFacesAlongPath(
        const AcArray<AcDbSubentId *> &faceSubentIds, const AcDbCurve* path);
    virtual Acad::ErrorStatus imprintEntity(const AcDbEntity *pEntity);
    virtual Acad::ErrorStatus cleanBody();
    virtual Acad::ErrorStatus offsetBody(double offsetDistance);
    ACDB_PORT virtual Acad::ErrorStatus offsetFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds, double offsetDistance);
    virtual Acad::ErrorStatus removeFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds);
    virtual Acad::ErrorStatus separateBody(AcArray<AcDb3dSolid *> &newSolids);
    virtual Acad::ErrorStatus shellBody(
        const AcArray<AcDbSubentId *> &faceSubentIds, double offsetDistance);
    virtual Acad::ErrorStatus taperFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds, 
        const AcGePoint3d &basePoint, const AcGeVector3d &draftVector,
        double draftAngle);
    virtual Acad::ErrorStatus transformFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds,
        const AcGeMatrix3d &matrix);

    virtual Acad::ErrorStatus setSubentColor(const AcDbSubentId &subentId,
        const AcCmColor &color);
    virtual Acad::ErrorStatus getSubentColor(const AcDbSubentId &subentId,
        AcCmColor &color) const;

    virtual Acad::ErrorStatus setSubentMaterial(const AcDbSubentId &subentId,
                                                AcDbObjectId matId);
    virtual Acad::ErrorStatus getSubentMaterial(const AcDbSubentId &subentId,
                                                AcDbObjectId& matId) const;


    virtual Acad::ErrorStatus setSubentMaterialMapper(const AcDbSubentId &subentId,
                                                    const AcGiMapper& mapper);
    virtual Acad::ErrorStatus getSubentMaterialMapper(const AcDbSubentId &subentId,
                                                    AcGiMapper& mapper) const;



    virtual bool recordHistory() const;

    virtual Acad::ErrorStatus setRecordHistory(bool bRecord);

    virtual bool showHistory() const;

    virtual Acad::ErrorStatus setShowHistory(bool bShow);

    virtual Acad::ErrorStatus convertToBrepAtSubentPaths(
                                 const AcDbFullSubentPathArray& paths);

    virtual Acad::ErrorStatus chamferEdges(
                            const AcArray<AcDbSubentId *> &edgeSubentIds,
                            const AcDbSubentId& baseFaceSubentId, 
                            double baseDist, double otherDist);

    virtual Acad::ErrorStatus filletEdges(
                            const AcArray<AcDbSubentId *> &edgeSubentIds,
                            const AcGeDoubleArray& radius, 
                            const AcGeDoubleArray& startSetback, 
                            const AcGeDoubleArray& endSetback);

    ACDB_PORT virtual bool usesGraphicsCache();

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;

public:
    Acad::ErrorStatus createSculptedSolid(
        const AcArray<AcDbEntity*>& limitingBodies,
        const AcGeIntArray& limitingFlags);

    Acad::ErrorStatus projectOnToSolid(const AcDbEntity* pEntityToProject,
        const AcGeVector3d& projectionDirection,
        AcArray<AcDbEntity*>& projectedEntities) const;
};

#pragma pack(pop)
#endif
