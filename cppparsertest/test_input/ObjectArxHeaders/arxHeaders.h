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
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//----- This file is preprocessor symbol driven.
//----- Define:
//-----		_HLR_SUPPORT_ to include and import HLR API headers and libs in your project.
//-----		_BREP_SUPPORT_ to include and import BRep API headers and libs in your project.
//-----		_AMODELER_SUPPORT_ to include and import AModeler API headers and libs in your project.
//-----		_RENDER_SUPPORT_ to include and import Render API headers and libs in your project.
//-----		_ASE_SUPPORT_ to include and import ASI/ASE API headers and libs in your project.
//-----		_INC_LEAGACY_HEADERS_ to include R12 legacy headers in your project.

//-----------------------------------------------------------------------------
//----- Note libs must be included in the following order:
//----- RxApi.lib, AcDb20.lib, ...
//----- This headers file will make sure to set the order properly
#include "dbxHeaders.h"

//-----------------------------------------------------------------------------
#pragma pack (push, 8)
#pragma warning (disable: 4311 4312 4275)

//-----------------------------------------------------------------------------
#pragma comment (lib ,"acad.lib")
#pragma comment (lib ,"accore.lib") 
#ifdef _AFXEXT
	#pragma comment (lib ,"acui23.lib")
	#pragma comment (lib ,"adui23.lib")
	#pragma comment (lib ,"aNav.lib")
	#pragma comment (lib ,"AcTc.lib")
	#pragma comment (lib ,"AcTcUi.lib")
	#pragma comment (lib ,"AcFdUi.lib")
#endif // #ifdef _AFXEXT
#pragma comment (lib ,"AcFdEval.lib")
#ifdef _RENDER_SUPPORT_
	#pragma comment (lib, "avlib.lib")
#endif // _RENDER_SUPPORT_
#ifdef _ASE_SUPPORT_
#ifndef AC_FULL_DEBUG
	#pragma comment (lib ,"aseapi23.lib")
	#pragma comment (lib ,"asiapi23.lib")
#else
	#pragma comment (lib ,"aseapi23d.lib")
	#pragma comment (lib ,"asiapi23d.lib")
#endif
	#pragma comment (lib ,"userdata.lib")
#endif // _ASE_SUPPORT_

//----- AutoCAD editor API
#include "accmd.h"
#include "aced.h"		//----- Access to AutoCAD Editor-specific services.
#include "acdocman.h"
#include "actrans.h"
#include "acedsel.h"
#include "acedxref.h"
#include "lngtrans.h"	//----- Header for Long Transaction Manager.
#include "dbltrans.h"
#include "acaplmgr.h"
#include "acedinet.h"
#include "acedinpt.h"
#include "AcDblClkEdit.h"
#include "AcGradThumbEng.h"
//#include "subselect.h"

//----- AutoCAD Db sub-system specific
#include "dbjig.h"
#include "dbmatch.h"
#include "dbInterferencePE.h"
#include "dbosnap.h"

//----- AutoCAD ext.
#include "clipdata.h"	//----- Supports Clipboard and Drag and Drop Geometry from AutoCAD.

//----- AutoCAD Graphic System
#ifdef _AFXEXT
#include "gs.h"				//----- Graphics System Interface.
#endif // _AFXEXT
#include "AcGsManager.h"	//----- Interface of Exported AutoCAD-GS-ARX-DB glue code.

//----- Plot
#include "AcPl.h"
#include "AcPlDSDData.h"
#include "AcPlDSDEntry.h"
#include "AcPlHostAppServices.h"
#include "AcPlObject.h"
#include "AcPlPlotConfig.h"
#include "AcPlPlotConfigMgr.h"
#include "AcPlPlotEngine.h"
#include "AcPlPlotErrorHandler.h"
#include "AcPlPlotErrorHandlerLock.h"
#include "AcPlPlotFactory.h"
#include "AcPlPlotInfo.h"
#include "AcPlPlotInfoValidator.h"
#include "AcPlPlotLogger.h"
#include "AcPlPlotLoggingErrorHandler.h"
#include "AcPlPlotProgress.h"
#include "acplplotreactor.h"
#include "acplplotreactormgr.h"

//----- Publish API
#include "acpublishreactors.h"
#include "acpublishuireactors.h"

//----- Publish/Plot API for DWF
#include "acdmmapi.h"
#include "acdmmeplotproperties.h"
#include "acdmmeplotproperty.h"
#include "acdmmutils.h"

