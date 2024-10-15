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
// acdbabb.h: Abbreviations for definitions in acdb.h
// 2/21/94: Up to date with respect to acdb.h


#ifdef AD_ACDBABB_H
// This file should only be included by .cpp files.  If it's
// included twice, we assume it's because it is being included
// by .h file(s), and so we complain.
#error "acdbabb.h included more than once!  Is it included by a .h file?"
#endif

#define AD_ACDBABB_H 1

#include "acdbabbES.h"

// enum AcDb::OpenMode

const AcDb::OpenMode kForRead = AcDb::kForRead;
const AcDb::OpenMode kForWrite = AcDb::kForWrite;
const AcDb::OpenMode kForNotify = AcDb::kForNotify;

// enum AcDb::ShowImagesMode

const AcDb::ShowImagesMode kNeverShow      = AcDb::kNeverShow;
const AcDb::ShowImagesMode kAlwaysShow     = AcDb::kAlwaysShow;
const AcDb::ShowImagesMode kBoundingBoxShow     = AcDb::kBoundingBoxShow;

// enum AcDb::SaveImagesMode

const AcDb::SaveImagesMode kNeverSave      = AcDb::kNeverSave;
const AcDb::SaveImagesMode kAlwaysSave     = AcDb::kAlwaysSave;

// enum AcDb::CoordAxis

const AcDb::CoordAxis kX = AcDb::kX;
const AcDb::CoordAxis kY = AcDb::kY;
const AcDb::CoordAxis kZ = AcDb::kZ;

// enum AcDb::CoordSystem

const AcDb::CoordSystem kWorldCS = AcDb::kWorldCS;
const AcDb::CoordSystem kUserCS = AcDb::kUserCS;
const AcDb::CoordSystem kCurDisplayCS = AcDb::kCurDisplayCS;
const AcDb::CoordSystem kPaperDisplayCS = AcDb::kPaperDisplayCS;
const AcDb::CoordSystem kEntityCS = AcDb::kEntityCS;

// enum AcDb::Intersect

const AcDb::Intersect kOnBothOperands = AcDb::kOnBothOperands;
const AcDb::Intersect kExtendThis = AcDb::kExtendThis;
const AcDb::Intersect kExtendArg = AcDb::kExtendArg;
const AcDb::Intersect kExtendBoth = AcDb::kExtendBoth;

// enum AcDb::Visibility

const AcDb::Visibility kInvisible = AcDb::kInvisible;
const AcDb::Visibility kVisible = AcDb::kVisible;

// enum AcDb::DxfCode

