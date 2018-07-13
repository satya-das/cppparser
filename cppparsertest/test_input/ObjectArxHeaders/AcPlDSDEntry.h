//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//  DESCRIPTION:  Header for AcPlDSDEntry.h
//
#ifndef ACPLDSDENTRY_H
#define ACPLDSDENTRY_H

#pragma once

#include "AcPl.h"
#include "AcPlObject.h"

/////////////////////////////////////////////////////////////////////////////
// AcPlDSDEntry

class AcPlDSDEntry  : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlDSDEntry)
public:

    enum SheetType {
        kSingleDWF  = 0,
        kMultiDWF = 1,
        kOriginalDevice = 2,
        kSingleDWFx = 3,
        kMultiDWFx = 4,
        kSinglePDF = 5,
        kMultiPDF = 6,
        kSingleSVF = 7,
        kMultiSVF = 8,
    };

    enum SetupType {
        kOriginalPS = 0,
        kNPSSameDWG = 1,
        kNPSOtherDWG = 2,
        k3dDwf = 3,
        kOverridePS = 4,
    };

    ACPL_PORT AcPlDSDEntry();

    ACPL_PORT virtual ~AcPlDSDEntry();

    ACPL_PORT AcPlDSDEntry(const AcPlDSDEntry & src);

    ACPL_PORT AcPlDSDEntry& operator= (const AcPlDSDEntry &src);

    ACPL_PORT const ACHAR *     dwgName() const;
    ACPL_PORT void              setDwgName(const ACHAR * pName);

    ACPL_PORT const ACHAR *     layout() const;
    ACPL_PORT void              setLayout(const ACHAR * pLayoutName);
    
    ACPL_PORT const ACHAR *     title() const;
    ACPL_PORT void              setTitle(const ACHAR * pTitle);
    
    ACPL_PORT const ACHAR *     NPS() const;
    ACPL_PORT void              setNPS(const ACHAR * pNPSName);
    
    ACPL_PORT const ACHAR *     NPSSourceDWG() const;
    ACPL_PORT void              setNPSSourceDWG(const ACHAR * pNPWDWGName);

    ACPL_PORT bool              has3dDwfSetup() const;
    ACPL_PORT void              setHas3dDwfSetup(bool b3dDwfSetup);

    ACPL_PORT AcPlDSDEntry::SetupType setupType() const;
    ACPL_PORT void              setSetupType(AcPlDSDEntry::SetupType eType);

    ACPL_PORT const ACHAR*      orgSheetPath() const;
};

#endif // ACPLDSDENTRY_H
