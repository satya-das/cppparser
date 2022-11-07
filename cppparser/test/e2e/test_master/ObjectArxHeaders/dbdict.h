#ifndef AD_DBDICT_H
#  define AD_DBDICT_H
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
// dbdict.h
//
// DESCRIPTION:  Class header for AcDbDictionary, a database-resident
//               dictionary.  A concerete API class whose implementation
//               can be inherited at runtime.
//
//               An instance of this class represents a single
//               "Drawing Symbol Table"-like object, to which
//               AcDbObject instances can be added, accessed and
//               removed.
//
//               Object pointers retrieved from the database represent
//               indivudual object are currently opened in the requested
//               mode.
//               The return status indicates the status for opening
//               the entry object.  If the status is not AcDb::eOpenOK,
//               the returned pointer is NULL.
//
// CONTRACTS:
//               Objects added to an AcDbDictionary instance must not
//               have a presence in the database, i.e. they must have
//               null handles.
//
//               Objects removed or replaced in the dictionary are 
//               erased via AcDbObject::erase().
//
#  include "dbmain.h"
#  pragma  pack(push, 8)
class AcDbImpDictionary;
class AcString;
class ADESK_NO_VTABLE AcDbDictionaryIterator : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbDictionaryIterator);
  AcDbDictionaryIterator(const AcDbDictionaryIterator&) = delete;
  AcDbDictionaryIterator& operator =(const AcDbDictionaryIterator&);
  virtual ~AcDbDictionaryIterator()
  {
  }
  virtual const ACHAR* name() const = 0;
    // Sets sName and returns true if not done. Else clears sName and returns false
  virtual bool name(AcString& sName) const = 0;
  template <typename ObjType>
  Acad::ErrorStatus getObject(ObjType*& pObject, AcDb::OpenMode mode = AcDb::kForRead)
  {
    const AcDbObjectId id = this->objectId();
    return ::acdbOpenObject(pObject, id, mode, false);
  }
    // Needed for cases where a smart ptr is passed in
  Acad::ErrorStatus getObject(AcDbObject*& pObject, AcDb::OpenMode mode = AcDb::kForRead)
  {
    return this->getObject<AcDbObject>(pObject, mode);
  }
  virtual AcDbObjectId objectId() const = 0;
  virtual bool done() const = 0;
  virtual bool next() = 0;
  virtual bool setPosition(AcDbObjectId objId) = 0;
protected:
  AcDbDictionaryIterator()
  {
  }
};
class AcDbDictionary : public AcDbObject
{
  ACDB_DECLARE_MEMBERS(AcDbDictionary);
public:
  AcDbDictionary();
  virtual ~AcDbDictionary();
  AcDbDictionary(const AcDbDictionary&) = delete;
  AcDbDictionary& operator =(const AcDbDictionary&);
    // Get an entry by name.
    //
  template <typename ObjType>
  Acad::ErrorStatus getAt(const ACHAR* entryName, ObjType*& entryObj, AcDb::OpenMode mode = AcDb::kForRead) const
  {
    entryObj = nullptr;
    AcDbObjectId id;
    Acad::ErrorStatus es = this->getAt(entryName, id);
    if (es == Acad::eOk)
    {
      es = ::acdbOpenObject(entryObj, id, mode, false);
    }
    return es;
  }
    // Needed for cases where a smart ptr is passed in
  Acad::ErrorStatus getAt(const ACHAR* entryName, AcDbObject*& entryObj, AcDb::OpenMode mode = AcDb::kForRead)
  {
    return this->getAt<AcDbObject>(entryName, entryObj, mode);
  }
  Acad::ErrorStatus getAt(const ACHAR* entryName, AcDbObjectId& entryId) const;
    // Find name corresponding to object id.
    //
  Acad::ErrorStatus nameAt(AcDbObjectId objId, ACHAR*& name) const;
  ACDBCORE2D_PORT Acad::ErrorStatus nameAt(AcDbObjectId objId, AcString& sName) const;
    // Query contents of dictionary
    //
  bool has(const ACHAR* entryName) const;
  bool has(AcDbObjectId objId) const;
  Adesk::UInt32 numEntries() const;
    // Remove entries.
    //
  Acad::ErrorStatus remove(const ACHAR* key);
  Acad::ErrorStatus remove(const ACHAR* key, AcDbObjectId& returnId);
  Acad::ErrorStatus remove(AcDbObjectId objId);
    // Reset an entry.
    //
  bool setName(const ACHAR* oldName, const ACHAR* newName);
  Acad::ErrorStatus setAt(const ACHAR* srchKey, AcDbObject* newValue, AcDbObjectId& retObjId);
    // Test/Set treatment of elements.
    //
  bool isTreatElementsAsHard() const;
  void setTreatElementsAsHard(bool doIt);
  virtual void setMergeStyle(AcDb::DuplicateRecordCloning style);
    // Get an iterator for this dictionary.
    //
  AcDbDictionaryIterator* newIterator() const;
    // AcDbObject Protocol
    //
  Acad::ErrorStatus subErase(Adesk::Boolean pErasing = Adesk::kTrue) override;
  Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
  Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
  Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
  Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
  AcDb::DuplicateRecordCloning mergeStyle() const override;
    // Support for persistent reactor to annotation.
    //
  void goodbye(const AcDbObject* pObject) override;
  void erased(const AcDbObject* pObject, bool bErasing) override;
    // Support for saving to previous releases' formats.
    //
  Acad::ErrorStatus decomposeForSave(AcDb::AcDbDwgVersion ver, AcDbObject*& replaceObj, AcDbObjectId& replaceId, Adesk::Boolean& exchangeXData) override;
protected:
  Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
// This overload is deprecated and will be removed. Please use the one
// taking an AcString & arg instead
inline Acad::ErrorStatus AcDbDictionary::nameAt(AcDbObjectId objId, ACHAR*& pName) const
{
  AcString sName;
  return ::acutAcStringToAChar(sName, pName, this->nameAt(objId, sName));
}
inline bool AcDbDictionary::has(const ACHAR* entryName) const
{
  AcDbObjectId id;
  return this->getAt(entryName, id) == Acad::eOk;
}
inline Acad::ErrorStatus AcDbDictionary::remove(const ACHAR* entryName)
{
  AcDbObjectId id;
  return this->remove(entryName, id);
}
#  pragma  pack(pop)
#endif
