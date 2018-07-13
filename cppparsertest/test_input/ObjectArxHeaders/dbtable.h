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
// dbtable.h
//
//  DESCRIPTION: AcDbTable api class declaration
//
//  AcRxObject
//    AcDbObject
//      AcDbEntity
//        AcDbBlockReference
//          AcDbTable
//

#pragma once

#include "dbmain.h"
#include "dbents.h"
#include "AcField.h"
#include "DbLinkedTableData.h"
#include "dbformattedtabledata.h"

#pragma pack(push, 8)

class AcDbTableIterator;
class AcDbTableTemplate;

// Typedef mapping old array name to new
typedef AcDbFullSubentPathArray AcSubentPathArray;

class AcDbTable: public AcDbBlockReference
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTable);

    enum TableStyleOverrides {
        //table
        kTitleSuppressed             = 1,
        kHeaderSuppressed            = 2,
        kFlowDirection               = 3,         
        kHorzCellMargin              = 4,
        kVertCellMargin              = 5,
        kTitleRowColor               = 6,
        kHeaderRowColor              = 7,
        kDataRowColor                = 8,
        kTitleRowFillNone            = 9,
        kHeaderRowFillNone           = 10,
        kDataRowFillNone             = 11,
        kTitleRowFillColor           = 12,
        kHeaderRowFillColor          = 13,
        kDataRowFillColor            = 14,
        kTitleRowAlignment           = 15,
        kHeaderRowAlignment          = 16,
        kDataRowAlignment            = 17,
        kTitleRowTextStyle           = 18,
        kHeaderRowTextStyle          = 19,
        kDataRowTextStyle            = 20,
        kTitleRowTextHeight          = 21,
        kHeaderRowTextHeight         = 22,
        kDataRowTextHeight           = 23,
        kTitleRowDataType            = 24,  // For internal use only
        kHeaderRowDataType           = 25,  // For internal use only
        kDataRowDataType             = 26,  // For internal use only

        // grid color
        kTitleHorzTopColor           = 40,
        kTitleHorzInsideColor        = 41,
        kTitleHorzBottomColor        = 42,
        kTitleVertLeftColor          = 43,
        kTitleVertInsideColor        = 44,
        kTitleVertRightColor         = 45,

        kHeaderHorzTopColor          = 46,
        kHeaderHorzInsideColor       = 47,
        kHeaderHorzBottomColor       = 48,
        kHeaderVertLeftColor         = 49,
        kHeaderVertInsideColor       = 50,
        kHeaderVertRightColor        = 51,

        kDataHorzTopColor            = 52,
        kDataHorzInsideColor         = 53,
        kDataHorzBottomColor         = 54,
        kDataVertLeftColor           = 55,
        kDataVertInsideColor         = 56,
        kDataVertRightColor          = 57,

        // grid line weight
        kTitleHorzTopLineWeight      = 70,
        kTitleHorzInsideLineWeight   = 71,
        kTitleHorzBottomLineWeight   = 72,
        kTitleVertLeftLineWeight     = 73,
        kTitleVertInsideLineWeight   = 74,
        kTitleVertRightLineWeight    = 75,

        kHeaderHorzTopLineWeight     = 76,
        kHeaderHorzInsideLineWeight  = 77,
        kHeaderHorzBottomLineWeight  = 78,
        kHeaderVertLeftLineWeight    = 79,
        kHeaderVertInsideLineWeight  = 80,
        kHeaderVertRightLineWeight   = 81,

        kDataHorzTopLineWeight       = 82,
        kDataHorzInsideLineWeight    = 83,
        kDataHorzBottomLineWeight    = 84,
        kDataVertLeftLineWeight      = 85,
        kDataVertInsideLineWeight    = 86,
        kDataVertRightLineWeight     = 87,

        // grid visibility
        kTitleHorzTopVisibility      = 100,
        kTitleHorzInsideVisibility   = 101,
        kTitleHorzBottomVisibility   = 102,
        kTitleVertLeftVisibility     = 103,
        kTitleVertInsideVisibility   = 104,
        kTitleVertRightVisibility    = 105,

        kHeaderHorzTopVisibility     = 106,
        kHeaderHorzInsideVisibility  = 107,
        kHeaderHorzBottomVisibility  = 108,
        kHeaderVertLeftVisibility    = 109,
        kHeaderVertInsideVisibility  = 110,
        kHeaderVertRightVisibility   = 111,

        kDataHorzTopVisibility       = 112,
        kDataHorzInsideVisibility    = 113,
        kDataHorzBottomVisibility    = 114,
        kDataVertLeftVisibility      = 115,
        kDataVertInsideVisibility    = 116,
        kDataVertRightVisibility     = 117,

        //cell 
        //
        kCellAlignment               = 130,
        kCellBackgroundFillNone      = 131,
        kCellBackgroundColor         = 132,
        kCellContentColor            = 133,
        kCellTextStyle               = 134,
        kCellTextHeight              = 135,
        kCellTopGridColor            = 136,
        kCellRightGridColor          = 137,
        kCellBottomGridColor         = 138,
        kCellLeftGridColor           = 139,
        kCellTopGridLineWeight       = 140,
        kCellRightGridLineWeight     = 141,
        kCellBottomGridLineWeight    = 142,
        kCellLeftGridLineWeight      = 143,
        kCellTopVisibility           = 144,
        kCellRightVisibility         = 145,
        kCellBottomVisibility        = 146,
        kCellLeftVisibility          = 147,
        kCellDataType                = 148,
    };

    AcDbTable();
    AcDbTable(const AcDbLinkedTableData* pTable, AcDb::TableCopyOption nCopyOption);
    virtual ~AcDbTable();


    //********************************************************************
    // Get and set methods for table properties
    //********************************************************************
    //
    virtual AcDbObjectId        tableStyle() const;
    virtual Acad::ErrorStatus   setTableStyle(const AcDbObjectId& id);

    virtual AcGeVector3d        direction() const;
    virtual Acad::ErrorStatus   setDirection(const AcGeVector3d& horzVec);

    virtual Adesk::UInt32       numRows() const;
    // Use setSize(int nRows, int nCols)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setNumRows(int nRows);

    virtual Adesk::UInt32       numColumns() const;
    // Use setSize(int nRows, int nCols)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setNumColumns(int nCols);

    virtual double              width() const;
    virtual Acad::ErrorStatus   setWidth(double width);

    virtual double              columnWidth(int col) const;
    virtual Acad::ErrorStatus   setColumnWidth(int col, double width);
    virtual Acad::ErrorStatus   setColumnWidth(double width);

    virtual double              height() const;
    virtual Acad::ErrorStatus   setHeight(double height);

    virtual double              rowHeight(int row) const;
    virtual Acad::ErrorStatus   setRowHeight(int row, double height);
    virtual Acad::ErrorStatus   setRowHeight(double height);
    virtual double              minimumColumnWidth(int col) const;
    virtual double              minimumRowHeight(int row) const;    
    virtual double              minimumTableWidth() const;
    virtual double              minimumTableHeight() const;        

    //********************************************************************
    // Get and set methods for table style overrides
    //********************************************************************
    //
    // Use margin(int nRow, int nCol, AcDb::CellMargin nMargin)
    ADESK_DEPRECATED virtual double horzCellMargin() const;
    // Use setMargin(int nRow, int nCol, AcDb::CellMargin nMargin, double fMargin)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setHorzCellMargin(double gap);

    // Use margin(int nRow, int nCol, AcDb::CellMargin nMargin)
    ADESK_DEPRECATED virtual double vertCellMargin() const;
    // Use setMargin(int nRow, int nCol, AcDb::CellMargin nMargin, double fMargin)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setVertCellMargin(double gap);

    virtual AcDb::FlowDirection flowDirection() const; 
    virtual Acad::ErrorStatus   setFlowDirection(AcDb::FlowDirection flow);

    ADESK_DEPRECATED virtual bool isTitleSuppressed() const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus suppressTitleRow(bool value);

    ADESK_DEPRECATED virtual bool isHeaderSuppressed() const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus suppressHeaderRow(bool value);

    ADESK_DEPRECATED virtual AcDb::CellAlignment alignment(AcDb::RowType type =
                                          AcDb::kDataRow) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus   setAlignment(AcDb::CellAlignment align,
                                          int rowTypes = AcDb::kAllRows);

    ADESK_DEPRECATED virtual bool isBackgroundColorNone(AcDb::RowType type = 
                                          AcDb::kDataRow) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus setBackgroundColorNone(bool value,
                                          int rowTypes = AcDb::kAllRows);

    ADESK_DEPRECATED virtual AcCmColor backgroundColor(AcDb::RowType type =
                                          AcDb::kDataRow) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus setBackgroundColor(const AcCmColor& color,
                                          int rowTypes = AcDb::kAllRows);

    ADESK_DEPRECATED virtual AcCmColor contentColor(AcDb::RowType type = 
                                          AcDb::kDataRow) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus setContentColor(const AcCmColor& color,
                                          int nRowType = AcDb::kAllRows);

    ADESK_DEPRECATED virtual Acad::ErrorStatus getDataType(AcValue::DataType& nDataType,
                                            AcValue::UnitType& nUnitType,
                                            AcDb::RowType type) const;

    ADESK_DEPRECATED virtual Acad::ErrorStatus setDataType(AcValue::DataType nDataType,
                                            AcValue::UnitType nUnitType);

    ADESK_DEPRECATED virtual Acad::ErrorStatus setDataType(AcValue::DataType nDataType, 
                                            AcValue::UnitType nUnitType, 
                                            int nRowTypes);

    // For internal use only
    ADESK_DEPRECATED virtual const ACHAR* format(AcDb::RowType type);
    // For internal use only
    ADESK_DEPRECATED virtual Acad::ErrorStatus setFormat(const ACHAR* pszFormat);
    // For internal use only
    ADESK_DEPRECATED virtual Acad::ErrorStatus setFormat(const ACHAR* pszFormat, 
                                          int nRowTypes);

    ADESK_DEPRECATED virtual AcDbObjectId  textStyle(AcDb::RowType type =
                                          AcDb::kDataRow) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus setTextStyle(const AcDbObjectId& id,
                                          int rowTypes = AcDb::kAllRows);

    ADESK_DEPRECATED virtual double textHeight(AcDb::RowType type =
                                          AcDb::kDataRow) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus setTextHeight(double height,
                                          int rowTypes = AcDb::kAllRows);

    ADESK_DEPRECATED virtual AcDb::LineWeight gridLineWeight(AcDb::GridLineType gridlineType,
                                AcDb::RowType type = AcDb::kDataRow) const; 
    ADESK_DEPRECATED virtual Acad::ErrorStatus setGridLineWeight(AcDb::LineWeight lwt,
                                               int nBorders,
                                               int nRows);

    ADESK_DEPRECATED virtual AcCmColor gridColor(AcDb::GridLineType gridlineType,
                                AcDb::RowType type = AcDb::kDataRow) const; 
    ADESK_DEPRECATED virtual Acad::ErrorStatus setGridColor(const AcCmColor& color,
                                               int nBorders,
                                               int nRows);

    ADESK_DEPRECATED virtual AcDb::Visibility gridVisibility(AcDb::GridLineType gridlineType,
                                AcDb::RowType type = AcDb::kDataRow) const; 
    ADESK_DEPRECATED virtual Acad::ErrorStatus setGridVisibility(AcDb::Visibility visible,
                                               int nBorders,
                                               int nRows);

    ADESK_DEPRECATED virtual bool tableStyleOverrides(
                                               AcDbIntArray& overrides) const;
    ADESK_DEPRECATED virtual void clearTableStyleOverrides(int options = 0);

    //********************************************************************
    // Get and set methods for common cell properties
    //********************************************************************
    //
    virtual AcDb::CellType      cellType(int row, 
                                         int col) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus setCellType(int row, 
                                         int col,
                                         AcDb::CellType type);

    virtual Acad::ErrorStatus   getCellExtents(int row, 
                                         int col,
                                         bool isOuterCell,
                                         AcGePoint3dArray& pts) const;

    virtual AcGePoint3d         attachmentPoint(int row, 
                                          int col) const; 

    virtual AcDb::CellAlignment alignment(int row, 
                                          int col) const;
    virtual Acad::ErrorStatus   setAlignment(int row, 
                                          int col,
                                          AcDb::CellAlignment align);

    virtual bool                isBackgroundColorNone(int row, 
                                          int col) const;
    virtual Acad::ErrorStatus   setBackgroundColorNone(int row, 
                                          int col, 
                                          bool value);

    virtual AcCmColor           backgroundColor(int row, 
                                          int col) const;
    virtual Acad::ErrorStatus   setBackgroundColor(int row, 
                                          int col,
                                          const AcCmColor& color);

    virtual AcCmColor           contentColor(int row, 
                                             int col) const;
    virtual Acad::ErrorStatus   setContentColor(int row, 
                                             int col,
                                             const AcCmColor& color);

    virtual bool                cellStyleOverrides(int row, 
                                         int col, 
                                         AcDbIntArray& overrides) const;
                                         
    void                        clearCellOverrides(int row, int column);

    // Use deleteContent(int nRow, int nCol, int nIndex)
    ADESK_DEPRECATED virtual Acad::ErrorStatus deleteCellContent(int row, 
                                             int col);
    ADESK_DEPRECATED virtual AcDb::RowType rowType(int row) const;


    //********************************************************************
    // Get and set methods for text cell properties
    //********************************************************************
    //
    Acad::ErrorStatus       getDataType(int row, int col,
                                        AcValue::DataType& nDataType,
                                        AcValue::UnitType& nUnitType) const;

    Acad::ErrorStatus       setDataType(int row, int col, 
                                        AcValue::DataType nDataType,
                                        AcValue::UnitType nUnitType);

    AcValue                 value(int row, int col) const;

    Acad::ErrorStatus       setValue(int row, int col, 
                                     const AcValue& val);

    Acad::ErrorStatus       setValue(int row, int col, 
                                     const wchar_t* pszText,
                                     AcValue::ParseOption nOption);

    Acad::ErrorStatus       resetValue(int row, int col);
    // For internal use only
    const ACHAR* format(int row, int col) const;
    // For internal use only
    ADESK_DEPRECATED Acad::ErrorStatus setFormat(int row, int col, 
                                                   const ACHAR* pszFormat);
    virtual const ACHAR*         textStringConst(int row, 
                                                int col) const;
    virtual ACHAR*               textString(int row, 
                                           int col) const;
    virtual Acad::ErrorStatus textString(int row, int col, 
                                   AcValue::FormatOption nOption,
                                   AcString& sText) const;
    virtual Acad::ErrorStatus   setTextString(int row, 
                                           int col,
                                           const ACHAR* text);

    virtual AcDbObjectId        fieldId(int row, int col) const;
    virtual Acad::ErrorStatus   setFieldId(int row, int col, const AcDbObjectId& fieldId);

    virtual Acad::ErrorStatus   setFieldId(int row, int col, const AcDbObjectId& fieldId, 
        AcDb::CellOption nFlag);

    virtual AcDbObjectId        textStyle(int row, 
                                          int col) const;
    virtual Acad::ErrorStatus   setTextStyle(int row, 
                                          int col,
                                          const AcDbObjectId& id);

    virtual double              textHeight(int row,
                                           int col) const;
    virtual Acad::ErrorStatus   setTextHeight(int row, 
                                           int col,
                                           double height);

    // Use rotation(int nRow, int nCol, int nContent)
    ADESK_DEPRECATED virtual AcDb::RotationAngle textRotation(int row,
                                              int col) const;
    // Use setRotation(int nRow, int nCol, int nContent, double fContent)
    ADESK_DEPRECATED virtual Acad::ErrorStatus  setTextRotation(int row, 
                                              int col,
                                              AcDb::RotationAngle rot);

    //********************************************************************
    // Get and set methods for block cell properties
    //********************************************************************
    //
    // Use isAutoScale(int row, int col, int nContent)
    ADESK_DEPRECATED virtual bool isAutoScale(int row,
                                              int col) const;
    // Use setAutoScale(int row, int col, int nContent, autoFit)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setAutoScale(int row, 
                                              int col,
                                              bool autoFit);

    virtual AcDbObjectId        blockTableRecordId(int row, 
                                                   int col) const;

    virtual Acad::ErrorStatus   setBlockTableRecordId(int row, 
                                                      int col,
                                                      const AcDbObjectId& blkId,
                                                      bool autoFit = false);

    // Use scale(int row, int col, int nContent)
    ADESK_DEPRECATED virtual double blockScale(int row,
                                               int col) const;
    // Use setScale(int row, int col, int nContent, double scale)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setBlockScale(int row, 
                                              int col,
                                              double scale);

    // Use rotation(int nRow, int nCol, int nContent)
    ADESK_DEPRECATED virtual double blockRotation(int row,
                                              int col) const;
    // Use setRotation(int nRow, int nCol, int nContent, double fContent)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setBlockRotation(int row, 
                                              int col,
                                              double rotAng);

    virtual Acad::ErrorStatus   getBlockAttributeValue(int row, 
                                           int col, 
                                           const AcDbObjectId& attdefId,
                                           ACHAR*& value) const;
    virtual Acad::ErrorStatus   setBlockAttributeValue(int row, 
                                           int col,
                                           const AcDbObjectId& attdefId,
                                           const ACHAR* value);

    //********************************************************************
    // Get and set methods for cell grid line properties
    //********************************************************************
    //
    virtual AcCmColor           gridColor(int row, 
                                          int col,
                                          AcDb::CellEdgeMask iEdge) const;
    virtual Acad::ErrorStatus   setGridColor(int row, 
                                          int col,
                                          short nEdges,
                                          const AcCmColor& color);

    virtual AcDb::Visibility    gridVisibility(int row, 
                                          int col,
                                          AcDb::CellEdgeMask iEdge) const;
    virtual Acad::ErrorStatus   setGridVisibility(int row, 
                                          int col,
                                          short nEdges,
                                          AcDb::Visibility value);

    virtual AcDb::LineWeight    gridLineWeight(int row, 
                                          int col,
                                          AcDb::CellEdgeMask iEdge) const;
    virtual Acad::ErrorStatus   setGridLineWeight(int row, 
                                          int col,
                                          short nEdges,
                                          AcDb::LineWeight value);

    //********************************************************************
    // Insert and delete methods for columns and rows
    //********************************************************************
    //
    virtual Acad::ErrorStatus insertColumns (int col, 
                                             double width, 
                                             int nCols = 1);
    virtual Acad::ErrorStatus deleteColumns (int col, 
                                             int nCols = 1);

    virtual Acad::ErrorStatus insertRows    (int row, 
                                             double height, 
                                             int nRows = 1);

    virtual Acad::ErrorStatus deleteRows    (int row, 
                                             int nRows = 1);

    //********************************************************************
    // Merge and unmerge methods
    //********************************************************************
    //
    virtual Acad::ErrorStatus   mergeCells(int minRow, int maxRow,
                                           int minCol, int maxCol);
    virtual Acad::ErrorStatus   unmergeCells(int minRow, int maxRow,
                                           int minCol, int maxCol);

    virtual bool                isMergedCell(int row, int col, 
                                             int* minRow = NULL, 
                                             int* maxRow = NULL,
                                             int* minCol = NULL, 
                                             int* maxCol = NULL) const;

    //********************************************************************
    // Methods to generate table layout and table block
    //********************************************************************
    //
    virtual Acad::ErrorStatus generateLayout();
    virtual Acad::ErrorStatus recomputeTableBlock(bool forceUpdate = true);

    //********************************************************************
    // Methods for sub-selection  
    //********************************************************************
    //
    virtual bool              hitTest(const AcGePoint3d& wpt, 
                                      const AcGeVector3d& wviewVec,
                                      double wxaper,
                                      double wyaper,
                                      int& resultRowIndex, 
                                      int& resultColumnIndex);
    bool                      hitTest(const AcGePoint3d& wpt, 
                                      const AcGeVector3d& wviewVec,
                                      double wxaper,
                                      double wyaper,
                                      int& resultRowIndex, 
                                      int& resultColumnIndex,
                                      int& contentIndex,
                                      AcDb::TableHitItem& nItem);

    virtual Acad::ErrorStatus select(const AcGePoint3d& wpt, 
                                     const AcGeVector3d& wvwVec, 
                                     const AcGeVector3d& wvwxVec, 
                                     double wxaper,
                                     double wyaper,
                                     bool allowOutside,
                                     bool bInPickFirst, 
                                     int& resultRowIndex, 
                                     int& resultColumnIndex,
                                     AcDbFullSubentPathArray* pPaths = NULL) const;

    virtual Acad::ErrorStatus selectSubRegion(const AcGePoint3d& wpt1, 
                                     const AcGePoint3d& wpt2,
                                     const AcGeVector3d& wvwVec, 
                                     const AcGeVector3d& wvwxVec,
                                     double wxaper,
                                     double wyaper,                             
                                     AcDb::SelectType seltype,
                                     bool bIncludeCurrentSelection,
                                     bool bInPickFirst,                             
                                     int& rowMin,
                                     int& rowMax,
                                     int& colMin,
                                     int& colMax,
                                     AcDbFullSubentPathArray* pPaths = NULL) const;

    virtual bool reselectSubRegion(AcDbFullSubentPathArray& paths) const;
            
    virtual Acad::ErrorStatus getSubSelection(int& rowMin, 
                                             int& rowMax, 
                                             int& colMin, 
                                             int& colMax) const;
    AcCellRange     getSubSelection         (void) const;
    virtual Acad::ErrorStatus setSubSelection(int rowMin, 
                                             int rowMax, 
                                             int colMin, 
                                             int colMax);
    Acad::ErrorStatus setSubSelection       (const AcCellRange& range);

    virtual void              clearSubSelection();

    virtual bool              hasSubSelection() const;

    //********************************************************************
    // Overridden methods from AcDbObject
    //********************************************************************
    //
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const override;

    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const override;

    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo) override;

    virtual Acad::ErrorStatus subClose() override;
    virtual void              objectClosed(const AcDbObjectId objId) override;
    virtual void              erased(const AcDbObject* dbObj,
                                      Adesk::Boolean pErasing = true) override;

    //********************************************************************
    // Overridden methods from AcDbBlockReference required for AcDbTable
    //********************************************************************
    //
    virtual Acad::ErrorStatus setPosition(const AcGePoint3d&) override;

    virtual Acad::ErrorStatus setNormal(const AcGeVector3d& newVal) override;

    //********************************************************************
    // Methods for internal use only
    //********************************************************************
    //
    virtual Acad::ErrorStatus select_next_cell(int dir,
                                     int& resultRowIndex, 
                                     int& resultColumnIndex,
                                     AcDbFullSubentPathArray* pPaths = NULL,
                                     bool bSupportTextCellOnly = true) const;

    virtual void              setRegen();
    virtual void              suppressInvisibleGrid(bool value);
    virtual Acad::ErrorStatus getCellExtents(int row, 
                                         int col,
                                         double& cellWidth,
                                         double& cellHeight,
                                         bool bAdjustForMargins) const;
    bool isRegenerateTableSuppressed() const;
    void suppressRegenerateTable(bool bSuppress);

    ACDBCORE2D_PORT void setRecomputeTableBlock(bool newVal);

    //********************************************************************
    // New Methods
    //********************************************************************

    Acad::ErrorStatus setSize               (int nRows, 
                                             int nCols);
    bool            canInsert               (int nIndex, 
                                             bool bRow) const;
    Acad::ErrorStatus insertRowsAndInherit  (int nIndex, 
                                             int nInheritFrom,
                                             int nNumRows);
    Acad::ErrorStatus insertColumnsAndInherit(int col, 
                                             int nInheritFrom, 
                                             int nNumCols);
    bool            canDelete               (int nIndex, 
                                             int nCount,
                                             bool bRow) const;
    bool            isEmpty                 (int nRow, 
                                             int nCol) const;
    AcCellRange     getMergeRange           (int nRow, 
                                             int nCol) const;
    AcDbTableIterator* getIterator          (void) const;
    AcDbTableIterator* getIterator          (const AcCellRange* pRange, 
                                             AcDb::TableIteratorOption nOption) const;
    bool            isContentEditable       (int nRow, 
                                             int nCol) const;
    bool            isFormatEditable        (int nRow, 
                                             int nCol) const;
    AcDb::CellState cellState               (int nRow, 
                                             int nCol) const;
    Acad::ErrorStatus setCellState          (int nRow, 
                                             int nCol, 
                                             AcDb::CellState nLock);

    int             numContents             (int nRow, 
                                             int nCol) const;
    int             createContent           (int nRow, 
                                             int nCol, 
                                             int nIndex);
    Acad::ErrorStatus moveContent           (int nRow, 
                                             int nCol, 
                                             int nFromIndex, 
                                             int nToIndex);
    Acad::ErrorStatus deleteContent         (int nRow, 
                                             int nCol);
    Acad::ErrorStatus deleteContent         (int nRow, 
                                             int nCol, 
                                             int nIndex);
    Acad::ErrorStatus deleteContent         (const AcCellRange& range);

    AcDb::CellContentType contentType       (int nRow, 
                                             int nCol) const;
    AcDb::CellContentType contentType       (int nRow, 
                                             int nCol, 
                                             int nIndex) const;

    AcValue value                           (int row, 
                                             int col, 
                                             int nContent) const;
    AcValue value                           (int row, 
                                             int col, 
                                             int nContent,
                                             AcValue::FormatOption nOption) const;
    Acad::ErrorStatus setValue              (int row, 
                                             int col, 
                                             int nContent, 
                                             const AcValue& val);
    Acad::ErrorStatus setValue              (int row, 
                                             int col, 
                                             int nContent, 
                                             const AcValue& val,
                                             AcValue::ParseOption nOption);
    Acad::ErrorStatus setValue              (int row, 
                                             int col, 
                                             int nContent, 
                                             const wchar_t* pszText, 
                                             AcValue::ParseOption nOption);
    AcString        dataFormat              (int row, 
                                             int col) const;
    AcString        dataFormat              (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setDataFormat         (int row, 
                                             int col, 
                                             const ACHAR* pszFormat);
    Acad::ErrorStatus setDataFormat         (int row, 
                                             int col, 
                                             int nContent, 
                                             const ACHAR* pszFormat);
    AcString        textString              (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus textString            (int row, 
                                             int col, 
                                             int nContent, 
                                             AcValue::FormatOption nOption, 
                                             AcString& sText) const;
    Acad::ErrorStatus setTextString         (int row, 
                                             int col, 
                                             int nContent, 
                                             const ACHAR* text);
    bool            hasFormula              (int nRow, 
                                             int nCol, 
                                             int nContent) const;
    AcString        getFormula              (int nRow, 
                                             int nCol, 
                                             int nContent) const;
    Acad::ErrorStatus setFormula            (int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             const ACHAR* pszFormula);
    AcDbObjectId    fieldId                 (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setFieldId            (int row, 
                                             int col, 
                                             int nContent, 
                                             const AcDbObjectId& fieldId, 
                                             AcDb::CellOption nFlag);
    AcDbObjectId    blockTableRecordId      (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setBlockTableRecordId (int row, 
                                             int col, 
                                             int nContent, 
                                             const AcDbObjectId& blkId, 
                                             bool autoFit);
    Acad::ErrorStatus getBlockAttributeValue(int row, 
                                             int col, 
                                             int nContent, 
                                             const AcDbObjectId& attdefId, 
                                             ACHAR*& value) const;
    Acad::ErrorStatus setBlockAttributeValue(int row, 
                                             int col, 
                                             int nContent, 
                                             const AcDbObjectId& attdefId, 
                                             const ACHAR* value);
    int             getCustomData           (int nRow, 
                                             int nCol) const;
    Acad::ErrorStatus setCustomData         (int nRow, 
                                             int nCol, 
                                             int nData);
    Acad::ErrorStatus getCustomData         (int nRow, 
                                             int nCol, 
                                             const ACHAR* pszKey, 
                                             AcValue* pData) const;
    Acad::ErrorStatus setCustomData         (int nRow, 
                                             int nCol, 
                                             const ACHAR* pszKey, 
                                             const AcValue* pData);
    const ACHAR *   cellStyle               (int nRow, 
                                             int nCol) const;
    Acad::ErrorStatus setCellStyle          (int nRow, 
                                             int nCol, 
                                             const ACHAR* pszCellStyle);
    double          margin                  (int nRow, 
                                             int nCol, 
                                             AcDb::CellMargin nMargin) const;
    Acad::ErrorStatus setMargin             (int nRow, 
                                             int nCol, 
                                             AcDb::CellMargin nMargins, 
                                             double fMargin);
    AcGePoint3d     attachmentPoint         (int row, 
                                             int col,
                                             int content) const;
    AcCmColor       contentColor            (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setContentColor       (int row, 
                                             int col, 
                                             int nContent, 
                                             const AcCmColor& color);
    Acad::ErrorStatus getDataType           (int row, 
                                             int col, 
                                             int nContent, 
                                             AcValue::DataType& nDataType, 
                                             AcValue::UnitType& nUnitType) const;
    Acad::ErrorStatus setDataType           (int row, 
                                             int col, 
                                             int nContent, 
                                             AcValue::DataType nDataType, 
                                             AcValue::UnitType nUnitType);
    AcDbObjectId    textStyle               (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setTextStyle          (int row, 
                                             int col, 
                                             int nContent, 
                                             const AcDbObjectId& id);
    double          textHeight              (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setTextHeight         (int row, 
                                             int col, 
                                             int nContent, 
                                             double height);
    double          rotation                (void) const;
    double          rotation                (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setRotation           (double fAngle) override;
    Acad::ErrorStatus setRotation           (int row, 
                                             int col, 
                                             int nContent, 
                                             double fAngle);
    bool            isAutoScale             (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setAutoScale          (int row, 
                                             int col, 
                                             int nContent, 
                                             bool autoFit);
    double          scale                   (int row, 
                                             int col, 
                                             int nContent) const;
    Acad::ErrorStatus setScale              (int row, 
                                             int col, 
                                             int nContent, 
                                             double scale);
    AcDb::CellContentLayout contentLayout  (int row, 
                                             int col) const;
    Acad::ErrorStatus setContentLayout      (int row, 
                                             int col, 
                                             AcDb::CellContentLayout nLayout);
    bool            isMergeAllEnabled       (int nRow, 
                                             int nCol) const;
    Acad::ErrorStatus enableMergeAll        (int nRow, 
                                             int nCol,
                                             bool bEnable);
    AcDb::CellProperty getOverride          (int nRow, 
                                             int nCol, 
                                             int nContent) const;
    AcDb::GridProperty getOverride          (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    Acad::ErrorStatus setOverride           (int nRow, 
                                             int nCol, 
                                             int nContent, 
                                             AcDb::CellProperty nOverride);
    Acad::ErrorStatus setOverride           (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType, 
                                             AcDb::GridProperty nOverride);
    Acad::ErrorStatus removeAllOverrides    (int nRow, 
                                             int nCol);
    AcDb::GridLineStyle gridLineStyle       (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    Acad::ErrorStatus setGridLineStyle      (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             AcDb::GridLineStyle nLineStyle);
    AcDb::LineWeight gridLineWeight         (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    Acad::ErrorStatus setGridLineWeight     (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             AcDb::LineWeight nLineWeight);
    AcDbObjectId    gridLinetype            (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    Acad::ErrorStatus setGridLinetype       (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             const AcDbObjectId& idLinetype);
    AcCmColor       gridColor               (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    Acad::ErrorStatus setGridColor          (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridlineTypes, 
                                             const AcCmColor& color);
    AcDb::Visibility gridVisibility         (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    Acad::ErrorStatus setGridVisibility     (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             AcDb::Visibility nVisibility);
    double          gridDoubleLineSpacing   (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType) const;
    Acad::ErrorStatus setGridDoubleLineSpacing(int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes,
                                             double fSpacing);
    Acad::ErrorStatus getGridProperty       (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineType, 
                                             AcGridProperty& gridProp) const;
    Acad::ErrorStatus setGridProperty       (int nRow, 
                                             int nCol, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             const AcGridProperty& gridProp);
    Acad::ErrorStatus setGridProperty       (const AcCellRange& rangeIn, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             const AcGridProperty& gridProp);

    bool            isLinked                (int nRow, 
                                             int nCol) const;
    AcDbObjectId getDataLink                (int nRow, 
                                             int nCol) const;
    Acad::ErrorStatus getDataLink           (int nRow, 
                                             int nCol, 
                                             AcDbDataLink*& pDataLink, 
                                             AcDb::OpenMode mode) const;
    int             getDataLink             (const AcCellRange* pRange, 
                                             AcDbObjectIdArray& dataLinkIds) const;
    Acad::ErrorStatus setDataLink           (int nRow, 
                                             int nCol, 
                                             const AcDbObjectId& idDataLink,
                                             bool bUpdate);
    Acad::ErrorStatus setDataLink           (const AcCellRange& range, 
                                             const AcDbObjectId& idDataLink,
                                             bool bUpdate);
    AcCellRange     getDataLinkRange        (int nRow, 
                                             int nCol) const;
    Acad::ErrorStatus removeDataLink        (int nRow, 
                                             int nCol);
    Acad::ErrorStatus removeDataLink        (void);
    Acad::ErrorStatus updateDataLink        (int nRow, 
                                             int nCol, 
                                             AcDb::UpdateDirection nDir,
                                             AcDb::UpdateOption nOption);
    Acad::ErrorStatus updateDataLink        (AcDb::UpdateDirection nDir, 
                                             AcDb::UpdateOption nOption);

    bool            isBreakEnabled          (void) const;
    Acad::ErrorStatus enableBreak           (bool bEnable);
    AcDb::TableBreakFlowDirection breakFlowDirection(void) const;
    Acad::ErrorStatus setBreakFlowDirection (AcDb::TableBreakFlowDirection nDir);
    double          breakHeight             (int nIndex) const;
    Acad::ErrorStatus setBreakHeight        (int nIndex, 
                                             double fHeight);
    AcGeVector3d    breakOffset             (int nIndex) const;
    Acad::ErrorStatus setBreakOffset        (int nIndex, 
                                             const AcGeVector3d& vec);
    AcDb::TableBreakOption breakOption      (void) const;
    Acad::ErrorStatus setBreakOption        (AcDb::TableBreakOption nOption);
    double          breakSpacing            (void) const;
    Acad::ErrorStatus setBreakSpacing       (double fSpacing);
    Acad::ErrorStatus copyFrom              (const AcDbLinkedTableData* pSrc, 
                                             AcDb::TableCopyOption nOption);
    Acad::ErrorStatus copyFrom              (const AcDbLinkedTableData* pSrc, 
                                             AcDb::TableCopyOption nOption, 
                                             const AcCellRange& srcRange, 
                                             const AcCellRange& targetRange,
                                             AcCellRange* pNewTargetRangeOut);
    Acad::ErrorStatus copyFrom              (const AcDbTable* pSrc, 
                                             AcDb::TableCopyOption nOption, 
                                             const AcCellRange& srcRange, 
                                             const AcCellRange& targetRange,
                                             AcCellRange* pNewTargetRangeOut);
    Acad::ErrorStatus fill                  (const AcCellRange& fillRange, 
                                             const AcCellRange& srcRange, 
                                             AcDb::TableFillOption nOption);
    const ACHAR *   getColumnName           (int nIndex) const;
    Acad::ErrorStatus setColumnName         (int nIndex, 
                                             const ACHAR* pszName);
    AcString        getToolTip              (int nRow, 
                                             int nCol) const;
    Acad::ErrorStatus setToolTip            (int nRow, 
                                             int nCol, 
                                             const ACHAR* pszToolTip);
    Acad::ErrorStatus createTemplate        (AcDbTableTemplate*& pTemplate, 
                                             AcDb::TableCopyOption nCopyOption);
    Acad::ErrorStatus getIndicatorSize      (double& fWidth, 
                                             double& fHeight) const;
    ACDBCORE2D_PORT AcCellRange                   cellRange() const;

protected:
    // Get corresponding COM wrapper class ID
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

#pragma pack(pop)
