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

#pragma once

#undef ACAD_OBJID_INLINE_INTERNAL
#include "dbhatch.h"
#include <tchar.h>

class AcDbCircle;
class AcDb2dPolyline;
class AcDbPolyline;
class AcDbMPolygonCrossingArray;
class AcDbMPolygonNode;

const double AcDbMPolygonCrossingFuzz = 1E-6;

#ifndef _ADESK_MAC_
#ifndef ACMPOLYGON_PORT
#ifdef ACMPOLYGON_API
    #define ACMPOLYGON_PORT _declspec(dllexport)
#else
    #define ACMPOLYGON_PORT _declspec(dllimport)
#endif
#endif
#else
// On OS X, we will export all symbols by default and will use GCC
// attributes to exclude symbols we don't want to export.
#define ACBASE_PORT
#endif // _ADESK_MAC_


class AcDbMPolygon : public AcDbEntity {
public:

    enum loopDir {
        kExterior     = 0,            // counter clockwise
        kInterior,                    // clockwise
        kAnnotation                   // text
    };

    // Constructors and Destructors
    //
    ACMPOLYGON_PORT AcDbMPolygon();
    ACMPOLYGON_PORT virtual ~AcDbMPolygon();

    ACRX_DECLARE_MEMBERS_EXPIMP(AcDbMPolygon, ACMPOLYGON_PORT);


    //*************************************************************************
    // Methods specific to AcDbMPolygon
    //*************************************************************************

    // Mpolygon hatch member access methods.
    //
    ACMPOLYGON_PORT virtual AcDbHatch * hatch();

    // Hatch Plane Methods
    //
    ACMPOLYGON_PORT virtual double elevation() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus setElevation(double elevation);

    ACMPOLYGON_PORT virtual AcGeVector3d normal() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus setNormal(const AcGeVector3d& normal);

    // Hatch Graphics Display Control Methods
    //
    ACMPOLYGON_PORT virtual Acad::ErrorStatus  evaluateHatch(bool bUnderestimateNumLines = false);

    // Hatch Pattern Methods
    //
    ACMPOLYGON_PORT virtual AcDbHatch::HatchPatternType patternType() const;

    ACMPOLYGON_PORT virtual const TCHAR* patternName() const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus  setPattern(AcDbHatch::HatchPatternType patType,
                                  const TCHAR* patName);

    ACMPOLYGON_PORT virtual double patternAngle() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus setPatternAngle(double angle);

    ACMPOLYGON_PORT virtual double patternSpace() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus setPatternSpace(double space);

    ACMPOLYGON_PORT virtual double patternScale() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus setPatternScale(double scale);

    ACMPOLYGON_PORT virtual bool patternDouble() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus setPatternDouble(bool isDouble);

    ACMPOLYGON_PORT virtual int numPatternDefinitions() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus  getPatternDefinitionAt(int index,
                                              double& angle,
                                              double& baseX,
                                              double& baseY,
                                              double& offsetX,
                                              double& offsetY,
                                              AcGeDoubleArray& dashes)
                                              const;

    // Hatch Gradient support

    ACMPOLYGON_PORT Acad::ErrorStatus setGradientAngle(double angle);
    ACMPOLYGON_PORT Acad::ErrorStatus setGradientShift( float shiftValue );
    ACMPOLYGON_PORT Acad::ErrorStatus setGradientOneColorMode( Adesk::Boolean oneColorMode );
    ACMPOLYGON_PORT Acad::ErrorStatus setGradientColors( unsigned int count,
                                            AcCmColor* colors,
                                            float* values );
    ACMPOLYGON_PORT Acad::ErrorStatus setGradient(AcDbHatch::GradientPatternType gradType,
                                   const TCHAR* gradName);


    // Mpolygon access methods.
    //
    ACMPOLYGON_PORT virtual AcCmColor patternColor() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus setPatternColor(const AcCmColor& pc);

    ACMPOLYGON_PORT virtual double getArea() const;
    ACMPOLYGON_PORT virtual double getPerimeter() const;

    ACMPOLYGON_PORT virtual bool isBalanced() const;

    ACMPOLYGON_PORT virtual AcGeVector2d getOffsetVector() const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus getMPolygonTree(AcDbMPolygonNode*& loopNode) const;
    ACMPOLYGON_PORT virtual void deleteMPolygonTree(AcDbMPolygonNode* loopNode) const;

    // Mpolygon loop quiry and manipulation methods.
    //
    ACMPOLYGON_PORT virtual Acad::ErrorStatus appendLoopFromBoundary(const AcDbCircle* pCircle,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);
    ACMPOLYGON_PORT virtual Acad::ErrorStatus appendLoopFromBoundary(const AcDbPolyline* pPoly,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);
    ACMPOLYGON_PORT virtual Acad::ErrorStatus appendLoopFromBoundary(const AcDb2dPolyline* pPoly,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);

    ACMPOLYGON_PORT virtual int numMPolygonLoops() const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus getMPolygonLoopAt(int loopIndex, AcGePoint2dArray& vertices,
                                        AcGeDoubleArray& bulges) const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus insertMPolygonLoopAt(int loopIndex,
        const AcGePoint2dArray& vertices, const AcGeDoubleArray& bulges,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);

