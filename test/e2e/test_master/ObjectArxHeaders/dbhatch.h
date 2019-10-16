//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBHATCH_H
#  define AD_DBHATCH_H	1
#  include "acdb.h"
#  include "dbmain.h"
#  include "gelnsg2d.h"
#  include "gelnsg3d.h"
#  include "gearc2d.h"
#  include "gearc3d.h"
#  include "gept2dar.h"
#  include "gevptar.h"
#  include "geintarr.h"
#  pragma  pack(push, 8)
#  define HATCH_PATTERN_NAME_LENGTH	35
#  define GRADIENT_PATTERN_NAME_LENGTH	32
#  define GRADIENT_COLOR_NAME_LENGTH	256
class AcDbRegion;
class AcDbHatch : public AcDbEntity
{
public:
  enum HatchObjectType
  {
    kHatchObject = 0,
    kGradientObject = 1
  };
  enum HatchLoopType
  {
    kDefault = 0,
    kExternal = 1,
    kPolyline = 2,
    kDerived = 4,
    kTextbox = 8,
    kOutermost = 0x10,
    kNotClosed = 0x20,
    kSelfIntersecting = 0x40,
    kTextIsland = 0x80,
    kDuplicate = 0x100,
    kIsAnnotative = 0x200,
    kDoesNotSupportScale = 0x400,
    kForceAnnoAllVisible = 0x800,
    kOrientToPaper = 0x1000,
    kIsAnnotativeBlock = 0x2000
  };
  enum HatchEdgeType
  {
    kLine = 1,
    kCirArc = 2,
    kEllArc = 3,
    kSpline = 4
  };
  enum HatchPatternType
  {
    kUserDefined = 0,
    kPreDefined = 1,
    kCustomDefined = 2
  };
  enum HatchStyle
  {
    kNormal = 0,
    kOuter = 1,
    kIgnore = 2
  };
  enum GradientPatternType
  {
    kPreDefinedGradient = 0,
    kUserDefinedGradient = 1
  };
  AcDbHatch();
  virtual ~AcDbHatch();
  ACDB_DECLARE_MEMBERS(AcDbHatch);
  double elevation() const;
  Acad::ErrorStatus setElevation(double elevation);
  AcGeVector3d normal() const;
  Acad::ErrorStatus setNormal(const AcGeVector3d& normal);
  virtual Adesk::Boolean isPlanar() const override
  {
    return true;
  }
  virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const override;
  AcCmColor backgroundColor() const;
  Acad::ErrorStatus setBackgroundColor(const AcCmColor& color);
  int numLoops() const;
  Adesk::Int32 loopTypeAt(int loopIndex) const;
  Acad::ErrorStatus getLoopAt(int loopIndex, Adesk::Int32& loopType, AcGeVoidPointerArray& edgePtrs, AcGeIntArray& edgeTypes) const;
  Acad::ErrorStatus getLoopAt(int loopIndex, Adesk::Int32& loopType, AcGePoint2dArray& vertices, AcGeDoubleArray& bulges) const;
  Acad::ErrorStatus appendLoop(Adesk::Int32 loopType, const AcGeVoidPointerArray& edgePtrs, const AcGeIntArray& edgeTypes);
  Acad::ErrorStatus appendLoop(Adesk::Int32 loopType, const AcGePoint2dArray& vertices, const AcGeDoubleArray& bulges);
  Acad::ErrorStatus insertLoopAt(int loopIndex, Adesk::Int32 loopType, const AcGeVoidPointerArray& edgePtrs, const AcGeIntArray& edgeTypes);
  Acad::ErrorStatus insertLoopAt(int loopIndex, Adesk::Int32 loopType, const AcGePoint2dArray& vertices, const AcGeDoubleArray& bulges);
  Acad::ErrorStatus removeLoopAt(int loopIndex);
  bool associative() const;
  Acad::ErrorStatus setAssociative(bool isAssociative);
  Acad::ErrorStatus appendLoop(Adesk::Int32 loopType, const AcDbObjectIdArray& dbObjIds);
  Acad::ErrorStatus insertLoopAt(int loopIndex, Adesk::Int32 loopType, const AcDbObjectIdArray& dbObjIds);
  Acad::ErrorStatus getAssocObjIdsAt(int loopIndex, AcDbObjectIdArray& dbObjIds) const;
  Acad::ErrorStatus getAssocObjIds(AcDbObjectIdArray& dbObjIds) const;
  Acad::ErrorStatus removeAssocObjIds();
  AcDbHatch::HatchObjectType hatchObjectType() const;
  Acad::ErrorStatus setHatchObjectType(AcDbHatch::HatchObjectType type);
  virtual Adesk::Boolean isGradient() const;
  virtual Adesk::Boolean isHatch() const;
  AcDbHatch::GradientPatternType gradientType() const;
  const ACHAR* gradientName() const;
  Acad::ErrorStatus setGradient(AcDbHatch::GradientPatternType gradType, const ACHAR* gradName);
  double gradientAngle() const;
  Acad::ErrorStatus setGradientAngle(double angle);
  Acad::ErrorStatus getGradientColors(unsigned int& count, AcCmColor*& colors, float*& values);
  Acad::ErrorStatus setGradientColors(unsigned int count, AcCmColor* colors, float* values);
  Adesk::Boolean getGradientOneColorMode() const;
  Acad::ErrorStatus setGradientOneColorMode(Adesk::Boolean oneColorMode);
  float getShadeTintValue() const;
  Acad::ErrorStatus setShadeTintValue(float value);
  Acad::ErrorStatus setShadeTintValueAndColor2(float value);
  float gradientShift() const;
  Acad::ErrorStatus setGradientShift(float shiftValue);
  Acad::ErrorStatus evaluateGradientColorAt(float value, AcCmColor& color);
  AcDbHatch::HatchPatternType patternType() const;
  Using PatternName = ACHAR[HATCH_PATTERN_NAME_LENGTH];
  ACDBCORE2D_PORT const PatternNameArray& patternName() const;
  Acad::ErrorStatus setPattern(AcDbHatch::HatchPatternType patType, const ACHAR* patName);
  double patternAngle() const;
  Acad::ErrorStatus setPatternAngle(double angle);
  double patternSpace() const;
  Acad::ErrorStatus setPatternSpace(double space);
  double patternScale() const;
  Acad::ErrorStatus setPatternScale(double scale);
  bool patternDouble() const;
  Acad::ErrorStatus setPatternDouble(bool isDouble);
  int numPatternDefinitions() const;
  Acad::ErrorStatus getPatternDefinitionAt(int index, double& angle, double& baseX, double& baseY, double& offsetX, double& offsetY, AcGeDoubleArray& dashes) const;
  AcDbHatch::HatchStyle hatchStyle() const;
  Acad::ErrorStatus setHatchStyle(AcDbHatch::HatchStyle hstyle);
  Acad::ErrorStatus evaluateHatch(bool bUnderestimateNumLines = false);
  Acad::ErrorStatus evaluateHatchAllScales(bool bUnderestimateNumLines = false);
  bool lineGenerationEnabled() const;
  bool setLineGenerationEnabled(bool bEnable);
  int numHatchLines() const;
  bool isSolidFill() const;
  Acad::ErrorStatus getHatchLineDataAt(int index, AcGePoint2d& startPt, AcGePoint2d& endPt) const;
  Acad::ErrorStatus getHatchLinesData(AcGePoint2dArray& startPts, AcGePoint2dArray& endPts) const;
  virtual void modifiedGraphics(const AcDbEntity* pObj) override;
  virtual Acad::ErrorStatus subSwapIdWith(AcDbObjectId otherId, Adesk::Boolean swapXdata = false, Adesk::Boolean swapExtDict = false) override;
  virtual Acad::ErrorStatus swapReferences(const AcDbIdMapping& idMap) override;
  Acad::ErrorStatus getArea(double& a) const;
  Acad::ErrorStatus setOriginPoint(const AcGePoint2d& pt);
  AcGePoint2d originPoint() const;
  AcDbRegion* getRegionArea() const;
  void removeHatchLines();
protected:
  virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
#  pragma  pack(pop)
#endif