//----- Autodesk MFC Extensions
#ifdef _AFXEXT
#pragma warning (disable: 4275)
#include "adui.h"
#include "AcExtensionModule.h"
#include "aduiBaseDialog.h"
#include "aduiButton.h"
#include "aduiComboBox.h"
#include "aduiDialog.h"
#include "aduiDialogBar.h"
#include "aduiDialogWorksheet.h"
#include "aduiDock.h"
#include "aduiDropTarget.h"
#include "aduiEdit.h"
#include "aduiFileDialog.h"
#include "aduiHeaderCtrl.h"
#include "aduiListBox.h"
#include "aduiListCtrl.h"
#include "aduiMessage.h"
#include "aduiPalette.h"
#include "aduiPaletteSet.h"
#include "aduiPathname.h"
#include "aduiRegistryAccess.h"
#include "aduiTabChildDialog.h"
#include "aduiTabCtrl.h"
#include "aduiTabExtension.h"
#include "aduiTabMainDialog.h"
#include "aduiTextTip.h"
#include "aduiTheme.h"
#include "aduiThemeManager.h"
#include "aduiCoupledGroupCtrl.h"
#include "aduiGroupCtrl.h"
#include "aduipathenums.h"

//----- AutoCAD MFC Extensions
#include "acui.h"
#include "rxmfcapi.h"		//----- ARX MFC API.
#include "AcStatusBar.h"
#include "acuiButton.h"
#include "acuiComboBox.h"
#include "acuiDialog.h"
#include "acuiDialogWorksheet.h"
#include "acuidock.h"
#include "acuiEdit.h"
#include "acuiHeaderCtrl.h"
#include "acuiListBox.h"
#include "acuiListCtrl.h"
#include "acuiNavDialog.h"
#include "acuiPathname.h"
#include "acuiTabCtrl.h"

//----- AutoCAD navigation dialog
#include "aNav.h"
#include "aNavArray.h"
#include "aNavData.h"
#include "aNavDataArray.h"
#include "aNavDialog.h"
#include "aNavFilter.h"
#include "aNavFilterArray.h"
#include "aNavListCtrl.h"

//----- AutoCAD Tool Palette API
#include "AcTc.h"
#include "AcTcUiManager.h"
#include "AcTcUI.h"
#include "AcTcUiCatalogView.h"
#include "AcTcUiCatalogViewItem.h"
#include "AcTcUiPaletteView.h"
#include "AcTcUiToolPalette.h"
#include "AcTcUiToolPaletteSet.h"
#include "AcTcUiToolPaletteGroup.h"
#include "AcTcUiScheme.h"
#include "AcTc_i.h"		// AcTc_i.c
#include "dcdispid.h"

//- Field API
#include "AcFdUi.h"
#include "AcFdUiFieldDialog.h"
#include "AcFdUiFieldDialogHook.h"
#include "AcFdUiFieldFormatDialog.h"
#include "AcFdUiFieldFormatList.h"
#include "AcFdUiFieldManager.h"
#include "AcFdUiFieldOptionDialog.h"
#include "AcFdUtil.h"

#endif // _AFXEXT

//----- ADS
#include "adsdlg.h"
#include "adsrxdef.h"
#include "adslib.h"

//----- Utils
#include "acssgetfilter.h"
#include "acutasrt.h"
#include "arxEntryPoint.h"
#include "AcApDMgr.h"
#include "acprofile.h"

//----- AutoCAD COM extensions
#ifdef __ATLCOM_H__
#include "dynpropmgr.h"
#endif // __ATLCOM_H__

//----- Legacy headers
#ifdef _INC_LEAGACY_HEADERS_
#include "ol_errno.h"	//----- R12 ELP ERRNO CODES
#endif // _INC_LEAGACY_HEADERS_

//----- AutoCAD ASI/ASE extensions
#ifdef _ASE_SUPPORT_
#include "asisys.h"
#include "asiappl.h"
#include "csptypes.h"
#include "avoidtry.h"
#include "asiucode.h"
#include "asiconst.h"
#include "asisdata.h"
#include "asiclass.h"
#include "aseconst.h"
#include "aseclass.h"
#endif // _ASE_SUPPORT_

//----- Render
#ifdef _RENDER_SUPPORT_
#include "averror.h"
#include "avlib.h"
#endif // _RENDER_SUPPORT_

#pragma pack (pop)
