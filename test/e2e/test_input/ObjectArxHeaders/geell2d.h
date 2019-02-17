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
// This file contains the class AcGeEllipArc2d - A mathematical entity
// used to represent an ellipse in 2-space.

#ifndef AC_GEELL2D_H
#define AC_GEELL2D_H

#include "gecurv2d.h"
#include "gevec2d.h"
#include "gepnt2d.h"
#include "geponc2d.h"
#include "geintrvl.h"
#pragma pack (push, 8)

class AcGeCircArc2d;
class AcGePlanarEnt;
class AcGeEllipArc2d;
class AcGeLinearEnt2d;


class
GE_DLLEXPIMPORT
AcGeEllipArc2d : public AcGeCurve2d
{
public:
    AcGeEllipArc2d();
    AcGeEllipArc2d(const AcGeEllipArc2d& ell);
    AcGeEllipArc2d(const AcGeCircArc2d& arc);
    AcGeEllipArc2d(const AcGePoint2d& cent, const AcGeVector2d& majorAxis,
                   const AcGeVector2d& minorAxis, double majorRadius,
                   double minorRadius);
    AcGeEllipArc2d(const AcGePoint2d& cent, const AcGeVector2d& majorAxis,
                   const AcGeVector2d& minorAxis, double majorRadius,
                   double minorRadius, double startAngle, double endAngle);

    // Intersection with other geometric objects.
    //
    Adesk::Boolean intersectWith (const AcGeLinearEnt2d& line, int& intn,
                                  AcGePoint2d& p1, AcGePoint2d& p2,
                                  const AcGeTol& tol = AcGeContext::gTol) const;
    // Inquiry Methods
    //
    Adesk::Boolean isCircular    (const AcGeTol& tol = AcGeContext::gTol) const;

    // Test if point is inside full ellipse
    //
    Adesk::Boolean isInside      (const AcGePoint2d& pnt,
                                  const AcGeTol& tol = AcGeContext::gTol) const;


    // Definition of ellipse
    //
    AcGePoint2d    center        () const;
    double         minorRadius   () const;
    double         majorRadius   () const;
    AcGeVector2d   minorAxis     () const;
    AcGeVector2d   majorAxis     () const;
    double         startAng      () const;
    double         endAng        () const;
    AcGePoint2d    startPoint    () const;
    AcGePoint2d    endPoint      () const;
    Adesk::Boolean isClockWise   () const;

    AcGeEllipArc2d& setCenter     (const AcGePoint2d& cent);
    AcGeEllipArc2d& setMinorRadius(double rad);
    AcGeEllipArc2d& setMajorRadius(double rad);
    AcGeEllipArc2d& setAxes       (const AcGeVector2d& majorAxis, const AcGeVector2d& minorAxis);
    AcGeEllipArc2d& setAngles     (double startAngle, double endAngle);
    AcGeEllipArc2d& set           (const AcGePoint2d& cent,
                                   const AcGeVector2d& majorAxis,
                                   const AcGeVector2d& minorAxis,
                                   double majorRadius, double minorRadius);
    AcGeEllipArc2d& set           (const AcGePoint2d& cent,
                                   const AcGeVector2d& majorAxis,
                                   const AcGeVector2d& minorAxis,
                                   double majorRadius, double minorRadius,
                                   double startAngle, double endAngle);
    AcGeEllipArc2d& set           (const AcGeCircArc2d& arc);

    // Assignment operator.
    //
    AcGeEllipArc2d& operator =    (const AcGeEllipArc2d& ell);
};

#pragma pack (pop)
#endif

