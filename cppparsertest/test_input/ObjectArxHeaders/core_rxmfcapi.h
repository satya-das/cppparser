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
// Name:    core_rxmfcapi.h
//
//////////////////////////////////////////////////////////////////////////////

#ifndef AD_CORE_RXMFCAPI_H
#define AD_CORE_RXMFCAPI_H 1

#pragma pack (push, 8)

#include "AcCoreDefs.h"
#include "AcHeapOpers.h"

class AcCommandToolTipInfo;

struct AcColorSettings {

    /* Solid background color for various contexts */
    DWORD dwGfxModelBkColor;    
    DWORD dwGfxLayoutBkColor;
    DWORD dwPaperBkColor;
    DWORD dwParallelBkColor;
    DWORD dwBEditBkColor;
    DWORD dwCmdLineBkColor;
    DWORD dwPlotPrevBkColor;

    /* Background color for 3D perspective projection */
    DWORD dwSkyGradientZenithColor;
    DWORD dwSkyGradientHorizonColor;
    DWORD dwGroundGradientOriginColor;
    DWORD dwGroundGradientHorizonColor;
    DWORD dwEarthGradientAzimuthColor; 
    DWORD dwEarthGradientHorizonColor;

    /* Crosshair color for various contexts */
    DWORD dwModelCrossHairColor;
    DWORD dwLayoutCrossHairColor;
    DWORD dwParallelCrossHairColor;
    DWORD dwPerspectiveCrossHairColor;
    DWORD dwBEditCrossHairColor;

    /* Ground plane grid major lines for various contexts */
    DWORD dwParallelGridMajorLines;
    DWORD dwPerspectiveGridMajorLines;

    /* Ground plane grid minor lines for various contexts */
    DWORD dwParallelGridMinorLines;
    DWORD dwPerspectiveGridMinorLines;

    /* Ground plane grid axis lines for various contexts */
    DWORD dwParallelGridAxisLines;
    DWORD dwPerspectiveGridAxisLines;

    /* Text window color */
    DWORD dwTextForeColor, dwTextBkColor;

    /* Command line text color */
    DWORD dwCmdLineForeColor;
    DWORD dwCmdLineTempPromptBkColor;
    DWORD dwCmdLineTempPromptTextColor;
    DWORD dwCmdLineCmdOptKeywordColor;
    DWORD dwCmdLineCmdOptBkColor;
    DWORD dwCmdLineCmdOptHighlightedColor;

    /* AutoTrack vector color for various contexts */
    // Note: dwAutoTrackingVecColor indicates autotrack vector color in model space.
    // We didn't change its name to dwModelATrackVecColor because that might break
    // existing arx app.
    DWORD dwAutoTrackingVecColor;
    DWORD dwLayoutATrackVecColor;
    DWORD dwParallelATrackVecColor;
    DWORD dwPerspectiveATrackVecColor;
    DWORD dwBEditATrackVecColor;

    /* Autosnap Marker color for various contexts */
    DWORD dwModelASnapMarkerColor;
    DWORD dwLayoutASnapMarkerColor;
    DWORD dwParallelASnapMarkerColor;
    DWORD dwPerspectiveASnapMarkerColor;
    DWORD dwBEditASnapMarkerColor;
    
    /* Drafting Tool tip color for various contexts */
    DWORD dwModelDftingTooltipColor;
    DWORD dwLayoutDftingTooltipColor;
    DWORD dwParallelDftingTooltipColor;
    DWORD dwPerspectiveDftingTooltipColor;
    DWORD dwBEditDftingTooltipColor;
        
    /* Drafting Tool tip background color for various contexts */    
    DWORD dwModelDftingTooltipBkColor;
    DWORD dwLayoutDftingTooltipBkColor;
    DWORD dwParallelDftingTooltipBkColor;
    DWORD dwPerspectiveDftingTooltipBkColor;
    DWORD dwBEditDftingTooltipBkColor;

