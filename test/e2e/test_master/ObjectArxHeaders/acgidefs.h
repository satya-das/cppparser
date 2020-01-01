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
#  define _ACGI_DEFS_H	1
#  include "adesk.h"
typedef enum
{
  eAcGiRegenTypeInvalid = 0,
  kAcGiStandardDisplay = 2,
  kAcGiHideOrShadeCommand,
  kAcGiRenderCommand,
  kAcGiShadedDisplay = kAcGiRenderCommand,
  kAcGiForExplode,
  kAcGiSaveWorldDrawForProxy
} AcGiRegenType;
#  define kAcGiSaveWorldDrawForR12	kAcGiForExplode 
typedef enum
{
  kAcGiFillAlways = 1,
  kAcGiFillNever
} AcGiFillType;
typedef enum
{
  kAcGiInvisible = 0,
  kAcGiVisible,
  kAcGiSilhouette
} AcGiVisibility;
typedef enum
{
  kAcGiArcSimple = 0,
  kAcGiArcSector,
  kAcGiArcChord
} AcGiArcType;
typedef enum
{
  kAcGiCounterClockwise = -1,
  kAcGiNoOrientation = 0,
  kAcGiClockwise = 1
} AcGiOrientationType;
typedef enum
{
  kAcGiMaxDevForCircle = 0,
  kAcGiMaxDevForCurve,
  kAcGiMaxDevForBoundary,
  kAcGiMaxDevForIsoline,
  kAcGiMaxDevForFacet
} AcGiDeviationType;
typedef enum
{
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
typedef enum
{
  kAcGiXLeftToRightTopFirst,
  kAcGiXLeftToRightBottomFirst,
  kAcGiXRightToLeftTopFirst,
  kAcGiXRightToLeftBottomFirst,
  kAcGiYTopToBottomLeftFirst,
  kAcGiYTopToBottomRightFirst,
  kAcGiYBottomToTopLeftFirst,
  kAcGiYBottomToTopRightFirst
} AcGiImageOrient;
typedef enum
{
  kDefaultScaleFilter,
  kNearestScaleFilter,
  kBellScaleFilter,
  kMitchellScaleFilter,
  kTriangleScaleFilter,
  kCubicScaleFilter,
  kBsplineScaleFilter,
  kLanczos3ScaleFilter
} AcGiScaleFilterType;
typedef enum
{
  kDefaultRotationFilter,
  kInterpolatedRotationFilter,
  kNearestRotationFilter
} AcGiRotationFilterType;
typedef enum
{
  kDefaultScale,
  kRelativeScale,
  kUnTransformedScale
} AcGiScaleType;
enum AcGiHighlightStyle
{
  kAcGiHighlightNone,
  kAcGiHighlightCustom,
  kAcGiHighlightDashedAndThicken,
  kAcGiHighlightDim,
  kAcGiHighlightThickDim,
  kAcGiHighlightGlow
};
enum AcGiEdgeStyleMaskValues
{
  kAcGiNoEdgeStyleMask = 0,
  kAcGiJitterMask = 1,
  kAcGiOverhangMask = 2,
  kAcGiEdgeColorMask = 4
};
typedef unsigned int AcGiEdgeStyleMask;
#endif
