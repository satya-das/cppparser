//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEARC2D_H
#  define AC_GEARC2D_H
#  include "gecurv2d.h"
#  include "gepnt2d.h"
#  include "gevec2d.h"
#  pragma  pack (push, 8)
class AcGeLine2d;
class AcGeLinearEnt2d;
class GE_DLLEXPIMPORT AcGeCircArc2d : public AcGeCurve2d
{
public:
  AcGeCircArc2d();
  AcGeCircArc2d(const AcGeCircArc2d& arc);
  AcGeCircArc2d(const AcGePoint2d& cent, double radius);
  AcGeCircArc2d(const AcGePoint2d& cent, double radius, double startAngle, double endAngle, const AcGeVector2d& refVec = AcGeVector2d::kXAxis, Adesk::Boolean isClockWise = Adesk::kFalse);
  AcGeCircArc2d(const AcGePoint2d& startPoint, const AcGePoint2d& point, const AcGePoint2d& endPoint);
  AcGeCircArc2d(const AcGePoint2d& startPoint, const AcGePoint2d& endPoint, double bulge, Adesk::Boolean bulgeFlag = Adesk::kTrue);
  Adesk::Boolean intersectWith(const AcGeLinearEnt2d& line, int& intn, AcGePoint2d& p1, AcGePoint2d& p2, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean intersectWith(const AcGeCircArc2d& arc, int& intn, AcGePoint2d& p1, AcGePoint2d& p2, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean tangent(const AcGePoint2d& pnt, AcGeLine2d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean tangent(const AcGePoint2d& pnt, AcGeLine2d& line, const AcGeTol& tol, AcGeError& error) const;
  Adesk::Boolean isInside(const AcGePoint2d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  AcGePoint2d center() const;
  double radius() const;
  double startAng() const;
  double endAng() const;
  Adesk::Boolean isClockWise() const;
  AcGeVector2d refVec() const;
  AcGePoint2d startPoint() const;
  AcGePoint2d endPoint() const;
  AcGeCircArc2d& setCenter(const AcGePoint2d& cent);
  AcGeCircArc2d& setRadius(double radius);
  AcGeCircArc2d& setAngles(double startAng, double endAng);
  AcGeCircArc2d& setToComplement();
  AcGeCircArc2d& setRefVec(const AcGeVector2d& vec);
  AcGeCircArc2d& set(const AcGePoint2d& cent, double radius);
  AcGeCircArc2d& set(const AcGePoint2d& cent, double radius, double ang1, double ang2, const AcGeVector2d& refVec = AcGeVector2d::kXAxis, Adesk::Boolean isClockWise = Adesk::kFalse);
  AcGeCircArc2d& set(const AcGePoint2d& startPoint, const AcGePoint2d& pnt, const AcGePoint2d& endPoint);
  AcGeCircArc2d& set(const AcGePoint2d& startPoint, const AcGePoint2d& pnt, const AcGePoint2d& endPoint, AcGeError& error);
  AcGeCircArc2d& set(const AcGePoint2d& startPoint, const AcGePoint2d& endPoint, double bulge, Adesk::Boolean bulgeFlag = Adesk::kTrue);
  AcGeCircArc2d& set(const AcGeCurve2d& curve1, const AcGeCurve2d& curve2, double radius, double& param1, double& param2, Adesk::Boolean& success);
  AcGeCircArc2d& set(const AcGeCurve2d& curve1, const AcGeCurve2d& curve2, const AcGeCurve2d& curve3, double& param1, double& param2, double& param3, Adesk::Boolean& success);
  AcGeCircArc2d& operator =(const AcGeCircArc2d& arc);
};
#  pragma  pack (pop)
#endif
