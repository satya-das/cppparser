//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACPLPLOTCONFIG_H
#  define ACPLPLOTCONFIG_H
#  include "AcPl.h"
#  include "AcArray.h"
#  include "gepnt2d.h"
#  include "geblok2d.h"
#  include "dblayout.h"
class HT_Plot_Config;
class HT_Media_Size;
class HT_Media_Description;
class AcPlPlotConfig : public AcPlObject
{
  ACPL_DECLARE_MEMBERS(AcPlPlotConfig)
public:
  enum PlotToFileCapability
  {
    kNoPlotToFile = 0,
    kPlotToFileAllowed = 1,
    kMustPlotToFile = 2
  };
  ACPL_PORT virtual ~AcPlPlotConfig();
  ACPL_PORT virtual Acad::ErrorStatus copyFrom(const AcRxObject* pSrc);
  ACPL_PORT virtual void getDescriptionFields(ACHAR*& pDriverName, ACHAR*& pLocationName, ACHAR*& pComment, ACHAR*& pPortName, ACHAR*& pServerName, ACHAR*& pTagLine) const;
  ACPL_PORT virtual const ACHAR* deviceName() const;
  ACPL_PORT virtual const ACHAR* fullPath() const;
  ACPL_PORT virtual unsigned int maxDeviceDPI() const;
  ACPL_PORT virtual unsigned long deviceType() const;
  ACPL_PORT virtual void getCanonicalMediaNameList(AcArray<ACHAR*>& mediaList) const;
  ACPL_PORT virtual void getLocalMediaName(const ACHAR* pCanonicalMediaName, ACHAR*& pLocalMediaName) const;
  ACPL_PORT virtual void getMediaBounds(const ACHAR* pCanonicalMediaName, AcGePoint2d& pageSize, AcGeBoundBlock2d& printableArea) const;
  ACPL_PORT virtual void refreshMediaNameList();
  ACPL_PORT virtual bool isPlotToFile() const;
  ACPL_PORT virtual Acad::ErrorStatus setPlotToFile(bool bPlotToFile);
  ACPL_PORT virtual Acad::ErrorStatus getDefaultFileExtension(const ACHAR*& pDefaultExtension) const;
  ACPL_PORT virtual PlotToFileCapability plotToFileCapability() const;
  ACPL_PORT virtual bool saveToPC3(const ACHAR* pPC3Name);
  ACPL_PORT virtual HT_Plot_Config* plotConfig() const;
  ACPL_PORT virtual unsigned long isCustomPossible(double width, double height, bool bIsDimensional, bool bIsSheet, int dpi, const ACHAR* pPC3Dir) const;
  ACPL_PORT virtual bool matchMediaSize(double page_x, double page_y, double printable_w, double printable_h, AcDbLayout::PlotPaperUnits units, bool bIsSheet, int dpi, const ACHAR* pTargetCanonicalName, ACHAR*& pNearestSizeName, ACHAR*& pLocalizedName, double& scaleFactor);
  ACPL_PORT virtual Acad::ErrorStatus makeCustomMediaFromSizeDesc(HT_Media_Size* pSize, HT_Media_Description* pDesc, bool bSameDriver, bool bSavePC3, const ACHAR* pSourceEntry, const ACHAR* pSourceName, ACHAR*& pCanonicalSizeName, ACHAR*& pLocalizedSizeName, ACHAR*& pPMPPath, ACHAR*& pPC3Path, int dpi, double& scaleFactor);
protected:
  friend class AcPlPlotConfigManagerImp;
  friend class AcPlPlotInfoImp;
  friend class AcPlPlotInfoValidatorImp;
  AcPlPlotConfig(HT_Plot_Config* pConfig, const ACHAR* pDevName, const ACHAR* pFullPath, unsigned long nDevType);
  AcPlPlotConfig(const AcPlPlotConfig* pOther);
private:
  AcPlPlotConfig();
};
#endif
