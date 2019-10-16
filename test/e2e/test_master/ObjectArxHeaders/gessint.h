//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GESSINT_H
#  define AC_GESSINT_H
#  include "adesk.h"
#  include "geent3d.h"
#  include "gegbl.h"
#  include "gegblabb.h"
#  pragma  pack (push, 8)
class AcGeCurve3d;
class AcGeCurve2d;
class AcGeSurface;
class GX_DLLEXPIMPORT AcGeSurfSurfInt : public AcGeEntity3d
{
public:
  AcGeSurfSurfInt();
  AcGeSurfSurfInt(const AcGeSurface& srf1, const AcGeSurface& srf2, const AcGeTol& tol = AcGeContext::gTol);
  AcGeSurfSurfInt(const AcGeSurfSurfInt& src);
  const AcGeSurface* surface1() const;
  const AcGeSurface* surface2() const;
  AcGeTol tolerance() const;
  int numResults(AcGe::AcGeIntersectError& err) const;
  AcGeCurve3d* intCurve(int intNum, Adesk::Boolean isExternal, AcGe::AcGeIntersectError& err) const;
  AcGeCurve2d* intParamCurve(int num, Adesk::Boolean isExternal, Adesk::Boolean isFirst, AcGe::AcGeIntersectError& err) const;
  AcGePoint3d intPoint(int intNum, AcGe::AcGeIntersectError& err) const;
  void getIntPointParams(int intNum, AcGePoint2d& param1, AcGePoint2d& param2, AcGe::AcGeIntersectError& err) const;
  void getIntConfigs(int intNum, AcGe::ssiConfig& surf1Left, AcGe::ssiConfig& surf1Right, AcGe::ssiConfig& surf2Left, AcGe::ssiConfig& surf2Right, AcGe::ssiType& intType, int& dim, AcGe::AcGeIntersectError& err) const;
  int getDimension(int intNum, AcGe::AcGeIntersectError& err) const;
  AcGe::ssiType getType(int intNum, AcGe::AcGeIntersectError& err) const;
  AcGeSurfSurfInt& set(const AcGeSurface& srf1, const AcGeSurface& srf2, const AcGeTol& tol = AcGeContext::gTol);
  AcGeSurfSurfInt& operator =(const AcGeSurfSurfInt& crvInt);
};
#  pragma  pack (pop)
#endif