    /* Light glyphs color for various contexts */
    DWORD dwModelLightGlyphs;
    DWORD dwLayoutLightGlyphs;
    DWORD dwParallelLightGlyphs;
    DWORD dwPerspectiveLightGlyphs;
    DWORD dwBEditLightGlyphs;

    /* Light Hotspot color for various contexts */
    DWORD dwModelLightHotspot;
    DWORD dwLayoutLightHotspot;
    DWORD dwParallelLightHotspot;
    DWORD dwPerspectiveLightHotspot;
    DWORD dwBEditLightHotspot;

    /* Light Falloff color for various contexts */
    DWORD dwModelLightFalloff;
    DWORD dwLayoutLightFalloff;
    DWORD dwParallelLightFalloff;
    DWORD dwPerspectiveLightFalloff;
    DWORD dwBEditLightFalloff;

    /* Light start limit color for various contexts */
    DWORD dwModelLightStartLimit;
    DWORD dwLayoutLightStartLimit;
    DWORD dwParallelLightStartLimit;
    DWORD dwPerspectiveLightStartLimit;
    DWORD dwBEditLightStartLimit;

    /* Light end limit color for various contexts */
    DWORD dwModelLightEndLimit;
    DWORD dwLayoutLightEndLimit;
    DWORD dwParallelLightEndLimit;
    DWORD dwPerspectiveLightEndLimit;
    DWORD dwBEditLightEndLimit;

    /* Camera glyphs color for various contexts */
    DWORD dwModelCameraGlyphs;
    DWORD dwLayoutCameraGlyphs;
    DWORD dwParallelCameraGlyphs;
    DWORD dwPerspectiveCameraGlyphs;

    /* Camera frustrum plane color for various contexts */
    DWORD dwModelCameraFrustrum;
    DWORD dwLayoutCameraFrustrum;
    DWORD dwParallelCameraFrustrum;
    DWORD dwPerspectiveCameraFrustrum;

    /* Camera clipping plane color for various contexts */
    DWORD dwModelCameraClipping;
    DWORD dwLayoutCameraClipping;
    DWORD dwParallelCameraClipping;
    DWORD dwPerspectiveCameraClipping;

    /* Flags - set if true */

    /* Flags for use tint X, Y, Z for crosshair */
    int nModelCrosshairUseTintXYZ;
    int nLayoutCrosshairUseTintXYZ;
    int nParallelCrosshairUseTintXYZ;
    int nPerspectiveCrosshairUseTintXYZ;
    int nBEditCrossHairUseTintXYZ;

    /* Flags for use tint X, Y, Z for AutoTrack Vector */
    int nModelATrackVecUseTintXYZ;
    int nLayoutATrackVecUseTintXYZ;
    int nParallelATrackVecUseTintXYZ;
    int nPerspectiveATrackVecUseTintXYZ;
    int nBEditATrackVecUseTintXYZ;

    /* Flags for use tint X, Y, Z for Drafting Tooltip Bk tint */
    int nModelDftingTooltipBkUseTintXYZ;
    int nLayoutDftingTooltipBkUseTintXYZ;
    int nParallelDftingTooltipBkUseTintXYZ;
    int nPerspectiveDftingTooltipBkUseTintXYZ;
    int nBEditDftingTooltipBkUseTintXYZ;

    /* Flags for use tint X, Y, Z for Ground plane grid major lines */
    int nParallelGridMajorLineTintXYZ;
    int nPerspectiveGridMajorLineTintXYZ;

    /* Flags for use tint X, Y, Z for Ground plane grid minor lines */
    int nParallelGridMinorLineTintXYZ;
    int nPerspectiveGridMinorLineTintXYZ;

    /* Flags for use tint X, Y, Z for Ground plane grid axis lines */
    int nParallelGridAxisLineTintXYZ;
    int nPerspectiveGridAxisLineTintXYZ;

};

// AutoCAD windows' colors
ACCORE_PORT bool acedGetCurrentColors(AcColorSettings* pColorSettings);
ACCORE_PORT bool acedSetCurrentColors(AcColorSettings* pColorSettings);
ACCORE_PORT bool acedGetSystemColors(AcColorSettings* pColorSettings);

