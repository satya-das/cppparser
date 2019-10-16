//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GESPHERE_H
#  define AC_GESPHERE_H
#  include "gegbl.h"
#  include "gepnt3d.h"
#  include "gevec3d.h"
#  include "geintrvl.h"
#  include "gesurf.h"
#  pragma  pack (push, 8)
class AcGeCircArc3d;
class GX_DLLEXPIMPORT AcGeSphere : public AcGeSurface
{
public:
  AcGeSphere();
  AcGeSphere(double radius, const AcGePoint3d& center);
  AcGeSphere(double radius, const AcGePoint3d& center, const AcGeVector3d& northAxis, const AcGeVector3d& refAxis, double startAngleU, double endAngleU, double startAngleV, double endAngleV);
  AcGeSphere(const AcGeSphere& sphere);
  double radius() const;
  AcGePoint3d center() const;
  void getAnglesInU(double& start, double& end) const;
  void getAnglesInV(double& start, double& end) const;
  AcGeVector3d northAxis() const;
  AcGeVector3d refAxis() const;
  AcGePoint3d northPole() const;
  AcGePoint3d southPole() const;
  Adesk::Boolean isOuterNormal() const;
  Adesk::Boolean isClosed(const AcGeTol& tol = AcGeContext::gTol) const;
  AcGeSphere& setRadius(double);
  AcGeSphere& setAnglesInU(double start, double end);
  AcGeSphere& setAnglesInV(double start, double end);
  AcGeSphere& set(double radius, const AcGePoint3d& center);
  AcGeSphere& set(double radius, const AcGePoint3d& center, const AcGeVector3d& northAxis, const AcGeVector3d& refAxis, double startAngleU, double endAngleU, double startAngleV, double endAngleV);
  AcGeSphere& operator =(const AcGeSphere& sphere);
  Adesk::Boolean intersectWith(const AcGeLinearEnt3d&, int& intn, AcGePoint3d& p1, AcGePoint3d& p2, const AcGeTol& tol = AcGeContext::gTol) const;
};
#  pragma  pack (pop)
#endif
