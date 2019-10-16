//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACDB_SORTTAB_H
#  define ACDB_SORTTAB_H	1
#  include "dbmain.h"
class AcDbImpSortentsTable;
class AcDbSortentsTable : public AcDbObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbSortentsTable);
  AcDbSortentsTable();
  virtual ~AcDbSortentsTable();
  Adesk::Boolean sortAs(AcDbObjectId, AcDbHandle&) const;
  void getSortHandle(AcDbObjectId id, AcDbHandle& h) const;
  Acad::ErrorStatus remove(AcDbObjectId);
  Acad::ErrorStatus moveToBottom(const AcDbObjectIdArray& ar);
  Acad::ErrorStatus moveToTop(const AcDbObjectIdArray& ar);
  Acad::ErrorStatus moveBelow(const AcDbObjectIdArray& ar, AcDbObjectId target);
  Acad::ErrorStatus moveAbove(const AcDbObjectIdArray& ar, AcDbObjectId target);
  Acad::ErrorStatus swapOrder(AcDbObjectId, AcDbObjectId);
  Acad::ErrorStatus setBlockId(AcDbObjectId);
  AcDbObjectId blockId() const;
  Acad::ErrorStatus firstEntityIsDrawnBeforeSecond(AcDbObjectId first, AcDbObjectId second, bool& result) const;
  Acad::ErrorStatus getFullDrawOrder(AcDbObjectIdArray& ents, Adesk::UInt8 honorSortentsMask = 0) const;
  Acad::ErrorStatus getRelativeDrawOrder(AcDbObjectIdArray& ar, Adesk::UInt8 honorSortentsMask = 0) const;
  Acad::ErrorStatus setRelativeDrawOrder(const AcDbObjectIdArray& ar);
  virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler*, AcRxClass*) override;
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler*) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler*) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const override;
  virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo) override;
private:
  friend class AcDbSystemInternals;
  AcDbImpSortentsTable* mpImpObj;
protected:
  virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
#endif
