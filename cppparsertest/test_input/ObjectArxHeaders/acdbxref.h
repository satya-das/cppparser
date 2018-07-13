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
//
//      AcDbXref.h
//      This file contains the definition of the functions used to handle
//      xrefs in DBX.
//
//
//   acdbResolveCurrentXRefs --
//   This function is used to resolve xrefs at drawing load.
//   acdbResolveCurrentXRefs() will get and load xref database
//   files and merge the symbol tables from the xrefs into the
//   symbol tables of the host drawing. The host database should
//   not be an xref in another drawing. If this is the case, the
//   function does nothing.  The acdbHostApplicationServices methods
//   isRemoteFile(), getRemoteFile(), mapFile(), and findFile()
//   will be used by acdbResolveCurrentXRefs() to access the xref
//   files if these functions are provided. Otherwise, the xrefs
//   will be accessed at the path assigned to them when the host
//   drawing was saved.
//
//   Some functionality is not included in the xref resolve. This includes:
//       Xref notification events
//       Xref message logging
//       Xref lazy loading (The xref drawing will be opened in mode
//                          SH_DENYNO and AcDbDatabase::closeInput()
//                          will be called after the drawing is read.)
//
//    Note  This function supports xref resolution, but not xref
//    database editing. You will not be able to reliably query or
//    modify some elements of the xref databases. Nor will you be
//    able to save your changes because the AcDbDatabase methods
//    needed to restore the integrity of xref databases,
//    restoreOriginalXrefSymbols() and restoreForwardingXrefSymbols(),
//    are not implemented for ObjectDBX.


#pragma once

#include "AdAChar.h"
#include "xgraph.h"

Acad::ErrorStatus acdbResolveCurrentXRefs(AcDbDatabase* pHostDb,
    bool useThreadEngine = true, bool doNewOnly = false);

/* acdbAttachXref --
   This function is used to attach a new xref to the specified file
   (pFilename) to a given database (pDb)..
   A new block table record with the name specified by pBlockName
   will be created and resolved as an external reference.  
   The id of the new record will be set into xrefBlkId.
*/
Acad::ErrorStatus acdbAttachXref(AcDbDatabase* pHostDb,
                                 const ACHAR * pFilename, 
                                 const ACHAR * pBlockName,
                                 AcDbObjectId& xrefBlkId);

/* acdbOverlayhXref --
   This function is used to overlay a new xref to the specified file
   (pFilename) to a given database (pDb)..
   A new block table record with the name specified by pBlockName
   will be created and resolved as an external reference and flagged
   as an overlay.  The id of the new record will be set into xrefBlkId.
*/
Acad::ErrorStatus acdbOverlayXref(AcDbDatabase* pHostDb,
                                  const ACHAR * pFilename,
                                  const ACHAR * pBlockName,
                                  AcDbObjectId& xrefBlkId);

/* acdbDetachXref --
   This function is used to detach a specified xref (xrefBlkId) from the
   given database (pDb).   Note, references to the xref should be
   erased prior to using this function.
*/

Acad::ErrorStatus acdbDetachXref(AcDbDatabase* pHostDb, 
                           const AcDbObjectId& xrefBlkId);



Acad::ErrorStatus acdbUnloadXrefs(AcDbDatabase*      pHostDb,
                            const AcDbObjectIdArray& xrefBlkIds,
                            const bool               bQuiet = true);

Acad::ErrorStatus acdbReloadXrefs(AcDbDatabase*      pHostDb,
                            const AcDbObjectIdArray& xrefBlkIds,
                                  bool               bQuiet = true);

Acad::ErrorStatus acdbBindXrefs(AcDbDatabase*      pHostDb,
                          const AcDbObjectIdArray& xrefBlkIds, 
                          const bool               bInsertBind,
                          const bool               bAllowUnresolved = false,
                          const bool               bQuiet = true);

Acad::ErrorStatus acdbXBindXrefs(AcDbDatabase*     pHostDb,
                           const AcDbObjectIdArray xrefSymbolIds,
                           const bool              bInsertBind,
                           const bool              bQuiet = true);


// This function does nothing in an AutoCAD based host environment.
// In a non-AutoCAD host environment this function will delete the
// database pointed to by pHostDb and will clean up some AcDbGlobals
// values.
//
void acdbReleaseHostDwg(AcDbDatabase* pHostDb);

Acad::ErrorStatus
acdbGetHostDwgXrefGraph(AcDbDatabase* pHostDb, AcDbXrefGraph& graph,
    Adesk::Boolean includeGhosts = Adesk::kFalse);


// Class AcDbXrefObjectId
//
// The purpose of this class is to provide a convenient method for referring
// to a specific AcDbObject within an XREF'd database.  It is persistant
// across drawing sessions, though the current DWG freeze requires that
// it be serialized out through extended data of some form or another.

class AcDbXrefObjectId {
public:

    AcDbXrefObjectId();
    AcDbXrefObjectId(const AcDbXrefObjectId& other);

    AcDbXrefObjectId& operator= (const AcDbXrefObjectId& other);
    bool operator== (const AcDbXrefObjectId& other) const;
    bool operator!= (const AcDbXrefObjectId& other) const;

    bool isValid(void) const;
    bool isXref(void) const { return !m_handle.isNull(); }
    bool isNull(void) const { return m_localId.isNull(); }

    Acad::ErrorStatus setNull(void);

    Acad::ErrorStatus setXrefId(AcDbObjectId xrefBlkId, const AcDbHandle & hObject);
    Acad::ErrorStatus getXrefId(AcDbObjectId& xrefBlkId, AcDbHandle& hObject) const;

    Acad::ErrorStatus setLocalId(AcDbObjectId objId);
    Acad::ErrorStatus getLocalId(AcDbObjectId& objId) const;

    Acad::ErrorStatus resolveObjectId(AcDbObjectId& id) const;

    Acad::ErrorStatus serializeToResbuf(resbuf*& pResBuf, resbuf*& pEndOfChain) const;
    Acad::ErrorStatus serializeFromResbuf(const resbuf* pResBuf, resbuf*& pNextInChain);

private:

    AcDbObjectId        m_localId;      // if m_handle.isNull(), this is a local objId
                                        // otherwise, it is the block table record of the xref

    AcDbHandle          m_handle;       // handle of the object we refer
                                        // to within the Xref
};

