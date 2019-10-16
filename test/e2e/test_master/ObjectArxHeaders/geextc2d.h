//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEEXTC2D_H
#  define AC_GEEXTC2D_H
#  include "gecurv2d.h"
#  include "gearc2d.h"
#  include "gevec2d.h"
#  include "gepnt2d.h"
#  pragma  pack (push, 8)
class AcGeNurbCurve2d;
class AcGeExternalCurve2d;
class AcGeExternalCurve2d;
class GX_DLLEXPIMPORT AcGeExternalCurve2d : public AcGeCurve2d
{
public:
  AcGeExternalCurve2d();
  AcGeExternalCurve2d(const AcGeExternalCurve2d&);
  AcGeExternalCurve2d(void* curveDef, AcGe::ExternalEntityKind curveKind, Adesk::Boolean makeCopy = Adesk::kTrue);
  Adesk::Boolean isNurbCurve() const;
  Adesk::Boolean isNurbCurve(AcGeNurbCurve2d& nurbCurve) const;
  Adesk::Boolean isDefined() const;
  void getExternalCurve(void*& curveDef) const;
  AcGe::ExternalEntityKind externalCurveKind() const;
  AcGeExternalCurve2d& set(void* curveDef, AcGe::ExternalEntityKind curveKind, Adesk::Boolean makeCopy = Adesk::kTrue);
  AcGeExternalCurve2d& operator =(const AcGeExternalCurve2d& src);
  Adesk::Boolean isOwnerOfCurve() const;
  AcGeExternalCurve2d& setToOwnCurve();
};
#  pragma  pack (pop)
#endif
