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
// dbTableStyle.h
//
//  DESCRIPTION: AcDbTableStyle API class declaration
//
//  AcRxObject
//    AcDbObject
//      AcDbTableStyle
//

#ifndef __DBTABLESTYLE_H__
#define __DBTABLESTYLE_H__

#pragma once

#include "dbmain.h"
#include "AdAChar.h"
#include "AcValue.h"
#include "AcString.h"
#include "DbFormattedTableData.h"
#include "AcDbCore2dDefs.h"

#pragma pack (push, 8)

class AcDbTableTemplate;
class AcDbTableStyle : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTableStyle);

    AcDbTableStyle();
    virtual ~AcDbTableStyle();

    // AcDbTableStyle protocol
    //

    // General Properties
    //
    ACDBCORE2D_PORT  virtual Acad::ErrorStatus   getName(AcString & sName) const;
    ACDBCORE2D_PORT  virtual Acad::ErrorStatus   getName(ACHAR*& pszName) const final;   // deprecated
    virtual Acad::ErrorStatus   setName(const ACHAR * pszName);
    bool                        isRenamable() const;

    virtual const ACHAR*        description(void) const;
    virtual Acad::ErrorStatus   setDescription(const ACHAR * pszDescription);

    virtual Adesk::UInt32       bitFlags() const;
    virtual Acad::ErrorStatus   setBitFlags(Adesk::UInt32 flags);

    virtual AcDb::FlowDirection flowDirection(void) const; 
    virtual Acad::ErrorStatus   setFlowDirection(AcDb::FlowDirection flow);

    // Use margin(AcDb::CellMargin nMargin, const ACHAR* pszCellStyle)
    ADESK_DEPRECATED virtual double horzCellMargin(void) const;
    // Use setMargin(AcDb::CellMargin nMargins, double fMargin, const ACHAR* pszCellStyle)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setHorzCellMargin(double dCellMargin);

    // Use margin(AcDb::CellMargin nMargin, const ACHAR* pszCellStyle)
    ADESK_DEPRECATED virtual double vertCellMargin(void) const;
    // Use setMargin(AcDb::CellMargin nMargins, double fMargin, const ACHAR* pszCellStyle)
    ADESK_DEPRECATED virtual Acad::ErrorStatus setVertCellMargin(double dCellMargin);

    ADESK_DEPRECATED virtual bool isTitleSuppressed(void) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus suppressTitleRow(bool bValue);

    ADESK_DEPRECATED virtual bool isHeaderSuppressed(void) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus suppressHeaderRow(bool bValue);


    // Cell properties
    //
    virtual AcDbObjectId        textStyle(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setTextStyle(const AcDbObjectId id,
                                            int rowTypes = AcDb::kAllRows);
    
    virtual double              textHeight(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setTextHeight(double dHeight,
                                              int rowTypes = AcDb::kAllRows);

    virtual AcDb::CellAlignment alignment(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setAlignment(AcDb::CellAlignment alignment,
                                             int rowTypes = AcDb::kAllRows);

    virtual AcCmColor           color(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setColor(const AcCmColor& color,
                                         int rowTypes = AcDb::kAllRows);

    virtual AcCmColor           backgroundColor(AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setBackgroundColor(const AcCmColor& color,
                                                   int rowTypes = AcDb::kAllRows);

    ADESK_DEPRECATED virtual bool isBackgroundColorNone(AcDb::RowType rowType = AcDb::kDataRow) const;
    ADESK_DEPRECATED virtual Acad::ErrorStatus setBackgroundColorNone(bool bValue,
                                                       int rowTypes = AcDb::kAllRows);
    virtual Acad::ErrorStatus   getDataType(AcValue::DataType& nDataType,
                                            AcValue::UnitType& nUnitType) const;
    // For internal use only
    ADESK_DEPRECATED virtual Acad::ErrorStatus   getDataType(AcValue::DataType& nDataType,
                                            AcValue::UnitType& nUnitType,
                                            AcDb::RowType rowType) const;
    virtual Acad::ErrorStatus   setDataType(AcValue::DataType nDataType,
                                            AcValue::UnitType nUnitType);
    // For internal use only
    ADESK_DEPRECATED virtual Acad::ErrorStatus   setDataType(AcValue::DataType nDataType, 
                                            AcValue::UnitType nUnitType,
                                            int rowTypes);

    // Use format(const ACHAR* pszCellStyle)
    ADESK_DEPRECATED virtual const ACHAR* format (void) const;
    // For internal use only
    ADESK_DEPRECATED virtual const ACHAR* format (AcDb::RowType rowType) const;
    // Use setFormat(const ACHAR* pszFormat, const ACHAR* pszCellStyle);
    ADESK_DEPRECATED virtual Acad::ErrorStatus   setFormat(const ACHAR* pszFormat);
    // For internal use only
    ADESK_DEPRECATED virtual Acad::ErrorStatus   setFormat(const ACHAR* pszFormat,
                                          int rowTypes);

    //Gridline properties
    //
    virtual AcDb::LineWeight    gridLineWeight(AcDb::GridLineType gridLineType, 
                                               AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setGridLineWeight(AcDb::LineWeight lineWeight,
                                                  int gridLineTypes = AcDb::kAllGridLines, 
                                                  int rowTypes = AcDb::kAllRows);
    virtual AcCmColor           gridColor(AcDb::GridLineType gridLineType, 
                                          AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setGridColor(const AcCmColor color,
                                             int gridLineTypes = AcDb::kAllGridLines, 
                                             int rowTypes = AcDb::kAllRows);
    virtual AcDb::Visibility    gridVisibility(AcDb::GridLineType gridLineType, 
                                               AcDb::RowType rowType = AcDb::kDataRow) const;
    virtual Acad::ErrorStatus   setGridVisibility(AcDb::Visibility visible,
                                                  int gridLineTypes = AcDb::kAllGridLines, 
                                                  int rowTypes = AcDb::kAllRows);

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const override;
    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo) override;

    // Utility functions
    //
    virtual Acad::ErrorStatus   postTableStyleToDb(AcDbDatabase* pDb, 
                                                   const ACHAR* styleName, 
                                                   AcDbObjectId& tableStyleId);

    // New functions added in Spago - these methods are not virtual so API
    // compatibility is maintained
    // Creates a cell style and assigns a unique name
    const ACHAR *   createCellStyle         (void);
    Acad::ErrorStatus createCellStyle       (const ACHAR* pszCellStyle);
    Acad::ErrorStatus createCellStyle       (const ACHAR* pszCellStyle, 
                                             const ACHAR* pszFromCellStyle);
    Acad::ErrorStatus renameCellStyle       (const ACHAR* pszOldName, 
                                             const ACHAR* pszNewName);
    Acad::ErrorStatus deleteCellStyle       (const ACHAR* pszCellStyle);
    Acad::ErrorStatus copyCellStyle         (const ACHAR* pszSrcCellStyle, 
                                             const ACHAR* pszTargetCellStyle);
    Acad::ErrorStatus copyCellStyle         (const AcDbTableStyle* pSrc, 
                                             const ACHAR* pszSrcCellStyle,
                                             const ACHAR* pszTargetCellStyle);
    Acad::ErrorStatus getUniqueCellStyleName(const ACHAR* pszBaseName, 
                                             AcString& sUniqueName) const;
    bool            isCellStyleInUse        (const ACHAR* pszCellStyle) const;
    int             numCellStyles           (void) const;
    int             getCellStyles           (AcStringArray& cellstyles) const;

    AcDbObjectId    textStyle               (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setTextStyle          (const AcDbObjectId& id, 
                                             const ACHAR* pszCellStyle);

    double          textHeight              (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setTextHeight         (double dHeight, 
                                             const ACHAR* pszCellStyle);

    AcDb::CellAlignment alignment           (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setAlignment          (AcDb::CellAlignment alignment, 
                                             const ACHAR* pszCellStyle);

    AcCmColor       color                   (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setColor              (const AcCmColor& color, 
                                             const ACHAR* pszCellStyle);

    AcCmColor       backgroundColor         (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setBackgroundColor    (const AcCmColor& color, 
                                             const ACHAR* pszCellStyle);

    Acad::ErrorStatus getDataType           (AcValue::DataType& nDataType, 
                                             AcValue::UnitType& nUnitType, 
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setDataType           (AcValue::DataType nDataType, 
                                             AcValue::UnitType nUnitType, 
                                             const ACHAR* pszCellStyle);

    const ACHAR *   format                  (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setFormat             (const ACHAR* pszFormat, 
                                             const ACHAR* pszCellStyle);

    int             cellClass               (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setCellClass          (int nClass, 
                                             const ACHAR* pszCellStyle);

    double          rotation                (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setRotation           (double fRotation, 
                                             const ACHAR* pszCellStyle);

    bool            isMergeAllEnabled       (const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus enableMergeAll        (bool bEnable, 
                                             const ACHAR* pszCellStyle);

    double          margin                  (AcDb::CellMargin nMargin,
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setMargin             (AcDb::CellMargin nMargins, 
                                             double fMargin,
                                             const ACHAR* pszCellStyle);

    //Gridline properties
    //
    AcDb::LineWeight gridLineWeight         (AcDb::GridLineType gridLineType, 
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setGridLineWeight     (AcDb::LineWeight lineWeight, 
                                             AcDb::GridLineType gridLineTypes, 
                                             const ACHAR* pszCellStyle);
    AcCmColor       gridColor               (AcDb::GridLineType gridLineType, 
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setGridColor          (const AcCmColor color, 
                                             AcDb::GridLineType gridLineTypes, 
                                             const ACHAR* pszCellStyle);
    AcDb::Visibility gridVisibility         (AcDb::GridLineType gridLineType, 
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setGridVisibility     (AcDb::Visibility visible, 
                                             AcDb::GridLineType gridLineTypes, 
                                             const ACHAR* pszCellStyle);
    double          gridDoubleLineSpacing   (AcDb::GridLineType gridLineType, 
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setGridDoubleLineSpacing(double fSpacing, 
                                             AcDb::GridLineType gridLineTypes, 
                                             const ACHAR* pszCellStyle);
    AcDb::GridLineStyle gridLineStyle       (AcDb::GridLineType gridLineType, 
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setGridLineStyle      (AcDb::GridLineStyle nLineStyle, 
                                             AcDb::GridLineType gridLineTypes, 
                                             const ACHAR* pszCellStyle);
    AcDbObjectId    gridLinetype            (AcDb::GridLineType gridLineType, 
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setGridLinetype       (const AcDbObjectId& id, 
                                             AcDb::GridLineType gridLineTypes, 
                                             const ACHAR* pszCellStyle);
    Acad::ErrorStatus getGridProperty       (AcGridProperty& gridProp, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             const ACHAR* pszCellStyle) const;
    Acad::ErrorStatus setGridProperty       (const AcGridProperty& gridProp, 
                                             AcDb::GridLineType nGridLineTypes, 
                                             const ACHAR* pszCellStyle);

    // Template functions
    AcDbObjectId    getTemplate             (void) const;
    Acad::ErrorStatus getTemplate           (AcDbTableTemplate*& pTemplate, 
                                             AcDb::OpenMode mode);
    Acad::ErrorStatus setTemplate           (const AcDbObjectId& templateId, 
                                             AcDb::MergeCellStyleOption nOption);
    Acad::ErrorStatus setTemplate           (AcDbTableTemplate* pTemplate, 
                                             AcDb::MergeCellStyleOption nOption,
                                             AcDbObjectId& templateId);
    AcDbObjectId    removeTemplate          (void);

protected:
    //********************************************************************
    // Get corresponding COM wrapper class ID
    //********************************************************************
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

#pragma pack (pop)

// This overload is deprecated. Please use the one taking AcString & arg instead
inline Acad::ErrorStatus AcDbTableStyle::getName(ACHAR*& pName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbTableStyle::getName, pName);
}
#endif // __DBTABLESTYLE_H__

