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

#ifndef _rxdict_h
#define _rxdict_h 1

#include "rxobject.h"
#include "AdAChar.h"

#pragma pack (push, 8)

class AcRxDictionaryIterator;

class AcRxDictionary: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxDictionary, ACBASE_PORT);

    virtual AcRxObject*    at      (const ACHAR* key) const = 0;
    virtual AcRxObject*    at      (Adesk::UInt32 id) const = 0;

    AcRxObject*            atPut   (const ACHAR* key, AcRxObject* pObject);
    virtual AcRxObject*    atPut   (const ACHAR* key, AcRxObject* pObject,
        Adesk::UInt32& retId) = 0;
    virtual AcRxObject*    atPut   (Adesk::UInt32 id, AcRxObject* pObject) = 0;

    virtual Adesk::Boolean resetKey(const ACHAR* oldKey, const ACHAR* newKey) = 0;
    virtual Adesk::Boolean resetKey(Adesk::UInt32 id, const ACHAR* newKey) = 0;

    virtual Adesk::Boolean atKeyAndIdPut(const ACHAR* newKey, Adesk::UInt32 id,
        AcRxObject* pObject) = 0;

    virtual AcRxObject*    remove  (const ACHAR* key) = 0;
    virtual AcRxObject*    remove  (Adesk::UInt32 id) = 0;

    virtual Adesk::Boolean has     (const ACHAR* entryName) const = 0;
    virtual Adesk::Boolean has     (Adesk::UInt32 id) const = 0;

    virtual Adesk::UInt32  idAt    (const ACHAR* key) const = 0;

    virtual const ACHAR*    keyAt   (Adesk::UInt32 id) const = 0;

    virtual Adesk::UInt32  numEntries() const = 0;

    virtual AcRxDictionaryIterator* newIterator(
        AcRx::DictIterType type = AcRx::kDictSorted) = 0;

    virtual Adesk::Boolean deletesObjects() const = 0;
    virtual Adesk::Boolean isCaseSensitive() const = 0;
    virtual Adesk::Boolean isSorted() const = 0;
};

extern "C" ACBASE_PORT AcRxDictionary* acrxSysRegistry();

inline AcRxObject* AcRxDictionary::atPut(const ACHAR* key, AcRxObject* pObj)
{ Adesk::UInt32 temp; return atPut(key, pObj, temp); }

#define acrxClassDictionary \
AcRxDictionary::cast(acrxSysRegistry()->at(ACRX_CLASS_DICTIONARY))

#define acrxServiceDictionary \
AcRxDictionary::cast(acrxSysRegistry()->at(ACRX_SERVICE_DICTIONARY))

#pragma pack (pop)
#endif
