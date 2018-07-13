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
// class AcGePointOnSurface to keep information of a point belonging
// to a surface.

#ifndef AC_GEPONSRF_H
#define AC_GEPONSRF_H

#include "gepent3d.h"
#pragma pack (push, 8)

class AcGeSurface;

class
GE_DLLEXPIMPORT
AcGePointOnSurface : public AcGePointEnt3d
{
public:
    AcGePointOnSurface();
    AcGePointOnSurface(const AcGeSurface& surf);
    AcGePointOnSurface(const AcGeSurface& surf, const AcGePoint2d& param);
    AcGePointOnSurface(const AcGePointOnSurface& src);

    // Assignment operator.
    //
    AcGePointOnSurface& operator =     (const AcGePointOnSurface& src);

    // Query functions.
    //
    const AcGeSurface*  surface        () const;
    AcGePoint2d         parameter      () const;

    // Functions to evaluate a point.
    //
    AcGePoint3d         point          () const;
    AcGePoint3d         point          (const AcGePoint2d& param );
    AcGePoint3d         point          (const AcGeSurface& surf,
                                        const AcGePoint2d& param);

    // Functions to evaluate surface normal.
    //
    AcGeVector3d        normal         () const;
    AcGeVector3d        normal         (const AcGePoint2d& param );
    AcGeVector3d        normal         (const AcGeSurface& surf,
                                        const AcGePoint2d& param);
    // Functions to evaluate derivatives.
    //
    AcGeVector3d        uDeriv         (int order) const;
    AcGeVector3d        uDeriv         (int order, const AcGePoint2d& param);
    AcGeVector3d        uDeriv         (int order, const AcGeSurface& surf,
                                        const AcGePoint2d& param);

    AcGeVector3d        vDeriv         (int order) const;
    AcGeVector3d        vDeriv         (int order, const AcGePoint2d& param);
    AcGeVector3d        vDeriv         (int order, const AcGeSurface& surf,
                                        const AcGePoint2d& param);

    // Functions to evaluate the mixed partial.
    //
    AcGeVector3d        mixedPartial   () const;
    AcGeVector3d        mixedPartial   (const AcGePoint2d& param);
    AcGeVector3d        mixedPartial   (const AcGeSurface& surf,
                                        const AcGePoint2d& param);

    // Functions to compute the tangent vector in a given direction.
    //
    AcGeVector3d        tangentVector  (const AcGeVector2d& vec) const;
    AcGeVector3d        tangentVector  (const AcGeVector2d& vec,
                                        const AcGePoint2d& param);
    AcGeVector3d        tangentVector  (const AcGeVector2d& vec,
                                        const AcGeSurface& vecSurf,
                                        const AcGePoint2d& param);

    // Functions to invert a tangent vector to parameter space.
    //
    AcGeVector2d        inverseTangentVector  (const AcGeVector3d& vec) const;
    AcGeVector2d        inverseTangentVector  (const AcGeVector3d& vec,
                                               const AcGePoint2d& param);
    AcGeVector2d        inverseTangentVector  (const AcGeVector3d& vec,
                                               const AcGeSurface& surf,
                                               const AcGePoint2d& param);
    // Set functions.
    //
    AcGePointOnSurface& setSurface     (const AcGeSurface& surf);
    AcGePointOnSurface& setParameter   (const AcGePoint2d& param);
};

#pragma pack (pop)
#endif

