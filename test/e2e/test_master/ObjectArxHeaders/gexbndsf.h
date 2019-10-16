//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEXBNDSF_H
#  define AC_GEXBNDSF_H
#  include "gegbl.h"
#  include "gesurf.h"
#  pragma  pack (push, 8)
class AcGeExternalSurface;
class AcGeCurveBoundary;
class GX_DLLEXPIMPORT AcGeExternalBoundedSurface : public AcGeSurface
{
public:
  AcGeExternalBoundedSurface();
  AcGeExternalBoundedSurface(void* surfaceDef, AcGe::ExternalEntityKind surfaceKind, Adesk::Boolean makeCopy = Adesk::kTrue);
  AcGeExternalBoundedSurface(const AcGeExternalBoundedSurface&);
  AcGe::ExternalEntityKind externalSurfaceKind() const;
  Adesk::Boolean isDefined() const;
  void getExternalSurface(void*& surfaceDef) const;
  void getBaseSurface(AcGeSurface*& surfaceDef) const;
  void getBaseSurface(AcGeExternalSurface& unboundedSurfaceDef) const;
  Adesk::Boolean isPlane() const;
  Adesk::Boolean isSphere() const;
  Adesk::Boolean isCylinder() const;
  Adesk::Boolean isCone() const;
  Adesk::Boolean isTorus() const;
  Adesk::Boolean isNurbs() const;
  Adesk::Boolean isExternalSurface() const;
  int numContours() const;
  void getContours(int& numContours, AcGeCurveBoundary*& curveBoundaries) const;
  AcGeExternalBoundedSurface& set(void* surfaceDef, AcGe::ExternalEntityKind surfaceKind, Adesk::Boolean makeCopy = Adesk::kTrue);
  AcGeExternalBoundedSurface& operator =(const AcGeExternalBoundedSurface&);
  Adesk::Boolean isOwnerOfSurface() const;
  AcGeExternalBoundedSurface& setToOwnSurface();
};
#  pragma  pack (pop)
#endif
