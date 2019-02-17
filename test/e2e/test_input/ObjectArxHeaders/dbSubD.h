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
// Name:        dbsubd.h
//
// Description: AcDbSubDMesh api class declaration
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "dbmain.h"
#include "gevc3dar.h"

#pragma pack(push, 8)

class AcDbSurface;
class AcGiFaceData;
class AcGiMapper;

///////////////////////////////////////////////////////////////////////////////
// class AcDbSubDMesh
//
class ACDB_PORT AcDbSubDMesh: public AcDbEntity
{
    ACDB_DECLARE_MEMBERS(AcDbSubDMesh);

public:
                                AcDbSubDMesh            ();
    virtual                    ~AcDbSubDMesh            ();

    ///////////////////////////////////////////////////////////////////////////
    // Methods for AcDbSubDMesh
    ///////////////////////////////////////////////////////////////////////////
    //
    Acad::ErrorStatus           setSubDMesh             (const AcGePoint3dArray& vertexArray,
                                                         const AcArray<Adesk::Int32>& faceArray,
                                                         int subDLevel);

    Acad::ErrorStatus           setSphere               (double radius,
                                                         int divAxis,
                                                         int divHeight,
                                                         int subDLevel);

    Acad::ErrorStatus           setCylinder             (double majorRadius,
                                                         double minorRadius,
                                                         double height,
                                                         int divAxis,
                                                         int divHeight,
                                                         int divCap,
                                                         int subDLevel);

    Acad::ErrorStatus           setCone                 (double majorRadius,
                                                         double minorRadius,
                                                         double height,
                                                         int divAxis,
                                                         int divHeight,
                                                         int divCap,
                                                         double radiusRatio,
                                                         int subDLevel);

    Acad::ErrorStatus           setTorus                (double majorRadius,
                                                         int divSection,
                                                         int divSweepPath,
                                                         double sectionRadiusRatio,
                                                         double sectionRotate,
                                                         int subDLevel);

    Acad::ErrorStatus           setBox                  (double xLen,
                                                         double yLen,
                                                         double zLen,
                                                         int divX,
                                                         int divY,
                                                         int divZ,
                                                         int subDLevel);

    Acad::ErrorStatus           setWedge                (double xLen,
                                                         double yLen,
                                                         double zLen,
                                                         int divLength,
                                                         int divWidth,
                                                         int divHeight,
                                                         int divSlope,
                                                         int divCap,
                                                         int subDLevel);

    Acad::ErrorStatus           setPyramid              (double radius,
                                                         double height,
                                                         int divLength,
                                                         int divHeight,
                                                         int divCap,
                                                         int nSides,
                                                         double radiusRatio,
                                                         int subDLevel);

    Acad::ErrorStatus           subdDivideUp            ();
    Acad::ErrorStatus           subdDivideDown          ();
    Acad::ErrorStatus           subdRefine              ();
    Acad::ErrorStatus           subdRefine              (const AcDbFullSubentPathArray& subentPaths);
    Acad::ErrorStatus           subdLevel               (Adesk::Int32& result) const;

    Acad::ErrorStatus           splitFace               (const AcDbSubentId& subentFaceId,
                                                         const AcDbSubentId& subent0,
                                                         const AcGePoint3d& point0,
                                                         const AcDbSubentId& subent1,
                                                         const AcGePoint3d& point1);

    Acad::ErrorStatus           extrudeFaces            (const AcDbFullSubentPathArray& subentPaths,
                                                         double length,
                                                         const AcGeVector3d& dir,
                                                         double taper);

    Acad::ErrorStatus           extrudeFaces            (const AcDbFullSubentPathArray& subentPaths,
                                                         const AcGePoint3dArray& alongPath,
                                                         double taper);

    Acad::ErrorStatus           extrudeConnectedFaces   (const AcDbFullSubentPathArray& subentPaths,
                                                         double length,
                                                         const AcGeVector3d& dir,
                                                         double taper);

    Acad::ErrorStatus           extrudeConnectedFaces   (const AcDbFullSubentPathArray& subentPaths,
                                                         const AcGePoint3dArray& alongPath,
                                                         double taper);

