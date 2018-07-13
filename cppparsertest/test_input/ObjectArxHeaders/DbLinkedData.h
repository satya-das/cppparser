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
// Name:            DbLinkedData.h
//
// Description:     Data classes
//                  Contains the following classes: 
//                      AcDbLinkedData
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcValue.h"
#include "DbDataLink.h"


//*************************************************************************
// AcDbLinkedData
//*************************************************************************

class AcDbLinkedData : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLinkedData);

    ACDB_PORT AcDbLinkedData(void);
    ACDB_PORT virtual ~AcDbLinkedData(void);

    ACDB_PORT virtual Acad::ErrorStatus clear(void);
    ACDB_PORT virtual bool isEmpty          (void) const;

    ACDB_PORT virtual const ACHAR* name     (void) const;
    ACDB_PORT virtual Acad::ErrorStatus setName(const ACHAR* pszName);
    ACDB_PORT virtual const ACHAR* description(void) const;
    ACDB_PORT virtual Acad::ErrorStatus setDescription(const ACHAR* pszDescription);

    ACDB_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
};

typedef AcArray<AcDbLinkedData*> AcDbDataArray;
