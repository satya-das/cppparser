//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GETOL_H
#  define AC_GETOL_H
#  ifndef unix
#    include <stdlib.h>
#  endif
#  include "gedll.h"
#  include "gedblar.h"
#  pragma  pack (push, 8)
class GE_DLLEXPIMPORT AcGeTol
{
public:
  AcGeTol();
  double equalPoint() const;
  double equalVector() const;
  void setEqualPoint(double val);
  void setEqualVector(double val);
private:
  double mTolArr[5];
  int mAbs;
  friend class AcGeTolA;
};
inline void AcGeTol::setEqualVector(double val)
{
  mTolArr[1] = val;
}
inline double AcGeTol::equalVector() const
{
  return mTolArr[1];
}
inline void AcGeTol::setEqualPoint(double val)
{
  mTolArr[0] = val;
}
inline double AcGeTol::equalPoint() const
{
  return mTolArr[0];
}
#  pragma  pack (pop)
#endif
