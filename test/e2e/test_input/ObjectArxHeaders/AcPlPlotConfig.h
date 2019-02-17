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
//  DESCRIPTION:  Header for Document and Document Manager Classes.
//
#ifndef ACPLPLOTCONFIG_H
#define ACPLPLOTCONFIG_H

#include "AcPl.h"

#include "AcArray.h"
#include "gepnt2d.h"
#include "geblok2d.h"
#include "dblayout.h"

class HT_Plot_Config;
class HT_Media_Size;
class HT_Media_Description;

class AcPlPlotConfig : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlPlotConfig)

public:
    enum PlotToFileCapability {
        kNoPlotToFile       = 0,
        kPlotToFileAllowed  = 1,
        kMustPlotToFile     = 2
    };
        
public:
    ACPL_PORT virtual ~AcPlPlotConfig();

    ACPL_PORT virtual Acad::ErrorStatus copyFrom(const AcRxObject* pSrc);


    // returns the description field information - driver name
    // location, comment, port name, server name and tag line
    ACPL_PORT virtual void getDescriptionFields(ACHAR*& pDriverName,
                                                ACHAR*& pLocationName,
                                                ACHAR*& pComment,
                                                ACHAR*& pPortName,
                                                ACHAR*& pServerName,
                                                ACHAR*& pTagLine) const;

    // returns the current device name from the current plot config
    ACPL_PORT virtual const ACHAR* deviceName() const;

    // returns the full path name if the current plot config is of a pc3 file
    // or the UNC name if it is a system printer
    ACPL_PORT virtual const ACHAR* fullPath() const;

    // returns the maximum DPI supported by the device
    ACPL_PORT virtual unsigned int maxDeviceDPI() const;

    // returns the deviceType for the current plot config device
    ACPL_PORT virtual unsigned long deviceType() const;

    // returns the canonical media name list for the current device
    ACPL_PORT virtual void getCanonicalMediaNameList(AcArray<ACHAR*> &mediaList) const;

    // given a canonical media name, returns its local media name
    ACPL_PORT virtual void getLocalMediaName(const ACHAR* pCanonicalMediaName, 
                                             ACHAR* &pLocalMediaName) const;

    // returns the media bounds (page size and printable bounds) for the 
    // canonical media name passed in
    ACPL_PORT virtual void getMediaBounds(const ACHAR* pCanonicalMediaName,
                                          AcGePoint2d &pageSize, 
                                          AcGeBoundBlock2d &printableArea) const;

    // resets the current cached media name list
    ACPL_PORT virtual void refreshMediaNameList();

    // gets/sets the config's plot to file setting
    ACPL_PORT virtual bool isPlotToFile() const;
    ACPL_PORT virtual Acad::ErrorStatus setPlotToFile(bool bPlotToFile);

    // returns the device's default file extension (if any)
    // including the leading '.'
    ACPL_PORT virtual Acad::ErrorStatus getDefaultFileExtension(const ACHAR*& pDefaultExtension) const;

    // returns the device's plot-to-file capability
    ACPL_PORT virtual PlotToFileCapability plotToFileCapability() const;

    // saves the current configuration to the specified pc3 file
    // Note: This doesn't load the saved pc3 as current config.
    // Use the method getPlotConfig() and pass in saved pc3 file to 
    // get to the plot config
    ACPL_PORT virtual bool saveToPC3(const ACHAR* pPC3Name);

    // returns the current HT_Plot_Config object (for internal use only)
    ACPL_PORT virtual HT_Plot_Config* plotConfig() const;
    
    // internal use only
    ACPL_PORT virtual unsigned long isCustomPossible(double width, double height, 
                                  bool bIsDimensional, bool bIsSheet, int dpi, const
                                  ACHAR * pPC3Dir) const;
    
    // internal use only
    ACPL_PORT virtual bool matchMediaSize(double page_x, double page_y,
                                  double printable_w, double printable_h, 
                                  AcDbLayout::PlotPaperUnits units, 
                                  bool bIsSheet, int dpi, 
                                  const ACHAR * pTargetCanonicalName, 
                                  ACHAR *& pNearestSizeName, 
                                  ACHAR *& pLocalizedName,
                                  double & scaleFactor);

    // internal use only
    ACPL_PORT virtual Acad::ErrorStatus makeCustomMediaFromSizeDesc( 
        HT_Media_Size * pSize, HT_Media_Description * pDesc,
        bool bSameDriver, bool bSavePC3,
        const ACHAR * pSourceEntry, const ACHAR * pSourceName, 
        ACHAR *& pCanonicalSizeName, ACHAR *& pLocalizedSizeName, 
        ACHAR *& pPMPPath, ACHAR *& pPC3Path, int dpi, double & scaleFactor);

protected:
    friend class AcPlPlotConfigManagerImp;
    friend class AcPlPlotInfoImp;
    friend class AcPlPlotInfoValidatorImp;
    AcPlPlotConfig(HT_Plot_Config* pConfig, const ACHAR* pDevName, 
                   const ACHAR* pFullPath, unsigned long nDevType);

    AcPlPlotConfig(const AcPlPlotConfig* pOther);

private:
    AcPlPlotConfig();

};

#endif // ACPLPLOTCONFIG_H
