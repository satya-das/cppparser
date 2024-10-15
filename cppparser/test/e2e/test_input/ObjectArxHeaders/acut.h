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
//
//
//  DESCRIPTION:
//
//  This header file contains definitions for the acutil library 
//
//

#pragma once
#pragma pack (push, 8)

struct AcUt {
    enum QFormatBitFlags {
        kSuppressZeroFeet     = 0x100,
        kSuppressZeroInches   = 0x200,
        kSuppressLeadingZero  = 0x400,
        kSuppressTrailingZero = 0x800,
        kIgnoreUnitMode       = 0x1000,
        kUseAltUnits          = 0x2000
    };
};

#pragma pack (pop)
