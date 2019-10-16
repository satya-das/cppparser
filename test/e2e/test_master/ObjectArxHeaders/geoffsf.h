//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEOFFSF_H
#  define AC_GEOFFSF_H
#  include "gegbl.h"
#  include "gepnt3d.h"
#  include "gesurf.h"
#  pragma  pack (push, 8)
class AcGePlane;
class AcGeBoundedPlane;
class AcGeCylinder;
class AcGeCone;
class AcGeSphere;
class AcGeTorus;
class GX_DLLEXPIMPORT AcGeOffsetSurface : public AcGeSurface
{
public:
  AcGeOffsetSurface();
  AcGeOffsetSurface(AcGeSurface* baseSurface, double offsetDist, Adesk::Boolean makeCopy = Adesk::kTrue);
  AcGeOffsetSurface(const AcGeOffsetSurface& offset);
  Adesk::Boolean isPlane() const;
  Adesk::Boolean isBoundedPlane() const;
  Adesk::Boolean isSphere() const;
  Adesk::Boolean isCylinder() const;
  Adesk::Boolean isCone() const;
  Adesk::Boolean isTorus() const;
  Adesk::Boolean getSurface(AcGeSurface*&) const;
  void getConstructionSurface(AcGeSurface*& base) const;
  double offsetDist() const;
  AcGeOffsetSurface& set(AcGeSurface*, double offsetDist, Adesk::Boolean makeCopy = Adesk::kTrue);
  AcGeOffsetSurface& operator =(const AcGeOffsetSurface& offset);
};
#  pragma  pack (pop)
#endif
