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
//
// This file contains "filer" class definitions of AcDbDeepCloneFiler
// and AcDbWblockCloneFiler.  These filers maintain a queue of typed
// object id's. All read/write requests are forwarded to a contained 
// "real" filer, except for object id's which are removed/added from/to 
// the queue.  The classes provide protocol for writing either "owned"
// or "hard" objects in the queue.
#ifndef AD_DBCFILERS_H
#  define AD_DBCFILERS_H	1
#  include "dbfiler.h"
#  pragma  pack (push, 8)
class AcDbWblockCloneFiler;
class AcDbImpDeepCloneFiler;
class AcDbDeepCloneFiler : public AcDbDwgFiler
{
  friend class AcDbSystemInternals;
public:
  ACRX_DECLARE_MEMBERS(AcDbDeepCloneFiler);
  AcDbDeepCloneFiler();
  virtual ~AcDbDeepCloneFiler();
    // overridden from AcDbDwgFiler 
    //
  Acad::ErrorStatus filerStatus() const override;
  AcDb::FilerType filerType() const override;
  void setFilerStatus(Acad::ErrorStatus) override;
  void resetFilerStatus() override;
  Acad::ErrorStatus readHardOwnershipId(AcDbHardOwnershipId*) override;
  Acad::ErrorStatus writeHardOwnershipId(const AcDbHardOwnershipId&) override;
  Acad::ErrorStatus readSoftOwnershipId(AcDbSoftOwnershipId*) override;
  Acad::ErrorStatus writeSoftOwnershipId(const AcDbSoftOwnershipId&) override;
  Acad::ErrorStatus readHardPointerId(AcDbHardPointerId*) override;
  Acad::ErrorStatus writeHardPointerId(const AcDbHardPointerId&) override;
  Acad::ErrorStatus readSoftPointerId(AcDbSoftPointerId*) override;
  Acad::ErrorStatus writeSoftPointerId(const AcDbSoftPointerId&) override;
  Acad::ErrorStatus readInt8(Adesk::Int8*) override;
  Acad::ErrorStatus writeInt8(Adesk::Int8) override;
    // This flavor of readString may go away in a future release.
  Acad::ErrorStatus readString(ACHAR**) override;
  Acad::ErrorStatus writeString(const ACHAR*) override;
  Acad::ErrorStatus readString(AcString&) override;
  Acad::ErrorStatus writeString(const AcString&) override;
  Acad::ErrorStatus readBChunk(ads_binary*) override;
  Acad::ErrorStatus writeBChunk(const ads_binary&) override;
  Acad::ErrorStatus readAcDbHandle(AcDbHandle*) override;
  Acad::ErrorStatus writeAcDbHandle(const AcDbHandle&) override;
  Acad::ErrorStatus readInt64(Adesk::Int64*) override;
  Acad::ErrorStatus writeInt64(Adesk::Int64) override;
  Acad::ErrorStatus readInt32(Adesk::Int32*) override;
  Acad::ErrorStatus writeInt32(Adesk::Int32) override;
  Acad::ErrorStatus readInt16(Adesk::Int16*) override;
  Acad::ErrorStatus writeInt16(Adesk::Int16) override;
  Acad::ErrorStatus readUInt64(Adesk::UInt64*) override;
  Acad::ErrorStatus writeUInt64(Adesk::UInt64) override;
  Acad::ErrorStatus readUInt32(Adesk::UInt32*) override;
  Acad::ErrorStatus writeUInt32(Adesk::UInt32) override;
  Acad::ErrorStatus readUInt16(Adesk::UInt16*) override;
  Acad::ErrorStatus writeUInt16(Adesk::UInt16) override;
  Acad::ErrorStatus readUInt8(Adesk::UInt8*) override;
  Acad::ErrorStatus writeUInt8(Adesk::UInt8) override;
  Acad::ErrorStatus readBoolean(Adesk::Boolean*) override;
  Acad::ErrorStatus writeBoolean(Adesk::Boolean) override;
  Acad::ErrorStatus readBool(bool*) override;
  Acad::ErrorStatus writeBool(bool) override;
  Acad::ErrorStatus readDouble(double*) override;
  Acad::ErrorStatus writeDouble(double) override;
  Acad::ErrorStatus readPoint2d(AcGePoint2d*) override;
  Acad::ErrorStatus writePoint2d(const AcGePoint2d&) override;
  Acad::ErrorStatus readPoint3d(AcGePoint3d*) override;
  Acad::ErrorStatus writePoint3d(const AcGePoint3d&) override;
  Acad::ErrorStatus readVector2d(AcGeVector2d*) override;
  Acad::ErrorStatus writeVector2d(const AcGeVector2d&) override;
  Acad::ErrorStatus readVector3d(AcGeVector3d*) override;
  Acad::ErrorStatus writeVector3d(const AcGeVector3d&) override;
  Acad::ErrorStatus readScale3d(AcGeScale3d*) override;
  Acad::ErrorStatus writeScale3d(const AcGeScale3d&) override;
  Acad::ErrorStatus readBytes(void*, Adesk::UIntPtr) override;
  Acad::ErrorStatus writeBytes(const void*, Adesk::UIntPtr) override;
  Acad::ErrorStatus readAddress(void**) override;
  Acad::ErrorStatus writeAddress(const void*) override;
  Acad::ErrorStatus seek(Adesk::Int64 nOffset, int nMethod) override;
  Adesk::Int64 tell() const override;
  Acad::ErrorStatus addReferences(AcDbIdRefQueue&) override;
  bool usesReferences() const override;
  AcDbFilerController& controller() const override;
    // Protocol specific to AcDbDeepCloneFiler
    //
  virtual bool getNextOwnedObject(AcDbObjectId& id);
  virtual bool moreOwnedObjects() const;
protected:
  AcDbDeepCloneFiler(AcDbSystemInternals*);
private:
  AcDbImpDeepCloneFiler* mpImpFiler;
};
class AcDbWblockCloneFiler : public AcDbDeepCloneFiler
{
  friend class AcDbSystemInternals;
public:
  ACRX_DECLARE_MEMBERS(AcDbWblockCloneFiler);
  AcDbWblockCloneFiler();
  Acad::ErrorStatus addReferences(AcDbIdRefQueue&) override;
  bool usesReferences() const override;
  virtual bool getNextHardObject(AcDbObjectId& id);
  virtual bool moreHardObjects() const;
  AcDb::FilerType filerType() const override;
};
#  pragma  pack (pop)
#endif
