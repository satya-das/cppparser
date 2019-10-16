//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEVEC3D_H
#  define AC_GEVEC3D_H
#  include "adesk.h"
#  include "gegbl.h"
#  include "gegblabb.h"
#  pragma  pack (push, 8)
class AcGeMatrix3d;
class AcGeVector2d;
class AcGePlane;
class AcGePlanarEnt;
class AcGeVector3d
{
public:
  GE_DLLEXPIMPORT AcGeVector3d();
  GE_DLLEXPIMPORT AcGeVector3d(const AcGeVector3d& vec);
  GE_DLLEXPIMPORT AcGeVector3d(double x, double y, double z);
  GE_DLLEXPIMPORT AcGeVector3d(const AcGePlanarEnt&, const AcGeVector2d&);
  GE_DLLDATAEXIMP static const AcGeVector3d kIdentity;
  GE_DLLDATAEXIMP static const AcGeVector3d kXAxis;
  GE_DLLDATAEXIMP static const AcGeVector3d kYAxis;
  GE_DLLDATAEXIMP static const AcGeVector3d kZAxis;
  GE_DLLEXPIMPORT friend AcGeVector3d operator *(const AcGeMatrix3d& mat, const AcGeVector3d& vec);
  GE_DLLEXPIMPORT AcGeVector3d& setToProduct(const AcGeMatrix3d& mat, const AcGeVector3d& vec);
  GE_DLLEXPIMPORT AcGeVector3d& transformBy(const AcGeMatrix3d& leftSide);
  GE_DLLEXPIMPORT AcGeVector3d& rotateBy(double ang, const AcGeVector3d& axis);
  GE_DLLEXPIMPORT AcGeVector3d& mirror(const AcGeVector3d& normalToPlane);
  GE_DLLEXPIMPORT AcGeVector2d convert2d(const AcGePlanarEnt& pln) const;
  GE_DLLEXPIMPORT AcGeVector3d operator *(double scl) const;
  GE_DLLEXPIMPORT friend AcGeVector3d operator *(double scl, const AcGeVector3d& vec);
  GE_DLLEXPIMPORT AcGeVector3d& operator *=(double scl);
  GE_DLLEXPIMPORT AcGeVector3d& setToProduct(const AcGeVector3d& vec, double scl);
  GE_DLLEXPIMPORT AcGeVector3d operator /(double scl) const;
  GE_DLLEXPIMPORT AcGeVector3d& operator /=(double scl);
  GE_DLLEXPIMPORT AcGeVector3d operator +(const AcGeVector3d& vec) const;
  GE_DLLEXPIMPORT AcGeVector3d& operator +=(const AcGeVector3d& vec);
  GE_DLLEXPIMPORT AcGeVector3d operator -(const AcGeVector3d& vec) const;
  GE_DLLEXPIMPORT AcGeVector3d& operator -=(const AcGeVector3d& vec);
  GE_DLLEXPIMPORT AcGeVector3d& setToSum(const AcGeVector3d& vec1, const AcGeVector3d& vec2);
  GE_DLLEXPIMPORT AcGeVector3d operator -() const;
  GE_DLLEXPIMPORT AcGeVector3d& negate();
  GE_DLLEXPIMPORT AcGeVector3d perpVector() const;
  GE_DLLEXPIMPORT double angleTo(const AcGeVector3d& vec) const;
  GE_DLLEXPIMPORT double angleTo(const AcGeVector3d& vec, const AcGeVector3d& refVec) const;
  GE_DLLEXPIMPORT double angleOnPlane(const AcGePlanarEnt& pln) const;
  GE_DLLEXPIMPORT AcGeVector3d normal(const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT AcGeVector3d& normalize(const AcGeTol& tol = AcGeContext::gTol);
  GE_DLLEXPIMPORT AcGeVector3d& normalize(const AcGeTol& tol, AcGeError& flag);
  GE_DLLEXPIMPORT double length() const;
  GE_DLLEXPIMPORT double lengthSqrd() const;
  GE_DLLEXPIMPORT Adesk::Boolean isUnitLength(const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isZeroLength(const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isParallelTo(const AcGeVector3d& vec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isParallelTo(const AcGeVector3d& vec, const AcGeTol& tol, AcGeError& flag) const;
  GE_DLLEXPIMPORT Adesk::Boolean isCodirectionalTo(const AcGeVector3d& vec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isCodirectionalTo(const AcGeVector3d& vec, const AcGeTol& tol, AcGeError& flag) const;
  GE_DLLEXPIMPORT Adesk::Boolean isPerpendicularTo(const AcGeVector3d& vec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT Adesk::Boolean isPerpendicularTo(const AcGeVector3d& vec, const AcGeTol& tol, AcGeError& flag) const;
  GE_DLLEXPIMPORT double dotProduct(const AcGeVector3d& vec) const;
  GE_DLLEXPIMPORT AcGeVector3d crossProduct(const AcGeVector3d& vec) const;
  GE_DLLEXPIMPORT AcGeMatrix3d rotateTo(const AcGeVector3d& vec, const AcGeVector3d& axis = AcGeVector3d::kIdentity) const;
  GE_DLLEXPIMPORT AcGeVector3d project(const AcGeVector3d& planeNormal, const AcGeVector3d& projectDirection) const;
  GE_DLLEXPIMPORT AcGeVector3d project(const AcGeVector3d& planeNormal, const AcGeVector3d& projectDirection, const AcGeTol& tol, AcGeError& flag) const;
  GE_DLLEXPIMPORT AcGeVector3d orthoProject(const AcGeVector3d& planeNormal) const;
  GE_DLLEXPIMPORT AcGeVector3d orthoProject(const AcGeVector3d& planeNormal, const AcGeTol& tol, AcGeError& flag) const;
  GE_DLLEXPIMPORT bool operator ==(const AcGeVector3d& vec) const;
  GE_DLLEXPIMPORT bool operator !=(const AcGeVector3d& vec) const;
  GE_DLLEXPIMPORT bool isEqualTo(const AcGeVector3d& vec, const AcGeTol& tol = AcGeContext::gTol) const;
  GE_DLLEXPIMPORT double operator [](unsigned int i) const;
  GE_DLLEXPIMPORT double& operator [](unsigned int i);
  GE_DLLEXPIMPORT unsigned int largestElement() const;
  GE_DLLEXPIMPORT AcGeVector3d& set(double x, double y, double z);
  GE_DLLEXPIMPORT AcGeVector3d& set(const AcGePlanarEnt& pln, const AcGeVector2d& vec);
  operator AcGeMatrix3d() const;
  double x, y, z;
};
inline AcGeVector3d::AcGeVector3d()
  : x(0.0)
  , y(0.0)
  , z(0.0)
{
}
inline AcGeVector3d::AcGeVector3d(const AcGeVector3d& src)
  : x(src.x)
  , y(src.y)
  , z(src.z)
{
}
inline AcGeVector3d::AcGeVector3d(double xx, double yy, double zz)
  : x(xx)
  , y(yy)
  , z(zz)
{
}
inline bool AcGeVector3d::operator ==(const AcGeVector3d& v) const
{
  return this->isEqualTo(v);
}
inline bool AcGeVector3d::operator !=(const AcGeVector3d& v) const
{
  return !this->isEqualTo(v);
}
inline AcGeVector3d AcGeVector3d::operator +(const AcGeVector3d& v) const
{
  return AcGeVector3d(x + v.x, y + v.y, z + v.z);
}
inline AcGeVector3d& AcGeVector3d::operator +=(const AcGeVector3d& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}
inline AcGeVector3d AcGeVector3d::operator -(const AcGeVector3d& v) const
{
  return AcGeVector3d(x - v.x, y - v.y, z - v.z);
}
inline AcGeVector3d& AcGeVector3d::operator -=(const AcGeVector3d& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}
inline AcGeVector3d& AcGeVector3d::setToSum(const AcGeVector3d& v1, const AcGeVector3d& v2)
{
  x = v1.x + v2.x;
  y = v1.y + v2.y;
  z = v1.z + v2.z;
  return *this;
}
inline AcGeVector3d AcGeVector3d::operator -() const
{
  return AcGeVector3d(-x, -y, -z);
}
inline AcGeVector3d& AcGeVector3d::negate()
{
  x = -x;
  y = -y;
  z = -z;
  return *this;
}
inline AcGeVector3d AcGeVector3d::operator *(double s) const
{
  return AcGeVector3d(x * s, y * s, z * s);
}
inline AcGeVector3d& AcGeVector3d::operator *=(double s)
{
  x *= s;
  y *= s;
  z *= s;
  return *this;
}
inline AcGeVector3d& AcGeVector3d::setToProduct(const AcGeVector3d& v, double s)
{
  x = s * v.x;
  y = s * v.y;
  z = s * v.z;
  return *this;
}
inline AcGeVector3d AcGeVector3d::operator /(double val) const
{
  return AcGeVector3d(x / val, y / val, z / val);
}
inline AcGeVector3d& AcGeVector3d::operator /=(double val)
{
  x /= val;
  y /= val;
  z /= val;
  return *this;
}
inline double AcGeVector3d::lengthSqrd() const
{
  return x * x + y * y + z * z;
}
inline double AcGeVector3d::dotProduct(const AcGeVector3d& v) const
{
  return x * v.x + y * v.y + z * v.z;
}
inline AcGeVector3d& AcGeVector3d::set(double xx, double yy, double zz)
{
  x = xx;
  y = yy;
  z = zz;
  return *this;
}
inline double AcGeVector3d::operator [](unsigned int i) const
{
  return *(&x + i);
}
inline double& AcGeVector3d::operator [](unsigned int i)
{
  return *(&x + i);
}
#  define ADSK_ACGEVECTOR3D_DEFINED
#  include "acarrayhelper.h"
#  pragma  pack (pop)
#endif
