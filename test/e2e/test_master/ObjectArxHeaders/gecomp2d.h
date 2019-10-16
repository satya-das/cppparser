//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECOMP2D_H
#  define AC_GECOMP2D_H
#  include "gecurv2d.h"
#  include "gevptar.h"
#  include "geintarr.h"
#  pragma  pack (push, 8)
class GE_DLLEXPIMPORT AcGeCompositeCurve2d : public AcGeCurve2d
{
public:
  AcGeCompositeCurve2d();
  AcGeCompositeCurve2d(const AcGeVoidPointerArray& curveList);
  AcGeCompositeCurve2d(const AcGeVoidPointerArray& curveList, const AcGeIntArray& isOwnerOfCurves);
  AcGeCompositeCurve2d(const AcGeCompositeCurve2d& compCurve);
  void getCurveList(AcGeVoidPointerArray& curveList) const;
  AcGeCompositeCurve2d& setCurveList(const AcGeVoidPointerArray& curveList);
  AcGeCompositeCurve2d& setCurveList(const AcGeVoidPointerArray& curveList, const AcGeIntArray& isOwnerOfCurves);
  double globalToLocalParam(double param, int& crvNum) const;
  double localToGlobalParam(double param, int crvNum) const;
  AcGeCompositeCurve2d& operator =(const AcGeCompositeCurve2d& compCurve);
};
#  pragma  pack (pop)
#endif
