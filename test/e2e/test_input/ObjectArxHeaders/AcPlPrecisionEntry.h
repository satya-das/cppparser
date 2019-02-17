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
//  DESCRIPTION:  Header for AcPlPrecisionEntry.h
//

#ifndef ACPLPRECISIONENTRY_H
#define ACPLPRECISIONENTRY_H

#pragma once

#include "AcPl.h"
#include "AcPlObject.h"

/////////////////////////////////////////////////////////////////////////////
// AcPlPrecisionEntry

class AcPlPrecisionEntry  : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlPrecisionEntry)
public:
    ACPL_PORT AcPlPrecisionEntry();

    ACPL_PORT virtual ~AcPlPrecisionEntry();

    ACPL_PORT AcPlPrecisionEntry(const AcPlPrecisionEntry & src);

    ACPL_PORT AcPlPrecisionEntry& operator= (const AcPlPrecisionEntry &src);

    ACPL_PORT const ACHAR *     title() const;
    ACPL_PORT void              setTitle(const ACHAR * pTitle);

    ACPL_PORT const ACHAR *     description() const;
    ACPL_PORT void              setDescription(const ACHAR * pDescription);

    ACPL_PORT const ACHAR *     unitType() const;
    ACPL_PORT void              setUnitType(const ACHAR * pUnitType);

    ACPL_PORT const ACHAR *     unitScale() const;
    ACPL_PORT void              setUnitScale(const ACHAR * pUnitScale);

    ACPL_PORT const double      desiredPrecision() const;
    ACPL_PORT void              setDesiredPrecision(double dDesiredPrecision);

    ACPL_PORT const int         gradientResolution() const;
    ACPL_PORT void              setGradientResolution(int nGradientResolution);

    ACPL_PORT const int         colorResolution() const;
    ACPL_PORT void              setColorResolution(int nColorResolution);

    ACPL_PORT const int         monoResolution() const;
    ACPL_PORT void              setMonoResolution(int nMonoResolution);
};

#endif // ACPLPRECISIONENTRY_H
