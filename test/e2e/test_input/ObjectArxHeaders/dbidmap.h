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
// DESCRIPTION:  Mapping class for object id's.

#ifndef AD_DBIDMAP_H
#define AD_DBIDMAP_H 1

#include "acdb.h"
#include "rxobject.h"
#include "dbid.h"

#pragma pack (push, 8)

class AcDbDatabase;

class AcDbIdPair
{
public:
    AcDbIdPair();
    AcDbIdPair(const AcDbIdPair&);
    AcDbIdPair(AcDbObjectId key, AcDbObjectId value,
               bool isCloned,
               bool isPrimary = false,
               bool isOwnerXlated = true);

    AcDbObjectId   key() const;
    AcDbObjectId   value() const;
    bool           isCloned() const;
    bool           isPrimary() const;
    bool           isOwnerXlated() const;

    void            setKey(AcDbObjectId);
    void            setValue(AcDbObjectId);
    void            setIsCloned(bool isCloned);
    void            setIsPrimary(bool isPrimary);
    void            setIsOwnerXlated(bool isOwnerXlated);

private:
    AcDbObjectId   mKey;
    AcDbObjectId   mValue;
    bool           mIsCloned : 1;
    bool           mIsPrimary : 1;
    bool           mIsOwnerXlated : 1;
};

class AcDbIdMappingIter;
class AcDbImpIdMapping;
class AcDbImpIdMappingIter;

class AcDbIdMapping: public  AcRxObject
{
public:
    AcDbIdMapping();
    virtual ~AcDbIdMapping();
    ACRX_DECLARE_MEMBERS(AcDbIdMapping);

    virtual Acad::ErrorStatus   assign(const AcDbIdPair&);
    virtual bool                compute(AcDbIdPair&) const;
    virtual bool                change(const AcDbIdPair&);
    virtual bool                del(AcDbObjectId key);

            Acad::ErrorStatus   destDb(AcDbDatabase*& db) const;
            Acad::ErrorStatus   setDestDb(AcDbDatabase* db);
            Acad::ErrorStatus   origDb(AcDbDatabase*& db) const;

            AcDb::DeepCloneType deepCloneContext() const;
            AcDb::DuplicateRecordCloning duplicateRecordCloning() const;

    virtual Acad::ErrorStatus   copyFrom(const AcRxObject* other) override;

private:
    friend class AcDbSystemInternals;
    friend class AcDbImpIdMappingIter;
    AcDbIdMapping(const AcDbIdMapping&) = delete; // no copy ctor or asst oper
    AcDbIdMapping& operator= (const AcDbIdMapping&) = delete;
    AcDbImpIdMapping* mpImp;
};


class AcDbIdMappingIter: public  AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbIdMappingIter);
    AcDbIdMappingIter(const AcDbIdMapping&);
    virtual ~AcDbIdMappingIter();

    virtual Acad::ErrorStatus   iterateOn(const AcDbIdMapping&);

    virtual void                start();
    virtual bool                getMap(AcDbIdPair&);
    virtual bool                next();
    virtual bool                done();

private:
    friend class                AcDbSystemInternals;
    AcDbImpIdMappingIter*       mpImp;
    AcDbIdMappingIter(const AcDbIdMappingIter&) = delete; // no copy ctor or asst oper
    AcDbIdMappingIter& operator= (const AcDbIdMappingIter&) = delete;
};

inline
AcDbObjectId AcDbIdPair::key() const
{ return mKey; }

inline
AcDbObjectId AcDbIdPair::value() const
{ return mValue; }

inline
bool AcDbIdPair::isCloned() const
{ return mIsCloned; }

inline
bool AcDbIdPair::isPrimary() const
{ return mIsPrimary; }

inline
bool AcDbIdPair::isOwnerXlated() const
{ return mIsOwnerXlated; }

inline
void AcDbIdPair::setKey(AcDbObjectId key)
{ mKey = key; }

inline
void AcDbIdPair::setValue(AcDbObjectId value)
{ mValue = value; }

inline
void AcDbIdPair::setIsCloned(bool isCloned)
{ mIsCloned = isCloned; }

inline
void AcDbIdPair::setIsPrimary(bool isPrimary)
{ mIsPrimary = isPrimary; }

inline
void AcDbIdPair::setIsOwnerXlated(bool isOwnerXlated)
{ mIsOwnerXlated = isOwnerXlated; }

#pragma pack (pop)

#endif

