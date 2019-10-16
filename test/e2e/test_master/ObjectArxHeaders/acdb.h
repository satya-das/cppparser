//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_ACDB_H
#  define AD_ACDB_H	1
#  include "adesk.h"
#  include "AdAChar.h"
#  define ACDB_MODEL_SPACE	ACRX_T(/*MSG0*/"*Model_Space")
#  define ACDB_PAPER_SPACE	ACRX_T(/*MSG0*/"*Paper_Space")
#  define ACDB_NULL_HANDLE	ACRX_T("\0\0\0\0\0\0\0")  // deprecated - use empty string instead
#  define ACDB_OPEN_BRACE_STR	ACRX_T(/*MSG0*/"{")
#  define ACDB_OPEN_BRACE_CHAR	ACRX_T(/*MSG0*/'{')
#  define ACDB_CLOSE_BRACE_STR	ACRX_T(/*MSG0*/"}")
#  define ACDB_CLOSE_BRACE_CHAR	ACRX_T(/*MSG0*/'}')
#  define ACDB_GROUP_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_GROUP")
#  define ACDB_MLINESTYLE_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_MLINESTYLE")
#  define ACDB_LAYOUT_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_LAYOUT")
#  define ACDB_PLOTSETTINGS_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_PLOTSETTINGS")
#  define ACDB_PLOTSTYLENAME_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_PLOTSTYLENAME")
#  define ACDB_MATERIAL_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_MATERIAL")
#  define ACDB_VISUALSTYLE_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_VISUALSTYLE")
#  define ACDB_COLOR_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_COLOR")
#  define ACDB_TABLESTYLE_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_TABLESTYLE")
#  define ACDB_EMBEDDED_OBJECT_STR	ACRX_T(/*MSG0*/"Embedded Object")
#  define ACDB_LAYERSTATES_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_LAYERSTATES")
#  define ACDB_FIELD_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_FIELD")
#  define ACDB_FIELDLIST	ACRX_T(/*MSG0*/"ACAD_FIELDLIST")
#  define ACDB_ENHANCED_BLOCK	ACRX_T(/*MSG0*/"ACAD_ENHANCEDBLOCK")
#  define ACDB_ENHANCED_BLOCK_EVALKEY	ACRX_T(/*MSG0*/"ACAD_ENHANCEDBLOCKEVALKEY")
#  define ACDB_ENHANCED_BLOCK_REF	ACRX_T(/*MSG0*/"ACAD_ENHANCEDBLOCK_REFERENCE")
#  define ACDB_SECTION_MANAGER	ACRX_T(/*MSG0*/"ACAD_SECTION_MANAGER")
#  define ACDB_DATALINK	ACRX_T(/*MSG0*/"ACAD_DATALINK")
#  define ACDB_MLEADERSTYLE_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_MLEADERSTYLE")
#  define ACDB_ASSOCNETWORK_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_ASSOCNETWORK")
#  define ACDB_SECTIONSTYLE_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_SECTIONVIEWSTYLE")
#  define ACDB_DETAILSTYLE_DICTIONARY	ACRX_T(/*MSG0*/"ACAD_DETAILVIEWSTYLE")
#  define ACDB_ANNOTATIONSCALES_COLLECTION	acdbAnnotationScaleCollectionName()
#  pragma  pack(push, 8)
struct AcDb
{
  enum OpenMode
  {
    kForRead = 0,
    kForWrite = 1,
    kForNotify = 2
  };
  enum CoordAxis
  {
    kX = 0,
    kY = 1,
    kZ = 2
  };
  enum CoordSystem
  {
    kWorldCS = 0,
    kUserCS = 1,
    kCurDisplayCS = 2,
    kPaperDisplayCS = 3,
    kEntityCS = 4
  };
  enum Intersect
  {
    kOnBothOperands = 0,
    kExtendThis = 1,
    kExtendArg = 2,
    kExtendBoth = 3
  };
  enum Visibility
  {
    kInvisible = 1,
    kVisible = 0
  };
  typedef Adesk::Int16 DxfCode;
  enum
  {
    kDxfInvalid = -9999,
    kDxfXDictionary = -6,
    kDxfPReactors = -5,
    kDxfOperator = -4,
    kDxfXDataStart = -3,
    kDxfHeaderId = -2,
    kDxfFirstEntId = -2,
    kDxfEnd = -1,
    kDxfStart = 0,
    kDxfText = 1,
    kDxfXRefPath = 1,
    kDxfShapeName = 2,
    kDxfBlockName = 2,
    kDxfAttributeTag = 2,
    kDxfSymbolTableName = 2,
    kDxfMstyleName = 2,
    kDxfSymTableRecName = 2,
    kDxfAttributePrompt = 3,
    kDxfDimStyleName = 3,
    kDxfLinetypeProse = 3,
    kDxfTextFontFile = 3,
    kDxfDescription = 3,
    kDxfDimPostStr = 3,
    kDxfTextBigFontFile = 4,
    kDxfDimAPostStr = 4,
    kDxfCLShapeName = 4,
    kDxfSymTableRecComments = 4,
    kDxfHandle = 5,
    kDxfDimBlk = 5,
    kDxfDimBlk1 = 6,
    kDxfLinetypeName = 6,
    kDxfDimBlk2 = 7,
    kDxfTextStyleName = 7,
    kDxfLayerName = 8,
    kDxfCLShapeText = 9,
    kDxfXCoord = 10,
    kDxfYCoord = 20,
    kDxfZCoord = 30,
    kDxfElevation = 38,
    kDxfThickness = 39,
    kDxfReal = 40,
    kDxfViewportHeight = 40,
    kDxfTxtSize = 40,
    kDxfTxtStyleXScale = 41,
    kDxfViewWidth = 41,
    kDxfViewportAspect = 41,
    kDxfTxtStylePSize = 42,
    kDxfViewLensLength = 42,
    kDxfViewFrontClip = 43,
    kDxfViewBackClip = 44,
    kDxfShapeXOffset = 44,
    kDxfShapeYOffset = 45,
    kDxfViewHeight = 45,
    kDxfShapeScale = 46,
    kDxfPixelScale = 47,
    kDxfLinetypeScale = 48,
    kDxfDashLength = 49,
    kDxfMlineOffset = 49,
    kDxfLinetypeElement = 49,
    kDxfAngle = 50,
    kDxfViewportSnapAngle = 50,
    kDxfViewportTwist = 51,
    kDxfVisibility = 60,
    kDxfViewportGridDisplay = 60,
    kDxfLayerLinetype = 61,
    kDxfViewportGridMajor = 61,
    kDxfColor = 62,
    kDxfHasSubentities = 66,
    kDxfViewportVisibility = 67,
    kDxfViewportActive = 68,
    kDxfViewportNumber = 69,
    kDxfInt16 = 70,
    kDxfViewMode = 71,
    kDxfCircleSides = 72,
    kDxfViewportZoom = 73,
    kDxfViewportIcon = 74,
    kDxfViewportSnap = 75,
    kDxfViewportGrid = 76,
    kDxfViewportSnapStyle = 77,
    kDxfViewportSnapPair = 78,
    kDxfRegAppFlags = 71,
    kDxfTxtStyleFlags = 71,
    kDxfLinetypeAlign = 72,
    kDxfLinetypePDC = 73,
    kDxfInt32 = 90,
    kDxfVertexIdentifier = 91,
    kDxfSubclass = 100,
    kDxfEmbeddedObjectStart = 101,
    kDxfControlString = 102,
    kDxfDimVarHandle = 105,
    kDxfUCSOrg = 110,
    kDxfUCSOriX = 111,
    kDxfUCSOriY = 112,
    kDxfXReal = 140,
    kDxfViewBrightness = 141,
    kDxfViewContrast = 142,
    kDxfInt64 = 160,
    kDxfXInt16 = 170,
    kDxfNormalX = 210,
    kDxfNormalY = 220,
    kDxfNormalZ = 230,
    kDxfXXInt16 = 270,
    kDxfInt8 = 280,
    kDxfRenderMode = 281,
    kDxfDefaultLightingType = 282,
    kDxfShadowFlags = 284,
    kDxfBool = 290,
    kDxfDefaultLightingOn = 292,
    kDxfXTextString = 300,
    kDxfBinaryChunk = 310,
    kDxfArbHandle = 320,
    kDxfSoftPointerId = 330,
    kDxfViewBackgroundId = 332,
    kDxfShadePlotId = 333,
    kDxfLiveSectionId = 334,
    kDxfLiveSectionName = 309,
    kDxfHardPointerId = 340,
    kDxfObjVisualStyleId = 345,
    kDxfVpVisualStyleId = 346,
    kDxfMaterialId = 347,
    kDxfVisualStyleId = 348,
    kDxfDragVisualStyleId = 349,
    kDxfSoftOwnershipId = 350,
    kDxfHardOwnershipId = 360,
    kDxfSunId = 361,
    kDxfLineWeight = 370,
    kDxfPlotStyleNameType = 380,
    kDxfPlotStyleNameId = 390,
    kDxfXXXInt16 = 400,
    kDxfLayoutName = 410,
    kDxfColorRGB = 420,
    kDxfColorName = 430,
    kDxfAlpha = 440,
    kDxfGradientObjType = 450,
    kDxfGradientPatType = 451,
    kDxfGradientTintType = 452,
    kDxfGradientColCount = 453,
    kDxfGradientAngle = 460,
    kDxfGradientShift = 461,
    kDxfGradientTintVal = 462,
    kDxfGradientColVal = 463,
    kDxfGradientName = 470,
    kDxfFaceStyleId = 480,
    kDxfEdgeStyleId = 481,
    kDxfComment = 999,
    kDxfXdAsciiString = 1000,
    kDxfRegAppName = 1001,
    kDxfXdControlString = 1002,
    kDxfXdLayerName = 1003,
    kDxfXdBinaryChunk = 1004,
    kDxfXdHandle = 1005,
    kDxfXdXCoord = 1010,
    kDxfXdYCoord = 1020,
    kDxfXdZCoord = 1030,
    kDxfXdWorldXCoord = 1011,
    kDxfXdWorldYCoord = 1021,
    kDxfXdWorldZCoord = 1031,
    kDxfXdWorldXDisp = 1012,
    kDxfXdWorldYDisp = 1022,
    kDxfXdWorldZDisp = 1032,
    kDxfXdWorldXDir = 1013,
    kDxfXdWorldYDir = 1023,
    kDxfXdWorldZDir = 1033,
    kDxfXdReal = 1040,
    kDxfXdDist = 1041,
    kDxfXdScale = 1042,
    kDxfXdInteger16 = 1070,
    kDxfXdInteger32 = 1071,
    kDxfXdMax = kDxfXdInteger32
  };
  enum DwgDataType
  {
    kDwgNull = 0,
    kDwgReal = 1,
    kDwgInt32 = 2,
    kDwgInt16 = 3,
    kDwgInt8 = 4,
    kDwgText = 5,
    kDwgBChunk = 6,
    kDwgHandle = 7,
    kDwgHardOwnershipId = 8,
    kDwgSoftOwnershipId = 9,
    kDwgHardPointerId = 10,
    kDwgSoftPointerId = 11,
    kDwg3Real = 12,
    kDwgInt64 = 13,
    kDwgNotRecognized = 19
  };
  enum OsnapMask
  {
    kOsMaskEnd = 1,
    kOsMaskMid = 2,
    kOsMaskCen = 4,
    kOsMaskNode = 8,
    kOsMaskQuad = 0x10,
    kOsMaskInt = 0x20,
    kOsMaskIns = 0x40,
    kOsMaskPerp = 0x80,
    kOsMaskTan = 0x100,
    kOsMaskNear = 0x200,
    kOsMaskQuick = 0x400,
    kOsMaskApint = 0x800,
    kOsMaskImmediate = 0x10000,
    kOsMaskAllowTan = 0x20000,
    kOsMaskDisablePerp = 0x40000,
    kOsMaskRelCartesian = 0x80000,
    kOsMaskRelPolar = 0x100000,
    kOsMaskNoneOverride = 0x200000
  };
  enum OsnapMode
  {
    kOsModeEnd = 1,
    kOsModeMid = 2,
    kOsModeCen = 3,
    kOsModeNode = 4,
    kOsModeQuad = 5,
    kOsModeIns = 7,
    kOsModePerp = 8,
    kOsModeTan = 9,
    kOsModeNear = 10,
    kOsModeCentroid = 11
  };
  enum ShowImagesMode
  {
    kNeverShow = 0,
    kAlwaysShow = 1,
    kBoundingBoxShow = 2
  };
  enum SaveImagesMode
  {
    kNeverSave = 0,
    kAlwaysSave = 1
  };
  enum TextHorzMode
  {
    kTextLeft = 0,
    kTextCenter = 1,
    kTextRight = 2,
    kTextAlign = 3,
    kTextMid = 4,
    kTextFit = 5
  };
  enum TextVertMode
  {
    kTextBase = 0,
    kTextBottom = 1,
    kTextVertMid = 2,
    kTextTop = 3
  };
  enum LineSpacingStyle
  {
    kAtLeast = 1,
    kExactly = 2
  };
  enum Planarity
  {
    kNonPlanar = 0,
    kPlanar = 1,
    kLinear = 2
  };
  enum PointIndex
  {
    kMPoint1 = 0,
    kMPoint2 = 1,
    kMPoint3 = 2,
    kMPoint4 = 3
  };
  enum EdgeIndex
  {
    kMEdge1 = 0,
    kMEdge2 = 1,
    kMEdge3 = 2,
    kMEdge4 = 3
  };
  enum Poly2dType
  {
    k2dSimplePoly = 0,
    k2dFitCurvePoly = 1,
    k2dQuadSplinePoly = 2,
    k2dCubicSplinePoly = 3
  };
  enum Poly3dType
  {
    k3dSimplePoly = 0,
    k3dQuadSplinePoly = 1,
    k3dCubicSplinePoly = 2
  };
  enum PolyMeshType
  {
    kSimpleMesh = 0,
    kQuadSurfaceMesh = 5,
    kCubicSurfaceMesh = 6,
    kBezierSurfaceMesh = 8
  };
  enum Vertex2dType
  {
    k2dVertex = 0,
    k2dSplineCtlVertex = 1,
    k2dSplineFitVertex = 2,
    k2dCurveFitVertex = 3
  };
  enum Vertex3dType
  {
    k3dSimpleVertex = 0,
    k3dControlVertex = 1,
    k3dFitVertex = 2
  };
  enum SpaceValueType
  {
    kUndefined,
    kStubPtr,
    kEndOfFile,
    kBackwardBranch,
    kForwardBranch,
    kDetour
  };
  enum BoolOperType
  {
    kBoolUnite = 0,
    kBoolIntersect = 1,
    kBoolSubtract = 2
  };
  typedef Adesk::UInt32 SubentType;
  enum
  {
    kNullSubentType = 0,
    kFaceSubentType = 1,
    kEdgeSubentType = 2,
    kVertexSubentType = 3,
////////////////////////////////////////////////////////////
    kMlineSubentCache = 4,
////////////////////////////////////////////////////////////
    kClassSubentType = 5,
    kAxisSubentType = 6,
    kSilhouetteSubentType = 7
  };
  typedef Adesk::UInt32 GeomId;
  enum
  {
    kNoGeom = 0
  };
  enum GeomType
  {
    kInvalidGeom = 0,
    kPointGeom,
    kLineGeom,
    kCircleGeom,
    kPlaneGeom
  };
  enum FilerType
  {
    kFileFiler = 0,
    kCopyFiler = 1,
    kUndoFiler = 2,
    kBagFiler = 3,
    kIdXlateFiler = 4,
    kPageFiler = 5,
    kDeepCloneFiler = 6,
    kIdFiler = 7,
    kPurgeFiler = 8,
    kWblockCloneFiler = 9
  };
  enum FilerSeekType
  {
    kSeekFromStart = 0,
    kSeekFromCurrent = 1,
    kSeekFromEnd = 2
  };
  enum AcDbDwgVersion
  {
    kDHL_MC0_0 = 0,
    kDHL_AC1_2 = 1,
    kDHL_AC1_40 = 2,
    kDHL_AC1_50 = 3,
    kDHL_AC2_20 = 4,
    kDHL_AC2_10 = 5,
    kDHL_AC2_21 = 6,
    kDHL_AC2_22 = 7,
    kDHL_1001 = 8,
    kDHL_1002 = 9,
    kDHL_1003 = 10,
    kDHL_1004 = 11,
    kDHL_1005 = 12,
    kDHL_1006 = 13,
    kDHL_1007 = 14,
    kDHL_1008 = 15,
    kDHL_1009 = 16,
    kDHL_1010 = 17,
    kDHL_1011 = 18,
    kDHL_1012 = 19,
    kDHL_1013 = 20,
    kDHL_1014 = 21,
    kDHL_1500 = 22,
    kDHL_1015 = 23,
    kDHL_1800a = 24,
    kDHL_1800 = 25,
    kDHL_2100a = 26,
    kDHL_1021 = 27,
    kDHL_2400a = 28,
    kDHL_1024 = 29,
    kDHL_2700a = 30,
    kDHL_1027 = 31,
    kDHL_3200a = 32,
    kDHL_1032 = 33,
    kDHL_Newest = kDHL_1032,
    kDHL_CURRENT = kDHL_Newest,
    kDHL_Unknown = 254,
    kDHL_Max = 255
  };
  enum MaintenanceReleaseVersion
  {
    kMRelease0 = 0,
    kMRelease1 = 1,
    kMRelease2 = 2,
    kMRelease3 = 3,
    kMRelease4 = 4,
    kMRelease5 = 5,
    kMRelease6 = 6,
    kMRelease7 = 7,
    kMRelease8 = 8,
    kMRelease9 = 9,
    kMRelease10 = 10,
    kMRelease11 = 11,
    kMRelease12 = 12,
    kMRelease13 = 13,
    kMRelease14 = 14,
    kMRelease15 = 15,
    kMRelease16 = 16,
    kMRelease17 = 17,
    kMRelease18 = 18,
    kMRelease19 = 19,
    kMRelease20 = 20,
    kMRelease21 = 21,
    kMRelease22 = 22,
    kMRelease23 = 23,
    kMRelease24 = 24,
    kMRelease25 = 25,
    kMRelease26 = 26,
    kMRelease27 = 27,
    kMRelease28 = 28,
    kMRelease29 = 29,
    kMRelease30 = 30,
    kMRelease31 = 31,
    kMRelease32 = 32,
    kMRelease33 = 33,
    kMRelease34 = 34,
    kMRelease35 = 35,
    kMRelease36 = 36,
    kMRelease37 = 37,
    kMRelease38 = 38,
    kMRelease39 = 39,
    kMRelease40 = 40,
    kMRelease41 = 41,
    kMReleaseFirstValid1500 = kMRelease41,
    kMRelease42 = 42,
    kMRelease43 = 43,
    kMRelease44 = 44,
    kMRelease45 = 45,
    kMRelease46 = 46,
    kMRelease47 = 47,
    kMRelease48 = 48,
    kMRelease49 = 49,
    kMRelease50 = 50,
    kMRelease51 = 51,
    kMRelease52 = 52,
    kMRelease53 = 53,
    kMRelease54 = 54,
    kMRelease55 = 55,
    kMRelease56 = 56,
    kMRelease57 = 57,
    kMRelease58 = 58,
    kMRelease59 = 59,
    kMRelease60 = 60,
    kMRelease61 = 61,
    kMRelease62 = 62,
    kMRelease63 = 63,
    kMRelease64 = 64,
    kMRelease65 = 65,
    kMRelease66 = 66,
    kMRelease67 = 67,
    kMRelease68 = 68,
    kMRelease69 = 69,
    kMRelease70 = 70,
    kMRelease71 = 71,
    kMRelease72 = 72,
    kMRelease73 = 73,
    kMRelease74 = 74,
    kMRelease75 = 75,
    kMRelease76 = 76,
    kMRelease77 = 77,
    kMRelease78 = 78,
    kMRelease79 = 79,
    kMRelease80 = 80,
    kMRelease81 = 81,
    kMRelease82 = 82,
    kMRelease83 = 83,
    kMRelease84 = 84,
    kMRelease85 = 85,
    kMRelease86 = 86,
    kMRelease87 = 87,
    kMRelease88 = 88,
    kMRelease89 = 89,
    kMRelease90 = 90,
    kMRelease91 = 91,
    kMRelease92 = 92,
    kMRelease93 = 93,
    kMRelease94 = 94,
    kMRelease95 = 95,
    kMRelease96 = 96,
    kMRelease97 = 97,
    kMRelease98 = 98,
    kMRelease99 = 99,
    kMRelease100 = 100,
    kMRelease101 = 101,
    kMRelease102 = 102,
    kMRelease103 = 103,
    kMRelease104 = 104,
    kMRelease105 = 105,
    kMRelease106 = 106,
    kMRelease107 = 107,
    kMRelease108 = 108,
    kMRelease109 = 109,
    kMRelease110 = 110,
    kMRelease111 = 111,
    kMRelease112 = 112,
    kMRelease113 = 113,
    kMRelease114 = 114,
    kMRelease115 = 115,
    kMRelease116 = 116,
    kMRelease117 = 117,
    kMRelease118 = 118,
    kMRelease119 = 119,
    kMRelease120 = 120,
    kMRelease121 = 121,
    kMRelease122 = 122,
    kMRelease123 = 123,
    kMRelease124 = 124,
    kMRelease125 = 125,
    kMRelease126 = 126,
    kMRelease127 = 127,
    kMRelease128 = 128,
    kMRelease129 = 129,
    kMRelease130 = 130,
    kMRelease131 = 131,
    kMRelease132 = 132,
    kMRelease133 = 133,
    kMRelease134 = 134,
    kMRelease135 = 135,
    kMRelease136 = 136,
    kMRelease137 = 137,
    kMRelease138 = 138,
    kMRelease139 = 139,
    kMRelease140 = 140,
    kMRelease141 = 141,
    kMRelease142 = 142,
    kMRelease143 = 143,
    kMRelease144 = 144,
    kMRelease145 = 145,
    kMRelease146 = 146,
    kMRelease147 = 147,
    kMRelease148 = 148,
    kMRelease149 = 149,
    kMRelease150 = 150,
    kMRelease151 = 151,
    kMRelease152 = 152,
    kMRelease153 = 153,
    kMRelease154 = 154,
    kMRelease155 = 155,
    kMRelease156 = 156,
    kMRelease157 = 157,
    kMRelease158 = 158,
    kMRelease159 = 159,
    kMRelease160 = 160,
    kMRelease161 = 161,
    kMRelease162 = 162,
    kMRelease163 = 163,
    kMRelease164 = 164,
    kMRelease165 = 165,
    kMRelease166 = 166,
    kMRelease167 = 167,
    kMRelease168 = 168,
    kMRelease169 = 169,
    kMRelease170 = 170,
    kMRelease171 = 171,
    kMRelease172 = 172,
    kMRelease173 = 173,
    kMRelease174 = 174,
    kMRelease175 = 175,
    kMRelease176 = 176,
    kMRelease177 = 177,
    kMRelease178 = 178,
    kMRelease179 = 179,
    kMRelease180 = 180,
    kMRelease181 = 181,
    kMRelease182 = 182,
    kMRelease183 = 183,
    kMRelease184 = 184,
    kMRelease185 = 185,
    kMRelease186 = 186,
    kMRelease187 = 187,
    kMRelease188 = 188,
    kMRelease189 = 189,
    kMRelease190 = 190,
    kMRelease191 = 191,
    kMRelease192 = 192,
    kMRelease193 = 193,
    kMRelease194 = 194,
    kMRelease195 = 195,
    kMRelease196 = 196,
    kMRelease197 = 197,
    kMRelease198 = 198,
    kMRelease199 = 199,
    kMRelease200 = 200,
    kMRelease201 = 201,
    kMRelease202 = 202,
    kMRelease203 = 203,
    kMRelease204 = 204,
    kMRelease205 = 205,
    kMRelease206 = 206,
    kMRelease207 = 207,
    kMRelease208 = 208,
    kMRelease209 = 209,
    kMRelease210 = 210,
    kMRelease211 = 211,
    kMRelease212 = 212,
    kMRelease213 = 213,
    kMRelease214 = 214,
    kMRelease215 = 215,
    kMRelease216 = 216,
    kMRelease217 = 217,
    kMRelease218 = 218,
    kMRelease219 = 219,
    kMRelease220 = 220,
    kMRelease221 = 221,
    kMRelease222 = 222,
    kMRelease223 = 223,
    kMRelease224 = 224,
    kMRelease225 = 225,
    kMRelease226 = 226,
    kMRelease227 = 227,
    kMRelease228 = 228,
    kMRelease229 = 229,
    kMRelease230 = 230,
    kMRelease231 = 231,
    kMRelease232 = 232,
    kMRelease233 = 233,
    kMRelease234 = 234,
    kMRelease235 = 235,
    kMRelease236 = 236,
    kMRelease237 = 237,
    kMRelease238 = 238,
    kMRelease239 = 239,
    kMRelease240 = 240,
    kMRelease241 = 241,
    kMRelease242 = 242,
    kMRelease243 = 243,
    kMRelease244 = 244,
    kMRelease245 = 245,
    kMRelease246 = 246,
    kMRelease247 = 247,
    kMRelease248 = 248,
    kMRelease249 = 249,
    kMRelease250 = 250,
    kMRelease251 = 251,
    kMRelease252 = 252,
    kMRelease253 = 253,
    kMRelease254 = 254,
    kMRelease255 = 255,
    kMReleaseNewest = kMRelease55,
    kMRelease2010Newest = kMRelease226,
    kMReleaseCurrent = kMReleaseNewest,
    kMReleaseUnknown = 2147483646,
    kMReleaseMax = 2147483647,
    kMRelease2010Max = 255,
    kMReleaseExtendedNewest = kMRelease105,
    kMReleaseExtendedCurrent = kMReleaseExtendedNewest,
    kMReleaseCheckExtended = kMRelease125
  };
  enum SaveType
  {
    kNoSave = 0,
    kR12Save,
    kR13Save,
    kR14Save,
    k2000Save,
    k2004Save,
    k2007Save,
    k2010Save,
    k2013Save,
    k2018Save
  };
  enum GroupOperType
  {
    kNoOp = 0,
    kAdd = 1,
    kRemove = 2,
    kRename = 3,
    kOrdered = 4,
    kGrpDesc = 5,
    kSelect = 6,
    kCreate = 7,
    kPrepend = 8,
    kInsert = 9,
    kGrpFlags = 10
  };
  enum DeepCloneType
  {
    kDcCopy = 0,
    kDcExplode = 1,
    kDcBlock = 2,
    kDcXrefBind = 3,
    kDcSymTableMerge = 4,
    kDcInsert = 6,
    kDcWblock = 7,
    kDcObjects = 8,
    kDcXrefInsert = 9,
    kDcInsertCopy = 10,
    kDcWblkObjects = 11
  };
  enum DuplicateRecordCloning
  {
    kDrcNotApplicable = 0,
    kDrcIgnore = 1,
    kDrcReplace = 2,
    kDrcXrefMangleName = 3,
    kDrcMangleName = 4,
    kDrcUnmangleName = 5
  };
  enum XrefStatus
  {
    kXrfNotAnXref = 0,
    kXrfResolved = 1,
    kXrfUnloaded = 2,
    kXrfUnreferenced = 3,
    kXrfFileNotFound = 4,
    kXrfUnresolved = 5
  };
  enum XrefNotificationStatus
  {
    kXrfNotifyNone = 0,
    kXrfNotifyResolvedMatch = 1,
    kXrfNotifyResolvedElsewhere = 2,
    kXrfNotifyResolvedWithUpdate = 3,
    kXrfNotifyResolvedUpdateAvailable = 4
  };
  enum MeasurementValue
  {
    kEnglish = 0,
    kMetric = 1
  };
  enum UnitsValue
  {
    kUnitsUndefined = 0,
    kUnitsInches = 1,
    kUnitsFeet = 2,
    kUnitsMiles = 3,
    kUnitsMillimeters = 4,
    kUnitsCentimeters = 5,
    kUnitsMeters = 6,
    kUnitsKilometers = 7,
    kUnitsMicroinches = 8,
    kUnitsMils = 9,
    kUnitsYards = 10,
    kUnitsAngstroms = 11,
    kUnitsNanometers = 12,
    kUnitsMicrons = 13,
    kUnitsDecimeters = 14,
    kUnitsDekameters = 15,
    kUnitsHectometers = 16,
    kUnitsGigameters = 17,
    kUnitsAstronomical = 18,
    kUnitsLightYears = 19,
    kUnitsParsecs = 20,
    kUnitsUSSurveyFeet = 21,
    kUnitsUSSurveyInch = 22,
    kUnitsUSSurveyYard = 23,
    kUnitsUSSurveyMile = 24,
    kUnitsMax = kUnitsUSSurveyMile
  };
  enum TimeZone
  {
    kInternationalDateLine = -12000,
    kMidwayIsland = -11000,
    kHawaii = -10000,
    kAlaska = -9000,
    kPacific = -8000,
    kMountain = -7000,
    kArizona = -7001,
    kMazatlan = -7002,
    kCentral = -6000,
    kCentralAmerica = -6001,
    kMexicoCity = -6002,
    kSaskatchewan = -6003,
    kEastern = -5000,
    kIndiana = -5001,
    kBogota = -5002,
    kAtlanticCanada = -4000,
    kCaracas = -4001,
    kSantiago = -4002,
    kNewfoundland = -3300,
    kBrasilia = -3000,
    kBuenosAires = -3001,
    kGreenland = -3002,
    kMidAtlantic = -2000,
    kAzores = -1000,
    kCapeVerde = -1001,
    kUTC = 0,
    kGMT = 1,
    kMonrovia = 2,
    kBerlin = 1000,
    kParis = 1001,
    kPrague = 1002,
    kSarajevo = 1003,
    kWestCentralAfrica = 1004,
    kAthens = 2000,
    kEasternEurope = 2001,
    kCairo = 2002,
    kHarare = 2003,
    kHelsinki = 2004,
    kJerusalem = 2005,
    kMoscow = 3000,
    kRiyadh = 3001,
    kBaghdad = 3002,
    kEastAfrica = 3003,
    kTehran = 3300,
    kAbuDhabi = 4000,
    kCaucasus = 4001,
    kKabul = 4300,
    kEkaterinburg = 5000,
    kIslamabad = 5001,
    kKolkata = 5300,
    kKathmandu = 5450,
    kAlmaty = 6000,
    kDhaka = 6001,
    kSriLanka = 6002,
    kRangoon = 6300,
    kBangkok = 7000,
    kKrasnoyarsk = 7001,
    kBeijing = 8000,
    kSingapore = 8001,
    kTaipei = 8002,
    kIrkutsk = 8003,
    kPerth = 8004,
    kTokyo = 9000,
    kSeoul = 9001,
    kYakutsk = 9002,
    kAdelaide = 9300,
    kDarwin = 9301,
    kSydney = 10000,
    kGuam = 10001,
    kBrisbane = 10002,
    kHobart = 10003,
    kVladivostock = 10004,
    kMagadan = 11000,
    kWellington = 12000,
    kFiji = 12001,
    kTonga = 13000
  };
  enum LineWeight
  {
    kLnWt000 = 0,
    kLnWt005 = 5,
    kLnWt009 = 9,
    kLnWt013 = 13,
    kLnWt015 = 15,
    kLnWt018 = 18,
    kLnWt020 = 20,
    kLnWt025 = 25,
    kLnWt030 = 30,
    kLnWt035 = 35,
    kLnWt040 = 40,
    kLnWt050 = 50,
    kLnWt053 = 53,
    kLnWt060 = 60,
    kLnWt070 = 70,
    kLnWt080 = 80,
    kLnWt090 = 90,
    kLnWt100 = 100,
    kLnWt106 = 106,
    kLnWt120 = 120,
    kLnWt140 = 140,
    kLnWt158 = 158,
    kLnWt200 = 200,
    kLnWt211 = 211,
    kLnWtByLayer = -1,
    kLnWtByBlock = -2,
    kLnWtByLwDefault = -3
  };
  enum EndCaps
  {
    kEndCapNone = 0,
    kEndCapRound = 1,
    kEndCapAngle = 2,
    kEndCapSquare = 3
  };
  enum JoinStyle
  {
    kJnStylNone = 0,
    kJnStylRound = 1,
    kJnStylAngle = 2,
    kJnStylFlat = 3
  };
  enum PlotStyleNameType
  {
    kPlotStyleNameByLayer = 0,
    kPlotStyleNameByBlock = 1,
    kPlotStyleNameIsDictDefault = 2,
    kPlotStyleNameById = 3
  };
  enum IndexCreation
  {
    kNoIndex = 0,
    kIndexByLayer = 1,
    kIndexSpatially = 2
  };
  enum LayerEvaluation
  {
    kNoNewLayerEvaluation = 0,
    kEvalNewXrefLayers = 1,
    kEvalAllNewLayers = 2
  };
  enum NewLayerNotification
  {
    kNoNewLayerNotification = 0,
    kNotifyOnPlot = 1,
    kNotifyOnOpen = 2,
    kNotifyOnXrefAttachAndReload = 4,
    kNotifyOnLayerStateRestore = 8,
    kNotifyOnSave = 16,
    kNotifyOnInsert = 32
  };
  enum DimArrowFlags
  {
    kFirstArrow = 0x00,
    kSecondArrow = 0x01
  };
  enum DimblkFlags
  {
    kDimblk = 0,
    kDimblk1,
    kDimblk2,
    kDimLdrBlk
  };
  enum OrthographicView
  {
    kNonOrthoView = 0,
    kTopView = 1,
    kBottomView = 2,
    kFrontView = 3,
    kBackView = 4,
    kLeftView = 5,
    kRightView = 6
  };
  enum VpFreezeOps
  {
    kFreeze = 0,
    kThaw,
    kReset
  };
  enum reservedStringEnumType
  {
    kByLayer = 0,
    kByBlock = 1,
    kNone = 2,
    kContinuous = 3,
    kStandard = 4,
    kNormal = 5,
    kDefPoints = 6,
    kDefault = 7,
    kMissing = 8,
    kByColor = 9,
    kModel = 10,
    kGlobal = 11,
    kVS2DWireframe = 12,
    kVS3DWireframe = 13,
    kVS3DHidden = 14,
    kVSRealistic = 15,
    kVSConceptual = 16,
    kTitle = 17,
    kHeader = 18,
    kData = 19,
    kVSShadesOfGray = 20,
    kVSSketchy = 21,
    kVSXRay = 22,
    kVSShadedWithEdges = 23,
    kVSShaded = 24,
    kReservedStringCount
  };
  enum SortEntsFlags
  {
    kSortEntsSelection = 0x01,
    kSortEntsOsnap = 0x02,
    kSortEntsRedraw = 0x04,
    kSortEntsSlide = 0x08,
    kSortEntsRegen = 0x10,
    kSortEntsPlot = 0x20,
    kSortEntsPsout = 0x40
  };
  enum DragStat
  {
    kDragStart = 0,
    kDragEnd = 1,
    kDragAbort = 2
  };
  enum GripStat
  {
    kGripsDone = 0,
    kGripsToBeDeleted = 1,
    kDimDataToBeDeleted = 2
  };
  enum DataLinkOption
  {
    kDataLinkOptionNone = 0,
    kDataLinkOptionAnonymous = 0x1,
    kDataLinkOptionPersistCache = 0x2,
    kDataLinkOptionObsolete = 0x4,
    kDataLinkHasCutomData = 0x8
  };
  enum PathOption
  {
    kNoPath = 1,
    kRelativePath = 2,
    kAbsolutePath = 3,
    kPathAndFile = 4
  };
  enum UpdateDirection
  {
    kUpdateDirSourceToData = 0x1,
    kUpdateDirDataToSource = 0x2
  };
  enum UpdateOption
  {
    kUpdateOptionNone = 0,
    kUpdateOptionSkipFormat = 0x20000,
    kUpdateOptionUpdateRowHeight = 0x40000,
    kUpdateOptionUpdateColumnWidth = 0x80000,
    kUpdateOptionAllowSourceUpdate = 0x100000,
    kUpdateOptionForceFullSourceUpdate = 0x200000,
    kUpdateOptionOverwriteContentModifiedAfterUpdate = 0x400000,
    kUpdateOptionOverwriteFormatModifiedAfterUpdate = 0x800000,
    kUpdateOptionForPreview = 0x1000000,
    kUpdateOptionIncludeXrefs = 0x2000000,
    kSkipFormatAfterFirstUpdate = 0x4000000
  };
  enum DataLinkGetSourceContext
  {
    kDataLinkGetSourceContextUnknown = 0,
    kDataLinkGetSourceContextEtransmit = 1,
    kDataLinkGetSourceContextXrefManager = 2,
    kDataLinkGetSourceContextFileWatcher = 3,
    kDataLinkGetSourceContextOther = 4,
    kDataLinkGetSourceContextOrignalPath = (0x1 << 8)
  };
  enum CellType
  {
    kUnknownCell = 0,
    kTextCell = 1,
    kBlockCell = 2,
    kMultipleContentCell = 3
  };
  enum CellContentType
  {
    kCellContentTypeUnknown = 0,
    kCellContentTypeValue = 0x1,
    kCellContentTypeField = 0x2,
    kCellContentTypeBlock = 0x4
  };
  enum CellEdgeMask
  {
    kTopMask = 1,
    kRightMask = 2,
    kBottomMask = 4,
    kLeftMask = 8
  };
  enum CellMargin
  {
    kCellMarginTop = 0x1,
    kCellMarginLeft = 0x2,
    kCellMarginBottom = 0x4,
    kCellMarginRight = 0x8,
    kCellMarginHorzSpacing = 0x10,
    kCellMarginVertSpacing = 0x20
  };
  enum CellContentLayout
  {
    kCellContentLayoutFlow = 0x1,
    kCellContentLayoutStackedHorizontal = 0x2,
    kCellContentLayoutStackedVertical = 0x4
  };
  enum CellState
  {
    kCellStateNone = 0,
    kCellStateContentLocked = 0x1,
    kCellStateContentReadOnly = 0x2,
    kCellStateLinked = 0x4,
    kCellStateContentModifiedAfterUpdate = 0x8,
    kCellStateFormatLocked = 0x10,
    kCellStateFormatReadOnly = 0x20,
    kCellStateFormatModifiedAfterUpdate = 0x40,
    kAllCellStates = (kCellStateContentLocked | kCellStateContentReadOnly | kCellStateLinked | kCellStateContentModifiedAfterUpdate | kCellStateFormatLocked | kCellStateFormatReadOnly | kCellStateFormatModifiedAfterUpdate)
  };
  enum CellClass
  {
    kCellClassNone = 0,
    kCellClassLabel = 0x1,
    kCellClassData = 0x2
  };
  enum CellProperty
  {
    kCellPropInvalid = 0,
    kCellPropDataType = 0x1,
    kCellPropDataFormat = 0x2,
    kCellPropRotation = 0x4,
    kCellPropScale = 0x8,
    kCellPropAlignment = 0x10,
    kCellPropContentColor = 0x20,
    kCellPropTextStyle = 0x40,
    kCellPropTextHeight = 0x80,
    kCellPropAutoScale = 0x100,
    kCellPropBackgroundColor = 0x200,
    kCellPropMarginLeft = 0x400,
    kCellPropMarginTop = 0x800,
    kCellPropMarginRight = 0x1000,
    kCellPropMarginBottom = 0x2000,
    kCellPropMarginHorzSpacing = 0x20000,
    kCellPropMarginVertSpacing = 0x40000,
    kCellPropContentLayout = 0x4000,
    kCellPropMergeAll = 0x8000,
    kCellPropFlowDirBtoT = 0x10000,
    kCellPropDataTypeAndFormat = (kCellPropDataType | kCellPropDataFormat),
    kCellPropContent = (kCellPropDataType | kCellPropDataFormat | kCellPropRotation | kCellPropScale | kCellPropContentColor | kCellPropTextStyle | kCellPropTextHeight | kCellPropAutoScale),
    kCellPropBitProperties = (kCellPropAutoScale | kCellPropMergeAll | kCellPropFlowDirBtoT),
    kCellPropAll = (kCellPropDataType | kCellPropDataFormat | kCellPropRotation | kCellPropScale | kCellPropAlignment | kCellPropContentColor | kCellPropBackgroundColor | kCellPropTextStyle | kCellPropTextHeight | kCellPropMarginLeft | kCellPropMarginTop | kCellPropMarginRight | kCellPropMarginBottom | kCellPropMarginHorzSpacing | kCellPropMarginVertSpacing | kCellPropAutoScale | kCellPropMergeAll | kCellPropFlowDirBtoT | kCellPropContentLayout)
  };
  enum GridProperty
  {
    kGridPropInvalid = 0,
    kGridPropLineStyle = 0x1,
    kGridPropLineWeight = 0x2,
    kGridPropLinetype = 0x4,
    kGridPropColor = 0x8,
    kGridPropVisibility = 0x10,
    kGridPropDoubleLineSpacing = 0x20,
    kGridPropAll = (kGridPropLineStyle | kGridPropLineWeight | kGridPropLinetype | kGridPropColor | kGridPropVisibility | kGridPropDoubleLineSpacing)
  };
  enum GridLineType
  {
    kInvalidGridLine = 0,
    kHorzTop = 1,
    kHorzInside = 2,
    kHorzBottom = 4,
    kVertLeft = 8,
    kVertInside = 0x10,
    kVertRight = 0x20,
    kHorzGridLineTypes = kHorzTop | kHorzBottom | kHorzInside,
    kVertGridLineTypes = kVertLeft | kVertRight | kVertInside,
    kOuterGridLineTypes = kHorzTop | kHorzBottom | kVertLeft | kVertRight,
    kInnerGridLineTypes = kHorzInside | kVertInside,
    kAllGridLineTypes = kOuterGridLineTypes | kInnerGridLineTypes
  };
  enum GridLineStyle
  {
    kGridLineStyleSingle = 1,
    kGridLineStyleDouble = 2
  };
  enum CellOption
  {
    kCellOptionNone = 0,
    kInheritCellFormat = 0x1
  };
  enum SelectType
  {
    kWindow = 1,
    kCrossing = 2
  };
  enum FlowDirection
  {
    kTtoB = 0,
    kBtoT = 1
  };
  enum RotationAngle
  {
    kDegreesUnknown = -1,
    kDegrees000 = 0,
    kDegrees090 = 1,
    kDegrees180 = 2,
    kDegrees270 = 3
  };
  enum CellAlignment
  {
    kTopLeft = 1,
    kTopCenter = 2,
    kTopRight = 3,
    kMiddleLeft = 4,
    kMiddleCenter = 5,
    kMiddleRight = 6,
    kBottomLeft = 7,
    kBottomCenter = 8,
    kBottomRight = 9
  };
  enum RowType
  {
    kUnknownRow = 0,
    kDataRow = 1,
    kTitleRow = 2,
    kHeaderRow = 4,
    kAllRowTypes = kDataRow | kTitleRow | kHeaderRow
  };
  enum TableStyleFlags
  {
    kHorzInsideLineFirst = 0x1,
    kHorzInsideLineSecond = 0x2,
    kHorzInsideLineThird = 0x4,
    kTableStyleModified = 0x8,
    kTableStyleDataTypeModified = 0x10
  };
  enum TableBreakOption
  {
    kTableBreakNone = 0,
    kTableBreakEnableBreaking = 0x1,
    kTableBreakRepeatTopLabels = 0x2,
    kTableBreakRepeatBottomLabels = 0x4,
    kTableBreakAllowManualPositions = 0x8,
    kTableBreakAllowManualHeights = 0x10
  };
  enum TableBreakFlowDirection
  {
    kTableBreakFlowRight = 0x1,
    kTableBreakFlowDownOrUp = 0x2,
    kTableBreakFlowLeft = 0x4
  };
  enum TableFillOption
  {
    kTableFillNone = 0,
    kTableFillRow = 0x1,
    kTableFillReverse = 0x2,
    kTableFillGenerateSeries = 0x4,
    kTableFillCopyContent = 0x8,
    kTableFillCopyFormat = 0x10,
    kTableFillOverwriteReadOnlyContent = 0x20,
    kTableFillOverwriteReadOnlyFormat = 0x40
  };
  enum TableCopyOption
  {
    kTableCopyNone = 0,
    kTableCopyExpandOrContractTable = 0x1,
    kTableCopySkipContent = 0x2,
    kTableCopySkipValue = 0x4,
    kTableCopySkipField = 0x8,
    kTableCopySkipFormula = 0x10,
    kTableCopySkipBlock = 0x20,
    kTableCopySkipDataLink = 0x40,
    kTableCopySkipLabelCell = 0x80,
    kTableCopySkipDataCell = 0x100,
    kTableCopySkipFormat = 0x200,
    kTableCopySkipCellStyle = 0x400,
    kTableCopyConvertFormatToOverrides = 0x800,
    kTableCopySkipCellState = 0x1000,
    kTableCopySkipContentFormat = 0x2000,
    kTableCopySkipDissimilarContentFormat = 0x4000,
    kTableCopySkipGeometry = 0x8000,
    kTableCopySkipMerges = 0x10000,
    kTableCopyFillTarget = 0x20000,
    kTableCopyOverwriteReadOnlyContent = 0x40000,
    kTableCopyOverwriteReadOnlyFormat = 0x80000,
    kTableCopyOverwriteContentModifiedAfterUpdate = 0x100000,
    kTableCopyOverwriteFormatModifiedAfterUpdate = 0x200000,
    kTableCopyOnlyContentModifiedAfterUpdate = 0x400000,
    kTableCopyOnlyFormatModifiedAfterUpdate = 0x800000,
    kTableCopyRowHeight = 0x1000000,
    kTableCopyColumnWidth = 0x2000000,
    kTableCopyFullCellState = 0x4000000,
    kTableCopyForRountrip = 0x8000000,
    kTableCopyConvertFieldToValue = 0x10000000,
    kTableCopySkipFieldTranslation = 0x20000000
  };
  enum TableIteratorOption
  {
    kTableIteratorNone = 0,
    kTableIteratorIterateSelection = 0x1,
    kTableIteratorIterateRows = 0x2,
    kTableIteratorIterateColumns = 0x4,
    kTableIteratorIterateDataLinks = 0x80,
    kTableIteratorReverseOrder = 0x8,
    kTableIteratorSkipReadOnlyContent = 0x10,
    kTableIteratorSkipReadOnlyFormat = 0x20,
    kTableIteratorSkipMerged = 0x40
  };
  enum MergeCellStyleOption
  {
    kMergeCellStyleNone = 0,
    kMergeCellStyleCopyDuplicates = 0x1,
    kMergeCellStyleOverwriteDuplicates = 0x2,
    kMergeCellStyleConvertDuplicatesToOverrides = 0x4,
    kMergeCellStyleIgnoreNewStyles = 0x8
  };
  enum TableHitItem
  {
    kTableHitNone = 0,
    kTableHitCell = 0x1,
    kTableHitRowIndicator = 0x2,
    kTableHitColumnIndicator = 0x4,
    kTableHitGridLine = 0x8
  };
  enum RowTypes
  {
    kAllRows = kDataRow | kTitleRow | kHeaderRow
  };
  enum GridLineTypes
  {
    kAllGridLines = kAllGridLineTypes
  };
  enum DrawOrderFlags
  {
    kDrawOrderInPlaceEditOn = 0x01,
    kDrawOrderInheritanceOn = 0x02
  };
  enum UpdateThumbnailFlags
  {
    kUpdateModelViews = 0x01,
    kUpdateSheetViews = 0x02,
    kUpdateSheets = 0x04,
    kUpdateWhenAccessed = 0x08,
    kUpdateWhenSaving = 0x10
  };
  enum EnhancedBlockEvalType
  {
    kInitialization = 1,
    kForUpdate = 2,
    kForRefresh = 3
  };
  enum SliceModelType
  {
    kKeepBothSides = 0x01,
    kUseCurrentColor = 0x02
  };
  enum CollisionType
  {
    kCollisionTypeNone = 0,
    kCollisionTypeSolid = 1
  };
  enum LoftParamType
  {
    kLoftNoParam = 0x00,
    kLoftNoTwist = 0x01,
    kLoftAlignDirection = 0x02,
    kLoftSimplify = 0x04,
    kLoftClose = 0x08,
    kLoftPeriodic = 0x10,
    kLoftDefault = kLoftNoTwist | kLoftAlignDirection | kLoftSimplify
  };
  enum LoftNormalsType
  {
    kLoftRuled = 0,
    kLoftSmooth = 1,
    kLoftFirstNormal = 2,
    kLoftLastNormal = 3,
    kLoftEndsNormal = 4,
    kLoftAllNormal = 5,
    kLoftUseDraftAngles = 6
  };
  enum ShadowFlags
  {
    kShadowsCastAndReceive = 0x00,
    kShadowsDoesNotReceive = 0x01,
    kShadowsDoesNotCast = 0x02,
    kShadowsIgnore = kShadowsDoesNotCast | kShadowsDoesNotReceive
  };
  enum LightingUnits
  {
    kLightingUnitsGeneric = 0,
    kLightingUnitsAmerican = 1,
    kLightingUnitsInternational = 2
  };
  enum FilletTrimMode
  {
    kTrimNone = 0,
    kTrimFirst = 1,
    kTrimSecond = 2,
    kTrimBoth = 3
  };
    /// <summary>
    /// The type of a constrained implicit point.
    /// </summary>
    ///
  enum ImplicitPointType
  {
        /// <summary>
        /// Start point of bounded line, arc or bounded ellipse.
        /// </summary>
        ///
    kStartImplicit = 0,
        /// <summary>
        /// End point of a bounded line (not valid for ray), arc or bounded ellipse.
        /// </summary>
        ///
    kEndImplicit,
        /// <summary>
        /// Mid point of a bounded line (not valid for ray) or arc.
        /// </summary>
        ///
    kMidImplicit,
        /// <summary>
        /// Center point of a circle, arc, ellipse or bounded ellipse.
        /// </summary>
        ///
    kCenterImplicit,
        /// <summary>
        /// Define point of a parametric curve, currently only valid for spline control point.
        /// </summary>
        ///
    kDefineImplicit
  };
};
#  pragma  pack(pop)
#endif
