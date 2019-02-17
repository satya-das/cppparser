//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//
// This file contains the class AcGePoint3d - A mathematical entity
// used to represent a location in 3-space using homogeneous
// co-ordinates (implicitly).

#ifndef AC_GEPNT3D_H
#define AC_GEPNT3D_H

#include "gevec3d.h"
#pragma pack (push, 8)

class AcGeMatrix3d;
class AcGeLinearEnt3d;
class AcGePlane;
class AcGePlanarEnt;
class AcGeVector3d;
class AcGePoint2d;

class
AcGePoint3d
{
public:
    GE_DLLEXPIMPORT AcGePoint3d();
    GE_DLLEXPIMPORT AcGePoint3d(const AcGePoint3d& pnt);
    GE_DLLEXPIMPORT AcGePoint3d(double x, double y, double z);
    GE_DLLEXPIMPORT AcGePoint3d(const AcGePlanarEnt& pln, const AcGePoint2d& pnt2d);

    // The origin, or (0, 0, 0).
    //
    GE_DLLDATAEXIMP static const   AcGePoint3d    kOrigin;

    // Matrix multiplication.
    //
    friend GE_DLLEXPIMPORT
    AcGePoint3d    operator *  (const AcGeMatrix3d& mat, const AcGePoint3d& pnt);
    GE_DLLEXPIMPORT AcGePoint3d&   setToProduct(const AcGeMatrix3d& mat, const AcGePoint3d& pnt);

    GE_DLLEXPIMPORT AcGePoint3d&   transformBy (const AcGeMatrix3d& leftSide);
    GE_DLLEXPIMPORT AcGePoint3d&   rotateBy    (double angle, const AcGeVector3d& vec,
                                const AcGePoint3d& wrtPoint = AcGePoint3d::kOrigin);
    GE_DLLEXPIMPORT AcGePoint3d&   mirror      (const AcGePlane& pln);
    GE_DLLEXPIMPORT AcGePoint3d&   scaleBy     (double scaleFactor, const AcGePoint3d&
                                wrtPoint = AcGePoint3d::kOrigin);
    GE_DLLEXPIMPORT AcGePoint2d    convert2d   (const AcGePlanarEnt& pln) const;

    // Scale multiplication.
    //
    GE_DLLEXPIMPORT AcGePoint3d    operator *  (double scl) const;
    GE_DLLEXPIMPORT friend
    AcGePoint3d    operator *  (double scl, const AcGePoint3d& pnt);
    GE_DLLEXPIMPORT AcGePoint3d&   operator *= (double scl);
    GE_DLLEXPIMPORT AcGePoint3d    operator /  (double scl) const;
    GE_DLLEXPIMPORT AcGePoint3d&   operator /= (double scl);

    // Translation by a vector.
    //
    GE_DLLEXPIMPORT AcGePoint3d    operator +  (const AcGeVector3d& vec) const;
    GE_DLLEXPIMPORT AcGePoint3d&   operator += (const AcGeVector3d& vec);
    GE_DLLEXPIMPORT AcGePoint3d    operator -  (const AcGeVector3d& vec) const;
    GE_DLLEXPIMPORT AcGePoint3d&   operator -= (const AcGeVector3d& vec);
    GE_DLLEXPIMPORT AcGePoint3d&   setToSum    (const AcGePoint3d& pnt, const AcGeVector3d& vec);

    // Get the vector between two points.
    //
    GE_DLLEXPIMPORT AcGeVector3d   operator -  (const AcGePoint3d& pnt) const;
    GE_DLLEXPIMPORT AcGeVector3d   asVector    () const;

    // Distance to other geometric objects.
    //
    GE_DLLEXPIMPORT double         distanceTo       (const AcGePoint3d& pnt) const;

    // Projection on plane
    //
    GE_DLLEXPIMPORT AcGePoint3d    project       (const AcGePlane& pln, const AcGeVector3d& vec) const;
    GE_DLLEXPIMPORT AcGePoint3d    orthoProject  (const AcGePlane& pln) const;

    // Tests for equivalence using the Euclidean norm.
    //
    GE_DLLEXPIMPORT bool operator == (const AcGePoint3d& pnt) const;
    GE_DLLEXPIMPORT bool operator != (const AcGePoint3d& pnt) const;
    GE_DLLEXPIMPORT bool isEqualTo   (const AcGePoint3d& pnt,
                      const AcGeTol& tol = AcGeContext::gTol) const;

    // For convenient access to the data.
    //
    GE_DLLEXPIMPORT double         operator [] (unsigned int i) const;
    GE_DLLEXPIMPORT double&        operator [] (unsigned int idx);
    GE_DLLEXPIMPORT AcGePoint3d&   set         (double x, double y, double z);
    GE_DLLEXPIMPORT AcGePoint3d&   set         (const AcGePlanarEnt& pln, const AcGePoint2d& pnt);

    // The co-ordinates of the point.
    //
    double         x, y, z;
};

