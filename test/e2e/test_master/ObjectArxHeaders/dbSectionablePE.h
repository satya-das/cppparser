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
///////////////////////////////////////////////////////////////////////////////
class AcDbSectionablePE : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS_EXPIMP(AcDbSectionablePE, ACDBCORE2D_PORT);
  virtual bool supportSection(const AcDbObject& pObject) = 0;
};
