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
// AcGeSurface class is an abstract base class for all other parametric
// surfaces.

#ifndef AC_GESURF_H
#define AC_GESURF_H

#include "geent3d.h"
#include "gevc3dar.h"
#pragma pack (push, 8)

class AcGePoint2d;
class AcGeCurve3d;
class AcGePointOnCurve3d;
class AcGePointOnSurface;
class AcGePointOnSurfaceData;
class AcGeInterval;


class
GE_DLLEXPIMPORT
AcGeSurface : public AcGeEntity3d
{
public:
    // Parameter related.
    //
    AcGePoint2d     paramOf        (const AcGePoint3d& pnt,
                                    const AcGeTol& tol = AcGeContext::gTol) const;
    // Point containment
    //
    Adesk::Boolean  isOn           (const AcGePoint3d& pnt,
                                    const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean  isOn           (const AcGePoint3d& pnt, AcGePoint2d& paramPoint,
                                    const AcGeTol& tol = AcGeContext::gTol ) const;
    // Operations.
    //
    AcGePoint3d closestPointTo(const AcGePoint3d& pnt,
                                  const AcGeTol& tol = AcGeContext::gTol) const;

    void getClosestPointTo(const AcGePoint3d& pnt, AcGePointOnSurface& result,
                           const AcGeTol& tol = AcGeContext::gTol) const;
	
    double          distanceTo     (const AcGePoint3d& pnt,
                                    const AcGeTol& tol = AcGeContext::gTol) const;

    Adesk::Boolean  isNormalReversed () const;
    AcGeSurface&    reverseNormal    ();

    // Assignment operator.
    //
    AcGeSurface&    operator =     (const AcGeSurface& otherSurface);

    // Bounds in parameter space.
    //
    void   getEnvelope  (AcGeInterval& intrvlX, AcGeInterval& intrvlY) const;

    // Geometric inquiry methods.
    //
    Adesk::Boolean isClosedInU       (const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isClosedInV       (const AcGeTol& tol = AcGeContext::gTol) const;

    // Evaluators.
    // Derivative arrays are indexed partialU, partialV followed by
    // the mixed partial.
    //
    AcGePoint3d   evalPoint   (const AcGePoint2d& param) const;
    AcGePoint3d   evalPoint   (const AcGePoint2d& param, int derivOrd,
                               AcGeVector3dArray& derivatives) const;
    AcGePoint3d   evalPoint   (const AcGePoint2d& param, int derivOrd,
                               AcGeVector3dArray& derivatives,
                               AcGeVector3d& normal) const;
protected:
    AcGeSurface ();
    AcGeSurface (const AcGeSurface&);
};

#pragma pack (pop)
#endif
