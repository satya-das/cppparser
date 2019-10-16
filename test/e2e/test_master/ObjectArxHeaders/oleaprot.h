//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef OLEAUTO_H
#  define OLEAUTO_H
#  include "adesk.h"
#  include "acdbport.h"
#  ifdef _ADESK_WINDOWS_
#    include "dbmain.h"
#    pragma  pack (push, 8)
class ADESK_NO_VTABLE AcAxOleLinkManager
{
public:
  virtual IUnknown* GetIUnknown(AcDbObject* pObject) = 0;
  virtual Adesk::Boolean SetIUnknown(AcDbObject* pObject, IUnknown* pUnknown) = 0;
  virtual IUnknown* GetIUnknown(AcDbDatabase* pDatabase) = 0;
  virtual Adesk::Boolean SetIUnknown(AcDbDatabase* pDatabase, IUnknown* pUnknown) = 0;
  virtual IDispatch* GetDocIDispatch(AcDbDatabase* pDatabase) = 0;
  virtual Adesk::Boolean SetDocIDispatch(AcDbDatabase* pDatabase, IDispatch* pDispatch) = 0;
  virtual IUnknown* GetIUnknown(AcDbObject* pObject, const AcDbSubentId& id) = 0;
  virtual Adesk::Boolean SetIUnknown(AcDbObject* pObject, const AcDbSubentId& id, IUnknown* pUnknown) = 0;
};
ACDB_PORT AcAxOleLinkManager* AcAxGetOleLinkManager();
#    pragma  pack (pop)
#  endif
#endif