// Creates a point at the origin.
//
inline
AcGePoint3d::AcGePoint3d() : x(0.0), y(0.0), z(0.0)
{
}

// Creates a point with the same values as `src'.
//
inline
AcGePoint3d::AcGePoint3d(const AcGePoint3d& src) : x(src.x), y(src.y), z(src.z)
{
}

// Creates a point intialized to ( xx, yy, zz ).
//
inline
AcGePoint3d::AcGePoint3d(double xx, double yy, double zz) : x(xx), y(yy), z(zz)
{
}

inline bool
AcGePoint3d::operator == (const AcGePoint3d& p) const
{
    return this->isEqualTo(p);
}

// This operator is the logical negation of the `==' operator.
//
inline bool
AcGePoint3d::operator != (const AcGePoint3d& p) const
{
    return !this->isEqualTo(p);
}

// Returns a point such that each of the coordinates of this point
// have been multiplied by val.
//
inline AcGePoint3d
AcGePoint3d::operator * (double val) const
{
    return AcGePoint3d(x*val, y*val, z*val);
}

// Returns a point such that each of the coordinates of this point
// have been multiplied by val.
//
inline AcGePoint3d
operator * (double val, const AcGePoint3d& p)
{
    return AcGePoint3d(p.x*val, p.y*val, p.z*val);
}

// This is equivalent to the statement `p = p * val;'
// Each coordinate of this point is multiplied by val.
//
inline AcGePoint3d&
AcGePoint3d::operator *= (double val)
{
    x *= val;
    y *= val;
    z *= val;
    return *this;
}

// Returns a point such that each of the coordinates of this point
// have been divided by val.
//
inline AcGePoint3d
AcGePoint3d::operator / (double val) const
{
    return AcGePoint3d (x/val, y/val, z/val);
}

// This is equivalent to the statement `p = p / val;'
// Each coordinate of this point is divided by val.
//
inline AcGePoint3d&
AcGePoint3d::operator /= (double val)
{
    x /= val;
    y /= val;
    z /= val;
    return *this;
}

// Returns a point that is equivalent to the result of translating
// this point by the vector `v'.  (It yields the same result as if
// the vector had been cast to a translation matrix and then
// multiplied with the point.)
//
inline AcGePoint3d
AcGePoint3d::operator + (const AcGeVector3d& v) const
{
    return AcGePoint3d (x + v.x, y + v.y, z + v.z);
}

// This is equivalent to the statement `p = p + v;'
//
inline AcGePoint3d&
AcGePoint3d::operator += (const AcGeVector3d& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

// This is equivalent to the statement `p + (-v);'
//
inline AcGePoint3d
AcGePoint3d::operator - (const AcGeVector3d& v) const
{
    return AcGePoint3d (x - v.x, y - v.y, z - v.z);
}

// This is equivalent to the statement `p = p - v;'
//
inline AcGePoint3d&
AcGePoint3d::operator -= (const AcGeVector3d& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

// This operator returns a vector such that if `v = p1 - p0',
// then, `v' is equivalent to the translation that takes
// `p0' to `p1'.  (This point is `p1').
//
inline AcGeVector3d
AcGePoint3d::operator - (const AcGePoint3d& p) const
{
    return AcGeVector3d (x - p.x, y - p.y, z - p.z);
}

// This operator returns the vector that would have resulted
// from the operation `p1 - AcGePoint3d::kOrigin', which is
// a common operation to perform.
//
inline AcGeVector3d
AcGePoint3d::asVector() const
{
    return AcGeVector3d(x, y, z);
}

// Sets the point to ( xx, yy, zz ).
//
inline AcGePoint3d&
AcGePoint3d::set(double xx, double yy, double zz)
{
    x = xx;
    y = yy;
    z = zz;
    return *this;
}

// Indexes the point as if it were an array.  `x' is index `0',
// `y' is index `1', `z' is index `2'.
//
inline double
AcGePoint3d::operator [] (unsigned int i) const
{
    return *(&x+i);
}

inline double&
AcGePoint3d::operator [] (unsigned int i)
{
    return *(&x+i);
}

#define ADSK_ACGEPOINT3D_DEFINED
#include "acarrayhelper.h"

#pragma pack (pop)
#endif
