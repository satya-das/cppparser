//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECYLNDR_H
#  define AC_GECYLNDR_H
#  include "gegbl.h"
#  include "gesurf.h"
#  include "gevec3d.h"
#  include "geintrvl.h"
#  include "gearc3d.h"
#  pragma  pack (push, 8)
class AcGeCircArc3d;
class GX_DLLEXPIMPORT AcGeCylinder : public AcGeSurface
{
public:
  AcGeCylinder();
  AcGeCylinder(double radius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry);
  AcGeCylinder(double radius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry, const AcGeVector3d& refAxis, const AcGeInterval& height, double startAngle, double endAngle);
  AcGeCylinder(const AcGeCylinder&);
  double radius() const;
  AcGePoint3d origin() const;
  void getAngles(double& start, double& end) const;
  void getHeight(AcGeInterval& height) const;
  double heightAt(double u) const;
  AcGeVector3d axisOfSymmetry() const;
  AcGeVector3d refAxis() const;
  Adesk::Boolean isOuterNormal() const;
  Adesk::Boolean isClosed(const AcGeTol& tol = AcGeContext::gTol) const;
  AcGeCylinder& setRadius(double radius);
  AcGeCylinder& setAngles(double start, double end);
  AcGeCylinder& setHeight(const AcGeInterval& height);
  AcGeCylinder& set(double radius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSym);
  AcGeCylinder& set(double radius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSym, const AcGeVector3d& refAxis, const AcGeInterval& height, double startAngle, double endAngle);
  AcGeCylinder& operator =(const AcGeCylinder& cylinder);
  Adesk::Boolean intersectWith(const AcGeLinearEnt3d& linEnt, int& intn, AcGePoint3d& p1, AcGePoint3d& p2, const AcGeTol& tol = AcGeContext::gTol) const;
};
#  pragma  pack (pop)
#endif
