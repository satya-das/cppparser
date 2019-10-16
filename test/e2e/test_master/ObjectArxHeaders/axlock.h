//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _AXLOCK_H
#  define _AXLOCK_H
#  include "acadstrc.h"
#  include "AcDbCore2dDefs.h"
#  pragma  pack (push, 8)
class AcDbDatabase;
class AcDbObjectId;
class AcAxDocLock
{
public:
  enum DocLockType
  {
    kNormal = 0,
    kCurDocSwitch = 1
  };
  AcAxDocLock();
  AcAxDocLock(const AcDbObjectId& objectId, DocLockType = kNormal);
  AcAxDocLock(AcDbDatabase* pDatabase, DocLockType = kNormal);
  ~AcAxDocLock();
  ACDBCORE2D_PORT Acad::ErrorStatus lockStatus() const;
  ACDBCORE2D_PORT void* document() const;
private:
  void lockDocument(AcDbDatabase* pDatabase, DocLockType lockType = kNormal);
  void initialize();
  Acad::ErrorStatus m_lockStatus;
  void* m_pDocToUnlock;
  void* m_pCurDocToRestore;
  bool m_restoreActivation;
};
#  pragma  pack (pop)
#endif
