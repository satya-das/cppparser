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
// Default implementation for Layer Filter.
//

#ifndef AD_DBLYFILT_H
#define AD_DBLYFILT_H

#include "dbfilter.h"
#include "AdAChar.h"

#pragma pack (push, 8)

class AcDbLayerFilter: public  AcDbFilter
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLayerFilter);
             AcDbLayerFilter();
    virtual ~AcDbLayerFilter();

    virtual AcRxClass* indexClass() const override;
    virtual Adesk::Boolean isValid() const;

    Acad::ErrorStatus add(const ACHAR * pLayer);
    Acad::ErrorStatus remove(const ACHAR * pLayer);
    Acad::ErrorStatus getAt(int index, const ACHAR *& pName) const;
    int layerCount() const;
};

#pragma pack (pop)

#endif // AD_DBLYFILT_H
