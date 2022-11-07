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
// Name:            AcCell.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


typedef struct AcCell
{
    int     mnRow;
    int     mnColumn;

} AcCell;

typedef AcArray<AcCell> AcCellArray;


typedef struct AcCellRange
{
    int     mnTopRow;
    int     mnLeftColumn;
    int     mnBottomRow;
    int     mnRightColumn;
    bool operator==(const AcCellRange& other) const;
} AcCellRange;
typedef AcArray<AcCellRange> AcCellRangeArray;
