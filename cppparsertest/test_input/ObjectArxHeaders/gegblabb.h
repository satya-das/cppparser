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
// Using the fully qualified names from the `AcGe' struct can be
// cumbersome.  If there are no global name conflicts use the
// following synonyms for convenience.
//
// Note:  All interface descriptions must use fully qualified names.
//        That is, header files MUST NOT include this file and MUST
//        NOT use these abbreviations.
//
// Note:  If any of the following abbreviations cause conflicts and
//        this file cannot be included, then the acceptable abbreviations
//        (those that do not cause conflicts) will have to be manually
//        introduced, or another abbreviation header file will have to
//        be created containing only the acceptable abbreviations.
//
// Note:  When this file is included in a source file, it MUST BE
//        included AFTER all other include files (except possibly
//        other abbreviation include files).
//        For example:
//            #include "foo.h"
//            #include "bar.h"
//            #include "gegblabb.h" // <- Must be last!

#ifndef AC_GEGBLABB_H
#define AC_GEGBLABB_H

#include "gegbl.h"

const int eGood = AcGe::eGood;
const int eBad = AcGe::eBad;

typedef AcGe::EntityId EntityId;

const AcGe::EntityId kEntity2d = AcGe::kEntity2d;
const AcGe::EntityId kEntity3d = AcGe::kEntity3d;
const AcGe::EntityId kPointEnt2d = AcGe::kPointEnt2d;
const AcGe::EntityId kPointEnt3d = AcGe::kPointEnt3d;
const AcGe::EntityId kPosition2d = AcGe::kPosition2d;
const AcGe::EntityId kPosition3d = AcGe::kPosition3d;
const AcGe::EntityId kPointOnCurve2d = AcGe::kPointOnCurve2d;
const AcGe::EntityId kPointOnCurve3d = AcGe::kPointOnCurve3d;
const AcGe::EntityId kBoundedPlane = AcGe::kBoundedPlane;
const AcGe::EntityId kCircArc2d = AcGe::kCircArc2d;
const AcGe::EntityId kCircArc3d = AcGe::kCircArc3d;
const AcGe::EntityId kConic2d = AcGe::kConic2d;
const AcGe::EntityId kConic3d = AcGe::kConic3d;
const AcGe::EntityId kCurve2d = AcGe::kCurve2d;
const AcGe::EntityId kCurve3d = AcGe::kCurve3d;
const AcGe::EntityId kEllipArc2d = AcGe::kEllipArc2d;
const AcGe::EntityId kEllipArc3d = AcGe::kEllipArc3d;
const AcGe::EntityId kHelix = AcGe::kHelix;
const AcGe::EntityId kLine2d = AcGe::kLine2d;
const AcGe::EntityId kLine3d = AcGe::kLine3d;
const AcGe::EntityId kLinearEnt2d = AcGe::kLinearEnt2d;
const AcGe::EntityId kLinearEnt3d = AcGe::kLinearEnt3d;
const AcGe::EntityId kLineSeg2d = AcGe::kLineSeg2d;
const AcGe::EntityId kLineSeg3d = AcGe::kLineSeg3d;
const AcGe::EntityId kPlanarEnt = AcGe::kPlanarEnt;
const AcGe::EntityId kExternalCurve3d = AcGe::kExternalCurve3d;
const AcGe::EntityId kExternalCurve2d = AcGe::kExternalCurve2d;
const AcGe::EntityId kPlane = AcGe::kPlane;
const AcGe::EntityId kRay2d = AcGe::kRay2d;
const AcGe::EntityId kRay3d = AcGe::kRay3d;
const AcGe::EntityId kSurface = AcGe::kSurface;
const AcGe::EntityId kSphere = AcGe::kSphere;
const AcGe::EntityId kCone = AcGe::kCone;
const AcGe::EntityId kTorus = AcGe::kTorus;
const AcGe::EntityId kCylinder = AcGe::kCylinder;
const AcGe::EntityId kSplineEnt2d = AcGe::kSplineEnt2d;
const AcGe::EntityId kSurfaceCurve2dTo3d = AcGe::kSurfaceCurve2dTo3d;
const AcGe::EntityId kSurfaceCurve3dTo2d = AcGe::kSurfaceCurve3dTo2d;

