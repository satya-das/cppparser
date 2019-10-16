//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEPONC3D_H
#  define AC_GEPONC3D_H
#  include "gepent3d.h"
#  pragma  pack (push, 8)
class AcGeCurve3d;
class GE_DLLEXPIMPORT AcGePointOnCurve3d : public AcGePointEnt3d
{
public:
  AcGePointOnCurve3d();
  AcGePointOnCurve3d(const AcGeCurve3d& crv);
  AcGePointOnCurve3d(const AcGeCurve3d& crv, double param);
  AcGePointOnCurve3d(const AcGePointOnCurve3d& src);
  AcGePointOnCurve3d& operator =(const AcGePointOnCurve3d& src);
  const AcGeCurve3d* curve() const;
  double parameter() const;
  AcGePoint3d point() const;
  AcGePoint3d point(double param);
  AcGePoint3d point(const AcGeCurve3d& crv, double param);
  AcGeVector3d deriv(int order) const;
  AcGeVector3d deriv(int order, double param);
  AcGeVector3d deriv(int order, const AcGeCurve3d& crv, double param);
  Adesk::Boolean isSingular(const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean curvature(double& res);
  Adesk::Boolean curvature(double param, double& res);
  AcGePointOnCurve3d& setCurve(const AcGeCurve3d& crv);
  AcGePointOnCurve3d& setParameter(double param);
};
#  pragma  pack (pop)
#endif
