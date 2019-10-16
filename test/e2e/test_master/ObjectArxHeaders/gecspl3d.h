//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECSPL3D_H
#  define AC_GECSPL3D_H
class AcGePointOnCurve3d;
class AcGeCurve3dIntersection;
class AcGeInterval;
class AcGePlane;
#  include "gesent3d.h"
#  include "gept3dar.h"
#  include "gevc3dar.h"
#  include "gevec3d.h"
#  include "gekvec.h"
#  pragma  pack (push, 8)
class GE_DLLEXPIMPORT AcGeCubicSplineCurve3d : public AcGeSplineEnt3d
{
public:
  AcGeCubicSplineCurve3d();
  AcGeCubicSplineCurve3d(const AcGeCubicSplineCurve3d& spline);
  AcGeCubicSplineCurve3d(const AcGePoint3dArray& fitPnts, const AcGeTol& tol = AcGeContext::gTol);
  AcGeCubicSplineCurve3d(const AcGePoint3dArray& fitPnts, const AcGeVector3d& startDeriv, const AcGeVector3d& endDeriv, const AcGeTol& tol = AcGeContext::gTol);
  AcGeCubicSplineCurve3d(const AcGeCurve3d& curve, double epsilon = AcGeContext::gTol.equalPoint());
  AcGeCubicSplineCurve3d(const AcGeKnotVector& knots, const AcGePoint3dArray& fitPnts, const AcGeVector3dArray& firstDerivs, Adesk::Boolean isPeriodic = Adesk::kFalse);
  int numFitPoints() const;
  AcGePoint3d fitPointAt(int idx) const;
  AcGeCubicSplineCurve3d& setFitPointAt(int idx, const AcGePoint3d& point);
  AcGeVector3d firstDerivAt(int idx) const;
  AcGeCubicSplineCurve3d& setFirstDerivAt(int idx, const AcGeVector3d& deriv);
  AcGeCubicSplineCurve3d& operator =(const AcGeCubicSplineCurve3d& spline);
};
#  pragma  pack (pop)
#endif
