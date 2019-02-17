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
// This file contains:
// The AcGePointOnCurve2d class which is used to keep information of a point
// belonging to a 2d curve

#ifndef AC_GEPONC2D_H
#define AC_GEPONC2D_H

#include "gepent2d.h"
#pragma pack (push, 8)

class AcGeCurve2d;

class
GE_DLLEXPIMPORT
AcGePointOnCurve2d : public AcGePointEnt2d
{
public:
    AcGePointOnCurve2d  ();
    AcGePointOnCurve2d  (const AcGeCurve2d& crv);
    AcGePointOnCurve2d  (const AcGeCurve2d& crv, double param);
    AcGePointOnCurve2d  (const AcGePointOnCurve2d& src);

    // Assignment operator.
    //
    AcGePointOnCurve2d& operator =     (const AcGePointOnCurve2d& src);

    // Query functions.
    //
    const AcGeCurve2d*  curve          () const;
    double              parameter      () const;

    // Functions to evaluate a point.
    //
    AcGePoint2d         point          () const;
    AcGePoint2d         point          (double param);
    AcGePoint2d         point          (const AcGeCurve2d& crv, double param);

    // Functions to evaluate the derivatives.
    //
    AcGeVector2d        deriv          (int order) const;
    AcGeVector2d        deriv          (int order, double param);
    AcGeVector2d        deriv          (int order, const AcGeCurve2d& crv,
                                        double param);
    // Singularity
    //
    Adesk::Boolean      isSingular     (const AcGeTol&  tol =
                                        AcGeContext::gTol) const;
    Adesk::Boolean      curvature      (double& res);
    Adesk::Boolean      curvature      (double param, double& res);
    // Set functions.
    //
    AcGePointOnCurve2d& setCurve       (const AcGeCurve2d& crv);
    AcGePointOnCurve2d& setParameter   (double param);
};

#pragma pack (pop)
#endif

