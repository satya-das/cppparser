//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GETORUS_H
#  define AC_GETORUS_H
#  include "gegbl.h"
#  include "gesurf.h"
#  include "geintrvl.h"
#  include "gevec3d.h"
#  pragma  pack (push, 8)
class AcGeCircArc3d;
class GX_DLLEXPIMPORT AcGeTorus : public AcGeSurface
{
public:
  AcGeTorus();
  AcGeTorus(double majorRadius, double minorRadius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry);
  AcGeTorus(double majorRadius, double minorRadius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry, const AcGeVector3d& refAxis, double startAngleU, double endAngleU, double startAngleV, double endAngleV);
  AcGeTorus(const AcGeTorus& torus);
  double majorRadius() const;
  double minorRadius() const;
  void getAnglesInU(double& start, double& end) const;
  void getAnglesInV(double& start, double& end) const;
  AcGePoint3d center() const;
  AcGeVector3d axisOfSymmetry() const;
  AcGeVector3d refAxis() const;
  Adesk::Boolean isOuterNormal() const;
  AcGeTorus& setMajorRadius(double radius);
  AcGeTorus& setMinorRadius(double radius);
  AcGeTorus& setAnglesInU(double start, double end);
  AcGeTorus& setAnglesInV(double start, double end);
  AcGeTorus& set(double majorRadius, double minorRadius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry);
  AcGeTorus& set(double majorRadius, double minorRadius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry, const AcGeVector3d& refAxis, double startAngleU, double endAngleU, double startAngleV, double endAngleV);
  AcGeTorus& operator =(const AcGeTorus& torus);
  Adesk::Boolean intersectWith(const AcGeLinearEnt3d& linEnt, int& intn, AcGePoint3d& p1, AcGePoint3d& p2, AcGePoint3d& p3, AcGePoint3d& p4, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isLemon() const;
  Adesk::Boolean isApple() const;
  Adesk::Boolean isVortex() const;
  Adesk::Boolean isDoughnut() const;
  Adesk::Boolean isDegenerate() const;
  Adesk::Boolean isHollow() const;
};
#  pragma  pack (pop)
#endif