    ACMPOLYGON_PORT virtual Acad::ErrorStatus appendMPolygonLoop(const AcGePoint2dArray& vertices,
        const AcGeDoubleArray& bulges, bool excludeCrossing = true,
        double tol = AcDbMPolygonCrossingFuzz);
    ACMPOLYGON_PORT virtual Acad::ErrorStatus removeMPolygonLoopAt(int loopIndex);

    ACMPOLYGON_PORT virtual Acad::ErrorStatus balanceTree();
    ACMPOLYGON_PORT virtual Acad::ErrorStatus balanceDisplay();

    ACMPOLYGON_PORT virtual Acad::ErrorStatus getLoopDirection(int lindex, AcDbMPolygon::loopDir& dir) const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus setLoopDirection(int lindex, AcDbMPolygon::loopDir dir);

    ACMPOLYGON_PORT virtual Acad::ErrorStatus getLoopAtGsMarker(int gsMark, int &loop) const;
    ACMPOLYGON_PORT virtual void getChildLoops(int curLoop, AcGeIntArray& selectedLoopIndexes) const;
    ACMPOLYGON_PORT virtual int getParentLoop(int curLoop) const;
    ACMPOLYGON_PORT virtual int getClosestLoopTo(const AcGePoint3d& worldPt) const;

    // Mpolyon loop crossing and inside methods.
    //
    ACMPOLYGON_PORT virtual int isPointInsideMPolygon(const AcGePoint3d& worldPt, AcGeIntArray& loopsArray,
                                      double tol = AcDbMPolygonCrossingFuzz) const;
    ACMPOLYGON_PORT virtual bool isPointOnLoopBoundary(const AcGePoint3d& worldPt, int loop,
                                       double tol = AcDbMPolygonCrossingFuzz) const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus loopCrossesItself(bool& crosses, bool findAll,
                                        AcDbMPolygonCrossingArray& crossingsArray,
                                        const AcGePoint2dArray& vertexPts,
                                        const AcGeDoubleArray& vertexBulges,
                                        double tol = AcDbMPolygonCrossingFuzz) const;

    ACMPOLYGON_PORT virtual bool loopCrossesItself(const AcGePoint2dArray& vertexPts,
                           const AcGeDoubleArray& vertexBulges,
                           double tol = AcDbMPolygonCrossingFuzz) const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus loopCrossesMPolygon(bool& crosses, bool findAll,
                                          AcDbMPolygonCrossingArray& crossingsArray,
                                          const AcGePoint2dArray& testVertexPts,
                                          const AcGeDoubleArray& testVertexBulges,
                                          double tol = AcDbMPolygonCrossingFuzz) const;

    ACMPOLYGON_PORT virtual bool selfCrosses(const AcGePoint2dArray& vertexPts,
                     const AcGeDoubleArray& vertexBulges,
                     double tol = AcDbMPolygonCrossingFuzz) const;

    ACMPOLYGON_PORT virtual bool includesTouchingLoops(double tol = AcDbMPolygonCrossingFuzz) const;

    //*************************************************************************
    // Overridden methods from AcDbEntity
    //*************************************************************************
    ACMPOLYGON_PORT virtual Acad::ErrorStatus subGetClassID( CLSID* pClsid) const;

    ACMPOLYGON_PORT virtual Adesk::Boolean    subWorldDraw(AcGiWorldDraw*  mode);
    ACMPOLYGON_PORT virtual void              saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

    ACMPOLYGON_PORT virtual Acad::ErrorStatus subGetSubentPathsAtGsMarker(
        AcDb::SubentType      type,
        Adesk::GsMarker       gsMark,
        const AcGePoint3d&    pickPoint,
        const AcGeMatrix3d&   viewXform,
        int&                  numPaths,
        AcDbFullSubentPath*&  subentPaths,
        int                   numInserts = 0,
        AcDbObjectId*         entAndInsertStack
        = NULL) const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus subGetGsMarkersAtSubentPath(
        const AcDbFullSubentPath& subPath,
        AcArray<Adesk::GsMarker>&         gsMarkers) const;

