//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECSINT_H
#  define AC_GECSINT_H
#  include "adesk.h"
#  include "geent3d.h"
#  include "geponc3d.h"
#  include "geponsrf.h"
#  include "geintrvl.h"
#  include "gegbl.h"
#  include "gegblabb.h"
#  pragma  pack (push, 8)
class AcGeCurve3d;
class AcGeSurface;
class GX_DLLEXPIMPORT AcGeCurveSurfInt : public AcGeEntity3d
{
public:
  AcGeCurveSurfInt();
  AcGeCurveSurfInt(const AcGeCurve3d& crv, const AcGeSurface& srf, const AcGeTol& tol = AcGeContext::gTol);
  AcGeCurveSurfInt(const AcGeCurveSurfInt& src);
  const AcGeCurve3d* curve() const;
  const AcGeSurface* surface() const;
  AcGeTol tolerance() const;
  int numIntPoints(AcGeIntersectError& err) const;
  AcGePoint3d intPoint(int intNum, AcGeIntersectError& err) const;
  void getIntParams(int intNum, double& param1, AcGePoint2d& param2, AcGeIntersectError& err) const;
  void getPointOnCurve(int intNum, AcGePointOnCurve3d&, AcGeIntersectError& err) const;
  void getPointOnSurface(int intNum, AcGePointOnSurface&, AcGeIntersectError& err) const;
  void getIntConfigs(int intNum, AcGe::csiConfig& lower, AcGe::csiConfig& higher, Adesk::Boolean& smallAngle, AcGeIntersectError& err) const;
  AcGeCurveSurfInt& set(const AcGeCurve3d& cvr, const AcGeSurface& srf, const AcGeTol& tol = AcGeContext::gTol);
  AcGeCurveSurfInt& operator =(const AcGeCurveSurfInt& crvInt);
};
#  pragma  pack (pop)
#endif
