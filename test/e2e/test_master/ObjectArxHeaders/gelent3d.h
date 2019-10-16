//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GELENT3D_H
#  define AC_GELENT3D_H
#  include "gecurv3d.h"
#  include "gevec3d.h"
#  include "gepnt3d.h"
#  pragma  pack (push, 8)
class AcGeLine3d;
class AcGeCircArc3d;
class AcGePlanarEnt;
class GE_DLLEXPIMPORT AcGeLinearEnt3d : public AcGeCurve3d
{
public:
  Adesk::Boolean intersectWith(const AcGeLinearEnt3d& line, AcGePoint3d& intPt, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean intersectWith(const AcGePlanarEnt& plane, AcGePoint3d& intPnt, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean projIntersectWith(const AcGeLinearEnt3d& line, const AcGeVector3d& projDir, AcGePoint3d& pntOnThisLine, AcGePoint3d& pntOnOtherLine, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean overlap(const AcGeLinearEnt3d& line, AcGeLinearEnt3d*& overlap, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(const AcGePoint3d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(const AcGePoint3d& pnt, double& param, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(double param, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOn(const AcGePlane& plane, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isParallelTo(const AcGeLinearEnt3d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isParallelTo(const AcGePlanarEnt& plane, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isPerpendicularTo(const AcGeLinearEnt3d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isPerpendicularTo(const AcGePlanarEnt& plane, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isColinearTo(const AcGeLinearEnt3d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  void getPerpPlane(const AcGePoint3d& pnt, AcGePlane& plane) const;
  AcGePoint3d pointOnLine() const;
  AcGeVector3d direction() const;
  void getLine(AcGeLine3d&) const;
  AcGeLinearEnt3d& operator =(const AcGeLinearEnt3d& line);
protected:
  AcGeLinearEnt3d();
  AcGeLinearEnt3d(const AcGeLinearEnt3d&);
};
#  pragma  pack (pop)
#endif
