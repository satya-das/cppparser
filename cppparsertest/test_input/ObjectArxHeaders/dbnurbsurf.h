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
//
// The AcDbNurbSurface class is the interface class for representing
// ASM NURBS surfaces inside AutoCAD.  

#pragma once

#include "dbsurf.h"
class AcGeKnotVector;
class AcGeNurbSurface;

#pragma pack(push, 8)

class ACDB_PORT AcDbNurbSurface: public AcDbSurface
{
public:

    AcDbNurbSurface();
    AcDbNurbSurface(int uDegree, int vDegree, bool rational,
                    int uNumControlPoints, int vNumControlPoints,
                    const AcGePoint3dArray& ctrlPts,
                    const AcGeDoubleArray& weights,
                    const AcGeKnotVector& uKnots, const AcGeKnotVector& vKnots );

    virtual ~AcDbNurbSurface();
    ACDB_DECLARE_MEMBERS(AcDbNurbSurface);

    //////////////////////////////////////////////////////////
    // NURBS surface methods
    //////////////////////////////////////////////////////////

    // get/set all data 
    Acad::ErrorStatus get (int& uDegree, int& vDegree, bool& rational,
                            int& uNumControlPoints, int& vNumControlPoints,
                            AcGePoint3dArray& ctrlPts, 
                            AcGeDoubleArray& weights,
                            AcGeKnotVector& uKnots, AcGeKnotVector& vKnots) const;
    Acad::ErrorStatus set (int uDegree, int vDegree, bool rational,
                            int uNumControlPoints, int vNumControlPoints,
                            const AcGePoint3dArray& ctrlPts,
                            const AcGeDoubleArray& weights,
                            const AcGeKnotVector& uKnots, const AcGeKnotVector& vKnots);    

    // get/set control points 
    Acad::ErrorStatus getControlPoints(int& uCount, int& vCount, AcGePoint3dArray& points) const;
    Acad::ErrorStatus setControlPoints(int uCount, int vCount, const AcGePoint3dArray& points);

    Acad::ErrorStatus getControlPointAt(int uIndex, int vIndex, AcGePoint3d& point) const;
    Acad::ErrorStatus setControlPointAt(int uIndex, int vIndex, const AcGePoint3d& point);

    // get the number of control points.
    Acad::ErrorStatus getNumberOfControlPointsInU(int& count) const;
    Acad::ErrorStatus getNumberOfControlPointsInV(int& count) const;

    // get knots
    Acad::ErrorStatus getUKnots(AcGeKnotVector& knots) const;
    Acad::ErrorStatus getVKnots(AcGeKnotVector& knots) const;

    // get the number of knots in u or v
    Acad::ErrorStatus getNumberOfKnotsInU(int& count) const;
    Acad::ErrorStatus getNumberOfKnotsInV(int& count) const;

    Acad::ErrorStatus getWeight(int uIndex, int vIndex, double& weight ) const;
    Acad::ErrorStatus setWeight(int uIndex, int vIndex, double weight );

    // Evaluate position, first and second derivatives
    Acad::ErrorStatus evaluate(double u, double v, AcGePoint3d& pos) const;
    Acad::ErrorStatus evaluate(double u, double v, AcGePoint3d& pos, AcGeVector3d& uDeriv, AcGeVector3d& vDeriv) const;
    Acad::ErrorStatus evaluate(double u, double v, AcGePoint3d& pos, AcGeVector3d& uDeriv, AcGeVector3d& vDeriv,
                                AcGeVector3d& uuDeriv, AcGeVector3d& uvDeriv, AcGeVector3d& vvDeriv) const;
    Acad::ErrorStatus evaluate(double u, double v, int derivDegree, AcGePoint3d& point, AcGeVector3dArray& derivatives) const;

    // get degree
    Acad::ErrorStatus getDegreeInU(int& degree) const;
    Acad::ErrorStatus getDegreeInV(int& degree) const;

    // is closed
    Acad::ErrorStatus isClosedInU(bool& isClosed) const;
    Acad::ErrorStatus isClosedInV(bool& isClosed) const;

    // is periodic
    Acad::ErrorStatus isPeriodicInU(bool& isPeriodic) const;
    Acad::ErrorStatus isPeriodicInV(bool& isPeriodic) const;

    // get period
    Acad::ErrorStatus getPeriodInU(double& period) const;
    Acad::ErrorStatus getPeriodInV(double& period) const;

    // test if rational 
    Acad::ErrorStatus isRational(bool& isRational) const;

    // test if planar
    Acad::ErrorStatus isPlanar(bool& isPlanar, AcGePoint3d& ptOnSurface, AcGeVector3d& normal) const;

    // test if a point is on the surface
    Acad::ErrorStatus isPointOnSurface(const AcGePoint3d& point, bool& onSurface) const;

    // get normal
    Acad::ErrorStatus getNormal(double u, double v, AcGeVector3d& normal) const;

    // get the simple patches in u v direction
    Acad::ErrorStatus getNumberOfSpansInU(int& span) const;
    Acad::ErrorStatus getNumberOfSpansInV(int& span) const;

    // get the u and v isolines.
    Acad::ErrorStatus getIsolineAtU(double u, AcArray<AcDbCurve*>& lineSegments) const;
    Acad::ErrorStatus getIsolineAtV(double v, AcArray<AcDbCurve*>& lineSegments) const;

    // knot insertion 
    Acad::ErrorStatus InsertKnotAtU(double u);
    Acad::ErrorStatus InsertKnotAtV(double v);

    // add / remove control points
    Acad::ErrorStatus InsertControlPointsAtU(double u, const AcGePoint3dArray& vCtrlPts, const AcGeDoubleArray& vWeights);
    Acad::ErrorStatus InsertControlPointsAtV(double v, const AcGePoint3dArray& uCtrlPts, const AcGeDoubleArray& uWeights);
    Acad::ErrorStatus RemoveControlPointsAtU(int uIndex);
    Acad::ErrorStatus RemoveControlPointsAtV(int vIndex);

    // rebuild
    Acad::ErrorStatus rebuild(int uDegree, int vDegree, int numUCtrlPts, int numVCtrlPts, bool bRestore = false);

    // adjust a point's location and tangent 
    Acad::ErrorStatus modifyPositionAndTangent(double u, double v, const AcGePoint3d& point,
                                 const AcGeVector3d* uDeriv = NULL, const AcGeVector3d* vDeriv = NULL);

    // get the u and v for a point
    Acad::ErrorStatus getParameterOfPoint(const AcGePoint3d& point, double& u, double& v) const;
   
    // Overridden methods from AcDbEntity
    void              dragStatus         (const AcDb::DragStat status) override;

    
protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

#pragma pack(pop)

