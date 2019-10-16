//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECURV2D_H
#  define AC_GECURV2D_H
#  include "adesk.h"
#  include "geent2d.h"
#  include "geponc2d.h"
#  include "gept2dar.h"
#  include "gevc2dar.h"
#  include "gedblar.h"
#  include "gevptar.h"
#  include "geintarr.h"
#  pragma  pack (push, 8)
class AcGePoint2d;
class AcGeVector2d;
class AcGePointOnCurve2d;
class AcGeInterval;
class AcGeMatrix2d;
class AcGeLine2d;
class AcGePointOnCurve2dData;
class AcGeBoundBlock2d;
class GE_DLLEXPIMPORT AcGeCurve2d : public AcGeEntity2d
{
public:
  void getInterval(AcGeInterval& intrvl) const;
  void getInterval(AcGeInterval& intrvl, AcGePoint2d& start, AcGePoint2d& end) const;
  AcGeCurve2d& reverseParam();
  AcGeCurve2d& setInterval();
  Adesk::Boolean setInterval(const AcGeInterval& intrvl);
  double distanceTo(const AcGePoint2d& pnt, const AcGeTol& = AcGeContext::gTol) const;
  double distanceTo(const AcGeCurve2d&, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGePoint2d closestPointTo(const AcGePoint2d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGePoint2d closestPointTo(const AcGeCurve2d& curve2d, AcGePoint2d& pntOnOtherCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  void getClosestPointTo(const AcGePoint2d& pnt, AcGePointOnCurve2d& pntOnCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  void getClosestPointTo(const AcGeCurve2d& curve2d, AcGePointOnCurve2d& pntOnThisCrv, AcGePointOnCurve2d& pntOnOtherCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean getNormalPoint(const AcGePoint2d& pnt, AcGePointOnCurve2d& pntOnCrv, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(const AcGePoint2d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(const AcGePoint2d& pnt, double& param, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(double param, const AcGeTol& tol = AcGeContext::gTol) const;
  double paramOf(const AcGePoint2d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  void getTrimmedOffset(double distance, AcGeVoidPointerArray& offsetCurveList, AcGe::OffsetCrvExtType extensionType = AcGe::kFillet, const AcGeTol& = AcGeContext::gTol) const;
  Adesk::Boolean isClosed(const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isPeriodic(double& period) const;
  Adesk::Boolean isLinear(AcGeLine2d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  double length(double fromParam, double toParam, double tol = AcGeContext::gTol.equalPoint()) const;
  double paramAtLength(double datumParam, double length, Adesk::Boolean posParamDir = Adesk::kTrue, double tol = AcGeContext::gTol.equalPoint()) const;
  Adesk::Boolean area(double startParam, double endParam, double& value, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isDegenerate(AcGe::EntityId& degenerateType, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isDegenerate(AcGeEntity2d*& pConvertedEntity, const AcGeTol& tol = AcGeContext::gTol) const;
  void getSplitCurves(double param, AcGeCurve2d*& piece1, AcGeCurve2d*& piece2) const;
  Adesk::Boolean explode(AcGeVoidPointerArray& explodedCurves, AcGeIntArray& newExplodedCurve, const AcGeInterval* intrvl = NULL) const;
  void getLocalClosestPoints(const AcGePoint2d& point, AcGePointOnCurve2d& approxPnt, const AcGeInterval* nbhd = 0, const AcGeTol& = AcGeContext::gTol) const;
  void getLocalClosestPoints(const AcGeCurve2d& otherCurve, AcGePointOnCurve2d& approxPntOnThisCrv, AcGePointOnCurve2d& approxPntOnOtherCrv, const AcGeInterval* nbhd1 = 0, const AcGeInterval* nbhd2 = 0, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGeBoundBlock2d boundBlock() const;
  AcGeBoundBlock2d boundBlock(const AcGeInterval& range) const;
  AcGeBoundBlock2d orthoBoundBlock() const;
  AcGeBoundBlock2d orthoBoundBlock(const AcGeInterval& range) const;
  Adesk::Boolean hasStartPoint(AcGePoint2d& startPoint) const;
  Adesk::Boolean hasEndPoint(AcGePoint2d& endPoint) const;
  AcGePoint2d evalPoint(double param) const;
  AcGePoint2d evalPoint(double param, int numDeriv, AcGeVector2dArray& derivArray) const;
  void getSamplePoints(double fromParam, double toParam, double approxEps, AcGePoint2dArray& pointArray, AcGeDoubleArray& paramArray) const;
  void getSamplePoints(int numSample, AcGePoint2dArray&) const;
  AcGeCurve2d& operator =(const AcGeCurve2d& curve);
protected:
  AcGeCurve2d();
  AcGeCurve2d(const AcGeCurve2d&);
};
#  pragma  pack (pop)
#endif
