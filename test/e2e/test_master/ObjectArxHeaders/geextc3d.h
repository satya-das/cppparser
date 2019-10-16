//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEEXTC3D_H
#  define AC_GEEXTC3D_H
#  include "gecurv3d.h"
#  include "gearc3d.h"
#  include "gevec3d.h"
#  include "gepnt3d.h"
#  pragma  pack (push, 8)
class AcGeLine3d;
class AcGeLineSeg3d;
class AcGeRay3d;
class AcGeEllipArc3d;
class AcGeNurbCurve3d;
class AcGeExternalCurve2d;
class AcGeExternalCurve3d;
class GX_DLLEXPIMPORT AcGeExternalCurve3d : public AcGeCurve3d
{
public:
  AcGeExternalCurve3d();
  AcGeExternalCurve3d(const AcGeExternalCurve3d& src);
  AcGeExternalCurve3d(void* curveDef, AcGe::ExternalEntityKind curveKind, Adesk::Boolean makeCopy = Adesk::kTrue);
  Adesk::Boolean isLine() const;
  Adesk::Boolean isRay() const;
  Adesk::Boolean isLineSeg() const;
  Adesk::Boolean isCircArc() const;
  Adesk::Boolean isEllipArc() const;
  Adesk::Boolean isNurbCurve() const;
  Adesk::Boolean isDefined() const;
  Adesk::Boolean isNativeCurve(AcGeCurve3d*& nativeCurve) const;
  void getExternalCurve(void*& curveDef) const;
  AcGe::ExternalEntityKind externalCurveKind() const;
  AcGeExternalCurve3d& set(void* curveDef, AcGe::ExternalEntityKind curveKind, Adesk::Boolean makeCopy = Adesk::kTrue);
  AcGeExternalCurve3d& operator =(const AcGeExternalCurve3d& src);
  Adesk::Boolean isOwnerOfCurve() const;
  AcGeExternalCurve3d& setToOwnCurve();
};
#  pragma  pack (pop)
#endif
