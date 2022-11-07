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
//////////////////////////////////////////////////////////////////////////////
// 
// Name:            DbTableTemplate.h
//
// Description:     Contains the following classes: 
//                      AcDbTableTemplate
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DbTableContent.h"

class AcDbTable;

//*************************************************************************
// AcDbTableTemplate
//*************************************************************************

class AcDbTableTemplate : public AcDbTableContent
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTableTemplate);

    AcDbTableTemplate(void);
    AcDbTableTemplate(const AcDbTable* pTable, AcDb::TableCopyOption nCopyOption);
    virtual ~AcDbTableTemplate(void);

    virtual Acad::ErrorStatus capture       (const AcDbTable* pTable, AcDb::TableCopyOption nCopyOption);
    virtual Acad::ErrorStatus createTable   (AcDbTable*& pTable, AcDb::TableCopyOption nCopyOption);

    virtual Acad::ErrorStatus dwgInFields   (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields  (AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields   (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields  (AcDbDxfFiler* pFiler) const override;
};
