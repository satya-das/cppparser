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
// Name:            AcTcUi.h
//
// Description:     Place for all the exported global functions 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUI_H__
#define __ACTCUI_H__

#include "adui.h"
#include "AdAChar.h"
#include <afxtempl.h>

#ifdef  _ACTCUI_BUILD
#  define   ACTCUI_PORT  __declspec(dllexport)
#else
#  define   ACTCUI_PORT  
#endif


class CAcTcUiManager;
class CAcTcUiToolPaletteSet;
class CAcTcUiToolPalette;
class CAcTcUiCatalogView;
class AcTcCatalogItem;
class AcTcCatalog;
class AcTcStockTool;
class AcTcTool;

typedef CTypedPtrArray<CPtrArray, AcTcCatalogItem*> AcTcCatalogItemArray;
typedef CTypedPtrArray<CPtrArray, AcTcStockTool*>   AcTcStockToolArray;
typedef CTypedPtrArray<CPtrArray, AcTcCatalog*>     AcTcCatalogArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiToolPaletteSet*> AcTcUiToolPaletteSetArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiToolPalette*> AcTcUiToolPaletteArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiCatalogView*> AcTcUiCatalogViewArray;



// Drag and drop formats
//
#define ACTCUI_DRAGFORMAT_CUSTOM        (0x1 << 0)
#define ACTCUI_DRAGFORMAT_IDROP         (0x1 << 1)
#define ACTCUI_DRAGFORMAT_HDROP         (0x1 << 2)

// For creating a new default palette set
//
#define ACTCUI_CNPS_NOCREATEWINDOW      (0x1 << 0)
#define ACTCUI_CNPS_NOADD               (0x1 << 1)
#define ACTCUI_CNPS_CREATEHIDDEN        (0x1 << 2)

// Clipboard formats
//
#define CF_ACTC_CATALOG_ITEM_17_11          ACRX_T(/*MSGO*/"CF_ACTC_CATALOG_ITEM_17_11")
#define CF_ACTCUI_CATALOG_ITEM_HEADER_17_11 ACRX_T(/*MSGO*/"CF_ACTCUI_CATALOG_ITEM_HEADER_17_11")
#define CF_ACTC_CATALOG_ITEM_17_1           ACRX_T(/*MSGO*/"CF_ACTC_CATALOG_ITEM_17_1")
#define CF_ACTCUI_CATALOG_ITEM_HEADER_17_1  ACRX_T(/*MSGO*/"CF_ACTCUI_CATALOG_ITEM_HEADER_17_1")
#define CF_ACTC_CATALOG_ITEM_16_1           ACRX_T(/*MSGO*/"CF_ACTC_CATALOG_ITEM_16_1")
#define CF_ACTCUI_CATALOG_ITEM_HEADER_16_1  ACRX_T(/*MSGO*/"CF_ACTCUI_CATALOG_ITEM_HEADER_16_1")
#define CF_ACTCUI_CATALOG_ITEM              ACRX_T(/*MSGO*/"CF_ACTC_CATALOG_ITEM")
#define CF_ACTCUI_CATALOG_ITEM_HEADER       ACRX_T(/*MSGO*/"CF_ACTCUI_CATALOG_ITEM_HEADER")
#define CF_IDROP_ACTCUI_TOOL                ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_TOOL")
#define CF_IDROP_ACTCUI_PALETTE             ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_PALETTE")
#define CF_IDROP_ACTCUI_PACKAGE             ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_PACKAGE")
#define CF_IDROP_ACTCUI_CATEGORY            ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_CATEGORY")
#define CF_IDROP_ACTCUI_CATALOG             ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_CATALOG")
#define CF_IDROP_ACTCUI_STOCKTOOL           ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_STOCKTOOL")
#define CF_ACTCUI_TOOLBAR_ITEM              ACRX_T(/*MSGO*/"CF_ACTCUI_TOOLBAR_ITEM")

// AcTcUiPasteItems flags
//
#define ACTCUI_PI_SHOW_PROGRESS         (0x1 << 0)
#define ACTCUI_PI_USE_NEW_IDS           (0x1 << 1)
#define ACTCUI_PI_BREAK_SOURCE_LINK     (0x1 << 2)      // For internal use
#define ACTCUI_PI_NOTIFY_TOOLS          (0x1 << 3)      // For internal use


// Structure for drag and drop header information
//
typedef struct ACTCUI_DRAG_HEADER
{
    DWORD               mdwDragFormat;      // Dragged object: ACTCUIDRAGFORMATCUSTOM, etc.
#ifdef _ADESK_WINDOWS_
    CLIPFORMAT          mcfClipFormat;      // Clipformat: CF_ACTC_CATALOG_ITEM, etc.
#endif
    BOOL                mbAutoCADSource;    // TRUE if source is AutoCAD
    DWORD               mdwSourceProcessId; // Source process ID
    GUID                mRootId;            // Root id of the catalog items being dragged
    GUID                mParentId;          // Parent id of the catalog items being dragged
    BOOL                mbReadOnlySource;   // True if source is read-only
    int                 mnCount;            // Number of items being dragged
    int                 mnStockTools;       // Number of stock tool items being dragged
    DWORD               mdwItemTypes;       // Item types being dragged
} ACTCUI_DRAG_HEADER;

ACTCUI_PORT void AcTcUiInitialize();
ACTCUI_PORT CAcTcUiManager* AcTcUiGetManager(void);

#ifdef _ADESK_WINDOWS_
ACTCUI_PORT BOOL        AcTcUiCopyItems     (COleDataSource* pDataSource,
                                             const AcTcCatalogItemArray* pItems,
                                             BOOL bAutoCADSource);
ACTCUI_PORT BOOL        AcTcUiGetDragInfo   (IDataObject* pDataObject,
                                             ACTCUI_DRAG_HEADER* pHeader);
ACTCUI_PORT BOOL        AcTcUiPasteItems    (IDataObject* pDataObject,
                                             AcTcCatalogItemArray* pItems,
                                             AcTcCatalogItemArray* pStockTools,
                                             DWORD dwFlag = ACTCUI_PI_SHOW_PROGRESS);
ACTCUI_PORT CAcTcUiToolPaletteSet* AcTcUiGetToolPaletteWindow(void);
ACTCUI_PORT BOOL        AcTcUiFilterShapesDialog(AcTcCatalogItem* pPackage,
                                             AcTcCatalogItemArray* pActiveShapes,
                                             AcTcTool*& pCurrentShape,
                                             CWnd* pParentWnd);
#endif //_ADESK_WINDOWS_
#endif //__ACTCUI_H__