const AcDb::DxfCode kDxfInvalid = AcDb::kDxfInvalid;
const AcDb::DxfCode kDxfXDictionary = AcDb::kDxfXDictionary;
const AcDb::DxfCode kDxfPReactors = AcDb::kDxfPReactors;
const AcDb::DxfCode kDxfOperator = AcDb::kDxfOperator;
const AcDb::DxfCode kDxfXDataStart = AcDb::kDxfXDataStart;
const AcDb::DxfCode kDxfHeaderId = AcDb::kDxfHeaderId;
const AcDb::DxfCode kDxfEnd = AcDb::kDxfEnd;
const AcDb::DxfCode kDxfStart = AcDb::kDxfStart;
const AcDb::DxfCode kDxfText = AcDb::kDxfText;
const AcDb::DxfCode kDxfShapeName = AcDb::kDxfShapeName;
const AcDb::DxfCode kDxfSymbolTableName = AcDb::kDxfSymbolTableName;
const AcDb::DxfCode kDxfBlockName = AcDb::kDxfBlockName;
const AcDb::DxfCode kDxfAttributeTag = AcDb::kDxfAttributeTag;
const AcDb::DxfCode kDxfAttributePrompt = AcDb::kDxfAttributePrompt;
const AcDb::DxfCode kDxfDimStyleName = AcDb::kDxfDimStyleName;
const AcDb::DxfCode kDxfXRefPath = AcDb::kDxfXRefPath;
const AcDb::DxfCode kDxfHandle = AcDb::kDxfHandle;
const AcDb::DxfCode kDxfLinetypeName = AcDb::kDxfLinetypeName;
const AcDb::DxfCode kDxfTextStyleName = AcDb::kDxfTextStyleName;
const AcDb::DxfCode kDxfCLShapeText = AcDb::kDxfCLShapeText;
const AcDb::DxfCode kDxfCLShapeName = AcDb::kDxfCLShapeName;
const AcDb::DxfCode kDxfLayerName = AcDb::kDxfLayerName;
const AcDb::DxfCode kDxfLayoutName = AcDb::kDxfLayoutName;
const AcDb::DxfCode kDxfXCoord = AcDb::kDxfXCoord;
const AcDb::DxfCode kDxfYCoord = AcDb::kDxfYCoord;
const AcDb::DxfCode kDxfZCoord = AcDb::kDxfZCoord;
const AcDb::DxfCode kDxfElevation = AcDb::kDxfElevation;
const AcDb::DxfCode kDxfThickness = AcDb::kDxfThickness;
const AcDb::DxfCode kDxfReal = AcDb::kDxfReal;
const AcDb::DxfCode kDxfXReal = AcDb::kDxfXReal;
const AcDb::DxfCode kDxfInt8 = AcDb::kDxfInt8;
const AcDb::DxfCode kDxfBool = AcDb::kDxfBool;
const AcDb::DxfCode kDxfLinetypeScale = AcDb::kDxfLinetypeScale;
const AcDb::DxfCode kDxfLinetypeElement = AcDb::kDxfLinetypeElement;
const AcDb::DxfCode kDxfAngle = AcDb::kDxfAngle;
const AcDb::DxfCode kDxfVisibility = AcDb::kDxfVisibility;
const AcDb::DxfCode kDxfLayerLinetype = AcDb::kDxfLayerLinetype;
const AcDb::DxfCode kDxfColor = AcDb::kDxfColor;
const AcDb::DxfCode kDxfHasSubentities = AcDb::kDxfHasSubentities;
const AcDb::DxfCode kDxfViewportVisibility = AcDb::kDxfViewportVisibility;
const AcDb::DxfCode kDxfViewportActive = AcDb::kDxfViewportActive;
const AcDb::DxfCode kDxfViewportNumber = AcDb::kDxfViewportNumber;
const AcDb::DxfCode kDxfInt16 = AcDb::kDxfInt16;
const AcDb::DxfCode kDxfXInt16 = AcDb::kDxfXInt16;
const AcDb::DxfCode kDxfXXInt16 = AcDb::kDxfXXInt16;
const AcDb::DxfCode kDxfInt32 = AcDb::kDxfInt32;
const AcDb::DxfCode kDxfInt64 = AcDb::kDxfInt64;
const AcDb::DxfCode kDxfControlString = AcDb::kDxfControlString;
const AcDb::DxfCode kDxfSymTableRecComments = AcDb::kDxfSymTableRecComments;
const AcDb::DxfCode kDxfDimVarHandle = AcDb::kDxfDimVarHandle;
const AcDb::DxfCode kDxfUCSOrg = AcDb::kDxfUCSOrg;
const AcDb::DxfCode kDxfUCSOriX = AcDb::kDxfUCSOriX;
const AcDb::DxfCode kDxfUCSOriY = AcDb::kDxfUCSOriY;
const AcDb::DxfCode kDxfSubclass = AcDb::kDxfSubclass;
const AcDb::DxfCode kDxfEmbeddedObjectStart = AcDb::kDxfEmbeddedObjectStart;
const AcDb::DxfCode kDxfNormalX = AcDb::kDxfNormalX;
const AcDb::DxfCode kDxfNormalY = AcDb::kDxfNormalY;
const AcDb::DxfCode kDxfNormalZ = AcDb::kDxfNormalZ;
const AcDb::DxfCode kDxfXTextString = AcDb::kDxfXTextString;
const AcDb::DxfCode kDxfBinaryChunk = AcDb::kDxfBinaryChunk;
const AcDb::DxfCode kDxfArbHandle   = AcDb::kDxfArbHandle;
const AcDb::DxfCode kDxfSoftPointerId = AcDb::kDxfSoftPointerId;
const AcDb::DxfCode kDxfHardPointerId = AcDb::kDxfHardPointerId;
const AcDb::DxfCode kDxfSoftOwnershipId = AcDb::kDxfSoftOwnershipId;
const AcDb::DxfCode kDxfHardOwnershipId = AcDb::kDxfHardOwnershipId;
const AcDb::DxfCode kDxfLineWeight = AcDb::kDxfLineWeight;
const AcDb::DxfCode kDxfPlotStyleNameType = AcDb::kDxfPlotStyleNameType;
const AcDb::DxfCode kDxfPlotStyleNameId = AcDb::kDxfPlotStyleNameId;
const AcDb::DxfCode kDxfXXXInt16 = AcDb::kDxfXXXInt16;
const AcDb::DxfCode kDxfComment = AcDb::kDxfComment;
const AcDb::DxfCode kDxfXdAsciiString = AcDb::kDxfXdAsciiString;
const AcDb::DxfCode kDxfRegAppName = AcDb::kDxfRegAppName;
const AcDb::DxfCode kDxfXdControlString = AcDb::kDxfXdControlString;
const AcDb::DxfCode kDxfXdLayerName = AcDb::kDxfXdLayerName;
const AcDb::DxfCode kDxfXdBinaryChunk = AcDb::kDxfXdBinaryChunk;
const AcDb::DxfCode kDxfXdHandle = AcDb::kDxfXdHandle;
const AcDb::DxfCode kDxfXdXCoord = AcDb::kDxfXdXCoord;
const AcDb::DxfCode kDxfXdYCoord = AcDb::kDxfXdYCoord;
const AcDb::DxfCode kDxfXdZCoord = AcDb::kDxfXdZCoord;
const AcDb::DxfCode kDxfXdWorldXCoord = AcDb::kDxfXdWorldXCoord;
const AcDb::DxfCode kDxfXdWorldYCoord = AcDb::kDxfXdWorldYCoord;
const AcDb::DxfCode kDxfXdWorldZCoord = AcDb::kDxfXdWorldZCoord;
const AcDb::DxfCode kDxfXdWorldXDisp = AcDb::kDxfXdWorldXDisp;
const AcDb::DxfCode kDxfXdWorldYDisp = AcDb::kDxfXdWorldYDisp;
const AcDb::DxfCode kDxfXdWorldZDisp = AcDb::kDxfXdWorldZDisp;
const AcDb::DxfCode kDxfXdWorldXDir = AcDb::kDxfXdWorldXDir;
const AcDb::DxfCode kDxfXdWorldYDir = AcDb::kDxfXdWorldYDir;
const AcDb::DxfCode kDxfXdWorldZDir = AcDb::kDxfXdWorldZDir;
const AcDb::DxfCode kDxfXdReal = AcDb::kDxfXdReal;
const AcDb::DxfCode kDxfXdDist = AcDb::kDxfXdDist;
const AcDb::DxfCode kDxfXdScale = AcDb::kDxfXdScale;
const AcDb::DxfCode kDxfXdInteger16 = AcDb::kDxfXdInteger16;
const AcDb::DxfCode kDxfXdInteger32 = AcDb::kDxfXdInteger32;
const AcDb::DxfCode kDxfColorRGB =  AcDb::kDxfColorRGB; 
const AcDb::DxfCode kDxfColorName =  AcDb::kDxfColorName;
const AcDb::DxfCode kDxfAlpha =  AcDb::kDxfAlpha;    
const AcDb::DxfCode kDxfMaterialId =  AcDb::kDxfMaterialId;
const AcDb::DxfCode kDxfViewportGridDisplay = AcDb::kDxfViewportGridDisplay;
const AcDb::DxfCode kDxfObjVisualStyleId = AcDb::kDxfObjVisualStyleId;
const AcDb::DxfCode kDxfVpVisualStyleId = AcDb::kDxfVpVisualStyleId;
const AcDb::DxfCode kDxfDragVisualStyleId = AcDb::kDxfDragVisualStyleId;
const AcDb::DxfCode kDxfShadowFlags = AcDb::kDxfShadowFlags;
const AcDb::DxfCode kDxfFaceStyleId = AcDb::kDxfFaceStyleId;
const AcDb::DxfCode kDxfEdgeStyleId = AcDb::kDxfEdgeStyleId;
const AcDb::DxfCode kDxfVisualStyleId = AcDb::kDxfVisualStyleId;

