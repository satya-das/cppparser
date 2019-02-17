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
// This file contains the class AcGeLinearEnt2d - A mathematical entity
// used to represent a line in 2-space.

#ifndef AC_GELENT2D_H
#define AC_GELENT2D_H

#include "gecurv2d.h"
#include "gepnt2d.h"
#include "gevec2d.h"
#pragma pack (push, 8)

class AcGeCircArc2d;

class
GE_DLLEXPIMPORT
AcGeLinearEnt2d : public AcGeCurve2d
{
public:
    // Intersection with other geometric objects.
    //
    Adesk::Boolean   intersectWith  (const AcGeLinearEnt2d& line, AcGePoint2d& intPnt,
                                     const AcGeTol& tol = AcGeContext::gTol) const;

    // Find the overlap with other AcGeLinearEnt object
    //
    Adesk::Boolean   overlap        (const AcGeLinearEnt2d& line,
                                     AcGeLinearEnt2d*& overlap,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    // Direction tests.
    //
    Adesk::Boolean   isParallelTo   (const AcGeLinearEnt2d& line,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean   isPerpendicularTo(const AcGeLinearEnt2d& line,
                                      const AcGeTol& tol = AcGeContext::gTol) const;
    // Test if two lines are colinear.
    //
    Adesk::Boolean   isColinearTo   (const AcGeLinearEnt2d& line,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    // Perpendicular through a given point
    //
    void             getPerpLine    (const AcGePoint2d& pnt, AcGeLine2d& perpLine) const;

    // Definition of line.
    //
    AcGePoint2d      pointOnLine    () const;
    AcGeVector2d     direction      () const;
    void             getLine        (AcGeLine2d& line) const;

    // Assignment operator.
    //
    AcGeLinearEnt2d& operator =     (const AcGeLinearEnt2d& line);

protected:
    AcGeLinearEnt2d ();
    AcGeLinearEnt2d (const AcGeLinearEnt2d&);
};

#pragma pack (pop)
#endif
