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
#ifndef AD_DBPLACEHOLDER_H
#  define AD_DBPLACEHOLDER_H
#  include "dbmain.h"
#  pragma  pack (push, 8)
class AcDbPlaceHolder : public AcDbObject
{
  ACDB_DECLARE_MEMBERS(AcDbPlaceHolder);
public:
  AcDbPlaceHolder();
  virtual ~AcDbPlaceHolder();
  Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
  Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
protected:
  Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, AcDbIdMapping& idMap, Adesk::Boolean isPrimary = Adesk::kTrue) const override;
};
#  pragma  pack (pop)
#endif
