//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ACED_H
#  define _ACED_H
#  include "adesk.h"
#  include "acadapidef.h"
#  include "rxevent.h"
#  include "ads.h"
#  pragma  pack (push, 8)
struct IDispatch;
class CAdUiPathname;
#  define ACED_SERVICES	ACRX_T("AcEdServices")
#  define ACED_EDITOR_OBJ	ACRX_T("AcEditor")
enum AcadContextMenuMode
{
  kDefault = 0,
  kEdit,
  kCommand,
  kHotGrip,
  kOsnap,
#  ifdef _ADESK_MAC_
  kCMPaperSpace,
#  endif
};
#  include "aced-xref.h"
enum undoSubcommandActivities
{
  kNone = 0,
  kOne = 1,
  kAll = 2
};
#  pragma  pack (pop)
#  include "accmd.h"
#  pragma  pack (push, 8)
struct AcEdCommandStruc;
class AcString;
class AcRxVariable;
class AcGiImageBGRA32;
class AcEdImpSysVarIterator;
ACAD_PORT bool acedCmdLookup2(const ACHAR* cmdStr, bool globalLookup, AcEdCommandStruc* retStruc, int sf = ACRX_CMD_DEFUN);
inline bool acedCmdLookup(const ACHAR* cmdStr, bool globalLookup, AcEdCommandStruc* retStruc, bool skipUndef = false)
{
  return ::acedCmdLookup2(cmdStr, globalLookup, retStruc, skipUndef ? (ACRX_CMD_DEFUN | ACRX_CMD_UNDEFINED) : ACRX_CMD_DEFUN);
}
ACAD_PORT int acedCmdUndefine(const ACHAR* cmdStr, int undefIt);
ACAD_PORT int acedPopCommandDirectory(const ACHAR* cmdDirName);
/// <summary>
///  Gets the global or local name of the innermost current command for the given document
/// </summary>
///
/// <param name="pDoc">
///  Pointer to the document whose command is to be queried.
/// </param>
///
/// <param name="sGlobalCmdName">
///  Reference to a string object which receives the command name.
/// </param>
///
/// <param name="bLocalized">
///  Selects the global command name if false, localized name if true.
/// </param>
///
/// <returns>
///  Returns Acad::eOk if successful, else eNullPtr or eInvalidInput on errors
/// </returns>
///
/// <remarks>
///  The overload taking an ACHAR*& pGlobalCmdName arg and no bLocalized arg is
///  is deprecated and will be removed in a future release
/// </remarks>
///
class AcApDocument;
ACAD_PORT Acad::ErrorStatus acedGetCommandForDocument(const AcApDocument* pDoc, AcString& sCmdName, bool bLocalized = false);
ACAD_PORT Acad::ErrorStatus acedGetCommandForDocument(const AcApDocument* pDoc, ACHAR*& pGlobalCmdName);
ACAD_PORT bool acedSetOLELock(int handle, int flags = 0);
ACAD_PORT bool acedClearOLELock(int handle);
ACAD_PORT void acedPostCommandPrompt();
Acad::ErrorStatus acedSyncFileOpen(const ACHAR* pszFileToOpen, const wchar_t* wszPassword = NULL);
Adesk::Boolean acedSetColorDialog(int& nColor, Adesk::Boolean bAllowMetaColor, int nCurLayerColor);
Adesk::Boolean acedSetColorDialogTrueColor(AcCmColor& color, Adesk::Boolean bAllowMetaColor, const AcCmColor& curLayerColor, AcCm::DialogTabs tabs = (AcCm::DialogTabs) (AcCm::kACITab | AcCm::kTrueColorTab | AcCm::kColorBookTab));
#  if  defined(_ADESK_WINDOWS_)
typedef void (ADESK_STDCALL *AcEdColorDialogCallbackFunction) (void* pCallbackData, const AcCmColor& newColor);
ACAD_PORT Adesk::Boolean acedSetColorDialogTrueColorWithCallback(AcCmColor& color, Adesk::Boolean bAllowMetaColor, const AcCmColor& curLayerColor, AcCm::DialogTabs tabs = (AcCm::DialogTabs) (AcCm::kACITab | AcCm::kTrueColorTab | AcCm::kColorBookTab), AcEdColorDialogCallbackFunction callback = NULL, void* pCallbackData = NULL);
#  endif
Adesk::Boolean acedSetColorPrompt(ACHAR* promptString, AcCmColor& color, Adesk::Boolean bAllowMetaColor);
Adesk::Boolean acedIsMenuGroupLoaded(const ACHAR* pszGroupName);
bool acedLoadPartialMenu(const wchar_t* pszMenuFile);
bool acedUnloadPartialMenu(const wchar_t* pszMenuFile);
void acedReloadMenus(bool bIncrementalReloading);
void acedSendModelessOperationStart(const ACHAR* strContext);
void acedSendModelessOperationEnded(const ACHAR* strContext);
void acedUpdateDisplay();
void acedUpdateDisplayPause(bool bEnable);
bool acedIsUpdateDisplayPaused(void);
Adesk::Boolean acedInitDialog(Adesk::Boolean useDialog = Adesk::kTrue);
/////////////////////////////////////////////////////////////////////////////
// This function sets a int variable in the current document establishing the 
// version of the command that will be run next.  The return value is the 
// old version value. Calling this method will no argument will initialize the
// value to 0, which indicates that no version has been established.
/////////////////////////////////////////////////////////////////////////////
Adesk::UInt8 acedInitCommandVersion(Adesk::UInt8 nVersion = 0);
/////////////////////////////////////////////////////////////////////////////
// This function is used to query the requested version of the command currently
// in progress.  It does this by querying the version set at this depth of 
// the command version stack.
/////////////////////////////////////////////////////////////////////////////
Adesk::UInt8 acedGetCommandVersion();
void acedDisableDefaultARXExceptionHandler(Adesk::Boolean disable = Adesk::kTrue);
Acad::ErrorStatus acedVportTableRecords2Vports();
Acad::ErrorStatus acedVports2VportTableRecords();
Acad::ErrorStatus acedVPLayer(const AcDbObjectId& vpId, const AcDbObjectIdArray& layerIds, AcDb::VpFreezeOps operation);
#  define acedServices	AcEdServices::cast(acrxServiceDictionary->at(ACED_SERVICES))
class AcEdCommand;
class AcEdServices : public AcRxService
{
public:
  ACRX_DECLARE_MEMBERS(AcEdServices);
  virtual AcEdCommand* newAcEdCommand(AcRxFunctionPtr cmdFcnAddr, Adesk::Int32 cmdFlags) const = 0;
};
class AcDbDatabase;
class AcEditorReactor : public AcRxEventReactor
{
public:
  ACRX_DECLARE_MEMBERS(AcEditorReactor);
  AcEditorReactor()
  {
  }
  virtual void unknownCommand(const ACHAR* cmdStr, AcDbVoidPtrArray* al);
  virtual void commandWillStart(const ACHAR* cmdStr);
  virtual void commandEnded(const ACHAR* cmdStr);
  virtual void commandCancelled(const ACHAR* cmdStr);
  virtual void commandFailed(const ACHAR* cmdStr);
  virtual void lispWillStart(const ACHAR* firstLine);
  virtual void lispEnded();
  virtual void lispCancelled();
  virtual void beginDxfIn(AcDbDatabase*) override;
  virtual void abortDxfIn(AcDbDatabase*) override;
  virtual void dxfInComplete(AcDbDatabase*) override;
  virtual void beginDxfOut(AcDbDatabase*) override;
  virtual void abortDxfOut(AcDbDatabase*) override;
  virtual void dxfOutComplete(AcDbDatabase*) override;
  ADESK_DEPRECATED virtual void beginDwgOpen(ACHAR*) final
  {
  }
  virtual void beginDwgOpen(const ACHAR*)
  {
  }
  virtual void endDwgOpen(const ACHAR* filename, AcDbDatabase* pDb);
  virtual void initialDwgFileOpenComplete(AcDbDatabase* pDwg) override;
  virtual void curDocOpenUpgraded(AcDbDatabase*, const CAdUiPathname&)
  {
  }
  virtual void curDocOpenDowngraded(AcDbDatabase*, const CAdUiPathname&)
  {
  }
  virtual void databaseConstructed(AcDbDatabase*) override;
  virtual void databaseToBeDestroyed(AcDbDatabase*) override;
  virtual void beginSave(AcDbDatabase*, const ACHAR* pIntendedName) override;
  virtual void saveComplete(AcDbDatabase*, const ACHAR* pActualName) override;
  virtual void abortSave(AcDbDatabase*) override;
  virtual void beginInsert(AcDbDatabase* pTo, const ACHAR* pBlockName, AcDbDatabase* pFrom) override;
  virtual void beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform, AcDbDatabase* pFrom) override;
  virtual void otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom) override;
  virtual void abortInsert(AcDbDatabase* pTo) override;
  virtual void endInsert(AcDbDatabase* pTo) override;
  virtual void wblockNotice(AcDbDatabase* pDb) override;
  virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, const AcGePoint3d*& insertionPoint) override;
  virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, AcDbObjectId blockId) override;
  virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom) override;
  virtual void otherWblock(AcDbDatabase* pTo, AcDbIdMapping&, AcDbDatabase* pFrom) override;
  virtual void abortWblock(AcDbDatabase* pTo) override;
  virtual void endWblock(AcDbDatabase* pTo) override;
  virtual void beginDeepClone(AcDbDatabase* pTo, AcDbIdMapping&) override;
  virtual void beginDeepCloneXlation(AcDbIdMapping&, Acad::ErrorStatus*) override;
  virtual void abortDeepClone(AcDbIdMapping&) override;
  virtual void endDeepClone(AcDbIdMapping&) override;
  virtual void sysVarChanged(const ACHAR* varName, Adesk::Boolean success);
  virtual void sysVarChanged(const ACHAR*, int) final
  {
  }
  virtual void sysVarWillChange(const ACHAR* varName);
  virtual void beginAttach(AcDbDatabase* pTo, const ACHAR*, AcDbDatabase* pFrom) override;
  virtual void otherAttach(AcDbDatabase* pTo, AcDbDatabase* pFrom) override;
  virtual void abortAttach(AcDbDatabase* pFrom) override;
  virtual void endAttach(AcDbDatabase* pTo) override;
  virtual void redirected(AcDbObjectId newId, AcDbObjectId oldId) override;
  virtual void comandeered(AcDbDatabase* pTo, AcDbObjectId id, AcDbDatabase* pFrom) override;
  virtual void beginRestore(AcDbDatabase* pTo, const ACHAR*, AcDbDatabase* pFrom) override;
  virtual void abortRestore(AcDbDatabase* pTo) override;
  virtual void endRestore(AcDbDatabase* pTo) override;
  virtual void xrefSubcommandBindItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId) override;
  virtual void xrefSubcommandAttachItem(AcDbDatabase* pHost, int activity, const ACHAR* pPath) override;
  virtual void xrefSubcommandOverlayItem(AcDbDatabase* pHost, int activity, const ACHAR* pPath) override;
  virtual void xrefSubcommandDetachItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId) override;
  virtual void xrefSubcommandPathItem(int activity, AcDbObjectId blockId, const ACHAR* pNewPath) override;
  virtual void xrefSubcommandReloadItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId) override;
  virtual void xrefSubcommandUnloadItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId) override;
  virtual void undoSubcommandAuto(int activity, Adesk::Boolean state);
  virtual void undoSubcommandAuto(int, int) final
  {
  }
  virtual void undoSubcommandControl(int activity, int option);
  virtual void undoSubcommandBegin(int activity);
  virtual void undoSubcommandEnd(int activity);
  virtual void undoSubcommandMark(int activity);
  virtual void undoSubcommandBack(int activity);
  virtual void undoSubcommandNumber(int activity, int num);
  virtual void pickfirstModified();
  virtual void layoutSwitched(const ACHAR* newLayoutName);
  virtual void layoutToBeSwitched(const ACHAR*, const ACHAR*)
  {
  }
  virtual void dwgViewResized(Adesk::LongPtr)
  {
  }
  virtual void fullRegenEnded(AcDbDatabase*, const AcDbIntArray&)
  {
  }
  virtual void docFrameMovedOrResized(Adesk::LongPtr hwndDocFrame, bool bMoved);
  virtual void mainFrameMovedOrResized(Adesk::LongPtr hwndMainFrame, bool bMoved);
  virtual void beginDoubleClick(const AcGePoint3d& clickPoint);
  virtual void beginRightClick(const AcGePoint3d& clickPoint);
  virtual void toolbarBitmapSizeWillChange(Adesk::Boolean bLarge);
  virtual void toolbarBitmapSizeChanged(Adesk::Boolean bLarge);
  virtual void toolbarBitmapSizeWillChange(int) final
  {
  }
  virtual void toolbarBitmapSizeChanged(int) final
  {
  }
  virtual void beginWblockObjects(AcDbDatabase* pFrom, AcDbIdMapping&) override;
  virtual void partialOpenNotice(AcDbDatabase* pDb) override;
  virtual void objectsLazyLoaded(const AcDbObjectIdArray& idArray);
  virtual void beginDocClose(AcDbDatabase*)
  {
  }
  virtual void docCloseAborted(AcDbDatabase*)
  {
  }
  virtual void docCloseWillStart(AcDbDatabase*)
  {
  }
  ADESK_DEPRECATED virtual void beginClose(AcDbDatabase*) final;
  virtual void beginCloseAll()
  {
  }
  virtual void beginQuit();
  virtual void quitAborted();
  virtual void quitWillStart();
  virtual void modelessOperationWillStart(const ACHAR* contextStr);
  virtual void modelessOperationEnded(const ACHAR* contextStr);
  virtual void cmdIUnkModified(const ACHAR* strCommand);
    /// <summary>
    ///
    ///  Sends notification on the start of an xref subcommand. The xref
    ///  subcommands are the ones in the following enum (aced.h):
    ///  
    ///     enum AcXrefSubCommand {
    ///                  kAttach,
    ///                  kBind,
    ///                  kDetach,
    ///                  kOverlay,
    ///                  kPath,
    ///                  kReload,
    ///                  kResolve,
    ///                  kUnload,
    ///                  kXBind
    ///     };
    ///
    ///   An application can veto the operation by returning a bad status,
    ///   e.g. Acad::eVetoed.
    ///
    ///   There are multiple output arguments, based on the subcommand.
    ///   Subcommands like attach have all the arguments provided.
    ///   Subcommands like Bind only supply the btrids.
    ///   
    ///   The rule for checking the output arguments is: Use the BtrIds first.
    ///   The other two arguments may be empty.
    ///   In subcommands like Path - the path in the Block Table Record could
    ///   differ from the one in the paths argument - in which case - both
    ///   could be used.
    ///
    /// </summary>
    ///
    /// <param name="subcmd">
    /// The subcommand which is about to start.
    /// </param>
    ///
    /// <param name="btrIds">
    /// The xref block table record ids. The primary output argument.
    /// </param>
    ///
    /// <param name="btrNames">
    ///  Xref Block Table Record names.
    /// </param>
    ///
    /// <param name="paths">
    /// The path strings for the subcommand, if applicable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. If the application return an
    /// error status, the subcommand will be vetoed.
    /// </returns>
    ///
    /// <remarks>
    ///  Though the btr names and path arguments seem redundant at times,
    ///  they can help applications avoid open for write/open for read conflicts
    ///  in case the subcommand already has the Block Table Record open.
    /// </remarks>
    ///
  virtual Acad::ErrorStatus xrefSubCommandStart(AcXrefSubCommand subcmd, const AcDbObjectIdArray& btrIds, const ACHAR* const * btrNames, const ACHAR* const * paths);
    /// <summary>
    /// Notification just before an Xref is locked via 
    /// AcEdXrefFileLock::lockFile().
    /// </summary>
    ///
    /// <param name = "btrId">
    /// The xref block table record id that is to be locked.
    /// </param>
    ///
  virtual void preXrefLockFile(AcDbObjectId btrId);
  virtual void viewChanged();
  virtual void fullRegenWillStart(AcDbDatabase*)
  {
  }
