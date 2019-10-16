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
const ACHAR ACDB_MOTIONPATH_DICTIONARY[] = ACRX_T("ACAD_MOTION");
Acad::ErrorStatus SCENEDLLIMPEXP acdbGetMotionPathDictionary(AcDbDatabase* pDb, AcDbDictionary*& pDict, AcDb::OpenMode mode, bool createIfNonExist);
Acad::ErrorStatus SCENEDLLIMPEXP acdbGetMotionPathDictionary(AcDbDatabase* pDb, AcDbDictionary*& pDict, AcDb::OpenMode mode);
class AcDbImpMotionPath;
class SCENEDLLIMPEXP AcDbMotionPath : public AcDbObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbMotionPath);
  AcDbMotionPath();
  virtual ~AcDbMotionPath();
  AcDbObjectId cameraPath() const;
  Acad::ErrorStatus setCameraPath(const AcDbObjectId& id);
  AcDbObjectId targetPath() const;
  Acad::ErrorStatus setTargetPath(const AcDbObjectId& id);
  AcDbObjectId viewTableRecordId() const;
  Acad::ErrorStatus setViewTableRecordId(const AcDbObjectId& id);
  Adesk::UInt32 frames() const;
  Acad::ErrorStatus setFrames(Adesk::UInt16 frames);
  Adesk::UInt32 frameRate() const;
  Acad::ErrorStatus setFrameRate(Adesk::UInt16 rate);
  bool cornerDecel() const;
  Acad::ErrorStatus setCornerDecel(bool cornerDecel);
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
protected:
  virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits);
  AcDbImpMotionPath* imp() const;
private:
  friend class AcDbImpMotionPath;
  AcDbImpMotionPath* mpImp;
};