const AcGe::EntityId kPolyline2d = AcGe::kPolyline2d;
const AcGe::EntityId kAugPolyline2d = AcGe::kAugPolyline2d;
const AcGe::EntityId kNurbCurve2d = AcGe::kNurbCurve2d;
const AcGe::EntityId kDSpline2d = AcGe::kDSpline2d;
const AcGe::EntityId kCubicSplineCurve2d = AcGe::kCubicSplineCurve2d;
const AcGe::EntityId kSplineEnt3d = AcGe::kSplineEnt3d;
const AcGe::EntityId kPolyline3d = AcGe::kPolyline3d;
const AcGe::EntityId kAugPolyline3d = AcGe::kAugPolyline3d;
const AcGe::EntityId kNurbCurve3d = AcGe::kNurbCurve3d;
const AcGe::EntityId kDSpline3d = AcGe::kDSpline3d;
const AcGe::EntityId kCubicSplineCurve3d = AcGe::kCubicSplineCurve3d;
const AcGe::EntityId kTrimmedCrv2d = AcGe::kTrimmedCrv2d;
const AcGe::EntityId kCompositeCrv2d = AcGe::kCompositeCrv2d;
const AcGe::EntityId kCompositeCrv3d = AcGe::kCompositeCrv3d;
const AcGe::EntityId kEnvelope2d = AcGe::kEnvelope2d;

const AcGe::EntityId kExternalSurface = AcGe::kExternalSurface;
const AcGe::EntityId kNurbSurface = AcGe::kNurbSurface;
const AcGe::EntityId kOffsetSurface = AcGe::kOffsetSurface;
const AcGe::EntityId kTrimmedSurface = AcGe::kTrimmedSurface;
const AcGe::EntityId kCurveBoundedSurface = AcGe::kCurveBoundedSurface;
const AcGe::EntityId kPointOnSurface = AcGe::kPointOnSurface;
const AcGe::EntityId kExternalBoundedSurface = AcGe::kExternalBoundedSurface;
const AcGe::EntityId kCurveCurveInt2d = AcGe::kCurveCurveInt2d;
const AcGe::EntityId kCurveCurveInt3d = AcGe::kCurveCurveInt3d;
const AcGe::EntityId kBoundBlock2d = AcGe::kBoundBlock2d;
const AcGe::EntityId kBoundBlock3d = AcGe::kBoundBlock3d;
const AcGe::EntityId kOffsetCurve2d = AcGe::kOffsetCurve2d;
const AcGe::EntityId kOffsetCurve3d = AcGe::kOffsetCurve3d;
const AcGe::EntityId kPolynomCurve3d = AcGe::kPolynomCurve3d;
const AcGe::EntityId kBezierCurve3d = AcGe::kBezierCurve3d;
const AcGe::EntityId kObject = AcGe::kObject;
const AcGe::EntityId kFitData3d = AcGe::kFitData3d;
const AcGe::EntityId kHatch = AcGe::kHatch;
const AcGe::EntityId kTrimmedCurve2d = AcGe::kTrimmedCurve2d;
const AcGe::EntityId kTrimmedCurve3d = AcGe::kTrimmedCurve3d;
const AcGe::EntityId kCurveSampleData = AcGe::kCurveSampleData;

const AcGe::EntityId kEllipCone = AcGe::kEllipCone;
const AcGe::EntityId kEllipCylinder = AcGe::kEllipCylinder;
const AcGe::EntityId kIntervalBoundBlock = AcGe::kIntervalBoundBlock;
const AcGe::EntityId kClipBoundary2d = AcGe::kClipBoundary2d;
const AcGe::EntityId kExternalObject = AcGe::kExternalObject;
const AcGe::EntityId kCurveSurfaceInt = AcGe::kCurveSurfaceInt;
const AcGe::EntityId kSurfaceSurfaceInt = AcGe::kSurfaceSurfaceInt;


typedef AcGe::ExternalEntityKind ExternalEntityKind;

const AcGe::ExternalEntityKind kAcisEntity = AcGe::kAcisEntity;
const AcGe::ExternalEntityKind kExternalEntityUndefined
                                = AcGe::kExternalEntityUndefined;

typedef AcGe::NurbSurfaceProperties NurbSurfaceProperties;

