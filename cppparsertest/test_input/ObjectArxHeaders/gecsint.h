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
// Description: class  AcGeCurveSurfInt to hold data for intersections
// of a 3d curve and a surface.

#ifndef AC_GECSINT_H
#define AC_GECSINT_H

#include "adesk.h"
#include "geent3d.h"
#include "geponc3d.h"
#include "geponsrf.h"
#include "geintrvl.h"
#include "gegbl.h"
#include "gegblabb.h"
#pragma pack (push, 8)

class AcGeCurve3d;

class AcGeSurface;

// The intersection class constructor references curve and surface objects, but the
// intersection object does not own them.  The curve and surface objects are linked to
// the intersection object.  On deletion or modification of one of them, internal
// intersection results are marked as invalid and to be re-computed.
//
// Computation of the intersection does not happen on construction or set(), but
// on demand from one of the query functions.
//
// Any output geometry from an intersection object is owned by the caller. The
// const base objects returned by curve() and surface() are not considered
// output objects.
//

class  
GX_DLLEXPIMPORT
AcGeCurveSurfInt : public AcGeEntity3d
{

public:
    // Constructors.
    //
    AcGeCurveSurfInt ();
    AcGeCurveSurfInt (const AcGeCurve3d& crv, const AcGeSurface& srf,
                         const AcGeTol& tol = AcGeContext::gTol );
    AcGeCurveSurfInt (const AcGeCurveSurfInt& src);

    // General query functions.
    //
    const AcGeCurve3d  *curve           () const;
    const AcGeSurface  *surface         () const;
    AcGeTol            tolerance        () const;

    // Intersection query methods.
    //
    int  numIntPoints (AcGeIntersectError& err) const;
    AcGePoint3d  intPoint (int intNum, AcGeIntersectError& err) const;
    void               getIntParams (int intNum,
                                         double& param1, AcGePoint2d& param2, AcGeIntersectError& err) const;
    void               getPointOnCurve (int intNum, AcGePointOnCurve3d&, AcGeIntersectError& err) const;
    void               getPointOnSurface (int intNum, AcGePointOnSurface&, AcGeIntersectError& err) const;
    void			   getIntConfigs (int intNum, AcGe::csiConfig& lower, 
								AcGe::csiConfig& higher, Adesk::Boolean& smallAngle, AcGeIntersectError& err) const;

        
   
    // Set functions.
    //
    AcGeCurveSurfInt& set (const AcGeCurve3d& cvr,
                                     const AcGeSurface& srf,
                                     const AcGeTol& tol = AcGeContext::gTol);

    // Assignment operator.
    //
    AcGeCurveSurfInt& operator = (const AcGeCurveSurfInt& crvInt);
};
#pragma pack (pop)
#endif