const AcDb::DxfCode kDxfGradientObjType  = AcDb::kDxfGradientObjType;
const AcDb::DxfCode kDxfGradientPatType  = AcDb::kDxfGradientPatType;
const AcDb::DxfCode kDxfGradientTintType = AcDb::kDxfGradientTintType;
const AcDb::DxfCode kDxfGradientColCount = AcDb::kDxfGradientColCount;
const AcDb::DxfCode kDxfGradientAngle    = AcDb::kDxfGradientAngle;
const AcDb::DxfCode kDxfGradientShift    = AcDb::kDxfGradientShift;
const AcDb::DxfCode kDxfGradientTintVal  = AcDb::kDxfGradientTintVal;
const AcDb::DxfCode kDxfGradientColVal   = AcDb::kDxfGradientColVal;
const AcDb::DxfCode kDxfGradientName     = AcDb::kDxfGradientName;

// enum AcDb::DwgDataType

const AcDb::DwgDataType kDwgNull = AcDb::kDwgNull;
const AcDb::DwgDataType kDwgReal = AcDb::kDwgReal;
const AcDb::DwgDataType kDwgInt64 = AcDb::kDwgInt64;
const AcDb::DwgDataType kDwgInt32 = AcDb::kDwgInt32;
const AcDb::DwgDataType kDwgInt16 = AcDb::kDwgInt16;
const AcDb::DwgDataType kDwgInt8 = AcDb::kDwgInt8;
const AcDb::DwgDataType kDwgText = AcDb::kDwgText;
const AcDb::DwgDataType kDwgBChunk = AcDb::kDwgBChunk;
const AcDb::DwgDataType kDwgHandle = AcDb::kDwgHandle;
const AcDb::DwgDataType kDwgHardOwnershipId = AcDb::kDwgHardOwnershipId;
const AcDb::DwgDataType kDwgSoftOwnershipId = AcDb::kDwgSoftOwnershipId;
const AcDb::DwgDataType kDwgHardPointerId   = AcDb::kDwgHardPointerId;
const AcDb::DwgDataType kDwgSoftPointerId   = AcDb::kDwgSoftPointerId;
const AcDb::DwgDataType kDwg3Real = AcDb::kDwg3Real;
const AcDb::DwgDataType kDwgNotRecognized = AcDb::kDwgNotRecognized;

