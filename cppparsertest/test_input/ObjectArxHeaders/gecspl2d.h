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
// Description:
//
// This file contains the class AcGeCubicSplineCurve2d - A mathematic
// entity used to represent a 2d interpolation cubic-spline curve.
//

#ifndef AC_GECSPL2D_H
#define AC_GECSPL2D_H

class AcGePointOnCurve2d;
class AcGeCurve2dIntersection;
class AcGeInterval;
class AcGePlane;

#include "gesent2d.h"
#include "gept2dar.h"
#include "gevc2dar.h"
#include "gevec2d.h"
#include "gekvec.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeCubicSplineCurve2d : public AcGeSplineEnt2d
{
public:

    AcGeCubicSplineCurve2d();
    AcGeCubicSplineCurve2d(const AcGeCubicSplineCurve2d& spline);

    // Construct a periodic cubic spline curve
    // Contract: the first fit point must be equal to the last fit point
    //
    AcGeCubicSplineCurve2d(const AcGePoint2dArray& fitPnts,
			   const AcGeTol& tol = AcGeContext::gTol);

    // Construct a cubic spline curve with clamped end condition
    //
    AcGeCubicSplineCurve2d(const AcGePoint2dArray& fitPnts,
			   const AcGeVector2d& startDeriv,
			   const AcGeVector2d& endDeriv,
                           const AcGeTol& tol = AcGeContext::gTol);

    // Construct a cubic spline approximating the curve
    //
    AcGeCubicSplineCurve2d(const AcGeCurve2d& curve,
                           double epsilon = AcGeContext::gTol.equalPoint());

    // Construct a cubic spline curve with given fit points and 1st derivatives
    //
	AcGeCubicSplineCurve2d(const AcGeKnotVector& knots,
	                       const AcGePoint2dArray& fitPnts,
			       const AcGeVector2dArray& firstDerivs,
	                       Adesk::Boolean isPeriodic = Adesk::kFalse );

    // Definition of spline
    //
    int                     numFitPoints   ()        const;
    AcGePoint2d             fitPointAt     (int idx) const;
    AcGeCubicSplineCurve2d& setFitPointAt  (int idx, const AcGePoint2d& point);
    AcGeVector2d            firstDerivAt   (int idx) const;
    AcGeCubicSplineCurve2d& setFirstDerivAt(int idx, const AcGeVector2d& deriv);

    // Assignment operator.
    //
    AcGeCubicSplineCurve2d&  operator = (const AcGeCubicSplineCurve2d& spline);
};

#pragma pack (pop)
#endif
