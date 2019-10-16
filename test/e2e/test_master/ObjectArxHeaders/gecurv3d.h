//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECURV3D_H
#  define AC_GECURV3D_H
#  include "adesk.h"
#  include "geent3d.h"
#  include "geponc3d.h"
#  include "gept3dar.h"
#  include "gevc3dar.h"
#  include "gedblar.h"
#  include "gevptar.h"
#  include "geintarr.h"
#  pragma  pack (push, 8)
class AcGeCurve2d;
class AcGeSurface;
class AcGePoint3d;
class AcGePlane;
class AcGeVector3d;
class AcGeLinearEnt3d;
class AcGeLine3d;
class AcGePointOnCurve3d;
class AcGePointOnSurface;
class AcGeInterval;
class AcGeMatrix3d;
class AcGePointOnCurve3dData;
class AcGeBoundBlock3d;
class GE_DLLEXPIMPORT AcGeCurve3d : public AcGeEntity3d
{
public:
  void getInterval(AcGeInterval& intrvl) const;
  void getInterval(AcGeInterval& intrvl, AcGePoint3d& start, AcGePoint3d& end) const;
  AcGeCurve3d& reverseParam();
  AcGeCurve3d& setInterval();
  Adesk::Boolean setInterval(const AcGeInterval& intrvl);
  double distanceTo(const AcGePoint3d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  double distanceTo(const AcGeCurve3d& curve, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGePoint3d closestPointTo(const AcGePoint3d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGePoint3d closestPointTo(const AcGeCurve3d& curve3d, AcGePoint3d& pntOnOtherCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  void getClosestPointTo(const AcGePoint3d& pnt, AcGePointOnCurve3d& pntOnCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  void getClosestPointTo(const AcGeCurve3d& curve3d, AcGePointOnCurve3d& pntOnThisCrv, AcGePointOnCurve3d& pntOnOtherCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGePoint3d projClosestPointTo(const AcGePoint3d& pnt, const AcGeVector3d& projectDirection, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGePoint3d projClosestPointTo(const AcGeCurve3d& curve3d, const AcGeVector3d& projectDirection, AcGePoint3d& pntOnOtherCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  void getProjClosestPointTo(const AcGePoint3d& pnt, const AcGeVector3d& projectDirection, AcGePointOnCurve3d& pntOnCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  void getProjClosestPointTo(const AcGeCurve3d& curve3d, const AcGeVector3d& projectDirection, AcGePointOnCurve3d& pntOnThisCrv, AcGePointOnCurve3d& pntOnOtherCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean getNormalPoint(const AcGePoint3d& pnt, AcGePointOnCurve3d& pntOnCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGeBoundBlock3d boundBlock() const;
  AcGeBoundBlock3d boundBlock(const AcGeInterval& range) const;
  AcGeBoundBlock3d orthoBoundBlock() const;
  AcGeBoundBlock3d orthoBoundBlock(const AcGeInterval& range) const;
  AcGeEntity3d* project(const AcGePlane& projectionPlane, const AcGeVector3d& projectDirection, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGeEntity3d* orthoProject(const AcGePlane& projectionPlane, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(const AcGePoint3d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(const AcGePoint3d& pnt, double& param, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(double param, const AcGeTol& tol = AcGeContext::gTol) const;
  double paramOf(const AcGePoint3d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  void getTrimmedOffset(double distance, const AcGeVector3d& planeNormal, AcGeVoidPointerArray& offsetCurveList, AcGe::OffsetCrvExtType extensionType = AcGe::kFillet, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isClosed(const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isPlanar(AcGePlane& plane, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isLinear(AcGeLine3d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isCoplanarWith(const AcGeCurve3d& curve3d, AcGePlane& plane, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isPeriodic(double& period) const;
  double length(double fromParam, double toParam, double tol = AcGeContext::gTol.equalPoint()) const;
  double paramAtLength(double datumParam, double length, Adesk::Boolean posParamDir = Adesk::kTrue, double tol = AcGeContext::gTol.equalPoint()) const;
  Adesk::Boolean area(double startParam, double endParam, double& value, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isDegenerate(AcGe::EntityId& degenerateType, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isDegenerate(AcGeEntity3d*& pConvertedEntity, const AcGeTol& tol = AcGeContext::gTol) const;
  void getSplitCurves(double param, AcGeCurve3d*& piece1, AcGeCurve3d*& piece2) const;
  Adesk::Boolean explode(AcGeVoidPointerArray& explodedCurves, AcGeIntArray& newExplodedCurves, const AcGeInterval* intrvl = NULL) const;
  void getLocalClosestPoints(const AcGePoint3d& point, AcGePointOnCurve3d& approxPnt, const AcGeInterval* nbhd = 0, const AcGeTol& tol = AcGeContext::gTol) const;
  void getLocalClosestPoints(const AcGeCurve3d& otherCurve, AcGePointOnCurve3d& approxPntOnThisCrv, AcGePointOnCurve3d& approxPntOnOtherCrv, const AcGeInterval* nbhd1 = 0, const AcGeInterval* nbhd2 = 0, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean hasStartPoint(AcGePoint3d& startPnt) const;
  Adesk::Boolean hasEndPoint(AcGePoint3d& endPnt) const;
  AcGePoint3d evalPoint(double param) const;
  AcGePoint3d evalPoint(double param, int numDeriv, AcGeVector3dArray& derivArray) const;
  void getSamplePoints(double fromParam, double toParam, double approxEps, AcGePoint3dArray& pointArray, AcGeDoubleArray& paramArray, bool forceResampling = false) const;
  void getSamplePoints(int numSample, AcGePoint3dArray& pointArray) const;
  void getSamplePoints(int numSample, AcGePoint3dArray& pointArray, AcGeDoubleArray& paramArray) const;
  AcGeCurve3d& operator =(const AcGeCurve3d& curve);
protected:
  AcGeCurve3d();
  AcGeCurve3d(const AcGeCurve3d&);
};
#  pragma  pack (pop)
#endif
