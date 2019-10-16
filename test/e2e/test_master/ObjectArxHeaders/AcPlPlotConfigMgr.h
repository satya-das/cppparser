//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACPLPLOTCONFIGMGR_H
#  define ACPLPLOTCONFIGMGR_H
#  include "AdAChar.h"
#  include "AcPl.h"
#  include "AcArray.h"
#  include "AcPlObject.h"
class AcPlPlotConfig;
class HT_Thin_Plot_Config_Manager;
class HT_Error_Handler;
enum DeviceType
{
  kSystemPrinter = 0,
  kPC3File = 1,
  kOneOffConfig = 2,
  kUninitialized = -1
};
class AcPlPlotConfigInfo : public AcPlObject
{
public:
  ACPL_PORT AcPlPlotConfigInfo();
  ACPL_PORT AcPlPlotConfigInfo(const ACHAR* pDevName, const ACHAR* pFullPath, DeviceType devType);
  ACPL_PORT AcPlPlotConfigInfo(const AcPlPlotConfigInfo& copy);
  ACPL_PORT Acad::ErrorStatus copyFrom(const AcRxObject* pSrc);
  ACPL_PORT const AcPlPlotConfigInfo& operator=(const AcPlPlotConfigInfo& src);
  ACPL_PORT virtual ~AcPlPlotConfigInfo();
  ACPL_DECLARE_MEMBERS(AcPlPlotConfigInfo);
  ACPL_PORT const ACHAR* fullPath() const;
  ACPL_PORT void setFullPath(const ACHAR* pPath);
  ACPL_PORT const ACHAR* deviceName() const;
  ACPL_PORT void setDeviceName(const ACHAR* pDevName);
  ACPL_PORT DeviceType deviceType() const;
  ACPL_PORT void setDeviceType(DeviceType devType);
  ACPL_PORT const ACHAR* deviceId() const;
  ACPL_PORT void setDeviceId(const ACHAR* pDevId);
};
class ADESK_NO_VTABLE AcPlPlotConfigManager
{
public:
  enum RefreshCode
  {
    kAll,
    kRefreshDevicesList,
    kRefreshStyleList,
    kRefreshSystemDevicesList,
    kRefreshPC3DevicesList
  };
  enum StyTypes
  {
    kUndefined = 0,
    kRegular = 0x01,
    kTranslation = 0x02,
    kColorDep = 0x04,
    kAllTypes = 0x07
  };
  enum StdConfigs
  {
    kNoneDevice,
    kDefaultWindowsSysPrinter,
    kDWF6ePlot,
    kDWFePlotOptForPlotting,
    kDWFePlotOptForViewing,
    kPublishToWebDWF,
    kPublishToWebJPG,
    kPublishToWebPNG,
    kDWFxePlot,
    kPublishToWebDWFx,
    kPDFePlot,
    kPDFePlotGeneralDocs,
    kPDFePlotHighQuality,
    kPDFePlotSmallerFile,
    kPDFePlotWebMobile,
    kSVFePlot
  };
  virtual bool getDevicesList(AcArray<AcPlPlotConfigInfo, AcArrayObjectCopyReallocator <AcPlPlotConfigInfo> >& deviceList);
  virtual bool getStyleList(AcArray<ACHAR *>& list, long styType = kAllTypes);
  virtual void refreshList(RefreshCode refreshCode = kAll);
  virtual Acad::ErrorStatus getCurrentConfig(AcPlPlotConfig*& pConfig);
  virtual Acad::ErrorStatus setCurrentConfig(AcPlPlotConfig*& pConfig, const ACHAR* pDeviceName);
  virtual const ACHAR* getStdConfigName(StdConfigs stdConfig);
  virtual HT_Thin_Plot_Config_Manager* thinPltCfgMgr();
  virtual HT_Error_Handler* errorHandler();
  virtual HT_Error_Handler* acadErrorHandler();
};
ACPL_PORT AcPlPlotConfigManager* ADESK_STDCALL acplPlotConfigManagerPtr();
#  define acplPlotConfigManager	acplPlotConfigManagerPtr()
#endif
