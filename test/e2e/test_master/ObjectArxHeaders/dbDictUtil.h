#ifndef AD_DBDICTUTIL_H
#  define AD_DBDICTUTIL_H	1
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#  include <stddef.h>
#  include "dbdict.h"
#  include "AcString.h"
namespace AcDbDictUtil
{
  inline Acad::ErrorStatus dictionaryNameAt(AcString& name, AcDbObjectId itemId, AcDbObjectId ownerDictId)
  {
    name.setEmpty();
    AcDbDictionary* pDict;
    Acad::ErrorStatus es = ::acdbOpenObject(pDict, ownerDictId, AcDb::kForRead);
    if (es == Acad::eOk)
    {
      es = pDict->nameAt(itemId, name);
      pDict->close();
    }
    return es;
  }
  inline Acad::ErrorStatus dictionaryNameAt(ACHAR*& pName, AcDbObjectId itemId, AcDbObjectId ownerDictId)
  {
    AcString sName;
    return ::acutAcStringToAChar(sName, pName, AcDbDictUtil::dictionaryNameAt(sName, itemId, ownerDictId));
  }
  inline Acad::ErrorStatus dictionaryNameAt(AcString& name, AcDbObjectId itemId)
  {
    name.setEmpty();
    AcDbObject* pObject;
    Acad::ErrorStatus es = ::acdbOpenObject(pObject, itemId, AcDb::kForRead);
    if (es != Acad::eOk)
    {
      return es;
    }
    const AcDbObjectId dictId = pObject->ownerId();
    es = pObject->close();
    return AcDbDictUtil::dictionaryNameAt(name, itemId, dictId);
  }
  inline Acad::ErrorStatus dictionaryNameAt(ACHAR*& pName, AcDbObjectId itemId)
  {
    AcString sName;
    return ::acutAcStringToAChar(sName, pName, AcDbDictUtil::dictionaryNameAt(sName, itemId));
  }
  inline Acad::ErrorStatus dictionaryGetAt(AcDbObjectId& id, const ACHAR* name, AcDbObjectId ownerDictId)
  {
    id.setNull();
    AcDbDictionary* pDict;
    Acad::ErrorStatus es = ::acdbOpenObject(pDict, ownerDictId, AcDb::kForRead);
    if (es == Acad::eOk)
    {
      es = pDict->getAt(name, id);
      pDict->close();
    }
    return es;
  }
#  define DBDICTUTIL_MAKE_DICTIONARY_UTILS(LOWERNAME, UPPERNAME)	 \
inline Acad::ErrorStatus \
get##UPPERNAME##Id(AcDbObjectId& id, const ACHAR* name, AcDbDatabase* pDb) \
{ \
    id.setNull(); \
    if (pDb == nullptr) \
        return Acad::eNoDatabase; \
    return AcDbDictUtil::dictionaryGetAt(id, name, pDb->LOWERNAME##DictionaryId()); \
} \
inline Acad::ErrorStatus \
get##UPPERNAME##Name(AcString& name, AcDbObjectId itemId) \
{ \
    name.setEmpty(); \
    AcDbDatabase* pDb = itemId.database(); \
    if (pDb == nullptr) \
        return Acad::eNoDatabase; \
    return AcDbDictUtil::dictionaryNameAt(name, itemId, pDb->LOWERNAME##DictionaryId()); \
} \
inline Acad::ErrorStatus \
get##UPPERNAME##Name(ACHAR*& name, AcDbObjectId itemId) \
{ \
    AcString sName; \
    return ::acutAcStringToAChar(sName, name, AcDbDictUtil::get##UPPERNAME##Name(sName, itemId)); \
} \
inline bool \
has##UPPERNAME(const ACHAR* name, AcDbDatabase* pDb) \
{ \
    AcDbObjectId id; \
    return AcDbDictUtil::get##UPPERNAME##Id(id, name, pDb) == Acad::eOk; \
}
#  undef DBDICTUTIL_MAKE_DICTIONARY_UTILS
}
#endif
