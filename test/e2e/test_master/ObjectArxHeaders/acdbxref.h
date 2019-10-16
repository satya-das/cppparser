//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "AdAChar.h"
#include "xgraph.h"
Acad::ErrorStatus acdbResolveCurrentXRefs(AcDbDatabase* pHostDb, bool useThreadEngine = true, bool doNewOnly = false);
Acad::ErrorStatus acdbAttachXref(AcDbDatabase* pHostDb, const ACHAR* pFilename, const ACHAR* pBlockName, AcDbObjectId& xrefBlkId);
Acad::ErrorStatus acdbOverlayXref(AcDbDatabase* pHostDb, const ACHAR* pFilename, const ACHAR* pBlockName, AcDbObjectId& xrefBlkId);
Acad::ErrorStatus acdbDetachXref(AcDbDatabase* pHostDb, const AcDbObjectId& xrefBlkId);
Acad::ErrorStatus acdbUnloadXrefs(AcDbDatabase* pHostDb, const AcDbObjectIdArray& xrefBlkIds, const bool bQuiet = true);
Acad::ErrorStatus acdbReloadXrefs(AcDbDatabase* pHostDb, const AcDbObjectIdArray& xrefBlkIds, bool bQuiet = true);
Acad::ErrorStatus acdbBindXrefs(AcDbDatabase* pHostDb, const AcDbObjectIdArray& xrefBlkIds, const bool bInsertBind, const bool bAllowUnresolved = false, const bool bQuiet = true);
Acad::ErrorStatus acdbXBindXrefs(AcDbDatabase* pHostDb, const AcDbObjectIdArray xrefSymbolIds, const bool bInsertBind, const bool bQuiet = true);
void acdbReleaseHostDwg(AcDbDatabase* pHostDb);
Acad::ErrorStatus acdbGetHostDwgXrefGraph(AcDbDatabase* pHostDb, AcDbXrefGraph& graph, Adesk::Boolean includeGhosts = Adesk::kFalse);
class AcDbXrefObjectId
{
public:
  AcDbXrefObjectId();
  AcDbXrefObjectId(const AcDbXrefObjectId& other);
  AcDbXrefObjectId& operator=(const AcDbXrefObjectId& other);
  bool operator==(const AcDbXrefObjectId& other) const;
  bool operator!=(const AcDbXrefObjectId& other) const;
  bool isValid(void) const;
  bool isXref(void) const
  {
    return !m_handle.isNull();
  }
  bool isNull(void) const
  {
    return m_localId.isNull();
  }
  Acad::ErrorStatus setNull(void);
  Acad::ErrorStatus setXrefId(AcDbObjectId xrefBlkId, const AcDbHandle& hObject);
  Acad::ErrorStatus getXrefId(AcDbObjectId& xrefBlkId, AcDbHandle& hObject) const;
  Acad::ErrorStatus setLocalId(AcDbObjectId objId);
  Acad::ErrorStatus getLocalId(AcDbObjectId& objId) const;
  Acad::ErrorStatus resolveObjectId(AcDbObjectId& id) const;
  Acad::ErrorStatus serializeToResbuf(resbuf*& pResBuf, resbuf*& pEndOfChain) const;
  Acad::ErrorStatus serializeFromResbuf(const resbuf* pResBuf, resbuf*& pNextInChain);
private:
  AcDbObjectId m_localId;
  AcDbHandle m_handle;
};
