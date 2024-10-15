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
// DESCRIPTION:  Class header for AcDbImage. Abstract base class 
//               for raster images.
//
//

#ifndef AD_DBIMAGE_H
#define AD_DBIMAGE_H

#include "dbmain.h"
#include "acgi.h"
#pragma pack (push, 8)

class AcDbImage: public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcDbImage);

    virtual AcGiSentScanLines*	
        getScanLines(const AcGiRequestScanLines&) const = 0;
    virtual Adesk::Boolean	
        freeScanLines(AcGiSentScanLines*) const = 0;    
};

#pragma pack (pop) 
#endif  // AD_DBIMAGE_H

