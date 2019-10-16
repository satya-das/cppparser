//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#include "acdb.h"
#include "dbmain.h"
#pragma  once
#pragma  pack (push, 8)
class AcDbInterferencePE : public AcRxObject
{
public:
  enum Flags
  {
    kDefault = 0x00
  };
  ACRX_DECLARE_MEMBERS(AcDbInterferencePE);
  virtual Acad::ErrorStatus createInterferenceObjects(AcArray<AcDbEntity*>& interferenceObjects, AcDbEntity* pEnt1, AcDbEntity* pEnt2, unsigned int flags) const = 0;
};
#pragma  pack (pop)
//#endif
