//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEELL3D_H
#  define AC_GEELL3D_H
#  include "gecurv3d.h"
#  include "gevec3d.h"
#  include "gepnt3d.h"
#  include "geintrvl.h"
#  include "geponc3d.h"
#  include "geplane.h"
#  pragma  pack (push, 8)
class AcGeEllipArc2d;
class AcGeCircArc3d;
class AcGeLineEnt3d;
class AcGePlanarEnt;
class GE_DLLEXPIMPORT AcGeEllipArc3d : public AcGeCurve3d
{
public:
  AcGeEllipArc3d();
  AcGeEllipArc3d(const AcGeEllipArc3d& ell);
  AcGeEllipArc3d(const AcGeCircArc3d& arc);
  AcGeEllipArc3d(const AcGePoint3d& cent, const AcGeVector3d& majorAxis, const AcGeVector3d& minorAxis, double majorRadius, double minorRadius);
  AcGeEllipArc3d(const AcGePoint3d& cent, const AcGeVector3d& majorAxis, const AcGeVector3d& minorAxis, double majorRadius, double minorRadius, double ang1, double ang2);
  AcGePoint3d closestPointToPlane(const AcGePlanarEnt& plane, AcGePoint3d& pointOnPlane, const AcGeTol& = AcGeContext::gTol) const;
  Adesk::Boolean intersectWith(const AcGeLinearEnt3d& line, int& intn, AcGePoint3d& p1, AcGePoint3d& p2, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean intersectWith(const AcGePlanarEnt& plane, int& numOfIntersect, AcGePoint3d& p1, AcGePoint3d& p2, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean projIntersectWith(const AcGeLinearEnt3d& line, const AcGeVector3d& projDir, int& numInt, AcGePoint3d& pntOnEllipse1, AcGePoint3d& pntOnEllipse2, AcGePoint3d& pntOnLine1, AcGePoint3d& pntOnLine2, const AcGeTol& tol = AcGeContext::gTol) const;
  void getPlane(AcGePlane& plane) const;
  Adesk::Boolean isCircular(const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isInside(const AcGePoint3d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGePoint3d center() const;
  double minorRadius() const;
  double majorRadius() const;
  AcGeVector3d minorAxis() const;
  AcGeVector3d majorAxis() const;
  AcGeVector3d normal() const;
  double startAng() const;
  double endAng() const;
  AcGePoint3d startPoint() const;
  AcGePoint3d endPoint() const;
  AcGeEllipArc3d& setCenter(const AcGePoint3d& cent);
  AcGeEllipArc3d& setMinorRadius(double rad);
  AcGeEllipArc3d& setMajorRadius(double rad);
  AcGeEllipArc3d& setAxes(const AcGeVector3d& majorAxis, const AcGeVector3d& minorAxis);
  AcGeEllipArc3d& setAngles(double startAngle, double endAngle);
  AcGeEllipArc3d& set(const AcGePoint3d& cent, const AcGeVector3d& majorAxis, const AcGeVector3d& minorAxis, double majorRadius, double minorRadius);
  AcGeEllipArc3d& set(const AcGePoint3d& cent, const AcGeVector3d& majorAxis, const AcGeVector3d& minorAxis, double majorRadius, double minorRadius, double startAngle, double endAngle);
  AcGeEllipArc3d& set(const AcGeCircArc3d&);
  AcGeEllipArc3d& operator =(const AcGeEllipArc3d& ell);
};
#  pragma  pack (pop)
#endif
