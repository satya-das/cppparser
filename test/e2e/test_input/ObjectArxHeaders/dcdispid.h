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
// dcdispid.h : DISP ids for Design Explorer API
//
#ifndef DCDISPID_H
#define DCDISPID_H

#define ACDC_MAKE_DISPID(ID)    (ID + 100)

// IAcDcContentBrowser methods
#define DISPID_IAcDcContentBrowser_AddPaletteItem           ACDC_MAKE_DISPID(1)
#define DISPID_IAcDcContentBrowser_AddNavigatorNode         ACDC_MAKE_DISPID(2)
#define DISPID_IAcDcContentBrowser_GetDCFrameWindow         ACDC_MAKE_DISPID(3)
#define DISPID_IAcDcContentBrowser_SetItemDescription       ACDC_MAKE_DISPID(4)
#define DISPID_IAcDcContentBrowser_SetPaletteImageList      ACDC_MAKE_DISPID(5)
#define DISPID_IAcDcContentBrowser_SetNavigatorImageList    ACDC_MAKE_DISPID(6)
#define DISPID_IAcDcContentBrowser_SetPaletteMultiSelect    ACDC_MAKE_DISPID(7)
#define DISPID_IAcDcContentBrowser_InsertPaletteColumn      ACDC_MAKE_DISPID(8)
#define DISPID_IAcDcContentBrowser_DeleteAllPaletteItems    ACDC_MAKE_DISPID(9)
#define DISPID_IAcDcContentBrowser_GetSelectedNavNodeText   ACDC_MAKE_DISPID(10)
#define DISPID_IAcDcContentBrowser_GetCurrentViewMode       ACDC_MAKE_DISPID(11)
#define DISPID_IAcDcContentBrowser_SetPaletteSubItem        ACDC_MAKE_DISPID(12)
#define DISPID_IAcDcContentBrowser_SortPaletteItems         ACDC_MAKE_DISPID(13)
#define DISPID_IAcDcContentBrowser_RestorePaletteSelection  ACDC_MAKE_DISPID(14)
#define DISPID_IAcDcContentBrowser_GetDCStatusBar           ACDC_MAKE_DISPID(15)
#define DISPID_IAcDcContentBrowser_GetPaneInfo              ACDC_MAKE_DISPID(16)
#define DISPID_IAcDcContentBrowser_SetPaletteViewType       ACDC_MAKE_DISPID(17)
#define DISPID_IAcDcContentBrowser_NavigateTo               ACDC_MAKE_DISPID(18)

// IAcDcContentView methods
#define DISPID_IAcDcContentView_Initialize                  ACDC_MAKE_DISPID(101)
#define DISPID_IAcDcContentView_SetImageLists               ACDC_MAKE_DISPID(102)
#define DISPID_IAcDcContentView_Refresh                     ACDC_MAKE_DISPID(103)
#define DISPID_IAcDcContentView_NavigatorNodeExpanding      ACDC_MAKE_DISPID(104)
#define DISPID_IAcDcContentView_NavigatorNodeCollapsing     ACDC_MAKE_DISPID(105)
#define DISPID_IAcDcContentView_NavigatorNodeClick          ACDC_MAKE_DISPID(106)
#define DISPID_IAcDcContentView_NavigatorMouseUp            ACDC_MAKE_DISPID(107)
#define DISPID_IAcDcContentView_PaletteItemClick            ACDC_MAKE_DISPID(108)
#define DISPID_IAcDcContentView_PaletteItemDblClick         ACDC_MAKE_DISPID(109)
#define DISPID_IAcDcContentView_PaletteColumnClick          ACDC_MAKE_DISPID(110)
#define DISPID_IAcDcContentView_PaletteMouseUp              ACDC_MAKE_DISPID(111)
#define DISPID_IAcDcContentView_PaletteMouseDown            ACDC_MAKE_DISPID(112)
#define DISPID_IAcDcContentView_RenderPreviewWindow         ACDC_MAKE_DISPID(113)
#define DISPID_IAcDcContentView_PreviewMouseUp              ACDC_MAKE_DISPID(114)
#define DISPID_IAcDcContentView_PaletteBeginDrag            ACDC_MAKE_DISPID(115)
#define DISPID_IAcDcContentView_ReleaseBrowser              ACDC_MAKE_DISPID(116)
#define DISPID_IAcDcContentView_QueryContextMenu            ACDC_MAKE_DISPID(117)
#define DISPID_IAcDcContentView_InvokeCommand               ACDC_MAKE_DISPID(118)
#define DISPID_IAcDcContentView_IsExpandable                ACDC_MAKE_DISPID(119)
#define DISPID_IAcDcContentView_GetLargeIcon                ACDC_MAKE_DISPID(120)
#define DISPID_IAcDcContentView_GetSmallImageListForContent ACDC_MAKE_DISPID(121)
#define DISPID_IAcDcContentView_GetLargeImageListForContent ACDC_MAKE_DISPID(122)
#define DISPID_IAcDcContentView_GetCommandString            ACDC_MAKE_DISPID(123)
#define DISPID_IAcDcContentView_DeleteItemData              ACDC_MAKE_DISPID(124)


#endif // DCDISPID_H
