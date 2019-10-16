//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBFRAME_H
#  define AD_DBFRAME_H
#  include "dbmain.h"
#  include "gepnt3d.h"
#  pragma  pack (push, 8)
class ADESK_NO_VTABLE AcDbFrame : public AcDbEntity
{
protected:
  AcDbFrame();
  ACDB_DECLARE_MEMBERS(AcDbFrame);
public:
  virtual ~AcDbFrame();
};
#  pragma  pack (pop)
#endif
