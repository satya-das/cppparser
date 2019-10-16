//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBINDEX_H
#  define AD_DBINDEX_H
#  include "dbmain.h"
#  pragma  pack(push, 8)
class AcDbIndexIterator;
class AcDbFilter;
class AcDbIndexUpdateData;
class AcDbBlockChangeIterator;
class AcDbFilteredBlockIterator;
class AcDbFilter;
class AcDbImpDatabase;
class AcDbBlockTableRecord;
class AcDbBlockChangeIterator;
class AcDbIndexUpdateData;
class AcDbIndex : public AcDbObject
{
  ACDB_DECLARE_MEMBERS(AcDbIndex);
public:
  AcDbIndex();
  virtual ~AcDbIndex();
  virtual AcDbFilteredBlockIterator* newIterator(const AcDbFilter* pFilter) const;
  virtual Acad::ErrorStatus rebuildFull(AcDbIndexUpdateData* pIdxData);
  virtual AcDbObjectId objectBeingIndexedId() const;
  void setLastUpdatedAt(const AcDbDate& time);
  AcDbDate lastUpdatedAt() const;
  void setLastUpdatedAtU(const AcDbDate& time);
  AcDbDate lastUpdatedAtU() const;
  Adesk::Boolean isUptoDate() const;
protected:
  virtual Acad::ErrorStatus rebuildModified(AcDbBlockChangeIterator* iter);
  friend class AcDbImpIndex;
  friend Acad::ErrorStatus processBTRIndexObjects(AcDbBlockTableRecord* pBTR, int indexCtlVal, AcDbBlockChangeIterator* pBlkChgIter, AcDbIndexUpdateData* pIdxUpdData);
};
class AcDbFilteredBlockIterator
{
public:
  AcDbFilteredBlockIterator()
  {
  }
  virtual ~AcDbFilteredBlockIterator()
  {
  }
  virtual Acad::ErrorStatus start() = 0;
  virtual AcDbObjectId next() = 0;
  virtual AcDbObjectId id() const = 0;
  virtual Acad::ErrorStatus seek(AcDbObjectId id) = 0;
  virtual double estimatedHitFraction() const = 0;
  virtual Acad::ErrorStatus accepts(AcDbObjectId id, Adesk::Boolean& idPassesFilter) const = 0;
  virtual Adesk::Boolean buffersForComposition() const;
  virtual Acad::ErrorStatus addToBuffer(AcDbObjectId id);
};
class AcDbCompositeFilteredBlockIterator
{
private:
  AcDbCompositeFilteredBlockIterator(const AcDbCompositeFilteredBlockIterator& copyFrom);
protected:
  AcDbCompositeFilteredBlockIterator()
  {
  }
public:
  virtual ~AcDbCompositeFilteredBlockIterator()
  {
  }
  virtual Acad::ErrorStatus init(AcDbFilter* const * ppFilters, int numFilters, const AcDbBlockTableRecord* pBtr) = 0;
  virtual Acad::ErrorStatus start() = 0;
  virtual AcDbObjectId next() = 0;
  virtual AcDbObjectId id() const = 0;
  virtual Acad::ErrorStatus seek(AcDbObjectId id) = 0;
  static AcDbCompositeFilteredBlockIterator* newIterator();
};
class AcDbBlockTableRecord;
class AcDbBlockReference;
namespace AcDbIndexFilterManager
{
  Acad::ErrorStatus updateIndexes(AcDbDatabase* pDb);
  Acad::ErrorStatus addIndex(AcDbBlockTableRecord* pBTR, AcDbIndex* pIndex);
  Acad::ErrorStatus removeIndex(AcDbBlockTableRecord* pBTR, const AcRxClass* key);
  Acad::ErrorStatus getIndex(const AcDbBlockTableRecord* pBTR, const AcRxClass* key, AcDb::OpenMode readOrWrite, AcDbIndex*& pIndex);
  Acad::ErrorStatus getIndex(const AcDbBlockTableRecord* pBTR, int index, AcDb::OpenMode readOrWrite, AcDbIndex*& pIndex);
  int numIndexes(const AcDbBlockTableRecord* pBtr);
  Acad::ErrorStatus addFilter(AcDbBlockReference* pBlkRef, AcDbFilter* pFilter);
  Acad::ErrorStatus removeFilter(AcDbBlockReference* pBlkRef, const AcRxClass* key);
  Acad::ErrorStatus getFilter(const AcDbBlockReference* pRef, const AcRxClass* key, AcDb::OpenMode readOrWrite, AcDbFilter*& pFilter);
  Acad::ErrorStatus getFilter(const AcDbBlockReference* pRef, int index, AcDb::OpenMode readOrWrite, AcDbFilter*& pFilter);
  int numFilters(const AcDbBlockReference* pBlkRef);
}
class AcDbHandleTable;
class AcDbHandleTableIterator;
class AcDbIndexUpdateData
{
public:
  enum UpdateFlags
  {
    kModified = 1,
    kDeleted = 2,
    kProcessed = 4,
    kUnknownKey = 8
  };
  Acad::ErrorStatus addId(AcDbObjectId id);
  Acad::ErrorStatus setIdFlags(AcDbObjectId id, Adesk::UInt8 flags);
  Acad::ErrorStatus setIdData(AcDbObjectId id, Adesk::ULongPtr data);
  Acad::ErrorStatus getIdData(AcDbObjectId id, Adesk::ULongPtr& data) const;
  Acad::ErrorStatus getIdFlags(AcDbObjectId id, Adesk::UInt8& flags) const;
  Acad::ErrorStatus getFlagsAndData(AcDbObjectId id, Adesk::UInt8& flags, Adesk::ULongPtr& data) const;
private:
  AcDbIndexUpdateData();
  ~AcDbIndexUpdateData();
  AcDbIndexUpdateData(const AcDbIndexUpdateData&);
  AcDbHandleTable* mpTable;
  friend class AcDbIndexUpdateDataIterator;
  friend class AcDbImpDatabase;
};
class AcDbIndexUpdateDataIterator
{
public:
  AcDbIndexUpdateDataIterator(const AcDbIndexUpdateData* p);
  ~AcDbIndexUpdateDataIterator();
  void start();
  void next();
  bool done();
  Acad::ErrorStatus currentData(AcDbObjectId& id, Adesk::UInt8& flags, Adesk::ULongPtr& data) const;
private:
  AcDbHandleTableIterator* mpIter;
};
class AcDbBlockChangeIterator
{
private:
  AcDbBlockChangeIterator();
  AcDbBlockChangeIterator(const AcDbBlockChangeIterator&);
  AcDbBlockChangeIterator(AcDbObjectId btrId, AcDbIndexUpdateData* pIdxUpdData);
  ~AcDbBlockChangeIterator();
public:
  void start();
  AcDbObjectId id() const;
  void next();
  bool done();
  Acad::ErrorStatus curIdInfo(AcDbObjectId& id, Adesk::UInt8& flags, Adesk::ULongPtr& data) const;
  Acad::ErrorStatus setCurIdInfo(Adesk::UInt8 flags, Adesk::ULongPtr data);
  AcDbIndexUpdateData* updateData() const;
  void clearProcessedFlags();
private:
  AcDbIndexUpdateData* mpIds;
  AcDbObjectId mBTRId;
  AcDbIndexUpdateDataIterator* mpIter;
  friend class AcDbImpDatabase;
};
#  pragma  pack(pop)
#endif
