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
// This file contains the class AcGePolyline3d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#ifndef AC_GEPLIN3D_H
#define AC_GEPLIN3D_H

#include "gecurv3d.h"
#include "gekvec.h"
#include "gept3dar.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "gesent3d.h"
#pragma pack (push, 8)


class
GE_DLLEXPIMPORT
AcGePolyline3d : public AcGeSplineEnt3d
{
public:

    AcGePolyline3d();
    AcGePolyline3d( const AcGePolyline3d& src );
    AcGePolyline3d( const AcGePoint3dArray& points);
    AcGePolyline3d( const AcGeKnotVector& knots,
                    const AcGePoint3dArray& cntrlPnts );

    // Approximate curve with polyline
    //
    AcGePolyline3d( const AcGeCurve3d& crv, double apprEps );

    // Interpolation data
    //
    int              numFitPoints () const;
    AcGePoint3d      fitPointAt   (int idx) const;
    AcGeSplineEnt3d& setFitPointAt(int idx, const AcGePoint3d& point);

    // Assignment operator.
    //
    AcGePolyline3d& operator =     (const AcGePolyline3d& pline);
};

#pragma pack (pop)
#endif

