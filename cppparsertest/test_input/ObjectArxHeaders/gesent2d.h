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
// This file contains the class AcGeSplineEnt2d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#ifndef AC_GESPNT2d_H
#define AC_GESPNT2d_H

#include "gecurv2d.h"
#include "gekvec.h"
#include "gept2dar.h"
#include "gevec2d.h"
#include "gepnt2d.h"
#include "gept2dar.h"
#pragma pack (push, 8)

class AcGeKnotVector;

class 
GE_DLLEXPIMPORT
AcGeSplineEnt2d : public AcGeCurve2d
{
public:

    // Definition of spline
    //
    Adesk::Boolean    isRational            () const;
    int               degree                () const;
    int               order                 () const;
    int               numKnots              () const;
    const
    AcGeKnotVector&   knots                 () const;
    int               numControlPoints      () const;
    int               continuityAtKnot      (int idx, const AcGeTol& tol =
                                             AcGeContext::gTol) const;

    double            startParam            () const;
    double            endParam              () const;
    AcGePoint2d       startPoint            () const;
    AcGePoint2d       endPoint              () const;

    // Interpolation data
    //
    Adesk::Boolean    hasFitData            () const;

    // Editting
    //
    double            knotAt                (int idx) const;
    AcGeSplineEnt2d&  setKnotAt             (int idx, double val);

    AcGePoint2d       controlPointAt        (int idx) const;
    AcGeSplineEnt2d&  setControlPointAt     (int idx, const AcGePoint2d& pnt);

    // Assignment operator.
    //
    AcGeSplineEnt2d&  operator =            (const AcGeSplineEnt2d& spline);

protected:
    AcGeSplineEnt2d ();
    AcGeSplineEnt2d (const AcGeSplineEnt2d&);
};

#pragma pack (pop)
#endif

