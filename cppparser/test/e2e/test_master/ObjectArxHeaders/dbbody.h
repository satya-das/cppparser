//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//
// DESCRIPTION:
// The AcDbBody class is the interface class for representing
// general ACIS bodies inside AutoCAD.  All the functionality
// supported through this class is implemented in the class
// AcDbImpBody and its base classes.
#ifndef GEOMENT_DBBODY_H
#  define GEOMENT_DBBODY_H
#  include "dbmain.h"
#  include "dbsubeid.h"
#  pragma  pack (push, 8)
class AcDbBody : public AcDbEntity
{
public:
  ACDB_DECLARE_MEMBERS(AcDbBody);
  AcDbBody();
  virtual ~AcDbBody();
  virtual Adesk::Boolean isNull() const;
  ACDB_PORT void dragStatus(const AcDb::DragStat) override;
  virtual void* ASMBodyCopy(bool bDeepCopy = false) const;
  virtual const void* getLockedASMBody();
  virtual void unlockASMBody();
  virtual void* getLockedWritableASMBody();
  virtual void commitWritableASMBody();
  virtual Acad::ErrorStatus setASMBody(const void* modelerBody);
  virtual AcDbSubentId internalSubentId(void*) const;
  virtual void* internalSubentPtr(const AcDbSubentId& id) const;
  static Acad::ErrorStatus acisOut(const ACHAR* fileName, const AcDbVoidPtrArray&);
  static Acad::ErrorStatus acisIn(const ACHAR* fileName, AcDbVoidPtrArray&);
  virtual Adesk::UInt32 numChanges() const;
  ACDB_PORT virtual bool usesGraphicsCache();
  void invalidateCachedBodySubentIds();
};
#  pragma  pack (pop)
#endif
