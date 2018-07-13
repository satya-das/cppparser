//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// This file contains the class AcGeScale3d - a mathematical entity used to
// represents scaling transformations in 3-space.
// Contract:  The scale vector components must never be set to zero
// (or near zero within floating point tolerances).

#ifndef AC_GESCL3D_H
#define AC_GESCL3D_H

#include "adesk.h"
#include "gegbl.h"
#pragma pack (push, 8)

class AcGeMatrix3d;

class 
AcGeScale3d
{
public:
    GE_DLLEXPIMPORT AcGeScale3d();
    GE_DLLEXPIMPORT AcGeScale3d(const AcGeScale3d& src);
    GE_DLLEXPIMPORT AcGeScale3d(double factor);
    GE_DLLEXPIMPORT AcGeScale3d(double xFact, double yFact, double zFact);

    // The identity scaling operation.
    //
    GE_DLLDATAEXIMP static const   AcGeScale3d kIdentity;

    // Multiplication.
    //
    GE_DLLEXPIMPORT AcGeScale3d    operator *  (const AcGeScale3d& sclVec) const;
    GE_DLLEXPIMPORT AcGeScale3d&   operator *= (const AcGeScale3d& scl);
    GE_DLLEXPIMPORT AcGeScale3d&   preMultBy   (const AcGeScale3d& leftSide);
    GE_DLLEXPIMPORT AcGeScale3d&   postMultBy  (const AcGeScale3d& rightSide);
    GE_DLLEXPIMPORT AcGeScale3d&   setToProduct(const AcGeScale3d& sclVec1, const AcGeScale3d& sclVec2);
    GE_DLLEXPIMPORT AcGeScale3d    operator *  (double s) const;
    GE_DLLEXPIMPORT AcGeScale3d&   operator *= (double s);
    GE_DLLEXPIMPORT AcGeScale3d&   setToProduct(const AcGeScale3d& sclVec, double s);
    friend GE_DLLEXPIMPORT
    AcGeScale3d    operator *  (double, const AcGeScale3d& scl);

    // Multiplicative inverse.
    //
    GE_DLLEXPIMPORT AcGeScale3d    inverse        () const;
    GE_DLLEXPIMPORT AcGeScale3d&   invert         ();

    GE_DLLEXPIMPORT Adesk::Boolean isProportional(const AcGeTol& tol = AcGeContext::gTol) const;

    // Tests for equivalence using the infinity norm.
    //
    GE_DLLEXPIMPORT bool operator == (const AcGeScale3d& sclVec) const;
    GE_DLLEXPIMPORT bool operator != (const AcGeScale3d& sclVec) const;
    GE_DLLEXPIMPORT bool isEqualTo   (const AcGeScale3d& scaleVec,
                      const AcGeTol& tol = AcGeContext::gTol) const;

    // For convenient access to the data.
    //
    GE_DLLEXPIMPORT double         operator [] (unsigned int i) const;
    GE_DLLEXPIMPORT double&        operator [] (unsigned int i);
    GE_DLLEXPIMPORT AcGeScale3d&   set         (double sc0, double sc1, double sc2);

    // Conversion to/from matrix form.
    //
    GE_DLLEXPIMPORT operator       AcGeMatrix3d   () const;
    GE_DLLEXPIMPORT void getMatrix(AcGeMatrix3d& mat) const;
    GE_DLLEXPIMPORT AcGeScale3d&   extractScale   ( const AcGeMatrix3d& mat );
    GE_DLLEXPIMPORT AcGeScale3d&   removeScale    ( AcGeMatrix3d& mat );

    // The scale components in x, y and z.
    //
    double         sx, sy, sz;
};

inline bool
AcGeScale3d::operator == (const AcGeScale3d& s) const
{
    return this->isEqualTo(s);
}

// This operator is the logical negation of the `==' operator.
//
inline bool
AcGeScale3d::operator != (const AcGeScale3d& s) const
{
    return !(this->isEqualTo(s));
}

// Indexes the scale vector as if it were an array.  `sx' is index `0',
// `sy' is index `1' and `sz' is index `2'.
//
inline double
AcGeScale3d::operator [] (unsigned int i) const
{
    return *(&sx+i);
}

inline double&
AcGeScale3d::operator [] (unsigned int i)
{
    return *(&sx+i);
}

#pragma pack (pop)
#endif
