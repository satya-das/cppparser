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
// This file contains the class AcGePlanarEnt. It is an abstract class
// representing an oriented plane in 3-space.

#ifndef AC_GEPLANAR_H
#define AC_GEPLANAR_H

#include "gesurf.h"
#include "gevec3d.h"
#pragma pack (push, 8)

class AcGeLineSeg3d;
class AcGeLinearEnt3d;
class AcGeCircArc3d;

class
GE_DLLEXPIMPORT
AcGePlanarEnt : public AcGeSurface
{
public:
    // Intersection
    //
    Adesk::Boolean  intersectWith    (const AcGeLinearEnt3d& linEnt, AcGePoint3d& pnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    // Closest point
    //
    AcGePoint3d     closestPointToLinearEnt (const AcGeLinearEnt3d& line,
                                             AcGePoint3d& pointOnLine,
                                             const AcGeTol& tol
                                               = AcGeContext::gTol) const;
    AcGePoint3d     closestPointToPlanarEnt (const AcGePlanarEnt& otherPln,
                                             AcGePoint3d& pointOnOtherPln,
                                             const AcGeTol& tol
                                               = AcGeContext::gTol) const;
    // Direction tests.
    //
    Adesk::Boolean isParallelTo      (const AcGeLinearEnt3d& linEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isParallelTo      (const AcGePlanarEnt& otherPlnEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isPerpendicularTo (const AcGeLinearEnt3d& linEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isPerpendicularTo (const AcGePlanarEnt& linEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;

    // Point set equality.
    //
    Adesk::Boolean isCoplanarTo      (const AcGePlanarEnt& otherPlnEnt,
                                      const AcGeTol& tol = AcGeContext::gTol) const;

    // Get methods.
    //
    void              get            (AcGePoint3d&, AcGeVector3d& uVec,
                                      AcGeVector3d& vVec) const;
    void              get            (AcGePoint3d&, AcGePoint3d& origin,
                                      AcGePoint3d&) const;

    // Geometric properties.
    //
    AcGePoint3d    pointOnPlane      () const;
    AcGeVector3d   normal            () const;
    void           getCoefficients(double& a, double& b, double& c, double& d) const;
    void           getCoordSystem(AcGePoint3d& origin, AcGeVector3d& axis1,
                                  AcGeVector3d& axis2) const;
    // Assignment operator.
    //
    AcGePlanarEnt& operator =        (const AcGePlanarEnt& src);

protected:
    AcGePlanarEnt ();
    AcGePlanarEnt (const AcGePlanarEnt&);
};

#pragma pack (pop)
#endif
