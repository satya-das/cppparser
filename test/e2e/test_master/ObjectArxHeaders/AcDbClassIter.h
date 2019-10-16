//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "dbmain.h"
#pragma  pack (push, 4)
class ADESK_NO_VTABLE AcDbClassIterator
{
public:
  ACDBCORE2D_PORT static AcDbClassIterator* newIterator();
  ACDBCORE2D_PORT static void deleteIterator(AcDbClassIterator* pIter);
  enum
  {
    kAllClasses = 0x01,
    kCustomClasses = 0x02,
    kProxyClasses = 0x04
  };
  virtual Acad::ErrorStatus start(AcDbDatabase* pDb, int nFlags) = 0;
  virtual bool next() = 0;
  virtual bool done() const = 0;
  virtual void detach() = 0;
  virtual const ACHAR* name() const = 0;
  virtual const ACHAR* appName() const = 0;
  virtual const ACHAR* dxfName() const = 0;
  virtual Adesk::UInt32 numInstances() const = 0;
  virtual bool isProxy() const = 0;
  virtual bool isEntity() const = 0;
protected:
  AcDbClassIterator();
  virtual ~AcDbClassIterator();
};
#pragma  pack (pop)
