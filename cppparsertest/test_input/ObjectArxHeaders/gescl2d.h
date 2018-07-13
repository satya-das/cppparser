//
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
// This file contains the class AcGeScale2d - a mathematical entity used
// to represent scaling transformations in 2-space.
// Contract:  The scale vector components must never be set to zero
// (or near zero within floating point tolerances).

#ifndef AC_GESCL2D_H
#define AC_GESCL2D_H

#include "adesk.h"
#include "gegbl.h"
#pragma pack (push, 8)

class AcGeMatrix2d;
class AcGeScale3d;

class 
AcGeScale2d
{
public:
    GE_DLLEXPIMPORT AcGeScale2d();
    GE_DLLEXPIMPORT AcGeScale2d(const AcGeScale2d& src);
    GE_DLLEXPIMPORT AcGeScale2d(double factor);
    GE_DLLEXPIMPORT AcGeScale2d(double xFactor, double yFactor);

    // The identity scaling operation.
    //
    GE_DLLDATAEXIMP static const   AcGeScale2d kIdentity;

    // Multiplication.
    //
    GE_DLLEXPIMPORT AcGeScale2d    operator *  (const AcGeScale2d& sclVec) const;
    GE_DLLEXPIMPORT AcGeScale2d&   operator *= (const AcGeScale2d& scl);
    GE_DLLEXPIMPORT AcGeScale2d&   preMultBy   (const AcGeScale2d& leftSide);
    GE_DLLEXPIMPORT AcGeScale2d&   postMultBy  (const AcGeScale2d& rightSide);
    GE_DLLEXPIMPORT AcGeScale2d&   setToProduct(const AcGeScale2d& sclVec1, const AcGeScale2d& sclVec2);
    GE_DLLEXPIMPORT AcGeScale2d    operator *  (double s) const;
    GE_DLLEXPIMPORT AcGeScale2d&   operator *= (double s);
    GE_DLLEXPIMPORT AcGeScale2d&   setToProduct(const AcGeScale2d& sclVec, double s);
    friend GE_DLLEXPIMPORT
    AcGeScale2d    operator *  (double, const AcGeScale2d& scl);

    // Multiplicative inverse.
    //
    GE_DLLEXPIMPORT AcGeScale2d    inverse        () const;
    GE_DLLEXPIMPORT AcGeScale2d&   invert         ();

    GE_DLLEXPIMPORT Adesk::Boolean isProportional(const AcGeTol& tol = AcGeContext::gTol) const;

    // Tests for equivalence using the infinity norm.
    //
    GE_DLLEXPIMPORT bool operator == (const AcGeScale2d& sclVec) const;
    GE_DLLEXPIMPORT bool operator != (const AcGeScale2d& sclVec) const;
    GE_DLLEXPIMPORT bool isEqualTo   (const AcGeScale2d& scaleVec,
                      const AcGeTol& tol = AcGeContext::gTol) const;

     // For convenient access to the data.
    //
    GE_DLLEXPIMPORT double         operator [] (unsigned int i) const;
    GE_DLLEXPIMPORT double&        operator [] (unsigned int i);
    GE_DLLEXPIMPORT AcGeScale2d&   set         (double sc0, double sc1);

    // Conversion to/from matrix form.
    //
    GE_DLLEXPIMPORT operator       AcGeMatrix2d   () const;
    GE_DLLEXPIMPORT void           getMatrix      (AcGeMatrix2d& mat) const;
    GE_DLLEXPIMPORT AcGeScale2d&   extractScale   ( const AcGeMatrix2d& mat );
    GE_DLLEXPIMPORT AcGeScale2d&   removeScale    ( AcGeMatrix2d& mat );

    // Cast up to 3d scale.
    //
    GE_DLLEXPIMPORT operator       AcGeScale3d    () const;

    // The scale components in x and y.
    //
    double         sx, sy;
};

inline double
AcGeScale2d::operator [] (unsigned int i) const
{
    return *(&sx+i);
}

inline double&
AcGeScale2d::operator [] (unsigned int i)
{
    return *(&sx+i);
}

inline bool
AcGeScale2d::operator == (const AcGeScale2d& s) const
{
    return this->isEqualTo(s);
}

// This operator is the logical negation of the `==' operator.
//
inline bool
AcGeScale2d::operator != (const AcGeScale2d& s) const
{
    return !this->isEqualTo(s);
}

#pragma pack (pop)
#endif
