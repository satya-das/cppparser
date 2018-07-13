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
// Name:    ClipData.h
//
// Remarks: Supports Clipboard and Drag and Drop Geometry from AutoCAD
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _CLIPDATA_H
#define _CLIPDATA_H

#pragma pack (push, 8)

#include "accoredefs.h"
#include "AdAChar.h"

enum eClipInfoFlags {
    kbDragGeometry  = 0x01,
};

enum eXrefType {
    kXrefTypeAttach     = 1,
    kXrefTypeOverlay    = 2
};

enum eExpandedClipDataTypes {
    kDcPlotStyles       = 1,
    kDcXrefs            = 2,
    kDcLayouts          = 3,
    kDcBlocks           = 4,
    kDcLayers           = 5,
    kDcDrawings         = 6,
    kDcLinetypes        = 7,
    kDcTextStyles       = 8,
    kDcDimStyles        = 9,
    kDcBlocksWithAttdef = 10,
//#ifdef ADCHATCH
    kDcHatches          = 11,
//#endif
    kTpXrefs            = 12,
    kTpImages           = 13,
    kTpTable            = 14,
    kDcTableStyles      = 15, 
    kDcMultileaderStyles = 16,
    kDcVisualStyles      = 17,
    kDcSectionViewStyles = 18,
    kDcDetailViewStyles  = 19,
};

const int nBlockFileSize = 260;
const int nSignatureSize = 4;

// Clipboard and drag and drop information stored in the format
// CAcadDoc::m_cfPrivate ("AutoCAD.r15").
//
typedef struct tagClipboardInfo {
    ACHAR        szTempFile[nBlockFileSize];     // block temp file name
    ACHAR        szSourceFile[nBlockFileSize];   // file name of drawing from which selection was made
    ACHAR        szSignature[nSignatureSize];   // szClipSignature
    int         nFlags;                         // kbDragGeometry: dragging geometry from AutoCAD?
    AcGePoint3d dptInsert;                      // original world coordinate of insertion point
    RECT        rectGDI;                        // GDI coord bounding rectangle of sset
    void*       mpView;                         // Used to verify that this object was created in this view (HWND*)
    DWORD       m_dwThreadId;                   // AutoCAD thread that created this DataObject
    int         nLen;                           // Length of next segment of data, if any, starting with chData
    int         nType;                          // Type of data, if any (eExpandedClipDataTypes)
    ACHAR        chData[1];                      // Start of data, if any.
} ClipboardInfo;

#define szClipSignature ACRX_T(/*MSG0*/"R15")

ACCORE_PORT const ACHAR* acedClipFormatName();

#pragma pack (pop)

#endif