    ACMPOLYGON_PORT virtual AcDbEntity*       subSubentPtr(const AcDbFullSubentPath& id) const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus   subIntersectWith(
        const AcDbEntity*   ent,
        AcDb::Intersect     intType,
        AcGePoint3dArray&   points,
        Adesk::GsMarker     thisGsMarker  = 0,
        Adesk::GsMarker     otherGsMarker = 0)
        const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus   subIntersectWith(
        const AcDbEntity*   ent,
        AcDb::Intersect     intType,
        const AcGePlane&    projPlane,
        AcGePoint3dArray&   points,
        Adesk::GsMarker     thisGsMarker  = 0,
        Adesk::GsMarker     otherGsMarker = 0)
        const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus   subGetOsnapPoints(
        AcDb::OsnapMode       osnapMode,
        Adesk::GsMarker       gsSelectionMark,
        const AcGePoint3d&    pickPoint,
        const AcGePoint3d&    lastPoint,
        const AcGeMatrix3d&   viewXform,
        AcGePoint3dArray&        snapPoints,
        AcDbIntArray&     geomIds) const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus subGetGripPoints(AcGePoint3dArray&     gripPoints,
        AcDbIntArray&  osnapModes,
        AcDbIntArray&  geomIds) const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbIntArray& indices,
        const AcGeVector3d& offset);

    ACMPOLYGON_PORT virtual Acad::ErrorStatus subGetStretchPoints(AcGePoint3dArray& stretchPoints) const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus subMoveStretchPointsAt( const AcDbIntArray& indices,
        const AcGeVector3d& offset);

    ACMPOLYGON_PORT virtual Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform);
    ACMPOLYGON_PORT virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;
    ACMPOLYGON_PORT virtual void              subList() const;

    ACMPOLYGON_PORT virtual Acad::ErrorStatus   subExplode( AcDbVoidPtrArray& entitySet) const;

    //*************************************************************************
    // Overridden methods from AcDbObject
    //*************************************************************************

    ACMPOLYGON_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    ACMPOLYGON_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    ACMPOLYGON_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
    ACMPOLYGON_PORT virtual Acad::ErrorStatus audit(AcDbAuditInfo* );
    ACMPOLYGON_PORT virtual Acad::ErrorStatus decomposeForSave(AcDb::AcDbDwgVersion ver,
        AcDbObject*& replaceObj, AcDbObjectId& replaceId,
        Adesk::Boolean& exchangeXData);

    // Batch Mpolygon creation (it should have no loops)
    //
    ACMPOLYGON_PORT virtual Acad::ErrorStatus createLoopsFromBoundaries (const AcDbObjectIdArray &ids,
        AcDbIntArray &rejectedObjs,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);
    ACMPOLYGON_PORT virtual Acad::ErrorStatus createLoops (const AcArray<AcGePoint2dArray,AcArrayObjectCopyReallocator<AcGePoint2dArray> > &vertices,
        const AcArray<AcGeDoubleArray,AcArrayObjectCopyReallocator<AcGeDoubleArray> > &bulges, AcDbIntArray &rejectedObjs,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);

private:
    friend class AcDbImpMPolygon;
    void* pImp;
};

// This class is used during loop editing to store loops.
// The MpolygonUI.arx application uses this during dragging
// while in the MPEDT Move command.
class AcDbMpolygonLoops {
public:
    AcDbMpolygonLoops(int lindex, int gindex = 0, int gcnt = 0);

    int mLoopIndex;                   // AcDbHatch loop index.
    bool mIsText;                     // Annotation Loop?
    int mGripIndex;                   // Base grip index for this loop (grip editing only.)
    int mGripCount;                   // Number of hot grips in the loop (grip editing only.)
    AcGePoint2dArray mVertexPoints;
    AcGeDoubleArray mVertexBulges;
};

inline
AcDbMpolygonLoops::AcDbMpolygonLoops(int lindex, int gindex, int gcnt)
{
    mLoopIndex = lindex;
    mGripIndex = gindex;
    mGripCount = gcnt;
}

// This class is used to store one mpolygon loop crossing point.
class AcDbMPolygonCrossing {
public:
    ACMPOLYGON_PORT AcDbMPolygonCrossing();
    ACMPOLYGON_PORT ~AcDbMPolygonCrossing();

    ACMPOLYGON_PORT int getLoopIndex() const;         // Crossing loop index
    ACMPOLYGON_PORT void setLoopIndex(int index);

    ACMPOLYGON_PORT int getEdgeIndex() const;         // Starting vertex index of loop edge
    ACMPOLYGON_PORT void setEdgeIndex(int index);

    ACMPOLYGON_PORT AcGePoint2d getCrossingPoint() const; // Loop crossing point
    ACMPOLYGON_PORT void setCrossingPoint(const AcGePoint2d& pt);

private:
    void* pImp;
};

// An Array of class AcDbMPolygonCrossing (loop crossing points).
class AcDbMPolygonCrossingArray {
public:
    ~AcDbMPolygonCrossingArray();

    AcArray<AcDbMPolygonCrossing *> mCrossingArray;
};


inline
AcDbMPolygonCrossingArray::~AcDbMPolygonCrossingArray()
{
    AcDbMPolygonCrossing* pCrossing;
    int numCross = mCrossingArray.length();
    for (int i = numCross - 1; i >= 0; i--) {
        pCrossing = mCrossingArray[i];
        mCrossingArray.removeAt(i);
        if (pCrossing != NULL)
            delete pCrossing;
    }
}

// The following class is used by the getMPolygonTree API to
//  return the internal tree ordered loops.

class AcDbMPolygonNode {
public:
    // Constructor
    AcDbMPolygonNode();

public:
    AcDbMPolygonNode * mParent;
    AcArray<AcDbMPolygonNode*> mChildren;
    int mLoopIndex;                   // MPolygon loop index.
};

inline
AcDbMPolygonNode::AcDbMPolygonNode()
    : mLoopIndex(-1), mParent(NULL)
{
}