// enum AcDb::OsnapMask

const AcDb::OsnapMask kOsMaskEnd = AcDb::kOsMaskEnd;
const AcDb::OsnapMask kOsMaskMid = AcDb::kOsMaskMid;
const AcDb::OsnapMask kOsMaskCen = AcDb::kOsMaskCen;
const AcDb::OsnapMask kOsMaskNode = AcDb::kOsMaskNode;
const AcDb::OsnapMask kOsMaskQuad = AcDb::kOsMaskQuad;
const AcDb::OsnapMask kOsMaskInt = AcDb::kOsMaskInt;
const AcDb::OsnapMask kOsMaskIns = AcDb::kOsMaskIns;
const AcDb::OsnapMask kOsMaskPerp = AcDb::kOsMaskPerp;
const AcDb::OsnapMask kOsMaskTan = AcDb::kOsMaskTan;
const AcDb::OsnapMask kOsMaskNear = AcDb::kOsMaskNear;
const AcDb::OsnapMask kOsMaskQuick = AcDb::kOsMaskQuick;
const AcDb::OsnapMask kOsMaskImmediate = AcDb::kOsMaskImmediate;
const AcDb::OsnapMask kOsMaskAllowTan = AcDb::kOsMaskAllowTan;
const AcDb::OsnapMask kOsMaskDisablePerp = AcDb::kOsMaskDisablePerp;
const AcDb::OsnapMask kOsMaskRelCartesian = AcDb::kOsMaskRelCartesian;
const AcDb::OsnapMask kOsMaskRelPolar = AcDb::kOsMaskRelPolar;
const AcDb::OsnapMask kOsMaskNoneOverride = AcDb::kOsMaskNoneOverride;

