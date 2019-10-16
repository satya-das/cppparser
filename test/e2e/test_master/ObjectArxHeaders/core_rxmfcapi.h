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
// Name:    core_rxmfcapi.h
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_CORE_RXMFCAPI_H
#  define AD_CORE_RXMFCAPI_H	1
#  pragma  pack (push, 8)
#  include "AcCoreDefs.h"
#  include "AcHeapOpers.h"
class AcCommandToolTipInfo;
struct AcColorSettings
{
  DWORD dwGfxModelBkColor;
  DWORD dwGfxLayoutBkColor;
  DWORD dwPaperBkColor;
  DWORD dwParallelBkColor;
  DWORD dwBEditBkColor;
  DWORD dwCmdLineBkColor;
  DWORD dwPlotPrevBkColor;
  DWORD dwSkyGradientZenithColor;
  DWORD dwSkyGradientHorizonColor;
  DWORD dwGroundGradientOriginColor;
  DWORD dwGroundGradientHorizonColor;
  DWORD dwEarthGradientAzimuthColor;
  DWORD dwEarthGradientHorizonColor;
  DWORD dwModelCrossHairColor;
  DWORD dwLayoutCrossHairColor;
  DWORD dwParallelCrossHairColor;
  DWORD dwPerspectiveCrossHairColor;
  DWORD dwBEditCrossHairColor;
  DWORD dwParallelGridMajorLines;
  DWORD dwPerspectiveGridMajorLines;
  DWORD dwParallelGridMinorLines;
  DWORD dwPerspectiveGridMinorLines;
  DWORD dwParallelGridAxisLines;
  DWORD dwPerspectiveGridAxisLines;
  DWORD dwTextForeColor, dwTextBkColor;
  DWORD dwCmdLineForeColor;
  DWORD dwCmdLineTempPromptBkColor;
  DWORD dwCmdLineTempPromptTextColor;
  DWORD dwCmdLineCmdOptKeywordColor;
  DWORD dwCmdLineCmdOptBkColor;
  DWORD dwCmdLineCmdOptHighlightedColor;
  DWORD dwAutoTrackingVecColor;
  DWORD dwLayoutATrackVecColor;
  DWORD dwParallelATrackVecColor;
  DWORD dwPerspectiveATrackVecColor;
  DWORD dwBEditATrackVecColor;
  DWORD dwModelASnapMarkerColor;
  DWORD dwLayoutASnapMarkerColor;
  DWORD dwParallelASnapMarkerColor;
  DWORD dwPerspectiveASnapMarkerColor;
  DWORD dwBEditASnapMarkerColor;
  DWORD dwModelDftingTooltipColor;
  DWORD dwLayoutDftingTooltipColor;
  DWORD dwParallelDftingTooltipColor;
  DWORD dwPerspectiveDftingTooltipColor;
  DWORD dwBEditDftingTooltipColor;
  DWORD dwModelDftingTooltipBkColor;
  DWORD dwLayoutDftingTooltipBkColor;
  DWORD dwParallelDftingTooltipBkColor;
  DWORD dwPerspectiveDftingTooltipBkColor;
  DWORD dwBEditDftingTooltipBkColor;
  DWORD dwModelLightGlyphs;
  DWORD dwLayoutLightGlyphs;
  DWORD dwParallelLightGlyphs;
  DWORD dwPerspectiveLightGlyphs;
  DWORD dwBEditLightGlyphs;
  DWORD dwModelLightHotspot;
  DWORD dwLayoutLightHotspot;
  DWORD dwParallelLightHotspot;
  DWORD dwPerspectiveLightHotspot;
  DWORD dwBEditLightHotspot;
  DWORD dwModelLightFalloff;
  DWORD dwLayoutLightFalloff;
  DWORD dwParallelLightFalloff;
  DWORD dwPerspectiveLightFalloff;
  DWORD dwBEditLightFalloff;
  DWORD dwModelLightStartLimit;
  DWORD dwLayoutLightStartLimit;
  DWORD dwParallelLightStartLimit;
  DWORD dwPerspectiveLightStartLimit;
  DWORD dwBEditLightStartLimit;
  DWORD dwModelLightEndLimit;
  DWORD dwLayoutLightEndLimit;
  DWORD dwParallelLightEndLimit;
  DWORD dwPerspectiveLightEndLimit;
  DWORD dwBEditLightEndLimit;
  DWORD dwModelCameraGlyphs;
  DWORD dwLayoutCameraGlyphs;
  DWORD dwParallelCameraGlyphs;
  DWORD dwPerspectiveCameraGlyphs;
  DWORD dwModelCameraFrustrum;
  DWORD dwLayoutCameraFrustrum;
  DWORD dwParallelCameraFrustrum;
  DWORD dwPerspectiveCameraFrustrum;
  DWORD dwModelCameraClipping;
  DWORD dwLayoutCameraClipping;
  DWORD dwParallelCameraClipping;
  DWORD dwPerspectiveCameraClipping;
  int nModelCrosshairUseTintXYZ;
  int nLayoutCrosshairUseTintXYZ;
  int nParallelCrosshairUseTintXYZ;
  int nPerspectiveCrosshairUseTintXYZ;
  int nBEditCrossHairUseTintXYZ;
  int nModelATrackVecUseTintXYZ;
  int nLayoutATrackVecUseTintXYZ;
  int nParallelATrackVecUseTintXYZ;
  int nPerspectiveATrackVecUseTintXYZ;
  int nBEditATrackVecUseTintXYZ;
  int nModelDftingTooltipBkUseTintXYZ;
  int nLayoutDftingTooltipBkUseTintXYZ;
  int nParallelDftingTooltipBkUseTintXYZ;
  int nPerspectiveDftingTooltipBkUseTintXYZ;
  int nBEditDftingTooltipBkUseTintXYZ;
  int nParallelGridMajorLineTintXYZ;
  int nPerspectiveGridMajorLineTintXYZ;
  int nParallelGridMinorLineTintXYZ;
  int nPerspectiveGridMinorLineTintXYZ;
  int nParallelGridAxisLineTintXYZ;
  int nPerspectiveGridAxisLineTintXYZ;
};
ACCORE_PORT bool acedGetCurrentColors(AcColorSettings* pColorSettings);
ACCORE_PORT bool acedSetCurrentColors(AcColorSettings* pColorSettings);
ACCORE_PORT bool acedGetSystemColors(AcColorSettings* pColorSettings);
struct AcColorSettingsEx
{
  DWORD dwModelLightWeb;
  DWORD dwLayoutLightWeb;
  DWORD dwParallelLightWeb;
  DWORD dwPerspectiveLightWeb;
  DWORD dwBEditLightWeb;
  DWORD dwModelLightWebMissingFile;
  DWORD dwLayoutLightWebMissingFile;
  DWORD dwParallelLightWebMissingFile;
  DWORD dwPerspectiveLightWebMissingFile;
  DWORD dwBEditLightWebMissingFile;
  DWORD dwModelLightWebShape;
  DWORD dwLayoutLightWebShape;
  DWORD dwParallelLightWebShape;
  DWORD dwPerspectiveLightWebShape;
  DWORD dwBEditLightWebShape;
  DWORD dwModelLightWebLuxAtDist;
  DWORD dwLayoutLightWebLuxAtDist;
  DWORD dwParallelLightWebLuxAtDist;
  DWORD dwPerspectiveLightWebLuxAtDist;
  DWORD dwBEditLightWebLuxAtDist;
  DWORD dwBEditUnconstrainedColor;
  DWORD dwBEditPartiallyConstrainedColor;
  DWORD dwBEditFullyConstrainedColor;
  DWORD dwBEditOverConstrainedColor;
};
ACCORE_PORT bool acedGetCurrentColorsEx(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx);
ACCORE_PORT bool acedSetCurrentColorsEx(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx);
ACCORE_PORT bool acedGetSystemColorsEx(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx);
struct AcColorSettingsEx2
{
  DWORD dw2DModelGridMajorLines;
  DWORD dwLayoutGridMajorLines;
  DWORD dwBEditGridMajorLines;
  DWORD dw2DModelGridMinorLines;
  DWORD dwLayoutGridMinorLines;
  DWORD dwBEditGridMinorLines;
  DWORD dw2DModelGridAxisLines;
  DWORD dwLayoutGridAxisLines;
  DWORD dwBEditGridAxisLines;
  DWORD dwModelDynamicDimensionLineColor;
  DWORD dwLayoutDynamicDimensionLineColor;
  DWORD dwParallelDynamicDimensionLineColor;
  DWORD dwPerspectiveDynamicDimensionLineColor;
  DWORD dwBEditDynamicDimensionLineColor;
  DWORD dwModelRubberBandLineColor;
  DWORD dwLayoutRubberBandLineColor;
  DWORD dwParallelRubberBandLineColor;
  DWORD dwPerspectiveRubberBandLineColor;
  DWORD dwBEditRubberBandLineColor;
  DWORD dwModelDftingTooltipContourColor;
  DWORD dwLayoutDftingTooltipContourColor;
  DWORD dwParallelDftingTooltipContourColor;
  DWORD dwPerspectiveDftingTooltipContourColor;
  DWORD dwBEditDftingTooltipContourColor;
  int n2DModelGridMajorLineTintXYZ;
  int nLayoutGridMajorLineTintXYZ;
  int nBEditGridMajorLineTintXYZ;
  int n2DModelGridMinorLineTintXYZ;
  int nLayoutGridMinorLineTintXYZ;
  int nBEditGridMinorLineTintXYZ;
  int n2DModelGridAxisLineTintXYZ;
  int nLayoutGridAxisLineTintXYZ;
  int nBEditGridAxisLineTintXYZ;
  DWORD dwControlVerticesHullColor;
};
ACCORE_PORT bool acedGetCurrentColorsEx2(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx, AcColorSettingsEx2* pColorSettingsEx2);
ACCORE_PORT bool acedSetCurrentColorsEx2(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx, AcColorSettingsEx2* pColorSettingsEx2);
ACCORE_PORT bool acedGetSystemColorsEx2(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx, AcColorSettingsEx2* pColorSettingsEx2);
struct AcColorSettingsEx3
{
  DWORD dwModel3dASnapMarkerColor;
  DWORD dwLayout3dASnapMarkerColor;
  DWORD dwParallel3dASnapMarkerColor;
  DWORD dwPerspective3dASnapMarkerColor;
  DWORD dwBEdit3dASnapMarkerColor;
  DWORD dw2DModelVportControl;
  DWORD dwParallelVportControl;
  DWORD dwPerspectiveVportControl;
};
ACCORE_PORT bool acedGetCurrentColorsEx3(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx, AcColorSettingsEx2* pColorSettingsEx2, AcColorSettingsEx3* pColorSettingsEx3);
ACCORE_PORT bool acedSetCurrentColorsEx3(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx, AcColorSettingsEx2* pColorSettingsEx2, AcColorSettingsEx3* pColorSettingsEx3);
ACCORE_PORT bool acedGetSystemColorsEx3(AcColorSettings* pColorSettings, AcColorSettingsEx* pColorSettingsEx, AcColorSettingsEx2* pColorSettingsEx2, AcColorSettingsEx3* pColorSettingsEx3);
typedef double acedDwgPoint[3];
#  ifndef _ADESK_CROSS_PLATFORM_
ACCORE_PORT void acedCoordFromPixelToWorld(const CPoint& ptIn, acedDwgPoint ptOut);
ACCORE_PORT bool acedCoordFromPixelToWorld(int windnum, CPoint ptIn, acedDwgPoint ptOut);
ACCORE_PORT bool acedCoordFromWorldToPixel(int windnum, const acedDwgPoint ptIn, CPoint& ptOut);
#  endif
int acedSetStatusBarProgressMeter(const ACHAR* pszLabel, int nMinPos, int nMaxPos);
int acedSetStatusBarProgressMeterPos(int nPos);
void acedRestoreStatusBar();
int acedGetWinNum(int ptx, int pty);
typedef void (*AcedWatchWinMsgFn) (const MSG*);
typedef bool (*AcedFilterWinMsgFn) (MSG*);
typedef void (*AcedOnIdleMsgFn) ();
typedef void (*AcedOnModalFn) (bool bModal);
ACCORE_PORT bool acedRegisterFilterWinMsg(const AcedFilterWinMsgFn pfn);
ACCORE_PORT bool acedRemoveFilterWinMsg(const AcedFilterWinMsgFn pfn);
ACCORE_PORT bool acedRegisterWatchWinMsg(const AcedWatchWinMsgFn pfn);
ACCORE_PORT bool acedRemoveWatchWinMsg(const AcedWatchWinMsgFn pfn);
ACCORE_PORT bool acedRegisterOnIdleWinMsg(const AcedOnIdleMsgFn pfn);
ACCORE_PORT bool acedRemoveOnIdleWinMsg(const AcedOnIdleMsgFn pfn);
ACCORE_PORT bool acedRegisterOnModal(const AcedOnModalFn pfn);
ACCORE_PORT bool acedRemoveOnModal(const AcedOnModalFn pfn);
typedef void (*AcedRunLoopFn) (void* pContext);
typedef long long TaskId;
ACCORE_PORT TaskId acedExecuteOnMainThread(const AcedRunLoopFn pfn, void* pContext, bool bWaitUntilDone = false);
class IAcEdRunLoopTask : public AcHeapOperators
{
public:
  virtual ~IAcEdRunLoopTask()
  {
  }
  virtual void execute() = 0;
};
ACCORE_PORT TaskId acedExecuteOnMainThread(IAcEdRunLoopTask* pTask, bool bWaitUntilDone = false);
ACCORE_PORT void acedRemoveRunLoopTask(TaskId taskId);
ACCORE_PORT HINSTANCE acedGetAcadResourceInstance();
typedef HBITMAP (*AcedCommandBitmapQueryFn) (const wchar_t* cmdName, const COLORREF& backgroundColor);
ACCORE_PORT bool acedRemoveCommandBitmapQuery(const AcedCommandBitmapQueryFn pfn);
ACCORE_PORT bool acedRegisterCommandBitmapQuery(const AcedCommandBitmapQueryFn pfn);
ACCORE_PORT HBITMAP acedGetBitmapForCommand(const wchar_t* cmdName, const COLORREF& backgroundColor);
ACCORE_PORT HBITMAP acedGetCachedBitmapForCommand(const wchar_t* cmdName, const COLORREF& backgroundColor);
ACCORE_PORT bool acedGetToolTipInfoForCommand(const ACHAR* cmdName, AcCommandToolTipInfo* pInfo);
class AcApStatusBar;
ACCORE_PORT AcApStatusBar* acedGetApplicationStatusBar();
ACCORE_PORT bool acedDrawingStatusBarsVisible();
ACCORE_PORT bool acedIsInputPending();
#  pragma  pack (pop)
#endif
