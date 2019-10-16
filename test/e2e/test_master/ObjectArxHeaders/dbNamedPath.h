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
#pragma  pack(push, 8)
#pragma  warning( disable: 4275 4251 )
#ifdef SCENEDLLIMPEXP
#  undef SCENEDLLIMPEXP
#endif
#ifdef SCENEOE
#  define SCENEDLLIMPEXP	__declspec( dllexport )
#else 
#  define SCENEDLLIMPEXP
#endif
const ACHAR ACDB_NAMEDPATH_DICTIONARY[] = ACRX_T("ACAD_NAMEDPATH");
Acad::ErrorStatus SCENEDLLIMPEXP acdbGetNamedPathDictionary(AcDbDatabase* pDb, AcDbDictionary*& pDict, AcDb::OpenMode mode, bool createIfNonExist);
Acad::ErrorStatus SCENEDLLIMPEXP acdbGetNamedPathDictionary(AcDbDatabase* pDb, AcDbDictionary*& pDict, AcDb::OpenMode mode);
class AcDbImpNamedPath;
class AcGeCurve3d;
class SCENEDLLIMPEXP AcDbNamedPath : public AcDbObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbNamedPath);
  virtual ~AcDbNamedPath();
  virtual Acad::ErrorStatus getGeometry(AcGeCurve3d*& pCurveGeometry) const = 0;
protected:
  AcDbNamedPath(AcDbImpNamedPath* pImp);
  AcDbImpNamedPath* imp() const;
private:
  friend class AcDbImpNamedPath;
  AcDbImpNamedPath* mpImp;
};
class SCENEDLLIMPEXP AcDbCurvePath : public AcDbNamedPath
{
public:
  ACRX_DECLARE_MEMBERS(AcDbCurvePath);
  AcDbCurvePath();
  virtual ~AcDbCurvePath();
  virtual Acad::ErrorStatus getGeometry(AcGeCurve3d*& pCurveGeometry) const;
  Acad::ErrorStatus setGeometry(const AcDbObjectId& id);
  AcDbObjectId entityId() const;
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
protected:
  virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits);
private:
  friend class AcDbImpCurvePath;
};
class SCENEDLLIMPEXP AcDbPointPath : public AcDbNamedPath
{
public:
  ACRX_DECLARE_MEMBERS(AcDbPointPath);
  AcDbPointPath();
  virtual ~AcDbPointPath();
  virtual Acad::ErrorStatus getGeometry(AcGeCurve3d*& pCurveGeometry) const;
  Acad::ErrorStatus setGeometry(const AcGePoint3d& pt);
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
protected:
  virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits);
#ifndef _ADESK_MAC_
private:
  friend class AcDbPointPath;
#endif
};
#pragma  pack(pop)