// enum AcDb::OsnapMode

const AcDb::OsnapMode kOsModeEnd = AcDb::kOsModeEnd;
const AcDb::OsnapMode kOsModeMid = AcDb::kOsModeMid;
const AcDb::OsnapMode kOsModeCen = AcDb::kOsModeCen;
const AcDb::OsnapMode kOsModeCentroid = AcDb::kOsModeCentroid;
const AcDb::OsnapMode kOsModeNode = AcDb::kOsModeNode;
const AcDb::OsnapMode kOsModeQuad = AcDb::kOsModeQuad;
const AcDb::OsnapMode kOsModeIns = AcDb::kOsModeIns;
const AcDb::OsnapMode kOsModePerp = AcDb::kOsModePerp;
const AcDb::OsnapMode kOsModeTan = AcDb::kOsModeTan;
const AcDb::OsnapMode kOsModeNear = AcDb::kOsModeNear;

// enum AcDb::TextHorzMode

const AcDb::TextHorzMode kTextLeft = AcDb::kTextLeft;
const AcDb::TextHorzMode kTextCenter = AcDb::kTextCenter;
const AcDb::TextHorzMode kTextRight = AcDb::kTextRight;
const AcDb::TextHorzMode kTextAlign = AcDb::kTextAlign;
const AcDb::TextHorzMode kTextMid = AcDb::kTextMid;
const AcDb::TextHorzMode kTextFit = AcDb::kTextFit;

// enum AcDb::TextVertMode

const AcDb::TextVertMode kTextBase = AcDb::kTextBase;
const AcDb::TextVertMode kTextBottom = AcDb::kTextBottom;
const AcDb::TextVertMode kTextVertMid = AcDb::kTextVertMid;
const AcDb::TextVertMode kTextTop = AcDb::kTextTop;

// enum LineSpacingStyle

const AcDb::LineSpacingStyle kAtLeast = AcDb::kAtLeast;
const AcDb::LineSpacingStyle kExactly = AcDb::kExactly;

// enum AcDb::Planarity

const AcDb::Planarity kNonPlanar = AcDb::kNonPlanar;
const AcDb::Planarity kPlanar = AcDb::kPlanar;
const AcDb::Planarity kLinear = AcDb::kLinear;

// enum AcDb::PointIndex

const AcDb::PointIndex kMPoint1 = AcDb::kMPoint1;
const AcDb::PointIndex kMPoint2 = AcDb::kMPoint2;
const AcDb::PointIndex kMPoint3 = AcDb::kMPoint3;
const AcDb::PointIndex kMPoint4 = AcDb::kMPoint4;

// enum AcDb::EdgeIndex

const AcDb::EdgeIndex kMEdge1 = AcDb::kMEdge1;
const AcDb::EdgeIndex kMEdge2 = AcDb::kMEdge2;
const AcDb::EdgeIndex kMEdge3 = AcDb::kMEdge3;
const AcDb::EdgeIndex kMEdge4 = AcDb::kMEdge4;

