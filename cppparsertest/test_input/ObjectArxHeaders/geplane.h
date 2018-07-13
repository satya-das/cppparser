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
// This file contains the class AcGePlane - A mathematical entity
// used to represent a plane in 3-space.

#ifndef AC_GEPLANE_H
#define AC_GEPLANE_H

#include "geplanar.h"
#pragma pack (push, 8)

class AcGeBoundedPlane;
class AcGeLine3d;

class
AcGePlane : public AcGePlanarEnt
{
public:
    // Global plane objects.
    //
    GE_DLLDATAEXIMP static const AcGePlane kXYPlane;
    GE_DLLDATAEXIMP static const AcGePlane kYZPlane;
    GE_DLLDATAEXIMP static const AcGePlane kZXPlane;

    GE_DLLEXPIMPORT AcGePlane();
    GE_DLLEXPIMPORT AcGePlane(const AcGePlane& src);
    GE_DLLEXPIMPORT AcGePlane(const AcGePoint3d& origin, const AcGeVector3d& normal);
    GE_DLLEXPIMPORT AcGePlane(const AcGePoint3d& pntU, const AcGePoint3d& org, const AcGePoint3d& pntV);
    GE_DLLEXPIMPORT AcGePlane(const AcGePoint3d& org, const AcGeVector3d& uAxis,
              const AcGeVector3d& vAxis);
    GE_DLLEXPIMPORT AcGePlane(double a, double b, double c, double d);

    // Signed distance from a point to a plane.
    //
    GE_DLLEXPIMPORT double         signedDistanceTo (const AcGePoint3d& pnt) const;

    // Intersection
    //
    GE_DLLEXPIMPORT Adesk::Boolean intersectWith    (const AcGeLinearEnt3d& linEnt, AcGePoint3d& resultPnt,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    GE_DLLEXPIMPORT Adesk::Boolean intersectWith    (const AcGePlane& otherPln, AcGeLine3d& resultLine,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    GE_DLLEXPIMPORT Adesk::Boolean intersectWith    (const AcGeBoundedPlane& bndPln, AcGeLineSeg3d& resultLineSeg,
                                     const AcGeTol& tol = AcGeContext::gTol) const;

    // Geometry redefinition.
    //
    GE_DLLEXPIMPORT AcGePlane&     set              (const AcGePoint3d& pnt, const AcGeVector3d& normal);
    GE_DLLEXPIMPORT AcGePlane&     set              (const AcGePoint3d& pntU, const AcGePoint3d& org,
                                     const AcGePoint3d& pntV);
    GE_DLLEXPIMPORT AcGePlane&     set              (double a, double b, double c, double d);
    GE_DLLEXPIMPORT AcGePlane&     set              (const AcGePoint3d& org,
                                     const AcGeVector3d& uAxis,
                                     const AcGeVector3d& vAxis);
    // Assignment operator.
    //
    GE_DLLEXPIMPORT AcGePlane&     operator =       (const AcGePlane& src);
};

#pragma pack (pop)
#endif
