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
// This file contains the class AcGeMatrix3d - a matrix used to
// represent general purpose 3d transformations in homogeneous
// co-ordinate space.

#ifndef AC_GEMAT3D_H
#define AC_GEMAT3D_H

#include "gegbl.h"
#include "gemat2d.h"
#include "gepnt3d.h"
#pragma pack (push, 8)

class AcGeLine3d;
class AcGeVector3d;
class AcGePlane;
class AcGeTol;

class 
AcGeMatrix3d
{
public:
    GE_DLLEXPIMPORT AcGeMatrix3d();
    GE_DLLEXPIMPORT AcGeMatrix3d(const AcGeMatrix3d& src);

    // The multiplicative identity.
    //
    GE_DLLDATAEXIMP static const   AcGeMatrix3d    kIdentity;

    // Reset matrix.
    //
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToIdentity();

    // Multiplication.
    //
    GE_DLLEXPIMPORT AcGeMatrix3d   operator *      (const AcGeMatrix3d& mat) const;
    GE_DLLEXPIMPORT AcGeMatrix3d&  operator *=     (const AcGeMatrix3d& mat);
    GE_DLLEXPIMPORT AcGeMatrix3d&  preMultBy       (const AcGeMatrix3d& leftSide);
    GE_DLLEXPIMPORT AcGeMatrix3d&  postMultBy      (const AcGeMatrix3d& rightSide);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToProduct    (const AcGeMatrix3d& mat1, const AcGeMatrix3d& mat2);

    // Multiplicative inverse.
    //
    GE_DLLEXPIMPORT AcGeMatrix3d&  invert          ();
    GE_DLLEXPIMPORT AcGeMatrix3d   inverse         () const;
    GE_DLLEXPIMPORT AcGeMatrix3d   inverse         (const AcGeTol& tol) const;
    // Test if it is a singular matrix.  A singular matrix is not invertable.
    //
    GE_DLLEXPIMPORT Adesk::Boolean isSingular      (const AcGeTol& tol = AcGeContext::gTol) const;

    // Matrix transposition.
    //
    GE_DLLEXPIMPORT AcGeMatrix3d&  transposeIt     ();
    GE_DLLEXPIMPORT AcGeMatrix3d   transpose       () const;

    // Tests for equivalence using the infinity norm.
    //
    GE_DLLEXPIMPORT bool operator ==     (const AcGeMatrix3d& mat) const;
    GE_DLLEXPIMPORT bool operator !=     (const AcGeMatrix3d& mat) const;
    GE_DLLEXPIMPORT bool isEqualTo       (const AcGeMatrix3d& mat, const AcGeTol& tol
                                    = AcGeContext::gTol) const;

    // Test scaling effects of matrix
    //
    GE_DLLEXPIMPORT Adesk::Boolean isUniScaledOrtho(const AcGeTol& tol = AcGeContext::gTol) const;
    GE_DLLEXPIMPORT Adesk::Boolean isScaledOrtho   (const AcGeTol& tol = AcGeContext::gTol) const;

    // Determinant
    //
    GE_DLLEXPIMPORT double         det             () const;

    // Set/retrieve translation.
    //
    GE_DLLEXPIMPORT AcGeMatrix3d&  setTranslation  (const AcGeVector3d& vec);
    GE_DLLEXPIMPORT AcGeVector3d   translation     () const;

    // Set/get coordinate system
    //
    GE_DLLEXPIMPORT AcGeMatrix3d&  setCoordSystem  (const AcGePoint3d& origin,
                                    const AcGeVector3d& xAxis,
                                    const AcGeVector3d& yAxis,
                                    const AcGeVector3d& zAxis);
    GE_DLLEXPIMPORT void           getCoordSystem  (AcGePoint3d& origin,
                                    AcGeVector3d& xAxis,
                                    AcGeVector3d& yAxis,
                                    AcGeVector3d& zAxis) const;

    // Set the matrix to be a specified transformation
    //
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToTranslation(const AcGeVector3d& vec);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToRotation   (double angle, const AcGeVector3d& axis,
                                    const AcGePoint3d& center
                                    = AcGePoint3d::kOrigin);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToScaling    (double scaleAll, const AcGePoint3d& center
                                    = AcGePoint3d::kOrigin);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToMirroring  (const AcGePlane& pln);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToMirroring  (const AcGePoint3d& pnt);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToMirroring  (const AcGeLine3d& line);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToProjection (const AcGePlane& projectionPlane,
                                    const AcGeVector3d& projectDir);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToAlignCoordSys(const AcGePoint3d& fromOrigin,
                                    const AcGeVector3d& fromXAxis,
                                    const AcGeVector3d& fromYAxis,
                                    const AcGeVector3d& fromZAxis,
                                    const AcGePoint3d& toOrigin,
                                    const AcGeVector3d& toXAxis,
                                    const AcGeVector3d& toYAxis,
                                    const AcGeVector3d& toZAxis);

    GE_DLLEXPIMPORT AcGeMatrix3d&  setToWorldToPlane(const AcGeVector3d& normal);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToWorldToPlane(const AcGePlane& plane);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToPlaneToWorld(const AcGeVector3d& normal);
    GE_DLLEXPIMPORT AcGeMatrix3d&  setToPlaneToWorld(const AcGePlane& plane);

    // Similar to above, but creates matrix on the stack.
    //
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   translation     (const AcGeVector3d& vec);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   rotation        (double angle, const AcGeVector3d& axis,
                                    const AcGePoint3d& center
                                    = AcGePoint3d::kOrigin);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   scaling         (double scaleAll, const AcGePoint3d& center
                                    = AcGePoint3d::kOrigin);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   mirroring       (const AcGePlane& pln);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   mirroring       (const AcGePoint3d& pnt);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   mirroring       (const AcGeLine3d& line);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   projection      (const AcGePlane& projectionPlane,
                                    const AcGeVector3d& projectDir);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   alignCoordSys   (const AcGePoint3d&  fromOrigin,
                                    const AcGeVector3d& fromXAxis,
                                    const AcGeVector3d& fromYAxis,
                                    const AcGeVector3d& fromZAxis,
                                    const AcGePoint3d&  toOrigin,
                                    const AcGeVector3d& toXAxis,
                                    const AcGeVector3d& toYAxis,
                                    const AcGeVector3d& toZAxis);

    GE_DLLEXPIMPORT static
    AcGeMatrix3d   worldToPlane    (const AcGeVector3d& normal);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   worldToPlane    (const AcGePlane&);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   planeToWorld    (const AcGeVector3d& normal);
    GE_DLLEXPIMPORT static
    AcGeMatrix3d   planeToWorld    (const AcGePlane&);

    // Get the length of the MAXIMUM column of the
    // 3x3 portion of the matrix.
    //
    GE_DLLEXPIMPORT double scale(void) const;

    GE_DLLEXPIMPORT double          norm            () const;

    GE_DLLEXPIMPORT AcGeMatrix2d convertToLocal     (AcGeVector3d& normal, double& elev) const;


    // For convenient access to the data.
    //
    GE_DLLEXPIMPORT double         operator ()     (unsigned int, unsigned int) const;
    GE_DLLEXPIMPORT double&        operator ()     (unsigned int, unsigned int);

    // The components of the matrix.
    //
    double         entry[4][4];    // [row][column]

    GE_DLLEXPIMPORT Adesk::Boolean  inverse(AcGeMatrix3d& inv, double tol) const;

private:
    void           pivot           (int, AcGeMatrix3d&);
    int            pivotIndex(int) const;
    void           swapRows        (int, int, AcGeMatrix3d&);
};

inline bool
AcGeMatrix3d::operator == (const AcGeMatrix3d& otherMatrix) const
{
    return this->isEqualTo(otherMatrix);
}

// This operator is the logical negation of the `==' operator.
//
inline bool
AcGeMatrix3d::operator != (const AcGeMatrix3d& otherMatrix) const
{
    return !this->isEqualTo(otherMatrix);
}

// Return the element in position [row][column] of the `entry' array.
//
inline double
AcGeMatrix3d::operator () (
    unsigned int row,
    unsigned int column) const
{
    return entry[row][column];
}

inline double&
AcGeMatrix3d::operator () (
    unsigned int row,
    unsigned int column)
{
    return entry[row][column];
}

#pragma pack (pop)
#endif
