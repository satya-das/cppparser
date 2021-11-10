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
//  acedinpt.h - Definition of AcEdInputPointManager and related stuff
#ifndef _ACEDINPT_H
#  define _ACEDINPT_H
#  include "rxobject.h"
#  include "dbmain.h"
#  pragma  pack (push, 8)
#  pragma  warning (disable: 4786)
class AcEdInputPointFilter;
class AcEdInputPointMonitor;
class AcApDocument;
class AcEdInputContextReactor;
class AcDbCustomOsnapMode;
class AcEdSubSelectFilter;
class AcEdInputPoint;
class AcEdInputPointFilterResult;
class AcEdInputPointMonitorResult;
class AcGeCurve3d;
class AcGeMatrix3d;
class AcGePoint3d;
class AcGeVector3d;
// AcEdInputPointManager defines the manager object for registered
// custom OSNAP modes, custom AutoSnap callbacks and point filter callbacks.
//
class AcEdInputPointManager
{
public:
  virtual ~AcEdInputPointManager()
  {
  }
    // registerPointFilter
    //
    // Invoke to register a point filter.  returns Acad::eOK if no filter
    // is currently in use, else returns Acad::eIllegalReplacement.  It's
    // not nice to hog the filter slot!
    //
  virtual Acad::ErrorStatus registerPointFilter(AcEdInputPointFilter* pFilter) = 0;
    // revokePointFilter
    //
    // Used to revoke the current Point Filter.  Returns Acad::eOk if there
    // was an active point filter, and Acad::eNullObjectPointer if there wasn't
    // one.  It's not nice to revoke someone else's filter!   If you must
    // do so, find out what it is (see currentPointFilter) and put it back,
    // right quick!
    //
  virtual Acad::ErrorStatus revokePointFilter() = 0;
    // currentPointFilter
    //
    // Returns the active point filter, if there is one, and NULL otherwise.
    //
  virtual AcEdInputPointFilter* currentPointFilter() const = 0;
    // addPointMonitor
    //
    // Used to add a point monitor to the active set.  Adding the same
    // point monitor twice (as compared by address) will cause Acad::eDuplicateKey
    // to be returned.  Each monitor will be invoked once and only once
    // per input point event. Otherwise, Acad::eOk will be returned.
    //
  virtual Acad::ErrorStatus addPointMonitor(AcEdInputPointMonitor* pMonitor) = 0;
    // removePointMonitor
    //
    // Used in remove a Point Monitor from the active set.
    // Returns Acad::eOk if the monitor indicated by the input address
    // was in the set, and Acad::eInvalidKey if it wasn't.
    //
  virtual Acad::ErrorStatus removePointMonitor(AcEdInputPointMonitor* pMonitor) = 0;
    // addInputContextReactor
    //
    // Add an input context reactor.  Find out what the user is currently
    // being prompted for via the AutoCAD Input mechanism (Windows dialogs
    // excluded).  Any number can be added, each reactor can only be added
    // once, same as input point monitors. Adding the same
    // reactor twice (as compared by address) will cause Acad::eDuplicateKey
    // to be returned. Otherwise, Acad::eOk will be returned.
    //
  virtual Acad::ErrorStatus addInputContextReactor(AcEdInputContextReactor* pReactor) = 0;
    // removeInputContextReactor
    //
    // Used in remove an input context reactor from the active set.
    // Returns Acad::eOk if the reactor indicated by the input address
    // was in the set, and Acad::eInvalidKey if it wasn't.
    //
  virtual Acad::ErrorStatus removeInputContextReactor(AcEdInputContextReactor* pReact) = 0;
    // Enable and disable cursor graphics for the associated document.
    // Intended for use in conjunction with custom cursor graphics.
    // IMPORTANT: This pair of calls operates on an internal counter, so
    // the system can keep track of multiple applications that wish to
    // suppress the system cursor.

