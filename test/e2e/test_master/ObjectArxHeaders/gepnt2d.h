//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEPNT2D_H
#  define AC_GEPNT2D_H
#  include "gevec2d.h"
#  pragma  pack (push, 8)
class AcGeMatrix2d;
class AcGeVector2d;
class AcGeLinearEnt2d;
class AcGeLine2d;
class AcGePoint2d
{
public:
  GE_DLLEXPIMPORT AcGePoint2d();
  GE_DLLEXPIMPORT AcGePoint2d(const AcGePoint2d& pnt);
  GE_DLLEXPIMPORT AcGePoint2d(double x, double y);
  GE_DLLDATAEXIMP static const AcGePoint2d kOrigin;
  GE_DLLEXPIMPORT friend AcGePoint2d operator *(const AcGeMatrix2d& mat, const AcGePoint2d& pnt);
  GE_DLLEXPIMPORT AcGePoint2d& setToProduct(const AcGeMatrix2d& mat, const AcGePoint2d& pnt);
  GE_DLLEXPIMPORT AcGePoint2d& transformBy(const AcGeMatrix2d& leftSide);
  GE_DLLEXPIMPORT AcGePoint2d& rotateBy(double angle, const AcGePoint2d& wrtPoint = AcGePoint2d::kOrigin);
  GE_DLLEXPIMPORT AcGePoint2d& mirror(const AcGeLine2d& line);
  GE_DLLEXPIMPORT AcGePoint2d& scaleBy(double scaleFactor, const AcGePoint2d& wrtPoint = AcGePoint2d::kOrigin);
  GE_DLLEXPIMPORT AcGePoint2d operator *(double) const;
  GE_DLLEXPIMPORT friend AcGePoint2d operator *(double, const AcGePoint2d& scl);
  GE_DLLEXPIMPORT AcGePoint2d& operator *=(double scl);
  GE_DLLEXPIMPORT AcGePoint2d operator /(double scl) const;
  GE_DLLEXPIMPORT AcGePoint2d& operator /=(double scl);
  GE_DLLEXPIMPORT AcGePoint2d operator +(const AcGeVector2d& vec) const;
  GE_DLLEXPIMPORT AcGePoint2d& operator +=(const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGePoint2d operator -(const AcGeVector2d& vec) const;
  GE_DLLEXPIMPORT AcGePoint2d& operator -=(const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGePoint2d& setToSum(const AcGePoint2d& pnt, const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGeVector2d operator -(const AcGePoint2d& pnt) const;
  GE_DLLEXPIMPORT AcGeVector2d asVector() const;
  GE_DLLEXPIMPORT double distanceTo(const AcGePoint2d& pnt) const;
  GE_DLLEXPIMPORT bool operator ==(const AcGePoint2d& pnt) const;
  GE_DLLEXPIMPORT bool operator !=(const AcGePoint2d& pnt) const;
  GE_DLLEXPIMPORT bool isEqualTo(const AcGePoint2d& pnt, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT double operator [](unsigned int i) const;
  GE_DLLEXPIMPORT double& operator [](unsigned int idx);
  GE_DLLEXPIMPORT AcGePoint2d& set(double x, double y);
  double x, y;
};
inline AcGePoint2d::AcGePoint2d()
  : x(0.0)
  , y(0.0)
{
}
inline AcGePoint2d::AcGePoint2d(const AcGePoint2d& src)
  : x(src.x)
  , y(src.y)
{
}
inline AcGePoint2d::AcGePoint2d(double xx, double yy)
  : x(xx)
  , y(yy)
{
}
inline bool AcGePoint2d::operator ==(const AcGePoint2d& p) const
{
  return this->isEqualTo(p);
}
inline bool AcGePoint2d::operator !=(const AcGePoint2d& p) const
{
  return !this->isEqualTo(p);
}
inline AcGePoint2d AcGePoint2d::operator *(double val) const
{
  return AcGePoint2d(x * val, y * val);
}
inline AcGePoint2d operator *(double val, const AcGePoint2d& p)
{
  return AcGePoint2d(p.x * val, p.y * val);
}
inline AcGePoint2d& AcGePoint2d::operator *=(double val)
{
  x *= val;
  y *= val;
  return *this;
}
inline AcGePoint2d AcGePoint2d::operator /(double val) const
{
  return AcGePoint2d(x / val, y / val);
}
inline AcGePoint2d& AcGePoint2d::operator /=(double val)
{
  x /= val;
  y /= val;
  return *this;
}
inline AcGePoint2d AcGePoint2d::operator +(const AcGeVector2d& v) const
{
  return AcGePoint2d(x + v.x, y + v.y);
}
inline AcGePoint2d& AcGePoint2d::operator +=(const AcGeVector2d& v)
{
  x += v.x;
  y += v.y;
  return *this;
}
inline AcGePoint2d AcGePoint2d::operator -(const AcGeVector2d& v) const
{
  return AcGePoint2d(x - v.x, y - v.y);
}
inline AcGePoint2d& AcGePoint2d::operator -=(const AcGeVector2d& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}
inline AcGeVector2d AcGePoint2d::operator -(const AcGePoint2d& p) const
{
  return AcGeVector2d(x - p.x, y - p.y);
}
inline AcGeVector2d AcGePoint2d::asVector() const
{
  return AcGeVector2d(x, y);
}
inline AcGePoint2d& AcGePoint2d::set(double xx, double yy)
{
  x = xx;
  y = yy;
  return *this;
}
inline double AcGePoint2d::operator [](unsigned int i) const
{
  return *(&x + i);
}
inline double& AcGePoint2d::operator [](unsigned int i)
{
  return *(&x + i);
}
#  define ADSK_ACGEPOINT2D_DEFINED
#  include "acarrayhelper.h"
#  pragma  pack (pop)
#endif
