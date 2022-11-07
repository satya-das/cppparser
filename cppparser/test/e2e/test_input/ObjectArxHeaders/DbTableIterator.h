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
// Name:            DbTableIterator.h
//
// Description:     Contains AcDbTableIterator class
//////////////////////////////////////////////////////////////////////////////

#pragma once

struct AcCell;
struct AcCellRange;
class AcDbTable;
class AcDbLinkedTableData;


//*************************************************************************
// AcDbTableIterator
//*************************************************************************

class AcDbTableIterator
{
public:
    AcDbTableIterator(const AcDbTable* pTable);
    AcDbTableIterator(const AcDbTable* pTable, const AcCellRange* pRange,
        AcDb::TableIteratorOption nOption);
    AcDbTableIterator(const AcDbLinkedTableData* pTable);
    AcDbTableIterator(const AcDbLinkedTableData* pTable, const AcCellRange* pRange,
        AcDb::TableIteratorOption nOption);
    AcDbTableIterator(const AcCellRange& range);
    AcDbTableIterator(const AcCellRange& range, AcDb::TableIteratorOption nOption);
    ~AcDbTableIterator();

    void            start                   (void);
    void            step                    (void);
    bool            done                    (void);
    bool            seek                    (const AcCell& cell);
    const AcCell&   getCell                 (void) const;
    int             getRow                  (void) const;
    int             getColumn               (void) const;

protected:
    AcDbTableIterator(void);

protected:
    void        *   mpImpObj;
};
