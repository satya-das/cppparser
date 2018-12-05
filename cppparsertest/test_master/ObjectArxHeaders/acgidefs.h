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
// These are the current kinds of viewport regeneration modes.
// This mode is not settable by the user, but it can be queried 
// in case you need to take different actions for different
// regeneration modes.
//
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
// No longer supported and will be removed
//
#  define kAcGiSaveWorldDrawForR12	kAcGiForExplode 
// These are the current face filling modes
//
enum AcGiFillType
{
  kAcGiFillAlways = 1,
  kAcGiFillNever
};
// These are the edge visibility types
//
enum AcGiVisibility
{
  kAcGiInvisible = 0,
  kAcGiVisible,
  kAcGiSilhouette
};
// These are the types of arcs
//
enum AcGiArcType
{
  kAcGiArcSimple = 0,
  kAcGiArcSector,
  kAcGiArcChord
};
// These are the possible types of vertex orientation 
// 
enum AcGiOrientationType
{
  kAcGiCounterClockwise = -1,
  kAcGiNoOrientation = 0,
  kAcGiClockwise = 1
};
// This signifies how to calculate maximum deviation for tessellation
//
enum AcGiDeviationType
{
  kAcGiMaxDevForCircle = 0,
  kAcGiMaxDevForCurve,
  kAcGiMaxDevForBoundary,
  kAcGiMaxDevForIsoline,
  kAcGiMaxDevForFacet
};
// Raster image organization
//
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
// Raster image orientation
//
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
// scale filter method to use
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
// rotation filter method to use
enum AcGiRotationFilterType
{
  kDefaultRotationFilter,
  kInterpolatedRotationFilter,
  kNearestRotationFilter
};
// how to interpret nRasterRatio
enum AcGiScaleType
{
  kDefaultScale,
  kRelativeScale,
  kUnTransformedScale
};
// highlight style
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
