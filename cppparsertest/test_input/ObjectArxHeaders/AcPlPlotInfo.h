//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef   _ACPLPLOTINFO_H
#define   _ACPLPLOTINFO_H

#include "AcPlObject.h"

class AcPlPlotConfig;
class AcRxObject;
class AcDbPlotSettings;

class AcPlPlotInfo : public AcPlObject
{
public:
    ACPL_PORT AcPlPlotInfo();
    ACPL_PORT virtual ~AcPlPlotInfo();

    ACPL_DECLARE_MEMBERS(AcPlPlotInfo);
    
public:

    enum MergeStatus {
        kNoChanges              = 0x00000000,
        kPlotCfgName            = 0x00000001,
        kPlotPaperMargins       = 0x00000002,
        kPlotPaperSize          = 0x00000004,
        kCanonicalMediaName     = 0x00000008,
        kPlotOrigin             = 0x00000010,
        kPlotPaperUnits         = 0x00000020,
        kPlotViewportBorders    = 0x00000040,
        kPlotPlotStyles         = 0x00000080,
        kShowPlotStyles         = 0x00000100,
        kPlotRotation           = 0x00000200,
        kPlotCentered           = 0x00000400,
        kPlotHidden             = 0x00000800,
        kShadePlot              = 0x00001000,
        kShadePlotResLevel      = 0x00002000,
        kShadePlotCustomDPI     = 0x00004000,
        kPlotType               = 0x00008000,
        kPlotWindowArea         = 0x00010000,
        kPlotViewName           = 0x00020000,
        kScale                  = 0x00040000,
        kCurrentStlyeSheet      = 0x00080000,
        kScaleLineWeights       = 0x00100000,
        kPrintLineWeights       = 0x00200000,
        kDrawViewportsFirst     = 0x00400000,
        kPlotTransparency       = 0x00800000
    };
    
    ACPL_PORT Acad::ErrorStatus copyFrom(const AcRxObject* pOther);

    // Layout to be plotted. Required. 
    ACPL_PORT void setLayout(AcDbObjectId& layoutId);

    // Layout to be plotted.  
    ACPL_PORT AcDbObjectId layout() const;
    
    // AcDbPlotSettings containing the settings to use for the plot. 
    // Optional, passing NULL removes any existing overrides. 
    // If not provided the object uses the layout settings. 
    ACPL_PORT void setOverrideSettings(const AcDbPlotSettings* pOverrides);
    
    // The current AcDbPlotSettings containing the overrides.
    ACPL_PORT const AcDbPlotSettings* overrideSettings() const;
   
    // Provides an AcPlPlotConfig (or PC3/Device name) to use instead of the
    // config/device specified in the layout or override.  Optional, passing
    // NULL removes any existing overrides. 
    ACPL_PORT void setDeviceOverride(const AcPlPlotConfig* pconf);
        
    // The "merged" AcDbPlotSettings object, created by merging the source
    // layout with the overrides and device override. 
    ACPL_PORT const AcDbPlotSettings* validatedSettings() const;

    // Sets the validated AcDbPlotSettings. 
    ACPL_PORT Acad::ErrorStatus setValidatedSettings(const AcDbPlotSettings* pValidatedSettings);

    // The AcPlPlotConfig for the validated settings
    ACPL_PORT const AcPlPlotConfig* validatedConfig() const;

    // Sets the validated config
    ACPL_PORT void setValidatedConfig(const AcPlPlotConfig* pConfig);

    // The AcPlPlotConfig object (or PC3/Device name) 
    // that will override the output device set in the layout. 
    ACPL_PORT const AcPlPlotConfig* deviceOverride() const;

    // Returns a bool indicating whether the current overrides have been merged 
    // with the layout settings. 
    ACPL_PORT bool isValidated() const;

    // Gets the "changed" bits on the info object to indicate the what
    // properties of the source layout changed as a result of applying the plot
    // settings and device overrides.  
    ACPL_PORT unsigned long mergeStatus() const;
    
    // Could this object be sufficiently similar to another plot info,
    // satisfying the requirements of multi-page documents
    // (Same device name, media size, orientation, etc.)
    ACPL_PORT bool isCompatibleDocument(const AcPlPlotInfo* pOtherInfo) const;

    // original file path of the current drawing accosicated with the current plot task
    // this path is now used only for finding plot style. see P038B013LAD1.txt.
    ACPL_PORT AcString& OrgFilePath() { return m_OrgFilePath; }
private:
    AcString m_OrgFilePath;
};

#endif // _ACPLPLOTINFO_H
