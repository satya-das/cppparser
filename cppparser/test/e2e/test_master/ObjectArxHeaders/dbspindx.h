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
// (Rights in Technical Data and Computer Software), as applicable.
//
// Concrete implementation for 3d spatial indexing.
//
#ifndef AD_DBSPINDX_H
#  define AD_DBSPINDX_H
#  include "dbindex.h"
#  pragma  pack (push, 8)
class AcDbSpatialIndex : public AcDbIndex
{
  ACDB_DECLARE_MEMBERS(AcDbSpatialIndex);
public:
  AcDbSpatialIndex();
  virtual ~AcDbSpatialIndex();
  AcDbFilteredBlockIterator* newIterator(const AcDbFilter* pFilter) const override;
  Acad::ErrorStatus rebuildFull(AcDbIndexUpdateData* pIdxData) override;
protected:
  Acad::ErrorStatus rebuildModified(AcDbBlockChangeIterator* iter) override;
};
class AcDbImpSpatialIndexIterator;
class AcDbSpatialFilter;
class AcDbSpatialIndexIterator : public AcDbFilteredBlockIterator
{
public:
  AcDbSpatialIndexIterator(const AcDbSpatialIndex* pIndex, const AcDbSpatialFilter* pFilter);
  virtual ~AcDbSpatialIndexIterator();
  virtual Acad::ErrorStatus start();
  virtual AcDbObjectId next();
  virtual AcDbObjectId id() const;
  virtual Acad::ErrorStatus seek(AcDbObjectId id);
  virtual double estimatedHitFraction() const;
  virtual Acad::ErrorStatus accepts(AcDbObjectId id, Adesk::Boolean& stat) const;
private:
  AcDbImpSpatialIndexIterator* mpImpIter;
};
#  pragma  pack (pop)
#endif
