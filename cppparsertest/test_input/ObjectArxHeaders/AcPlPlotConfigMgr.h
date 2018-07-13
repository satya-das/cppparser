//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

//  DESCRIPTION:  Header for Document and Document Manager Classes.
//
#ifndef ACPLPLOTCONFIGMGR_H
#define ACPLPLOTCONFIGMGR_H

#include "AdAChar.h"
#include "AcPl.h"
#include "AcArray.h"
#include "AcPlObject.h"

class AcPlPlotConfig;
class HT_Thin_Plot_Config_Manager;
class HT_Error_Handler;

enum DeviceType {
    kSystemPrinter = 0,
    kPC3File = 1,
    kOneOffConfig = 2,      // for internal use only
    kUninitialized = -1
};

class AcPlPlotConfigInfo : public AcPlObject
{
public:
    ACPL_PORT AcPlPlotConfigInfo();
    ACPL_PORT AcPlPlotConfigInfo(const ACHAR * pDevName,
                                 const ACHAR * pFullPath, 
                                 DeviceType devType);
    // copy constructor
    ACPL_PORT AcPlPlotConfigInfo(const AcPlPlotConfigInfo &copy);

    // assignment operator calls this method to copy the contents from src
    ACPL_PORT Acad::ErrorStatus copyFrom(const AcRxObject* pSrc);

    // assignment operator copies the device name, full path and device type
    // information
    ACPL_PORT const AcPlPlotConfigInfo& operator=(const AcPlPlotConfigInfo& src);

    // destructor
    ACPL_PORT virtual ~AcPlPlotConfigInfo();

    ACPL_DECLARE_MEMBERS(AcPlPlotConfigInfo);

    // returns the full path for the pc3 file. In case of system printers
    // just returns the UNC name
    ACPL_PORT const ACHAR * fullPath() const;

    // call to set the full path for the pc3 file or just the UNC name for 
    // system printers
    ACPL_PORT void setFullPath(const ACHAR * pPath);

	
    // returns the pc3 filename+ext portion or UNC name for system printers
    ACPL_PORT const ACHAR * deviceName() const;

    // call to set the pc3 filename+ext portion or UNC name for system printers
    ACPL_PORT void setDeviceName(const ACHAR * pDevName);

    // returns the device type (kSystemPrinter, kPC3file)
    ACPL_PORT DeviceType deviceType() const;

    // call to set the device type (kSystemPrinter, kPC3file)
    ACPL_PORT void setDeviceType(DeviceType devType);
	
	ACPL_PORT const ACHAR * deviceId() const;
    ACPL_PORT void setDeviceId(const ACHAR * pDevId);
};

class ADESK_NO_VTABLE AcPlPlotConfigManager
{
public:

    // Refresh Codes
    enum RefreshCode {
        kAll,
        kRefreshDevicesList,
        kRefreshStyleList,
        kRefreshSystemDevicesList,
        kRefreshPC3DevicesList
    };
    // Different type of plot style tables
    enum StyTypes {
        kUndefined      = 0,
        kRegular        = 0x01,
        kTranslation    = 0x02,
        kColorDep       = 0x04,
        kAllTypes       = 0x07
    };
    // List of standard pc3 files that are installed by default
    enum StdConfigs {
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
        kPDFePlotGeneralDocs,   // to specify Pdf pc3 config file for General Documentation.
        kPDFePlotHighQuality,   // to specify Pdf pc3 config file for High Quality Print.
        kPDFePlotSmallerFile,   // to specify Pdf pc3 config file for Smallest File Size.
        kPDFePlotWebMobile,     // to specify Pdf pc3 config file for Web and Mobile.
        kSVFePlot
    };

    // Returns the list of system printer, pc3 file installed on the current
    // system. Also includes the None device as the first element of the array
    virtual bool getDevicesList(AcArray<AcPlPlotConfigInfo, 
        AcArrayObjectCopyReallocator <AcPlPlotConfigInfo> > &deviceList);

    // Returns a list of plot style table based on the styType flag specified
    // currently installed on a system
    virtual bool getStyleList(AcArray<ACHAR *> &list, 
                              long styType = kAllTypes); //VC8: Removed extra qualifier

    // Resets the local cache of the devices or plot style tables based on
    // the refreshCode specified
    virtual void refreshList(RefreshCode refreshCode = kAll);

    // Returns the current active plot config object in the Plot Config Manager
    // wrapped as a AcPlPlotConfig object
    virtual Acad::ErrorStatus getCurrentConfig(AcPlPlotConfig*& pConfig);

    // Creates a plot config for the specified device, wraps it as a
    // AcPlPlotConfig object and returns it
    virtual Acad::ErrorStatus setCurrentConfig(AcPlPlotConfig*& pConfig, 
                                               const ACHAR * pDeviceName);

    // Returns the localized name for the default pc3 files that are 
    // installed with AutoCAD
    virtual const ACHAR * getStdConfigName(StdConfigs stdConfig);

    // Returns a pointer to the current global thin plot config manager
    virtual HT_Thin_Plot_Config_Manager* thinPltCfgMgr(); //  (for internal use only)

    // Returns a pointer to the Plot Config Manager's error handler
    virtual HT_Error_Handler* errorHandler(); //  (for internal use only)

    // Returns a pointer the parent error handler (ACAD_Err_Handler)
    virtual HT_Error_Handler* acadErrorHandler(); //  (for internal use only)
};

ACPL_PORT AcPlPlotConfigManager* ADESK_STDCALL acplPlotConfigManagerPtr();
#define acplPlotConfigManager acplPlotConfigManagerPtr()

#endif // ACPLPLOTCONFIGMGR_H
