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
// This file contains the class AcGeCurve2d - An abstract base class
// from which all 2d curves are derived.

#ifndef AC_GECURV2D_H
#define AC_GECURV2D_H

#include "adesk.h"
#include "geent2d.h"
#include "geponc2d.h"
#include "gept2dar.h"
#include "gevc2dar.h"
#include "gedblar.h"
#include "gevptar.h"
#include "geintarr.h"
#pragma pack (push, 8)

class AcGePoint2d;
class AcGeVector2d;
class AcGePointOnCurve2d;
class AcGeInterval;
class AcGeMatrix2d;
class AcGeLine2d;
class AcGePointOnCurve2dData;
class AcGeBoundBlock2d;

class
GE_DLLEXPIMPORT
AcGeCurve2d : public AcGeEntity2d
{
public:

    // Parametrization.
    //
    void           getInterval(AcGeInterval& intrvl) const;
    void           getInterval(AcGeInterval& intrvl, AcGePoint2d& start,
			                   AcGePoint2d& end) const;
    AcGeCurve2d&   reverseParam();
	AcGeCurve2d&   setInterval();
	Adesk::Boolean setInterval(const AcGeInterval& intrvl);

    // Distance to other geometric objects.
    //
    double         distanceTo(const AcGePoint2d& pnt,
                              const AcGeTol& = AcGeContext::gTol) const;
    double         distanceTo(const AcGeCurve2d&,
                              const AcGeTol& tol = AcGeContext::gTol) const;

    // Return the point on this object that is closest to the other object.
    // These methods return point on this curve as a simple 2d point.
    //
    AcGePoint2d closestPointTo(const AcGePoint2d& pnt,
                               const AcGeTol& tol = AcGeContext::gTol) const;
    AcGePoint2d closestPointTo(const AcGeCurve2d& curve2d,
                               AcGePoint2d& pntOnOtherCrv,
                               const AcGeTol& tol= AcGeContext::gTol) const;


    // Alternate signatures for above functions.  These methods return point
    // on this curve as an AcGePointOnCurve2d.
    //
    void getClosestPointTo(const AcGePoint2d& pnt,
                           AcGePointOnCurve2d& pntOnCrv,
                           const AcGeTol& tol = AcGeContext::gTol) const;
    void getClosestPointTo(const AcGeCurve2d& curve2d,
                           AcGePointOnCurve2d& pntOnThisCrv,
                           AcGePointOnCurve2d& pntOnOtherCrv,
                           const AcGeTol& tol = AcGeContext::gTol) const;

    // Return point on curve whose normal vector passes thru input point.
    // Second parameter contains initial guess value and also contains output point.
    // Returns true or false depending on whether a normal point was found.
    //
    Adesk::Boolean getNormalPoint (const AcGePoint2d& pnt,
	                           AcGePointOnCurve2d& pntOnCrv,
                                   const AcGeTol& tol = AcGeContext::gTol) const;

    // Tests if point is on curve.
    //
    Adesk::Boolean isOn(const AcGePoint2d& pnt,
                        const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isOn(const AcGePoint2d& pnt, double& param,
                        const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isOn(double param,
                        const AcGeTol& tol = AcGeContext::gTol) const;

    // Parameter of the point on curve.  Contract: point IS on curve
    //
    double         paramOf(const AcGePoint2d& pnt,
                           const AcGeTol& tol = AcGeContext::gTol) const;

        // Return the offset of the curve.
        //
	void           getTrimmedOffset (double distance,
									 AcGeVoidPointerArray& offsetCurveList,
									 AcGe::OffsetCrvExtType extensionType = AcGe::kFillet,
                                     const AcGeTol& = AcGeContext::gTol) const;

    // Geometric inquiry methods.
    //
    Adesk::Boolean isClosed  (const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isPeriodic(double& period) const;
    Adesk::Boolean isLinear  (AcGeLine2d& line,
                              const AcGeTol& tol = AcGeContext::gTol) const;

    // Length based methods.
    //
    double         length       (double fromParam, double toParam,
                                 double tol = AcGeContext::gTol.equalPoint()) const;
    double         paramAtLength(double datumParam, double length,
                                 Adesk::Boolean posParamDir = Adesk::kTrue,
                                 double tol = AcGeContext::gTol.equalPoint()) const;
    Adesk::Boolean area         (double startParam, double endParam,
                                 double& value,
                                 const AcGeTol& tol = AcGeContext::gTol) const;

    // Degeneracy.
    //
    Adesk::Boolean isDegenerate(AcGe::EntityId& degenerateType,
                                const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isDegenerate(AcGeEntity2d*& pConvertedEntity,
                                const AcGeTol& tol = AcGeContext::gTol) const;

    // Modify methods.
    //
    void           getSplitCurves (double param, AcGeCurve2d* & piece1,
                                   AcGeCurve2d* & piece2) const;

	// Explode curve into its component sub-curves.
	//
	Adesk::Boolean explode      (AcGeVoidPointerArray& explodedCurves,
	                             AcGeIntArray& newExplodedCurve,
				     const AcGeInterval* intrvl = NULL ) const;

    // Local closest points
    //
    void getLocalClosestPoints(const AcGePoint2d& point,
                               AcGePointOnCurve2d& approxPnt,
                               const AcGeInterval* nbhd = 0,
                               const AcGeTol& = AcGeContext::gTol) const;
    void getLocalClosestPoints(const AcGeCurve2d& otherCurve,
                               AcGePointOnCurve2d& approxPntOnThisCrv,
                               AcGePointOnCurve2d& approxPntOnOtherCrv,
                               const AcGeInterval* nbhd1 = 0,
                               const AcGeInterval* nbhd2 = 0,
                               const AcGeTol& tol = AcGeContext::gTol) const;

    // Return oriented bounding box of curve.
    //
    AcGeBoundBlock2d  boundBlock() const;
    AcGeBoundBlock2d  boundBlock(const AcGeInterval& range) const;

    // Return bounding box whose sides are parallel to coordinate axes.
    //
    AcGeBoundBlock2d  orthoBoundBlock() const;
    AcGeBoundBlock2d  orthoBoundBlock(const AcGeInterval& range) const;

    // Return start and end points.
    //
    Adesk::Boolean hasStartPoint(AcGePoint2d& startPoint) const;
    Adesk::Boolean hasEndPoint  (AcGePoint2d& endPoint) const;

    // Evaluate methods.
    //
    AcGePoint2d    evalPoint(double param) const;
    AcGePoint2d    evalPoint(double param, int numDeriv,
                             AcGeVector2dArray& derivArray) const;

    // Polygonize curve to within a specified tolerance.
    //
    void     getSamplePoints(double fromParam, double toParam,
                             double approxEps, AcGePoint2dArray& pointArray,
			     AcGeDoubleArray& paramArray) const;
    void     getSamplePoints(int numSample, AcGePoint2dArray&) const;

    // Assignment operator.
    //
    AcGeCurve2d&   operator =  (const AcGeCurve2d& curve);

protected:

    // Private constructors so that no object of this class can be instantiated.
    AcGeCurve2d ();
    AcGeCurve2d (const AcGeCurve2d&);
};

#pragma pack (pop)
#endif
