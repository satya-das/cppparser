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
// This file contains the class AcGeMatrix2d - a matrix used to
// represent general purpose 2d transformations in homogeneous
// co-ordinate space.

#ifndef AC_GEMAT2D_H
#define AC_GEMAT2D_H

#include "gegbl.h"
#include "gepnt2d.h"
#pragma pack (push, 8)

class AcGeVector2d;
class AcGeLine2d;
class AcGeTol;

class 
AcGeMatrix2d
{
public:
    GE_DLLEXPIMPORT AcGeMatrix2d();
    GE_DLLEXPIMPORT AcGeMatrix2d(const AcGeMatrix2d& src);

    // The multiplicative identity.
    //
    GE_DLLDATAEXIMP static const   AcGeMatrix2d   kIdentity;

    // Reset matrix.
    //
    GE_DLLEXPIMPORT AcGeMatrix2d&  setToIdentity();

    // Multiplication.
    //
    GE_DLLEXPIMPORT AcGeMatrix2d   operator *   (const AcGeMatrix2d& mat) const;
    GE_DLLEXPIMPORT AcGeMatrix2d&  operator *=  (const AcGeMatrix2d& mat);
    GE_DLLEXPIMPORT AcGeMatrix2d&  preMultBy    (const AcGeMatrix2d& leftSide);
    GE_DLLEXPIMPORT AcGeMatrix2d&  postMultBy   (const AcGeMatrix2d& rightSide);
    GE_DLLEXPIMPORT AcGeMatrix2d&  setToProduct (const AcGeMatrix2d& mat1, const AcGeMatrix2d& mat2);

    // Multiplicative inverse.
    //
    GE_DLLEXPIMPORT AcGeMatrix2d&  invert       ();
    GE_DLLEXPIMPORT AcGeMatrix2d   inverse      () const;

    // Test if it is a singular matrix. A singular matrix is not invertable.
    //
    GE_DLLEXPIMPORT Adesk::Boolean isSingular   (const AcGeTol& tol = AcGeContext::gTol) const;

    // Matrix transposition.
    //
    GE_DLLEXPIMPORT AcGeMatrix2d&  transposeIt  ();
    GE_DLLEXPIMPORT AcGeMatrix2d   transpose    () const;

    // Tests for equivalence using the infinity norm.
    //
    GE_DLLEXPIMPORT bool operator ==  (const AcGeMatrix2d& mat) const;
    GE_DLLEXPIMPORT bool operator !=  (const AcGeMatrix2d& mat) const;
    GE_DLLEXPIMPORT bool isEqualTo    (const AcGeMatrix2d& mat,
                       const AcGeTol& tol = AcGeContext::gTol) const;

    // Test scaling effects of matrix
    //
    GE_DLLEXPIMPORT Adesk::Boolean isUniScaledOrtho(const AcGeTol& tol = AcGeContext::gTol) const;
    GE_DLLEXPIMPORT Adesk::Boolean isScaledOrtho(const AcGeTol& tol = AcGeContext::gTol) const;
    GE_DLLEXPIMPORT double		   scale(void);

    // Determinant
    //
    GE_DLLEXPIMPORT double         det          () const;

    // Set/retrieve translation.
    //
    GE_DLLEXPIMPORT AcGeMatrix2d&  setTranslation(const AcGeVector2d& vec);
    GE_DLLEXPIMPORT AcGeVector2d   translation  () const;

    // Retrieve scaling, rotation, mirror components
    //
    GE_DLLEXPIMPORT Adesk::Boolean isConformal (double& scale, double& angle,
                                Adesk::Boolean& isMirror, AcGeVector2d& reflex) const;


    // Set/get coordinate system
    //
    GE_DLLEXPIMPORT AcGeMatrix2d&  setCoordSystem(const AcGePoint2d& origin,
                                 const AcGeVector2d& e0,
                                 const AcGeVector2d& e1);
    GE_DLLEXPIMPORT void           getCoordSystem(AcGePoint2d& origin,
                                 AcGeVector2d& e0,
                                 AcGeVector2d& e1) const;

    // Set the matrix to be a specified transformation
    //
    GE_DLLEXPIMPORT AcGeMatrix2d& setToTranslation(const AcGeVector2d& vec);
    GE_DLLEXPIMPORT AcGeMatrix2d& setToRotation (double angle,
                                 const AcGePoint2d& center
				 = AcGePoint2d::kOrigin);
    GE_DLLEXPIMPORT AcGeMatrix2d& setToScaling  (double scaleAll,
                                 const AcGePoint2d& center
				 = AcGePoint2d::kOrigin);
    GE_DLLEXPIMPORT AcGeMatrix2d& setToMirroring(const AcGePoint2d& pnt);
    GE_DLLEXPIMPORT AcGeMatrix2d& setToMirroring(const AcGeLine2d& line);
    GE_DLLEXPIMPORT AcGeMatrix2d& setToAlignCoordSys(const AcGePoint2d&  fromOrigin,
                                 const AcGeVector2d& fromE0,
                                 const AcGeVector2d& fromE1,
                                 const AcGePoint2d&  toOrigin,
                                 const AcGeVector2d& toE0,
                                 const AcGeVector2d& toE1);

    // Functions that make a 2d transformation matrix using various approaches
    //
    GE_DLLEXPIMPORT static
    AcGeMatrix2d translation    (const AcGeVector2d& vec);
    GE_DLLEXPIMPORT static
    AcGeMatrix2d rotation       (double angle, const AcGePoint2d& center
				 = AcGePoint2d::kOrigin);
    GE_DLLEXPIMPORT static
    AcGeMatrix2d scaling        (double scaleAll, const AcGePoint2d& center
				 = AcGePoint2d::kOrigin);
    GE_DLLEXPIMPORT static
    AcGeMatrix2d mirroring      (const AcGePoint2d& pnt);
    GE_DLLEXPIMPORT static
    AcGeMatrix2d mirroring      (const AcGeLine2d& line);
    GE_DLLEXPIMPORT static
    AcGeMatrix2d alignCoordSys  (const AcGePoint2d& fromOrigin,
                                 const AcGeVector2d& fromE0,
                                 const AcGeVector2d& fromE1,
                                 const AcGePoint2d&  toOrigin,
                                 const AcGeVector2d& toE0,
                                 const AcGeVector2d& toE1);

    // For convenient access to the data.
    //
    GE_DLLEXPIMPORT double         operator ()  (unsigned int, unsigned int) const;
    GE_DLLEXPIMPORT double&        operator ()  (unsigned int, unsigned int);

    // The components of the matrix.
    //
    double         entry[3][3]; // [row][column]
};

inline bool
AcGeMatrix2d::operator == (const AcGeMatrix2d& otherMatrix) const
{
    return this->isEqualTo(otherMatrix);
}

// This operator is the logical negation of the `==' operator.
//
inline bool
AcGeMatrix2d::operator != (const AcGeMatrix2d& otherMatrix) const
{
    return !this->isEqualTo(otherMatrix);
}

// Return a reference to the element in position [row][column]
// of the `entry' array.
//
inline double
AcGeMatrix2d::operator () (
    unsigned int row,
    unsigned int column) const
{
    return entry[row][column];
}

inline double&
AcGeMatrix2d::operator () (
    unsigned int row,
    unsigned int column)
{
    return entry[row][column];
}

#pragma pack (pop)
#endif