    Acad::ErrorStatus           mergeFaces              (const AcDbFullSubentPathArray& subentPaths);
    Acad::ErrorStatus           collapse                (const AcDbSubentId& subent);
    Acad::ErrorStatus           cap                     (const AcDbFullSubentPathArray& edgePaths);
    Acad::ErrorStatus           spin                    (const AcDbSubentId& subent);

    Acad::ErrorStatus           isWatertight            (bool& result) const;

    Acad::ErrorStatus           numOfFaces              (Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfSubDividedFaces    (Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfSubDividedFacesAt  (const AcDbFullSubentPathArray& subentPaths, Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfVertices           (Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfSubDividedVertices (Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfEdges              (Adesk::Int32& result) const;

    Acad::ErrorStatus           getVertices             (AcGePoint3dArray& vertexArray) const;
    Acad::ErrorStatus           getEdgeArray            (AcArray<Adesk::Int32>& edgeArray) const;
    Acad::ErrorStatus           getFaceArray            (AcArray<Adesk::Int32>& faceArray) const;
    Acad::ErrorStatus           getNormalArray          (AcGeVector3dArray& normalArray) const;

    Acad::ErrorStatus           getSubDividedVertices   (AcGePoint3dArray& vertexArray) const;
    Acad::ErrorStatus           getSubDividedFaceArray  (AcArray<Adesk::Int32>& faceArray) const;
    Acad::ErrorStatus           getSubDividedNormalArray(AcGeVector3dArray& normalArray) const;

    Acad::ErrorStatus           getVertexAt             (Adesk::Int32 nIndex, AcGePoint3d& vertex) const;
    Acad::ErrorStatus           setVertexAt             (Adesk::Int32 nIndex, const AcGePoint3d& vertex);
    Acad::ErrorStatus           getVertexAt             (const AcDbSubentId& id, AcGePoint3d& vertex) const;
    Acad::ErrorStatus           setVertexAt             (const AcDbSubentId& id, const AcGePoint3d& vertex);

    Acad::ErrorStatus           getSubDividedVertexAt   (Adesk::Int32 nIndex, AcGePoint3d& vertex) const;
    Acad::ErrorStatus           getSubDividedVertexAt   (const AcDbSubentId& id, AcGePoint3d& vertex) const;

    Acad::ErrorStatus           setCrease               (double creaseVal);
    Acad::ErrorStatus           setCrease               (const AcDbFullSubentPathArray& subentPaths, double creaseVal);
    Acad::ErrorStatus           getCrease               (const AcDbFullSubentPathArray& subentPaths, AcArray<double>& result) const;
    Acad::ErrorStatus           getCrease               (const AcDbSubentId& id, double& result) const;

    Acad::ErrorStatus           getAdjacentSubentPath   (const AcDbFullSubentPath& path,
                                                         AcDb::SubentType type,
                                                         AcDbFullSubentPathArray& subentPaths) const;

    Acad::ErrorStatus           getSubentPath           (Adesk::Int32 nIndex,
                                                         AcDb::SubentType type,
                                                         AcDbFullSubentPathArray& subentPaths) const;

    Acad::ErrorStatus           convertToSurface        (bool bConvertAsSmooth, const AcDbSubentId& id, AcDbSurface*& pSurface) const;
    Acad::ErrorStatus           convertToSurface        (bool bConvertAsSmooth, bool optimize, AcDbSurface*& pSurface) const;
    Acad::ErrorStatus           convertToSolid          (bool bConvertAsSmooth, bool optimize, AcDb3dSolid*& pSolid) const;

    Acad::ErrorStatus           getSubentColor          (const AcDbSubentId& id, AcCmColor& color) const;
    Acad::ErrorStatus           setSubentColor          (const AcDbSubentId& id, const AcCmColor& color);
    Acad::ErrorStatus           getSubentMaterial       (const AcDbSubentId& id, AcDbObjectId& material) const;
    Acad::ErrorStatus           setSubentMaterial       (const AcDbSubentId& id, const AcDbObjectId& material);
    Acad::ErrorStatus           getSubentMaterialMapper (const AcDbSubentId& id, AcGiMapper& mapper) const;
    Acad::ErrorStatus           setSubentMaterialMapper (const AcDbSubentId& id, const AcGiMapper& mapper);

    Acad::ErrorStatus           getFacePlane            (const AcDbSubentId& id, AcGePlane& facePlane) const;

    Acad::ErrorStatus           computeVolume           (double &retVolume) const;
    Acad::ErrorStatus           computeSurfaceArea      (double &retSurfArea) const;

    ///////////////////////////////////////////////////////////////////////////
    // Overridden methods from AcDbEntity
    ///////////////////////////////////////////////////////////////////////////
    //
    virtual void                dragStatus              (const AcDb::DragStat status) override;
    virtual Acad::ErrorStatus   subGetClassID           (CLSID* pClsid) const override;

    ///////////////////////////////////////////////////////////////////////////
    // Overridden methods from AcGiDrawable
    ///////////////////////////////////////////////////////////////////////////
    //
    virtual bool                bounds                  ( AcDbExtents& retBounds ) const override;

    ///////////////////////////////////////////////////////////////////////////
    // Internal use
    ///////////////////////////////////////////////////////////////////////////
    //
    Acad::ErrorStatus           setSphere               (const AcGeMatrix3d& xForm,
                                                         int divAxis,
                                                         int divHeight,
                                                         int subDLevel);

    Acad::ErrorStatus           setCylinder             (const AcGeMatrix3d& xForm,
                                                         int divAxis,
                                                         int divHeight,
                                                         int divCap,
                                                         int subDLevel);

    Acad::ErrorStatus           setCone                 (const AcGeMatrix3d& xForm,
                                                         int divAxis,
                                                         int divHeight,
                                                         int divCap,
                                                         double radiusRatio,
                                                         int subDLevel);

    Acad::ErrorStatus           setTorus                (const AcGeMatrix3d& xForm,
                                                         int divSection,
                                                         int divSweepPath,
                                                         double sectionRadiusRatio,
                                                         double sectionRotate,
                                                         int subDLevel);

    Acad::ErrorStatus           setBox                  (const AcGeMatrix3d& xForm,
                                                         int divX,
                                                         int divY,
                                                         int divZ,
                                                         int subDLevel);

    Acad::ErrorStatus           setWedge                (const AcGeMatrix3d& xForm,
                                                         int divLength,
                                                         int divWidth,
                                                         int divHeight,
                                                         int divSlope,
                                                         int divCap,
                                                         int subDLevel);

    Acad::ErrorStatus           setPyramid              (const AcGeMatrix3d& xForm,
                                                         int divLength,
                                                         int divHeight,
                                                         int divCap,
                                                         int nSides,
                                                         double radiusRatio,
                                                         int subDLevel);

    Acad::ErrorStatus           computeRayIntersection  (const AcGePoint3d &rayStart,
                                                         const AcGeVector3d &rayDir,
                                                         AcArray<AcDbSubentId> &retSubents,
                                                         AcArray<double> &retIntersectDist,
                                                         AcGePoint3dArray& retIntersectPoint) const;

    Acad::ErrorStatus           setVertexNormalArray(AcGeVector3dArray &arr);
    Acad::ErrorStatus           setVertexTextureArray(AcGePoint3dArray &arr);
    Acad::ErrorStatus           setVertexColorArray(AcArray<AcCmEntityColor> &arr);

    Acad::ErrorStatus           getVertexNormalArray(AcGeVector3dArray &arr);
    Acad::ErrorStatus           getVertexTextureArray(AcGePoint3dArray &arr);
    Acad::ErrorStatus           getVertexColorArray(AcArray<AcCmEntityColor> &arr);
};

///////////////////////////////////////////////////////////////////////////
//  Global API functions 
///////////////////////////////////////////////////////////////////////////
//
struct MeshFaceterSettings
{
    double faceterDevSurface;
    double faceterDevNormal;
    double faceterGridRatio;
    double faceterMaxEdgeLength;
    Adesk::UInt16 faceterMaxGrid;
    Adesk::UInt16 faceterMinUGrid; // Unused
    Adesk::UInt16 faceterMinVGrid; // Unused
    Adesk::Int16 faceterMeshType;
};

typedef struct MeshFaceterSettings  AcDbFaceterSettings;

ACDB_PORT  Acad::ErrorStatus acdbGetObjectMesh(AcDbObject *pObj, 
                                               const AcDbFaceterSettings *faceter,
                                               AcGePoint3dArray& vertexArray, 
                                               AcArray<Adesk::Int32>& faceArray,
                                               AcGiFaceData*& faceData); 

#pragma pack(pop)
