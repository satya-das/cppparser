//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GESCL3D_H
#  define AC_GESCL3D_H
#  include "adesk.h"
#  include "gegbl.h"
#  pragma  pack (push, 8)
class AcGeMatrix3d;
class AcGeScale3d
{
public:
  GE_DLLEXPIMPORT AcGeScale3d();
  GE_DLLEXPIMPORT AcGeScale3d(const AcGeScale3d& src);
  GE_DLLEXPIMPORT AcGeScale3d(double factor);
  GE_DLLEXPIMPORT AcGeScale3d(double xFact, double yFact, double zFact);
  GE_DLLDATAEXIMP static const AcGeScale3d kIdentity;
  GE_DLLEXPIMPORT AcGeScale3d operator *(const AcGeScale3d& sclVec) const;
  GE_DLLEXPIMPORT AcGeScale3d& operator *=(const AcGeScale3d& scl);
  GE_DLLEXPIMPORT AcGeScale3d& preMultBy(const AcGeScale3d& leftSide);
  GE_DLLEXPIMPORT AcGeScale3d& postMultBy(const AcGeScale3d& rightSide);
  GE_DLLEXPIMPORT AcGeScale3d& setToProduct(const AcGeScale3d& sclVec1, const AcGeScale3d& sclVec2);
  GE_DLLEXPIMPORT AcGeScale3d operator *(double s) const;
  GE_DLLEXPIMPORT AcGeScale3d& operator *=(double s);
  GE_DLLEXPIMPORT AcGeScale3d& setToProduct(const AcGeScale3d& sclVec, double s);
  GE_DLLEXPIMPORT friend AcGeScale3d operator *(double, const AcGeScale3d& scl);
  GE_DLLEXPIMPORT AcGeScale3d inverse() const;
  GE_DLLEXPIMPORT AcGeScale3d& invert();
  GE_DLLEXPIMPORT Adesk::Boolean isProportional(const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT bool operator ==(const AcGeScale3d& sclVec) const;
  GE_DLLEXPIMPORT bool operator !=(const AcGeScale3d& sclVec) const;
  GE_DLLEXPIMPORT bool isEqualTo(const AcGeScale3d& scaleVec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT double operator [](unsigned int i) const;
  GE_DLLEXPIMPORT double& operator [](unsigned int i);
  GE_DLLEXPIMPORT AcGeScale3d& set(double sc0, double sc1, double sc2);
  operator AcGeMatrix3d() const;
  GE_DLLEXPIMPORT void getMatrix(AcGeMatrix3d& mat) const;
  GE_DLLEXPIMPORT AcGeScale3d& extractScale(const AcGeMatrix3d& mat);
  GE_DLLEXPIMPORT AcGeScale3d& removeScale(AcGeMatrix3d& mat);
  double sx, sy, sz;
};
inline bool AcGeScale3d::operator ==(const AcGeScale3d& s) const
{
  return this->isEqualTo(s);
}
inline bool AcGeScale3d::operator !=(const AcGeScale3d& s) const
{
  return !(this->isEqualTo(s));
}
inline double AcGeScale3d::operator [](unsigned int i) const
{
  return *(&sx + i);
}
inline double& AcGeScale3d::operator [](unsigned int i)
{
  return *(&sx + i);
}
#  pragma  pack (pop)
#endif
