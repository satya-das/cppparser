//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "dbsurf.h"
class AcGeKnotVector;
class AcGeNurbSurface;
#pragma  pack(push, 8)
class ACDB_PORT AcDbNurbSurface : public AcDbSurface
{
public:
  AcDbNurbSurface();
  AcDbNurbSurface(int uDegree, int vDegree, bool rational, int uNumControlPoints, int vNumControlPoints, const AcGePoint3dArray& ctrlPts, const AcGeDoubleArray& weights, const AcGeKnotVector& uKnots, const AcGeKnotVector& vKnots);
  virtual ~AcDbNurbSurface();
  ACDB_DECLARE_MEMBERS(AcDbNurbSurface);
    //////////////////////////////////////////////////////////
    // NURBS surface methods
    //////////////////////////////////////////////////////////
  Acad::ErrorStatus get(int& uDegree, int& vDegree, bool& rational, int& uNumControlPoints, int& vNumControlPoints, AcGePoint3dArray& ctrlPts, AcGeDoubleArray& weights, AcGeKnotVector& uKnots, AcGeKnotVector& vKnots) const;
  Acad::ErrorStatus set(int uDegree, int vDegree, bool rational, int uNumControlPoints, int vNumControlPoints, const AcGePoint3dArray& ctrlPts, const AcGeDoubleArray& weights, const AcGeKnotVector& uKnots, const AcGeKnotVector& vKnots);
  Acad::ErrorStatus getControlPoints(int& uCount, int& vCount, AcGePoint3dArray& points) const;
  Acad::ErrorStatus setControlPoints(int uCount, int vCount, const AcGePoint3dArray& points);
  Acad::ErrorStatus getControlPointAt(int uIndex, int vIndex, AcGePoint3d& point) const;
  Acad::ErrorStatus setControlPointAt(int uIndex, int vIndex, const AcGePoint3d& point);
  Acad::ErrorStatus getNumberOfControlPointsInU(int& count) const;
  Acad::ErrorStatus getNumberOfControlPointsInV(int& count) const;
  Acad::ErrorStatus getUKnots(AcGeKnotVector& knots) const;
  Acad::ErrorStatus getVKnots(AcGeKnotVector& knots) const;
  Acad::ErrorStatus getNumberOfKnotsInU(int& count) const;
  Acad::ErrorStatus getNumberOfKnotsInV(int& count) const;
  Acad::ErrorStatus getWeight(int uIndex, int vIndex, double& weight) const;
  Acad::ErrorStatus setWeight(int uIndex, int vIndex, double weight);
  Acad::ErrorStatus evaluate(double u, double v, AcGePoint3d& pos) const;
  Acad::ErrorStatus evaluate(double u, double v, AcGePoint3d& pos, AcGeVector3d& uDeriv, AcGeVector3d& vDeriv) const;
  Acad::ErrorStatus evaluate(double u, double v, AcGePoint3d& pos, AcGeVector3d& uDeriv, AcGeVector3d& vDeriv, AcGeVector3d& uuDeriv, AcGeVector3d& uvDeriv, AcGeVector3d& vvDeriv) const;
  Acad::ErrorStatus evaluate(double u, double v, int derivDegree, AcGePoint3d& point, AcGeVector3dArray& derivatives) const;
  Acad::ErrorStatus getDegreeInU(int& degree) const;
  Acad::ErrorStatus getDegreeInV(int& degree) const;
  Acad::ErrorStatus isClosedInU(bool& isClosed) const;
  Acad::ErrorStatus isClosedInV(bool& isClosed) const;
  Acad::ErrorStatus isPeriodicInU(bool& isPeriodic) const;
  Acad::ErrorStatus isPeriodicInV(bool& isPeriodic) const;
  Acad::ErrorStatus getPeriodInU(double& period) const;
  Acad::ErrorStatus getPeriodInV(double& period) const;
  Acad::ErrorStatus isRational(bool& isRational) const;
  Acad::ErrorStatus isPlanar(bool& isPlanar, AcGePoint3d& ptOnSurface, AcGeVector3d& normal) const;
  Acad::ErrorStatus isPointOnSurface(const AcGePoint3d& point, bool& onSurface) const;
  Acad::ErrorStatus getNormal(double u, double v, AcGeVector3d& normal) const;
  Acad::ErrorStatus getNumberOfSpansInU(int& span) const;
  Acad::ErrorStatus getNumberOfSpansInV(int& span) const;
  Acad::ErrorStatus getIsolineAtU(double u, AcArray<AcDbCurve*>& lineSegments) const;
  Acad::ErrorStatus getIsolineAtV(double v, AcArray<AcDbCurve*>& lineSegments) const;
  Acad::ErrorStatus InsertKnotAtU(double u);
  Acad::ErrorStatus InsertKnotAtV(double v);
  Acad::ErrorStatus InsertControlPointsAtU(double u, const AcGePoint3dArray& vCtrlPts, const AcGeDoubleArray& vWeights);
  Acad::ErrorStatus InsertControlPointsAtV(double v, const AcGePoint3dArray& uCtrlPts, const AcGeDoubleArray& uWeights);
  Acad::ErrorStatus RemoveControlPointsAtU(int uIndex);
  Acad::ErrorStatus RemoveControlPointsAtV(int vIndex);
  Acad::ErrorStatus rebuild(int uDegree, int vDegree, int numUCtrlPts, int numVCtrlPts, bool bRestore = false);
  Acad::ErrorStatus modifyPositionAndTangent(double u, double v, const AcGePoint3d& point, const AcGeVector3d* uDeriv = NULL, const AcGeVector3d* vDeriv = NULL);
  Acad::ErrorStatus getParameterOfPoint(const AcGePoint3d& point, double& u, double& v) const;
  void dragStatus(const AcDb::DragStat status) override;
protected:
  virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
#pragma  pack(pop)
