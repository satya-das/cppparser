//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ACAPLMGR_H
#  define _ACAPLMGR_H
#  include "AcDbLMgr.h"
#  pragma  pack (push, 8)
class AcDbObjectId;
class AcGePoint2d;
class AcGePoint3d;
template <typename T>
class AcArrayMemCopyReallocator;
template <typename T, typename R>
class AcArray;
typedef AcArray<AcGePoint2d> AcGePoint2dArray;
class AcApLayoutManager : public AcDbLayoutManager
{
public:
  virtual int pageSetup(AcDbObjectId layoutBTRId = AcDbObjectId::kNull, void* pParent = nullptr, Adesk::Boolean isPageSetupDlg = true) = 0;
  virtual void updateCurrentPaper(Adesk::Boolean zoomToPaper = false) = 0;
  virtual void updateLayoutTabs() = 0;
  virtual Acad::ErrorStatus getActiveTab(AcString& sName) = 0;
  virtual const ACHAR* findActiveTab() final;
  virtual Adesk::Boolean showTabs() = 0;
  virtual void setShowTabs(Adesk::Boolean showTabs) = 0;
  virtual Adesk::Boolean showPageSetup() = 0;
  virtual void setShowPageSetup(Adesk::Boolean showPageSetupDlg) = 0;
  virtual Adesk::Boolean createViewports() = 0;
  virtual void setCreateViewports(Adesk::Boolean createViewports) = 0;
  virtual Adesk::Boolean showPaperBackground() = 0;
  virtual void setShowPaperBackground(Adesk::Boolean showPaperBackground) = 0;
  virtual Adesk::Boolean showPaperMargins() = 0;
  virtual void setShowPaperMargins(Adesk::Boolean showPaperMargins) = 0;
  virtual Adesk::Boolean showPrintBorder() = 0;
  virtual void setShowPrintBorder(Adesk::Boolean showPrintBorder) = 0;
  virtual Acad::ErrorStatus generateNextNewLayoutName(AcString& sName, AcDbDatabase* useDb = nullptr) = 0;
  virtual ACHAR* getNextNewLayoutName(AcDbDatabase* useDb = nullptr) final;
  virtual void setDefaultPlotConfig(AcDbObjectId layoutBTRId) = 0;
  virtual Acad::ErrorStatus getClipBoundaryElaboration(AcDbObjectId clipId, AcGePoint2dArray*& clipBoundary) = 0;
  virtual Acad::ErrorStatus pointInViewports(const AcGePoint3d& pickPt, AcDbObjectIdArray& viewports) = 0;
  virtual void setCaptureOnLayoutSwitch(bool bCaptureOnLayout) = 0;
  virtual Acad::ErrorStatus createLayoutFromTemplate(const ACHAR* newLayoutName, AcDbObjectId& newLayoutId, const ACHAR* templatePath, const ACHAR* layoutName, AcDbDatabase* pDb = NULL) = 0;
};
#  pragma  pack (pop)
inline const ACHAR* AcApLayoutManager::findActiveTab()
{
  static AcString sCachedName;
  this->getActiveTab(sCachedName);
  return sCachedName.constPtr();
}
inline ACHAR* AcApLayoutManager::getNextNewLayoutName(AcDbDatabase* useDb)
{
  AcString sName;
  return ::acutAcStringToAChar(sName, this->generateNextNewLayoutName(sName, useDb));
}
#endif
