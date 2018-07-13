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
// dbDataTable.H
//
// DESCRIPTION: Contains Cell, Column, Row, and Table classes
//              for general purpose table representation.

// These warnings have to do with exporting classes from dlls...

#pragma once
#pragma warning( disable: 4275 4251 )

#include "acarray.h"
#include "gepnt3d.h"

#include "dbmain.h"
#include "dbents.h"
#include "AcDbCore2dDefs.h"     // ACDBCORE2D_PORT

#pragma pack (push, 8)

class AcDbImpDataCell;
class AcDbImpDataColumn;


//////////////////////////////////// AcDbDataCell /////////////////////////////
class AcDbDataCell : public AcRxObject
{
public:
    enum CellType {
        kUnknown = 0,
        kInteger,
        kDouble,
        kCharPtr,
        kPoint,
        kObjectId,
        kHardOwnerId,
        kSoftOwnerId,
        kHardPtrId,
        kSoftPtrId,
        kBool,
        kVector
    };

    // Constructors
    AcDbDataCell();
    AcDbDataCell(const AcDbDataCell& rCell);

    AcDbDataCell(bool b);
    AcDbDataCell(int i);
    AcDbDataCell(double d);
    AcDbDataCell(const ACHAR * pChar);
    AcDbDataCell(const AcGePoint3d& point);
    AcDbDataCell(const AcGeVector3d& vec);
    AcDbDataCell(const AcDbObjectId& id);
    AcDbDataCell(const AcDbHardOwnershipId& hoId);
    AcDbDataCell(const AcDbSoftOwnershipId& soId);
    AcDbDataCell(const AcDbHardPointerId&   hpId);
    AcDbDataCell(const AcDbSoftPointerId&   spId);

    virtual ~AcDbDataCell();
    ACRX_DECLARE_MEMBERS(AcDbDataCell);


    virtual void init();

    virtual AcDbDataCell& operator = (const AcDbDataCell &cell);
    virtual AcDbDataCell& operator = (bool b);
    virtual AcDbDataCell& operator = (int i);
    virtual AcDbDataCell& operator = (double d);
    virtual AcDbDataCell& operator = (const ACHAR * pChar);
    ACDBCORE2D_PORT
    virtual AcDbDataCell& operator = (const AcString & s);
    virtual AcDbDataCell& operator = (const AcGePoint3d &pt);
    virtual AcDbDataCell& operator = (const AcGeVector3d &vec);
    virtual AcDbDataCell& operator = (const AcDbObjectId &id);
    virtual AcDbDataCell& operator = (const AcDbHardOwnershipId &hoId);
    virtual AcDbDataCell& operator = (const AcDbSoftOwnershipId &soId);
    virtual AcDbDataCell& operator = (const AcDbHardPointerId   &hpId);
    virtual AcDbDataCell& operator = (const AcDbSoftPointerId   &spId);

    virtual operator bool() const;
    virtual operator int() const;
    virtual operator double() const;
    virtual operator const ACHAR *() const;
    ACDBCORE2D_PORT
    virtual operator AcString & () const;
    virtual operator AcGePoint3d&()const;
    virtual operator AcGeVector3d&()const;
    virtual operator AcDbObjectId&() const;
    virtual operator AcDbHardOwnershipId&() const;
    virtual operator AcDbSoftOwnershipId&() const;
    virtual operator AcDbHardPointerId&() const;
    virtual operator AcDbSoftPointerId&() const;

    virtual bool operator == (const AcDbDataCell &cell) const;
    virtual bool operator != (const AcDbDataCell &cell) const;

    virtual AcDbDataCell::CellType type() const;

private:
    friend class AcDbSystemInternals;
//    friend class AcDbImpDataCell;
    AcDbImpDataCell* mpImpDataCell;
};


/////////////////////////////////// AcDbDataCellArray /////////////////////////
// An Array of AcDbDataCells following the standard ARX AcArray template.
//
typedef AcArray<AcDbDataCell, AcArrayObjectCopyReallocator<AcDbDataCell> >
    AcDbDataCellArray;


//////////////////////////////////// AcDbDataColumn /////////////////////////////
//
class AcDbDataColumn : public AcRxObject
{
public:
    AcDbDataColumn();
    AcDbDataColumn(const AcDbDataColumn& rCol);
    AcDbDataColumn(const AcDbDataCell::CellType type,
        const ACHAR * pColName = NULL);

    virtual ~AcDbDataColumn();
    ACRX_DECLARE_MEMBERS(AcDbDataColumn);

    virtual Adesk::UInt32 physicalLength() const;
    virtual Adesk::UInt32 growLength() const;
    virtual Acad::ErrorStatus setPhysicalLength(Adesk::UInt32 n);
    virtual Acad::ErrorStatus setGrowLength(Adesk::UInt32 n);

    virtual AcDbDataColumn& operator = (const AcDbDataColumn& col);

