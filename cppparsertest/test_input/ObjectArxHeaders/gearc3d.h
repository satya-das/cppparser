//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//
// This file contains the class AcGeCircArc3d - A mathematical entity
// used to represent a circular arc in 3-space.

#ifndef AC_GEARC3D_H
#define AC_GEARC3D_H

#include "gecurv3d.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "geplane.h"
#include "gegblabb.h"
#pragma pack (push, 8)
class AcGeLine3d;
class AcGeCircArc2d;
class AcGePlanarEnt;

class 
GE_DLLEXPIMPORT
AcGeCircArc3d : public AcGeCurve3d
{
public:
    AcGeCircArc3d();
    AcGeCircArc3d(const AcGeCircArc3d& arc);
    AcGeCircArc3d(const AcGePoint3d& cent,
                  const AcGeVector3d& nrm, double radius);
    AcGeCircArc3d(const AcGePoint3d& cent, const AcGeVector3d& nrm,
                  const AcGeVector3d& refVec, double radius,
                  double startAngle, double endAngle);
    AcGeCircArc3d(const AcGePoint3d& startPoint, const AcGePoint3d& pnt, const AcGePoint3d& endPoint);
                                            
    // Return the point on this object that is closest to the other object.
    //
    AcGePoint3d    closestPointToPlane (const AcGePlanarEnt& plane,
                                        AcGePoint3d& pointOnPlane,
                                        const AcGeTol& tol
                                        = AcGeContext::gTol) const;

    // Intersection with other geometric objects.
    //
    Adesk::Boolean intersectWith  (const AcGeLinearEnt3d& line, int& intn,
                                   AcGePoint3d& p1, AcGePoint3d& p2,
                                   const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean intersectWith  (const AcGeCircArc3d& arc, int& intn,
                                   AcGePoint3d& p1, AcGePoint3d& p2,
                                   const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean  intersectWith (const AcGePlanarEnt& plane, int& numOfIntersect,
                                   AcGePoint3d& p1, AcGePoint3d& p2,
                                   const AcGeTol& tol = AcGeContext::gTol) const;

    // Projection-intersection with other geometric objects.
    Adesk::Boolean projIntersectWith (const AcGeLinearEnt3d& line,
                                      const AcGeVector3d& projDir, int& numInt,
                                      AcGePoint3d& pntOnArc1,
                                      AcGePoint3d& pntOnArc2,
                                      AcGePoint3d& pntOnLine1,
                                      AcGePoint3d& pntOnLine2,
                                      const AcGeTol& tol = AcGeContext::gTol) const;

    // Tangent to the circular arc.
    //
    Adesk::Boolean tangent        (const AcGePoint3d& pnt, AcGeLine3d& line,
                                   const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean tangent        (const AcGePoint3d& pnt, AcGeLine3d& line,
                                   const AcGeTol& tol, AcGeError& error) const;
		 // Possible error conditions:  kArg1TooBig, kArg1InsideThis, 
		 // kArg1OnThis, kThisIsInfiniteLine

    // Plane of the arc
    //
    void           getPlane       (AcGePlane& plane) const;

    // Test if point is inside circle.
    //
    Adesk::Boolean isInside       (const AcGePoint3d& pnt,
                                   const AcGeTol& tol = AcGeContext::gTol) const;

    // Definition of circular arc
    //
    AcGePoint3d    center         () const;
    AcGeVector3d   normal         () const;
    AcGeVector3d   refVec         () const;
    double         radius         () const;
    double         startAng       () const;
    double         endAng         () const;
    AcGePoint3d    startPoint     () const;
    AcGePoint3d    endPoint       () const;

    AcGeCircArc3d& setCenter      (const AcGePoint3d&);
    AcGeCircArc3d& setAxes        (const AcGeVector3d& normal,
                                   const AcGeVector3d& refVec);
    AcGeCircArc3d& setRadius      (double);
    AcGeCircArc3d& setAngles      (double startAngle, double endAngle);

    AcGeCircArc3d& set            (const AcGePoint3d& cent,
                                   const AcGeVector3d& nrm, double radius);
    AcGeCircArc3d& set            (const AcGePoint3d& cent,
                                   const AcGeVector3d& nrm,
                                   const AcGeVector3d& refVec, double radius,
                                   double startAngle, double endAngle);
    AcGeCircArc3d& set            (const AcGePoint3d& startPoint, const AcGePoint3d& pnt,
                                   const AcGePoint3d& endPoint);
    AcGeCircArc3d& set            (const AcGePoint3d& startPoint, const AcGePoint3d& pnt,
                                   const AcGePoint3d& endPoint, AcGeError& error);
			 // Possible errors:  kEqualArg1Arg2, kEqualArg1Arg3, kEqualArg2Arg3, 
			 // kLinearlyDependentArg1Arg2Arg3.
			 // Degenerate results: none.
			 // On error, the object is unchanged.

    AcGeCircArc3d& set            (const AcGeCurve3d& curve1,
                                   const AcGeCurve3d& curve2,
                                   double radius, double& param1, double& param2,
								   Adesk::Boolean& success);
		// On success, this arc becomes the fillet of the given radius between the two curves,
	    // whose points of tangency are nearest param1 and param2 respectively.
    AcGeCircArc3d& set            (const AcGeCurve3d& curve1,
                                   const AcGeCurve3d& curve2,
                                   const AcGeCurve3d& curve3,
                                   double& param1, double& param2, double& param3,
								   Adesk::Boolean& success);

    // Assignment operator.
    //
    AcGeCircArc3d& operator =     (const AcGeCircArc3d& arc);
};

#pragma pack (pop)
#endif