    // disableSystemCursorGraphics
    //
    // Will either return Acad::eOk if it
    // works or Acad::eInvalidContext if there the cursor cannot be
    // disabled.
    //
    // Currenly Acad::eOk is always returned.
    //
  virtual Acad::ErrorStatus disableSystemCursorGraphics() = 0;
    // enableSystemCursorGraphics
    //
    // Returns Acad::eOk unless the disble count was already 0, in which
    // case Acad::eInvalidContext is returned.
    //
  virtual Acad::ErrorStatus enableSystemCursorGraphics() = 0;
    // systemCursorDisableCount
    //
    // Returns the count of callers who have the cursor disabled.
    //
  virtual int systemCursorDisableCount() const = 0;
    // turnOnForcedPick
    //
    // This call causes the AutoCAD input event mechanism to do a pick under the
    // prevailing pick aperture on all digitizer events, regardless of whether a
    // point is being acquired or whether any OSNAP modes are currently active.
    // If a point is being acquired AND OSNAP is active, the (osnap) $APERTURE
    // dimensions define the pickbox size, otherwise the normal $PICKBOX
    // will be used.  In the Acad::PointHistory enum, the following enum values
    // are related to this capability, as indicated by their related comments:
    // eForcedPick, ePickMask, eDidNotPick, eUsedPickBox, eUsedOsnapBox.
    //
    // A count is maintained, so that if multiple apps want to force picking,
    // it occurs until they are all done.
    //
    // Currenly Acad::eOk is always returned.
    //
  virtual Acad::ErrorStatus turnOnForcedPick() = 0;
    // turnOffForcedPick
    //
    // decrements the forced pick counter, and if the counter hits 0,
    // disables forced picking, which means entity picking occurs in "normal
    // circumstances, such as when input points are being acquired and
    // an OSNAP mode is active, or normal entity selection operations.
    // 
    // Returns Acad::eOk unless the forced pick count was already 0, in which
    // case Acad::eInvalidContext is returned.
    //
  virtual Acad::ErrorStatus turnOffForcedPick() = 0;
    // forcedPickCount
    //
    // Returns the count of callers who have forced picking turned on.
    //
  virtual int forcedPickCount() const = 0;
  virtual int mouseHasMoved() const = 0;
  virtual Acad::ErrorStatus turnOnSubentityWindowSelection() = 0;
  virtual Acad::ErrorStatus turnOffSubentityWindowSelection() = 0;
  virtual void enableMultiSubentPathSelection(bool bEnable) = 0;
    /**
     * This method registers a sub-selection filter
     *
     *  @param  pSSSubFilter    the sub-selection filter to be registered.
     *  
     *  @returns eSelectFilterError if there is an error when trying to
     *  initialize the filter data, e.g. get a list of AcRxClass* that this
     *  filter applies to. Otherwise, eOk.
     */
  virtual Acad::ErrorStatus addSubSelectFilter(AcEdSubSelectFilter* pSSSubFilter) = 0;
    /**
     * This method unregisters a sub-selection filter
     *
     * @param   pSSubFilter   the sub-selection filter to be unregistered.
     *
     * @returns eKeyNotFound if the object does not exist. eOk otherwise.
     */
  virtual Acad::ErrorStatus removeSubSelectFilter(AcEdSubSelectFilter* pSSSubFilter) = 0;
};
// AcEdInputPointFilter
//
// This callback protocol defines a combination 
// "Input Point Notification and Input Point filter" mechanism.
class AcEdImpInputPointFilterResult;
class AcEdImpInputPointManager;
#  ifndef _ADESK_MAC_
#    ifndef ACAD_PORT
#      ifdef ACAD_API
#        define ACAD_PORT	_declspec(dllexport)
#      else 
#        define ACAD_PORT
#      endif
#    endif
#  else 
// On OS X, we will export all symbols by default and will use GCC
// attributes to exclude symbols we don't want to export.
// In this case, we do want to export the AcEdInputPoint symbol
#    undef ACAD_PORT
#    define ACAD_PORT
#  endif
class ACAD_PORT AcEdInputPoint
{
private:
  AcEdImpInputPointManager* m_pImpMgr;
  AcEdInputPoint(AcEdImpInputPointManager* pImpMgr);
  AcEdInputPoint& operator=(const AcEdInputPoint&);
public:
  AcApDocument* document() const;
  bool pointComputed() const;
  int history() const;
  const AcGePoint3d& lastPoint() const;
  const AcGePoint3d& rawPoint() const;
  const AcGePoint3d& grippedPoint() const;
  const AcGePoint3d& cartesianSnappedPoint() const;
  const AcGePoint3d& osnappedPoint() const;
  const AcDb::OsnapMask osnapMask() const;
  const AcArray<AcDbCustomOsnapMode*>& customOsnapModes() const;
  const AcDb::OsnapMask osnapOverrides() const;
  const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides() const;
  const AcArray<AcDbObjectId>& pickedEntities() const;
  const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedPickedEntities() const;
  const AcArray<Adesk::GsMarker>& gsSelectionMark() const;
  const AcArray<AcDbObjectId>& keyPointEntities() const;
  const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedKeyPointEntities() const;
  const AcArray<Adesk::GsMarker>& keyPointGsSelectionMark() const;
  const AcArray<AcGeCurve3d*>& alignmentPaths() const;
  const AcGePoint3d& computedPoint() const;
  const ACHAR* tooltipString() const;
  AcGiViewportDraw* drawContext() const;
  friend class AcEdImpInputPointManager;
};
class ACAD_PORT AcEdInputPointFilterResult
{
private:
  AcEdImpInputPointFilterResult* m_pImp;
  AcEdInputPointFilterResult();
  AcEdInputPointFilterResult& operator=(const AcEdInputPointFilterResult&);
public:
  ~AcEdInputPointFilterResult();
  void setNewPoint(const AcGePoint3d& newValue);
  void setDisplayOsnapGlyph(bool newValue);
  void setNewTooltipString(const ACHAR* newValue);
  void setRetry(bool newValue);
  const AcGePoint3d& newPoint() const;
  bool displayOsnapGlyph() const;
  const ACHAR* newTooltipString() const;
  bool retry() const;
  friend class AcEdImpInputPointManager;
};
class AcEdImpInputPointMonitorResult;
class ACAD_PORT AcEdInputPointMonitorResult
{
private:
  AcEdImpInputPointMonitorResult* m_pImp;
  AcEdInputPointMonitorResult();
  AcEdInputPointMonitorResult& operator=(const AcEdInputPointMonitorResult&);
public:
  ~AcEdInputPointMonitorResult();
  void setAdditionalTooltipString(const ACHAR*);
  bool appendToTooltipStr() const;
  const ACHAR* additionalTooltipString() const;
  friend class AcEdImpInputPointManager;
};
class AcEdInputPointFilter : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcEdInputPointFilter);
    // processInputPoint
    //
    // This callback is made every time an input event results in an
    // 3D point in the prevailing geometric space.  Such events include:
    // - digitizer motion with the cursor over the active viewport of the
    //   active document window
    // - digitizer motion in TABLET mode in the active document window,
    // - A string entered representing a point, either interactively, by
    //   script, (command) input, menu macro expansion, and Windows Message
    //   loop stuffing.
    // - A LISP expression that evaluates to be a 2D or 3D point.
    //
    // The callback is made after the AutoCAD user input complex has
    // fully processed the point except for XYZ coordinate filtering,
    // at which time AutoCAD will either
    // return the point to a caller, or accept the coordinate(s) being
    // prompted for and return for another point if XYZ coordinage filtering
    // is happening.
    //
    // Output Values
    //
    // The function can return a new "final" point, a new tooltip string, and/or
    // tell the system to reprompt for another point, essentially not returning the
    // the point to the caller.  This reprompting capability can allow things like,
    // say, a polar coordinate filter (first the direction, then the distance).
    //
    // Graphics Output.
    //
    // Graphics output to the current viewport is facilitated by passing in an
    // instance of AcGiViewportDraw*, the viewport drawing context.  This yields
    // the same graphics capability that AcDbEntity::viewportDraw() has at its
    // disposal.
    //
    // Input Values
    //
    // A set of arguments that together described the
    // history of the point computed so far for this particular event,
    // which could be either a digitizer motion or string entered by various
    // means.  Each of the arguments is described in comments below, but the
    // key arguments are:
    // - the "pointComputed" bool, which indicates whether points
    // could even be computed at all (they can't be under certain view conditions
    // where forced picking is enabled, and a pick could be made in spite of the
    // view conditions.  Otherwise, pointComputed will return TRUE.
    // - A "history" mask has bits set indicating what actually happened out
    // of the builtin AutoCAD point processing, plus the point filter, for monitor
    // callbacks.
    // - the point(s) computed by AutoCAD by various builtin filters
    // - entities under the prevailing cursor aperture, if any.
    // - and there are more arguments, as listed and described below.
    //
    // Return Status:  Acad::eOk should always be returned.
    //
  ADESK_DEPRECATED virtual Acad::ErrorStatus processInputPoint(bool&, AcGePoint3d&, bool&, bool&, ACHAR*&, bool&, AcGiViewportDraw*, AcApDocument*, bool, int, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, AcDb::OsnapMask, const AcArray<AcDbCustomOsnapMode*>&, AcDb::OsnapMask, const AcArray<AcDbCustomOsnapMode*>&, const AcArray<AcDbObjectId>&, const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&, const AcArray<Adesk::GsMarker>&, const AcArray<AcDbObjectId>&, const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&, const AcArray<Adesk::GsMarker>&, const AcArray<AcGeCurve3d*>&, const AcGePoint3d&, const ACHAR*)
  {
    return Acad::eOk;
  }
    // --- end of processInputPoint (big one, eh?)
  ACAD_PORT virtual Acad::ErrorStatus processInputPoint(const AcEdInputPoint& input, AcEdInputPointFilterResult& output);
    // revokeInputFilter
    //
    // This callback is made whenever a filter is revoked.  If another filter
    // has "chained" a registered filter, it should forward this call, and compare
    // the input "revokedFilter" with its own "this" address.  If they match, the
    // filter returns its embedded filter, if there is any, so the calling filter
    // (or AutoCAD) can update its own filter pointer with it.  If they don't match,
    // the filter should forward the call to its embedded filter, if there is any,
    // and return its "this" pointer, which effectively leaves its nesting status
    // unchanged (Note that this is the default behavior).
    // The net effect is to remove the revoked filter from the chain,
    // and leave the rest of the chain alone.  Of course, if an outer filter
    // detects its immediate nested filter as being changed (i.e. removed), it
    // can query the new filter's class and take whatever action is necessary.
    // which is hopefully nothing, else you have an unstable sequence.
    //
  virtual AcEdInputPointFilter* revokeInputFilter(AcEdInputPointFilter*)
  {
    return this;
  }
};
// AcEdInputPointMonitor
//
// This callback Is like point filter, except it cannot alter the point, tooltip
// string, or ask the system to retry.
class AcEdInputPointMonitor : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcEdInputPointMonitor);
    // monitorInputPoint
    //
    // This callback is under the exact same conditions as AcEdInputPointFilter,
    // except that the point filter is invoked first, and can affect the
    // "computed point".
    //
    // The callback is made after the AutoCAD user input complex has
    // fully processed the point except for XYZ coordinate filtering,
    // AND after an app-defined input point filter has processed the point,
    // if one is registered.  After invoking all registered instances of
    // AcEdInputPointMonitor, AutoCAD will either
    // return the point to a caller, or accept the coordinate(s) being
    // prompted for and return for another point if XYZ coordinage filtering
    // is happening.
    //
    // Output Values
    //
    // Unlike AcEdInpoutPointFilter, this function cannot affect the point or
    // influence the prompting, and therefore has none of the Output Value
    // parameters of AcEdInputPointFilter.  However, see graphics output, which
    // is the same for monitors as for filters.
    //
    // Graphics Input/Output.
    //
    // Same as AcEdInputPointFilter
    //
    // Input Values
    //
    // Same as AcEdInputPointFilter, except where noted.
    //
    // Return Status:  Acad::eOk should always be returned.
    //
  ADESK_DEPRECATED virtual Acad::ErrorStatus monitorInputPoint(bool&, ACHAR*&, AcGiViewportDraw*, AcApDocument*, bool, int, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, AcDb::OsnapMask, const AcArray<AcDbCustomOsnapMode*>&, AcDb::OsnapMask, const AcArray<AcDbCustomOsnapMode*>&, const AcArray<AcDbObjectId>&, const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&, const AcArray<Adesk::GsMarker>&, const AcArray<AcDbObjectId>&, const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&, const AcArray<Adesk::GsMarker>&, const AcArray<AcGeCurve3d*>&, const AcGePoint3d&, const ACHAR*)
  {
    return Acad::eOk;
  }
  ACAD_PORT virtual Acad::ErrorStatus monitorInputPoint(const AcEdInputPoint& input, AcEdInputPointMonitorResult& output);
  virtual bool excludeFromOsnapCalculation(const AcArray<AcDbObjectId>&, Adesk::GsMarker)
  {
    return false;
  }
};
class AcEdInputContextReactor
{
// Notification that user prompts are starting and completing.  
//
// The parameters ALL have the same meaning as the corresponding parameters
// in the corresponding "acedGet*()" functions.  As far as apps are concerned,
// that is exactly what we are monitoring, although internally, the values
// will be taken from the prevailing upkt struct.
//
// Note that the inputs can only be discerned from the "beginGetXxx" callbacks
// and the outputs are returned to the "endGetXxx" callbacks.  This eliminates
// redundancy, and obviously, the timing is right.   Within a given
// document, these callbacks can be nested, but an "endGetXxx" callback will
// always balance with a "beginGetXxx" callback within a document.
//
// Note also that the acedInitGet() parameters are folded into the beginGetXxx
// callbacks, and if a keyword is specified and entered, they PromptStatus
// will be set accordingly and and the pKeyword parameter will point to the
// keyword.
//
public:
  virtual ~AcEdInputContextReactor()
  {
  }
  virtual void beginGetPoint(const AcGePoint3d*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetPoint(Acad::PromptStatus, const AcGePoint3d&, const ACHAR*&)
  {
  }
  virtual void beginGetAngle(const AcGePoint3d*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetAngle(Acad::PromptStatus, double&, const ACHAR*&)
  {
  }
  virtual void beginGetDistance(const AcGePoint3d*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetDistance(Acad::PromptStatus, double&, const ACHAR*&)
  {
  }
  virtual void beginGetOrientation(const AcGePoint3d*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetOrientation(Acad::PromptStatus, double&, const ACHAR*&)
  {
  }
  virtual void beginGetCorner(const AcGePoint3d*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetCorner(Acad::PromptStatus, AcGePoint3d&, const ACHAR*&)
  {
  }
    // *ScaleFactor is the same as *Distance, except a negative
    // value can be returned.  There is no exported ADS/LISP/ActiveX equivalent.
    //
  virtual void beginGetScaleFactor(const AcGePoint3d*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetScaleFactor(Acad::PromptStatus, double&, const ACHAR*&)
  {
  }
    // Begin Nongeometric value input contexts.
    // Design note:  No mistake, getstring() does NOT do keywords!
    //
  virtual void beginGetString(const ACHAR*, int)
  {
  }
  virtual void endGetString(Acad::PromptStatus, ACHAR*)
  {
  }
  virtual void beginGetKeyword(const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetKeyword(Acad::PromptStatus, const ACHAR*&)
  {
  }
  virtual void beginGetInteger(const int*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetInteger(Acad::PromptStatus, int&, const ACHAR*&)
  {
  }
    // *Color() is effectively a ranged-checked *Integer()
  virtual void beginGetColor(const int*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetColor(Acad::PromptStatus, int&, const ACHAR*&)
  {
  }
  virtual void beginGetReal(const double*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetReal(Acad::PromptStatus, double&, const ACHAR*&)
  {
  }
  virtual void beginEntsel(const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endEntsel(Acad::PromptStatus, AcDbObjectId&, AcGePoint3d&, const ACHAR*)
  {
  }
    // These two callbacks service both acedNEntSel() and acedNEntSelP()
    // calls.  The differences are immaterial with regard to monitoring
    // input.
    //
  virtual void beginNentsel(const ACHAR*, Adesk::Boolean, int, const ACHAR*)
  {
  }
  virtual void endNentsel(Acad::PromptStatus, AcDbObjectId, const AcGePoint3d&, const AcGeMatrix3d&, const resbuf*, const ACHAR*)
  {
  }
  virtual void beginSSGet(const ACHAR*, int, const ACHAR*, const ACHAR*, const AcArray<AcGePoint3d>&, const resbuf*)
  {
  }
  virtual void endSSGet(Acad::PromptStatus, const AcArray<AcDbObjectId>&)
  {
  }
    // These two callbacks cover internal AutoCAD drag sequences, acedDraggen()
    // and AcEdJig drag sequences also.
    //
  virtual void beginDragSequence(const ACHAR*)
  {
  }
  virtual void endDragSequence(Acad::PromptStatus, AcGePoint3d&, AcGeVector3d&)
  {
  }
    // Quiescent state begin/end notification
  virtual void beginQuiescentState()
  {
  }
  virtual void endQuiescentState()
  {
  }
};
#  pragma  pack (pop)
#endif