// More color settings.
struct AcColorSettingsEx
{
    // Light Web color for various contexts 
    DWORD dwModelLightWeb;
    DWORD dwLayoutLightWeb;
    DWORD dwParallelLightWeb;
    DWORD dwPerspectiveLightWeb;
    DWORD dwBEditLightWeb;

    // Light Web(missingfile) color for various contexts
    DWORD dwModelLightWebMissingFile;
    DWORD dwLayoutLightWebMissingFile;
    DWORD dwParallelLightWebMissingFile;
    DWORD dwPerspectiveLightWebMissingFile;
    DWORD dwBEditLightWebMissingFile;

    // Light Web shape(extend source) color for various contexts
    DWORD dwModelLightWebShape;
    DWORD dwLayoutLightWebShape;
    DWORD dwParallelLightWebShape;
    DWORD dwPerspectiveLightWebShape;
    DWORD dwBEditLightWebShape;

    // Light Web lux at distance color for various contexts
    DWORD dwModelLightWebLuxAtDist;
    DWORD dwLayoutLightWebLuxAtDist;
    DWORD dwParallelLightWebLuxAtDist;
    DWORD dwPerspectiveLightWebLuxAtDist;
    DWORD dwBEditLightWebLuxAtDist;

    /* Block editor constraints colors */
    DWORD dwBEditUnconstrainedColor;
    DWORD dwBEditPartiallyConstrainedColor;
    DWORD dwBEditFullyConstrainedColor;
    DWORD dwBEditOverConstrainedColor;
};

// AutoCAD windows' colors
ACCORE_PORT bool acedGetCurrentColorsEx(AcColorSettings* pColorSettings, 
                            AcColorSettingsEx* pColorSettingsEx);

ACCORE_PORT bool acedSetCurrentColorsEx(AcColorSettings* pColorSettings, 
                            AcColorSettingsEx* pColorSettingsEx);

ACCORE_PORT bool acedGetSystemColorsEx(AcColorSettings* pColorSettings, 
                           AcColorSettingsEx* pColorSettingsEx);


// More and More color settings.
struct AcColorSettingsEx2
{
    /* Ground plane grid major lines for various contexts */
    DWORD dw2DModelGridMajorLines;
    DWORD dwLayoutGridMajorLines;
    DWORD dwBEditGridMajorLines;

    /* Ground plane grid minor lines for various contexts */
    DWORD dw2DModelGridMinorLines;
    DWORD dwLayoutGridMinorLines;
    DWORD dwBEditGridMinorLines;

    /* Ground plane grid axis lines for various contexts */
    DWORD dw2DModelGridAxisLines;
    DWORD dwLayoutGridAxisLines;
    DWORD dwBEditGridAxisLines;

    /* Dynamic Dimension Line color for various contexts */
    DWORD dwModelDynamicDimensionLineColor;
    DWORD dwLayoutDynamicDimensionLineColor;
    DWORD dwParallelDynamicDimensionLineColor;
    DWORD dwPerspectiveDynamicDimensionLineColor;
    DWORD dwBEditDynamicDimensionLineColor;

    /* Rubber-band Line color for various contexts */
    DWORD dwModelRubberBandLineColor;
    DWORD dwLayoutRubberBandLineColor;
    DWORD dwParallelRubberBandLineColor;
    DWORD dwPerspectiveRubberBandLineColor;
    DWORD dwBEditRubberBandLineColor;

    /* Drafting Tool tip contour color for various contexts */
    DWORD dwModelDftingTooltipContourColor;
    DWORD dwLayoutDftingTooltipContourColor;
    DWORD dwParallelDftingTooltipContourColor;
    DWORD dwPerspectiveDftingTooltipContourColor;
    DWORD dwBEditDftingTooltipContourColor;

    /* Flags for use tint X, Y, Z for Ground plane grid major lines */
    int n2DModelGridMajorLineTintXYZ;
    int nLayoutGridMajorLineTintXYZ;
    int nBEditGridMajorLineTintXYZ;

