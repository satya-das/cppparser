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
// This file contains the class AcGeSplineEnt3d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#ifndef AC_GESPNT3D_H
#define AC_GESPNT3D_H

#include "gecurv3d.h"
#include "gekvec.h"
#include "gept3dar.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "gept3dar.h"
#pragma pack (push, 8)

class AcGeKnotVector;

class
GE_DLLEXPIMPORT
AcGeSplineEnt3d : public AcGeCurve3d
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
                                             AcGeContext::gTol ) const;

    double            startParam            () const;
    double            endParam              () const;
    AcGePoint3d       startPoint            () const;
    AcGePoint3d       endPoint              () const;

    // Interpolation data
    //
    Adesk::Boolean    hasFitData            () const;

    // Editting
    //
    double            knotAt                (int idx) const;
    AcGeSplineEnt3d&  setKnotAt             (int idx, double val);

    AcGePoint3d       controlPointAt        (int idx) const;
    AcGeSplineEnt3d&  setControlPointAt     (int idx, const AcGePoint3d& pnt);


    // Assignment operator.
    //
    AcGeSplineEnt3d&  operator =            (const AcGeSplineEnt3d& spline);

protected:
    AcGeSplineEnt3d ();
    AcGeSplineEnt3d (const AcGeSplineEnt3d&);
};

#pragma pack (pop)
#endif

