//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _DBOSNAP_H
#  define _DBOSNAP_H
#  include "Adesk.h"
#  pragma  warning (disable: 4786)
#  pragma  pack (push, 8)
class AcDbCustomOsnapInfo : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbCustomOsnapInfo);
  virtual Acad::ErrorStatus getOsnapInfo(AcDbEntity* pickedObject, Adesk::GsMarker gsSelectionMark, const AcGePoint3d& pickPoint, const AcGePoint3d& lastPoint, const AcGeMatrix3d& viewXform, AcArray<AcGePoint3d>& snapPoints, AcDbIntArray& geomIdsForPts, AcArray<AcGeCurve3d*>& snapCurves, AcDbIntArray& geomIdsForLines) = 0;
};
class AcGiGlyph : public AcGiDrawable
{
public:
  ACRX_DECLARE_MEMBERS(AcGiGlyph);
  virtual Acad::ErrorStatus setLocation(const AcGePoint3d& dcsPoint) = 0;
  virtual Adesk::Boolean isPersistent() const override
  {
    return Adesk::kFalse;
  }
  virtual AcDbObjectId id() const override
  {
    return 0;
  }
protected:
  virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits*) override
  {
    return 0;
  }
  virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw*) override
  {
    return Adesk::kFalse;
  }
  virtual void subViewportDraw(AcGiViewportDraw* vportDrawContext) = 0;
};
class AcDbCustomOsnapMode
{
public:
  virtual const ACHAR* localModeString() const = 0;
  virtual const ACHAR* globalModeString() const = 0;
  virtual const AcRxClass* entityOsnapClass() const = 0;
  virtual AcGiGlyph* glyph() const = 0;
  virtual const ACHAR* tooltipString() const = 0;
  virtual ~AcDbCustomOsnapMode()
  {
  }
};
class AcDbCustomOsnapManager
{
public:
  virtual ~AcDbCustomOsnapManager()
  {
  }
  virtual Acad::ErrorStatus addCustomOsnapMode(AcDbCustomOsnapMode* pMode) = 0;
  virtual Acad::ErrorStatus removeCustomOsnapMode(AcDbCustomOsnapMode* pMode) = 0;
  virtual Acad::ErrorStatus activateOsnapMode(const ACHAR* modeStr) = 0;
  virtual Acad::ErrorStatus deactivateOsnapMode(const ACHAR* modeStr) = 0;
  virtual Adesk::Boolean modeIsActive(const ACHAR* modeStr) = 0;
  virtual int osnapGlyphSize() const = 0;
};
AcDbCustomOsnapManager* acdbCustomOsnapManager();
__declspec (dllexport) bool acedIsOsnapOverride();
#  pragma  pack (pop)
#endif