    /* Flags for use tint X, Y, Z for Ground plane grid minor lines */
    int n2DModelGridMinorLineTintXYZ;
    int nLayoutGridMinorLineTintXYZ;
    int nBEditGridMinorLineTintXYZ;

    /* Flags for use tint X, Y, Z for Ground plane grid axis lines */
    int n2DModelGridAxisLineTintXYZ;
    int nLayoutGridAxisLineTintXYZ;
    int nBEditGridAxisLineTintXYZ;

    /* Control vertices hull color for various contexts */
    DWORD dwControlVerticesHullColor;

};

// AutoCAD windows' colors
ACCORE_PORT bool acedGetCurrentColorsEx2(AcColorSettings* pColorSettings, 
                             AcColorSettingsEx* pColorSettingsEx,
                             AcColorSettingsEx2* pColorSettingsEx2);

ACCORE_PORT bool acedSetCurrentColorsEx2(AcColorSettings* pColorSettings, 
                             AcColorSettingsEx* pColorSettingsEx,
                             AcColorSettingsEx2* pColorSettingsEx2);

ACCORE_PORT bool acedGetSystemColorsEx2(AcColorSettings* pColorSettings, 
                            AcColorSettingsEx* pColorSettingsEx,
                            AcColorSettingsEx2* pColorSettingsEx2);

// More, more and More color settings 
// AutoCAD 2012
struct AcColorSettingsEx3
{
    /* 3d autosnap Marker color for various contexts */
    DWORD dwModel3dASnapMarkerColor;
    DWORD dwLayout3dASnapMarkerColor;
    DWORD dwParallel3dASnapMarkerColor;
    DWORD dwPerspective3dASnapMarkerColor;
    DWORD dwBEdit3dASnapMarkerColor;

    /* Viewport control for various contexts */
    DWORD dw2DModelVportControl;
    DWORD dwParallelVportControl;
    DWORD dwPerspectiveVportControl;
};

ACCORE_PORT
bool acedGetCurrentColorsEx3(AcColorSettings* pColorSettings, 
                             AcColorSettingsEx* pColorSettingsEx,
                             AcColorSettingsEx2* pColorSettingsEx2,
                             AcColorSettingsEx3* pColorSettingsEx3);

ACCORE_PORT
bool acedSetCurrentColorsEx3(AcColorSettings* pColorSettings, 
                             AcColorSettingsEx* pColorSettingsEx,
                             AcColorSettingsEx2* pColorSettingsEx2,
                             AcColorSettingsEx3* pColorSettingsEx3);

ACCORE_PORT
bool acedGetSystemColorsEx3(AcColorSettings* pColorSettings, 
                            AcColorSettingsEx* pColorSettingsEx,
                            AcColorSettingsEx2* pColorSettingsEx2,
                            AcColorSettingsEx3* pColorSettingsEx3);


/* acedDwgPoint
* used in acedCoordinate function :
*/
typedef double acedDwgPoint[3];

// AutoCAD coordinates and viewports

#ifndef _ADESK_CROSS_PLATFORM_

/* acedCoordFromPixelToWorld
* Takes a coordinate in Window's coordinate (mouse coordinate)
* and converts it to current viewport world coordinate
*/
ACCORE_PORT void acedCoordFromPixelToWorld(const CPoint &ptIn, acedDwgPoint ptOut);

/* acedCoordFromPixelToWorld
* Takes a coordinate in Windows' coordinate (mouse coordinate) and
* a viewport number; and converts it to current viewport world coordinate
*/
ACCORE_PORT bool acedCoordFromPixelToWorld(int windnum, CPoint ptIn, acedDwgPoint ptOut);

/* acedCoordFromWorldToPixel
* Takes a coordinate in AutoCAD world coordinate and a viewport number; 
* and converts it to Windows' coordinate.
*/
ACCORE_PORT bool acedCoordFromWorldToPixel(int windnum, const acedDwgPoint ptIn, CPoint& ptOut);

#endif

// Progress Bar API

