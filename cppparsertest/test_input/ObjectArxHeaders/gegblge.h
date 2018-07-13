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
// Provides a namespace-like struct for gelib.
//
//

#ifndef AC_GEGBLGE_H
#define AC_GEGBLGE_H

#include "gelibver.h"
#pragma pack (push, 8)

struct
AcGe
{
    GE_DLLDATAEXIMP static const AcGeLibVersion gLibVersion;
    enum { eGood, eBad };

    enum EntityId {
        kEntity2d,
        kEntity3d,
        kPointEnt2d,
        kPointEnt3d,
        kPosition2d,
        kPosition3d,
        kPointOnCurve2d,
        kPointOnCurve3d,
        kPointOnSurface,
        kBoundedPlane,
        kCircArc2d,
        kCircArc3d,
        kConic2d,
        kConic3d,
        kCurve2d,
        kCurve3d,
        kEllipArc2d,
        kEllipArc3d,
        kLine2d,
        kLine3d,
        kLinearEnt2d,
        kLinearEnt3d,
        kLineSeg2d,
        kLineSeg3d,
        kPlanarEnt,
        kPlane,
        kRay2d,
        kRay3d,
        kSurface,
        kSphere,
        kCylinder,
        kTorus,
        kCone,
        kSplineEnt2d,
        kPolyline2d,
        kAugPolyline2d,
        kNurbCurve2d,
        kDSpline2d,
        kCubicSplineCurve2d,
        kSplineEnt3d,
        kPolyline3d,
        kAugPolyline3d,
        kNurbCurve3d,
        kDSpline3d,
        kCubicSplineCurve3d,
        kTrimmedCrv2d,
        kCompositeCrv2d,
        kCompositeCrv3d,
        kExternalSurface,
        kNurbSurface,
        kTrimmedSurface,
        kOffsetSurface,
        kEnvelope2d,
        kCurveBoundedSurface,
        kExternalCurve3d,
        kExternalCurve2d,
        kSurfaceCurve2dTo3d,
        kSurfaceCurve3dTo2d,
	    kExternalBoundedSurface,
        kCurveCurveInt2d,
        kCurveCurveInt3d,
	    kBoundBlock2d,
	    kBoundBlock3d,
        kOffsetCurve2d,
        kOffsetCurve3d,
        kPolynomCurve3d,
        kBezierCurve3d,
	    kObject,
	    kFitData3d,
        kHatch,
        kTrimmedCurve2d,
        kTrimmedCurve3d,
		kCurveSampleData,
		kEllipCone,
		kEllipCylinder,
		kIntervalBoundBlock,
		kClipBoundary2d,
		kExternalObject,
		kCurveSurfaceInt,
		kSurfaceSurfaceInt,
        kHelix
    };

    enum ExternalEntityKind {kAcisEntity= 0, kExternalEntityUndefined};

    enum PointContainment {kInside, kOutside, kOnBoundary};

    enum NurbSurfaceProperties {kOpen=0x01, kClosed=0x02, kPeriodic=0x04,
                                kRational=0x08, kNoPoles=0x10, kPoleAtMin=0x20,
                                kPoleAtMax=0x40, kPoleAtBoth=0x80};

    enum OffsetCrvExtType {kFillet, kChamfer, kExtend};

    enum AcGeXConfig
    {
        kNotDefined = 1 << 0,
        kUnknown = 1 << 1,
        kLeftRight = 1 << 2,
        kRightLeft = 1 << 3,
        kLeftLeft = 1 << 4,
        kRightRight = 1 << 5,
        kPointLeft = 1 << 6,
        kPointRight = 1 << 7,
        kLeftOverlap = 1 << 8,
        kOverlapLeft = 1 << 9,
        kRightOverlap = 1 << 10,
        kOverlapRight = 1 << 11,
        kOverlapStart = 1 << 12,
        kOverlapEnd = 1 << 13,
        kOverlapOverlap = 1 << 14
    };

    enum BooleanType {kUnion, kSubtract, kCommon};
    
	enum ClipError 
	{
        eOk, 
        eInvalidClipBoundary,
        eNotInitialized
    };

    enum ClipCondition 
	{
        kInvalid, 
        kAllSegmentsInside,
        kSegmentsIntersect,
        kAllSegmentsOutsideZeroWinds,
        kAllSegmentsOutsideOddWinds,
        kAllSegmentsOutsideEvenWinds
    };

	enum ErrorCondition 
	{ 
		kOk, 
		k0This,
		k0Arg1,
		k0Arg2, 
		kPerpendicularArg1Arg2,       
		kEqualArg1Arg2, 
		kEqualArg1Arg3, 
		kEqualArg2Arg3, 
		kLinearlyDependentArg1Arg2Arg3,
		kArg1TooBig,
		kArg1OnThis,
		kArg1InsideThis
	};

// Curve/surface intersection configuration.
// Categorize an intersection and categorize a neighborhood of the 
// curve just above or below the curve/surface intersection.  
// 'Above' and 'below' is with respect to the curve parameterization.
// If an intersection is not empty, coincident or tangent, it is transverse.
// 'Inside' and 'outside' the surface is with respect to its surface normal
// orientation.
enum csiConfig { 
  kXUnknown, 
  kXOut, 						// Transverse.  Curve neighborhood is outside the surface.
  kXIn,							 // Transverse.  Curve neighborhood is inside the surface.
  kXTanOut,					 // Tangent.  Curve neighborhood is outside the surface.
  kXTanIn,						//  Tangent.  Curve neighborhood is inside the surface.
  kXCoincident,					// Non-zero length.  Point is on the intersection boundary.
  kXCoincidentUnbounded	// Non-zero length.  Point is an arbitrary point on an unbounded intersection.
 };

// Categorize the surface/surface intersection component.
 enum ssiType {
  kSSITransverse,	// Non-tangent intersection.
  kSSITangent,		// Tangent intersection.  
                            // Surface normals identical at any point within the component.
  kSSIAntiTangent  // Tangent intersection.  
                            // Surface normals opposite at any point within the component.
  };

 // Surface/surface intersection configuration.
// Categorize the neighborhood of a surface just to the left or right of the
// surface/surface intersection curve with respect to the other surface.  
// Inside (outside) means that the neighborhood is inside (outside) the 
// other surface with respect to the surface normal orientation 
// of the other surface.
// The surface neighborhoods 'left' and 'right' of a curve on a surface
// are with respect to its surface normal orientation and the direction of
// the curve parameterization.
enum ssiConfig { 
  kSSIUnknown, 
  kSSIOut, 					 // Neighborhood is outside the surface.
  kSSIIn,					  // Neighborhood is inside the surface.
  kSSICoincident	     // Non-zero area intersection.
 };

enum AcGeIntersectError {
    kXXOk,
    kXXIndexOutOfRange,
    kXXWrongDimensionAtIndex,
    kXXUnknown
};

enum KnotParameterization {
    kChord = 0,
    kSqrtChord,
    kUniform,
    kCustomParameterization = 15,
    kNotDefinedKnotParam = 16
};

#pragma pack (pop)
#ifdef GE_LOCATED_NEW
#include "gemetatp.h"
#endif
};


#endif  // AC_GEGBLGE_H
