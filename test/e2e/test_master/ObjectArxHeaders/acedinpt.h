//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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
class AcEdInputPointManager
{
public:
  virtual ~AcEdInputPointManager()
  {
  }
  virtual Acad::ErrorStatus registerPointFilter(AcEdInputPointFilter* pFilter) = 0;
  virtual Acad::ErrorStatus revokePointFilter() = 0;
  virtual AcEdInputPointFilter* currentPointFilter() const = 0;
  virtual Acad::ErrorStatus addPointMonitor(AcEdInputPointMonitor* pMonitor) = 0;
  virtual Acad::ErrorStatus removePointMonitor(AcEdInputPointMonitor* pMonitor) = 0;
  virtual Acad::ErrorStatus addInputContextReactor(AcEdInputContextReactor* pReactor) = 0;
  virtual Acad::ErrorStatus removeInputContextReactor(AcEdInputContextReactor* pReact) = 0;
  virtual Acad::ErrorStatus disableSystemCursorGraphics() = 0;
  virtual Acad::ErrorStatus enableSystemCursorGraphics() = 0;
  virtual int systemCursorDisableCount() const = 0;
  virtual Acad::ErrorStatus turnOnForcedPick() = 0;
  virtual Acad::ErrorStatus turnOffForcedPick() = 0;
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
  ADESK_DEPRECATED virtual Acad::ErrorStatus processInputPoint(bool&, AcGePoint3d&, bool&, bool&, ACHAR*&, bool&, AcGiViewportDraw*, AcApDocument*, bool, int, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&, AcDb::OsnapMask, const AcArray<AcDbCustomOsnapMode*>&, AcDb::OsnapMask, const AcArray<AcDbCustomOsnapMode*>&, const AcArray<AcDbObjectId>&, const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&, const AcArray<Adesk::GsMarker>&, const AcArray<AcDbObjectId>&, const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&, const AcArray<Adesk::GsMarker>&, const AcArray<AcGeCurve3d*>&, const AcGePoint3d&, const ACHAR*)
  {
    return Acad::eOk;
  }
  ACAD_PORT virtual Acad::ErrorStatus processInputPoint(const AcEdInputPoint& input, AcEdInputPointFilterResult& output);
  virtual AcEdInputPointFilter* revokeInputFilter(AcEdInputPointFilter*)
  {
    return this;
  }
};
class AcEdInputPointMonitor : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcEdInputPointMonitor);
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
  virtual void beginGetScaleFactor(const AcGePoint3d*, const ACHAR*, int, const ACHAR*)
  {
  }
  virtual void endGetScaleFactor(Acad::PromptStatus, double&, const ACHAR*&)
  {
  }
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
  virtual void beginDragSequence(const ACHAR*)
  {
  }
  virtual void endDragSequence(Acad::PromptStatus, AcGePoint3d&, AcGeVector3d&)
  {
  }
  virtual void beginQuiescentState()
  {
  }
  virtual void endQuiescentState()
  {
  }
};
#  pragma  pack (pop)
#endif
