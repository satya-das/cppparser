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
class AcDbDynamicUCSPE : public AcRxObject
{
public:
  enum Flags
  {
    kDefault = 0x00
  };
  ACRX_DECLARE_MEMBERS(AcDbDynamicUCSPE);
  virtual Acad::ErrorStatus getCandidatePlanes(AcArray<AcGePlane>& results, double& distToEdge, double& objWidth, double& objHeight, AcDbEntity* pEnt, const AcDbSubentId& subentId, const AcGePlane& viewplane, AcDbDynamicUCSPE::Flags flags = kDefault) const = 0;
};
class CPoint;
class AcDbNonSubEntDynamicUCSPE : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS_EXPIMP(AcDbNonSubEntDynamicUCSPE, ACDBCORE2D_PORT);
  virtual Acad::ErrorStatus getCandidatePlane(AcDbEntity* Ent, const CPoint& pt, AcGePlane& result, double& distToEdge, double& objWidth, double& objHeight, void*& context) = 0;
  virtual Acad::ErrorStatus highlightPlane(AcDbEntity* Ent, void* context) = 0;
  virtual Acad::ErrorStatus dehighlightPlane(AcDbEntity* Ent, void* context) = 0;
};
#pragma  pack (pop)
