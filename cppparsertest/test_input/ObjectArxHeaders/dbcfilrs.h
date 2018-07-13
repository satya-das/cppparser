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
#define AD_DBCFILERS_H 1

#include "dbfiler.h"
#pragma pack (push, 8)

class AcDbWblockCloneFiler;
class AcDbImpDeepCloneFiler;

class AcDbDeepCloneFiler: public AcDbDwgFiler
{
    friend class AcDbSystemInternals;
public:
    ACRX_DECLARE_MEMBERS(AcDbDeepCloneFiler);
    AcDbDeepCloneFiler();
    virtual ~AcDbDeepCloneFiler();

    // overridden from AcDbDwgFiler 
    //
    virtual Acad::ErrorStatus filerStatus() const override;
    virtual AcDb::FilerType   filerType() const override;
    virtual void              setFilerStatus(Acad::ErrorStatus) override;
    virtual void              resetFilerStatus() override;

    virtual Acad::ErrorStatus readHardOwnershipId(AcDbHardOwnershipId*) override;
    virtual Acad::ErrorStatus writeHardOwnershipId(const AcDbHardOwnershipId&) override;

    virtual Acad::ErrorStatus readSoftOwnershipId(AcDbSoftOwnershipId*) override;
    virtual Acad::ErrorStatus writeSoftOwnershipId(const AcDbSoftOwnershipId&) override;

    virtual Acad::ErrorStatus readHardPointerId(AcDbHardPointerId*) override;
    virtual Acad::ErrorStatus writeHardPointerId(const AcDbHardPointerId&) override;

    virtual Acad::ErrorStatus readSoftPointerId(AcDbSoftPointerId*) override;
    virtual Acad::ErrorStatus writeSoftPointerId(const AcDbSoftPointerId&) override;

    virtual Acad::ErrorStatus readInt8(Adesk::Int8 *) override;
    virtual Acad::ErrorStatus writeInt8(Adesk::Int8) override;

    // This flavor of readString may go away in a future release.
    virtual Acad::ErrorStatus readString(ACHAR **) override;
    virtual Acad::ErrorStatus writeString(const ACHAR *) override;

    virtual Acad::ErrorStatus readString(AcString &) override;
    virtual Acad::ErrorStatus writeString(const AcString &) override;

    virtual Acad::ErrorStatus readBChunk(ads_binary*) override;
    virtual Acad::ErrorStatus writeBChunk(const ads_binary&) override;

    virtual Acad::ErrorStatus readAcDbHandle(AcDbHandle*) override;
    virtual Acad::ErrorStatus writeAcDbHandle(const AcDbHandle&) override;

    virtual Acad::ErrorStatus readInt64(Adesk::Int64*) override;
    virtual Acad::ErrorStatus writeInt64(Adesk::Int64) override;

    virtual Acad::ErrorStatus readInt32(Adesk::Int32*) override;
    virtual Acad::ErrorStatus writeInt32(Adesk::Int32) override;

    virtual Acad::ErrorStatus readInt16(Adesk::Int16*) override;
    virtual Acad::ErrorStatus writeInt16(Adesk::Int16) override;

    virtual Acad::ErrorStatus readUInt64(Adesk::UInt64*) override;
    virtual Acad::ErrorStatus writeUInt64(Adesk::UInt64) override;

    virtual Acad::ErrorStatus readUInt32(Adesk::UInt32*) override;
    virtual Acad::ErrorStatus writeUInt32(Adesk::UInt32) override;

    virtual Acad::ErrorStatus readUInt16(Adesk::UInt16*) override;
    virtual Acad::ErrorStatus writeUInt16(Adesk::UInt16) override;

    virtual Acad::ErrorStatus readUInt8(Adesk::UInt8*) override;
    virtual Acad::ErrorStatus writeUInt8(Adesk::UInt8) override;

    virtual Acad::ErrorStatus readBoolean(Adesk::Boolean*) override;
    virtual Acad::ErrorStatus writeBoolean(Adesk::Boolean) override;

    virtual Acad::ErrorStatus readBool(bool*) override;
    virtual Acad::ErrorStatus writeBool(bool) override;

    virtual Acad::ErrorStatus readDouble(double*) override;
    virtual Acad::ErrorStatus writeDouble(double) override;

    virtual Acad::ErrorStatus readPoint2d(AcGePoint2d*) override;
    virtual Acad::ErrorStatus writePoint2d(const AcGePoint2d&) override;

    virtual Acad::ErrorStatus readPoint3d(AcGePoint3d*) override;
    virtual Acad::ErrorStatus writePoint3d(const AcGePoint3d&) override;

    virtual Acad::ErrorStatus readVector2d(AcGeVector2d*) override;
    virtual Acad::ErrorStatus writeVector2d(const AcGeVector2d&) override;

    virtual Acad::ErrorStatus readVector3d(AcGeVector3d*) override;
    virtual Acad::ErrorStatus writeVector3d(const AcGeVector3d&) override;

    virtual Acad::ErrorStatus readScale3d(AcGeScale3d*) override;
    virtual Acad::ErrorStatus writeScale3d(const AcGeScale3d&) override;

    virtual Acad::ErrorStatus readBytes(void*, Adesk::UIntPtr) override;
    virtual Acad::ErrorStatus writeBytes(const void*, Adesk::UIntPtr) override;

    virtual Acad::ErrorStatus readAddress(void **) override;
    virtual Acad::ErrorStatus writeAddress(const void *) override;

    virtual Acad::ErrorStatus seek(Adesk::Int64 nOffset, int nMethod) override;
    virtual Adesk::Int64      tell() const override;

    virtual Acad::ErrorStatus addReferences(AcDbIdRefQueue&) override;
    virtual              bool usesReferences() const override;
    virtual AcDbFilerController& controller() const override;

    // Protocol specific to AcDbDeepCloneFiler
    //
    virtual bool              getNextOwnedObject(AcDbObjectId& id);
    virtual bool              moreOwnedObjects() const;

protected:
    AcDbDeepCloneFiler(AcDbSystemInternals*);
private:
    AcDbImpDeepCloneFiler*      mpImpFiler;
};

class AcDbWblockCloneFiler: public  AcDbDeepCloneFiler
{
    friend class AcDbSystemInternals;
public:
    ACRX_DECLARE_MEMBERS(AcDbWblockCloneFiler);

    AcDbWblockCloneFiler();

    virtual Acad::ErrorStatus addReferences(AcDbIdRefQueue&) override;
    virtual              bool usesReferences() const override;

    virtual bool              getNextHardObject(AcDbObjectId& id);
    virtual bool              moreHardObjects() const;

    virtual AcDb::FilerType   filerType() const override;
};

#pragma pack (pop)
#endif
