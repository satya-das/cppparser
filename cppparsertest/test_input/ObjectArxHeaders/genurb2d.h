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
// This file contains the class AcGeNurbCurve2d - A mathematical entity
// used to represent a different types of spline curves in 2-space.

#ifndef AC_GENURB2d_H
#define AC_GENURB2d_H

#include "gecurv2d.h"
#include "geintrvl.h"
#include "gekvec.h"
#include "gept2dar.h"
#include "gevec2d.h"
#include "gepnt2d.h"
#include "gesent2d.h"
#include "geplin2d.h"
#include "gedblar.h"
#include "gept2dar.h"
#include "gevc2dar.h"
#pragma pack (push, 8)

class AcGeEllipArc2d;
class AcGeLineSeg2d;

class 
GE_DLLEXPIMPORT
AcGeNurbCurve2d : public AcGeSplineEnt2d
{
public:
    // Construct spline from control points.
	//
    AcGeNurbCurve2d ();
    AcGeNurbCurve2d (const AcGeNurbCurve2d& src );
    AcGeNurbCurve2d (int degree, const AcGeKnotVector& knots,
                     const AcGePoint2dArray& cntrlPnts, 
                     Adesk::Boolean isPeriodic = Adesk::kFalse );
    AcGeNurbCurve2d (int degree, const AcGeKnotVector& knots,
                     const AcGePoint2dArray& cntrlPnts, 
                     const AcGeDoubleArray&  weights,
                     Adesk::Boolean isPeriodic = Adesk::kFalse );

    // Construct spline from interpolation data.
    //
    AcGeNurbCurve2d (int degree, const AcGePolyline2d& fitPolyline,
                     Adesk::Boolean isPeriodic = Adesk::kFalse );

    AcGeNurbCurve2d (const AcGePoint2dArray& fitPoints, 
				     const AcGeVector2d& startTangent, 
				     const AcGeVector2d& endTangent,
				     Adesk::Boolean startTangentDefined = Adesk::kTrue,
					 Adesk::Boolean endTangentDefined   = Adesk::kTrue,
				     const AcGeTol& fitTolerance = AcGeContext::gTol);

    // specify the fitting points and the wanted knot parameterization
    AcGeNurbCurve2d (const AcGePoint2dArray& fitPoints, 
				     const AcGeVector2d& startTangent, 
				     const AcGeVector2d& endTangent,
				     Adesk::Boolean startTangentDefined,
					 Adesk::Boolean endTangentDefined,
                     AcGe::KnotParameterization knotParam,
				     const AcGeTol& fitTolerance = AcGeContext::gTol);

    AcGeNurbCurve2d (const AcGePoint2dArray& fitPoints, 
				     const AcGeTol& fitTolerance = AcGeContext::gTol);

    AcGeNurbCurve2d (const AcGePoint2dArray& fitPoints, 
                     const AcGeVector2dArray& fitTangents,
				     const AcGeTol& fitTolerance = AcGeContext::gTol,
				     Adesk::Boolean isPeriodic = Adesk::kFalse);
    
    // Spline representation of ellipse
	//
	AcGeNurbCurve2d (const AcGeEllipArc2d&  ellipse);

    // Spline representation of line segment
	//
	AcGeNurbCurve2d (const AcGeLineSeg2d& linSeg);

    // Construct a cubic spline approximating the curve
    AcGeNurbCurve2d(const AcGeCurve2d& curve, 
                    double epsilon = AcGeContext::gTol.equalPoint());

	// Query methods.
	//
    int             numFitPoints      () const;
    Adesk::Boolean  getFitPointAt     (int index, AcGePoint2d& point) const;
    Adesk::Boolean  getFitTolerance   (AcGeTol& fitTolerance) const;
    Adesk::Boolean  getFitTangents    (AcGeVector2d& startTangent, 
				                       AcGeVector2d& endTangent) const;
    Adesk::Boolean  getFitKnotParameterization(KnotParameterization& knotParam) const;
    Adesk::Boolean  getFitData        (AcGePoint2dArray& fitPoints,
		                               AcGeTol& fitTolerance,
				                       Adesk::Boolean& tangentsExist,
				                       AcGeVector2d& startTangent, 
				                       AcGeVector2d& endTangent) const;
    Adesk::Boolean  getFitData        (AcGePoint2dArray& fitPoints,
		                               AcGeTol& fitTolerance,
				                       Adesk::Boolean& tangentsExist,
				                       AcGeVector2d& startTangent, 
				                       AcGeVector2d& endTangent,
                                       KnotParameterization& knotParam) const;
    void            getDefinitionData (int& degree, Adesk::Boolean& rational,
								       Adesk::Boolean& periodic,
			                           AcGeKnotVector& knots,
			                           AcGePoint2dArray& controlPoints,
			                           AcGeDoubleArray& weights) const;
    int             numWeights        () const;
    double          weightAt          (int idx) const;
    Adesk::Boolean  evalMode          () const;        
	Adesk::Boolean  getParamsOfC1Discontinuity (AcGeDoubleArray& params,
				                                const AcGeTol& tol 
					                            = AcGeContext::gTol) const;
	Adesk::Boolean	getParamsOfG1Discontinuity (AcGeDoubleArray& params,
					                            const AcGeTol& tol 
					                            = AcGeContext::gTol) const;

	// Modification methods.
	//
    Adesk::Boolean   setFitPointAt    (int index, const AcGePoint2d& point);
    Adesk::Boolean   addFitPointAt    (int index, const AcGePoint2d& point);
    Adesk::Boolean   deleteFitPointAt (int index);
    Adesk::Boolean   setFitTolerance  (const AcGeTol& fitTol=AcGeContext::gTol);
    Adesk::Boolean   setFitTangents   (const AcGeVector2d& startTangent, 
	                        	       const AcGeVector2d& endTangent);
    Adesk::Boolean   setFitKnotParameterization(KnotParameterization knotParam);
    AcGeNurbCurve2d& setFitData       (const AcGePoint2dArray& fitPoints,                                             
				                       const AcGeVector2d& startTangent, 
				                       const AcGeVector2d& endTangent,
				                       const AcGeTol& fitTol=AcGeContext::gTol);
    AcGeNurbCurve2d& setFitData       (const AcGePoint2dArray& fitPoints,                                             
				                       const AcGeVector2d& startTangent, 
				                       const AcGeVector2d& endTangent,
                                       KnotParameterization knotParam,
				                       const AcGeTol& fitTol=AcGeContext::gTol);
    AcGeNurbCurve2d& setFitData       (const AcGeKnotVector& fitKnots,
		                               const AcGePoint2dArray& fitPoints,
				                       const AcGeVector2d& startTangent, 
				                       const AcGeVector2d& endTangent,										 
                        			   const AcGeTol& fitTol=AcGeContext::gTol,
				                       Adesk::Boolean isPeriodic=Adesk::kFalse);
    AcGeNurbCurve2d&  setFitData      (int degree, 
                                       const AcGePoint2dArray& fitPoints,
				                       const AcGeTol& fitTol=AcGeContext::gTol);
    Adesk::Boolean    purgeFitData    ();
    Adesk::Boolean    buildFitData    ();
    Adesk::Boolean    buildFitData    (KnotParameterization kp);
    AcGeNurbCurve2d&  addKnot         (double newKnot);
    AcGeNurbCurve2d&  insertKnot      (double newKnot);
    AcGeSplineEnt2d&  setWeightAt     (int idx, double val);
    AcGeNurbCurve2d&  setEvalMode     (Adesk::Boolean evalMode=Adesk::kFalse );
	AcGeNurbCurve2d&  joinWith        (const AcGeNurbCurve2d& curve);
	AcGeNurbCurve2d&  hardTrimByParams(double newStartParam, 
		                               double newEndParam);
    AcGeNurbCurve2d&  makeRational    (double weight = 1.0);
    AcGeNurbCurve2d&  makeClosed      ();
    AcGeNurbCurve2d&  makePeriodic    ();
    AcGeNurbCurve2d&  makeNonPeriodic ();
    AcGeNurbCurve2d&  makeOpen        ();
    AcGeNurbCurve2d&  elevateDegree   (int plusDegree);

    // add/remove control point.
    Adesk::Boolean    addControlPointAt(double newKnot, const AcGePoint2d& point, double weight = 1.0);
    Adesk::Boolean    deleteControlPointAt(int index);

    // Assignment operator.
    //
    AcGeNurbCurve2d&  operator =      (const AcGeNurbCurve2d& spline);
};

#pragma pack (pop)
#endif
