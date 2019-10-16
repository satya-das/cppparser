//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEVEC2D_H
#  define AC_GEVEC2D_H
#  include "adesk.h"
#  include "gegbl.h"
#  include "gegblabb.h"
#  pragma  pack (push, 8)
class AcGeMatrix2d;
class AcGeVector2d
{
public:
  GE_DLLEXPIMPORT AcGeVector2d();
  GE_DLLEXPIMPORT AcGeVector2d(const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGeVector2d(double x, double y);
  GE_DLLDATAEXIMP static const AcGeVector2d kIdentity;
  GE_DLLDATAEXIMP static const AcGeVector2d kXAxis;
  GE_DLLDATAEXIMP static const AcGeVector2d kYAxis;
  GE_DLLEXPIMPORT friend AcGeVector2d operator *(const AcGeMatrix2d& mat, const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGeVector2d& setToProduct(const AcGeMatrix2d& mat, const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGeVector2d& transformBy(const AcGeMatrix2d& leftSide);
  GE_DLLEXPIMPORT AcGeVector2d& rotateBy(double angle);
  GE_DLLEXPIMPORT AcGeVector2d& mirror(const AcGeVector2d& line);
  GE_DLLEXPIMPORT AcGeVector2d operator *(double scl) const;
  GE_DLLEXPIMPORT friend AcGeVector2d operator *(double scl, const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGeVector2d& operator *=(double scl);
  GE_DLLEXPIMPORT AcGeVector2d& setToProduct(const AcGeVector2d& vec, double scl);
  GE_DLLEXPIMPORT AcGeVector2d operator /(double scl) const;
  GE_DLLEXPIMPORT AcGeVector2d& operator /=(double scl);
  GE_DLLEXPIMPORT AcGeVector2d operator +(const AcGeVector2d& vec) const;
  GE_DLLEXPIMPORT AcGeVector2d& operator +=(const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGeVector2d operator -(const AcGeVector2d& vec) const;
  GE_DLLEXPIMPORT AcGeVector2d& operator -=(const AcGeVector2d& vec);
  GE_DLLEXPIMPORT AcGeVector2d& setToSum(const AcGeVector2d& vec1, const AcGeVector2d& vec2);
  GE_DLLEXPIMPORT AcGeVector2d operator -() const;
  GE_DLLEXPIMPORT AcGeVector2d& negate();
  GE_DLLEXPIMPORT AcGeVector2d perpVector() const;
  GE_DLLEXPIMPORT double angle() const;
  GE_DLLEXPIMPORT double angleTo(const AcGeVector2d& vec) const;
  GE_DLLEXPIMPORT AcGeVector2d normal(const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT AcGeVector2d& normalize(const AcGeTol& tol = AcGeContext::gTol);
  GE_DLLEXPIMPORT AcGeVector2d& normalize(const AcGeTol& tol, AcGeError& flag);
  GE_DLLEXPIMPORT double length() const;
  GE_DLLEXPIMPORT double lengthSqrd() const;
  GE_DLLEXPIMPORT Adesk::Boolean isUnitLength(const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isZeroLength(const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isParallelTo(const AcGeVector2d& vec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isParallelTo(const AcGeVector2d& vec, const AcGeTol& tol, AcGeError& flag) const;
  GE_DLLEXPIMPORT Adesk::Boolean isCodirectionalTo(const AcGeVector2d& vec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isCodirectionalTo(const AcGeVector2d& vec, const AcGeTol& tol, AcGeError& flag) const;
  GE_DLLEXPIMPORT Adesk::Boolean isPerpendicularTo(const AcGeVector2d& vec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isPerpendicularTo(const AcGeVector2d& vec, const AcGeTol& tol, AcGeError& flag) const;
  GE_DLLEXPIMPORT double dotProduct(const AcGeVector2d& vec) const;
  GE_DLLEXPIMPORT bool operator ==(const AcGeVector2d& vec) const;
  GE_DLLEXPIMPORT bool operator !=(const AcGeVector2d& vec) const;
  GE_DLLEXPIMPORT bool isEqualTo(const AcGeVector2d& vec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT double operator [](unsigned int i) const;
  GE_DLLEXPIMPORT double& operator [](unsigned int i);
  GE_DLLEXPIMPORT AcGeVector2d& set(double x, double y);
  operator AcGeMatrix2d() const;
  double x, y;
};
inline AcGeVector2d::AcGeVector2d()
  : x(0.0)
  , y(0.0)
{
}
inline AcGeVector2d::AcGeVector2d(const AcGeVector2d& src)
  : x(src.x)
  , y(src.y)
{
}
inline AcGeVector2d::AcGeVector2d(double xx, double yy)
  : x(xx)
  , y(yy)
{
}
inline bool AcGeVector2d::operator ==(const AcGeVector2d& v) const
{
  return this->isEqualTo(v);
}
inline bool AcGeVector2d::operator !=(const AcGeVector2d& v) const
{
  return !this->isEqualTo(v);
}
inline AcGeVector2d AcGeVector2d::operator *(double s) const
{
  return AcGeVector2d(x * s, y * s);
}
inline AcGeVector2d& AcGeVector2d::operator *=(double s)
{
  x *= s;
  y *= s;
  return *this;
}
inline AcGeVector2d& AcGeVector2d::setToProduct(const AcGeVector2d& v, double s)
{
  x = s * v.x;
  y = s * v.y;
  return *this;
}
inline AcGeVector2d AcGeVector2d::operator /(double val) const
{
  return AcGeVector2d(x / val, y / val);
}
inline AcGeVector2d& AcGeVector2d::operator /=(double val)
{
  x /= val;
  y /= val;
  return *this;
}
inline AcGeVector2d AcGeVector2d::operator +(const AcGeVector2d& v) const
{
  return AcGeVector2d(x + v.x, y + v.y);
}
inline AcGeVector2d& AcGeVector2d::operator +=(const AcGeVector2d& v)
{
  x += v.x;
  y += v.y;
  return *this;
}
inline AcGeVector2d AcGeVector2d::operator -(const AcGeVector2d& v) const
{
  return AcGeVector2d(x - v.x, y - v.y);
}
inline AcGeVector2d& AcGeVector2d::operator -=(const AcGeVector2d& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}
inline AcGeVector2d& AcGeVector2d::setToSum(const AcGeVector2d& v1, const AcGeVector2d& v2)
{
  x = v1.x + v2.x;
  y = v1.y + v2.y;
  return *this;
}
inline AcGeVector2d AcGeVector2d::operator -() const
{
  return AcGeVector2d(-x, -y);
}
inline AcGeVector2d& AcGeVector2d::negate()
{
  x = -x;
  y = -y;
  return *this;
}
inline AcGeVector2d AcGeVector2d::perpVector() const
{
  return AcGeVector2d(-y, x);
}
inline double AcGeVector2d::lengthSqrd() const
{
  return x * x + y * y;
}
inline double AcGeVector2d::dotProduct(const AcGeVector2d& v) const
{
  return x * v.x + y * v.y;
}
inline AcGeVector2d& AcGeVector2d::set(double xx, double yy)
{
  x = xx;
  y = yy;
  return *this;
}
inline double AcGeVector2d::operator [](unsigned int i) const
{
  return *(&x + i);
}
inline double& AcGeVector2d::operator [](unsigned int i)
{
  return *(&x + i);
}
#  define ADSK_ACGEVECTOR2D_DEFINED
#  include "acarrayhelper.h"
#  pragma  pack (pop)
#endif
