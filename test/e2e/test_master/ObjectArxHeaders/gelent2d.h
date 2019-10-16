//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GELENT2D_H
#  define AC_GELENT2D_H
#  include "gecurv2d.h"
#  include "gepnt2d.h"
#  include "gevec2d.h"
#  pragma  pack (push, 8)
class AcGeCircArc2d;
class GE_DLLEXPIMPORT AcGeLinearEnt2d : public AcGeCurve2d
{
public:
  Adesk::Boolean intersectWith(const AcGeLinearEnt2d& line, AcGePoint2d& intPnt, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean overlap(const AcGeLinearEnt2d& line, AcGeLinearEnt2d*& overlap, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isParallelTo(const AcGeLinearEnt2d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isPerpendicularTo(const AcGeLinearEnt2d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  Adesk::Boolean isColinearTo(const AcGeLinearEnt2d& line, const AcGeTol& tol = AcGeContext::gTol) const;
  void getPerpLine(const AcGePoint2d& pnt, AcGeLine2d& perpLine) const;
  AcGePoint2d pointOnLine() const;
  AcGeVector2d direction() const;
  void getLine(AcGeLine2d& line) const;
  AcGeLinearEnt2d& operator =(const AcGeLinearEnt2d& line);
protected:
  AcGeLinearEnt2d();
  AcGeLinearEnt2d(const AcGeLinearEnt2d&);
};
#  pragma  pack (pop)
#endif
