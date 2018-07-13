//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef   _ACPLPLOTINFOVALIDATOR_H
#define   _ACPLPLOTINFOVALIDATOR_H

#include "AcPlObject.h"
#include "AcPlPlotInfo.h"

class AcPlPlotInfo;

// Default media matching weights
#define DEFAULT_MEDIA_GROUP_WEIGHT 50
#define DEFAULT_SHEET_MEDIA_GROUP_WEIGHT 10
#define DEFAULT_MEDIA_BOUNDS_WEIGHT 100
#define DEFAULT_PRINTABLE_BOUNDS_WEIGHT 10
#define DEFAULT_DIMENSIONAL_WEIGHT 50
#define DEFAULT_SHEET_DIMENSIONAL_WEIGHT 10
#define DEFAULT_THRESHOLD 500

class AcPlPlotInfoValidator : public AcPlObject
{
public:
    ACPL_PORT AcPlPlotInfoValidator();
    ACPL_PORT virtual ~AcPlPlotInfoValidator();

    ACPL_DECLARE_MEMBERS(AcPlPlotInfoValidator);

public:
    // Supported media matching policies
    enum MatchingPolicy {
        kMatchDisabled = 1,    // no media matching (default)
        kMatchEnabled,         // look for matching media and use if found
        kMatchEnabledCustom,   // create and save custom media size if necessary
        kMatchEnabledTmpCustom // create temporary custom media size if necessary
    };
 
    // Possible result codes from isCustomPossible()     
    enum eCustomSizeResult {
        ePossible           = 0x0000,
        eMustCreatePC3      = 0x0001,  // no PC3 file, one is required
        eRotationRequired   = 0x0002,  // size only possible with 90 degree rotation
        ePC3DirReadOnly     = 0x0004,
        ePMPDirReadOnly     = 0x0008,
        ePMPDirMissing      = 0x0010,
        eUnknownErrPMPDir   = 0x0020,
        ePC3FileReadOnly    = 0x0040,
        eSizeTooBig         = 0x0080,
        eException          = 0x0100,
        eUnknownErrPC3File  = 0x0200,
        eUnknownErrPMPFile  = 0x0400,
        ePMPFileReadOnly    = 0x0800,
        eWidthAndHeightMustBePositive = 0x1000,
        eDeviceLoadFailed   = 0x2000
    };


    // Validate an AcPlPlotInfo object
    ACPL_PORT virtual Acad::ErrorStatus validate(AcPlPlotInfo& info);

    // Returns a bitwise-OR of eCustomSizeResults bits indicating whether
    // a custom size is possible for the plot info object provided, using the
    // current media size and device specified in the info object.
    ACPL_PORT virtual unsigned long isCustomPossible(AcPlPlotInfo& info) const;

    // Media matching policy used by validator
    ACPL_PORT void setMediaMatchingPolicy(MatchingPolicy policy);
    ACPL_PORT MatchingPolicy matchingPolicy() const;

    // Media matching weights
    ACPL_PORT void setMediaGroupWeight(unsigned int weight = DEFAULT_MEDIA_GROUP_WEIGHT);      
    ACPL_PORT unsigned int mediaGroupWeight() const; 

    ACPL_PORT void setSheetMediaGroupWeight(unsigned int weight = DEFAULT_SHEET_MEDIA_GROUP_WEIGHT);
    ACPL_PORT unsigned int sheetMediaGroupWeight() const;

    ACPL_PORT void setMediaBoundsWeight(unsigned int weight = DEFAULT_MEDIA_BOUNDS_WEIGHT);
    ACPL_PORT unsigned int mediaBoundsWeight() const;

    ACPL_PORT void setPrintableBoundsWeight(unsigned int weight = DEFAULT_PRINTABLE_BOUNDS_WEIGHT); 
    ACPL_PORT unsigned int printableBoundsWeight() const;

    ACPL_PORT void setDimensionalWeight(unsigned int weight = DEFAULT_DIMENSIONAL_WEIGHT);     
    ACPL_PORT unsigned int dimensionalWeight() const;

    ACPL_PORT void setSheetDimensionalWeight(unsigned int weight = DEFAULT_SHEET_DIMENSIONAL_WEIGHT);
    ACPL_PORT unsigned int sheetDimensionalWeight() const;

    // Media matching threshold
    ACPL_PORT void setMediaMatchingThreshold(unsigned int threshold = DEFAULT_THRESHOLD);
    ACPL_PORT unsigned int mediaMatchingThreshold() const;

protected:
    // Media matching members
    unsigned int m_mediaBoundsWeight;
    unsigned int m_dimensionalWeight;
    unsigned int m_mediaGroupWeight;
    unsigned int m_printableBoundsWeight;
    unsigned int m_sheetDimensionalWeight;
    unsigned int m_sheetMediaGroupWeight;

    unsigned int m_matchingThreshold;

    MatchingPolicy m_matchingPolicy;
};
#endif // _ACPLPLOTINFOVALIDATOR_H
