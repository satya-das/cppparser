#ifndef AD_DBDICTUTIL_H
#define AD_DBDICTUTIL_H 1
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
//  DESCRIPTION:
//
//   The following are some dictionary utility functions similar 
//   to those defined for symbol tables in dbsymutl.h
//   NOTE: These utils have the same usage guidelines as the symbol 
//   table versions. That is; These functions are very handy for 
//   quick one-time access to the name or id of a dictionary entry.
//   On the other hand; if you need to make multiple accesses to 
//   a given dictionary, then avoid the overhead of these functions
//   and open the dictionary directly.
//
// -----------------------
// Get the ID of an item 
// -----------------------
//  General purpose:
//    Acad::ErrorStatus 
//      AcDbDictUtil::dictionaryGetAt(AcDbObjectId& id, const ACHAR* name, AcDbObjectId ownerDictId);
//
//  Specific:
//    Acad::ErrorStatus 
//      AcDbDictUtil::getGroupId(AcDbObjectId& id, const ACHAR* name, AcDbDatabase* pDb);
//     also...
//       getColorId
//       getLayoutId
//       getMaterialId
//       getMLStyleId
//       getNamedObjectId
//       getPlotSettingsId
//       getPlotStyleNameId
//       getScaleListId
//       getTableStyleId
//       getVisualStyleId
//
// -----------------------
// Get the NAME/KEY of an item:
// -----------------------
//  General purpose:
//    Acad::ErrorStatus 
//      AcDbDictUtil::dictionaryNameAt(AcString & sName, AcDbObjectId itemId, AcDbObjectId ownerDictId);
//  or...
//    Acad::ErrorStatus 
//      AcDbDictUtil::dictionaryNameAt(AcString & sName, AcDbObjectId itemId);
//
//  Specific:
//    Acad::ErrorStatus 
//      AcDbDictUtil::getGroupName(AcString & sName, AcDbObjectId id);
//       also...
//        getColorName
//        getLayoutName
//        getMaterialName
//        getMLStyleName
//        getNamedObjectName
//        getPlotSettingsName
//        getPlotStyleNameName
//        getScaleListName
//        getTableStyleName
//        getVisualStyleName
//
//  NOTE: There are also "get name" overloads which take ACHAR *& args and allocate a
//        new buffer for the returned string.
//        In this case, the caller is responsible for deallocating the buffer.
//        These overloads are deprecated and should no longer be used.
//
// -----------------------
// Check for existence
// -----------------------
//  
//        bool hasGroup(const ACHAR* name, AcDbDatabase* pDb);
//       also...
//        hasColor
//        hasLayout
//        hasMaterial
//        hasMLStyle
//        hasNamedObject
//        hasPlotSettings
//        hasPlotStyleName
//        hasScaleList
//        hasTableStyle
//        hasVisualStyle
//

#include <stddef.h>
#include "dbdict.h"
#include "AcString.h"

namespace AcDbDictUtil
{

// Given an item id and a dictionary (owner) id, get the item's name in that dictionary
inline Acad::ErrorStatus 
dictionaryNameAt(AcString& name, AcDbObjectId itemId, AcDbObjectId ownerDictId)
{
    name.setEmpty();
    AcDbDictionary* pDict;
    Acad::ErrorStatus es = ::acdbOpenObject(pDict, ownerDictId, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pDict->nameAt(itemId, name);
        pDict->close();
    }
    return es;
}

// This overload which allocates a string buffer is deprecated and will be removed
// in a future release. Please use the one that takes an AcString & arg
inline Acad::ErrorStatus 
dictionaryNameAt(ACHAR*& pName, AcDbObjectId itemId, AcDbObjectId ownerDictId)
{
    AcString sName;
    return ::acutAcStringToAChar(sName, pName,
                                 AcDbDictUtil::dictionaryNameAt(sName, itemId, ownerDictId));
}

// Given an item id, get the item's name in its owning dictionary
// Note: If you already know the owner of itemId, then call the overload above
//       avoid the overhead of opening the item to get its owner id
inline Acad::ErrorStatus 
dictionaryNameAt(AcString& name, AcDbObjectId itemId)
{
    name.setEmpty();
    AcDbObject* pObject;
    Acad::ErrorStatus es = ::acdbOpenObject(pObject, itemId, AcDb::kForRead);
    if (es != Acad::eOk)
        return es;
    const AcDbObjectId dictId = pObject->ownerId(); //get the owner id
    es = pObject->close();
    return AcDbDictUtil::dictionaryNameAt(name, itemId, dictId);
}

// This overload which allocates a string buffer is deprecated and will be removed
// in a future release. Please use the above overloads that take an AcString & arg
inline Acad::ErrorStatus 
dictionaryNameAt(ACHAR*& pName, AcDbObjectId itemId)
{
    AcString sName;
    return ::acutAcStringToAChar(sName, pName, AcDbDictUtil::dictionaryNameAt(sName, itemId));
}

// Given a dictionary and a key name, retrieve the id for that entry.
inline Acad::ErrorStatus
dictionaryGetAt(AcDbObjectId& id, const ACHAR* name, AcDbObjectId ownerDictId)
{
    id.setNull();
    AcDbDictionary* pDict;
    Acad::ErrorStatus es = ::acdbOpenObject(pDict, ownerDictId, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pDict->getAt(name, id);
        pDict->close();
    }
    return es;
}

// Now define functions of this form:
//   Acad::ErrorStatus AcDbDictUtil::getGroupId(AcDbObjectId &id, const ACHAR *name,
//                                              AcDbDatabase *pDb);
//   Acad::ErrorStatus AcDbDictUtil::getGroupName(AcString &sName, AcDbObjectId itemId);
//   Acad::ErrorStatus AcDbDictUtil::getGroupName(ACHAR *&pName, AcDbObjectId itemId); // DEPRECATED
//   bool AcDbDictUtil::hasGroup(const ACHAR *name, AcDbDatabase *pDb);
//
// Note that the overload of the form getGroupName(ACHAR *& pName, AcDbObjectId id) is
// deprecated and will be removed in a future release.
// Please use the overload taking "AcString &" arg instead
//
#define DBDICTUTIL_MAKE_DICTIONARY_UTILS(LOWERNAME, UPPERNAME) \
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

DBDICTUTIL_MAKE_DICTIONARY_UTILS( color,         Color)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( group,         Group)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( layout,        Layout)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( material,      Material)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( mLStyle,       MLStyle)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( namedObjects,  NamedObjects)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( plotSettings,  PlotSettings)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( plotStyleName, PlotStyleName)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( scaleList,     ScaleList)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( tableStyle,    TableStyle)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( visualStyle,   VisualStyle)

#undef DBDICTUTIL_MAKE_DICTIONARY_UTILS

} // end AcDbDictUtil namespace

#endif // !AD_DBDICTUTIL_H