// enum AcDb::Poly2dType

const AcDb::Poly2dType k2dSimplePoly = AcDb::k2dSimplePoly;
const AcDb::Poly2dType k2dFitCurvePoly = AcDb::k2dFitCurvePoly;
const AcDb::Poly2dType k2dQuadSplinePoly = AcDb::k2dQuadSplinePoly;
const AcDb::Poly2dType k2dCubicSplinePoly = AcDb::k2dCubicSplinePoly;

// enum AcDb::Poly3dType

const AcDb::Poly3dType k3dSimplePoly = AcDb::k3dSimplePoly;
const AcDb::Poly3dType k3dQuadSplinePoly = AcDb::k3dQuadSplinePoly;
const AcDb::Poly3dType k3dCubicSplinePoly = AcDb::k3dCubicSplinePoly;

// enum AcDb::PolyMeshType

const AcDb::PolyMeshType kSimpleMesh = AcDb::kSimpleMesh;
const AcDb::PolyMeshType kQuadSurfaceMesh = AcDb::kQuadSurfaceMesh;
const AcDb::PolyMeshType kCubicSurfaceMesh = AcDb::kCubicSurfaceMesh;
const AcDb::PolyMeshType kBezierSurfaceMesh = AcDb::kBezierSurfaceMesh;

// enum AcDb::Vertex2dType

const AcDb::Vertex2dType k2dVertex = AcDb::k2dVertex;
const AcDb::Vertex2dType k2dSplineCtlVertex = AcDb::k2dSplineCtlVertex;
const AcDb::Vertex2dType k2dSplineFitVertex = AcDb::k2dSplineFitVertex;
const AcDb::Vertex2dType k2dCurveFitVertex = AcDb::k2dCurveFitVertex;

// enum AcDb::Vertex3dType

const AcDb::Vertex3dType k3dSimpleVertex = AcDb::k3dSimpleVertex;
const AcDb::Vertex3dType k3dControlVertex = AcDb::k3dControlVertex;
const AcDb::Vertex3dType k3dFitVertex = AcDb::k3dFitVertex;

// enum AcDb::SpaceValueType

const AcDb::SpaceValueType kUndefined = AcDb::kUndefined;
const AcDb::SpaceValueType kStubPtr = AcDb::kStubPtr;
const AcDb::SpaceValueType kEndOfFile = AcDb::kEndOfFile;
const AcDb::SpaceValueType kBackwardBranch = AcDb::kBackwardBranch;
const AcDb::SpaceValueType kForwardBranch = AcDb::kForwardBranch;
const AcDb::SpaceValueType kDetour = AcDb::kDetour;

// enum AcDb::BoolOperType

const AcDb::BoolOperType kBoolUnite = AcDb::kBoolUnite;
const AcDb::BoolOperType kBoolIntersect = AcDb::kBoolIntersect;
const AcDb::BoolOperType kBoolSubtract = AcDb::kBoolSubtract;

// enum AcDb::SubentType

const AcDb::SubentType kNullSubentType   = AcDb::kNullSubentType;
const AcDb::SubentType kVertexSubentType = AcDb::kVertexSubentType;
const AcDb::SubentType kEdgeSubentType   = AcDb::kEdgeSubentType;
const AcDb::SubentType kFaceSubentType   = AcDb::kFaceSubentType;
const AcDb::SubentType kMlineSubentCache = AcDb::kMlineSubentCache;
const AcDb::SubentType kClassSubentType  = AcDb::kClassSubentType;
const AcDb::SubentType kAxisSubentType   = AcDb::kAxisSubentType;
const AcDb::SubentType kSilhouetteSubentType = AcDb::kSilhouetteSubentType;

// enum AcDb::GeomId

const AcDb::GeomId kNoGeom = AcDb::kNoGeom;

// enum AcDb::GeomType

