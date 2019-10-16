#ifndef AD_DBDICT_H
#  define AD_DBDICT_H
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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
  virtual bool name(AcString& sName) const = 0;
  template <typename ObjType>
  Acad::ErrorStatus getObject(ObjType*& pObject, AcDb::OpenMode mode = AcDb::kForRead)
  {
    const AcDbObjectId id = this->objectId();
    return ::acdbOpenObject(pObject, id, mode, false);
  }
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
  Acad::ErrorStatus getAt(const ACHAR* entryName, AcDbObject*& entryObj, AcDb::OpenMode mode = AcDb::kForRead)
  {
    return this->getAt<AcDbObject>(entryName, entryObj, mode);
  }
  Acad::ErrorStatus getAt(const ACHAR* entryName, AcDbObjectId& entryId) const;
  Acad::ErrorStatus nameAt(AcDbObjectId objId, ACHAR*& name) const;
  ACDBCORE2D_PORT Acad::ErrorStatus nameAt(AcDbObjectId objId, AcString& sName) const;
  bool has(const ACHAR* entryName) const;
  bool has(AcDbObjectId objId) const;
  Adesk::UInt32 numEntries() const;
  Acad::ErrorStatus remove(const ACHAR* key);
  Acad::ErrorStatus remove(const ACHAR* key, AcDbObjectId& returnId);
  Acad::ErrorStatus remove(AcDbObjectId objId);
  bool setName(const ACHAR* oldName, const ACHAR* newName);
  Acad::ErrorStatus setAt(const ACHAR* srchKey, AcDbObject* newValue, AcDbObjectId& retObjId);
  bool isTreatElementsAsHard() const;
  void setTreatElementsAsHard(bool doIt);
  virtual void setMergeStyle(AcDb::DuplicateRecordCloning style);
  AcDbDictionaryIterator* newIterator() const;
  virtual Acad::ErrorStatus subErase(Adesk::Boolean pErasing = Adesk::kTrue) override;
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
  virtual AcDb::DuplicateRecordCloning mergeStyle() const override;
  virtual void goodbye(const AcDbObject* pObject) override;
  virtual void erased(const AcDbObject* pObject, bool bErasing) override;
  virtual Acad::ErrorStatus decomposeForSave(AcDb::AcDbDwgVersion ver, AcDbObject*& replaceObj, AcDbObjectId& replaceId, Adesk::Boolean& exchangeXData) override;
protected:
  virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
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
