//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECBNDRY_H
#  define AC_GECBNDRY_H
#  include "gegbl.h"
#  pragma  pack (push, 8)
class AcGeCurve2d;
class AcGeEntity3d;
class AcGePosition3d;
class AcGeImpCurveBoundary;
class GX_DLLEXPIMPORT AcGeCurveBoundary
{
public:
  AcGeCurveBoundary();
  AcGeCurveBoundary(int numberOfCurves, const AcGeEntity3d* const * crv3d, const AcGeCurve2d* const * crv2d, Adesk::Boolean* orientation3d, Adesk::Boolean* orientation2d, Adesk::Boolean makeCopy = Adesk::kTrue);
  AcGeCurveBoundary(const AcGeCurveBoundary&);
  ~AcGeCurveBoundary();
  AcGeCurveBoundary& operator =(const AcGeCurveBoundary& src);
  Adesk::Boolean isDegenerate() const;
  Adesk::Boolean isDegenerate(AcGePosition3d& degenPoint, AcGeCurve2d** paramCurve) const;
  int numElements() const;
  void getContour(int& n, AcGeEntity3d*** crv3d, AcGeCurve2d*** paramGeometry, Adesk::Boolean** orientation3d, Adesk::Boolean** orientation2d) const;
  AcGeCurveBoundary& set(int numElements, const AcGeEntity3d* const * crv3d, const AcGeCurve2d* const * crv2d, Adesk::Boolean* orientation3d, Adesk::Boolean* orientation2d, Adesk::Boolean makeCopy = Adesk::kTrue);
  Adesk::Boolean isOwnerOfCurves() const;
  AcGeCurveBoundary& setToOwnCurves();
protected:
  friend class AcGeImpCurveBoundary;
  AcGeImpCurveBoundary* mpImpBnd;
  int mDelBnd;
};
#  pragma  pack (pop)
#endif