const AcDb::GeomType kInvalidGeom = AcDb::kInvalidGeom;
const AcDb::GeomType kPointGeom = AcDb::kPointGeom;
const AcDb::GeomType kLineGeom = AcDb::kLineGeom;
const AcDb::GeomType kCircleGeom = AcDb::kCircleGeom;
const AcDb::GeomType kPlaneGeom = AcDb::kPlaneGeom;

// enum AcDb::UnitsValue
const AcDb::UnitsValue kUnitsUndefined      = AcDb::kUnitsUndefined;
const AcDb::UnitsValue kUnitsInches         = AcDb::kUnitsInches;
const AcDb::UnitsValue kUnitsFeet           = AcDb::kUnitsFeet;
const AcDb::UnitsValue kUnitsMillimeters    = AcDb::kUnitsMillimeters;
const AcDb::UnitsValue kUnitsMeters         = AcDb::kUnitsMeters;
const AcDb::UnitsValue kUnitsMicroinches    = AcDb::kUnitsMicroinches;
const AcDb::UnitsValue kUnitsMils           = AcDb::kUnitsMils;
const AcDb::UnitsValue kUnitsYards          = AcDb::kUnitsYards;
const AcDb::UnitsValue kUnitsMiles          = AcDb::kUnitsMiles;
const AcDb::UnitsValue kUnitsAngstroms      = AcDb::kUnitsAngstroms;
const AcDb::UnitsValue kUnitsNanometers     = AcDb::kUnitsNanometers;
const AcDb::UnitsValue kUnitsMicrons        = AcDb::kUnitsMicrons;
const AcDb::UnitsValue kUnitsDecimeters     = AcDb::kUnitsDecimeters;
const AcDb::UnitsValue kUnitsCentimeters    = AcDb::kUnitsCentimeters;
const AcDb::UnitsValue kUnitsDekameters     = AcDb::kUnitsDekameters;
const AcDb::UnitsValue kUnitsHectometers    = AcDb::kUnitsHectometers;
const AcDb::UnitsValue kUnitsKilometers     = AcDb::kUnitsKilometers;
const AcDb::UnitsValue kUnitsGigameters     = AcDb::kUnitsGigameters;
const AcDb::UnitsValue kUnitsAstronomical   = AcDb::kUnitsAstronomical;
const AcDb::UnitsValue kUnitsLightYears     = AcDb::kUnitsLightYears;
const AcDb::UnitsValue kUnitsParsecs        = AcDb::kUnitsParsecs;
const AcDb::UnitsValue kUnitsUSSurveyFeet   = AcDb::kUnitsUSSurveyFeet;
const AcDb::UnitsValue kUnitsUSSurveyInch   = AcDb::kUnitsUSSurveyInch;
const AcDb::UnitsValue kUnitsUSSurveyYard   = AcDb::kUnitsUSSurveyYard;
const AcDb::UnitsValue kUnitsUSSurveyMile   = AcDb::kUnitsUSSurveyMile;
const AcDb::UnitsValue kUnitsMax            = AcDb::kUnitsMax;

// enum AcDb::OrthographicView

const AcDb::OrthographicView kTopView      = AcDb::kTopView;
const AcDb::OrthographicView kBottomView   = AcDb::kBottomView;
const AcDb::OrthographicView kFrontView    = AcDb::kFrontView;
const AcDb::OrthographicView kBackView     = AcDb::kBackView;
const AcDb::OrthographicView kLeftView     = AcDb::kLeftView;
const AcDb::OrthographicView kRightView    = AcDb::kRightView;
const AcDb::OrthographicView kNonOrthoView = AcDb::kNonOrthoView;

// enum AcDb::CellType

const AcDb::CellType kUnknownCell          =  AcDb::kUnknownCell;	
const AcDb::CellType kTextCell             =  AcDb::kTextCell;	
const AcDb::CellType kBlockCell            =  AcDb::kBlockCell;	

// enum AcDb::CellEdgeMask
 
