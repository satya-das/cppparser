//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ACPLPLOTINFO_H
#  define _ACPLPLOTINFO_H
#  include "AcPlObject.h"
class AcPlPlotConfig;
class AcRxObject;
class AcDbPlotSettings;
class AcPlPlotInfo : public AcPlObject
{
public:
  ACPL_PORT AcPlPlotInfo();
  ACPL_PORT virtual ~AcPlPlotInfo();
  ACPL_DECLARE_MEMBERS(AcPlPlotInfo);
  enum MergeStatus
  {
    kNoChanges = 0x00000000,
    kPlotCfgName = 0x00000001,
    kPlotPaperMargins = 0x00000002,
    kPlotPaperSize = 0x00000004,
    kCanonicalMediaName = 0x00000008,
    kPlotOrigin = 0x00000010,
    kPlotPaperUnits = 0x00000020,
    kPlotViewportBorders = 0x00000040,
    kPlotPlotStyles = 0x00000080,
    kShowPlotStyles = 0x00000100,
    kPlotRotation = 0x00000200,
    kPlotCentered = 0x00000400,
    kPlotHidden = 0x00000800,
    kShadePlot = 0x00001000,
    kShadePlotResLevel = 0x00002000,
    kShadePlotCustomDPI = 0x00004000,
    kPlotType = 0x00008000,
    kPlotWindowArea = 0x00010000,
    kPlotViewName = 0x00020000,
    kScale = 0x00040000,
    kCurrentStlyeSheet = 0x00080000,
    kScaleLineWeights = 0x00100000,
    kPrintLineWeights = 0x00200000,
    kDrawViewportsFirst = 0x00400000,
    kPlotTransparency = 0x00800000
  };
  ACPL_PORT Acad::ErrorStatus copyFrom(const AcRxObject* pOther);
  ACPL_PORT void setLayout(AcDbObjectId& layoutId);
  ACPL_PORT AcDbObjectId layout() const;
  ACPL_PORT void setOverrideSettings(const AcDbPlotSettings* pOverrides);
  ACPL_PORT const AcDbPlotSettings* overrideSettings() const;
  ACPL_PORT void setDeviceOverride(const AcPlPlotConfig* pconf);
  ACPL_PORT const AcDbPlotSettings* validatedSettings() const;
  ACPL_PORT Acad::ErrorStatus setValidatedSettings(const AcDbPlotSettings* pValidatedSettings);
  ACPL_PORT const AcPlPlotConfig* validatedConfig() const;
  ACPL_PORT void setValidatedConfig(const AcPlPlotConfig* pConfig);
  ACPL_PORT const AcPlPlotConfig* deviceOverride() const;
  ACPL_PORT bool isValidated() const;
  ACPL_PORT unsigned long mergeStatus() const;
  ACPL_PORT bool isCompatibleDocument(const AcPlPlotInfo* pOtherInfo) const;
  ACPL_PORT AcString& OrgFilePath()
  {
    return m_OrgFilePath;
  }
private:
  AcString m_OrgFilePath;
};
#endif