protected:
  Acad::ErrorStatus veto();
private:
  Adesk::UInt8 mVeto = 0;
  friend class AcEditorImp;
};
#  define AcEditorReactor2	AcEditorReactor
#  define AcEditorReactor3	AcEditorReactor
#  define acedEditor	AcEditor::cast(acrxSysRegistry()->at(ACED_EDITOR_OBJ))
class AcEditor : public AcRxEvent
{
public:
  ACRX_DECLARE_MEMBERS(AcEditor);
  virtual void addReactor(AcRxEventReactor* newObj) = 0;
  virtual void removeReactor(AcRxEventReactor* delObj) = 0;
};
class AcEdUIContext : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcEdUIContext);
  virtual void* getMenuContext(const AcRxClass*, const AcDbObjectIdArray&) = 0;
  virtual void* getMenuContext(const AcRxClass*, const AcDbObjectIdArray&, const AcArray<AcDbFullSubentPathArray, AcArrayObjectCopyReallocator<AcDbFullSubentPathArray> >& subentIds);
  virtual void onCommand(Adesk::UInt32) = 0;
  virtual void OnUpdateMenu();
};
Adesk::Boolean acedAddObjectContextMenu(AcRxClass* pClass, AcEdUIContext* pContext, const void* appId);
Adesk::Boolean acedRemoveObjectContextMenu(AcRxClass* pClass, AcEdUIContext* pContext);
Adesk::Boolean acedAddDefaultContextMenu(AcEdUIContext* pContext, const void* appId, const ACHAR* appName = NULL);
Adesk::Boolean acedRemoveDefaultContextMenu(AcEdUIContext* pContext);
bool acedSetCMBaseAlias(const wchar_t* strAlias, AcadContextMenuMode mode);
const wchar_t* acedGetCMBaseAlias(AcadContextMenuMode mode);
Acad::ErrorStatus acedMspace();
Acad::ErrorStatus acedPspace();
Acad::ErrorStatus acedSetCurrentVPort(int vpnumber);
Acad::ErrorStatus acedSetCurrentVPort(const AcDbViewport* pVp);
int acedIsDragging(void);
Acad::ErrorStatus acedSetCurrentView(AcDbViewTableRecord* pVwRec, AcDbViewport* pVP);
Acad::ErrorStatus acedRestoreCurrentView(const AcDbObjectId& namedViewId);
short acedGetCurVportCircleSides();
Acad::ErrorStatus acedSetCurVportCircleSides(short value);
void acedGetCurVportPixelToDisplay(double& xFactor, double& yFactor);
void acedGetCurVportScreenToDisplay(double& xFactor, double& yFactor);
Acad::ErrorStatus acedSetCurrentUCS(const AcGeMatrix3d& mat);
Acad::ErrorStatus acedGetCurrentUCS(AcGeMatrix3d& mat);
Acad::ErrorStatus acedRestorePreviousUCS();
class AcDbFcf;
class AcDbMText;
void acedEditToleranceInteractive(AcDbFcf* pTol);
int acedEditMTextInteractive(AcDbMText* pMText, bool useNewUI = false, bool allowTabs = false);
enum DimstyleTabSuppressed
{
  kSymbolsArrowsTabSuppressed = 0x01,
  kTextTabSuppressed = 0x02,
  kFitTabSuppressed = 0x04,
  kPrimaryTabSuppressed = 0x08,
  kAlternateTabSuppressed = 0x10,
  kToleranceTabSuppressed = 0x20
};
int acedEditDimstyleInteractiveEx(AcDbDatabase* pDb, AcDbDimStyleTableRecord* pRec, int familyType, const ACHAR* title = NULL, int tabCtrlFlags = 0);
Adesk::UInt32 acedGetRGB(int color);
Acad::ErrorStatus acedGetCurrentSelectionSet(AcDbObjectIdArray& sset);
Acad::ErrorStatus acedGetFullSubentPathsForCurrentSelection(const AcDbObjectId& selectedObject, AcDbFullSubentPathArray& selectedSubentities);
class AcDbHatch;
class AcDbEntity;
#  define acedGetIDispatch	AcadGetIDispatch
IDispatch* acedGetIDispatch(bool bAddRef);
AcDbObjectId acedActiveViewportId();
AcDbObjectId acedViewportIdFromNumber(int nVpNum);
int acedNumberOfViewports();
AcDbObjectId acedGetCurViewportObjectId();
Acad::ErrorStatus acedConvertEntityToHatch(AcDbHatch* pHatch, AcDbEntity*& pEnt, bool transferId);
#  include "aced-hatch.h"
Acad::ErrorStatus acedManageHatchEditorReactor(AcDbObjectId hatchId, AcHatchEdReact action, AcDbObjectId boundaryId = AcDbObjectId::kNull, AcHatchNotifier notifyType = kNobody, bool transformed = false);
enum AcEdDrawOrderCmdType
{
  kDrawOrderNone = 0,
  kDrawOrderBottom,
  kDrawOrderTop,
  kDrawOrderBelow,
  kDrawOrderAbove
};
Acad::ErrorStatus acedDrawOrderInherit(AcDbObjectId parent, AcDbObjectIdArray& childArray, AcEdDrawOrderCmdType cmd);
Acad::ErrorStatus acedCreateViewportByView(AcDbDatabase* pDb, const AcDbObjectId& view, const AcGePoint2d& location, double scale, AcDbObjectId& viewportId);
ACAD_PORT Acad::ErrorStatus acedCreateEnhancedViewportOnDrop(const ACHAR* filename, const ACHAR* viewName, const AcGePoint2d& location, double scale, AcDbObjectId labelBlockId, AcDbObjectId& sheetViewId, AcDbObjectId& viewportId);
ACAD_PORT Acad::ErrorStatus acedCreateEnhancedViewportOnDropDWG(const ACHAR* filename, AcDbExtents* extents, const AcGePoint2d& location, double scale, AcDbObjectId labelBlockId, AcDbObjectId& sheetViewId, AcDbObjectId& viewportId);
ACAD_PORT Acad::ErrorStatus acedGetUnitsValueString(AcDb::UnitsValue units, AcString& sUnits);
inline const AcString* acedGetUnitsValueString(AcDb::UnitsValue units)
{
  static AcString sRetVal;
  ::acedGetUnitsValueString(units, sRetVal);
  return &sRetVal;
}
/// <summary>
/// This function computes the conversion factor that blocks and xrefs 
/// need to be scaled duing insertion to retain their size.  So for example, 
/// if a block that is created using feet as its units is inserted into a drawing
/// with inches as its units, the conversion will be 12.
/// </summary>
/// <param name="blkInsunits">Input units that the block is created with.</param>
/// <param name="conversionFactor">Return the conversion factor between the block's
/// units and the current drawing's units.</param>
/// <returns>Returns true if a conversion factor was computed.</returns>
bool acedGetUnitsConversion(AcDb::UnitsValue blkInsunits, double& conversionFactor);
bool acdbCanonicalToSystemRange(int eUnits, const AcString& strIn, AcString& strOut);
bool acdbSystemRangeToCanonical(int eUnits, const AcString& strIn, AcString& strOut);
void acedEnableUsrbrk();
void acedDisableUsrbrk();
bool acedIsUsrbrkDisabled();
bool acedIsInBackgroundMode();
enum BlockEditModeFlags
{
  kBlkEditModeNone = 0x0,
  kBlkEditModeActive = 0x01,
  kBlkEditModeOpen = 0x02,
  kBlkEditModeDirty = 0x04
};
unsigned int acedGetBlockEditMode();
void acedOpenDocWindowsMinimized(bool bMinimized);
bool acedCompareToCurrentViewport(const AcDbViewTableRecord* pVwRec);
/// <summary>
/// Provides the id of the last frame rendered in animations invoked from the 
/// ANIPATH command 
/// </summary>
/// <returns>
/// Returns 0 when ANIPATH animation is inactive.  The first frame of an
/// an ANIPATH animation returns 1, and subsequent frames increment by 1 
/// from the previous frame.  
/// </returns>
Adesk::UInt32 acedGetAnimationFrameId(void);
/// <summary>This function is used to show the constraint bars for a given 
/// set of constrained entities.</summary>
/// <param name="subentPaths">Full sub-entity paths of entities for which 
/// constraint bars are to be shown.</param>
/// <returns>Returns true if successful, or false otherwise.</returns>
ACAD_PORT bool acedShowConstraintBar(AcDbFullSubentPathArray& subentPaths);
/// <summary>This function is used to hide the constraint bars for a given 
/// set of constrained entities.</summary>
/// <param name="subentPaths">Full sub-entity paths of entities for which 
/// constraint bars are to be hidden.</param>
/// <returns>Returns true if successful, or false otherwise.</returns>
ACAD_PORT bool acedHideConstraintBar(AcDbFullSubentPathArray& subentPaths);
/// <summary>This function is used to show or hide the constraint bars for 
/// all constrained entities in the active document.</summary>
/// <param name="bToShow">Set this to true to show constraint bars,
/// set to false to hide constraint bars. </param>
/// <returns>Returns true if successful, or false otherwise.</returns>
ACAD_PORT bool acedShowConstraintBarForAll(bool bToShow);
Acad::ErrorStatus acedTraceBoundary(const AcGePoint3d& seedPoint, bool detectIslands, AcDbVoidPtrArray& resultingBoundarySet);
void acedSetDrawComplexShape(int val);
int acedGetDrawComplexShape();
void acedSetRecursingLinetypeVectorGeneration(int val);
int acedGetRecursingLinetypeVectorGeneration();
struct flagmat* acedGetComplexLineTypeTransformPtr();
ACAD_PORT Acad::ErrorStatus acedAudit(AcDbDatabase* pDb, bool bFixErrors, bool bCmdLnEcho = false);
/// <summary>
/// Adds a supplemental cursor image. Only one cursor badge image can be shown at a time.
/// If multiple features supply badges the last badge with the highest priorityOrder will 
/// be the badge shown.
/// </summary>
/// <param name="pSuppCursorImage">Input image</param>
/// <param name="priorityOrder">Stacking order badge should appear in. Higher numbers win.</param>
/// <returns>Returns true if successful.</returns>
ACCORE_PORT bool acedAddSupplementalCursorImage(const AcGiImageBGRA32* pSuppCursorImage, int priorityOrder = 0);
/// <summary>
/// Removes a previously added supplemental cursor badge.
/// </summary>
/// <param name="pSuppCursorImage">Input image</param>
/// <returns>Returns true if successful.</returns>
ACCORE_PORT bool acedRemoveSupplementalCursorImage(const AcGiImageBGRA32* pSuppCursorImage);
/// <summary>
/// Checks if the current supplemental cursor badge is set.
/// </summary>
/// <returns>Returns true if there is supplemental cursor badge; otherwise false.</returns>
ACAD_PORT bool acedHasSupplementalCursorImage();
/// <summary>
/// Sets <x, y> to be the cursor offset to the top right corner of the pickbox.
/// </summary>
/// <param name="x">Input X offset</param>
/// <param name="y">Input Y offset</param>
ACCORE_PORT void acedSetSupplementalCursorOffset(int x, int y);
/// <summary>
/// Gets the cursor offset <x, y>, which is to the top right corner of the pickbox.
/// </summary>
/// <param name="x">X offset</param>
/// <param name="y">Y offset</param>
ACAD_PORT void acedGetSupplementalCursorOffset(int& x, int& y);
/// <summary>
/// Gets Dpi scaling value of Windows system.
/// </summary>
ACCORE_PORT float acedGetDpiScalingValue();
/// <summary>
/// Scale AcGiImage using gpiplus functions.
/// </summary>
ACAD_PORT bool acedScaleImageWithGDIPlus(const AcGiImageBGRA32* pSrcImg, const AcGiImageBGRA32* pDstImg);
class AcEdSysVarIterator
{
public:
  ACAD_PORT AcEdSysVarIterator();
  ACAD_PORT ~AcEdSysVarIterator();
  ACAD_PORT void step();
  ACAD_PORT const AcRxVariable* getSysVar();
  ACAD_PORT void reset();
  ACAD_PORT bool done() const;
private:
  AcEdImpSysVarIterator* m_pImp = nullptr;
};
#  pragma  pack (pop)
#endif
