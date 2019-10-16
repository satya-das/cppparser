//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEPENT2D_H
#  define AC_GEPENT2D_H
#  include "adesk.h"
#  include "geent2d.h"
#  include "gepnt2d.h"
#  pragma  pack (push, 8)
class GE_DLLEXPIMPORT AcGePointEnt2d : public AcGeEntity2d
{
public:
  AcGePoint2d point2d() const;
  operator AcGePoint2d() const;
  AcGePointEnt2d& operator =(const AcGePointEnt2d& pnt);
protected:
  AcGePointEnt2d();
  AcGePointEnt2d(const AcGePointEnt2d&);
};
#  pragma  pack (pop)
#endif