const AcGe::NurbSurfaceProperties kOpen = AcGe::kOpen;
const AcGe::NurbSurfaceProperties kClosed = AcGe::kClosed;
const AcGe::NurbSurfaceProperties kPeriodic = AcGe::kPeriodic;
const AcGe::NurbSurfaceProperties kRational = AcGe::kRational;
const AcGe::NurbSurfaceProperties kNoPoles= AcGe::kNoPoles;
const AcGe::NurbSurfaceProperties kPoleAtMin = AcGe::kPoleAtMin;
const AcGe::NurbSurfaceProperties kPoleAtMax = AcGe::kPoleAtMax;
const AcGe::NurbSurfaceProperties kPoleAtBoth = AcGe::kPoleAtBoth;

typedef AcGe::PointContainment PointContainment;

const AcGe::PointContainment kInside = AcGe::kInside;
const AcGe::PointContainment kOutside = AcGe::kOutside;
const AcGe::PointContainment kOnBoundary = AcGe::kOnBoundary;

typedef AcGe::AcGeXConfig AcGeXConfig;

const AcGe::AcGeXConfig kNotDefined = AcGe::kNotDefined;
const AcGe::AcGeXConfig kUnknown = AcGe::kUnknown;
const AcGe::AcGeXConfig kLeftRight = AcGe::kLeftRight;
const AcGe::AcGeXConfig kRightLeft = AcGe::kRightLeft;
const AcGe::AcGeXConfig kLeftLeft = AcGe::kLeftLeft;
const AcGe::AcGeXConfig kRightRight = AcGe::kRightRight;
const AcGe::AcGeXConfig kPointLeft = AcGe::kPointLeft;
const AcGe::AcGeXConfig kPointRight = AcGe::kPointRight;
const AcGe::AcGeXConfig kLeftOverlap = AcGe::kLeftOverlap;
const AcGe::AcGeXConfig kOverlapLeft = AcGe::kOverlapLeft;
const AcGe::AcGeXConfig kRightOverlap = AcGe::kRightOverlap;
const AcGe::AcGeXConfig kOverlapRight = AcGe::kOverlapRight;
const AcGe::AcGeXConfig kOverlapStart = AcGe::kOverlapStart;
const AcGe::AcGeXConfig kOverlapEnd = AcGe::kOverlapEnd;
const AcGe::AcGeXConfig kOverlapOverlap = AcGe::kOverlapOverlap;

typedef AcGe::ErrorCondition  AcGeError;
 
const AcGe::ErrorCondition	kOk = AcGe::kOk;
const AcGe::ErrorCondition	k0This = AcGe::k0This;
const AcGe::ErrorCondition	k0Arg1 = AcGe::k0Arg1;
const AcGe::ErrorCondition	k0Arg2 = AcGe::k0Arg2;
const AcGe::ErrorCondition	kPerpendicularArg1Arg2 = AcGe::kPerpendicularArg1Arg2;     
const AcGe::ErrorCondition	kEqualArg1Arg2 = AcGe::kEqualArg1Arg2;
const AcGe::ErrorCondition	kEqualArg1Arg3 = AcGe::kEqualArg1Arg3;
const AcGe::ErrorCondition	kEqualArg2Arg3 = AcGe::kEqualArg2Arg3;
const AcGe::ErrorCondition	kLinearlyDependentArg1Arg2Arg3 = AcGe::kLinearlyDependentArg1Arg2Arg3;
const AcGe::ErrorCondition	kArg1TooBig = AcGe::kArg1TooBig;
const AcGe::ErrorCondition	kArg1OnThis = AcGe::kArg1OnThis;
const AcGe::ErrorCondition	kArg1InsideThis = AcGe::kArg1InsideThis;

typedef AcGe::AcGeIntersectError AcGeIntersectError;

const AcGe::AcGeIntersectError kXXOk = AcGe::kXXOk;
const AcGe::AcGeIntersectError kXXIndexOutOfRange = AcGe::kXXIndexOutOfRange;
const AcGe::AcGeIntersectError kXXWrongDimensionAtIndex = AcGe::kXXWrongDimensionAtIndex;
const AcGe::AcGeIntersectError kXXUnknown = AcGe::kXXUnknown;

typedef AcGe::KnotParameterization KnotParameterization;

const AcGe::KnotParameterization kChord = AcGe::kChord;
const AcGe::KnotParameterization kSqrtChord = AcGe::kSqrtChord;
const AcGe::KnotParameterization kUniform = AcGe::kUniform;
const AcGe::KnotParameterization kCustomParameterization = AcGe::kCustomParameterization;
const AcGe::KnotParameterization kNotDefinedKnotParam = AcGe::kNotDefinedKnotParam;

#endif
