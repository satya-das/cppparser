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

#ifndef GEOMENT_DBSUBEID_H
#define GEOMENT_DBSUBEID_H

#include "acdb.h"
#include "dbidar.h"

#pragma pack (push, 8)

class AcDbSubentId
{
public:
    AcDbSubentId();
    AcDbSubentId(AcDb::SubentType type, Adesk::GsMarker index);
    AcDbSubentId(AcRxClass* pTypeClass, Adesk::GsMarker index);
#ifdef __clang__
    ~AcDbSubentId() {};
#endif

    bool               operator ==(const AcDbSubentId& id) const;
    bool               operator !=(const AcDbSubentId& id) const;

    AcDb::SubentType   type () const;
    void               setType(AcDb::SubentType);
    AcRxClass*         typeClass () const;
    void               setTypeClass(AcRxClass* pClass);
    Adesk::GsMarker    index() const;
    void               setIndex(Adesk::GsMarker);
    
private:
    AcDb::SubentType mType;
    Adesk::GsMarker  mIndex;
    AcRxClass*       mpTypeClass;
};

const Adesk::GsMarker kNullSubentIndex = 0;

__declspec(selectany) extern const AcDbSubentId kNullSubentId(AcDb::kNullSubentType,
                                                              kNullSubentIndex);

class AcDbFullSubentPath
{
public:
    AcDbFullSubentPath();
    AcDbFullSubentPath(AcDb::SubentType type, Adesk::GsMarker index);
    AcDbFullSubentPath(AcDbObjectId entId, AcDb::SubentType type, Adesk::GsMarker index);
    AcDbFullSubentPath(AcDbObjectId entId, AcDbSubentId subId);
    AcDbFullSubentPath(AcDbObjectIdArray objectIds, AcDbSubentId subId);
    AcDbFullSubentPath(const AcDbFullSubentPath&);
    ~AcDbFullSubentPath();

    AcDbFullSubentPath&     operator =  (const AcDbFullSubentPath&);


    bool           operator ==(const AcDbFullSubentPath& id) const;
    bool           operator !=(const AcDbFullSubentPath& id) const;

    void                objectIds(AcDbObjectIdArray& objectIds) const;
    AcDbObjectIdArray&  objectIds();
    const AcDbObjectIdArray&  objectIds() const;
    const AcDbSubentId  subentId () const;
    AcDbSubentId&       subentId ();
    void* userAppData() const;
    void setUserAppData(void* pData);
    
private:                            
    AcDbObjectIdArray mObjectIds;
    AcDbSubentId      mSubentId;
    void*             mpUserAppData {nullptr};
};

// inlines

inline AcDb::SubentType
AcDbSubentId::type () const
{
    return mType;
}

inline void
AcDbSubentId::setType(AcDb::SubentType type)
{
    mType = type;
    if (mType != AcDb::kClassSubentType)
        mpTypeClass = nullptr;
}

inline Adesk::GsMarker
AcDbSubentId::index() const
{
    return mIndex;
}

inline void  
AcDbSubentId::setIndex(Adesk::GsMarker index)
{
    mIndex = index;
}

inline AcRxClass* 
AcDbSubentId::typeClass() const
{
    return mpTypeClass;
}

inline void
AcDbSubentId::setTypeClass(AcRxClass* pTypeClass)
{
    mpTypeClass = pTypeClass;
    if (mpTypeClass != nullptr)
        mType = AcDb::kClassSubentType;
}

inline
AcDbSubentId::AcDbSubentId() 
    : mType(AcDb::kNullSubentType), mIndex(kNullSubentIndex), mpTypeClass(nullptr)
{
}

inline
AcDbSubentId::AcDbSubentId(AcDb::SubentType t, Adesk::GsMarker i) 
    : mType(t), mIndex(i), mpTypeClass(nullptr)
{
}

inline
AcDbSubentId::AcDbSubentId(AcRxClass* pTypeClass, Adesk::GsMarker i) 
    : mType(AcDb::kClassSubentType), mIndex(i), mpTypeClass(pTypeClass)
{
}

inline bool
AcDbSubentId::operator ==(const AcDbSubentId& id) const
{
    return ((mIndex == id.mIndex) 
            && (mType == id.mType) 
            && (mpTypeClass == id.mpTypeClass));
}


inline bool
AcDbSubentId::operator !=(const AcDbSubentId& id) const
{
    return ((mIndex != id.mIndex) 
            || (mType != id.mType)
            || (mpTypeClass != id.mpTypeClass));
}

inline
AcDbFullSubentPath::AcDbFullSubentPath() : mpUserAppData(NULL)
{
}

inline
AcDbFullSubentPath::AcDbFullSubentPath(AcDb::SubentType type,
                                       Adesk::GsMarker index)
    : mSubentId(type, index), mpUserAppData(NULL)
{
}

inline void
AcDbFullSubentPath::objectIds(AcDbObjectIdArray& objectIds) const
{
    objectIds = mObjectIds;
}

inline AcDbObjectIdArray&
AcDbFullSubentPath::objectIds()
{
    return mObjectIds;
}

inline const AcDbObjectIdArray&
AcDbFullSubentPath::objectIds() const
{
    return mObjectIds;
}

inline const AcDbSubentId
AcDbFullSubentPath::subentId () const
{
    return mSubentId;
}

inline AcDbSubentId&
AcDbFullSubentPath::subentId ()
{
    return mSubentId;
}

inline void*
AcDbFullSubentPath::userAppData() const
{
    return mpUserAppData;
}

inline void
AcDbFullSubentPath::setUserAppData(void* pData)
{
    mpUserAppData = pData;
}

#pragma pack (pop)

#endif