/* acedSetStatusBarProgressMeter
 * Creates a progress meter on AutoCAD status bar.
 * Returns 0 if it successfully creates the label and progress meter. 
 * Otherwise -1
 */
int acedSetStatusBarProgressMeter(const ACHAR* pszLabel, int nMinPos, 
                                  int nMaxPos);
/* acedSetStatusBarProgressMeter
 * Call this with a positive value within the range specified to set 
 * the current position of the status bar.  
 * Pass a negative number to add an amount to the current position (relative).
 */
int acedSetStatusBarProgressMeterPos(int nPos);

/* acedRestoreStatusBar
 * Resets AutoCAD status bar
 */
void acedRestoreStatusBar();

/* acedGetWinNum
 * Takes a Windows' client coordinate and return the viewport number where 
 * the point is on
 * Returns 0 for no viewport, 1 if tilemode is off.
 * It's used with acedCoordFromWorldToPixel/acedCoordFromPixelToWorld
 */
int acedGetWinNum(int ptx, int pty);


// Define callback function for apps that want windows messages
typedef void (* AcedWatchWinMsgFn)(const MSG*);
typedef bool (* AcedFilterWinMsgFn)(MSG*);
typedef void (* AcedOnIdleMsgFn) ();
typedef void (* AcedOnModalFn) (bool bModal);

// Windows messages hooks
/* Register a filter message hook into AutoCAD's Windows message loop.
 * The message passed to your application can be changed and can be blocked out.
 * If the function returns true, the message WON'T be passed to other hook 
 * functions or AutoCAD at all. The message is terminated.
 * Returns true if successfully registers the hook. Otherwise false.
 */
ACCORE_PORT bool acedRegisterFilterWinMsg(const AcedFilterWinMsgFn pfn);

/* acedRemoveFilterWinMsg
 * Takes a message hook function pointer and remove it 
 * Returns true if successfully registers the hook. Otherwise false.
 */
ACCORE_PORT bool acedRemoveFilterWinMsg(const AcedFilterWinMsgFn pfn);

/* acedRegisterWatchWinMsg
 * Register a hook function into AutoCAD message loop. 
 * The function can only look up AutoCAD's Windows message.
 * It can't  change or block message.
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
ACCORE_PORT bool acedRegisterWatchWinMsg(const AcedWatchWinMsgFn pfn);

/* acedRemoveWatchWinMsg
 * Takes a message hook function pointer and remove it 
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 * 
 */
ACCORE_PORT bool acedRemoveWatchWinMsg(const AcedWatchWinMsgFn pfn); 

/* acedRegisterOnIdleWinMsg
 * Register a hook function to be notified when AutoCAD is on idle 
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
ACCORE_PORT bool acedRegisterOnIdleWinMsg(const AcedOnIdleMsgFn pfn);

/* acedRemoveOnIdleWinMsg
 * Takes a message on idle hook function pointer and remove it 
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 * 
 */
ACCORE_PORT bool acedRemoveOnIdleWinMsg(const AcedOnIdleMsgFn pfn); 

/* acedRegisterOnModal
 * Register a hook function to be notified when AutoCAD displays a modal dialog.
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
ACCORE_PORT bool acedRegisterOnModal(const AcedOnModalFn pfn);

/* acedRemoveOnModal
 * Takes a hook function pointer and removes it
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 * 
 */
ACCORE_PORT bool acedRemoveOnModal(const AcedOnModalFn pfn); 


// Defines the callback function that needs to be executed on AutoCAD main thread. 
typedef void (*AcedRunLoopFn)(void* pContext);

// Defines the data type of the task id
typedef long long TaskId;

/* acedExecuteOnMainThread
 * Dispatches a function to be executed on AutoCAD main thread.
 *
 * Returns the task id if bWaitUntilDone == false. Otherwise, the return value is undefined.
 * The task id indicates the order in which the queued tasks will be executed.
 * Given two tasks, the task with the lower task id will be executed first.
 */
ACCORE_PORT TaskId acedExecuteOnMainThread(const AcedRunLoopFn pfn, void* pContext, bool bWaitUntilDone = false);

