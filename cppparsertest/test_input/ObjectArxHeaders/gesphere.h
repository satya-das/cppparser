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
// This file implements the class AcGeSphere, a representation for a
// sphere.  It is defined by its radius, and the center. Two vectors,
// northAxis and refAxis are used in the parameterization of
// the sphere.  northAxis identifies the north and the south poles
// of the sphere. refAxis serves as a reference for the parameters.
// It is a vector orthogonal to northAxis.
// Parameter u is the longitude, which for a closed sphere defaults
// to the range [-PI, PI).  Zero corresponds to the meridian that
// contains the refAxis of the sphere.
// Parameter v is the latitude, which for a closed sphere defaults
// to the range [-PI/2, PI/2].  The lower bound maps to the south
// pole, zero is on the equator, and the upperbound maps to the north
// pole.
// The sphere is periodic in u with a period of 2PI.
// [umin, umax] x [vmin, vmax] defines a four sided spherical patch
// bounded by two arcs that are meridians of longitude, and two arcs
// that are parallels of latitude.  Following constraints apply when
// defining a spherical patch.
// umin < umax and |umin - umax| <= 2PI.
// vmin < vmax and |vmin - vmax| <= PI.
//

#ifndef AC_GESPHERE_H
#define AC_GESPHERE_H

#include "gegbl.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "geintrvl.h"
#include "gesurf.h"
#pragma pack (push, 8)

class AcGeCircArc3d;

class
GX_DLLEXPIMPORT
AcGeSphere : public AcGeSurface
{
public:
    AcGeSphere();
    AcGeSphere(double radius, const AcGePoint3d& center);
    AcGeSphere(double radius, const AcGePoint3d& center,
               const AcGeVector3d& northAxis, const AcGeVector3d& refAxis,
               double startAngleU, double endAngleU,
               double startAngleV, double endAngleV);
    AcGeSphere(const AcGeSphere& sphere);

    // Geometric properties.
    //
    double         radius            () const;
    AcGePoint3d    center            () const;
    void           getAnglesInU      (double& start, double& end) const;
    void           getAnglesInV      (double& start, double& end) const;
    AcGeVector3d   northAxis         () const;
    AcGeVector3d   refAxis           () const;
    AcGePoint3d    northPole         () const;
    AcGePoint3d    southPole         () const;
    Adesk::Boolean isOuterNormal     () const;
    Adesk::Boolean isClosed       (const AcGeTol& tol = AcGeContext::gTol) const;

    AcGeSphere&    setRadius         (double);
    AcGeSphere&    setAnglesInU      (double start, double end);
    AcGeSphere&    setAnglesInV      (double start, double end);
    AcGeSphere&    set               (double radius, const AcGePoint3d& center);
    AcGeSphere&    set               (double radius, const AcGePoint3d& center,
                                      const AcGeVector3d& northAxis,
                                      const AcGeVector3d& refAxis,
                                      double startAngleU,
                                      double endAngleU,
                                      double startAngleV,
                                      double endAngleV);
    // Assignment operator.
    //
    AcGeSphere&    operator =     (const AcGeSphere& sphere);

    // Intersection with a linear entity
    //
    Adesk::Boolean intersectWith  (const AcGeLinearEnt3d&, int& intn,
                                   AcGePoint3d& p1, AcGePoint3d& p2,
                                   const AcGeTol& tol = AcGeContext::gTol) const;
};

#pragma pack (pop)
#endif
