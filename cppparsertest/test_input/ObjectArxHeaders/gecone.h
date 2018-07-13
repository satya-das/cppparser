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
// Description:
//
// This file implements the class AcGeCone, a representation for
// a single right circular cone.  It is defined by its axis of
// symmetry, height, half angle (the angle between the generating
// line and the axis of symmetry), its origin which is a point on
// the axis of symmetry, and the radius at the origin.  The cross
// section containing the origin is refered to as the base.  The
// radius at the base should not be zero.  The cone may extend on
// either side of the base.
// The fabs(halfAngle) is constrained to the interval (0, PI/2),
// and is measured from the symmetric axis of the cone.  A positive
// angle results in a cone apex on the opposite direction of the
// symmetric axis, and vice versa for a negative angle.
// Parameter u is the angle of revolution measured from the refAxis
// (an axis perpendicular to the axis of symmetry).  For a closed cone,
// it defaults to [-PI, PI).  Right hand rule applied along the
// direction of the axis of symmetry defines the positive direction
// of u.  The surface is periodic in u with a period of 2PI.
// Parameter v varies along the generating line.  v = 0 correspond
// to the base of the cone.  v is dimensionless and increases in the
// direction the axis of symmetry.  It is scaled against the initial
// base radius of the cone.
// [umin, umax] x [vmin, vmax] defines a four sided conical patch
// bounded by two straight lines (at angles umin and umax), and two
// circular arcs (at vmin and vmax).  Following must be observed
// when defining a cone.
// umin < umax and |umin - umax| <= 2PI.
// Base radius > 0.0
// The hight of the cone is specified relative to its origin
// (with the height increasing in the direction of the symetric
// axis).
//

#ifndef AC_GECONE_H
#define AC_GECONE_H

#include "gegbl.h"
#include "geintrvl.h"
#include "gevec3d.h"
#include "gesurf.h"
#include "gearc3d.h"
#pragma pack (push, 8)

class AcGePoint3d;
class AcGeVector3d;
class AcGeCircArc3d;
class AcGeInterval;
class AcGeLinearEnt3d;

class 
GX_DLLEXPIMPORT
AcGeCone : public AcGeSurface
{
public:
    AcGeCone();
    AcGeCone(double cosineAngle, double sineAngle,
             const  AcGePoint3d& baseOrigin, double baseRadius,
             const  AcGeVector3d& axisOfSymmetry);
    AcGeCone(double cosineAngle, double sineAngle,
             const  AcGePoint3d& baseOrigin, double baseRadius,
             const  AcGeVector3d& axisOfSymmetry,
             const  AcGeVector3d& refAxis, const  AcGeInterval& height,
             double startAngle, double endAngle);
    AcGeCone(const AcGeCone& cone);

    // Geometric properties.
    //
    double           baseRadius        () const;
    AcGePoint3d      baseCenter        () const;
    void             getAngles         (double& start, double& end) const;
    double           halfAngle         () const;
    void             getHalfAngle      (double& cosineAngle, double& sineAngle)
                                                 const;
    void             getHeight         (AcGeInterval& range) const;
    double           heightAt          (double u) const;
    AcGeVector3d     axisOfSymmetry    () const;
    AcGeVector3d     refAxis           () const;
    AcGePoint3d      apex              () const;
    Adesk::Boolean   isClosed          (const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean   isOuterNormal     () const;


    AcGeCone&        setBaseRadius     (double radius);
    AcGeCone&        setAngles         (double startAngle, double endAngle);
    AcGeCone&        setHeight         (const AcGeInterval& height);
    AcGeCone&        set               (double cosineAngle, double sineAngle,
                                        const  AcGePoint3d& baseCenter,
                                        double baseRadius,
                                        const  AcGeVector3d& axisOfSymmetry);
    AcGeCone&        set               (double cosineAngle, double sineAngle,
                                        const  AcGePoint3d& baseCenter,
                                        double baseRadius,
                                        const  AcGeVector3d& axisOfSymmetry,
                                        const  AcGeVector3d& refAxis,
                                        const  AcGeInterval& height,
                                        double startAngle, double endAngle);
    // Assignment operator.
    //
    AcGeCone&        operator =        (const AcGeCone& cone);

    // Intersection with a linear entity
    //
    Adesk::Boolean   intersectWith     (const AcGeLinearEnt3d& linEnt, int& intn,
                                        AcGePoint3d& p1, AcGePoint3d& p2,
                                        const AcGeTol& tol = AcGeContext::gTol) const;
};


#pragma pack (pop)
#endif
