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

#ifndef AD_DBDICTDFLT_H
#define AD_DBDICTDFLT_H

#include "dbdict.h"

#pragma pack(push, 8)

class AcDbImpDictionaryWithDefault;

class AcDbDictionaryWithDefault : public AcDbDictionary
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDictionaryWithDefault);
    AcDbDictionaryWithDefault();
    virtual ~AcDbDictionaryWithDefault();

    Acad::ErrorStatus setDefaultId(const AcDbObjectId& newId);
    AcDbObjectId defaultId() const;

    virtual Acad::ErrorStatus getObjectBirthVersion(
                                 AcDb::AcDbDwgVersion& ver,
                                 AcDb::MaintenanceReleaseVersion& maintVer);
};

#pragma pack(pop)

#endif
