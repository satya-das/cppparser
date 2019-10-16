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
enum AcGiRegenType
{
  eAcGiRegenTypeInvalid = 0,
  kAcGiStandardDisplay = 2,
  kAcGiHideOrShadeCommand,
  kAcGiRenderCommand,
  kAcGiShadedDisplay = kAcGiRenderCommand,
  kAcGiForExplode,
  kAcGiSaveWorldDrawForProxy
};
#  define kAcGiSaveWorldDrawForR12	kAcGiForExplode 
enum AcGiFillType
{
  kAcGiFillAlways = 1,
  kAcGiFillNever
};
enum AcGiVisibility
{
  kAcGiInvisible = 0,
  kAcGiVisible,
  kAcGiSilhouette
};
enum AcGiArcType
{
  kAcGiArcSimple = 0,
  kAcGiArcSector,
  kAcGiArcChord
};
enum AcGiOrientationType
{
  kAcGiCounterClockwise = -1,
  kAcGiNoOrientation = 0,
  kAcGiClockwise = 1
};
enum AcGiDeviationType
{
  kAcGiMaxDevForCircle = 0,
  kAcGiMaxDevForCurve,
  kAcGiMaxDevForBoundary,
  kAcGiMaxDevForIsoline,
  kAcGiMaxDevForFacet
};
enum AcGiImageOrg
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
};
enum AcGiImageOrient
{
  kAcGiXLeftToRightTopFirst,
  kAcGiXLeftToRightBottomFirst,
  kAcGiXRightToLeftTopFirst,
  kAcGiXRightToLeftBottomFirst,
  kAcGiYTopToBottomLeftFirst,
  kAcGiYTopToBottomRightFirst,
  kAcGiYBottomToTopLeftFirst,
  kAcGiYBottomToTopRightFirst
};
enum AcGiScaleFilterType
{
  kDefaultScaleFilter,
  kNearestScaleFilter,
  kBellScaleFilter,
  kMitchellScaleFilter,
  kTriangleScaleFilter,
  kCubicScaleFilter,
  kBsplineScaleFilter,
  kLanczos3ScaleFilter
};
enum AcGiRotationFilterType
{
  kDefaultRotationFilter,
  kInterpolatedRotationFilter,
  kNearestRotationFilter
};
enum AcGiScaleType
{
  kDefaultScale,
  kRelativeScale,
  kUnTransformedScale
};
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
