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
// Name:            DbTableContent.h
//
// Description:     Contains the following classes: 
//                      AcDbTableContent
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DbFormattedTableData.h"


//*************************************************************************
// AcDbTableContent
//*************************************************************************

class AcDbTableContent : public AcDbFormattedTableData
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTableContent);

    ACDB_PORT AcDbTableContent(void);
    ACDB_PORT virtual ~AcDbTableContent(void);

    ACDB_PORT virtual AcDbObjectId tableStyleId(void) const;
    ACDB_PORT virtual Acad::ErrorStatus setTableStyleId(const AcDbObjectId& idTableStyle);
    ACDB_PORT virtual const ACHAR* cellStyle(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setCellStyle(int nRow, 
                                             int nCol, 
                                             const ACHAR* pszCellStyle);
    ACDB_PORT virtual double rowHeight      (int nRow) const;
    ACDB_PORT virtual Acad::ErrorStatus setRowHeight(int nRow, 
                                             double fWidth);
    ACDB_PORT virtual double columnWidth    (int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setColumnWidth(int nCol, 
                                             double fWidth);

    ACDB_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
};
