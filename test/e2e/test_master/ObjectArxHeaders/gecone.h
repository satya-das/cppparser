//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECONE_H
#  define AC_GECONE_H
#  include "gegbl.h"
#  include "geintrvl.h"
#  include "gevec3d.h"
#  include "gesurf.h"
#  include "gearc3d.h"
#  pragma  pack (push, 8)
class AcGePoint3d;
class AcGeVector3d;
class AcGeCircArc3d;
class AcGeInterval;
class AcGeLinearEnt3d;
class GX_DLLEXPIMPORT AcGeCone : public AcGeSurface
{
public:
  AcGeCone();
  AcGeCone(double cosineAngle, double sineAngle, const AcGePoint3d& baseOrigin, double baseRadius, const AcGeVector3d& axisOfSymmetry);
  AcGeCone(double cosineAngle, double sineAngle, const AcGePoint3d& baseOrigin, double baseRadius, const AcGeVector3d& axisOfSymmetry, const AcGeVector3d& refAxis, const AcGeInterval& height, double startAngle, double endAngle);
  AcGeCone(const AcGeCone& cone);
  double baseRadius() const;
  AcGePoint3d baseCenter() const;
  void getAngles(double& start, double& end) const;
  double halfAngle() const;
  void getHalfAngle(double& cosineAngle, double& sineAngle) const;
  void getHeight(AcGeInterval& range) const;
  double heightAt(double u) const;
  AcGeVector3d axisOfSymmetry() const;
  AcGeVector3d refAxis() const;
  AcGePoint3d apex() const;
  Adesk::Boolean isClosed(const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isOuterNormal() const;
  AcGeCone& setBaseRadius(double radius);
  AcGeCone& setAngles(double startAngle, double endAngle);
  AcGeCone& setHeight(const AcGeInterval& height);
  AcGeCone& set(double cosineAngle, double sineAngle, const AcGePoint3d& baseCenter, double baseRadius, const AcGeVector3d& axisOfSymmetry);
  AcGeCone& set(double cosineAngle, double sineAngle, const AcGePoint3d& baseCenter, double baseRadius, const AcGeVector3d& axisOfSymmetry, const AcGeVector3d& refAxis, const AcGeInterval& height, double startAngle, double endAngle);
  AcGeCone& operator =(const AcGeCone& cone);
  Adesk::Boolean intersectWith(const AcGeLinearEnt3d& linEnt, int& intn, AcGePoint3d& p1, AcGePoint3d& p2, const AcGeTol& tol = AcGeContext::gTol) const;
};
#  pragma  pack (pop)
#endif