// Defines the base type IAcEdRunLoopTask for tasks that can be dispatched and executed on 
// AutoCAD main thread.
class IAcEdRunLoopTask : public AcHeapOperators
{
public:
    virtual ~IAcEdRunLoopTask() {}

    virtual void execute() = 0;
};

/* acedExecuteOnMainThread
 * Dispatches a task to be executed on AutoCAD main thread.
 * 
 * This function takes the ownership of the pTask instance, and deletes the instance
 * once the task has completed execution on main thread.
 *
 * Returns the task id if bWaitUntilDone = false. Otherwise, the return value is undefined.
 * The task id indicates the order in which the queued tasks will be executed.
 * Given two tasks, the task with the lower task id will be executed first.
 */
ACCORE_PORT TaskId acedExecuteOnMainThread(IAcEdRunLoopTask* pTask, bool bWaitUntilDone = false);


/* acedRemoveRunLoopTask
 * Removes a task that has been queued previously using any variant of the
 * acedExecuteOnMainThread() function.
 * 
 */
ACCORE_PORT void acedRemoveRunLoopTask(TaskId taskId);


/* acedGetAcadResourceInstance()
 * Returns the Instance of AutoCAD's resource
 */
ACCORE_PORT HINSTANCE acedGetAcadResourceInstance();

// Define callback function for apps that want bitmap query.
typedef HBITMAP (* AcedCommandBitmapQueryFn)(const wchar_t* cmdName, 
                                             const COLORREF& backgroundColor);

/* acedRemoveCommandBitmapQuery
 * Takes a bitmap query hook function pointer and remove it 
 * Returns TRUE if successfully removes the hook. Otherwise FALSE.
 * 
 */
ACCORE_PORT bool      acedRemoveCommandBitmapQuery   (const AcedCommandBitmapQueryFn pfn); 


/* acedRegisterCommandBitmapQuery
 * Register a bitmap query function to be notified when AutoCAD queries
 * for a bitmap for a given command.
 * Returns TRUE if successfully registers the hook. Otherwise FALSE.
 */
ACCORE_PORT bool      acedRegisterCommandBitmapQuery (const AcedCommandBitmapQueryFn pfn);


// Currently this is used to query bitmap associated with a command in the  AutoComplete 
// Suggestion List pop-up window. 
// 
// By default a bitmap/icon in the CUI menu macro can be associated with a command/sysvar.
// In the CUI dialog, the 'Command Display Name' property points to a command/sysvar name.
// This is how to link a bitmap to a command.
//
// It's recommended that the bitmap to command association is done thought CUI. If this is
// not possible or there is a need for override behavior, please use the callback function
// mentioned above. 
// Note that the name is all in Localized name.
ACCORE_PORT HBITMAP   acedGetBitmapForCommand        (const wchar_t* cmdName, 
                                                      const COLORREF& backgroundColor);

ACCORE_PORT HBITMAP   acedGetCachedBitmapForCommand  (const wchar_t* cmdName, 
                                                      const COLORREF& backgroundColor);

ACCORE_PORT bool acedGetToolTipInfoForCommand( const ACHAR* cmdName
                                             , AcCommandToolTipInfo* pInfo );

class AcApStatusBar;

/* acedGetApplicationStatusBar
* Returns the pointer to AutoCAD Application Status Bar.
*/
ACCORE_PORT
AcApStatusBar* acedGetApplicationStatusBar();

/* acedDrawingStatusBarsVisible
* Returns TRUE if the drawing status bar are visible
* in AutoCAD, otherwise FALSE.
*/
ACCORE_PORT bool acedDrawingStatusBarsVisible();

// This routine is exported primarily for use by AcUi. The routine is called
// from a dialog to determine if input is queued after an interactive command
// has been cancelled. Generally, if there's no input queued then the dialog
// will be restored, otherwise the dialog will terminate and allow the queued
// commands to be processed.
ACCORE_PORT bool acedIsInputPending();

#pragma pack (pop)

#endif // AD_CORE_RXMFCAPI_H
