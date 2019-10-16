//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECOMP3D_H
#  define AC_GECOMP3D_H
#  include "gecurv3d.h"
#  include "gevptar.h"
#  include "geintarr.h"
#  pragma  pack (push, 8)
class GE_DLLEXPIMPORT AcGeCompositeCurve3d : public AcGeCurve3d
{
public:
  AcGeCompositeCurve3d();
  AcGeCompositeCurve3d(const AcGeVoidPointerArray& curveList);
  AcGeCompositeCurve3d(const AcGeVoidPointerArray& curveList, const AcGeIntArray& isOwnerOfCurves);
  AcGeCompositeCurve3d(const AcGeCompositeCurve3d& compCurve);
  void getCurveList(AcGeVoidPointerArray& curveList) const;
  AcGeCompositeCurve3d& setCurveList(const AcGeVoidPointerArray& curveList);
  AcGeCompositeCurve3d& setCurveList(const AcGeVoidPointerArray& curveList, const AcGeIntArray& isOwnerOfCurves);
  double globalToLocalParam(double param, int& segNum) const;
  double localToGlobalParam(double param, int segNum) const;
  AcGeCompositeCurve3d& operator =(const AcGeCompositeCurve3d& compCurve);
};
#  pragma  pack (pop)
#endif
