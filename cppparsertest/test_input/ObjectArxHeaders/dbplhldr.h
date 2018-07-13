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

#ifndef AD_DBPLACEHOLDER_H
#define AD_DBPLACEHOLDER_H

#include "dbmain.h"

#pragma pack (push, 8)

class AcDbPlaceHolder : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbPlaceHolder);
    AcDbPlaceHolder();
    virtual ~AcDbPlaceHolder();

    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;

protected:
    virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject,
                                         AcDbObject*& pClonedObject,
                                         AcDbIdMapping& idMap,
                                         Adesk::Boolean isPrimary
                                         = Adesk::kTrue) const override;
};

#pragma pack (pop)

#endif

