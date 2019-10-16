//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEEXTSF_H
#  define AC_GEEXTSF_H
#  include "gegbl.h"
#  include "gesurf.h"
#  pragma  pack (push, 8)
class AcGePlane;
class AcGeCylinder;
class AcGeCone;
class AcGeSphere;
class AcGeTorus;
class AcGeNurbSurface;
class surface;
class GX_DLLEXPIMPORT AcGeExternalSurface : public AcGeSurface
{
public:
  AcGeExternalSurface();
  AcGeExternalSurface(void* surfaceDef, AcGe::ExternalEntityKind surfaceKind, Adesk::Boolean makeCopy = Adesk::kTrue);
  AcGeExternalSurface(const AcGeExternalSurface&);
  void getExternalSurface(void*& surfaceDef) const;
  AcGe::ExternalEntityKind externalSurfaceKind() const;
  Adesk::Boolean isPlane() const;
  Adesk::Boolean isSphere() const;
  Adesk::Boolean isCylinder() const;
  Adesk::Boolean isCone() const;
  Adesk::Boolean isTorus() const;
  Adesk::Boolean isNurbSurface() const;
  Adesk::Boolean isDefined() const;
  Adesk::Boolean isNativeSurface(AcGeSurface*& nativeSurface) const;
  AcGeExternalSurface& operator =(const AcGeExternalSurface& src);
  AcGeExternalSurface& set(void* surfaceDef, AcGe::ExternalEntityKind surfaceKind, Adesk::Boolean makeCopy = Adesk::kTrue);
  Adesk::Boolean isOwnerOfSurface() const;
  AcGeExternalSurface& setToOwnSurface();
};
#  pragma  pack (pop)
#endif
