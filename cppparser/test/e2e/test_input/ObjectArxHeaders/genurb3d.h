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
// This file contains the class AcGeNurbCurve3d - A mathematical entity
// used to represent a different types of spline curves in 3-space.

#ifndef AC_GENURB3D_H
#define AC_GENURB3D_H

#include "gecurv3d.h"
#include "geintrvl.h"
#include "gekvec.h"
#include "gept3dar.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "gesent3d.h"
#include "geplin3d.h"
#include "gedblar.h"
#include "gept3dar.h"
#include "gevc3dar.h"
#pragma pack (push, 8)

class AcGeEllipArc3d;
class AcGeLineSeg3d;

class 
GE_DLLEXPIMPORT
AcGeNurbCurve3d : public AcGeSplineEnt3d
{
public:
    // Construct spline from control points.
    //
    AcGeNurbCurve3d ();
    AcGeNurbCurve3d (const AcGeNurbCurve3d& src );
    AcGeNurbCurve3d (int degree, const AcGeKnotVector& knots,
                     const AcGePoint3dArray& cntrlPnts, 
                     Adesk::Boolean isPeriodic = Adesk::kFalse );
    AcGeNurbCurve3d (int degree, const AcGeKnotVector& knots,
                     const AcGePoint3dArray& cntrlPnts, 
                     const AcGeDoubleArray&  weights,
                     Adesk::Boolean isPeriodic = Adesk::kFalse );

    // Construct spline from interpolation data.
    //
    AcGeNurbCurve3d (int degree, const AcGePolyline3d& fitPolyline,
                     Adesk::Boolean isPeriodic = Adesk::kFalse );

    AcGeNurbCurve3d (const AcGePoint3dArray& fitPoints, 
                     const AcGeVector3d& startTangent, 
                     const AcGeVector3d& endTangent,
                     Adesk::Boolean startTangentDefined = Adesk::kTrue,
                     Adesk::Boolean endTangentDefined   = Adesk::kTrue,
                     const AcGeTol& fitTolerance = AcGeContext::gTol); 

    // specify the fitting points and the wanted knot parameterization
    AcGeNurbCurve3d (const AcGePoint3dArray& fitPoints, 
                     const AcGeVector3d& startTangent, 
                     const AcGeVector3d& endTangent,
                     Adesk::Boolean startTangentDefined,
                     Adesk::Boolean endTangentDefined,
                     AcGe::KnotParameterization knotParam,
                     const AcGeTol& fitTolerance = AcGeContext::gTol);

    AcGeNurbCurve3d (const AcGePoint3dArray& fitPoints, 
                     const AcGeTol& fitTolerance = AcGeContext::gTol);

    AcGeNurbCurve3d (const AcGePoint3dArray& fitPoints, 
                     const AcGeVector3dArray& fitTangents,
                     const AcGeTol& fitTolerance = AcGeContext::gTol,
                     Adesk::Boolean isPeriodic = Adesk::kFalse);   

    // Construct a cubic spline approximating the curve
    AcGeNurbCurve3d(const AcGeCurve3d& curve, 
                    double epsilon = AcGeContext::gTol.equalPoint());


    // Spline representation of ellipse
    //
    AcGeNurbCurve3d (const AcGeEllipArc3d&  ellipse);

    // Spline representation of line segment
    //
    AcGeNurbCurve3d (const AcGeLineSeg3d& linSeg);

    // Query methods.
    //
    int             numFitPoints      () const;
    Adesk::Boolean  getFitPointAt     (int index, AcGePoint3d& point) const;
    Adesk::Boolean  getFitTolerance   (AcGeTol& fitTolerance) const;
    Adesk::Boolean  getFitTangents    (AcGeVector3d& startTangent, 
                                       AcGeVector3d& endTangent) const;
    Adesk::Boolean  getFitTangents    (AcGeVector3d& startTangent, 
                                       AcGeVector3d& endTangent,
                                       Adesk::Boolean& startTangentDefined,
                                       Adesk::Boolean& endTangentDefined) const;
    Adesk::Boolean  getFitKnotParameterization(KnotParameterization& knotParam) const;
    Adesk::Boolean  getFitData        (AcGePoint3dArray& fitPoints,
                                       AcGeTol& fitTolerance,
                                       Adesk::Boolean& tangentsExist,
                                       AcGeVector3d& startTangent, 
                                       AcGeVector3d& endTangent) const;
    Adesk::Boolean  getFitData        (AcGePoint3dArray& fitPoints,
                                       AcGeTol& fitTolerance,
                                       Adesk::Boolean& tangentsExist,
                                       AcGeVector3d& startTangent, 
                                       AcGeVector3d& endTangent,
                                       KnotParameterization& knotParam) const;
    void            getDefinitionData (int& degree, Adesk::Boolean& rational,
                                       Adesk::Boolean& periodic,
                                       AcGeKnotVector& knots,
                                       AcGePoint3dArray& controlPoints,
                                       AcGeDoubleArray& weights) const;
    int             numWeights        () const;
    double          weightAt          (int idx) const;
    Adesk::Boolean  evalMode          () const;        
    Adesk::Boolean  getParamsOfC1Discontinuity (AcGeDoubleArray& params,
                                                const AcGeTol& tol 
                                                = AcGeContext::gTol) const;
    Adesk::Boolean  getParamsOfG1Discontinuity (AcGeDoubleArray& params,
                                                const AcGeTol& tol 
                                                = AcGeContext::gTol) const;

    // Modification methods.
    //
    Adesk::Boolean   setFitPointAt    (int index, const AcGePoint3d& point);
    Adesk::Boolean   addFitPointAt    (int index, const AcGePoint3d& point);
    Adesk::Boolean   deleteFitPointAt (int index);
    Adesk::Boolean   setFitTolerance  (const AcGeTol& fitTol=AcGeContext::gTol);
    Adesk::Boolean   setFitTangents   (const AcGeVector3d& startTangent, 
                                       const AcGeVector3d& endTangent);
    Adesk::Boolean   setFitTangents   (const AcGeVector3d& startTangent, 
                                       const AcGeVector3d& endTangent,
                                       Adesk::Boolean startTangentDefined,
                                       Adesk::Boolean endTangentDefined) const;
    Adesk::Boolean   setFitKnotParameterization(KnotParameterization knotParam);
    AcGeNurbCurve3d& setFitData       (const AcGePoint3dArray& fitPoints,                                             
                                       const AcGeVector3d& startTangent, 
                                       const AcGeVector3d& endTangent,
                                       const AcGeTol& fitTol=AcGeContext::gTol);
    AcGeNurbCurve3d& setFitData       (const AcGePoint3dArray& fitPoints,                                             
                                       const AcGeVector3d& startTangent, 
                                       const AcGeVector3d& endTangent,
                                       KnotParameterization knotParam,
                                       const AcGeTol& fitTol=AcGeContext::gTol);
    AcGeNurbCurve3d& setFitData       (const AcGeKnotVector& fitKnots,
                                       const AcGePoint3dArray& fitPoints,
                                       const AcGeVector3d& startTangent, 
                                       const AcGeVector3d& endTangent,                                         
                                       const AcGeTol& fitTol=AcGeContext::gTol,
                                       Adesk::Boolean isPeriodic=Adesk::kFalse);
    AcGeNurbCurve3d&  setFitData      (int degree, 
                                       const AcGePoint3dArray& fitPoints,
                                       const AcGeTol& fitTol=AcGeContext::gTol);
    Adesk::Boolean    purgeFitData    ();
    Adesk::Boolean    buildFitData    ();
    Adesk::Boolean    buildFitData    (KnotParameterization kp);
    AcGeNurbCurve3d&  addKnot         (double newKnot);
    AcGeNurbCurve3d&  insertKnot      (double newKnot);
    AcGeSplineEnt3d&  setWeightAt     (int idx, double val);
    AcGeNurbCurve3d&  setEvalMode     (Adesk::Boolean evalMode=Adesk::kFalse );
    AcGeNurbCurve3d&  joinWith        (const AcGeNurbCurve3d& curve);
    AcGeNurbCurve3d&  hardTrimByParams(double newStartParam, 
                                       double newEndParam);
    AcGeNurbCurve3d&  makeRational    (double weight = 1.0);
    AcGeNurbCurve3d&  makeClosed      ();
    AcGeNurbCurve3d&  makePeriodic    ();
    AcGeNurbCurve3d&  makeNonPeriodic ();
    AcGeNurbCurve3d&  makeOpen        ();
    AcGeNurbCurve3d&  elevateDegree   (int plusDegree);

    // add/remove control point.
    Adesk::Boolean    addControlPointAt(double newKnot, const AcGePoint3d& point, double weight = 1.0);
    Adesk::Boolean    deleteControlPointAt(int index);

    // Assignment operator.
    //
    AcGeNurbCurve3d&  operator =      (const AcGeNurbCurve3d& spline);
};

#pragma pack (pop)
#endif
