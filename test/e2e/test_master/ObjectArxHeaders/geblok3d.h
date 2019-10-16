//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEBLOCK3D_H
#  define AC_GEBLOCK3D_H
#  include "geent3d.h"
#  pragma  pack (push, 8)
class AcGePoint3d;
class AcGeVector3d;
class GE_DLLEXPIMPORT AcGeBoundBlock3d : public AcGeEntity3d
{
public:
  AcGeBoundBlock3d();
  AcGeBoundBlock3d(const AcGePoint3d& base, const AcGeVector3d& dir1, const AcGeVector3d& dir2, const AcGeVector3d& dir3);
  AcGeBoundBlock3d(const AcGeBoundBlock3d& block);
  void getMinMaxPoints(AcGePoint3d& point1, AcGePoint3d& point2) const;
  void get(AcGePoint3d& base, AcGeVector3d& dir1, AcGeVector3d& dir2, AcGeVector3d& dir3) const;
  AcGeBoundBlock3d& set(const AcGePoint3d& point1, const AcGePoint3d& point2);
  AcGeBoundBlock3d& set(const AcGePoint3d& base, const AcGeVector3d& dir1, const AcGeVector3d& dir2, const AcGeVector3d& dir3);
  AcGeBoundBlock3d& extend(const AcGePoint3d& point);
  AcGeBoundBlock3d& swell(double distance);
  Adesk::Boolean contains(const AcGePoint3d& point) const;
  Adesk::Boolean isDisjoint(const AcGeBoundBlock3d& block) const;
  AcGeBoundBlock3d& operator =(const AcGeBoundBlock3d& block);
  Adesk::Boolean isBox() const;
  AcGeBoundBlock3d& setToBox(Adesk::Boolean);
};
#  pragma  pack (pop)
#endif