    virtual Acad::ErrorStatus setColumnType(AcDbDataCell::CellType type);
    virtual AcDbDataCell::CellType columnType() const;
    virtual Acad::ErrorStatus setColumnName(const ACHAR * pName);
    virtual const ACHAR * columnName() const;

    virtual Acad::ErrorStatus getCellAt(Adesk::UInt32 index, AcDbDataCell& outCell) const;
    virtual Acad::ErrorStatus setCellAt(Adesk::UInt32 index, const AcDbDataCell& cell);
    virtual Acad::ErrorStatus appendCell(const AcDbDataCell& cell);
    virtual Acad::ErrorStatus insertCellAt(Adesk::UInt32 index, const AcDbDataCell& cell);
    virtual Acad::ErrorStatus removeCellAt(Adesk::UInt32 index);
    virtual Acad::ErrorStatus getIndexAtCell(const AcDbDataCell& cell, Adesk::UInt32& index) const;

    virtual Adesk::UInt32 numCells() const;

private:
    friend class AcDbSystemInternals;
    friend class AcDbImpDataColumn;
    AcDbImpDataColumn* mpImpDataColumn;
};

/////////////////////////////////////// AcDbDataTable /////////////////////////
class AcDbDataTable : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDataTable);
    
    AcDbDataTable();
    virtual ~AcDbDataTable(); 
   
    virtual AcDbDataTable& operator = (const AcDbDataTable& table);

    virtual Adesk::UInt32 numColumns() const;
    virtual Adesk::UInt32 numRows() const;

    virtual Acad::ErrorStatus setNumRowsPhysicalSize(Adesk::UInt32 n);
    virtual Acad::ErrorStatus setNumRowsGrowSize(Adesk::UInt32 n);
    virtual Adesk::UInt32 numRowsPhysicalSize() const;
    virtual Adesk::UInt32 numRowsGrowSize() const;
    virtual Acad::ErrorStatus setNumColsPhysicalSize(Adesk::UInt32 n);
    virtual Acad::ErrorStatus setNumColsGrowSize(Adesk::UInt32 n);
    virtual Adesk::UInt32 numColsPhysicalSize() const;
    virtual Adesk::UInt32 numColsGrowSize() const;

    virtual const ACHAR * tableName() const;
    virtual Acad::ErrorStatus setTableName(const ACHAR * pName);

    virtual Acad::ErrorStatus getColumnAt(Adesk::UInt32 index,
        const AcDbDataColumn*& pCol) const;
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus getColumnNameAt(Adesk::UInt32 index, AcString & sName) const;
    virtual Acad::ErrorStatus getColumnNameAt(Adesk::UInt32 index,
                        ACHAR *& pName) const final;    // deprecated
    virtual Acad::ErrorStatus getColumnTypeAt(Adesk::UInt32 index, 
        AcDbDataCell::CellType& type) const;
    virtual Acad::ErrorStatus getColumnIndexAtName(
        const ACHAR * pName, Adesk::UInt32& index) const;

    virtual Acad::ErrorStatus appendColumn(
        AcDbDataCell::CellType type, const ACHAR * pColName = NULL);
    virtual Acad::ErrorStatus insertColumnAt(Adesk::UInt32 index, 
        AcDbDataCell::CellType type, const ACHAR * pColName = NULL);
    virtual Acad::ErrorStatus removeColumnAt(Adesk::UInt32 index);

    virtual Acad::ErrorStatus getRowAt(Adesk::UInt32 index, 
        AcDbDataCellArray& outRow) const;
    virtual Acad::ErrorStatus setRowAt(Adesk::UInt32 index,
        const AcDbDataCellArray& row, bool bValidate = true);
    virtual Acad::ErrorStatus appendRow(
        const AcDbDataCellArray& row, bool bValidate = true);

    virtual Acad::ErrorStatus insertRowAt(Adesk::UInt32 index,
        const AcDbDataCellArray& row, bool bValidate = true);
    virtual Acad::ErrorStatus removeRowAt(Adesk::UInt32 index);

    virtual Acad::ErrorStatus getCellAt(Adesk::UInt32 row, Adesk::UInt32 col,
        AcDbDataCell& outCell) const;
    virtual Acad::ErrorStatus setCellAt(Adesk::UInt32 row, Adesk::UInt32 col,
        const AcDbDataCell& cell);

    //*************************************************************************
    // Overridden methods from AcDbObject
    //*************************************************************************
    
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;

    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo) override;
};

// This overload is deprecated. Please use the one taking AcString & arg
inline Acad::ErrorStatus AcDbDataTable::getColumnNameAt(Adesk::UInt32 index,
                                                ACHAR *& pName) const
{
    AcString sName;
    return ::acutAcStringToAChar(sName, pName, this->getColumnNameAt(index, sName));
}

#pragma pack (pop)