const AcDb::CellEdgeMask kTopMask          =  AcDb::kTopMask;	
const AcDb::CellEdgeMask kRightMask        =  AcDb::kRightMask;	
const AcDb::CellEdgeMask kBottomMask       =  AcDb::kBottomMask;	
const AcDb::CellEdgeMask kLeftMask         =  AcDb::kLeftMask;	

// enum AcDb::FlowDirection
 
const AcDb::FlowDirection kTtoB            =  AcDb::kTtoB;	
const AcDb::FlowDirection kBtoT            =  AcDb::kBtoT;

// enum AcDb::RotationAngle
 
const AcDb::RotationAngle kDegrees000      =  AcDb::kDegrees000;	
const AcDb::RotationAngle kDegrees090      =  AcDb::kDegrees090;	
const AcDb::RotationAngle kDegrees180      =  AcDb::kDegrees180;	
const AcDb::RotationAngle kDegrees270      =  AcDb::kDegrees270;	
const AcDb::RotationAngle kDegreesUnknown  =  AcDb::kDegreesUnknown;	

// enum AcDb::CellAlignment

const AcDb::CellAlignment kTopLeft		   =  AcDb::kTopLeft;
const AcDb::CellAlignment kTopCenter	   =  AcDb::kTopCenter;	
const AcDb::CellAlignment kTopRight		   =  AcDb::kTopRight;	
const AcDb::CellAlignment kMiddleLeft	   =  AcDb::kMiddleLeft;	
const AcDb::CellAlignment kMiddleCenter	   =  AcDb::kMiddleCenter;	
const AcDb::CellAlignment kMiddleRight	   =  AcDb::kMiddleRight;	
const AcDb::CellAlignment kBottomLeft	   =  AcDb::kBottomLeft;	
const AcDb::CellAlignment kBottomCenter	   =  AcDb::kBottomCenter;	
const AcDb::CellAlignment kBottomRight	   =  AcDb::kBottomRight;	

// enum AcDb::GridLineType

const AcDb::GridLineType kInvalidGridLine  =  AcDb::kInvalidGridLine;	  // TODO: May not be needed
const AcDb::GridLineType kHorzTop		   =  AcDb::kHorzTop;	
const AcDb::GridLineType kHorzInside	   =  AcDb::kHorzInside;	
const AcDb::GridLineType kHorzBottom	   =  AcDb::kHorzBottom;	
const AcDb::GridLineType kVertLeft		   =  AcDb::kVertLeft;	
const AcDb::GridLineType kVertInside	   =  AcDb::kVertInside;	
const AcDb::GridLineType kVertRight		   =  AcDb::kVertRight;	

// enum AcDb::GridLineTypes
const AcDb::GridLineTypes kAllGridLines	=  AcDb::kAllGridLines;	

// enum AcDb::RowType

const AcDb::RowType kUnknownRow			   =  AcDb::kUnknownRow;	// TODO: May not be needed
const AcDb::RowType kDataRow			   =  AcDb::kDataRow;	
const AcDb::RowType kTitleRow			   =  AcDb::kTitleRow;	
const AcDb::RowType kHeaderRow			   =  AcDb::kHeaderRow;	

// enum AcDb::RowTypes
const AcDb::RowTypes kAllRows               =  AcDb::kAllRows;	

// enum AcDb::TableStyleFlags
const AcDb::TableStyleFlags kHorzInsideLineFirst =  AcDb::kHorzInsideLineFirst;
const AcDb::TableStyleFlags kHorzInsideLineSecond =  AcDb::kHorzInsideLineSecond;
const AcDb::TableStyleFlags kHorzInsideLineThird =  AcDb::kHorzInsideLineThird;
const AcDb::TableStyleFlags kTableStyleModified =  AcDb::kTableStyleModified;

const AcDb::SliceModelType kKeepBothSides    =  AcDb::kKeepBothSides;	
const AcDb::SliceModelType kUseCurrentColor  =  AcDb::kUseCurrentColor;	
