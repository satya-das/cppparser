
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _ACGI_DEFS_H
#define _ACGI_DEFS_H 1

#include "adesk.h"


// These are the current kinds of viewport regeneration modes.
// This mode is not settable by the user, but it can be queried 
// in case you need to take different actions for different
// regeneration modes.
//
typedef enum {
    eAcGiRegenTypeInvalid = 0,
    kAcGiStandardDisplay = 2,
    kAcGiHideOrShadeCommand,
    kAcGiRenderCommand, // deprecated
    kAcGiShadedDisplay = kAcGiRenderCommand,
    kAcGiForExplode,
    kAcGiSaveWorldDrawForProxy
} AcGiRegenType;

// No longer supported and will be removed
//
#define kAcGiSaveWorldDrawForR12 kAcGiForExplode 

// These are the current face filling modes
//
typedef enum {
     kAcGiFillAlways = 1,
     kAcGiFillNever
} AcGiFillType;

// These are the edge visibility types
//
typedef enum {
    kAcGiInvisible = 0,
    kAcGiVisible,
    kAcGiSilhouette
} AcGiVisibility;

// These are the types of arcs
//
typedef enum {
    kAcGiArcSimple = 0,                 // just the arc (not fillable)
    kAcGiArcSector,                     // area bounded by the arc and its center of curvature
    kAcGiArcChord                       // area bounded by the arc and its end points
} AcGiArcType;

// These are the possible types of vertex orientation 
// 
typedef enum {
    kAcGiCounterClockwise = -1,
    kAcGiNoOrientation = 0,
    kAcGiClockwise = 1
} AcGiOrientationType;

// This signifies how to calculate maximum deviation for tessellation
//
typedef enum {
    kAcGiMaxDevForCircle = 0,
    kAcGiMaxDevForCurve,
    kAcGiMaxDevForBoundary,
    kAcGiMaxDevForIsoline,
    kAcGiMaxDevForFacet
} AcGiDeviationType;

// Raster image organization
//
typedef enum {
    kAcGiBitonal,
    kAcGiPalette,
    kAcGiGray,
    kAcGiRGBA,
    kAcGiBGRA,
    kAcGiARGB,
    kAcGiABGR,
    kAcGiBGR,
    kAcGiRGB                              
} AcGiImageOrg;

// Raster image orientation
//
typedef enum {
    kAcGiXLeftToRightTopFirst,
    kAcGiXLeftToRightBottomFirst,
    kAcGiXRightToLeftTopFirst,
    kAcGiXRightToLeftBottomFirst,
    kAcGiYTopToBottomLeftFirst,
    kAcGiYTopToBottomRightFirst,
    kAcGiYBottomToTopLeftFirst,
    kAcGiYBottomToTopRightFirst
} AcGiImageOrient;

// scale filter method to use
typedef enum {
    kDefaultScaleFilter,
    kNearestScaleFilter,
    kBellScaleFilter,
    kMitchellScaleFilter,
    kTriangleScaleFilter,
    kCubicScaleFilter,
    kBsplineScaleFilter,
    kLanczos3ScaleFilter
} AcGiScaleFilterType;

// rotation filter method to use
typedef enum {
    kDefaultRotationFilter,
    kInterpolatedRotationFilter,
    kNearestRotationFilter,
} AcGiRotationFilterType;

// how to interpret nRasterRatio
typedef enum {
    kDefaultScale,                  // classic scaling scheme
    kRelativeScale,                 // relative to original image, do rotation
    kUnTransformedScale             // original pixels, unscaled, unrotated
} AcGiScaleType;

// highlight style
enum AcGiHighlightStyle { 
    kAcGiHighlightNone,
    kAcGiHighlightCustom,
    kAcGiHighlightDashedAndThicken,
    kAcGiHighlightDim,
    kAcGiHighlightThickDim,
    kAcGiHighlightGlow
};

enum AcGiEdgeStyleMaskValues {
    kAcGiNoEdgeStyleMask = 0,
    kAcGiJitterMask      = 1,
    kAcGiOverhangMask    = 2,
    kAcGiEdgeColorMask   = 4
};
typedef unsigned int AcGiEdgeStyleMask;



#endif
