//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEOFFC3D_H
#  define AC_GEOFFC3D_H
#  include "gecurv3d.h"
#  pragma  pack (push, 8)
class GE_DLLEXPIMPORT AcGeOffsetCurve3d : public AcGeCurve3d
{
public:
  AcGeOffsetCurve3d(const AcGeCurve3d& baseCurve, const AcGeVector3d& planeNormal, double offsetDistance);
  AcGeOffsetCurve3d(const AcGeOffsetCurve3d& offsetCurve);
  const AcGeCurve3d* curve() const;
  AcGeVector3d normal() const;
  double offsetDistance() const;
  Adesk::Boolean paramDirection() const;
  AcGeMatrix3d transformation() const;
  AcGeOffsetCurve3d& setCurve(const AcGeCurve3d& baseCurve);
  AcGeOffsetCurve3d& setNormal(const AcGeVector3d& planeNormal);
  AcGeOffsetCurve3d& setOffsetDistance(double offsetDistance);
  AcGeOffsetCurve3d& operator =(const AcGeOffsetCurve3d& offsetCurve);
};
#  pragma  pack (pop)
#endif
