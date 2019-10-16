//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef DOUBLECLICKEDIT_H
#  define DOUBLECLICKEDIT_H
#  include "acdb.h"
#  include "dbmain.h"
#  pragma  pack (push, 8)
class ADESK_NO_VTABLE AcDbDoubleClickEdit : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbDoubleClickEdit);
  virtual void startEdit(AcDbEntity* pEnt, AcGePoint3d pt) = 0;
  virtual void finishEdit(void) = 0;
};
#  pragma  pack (pop)
#endif
