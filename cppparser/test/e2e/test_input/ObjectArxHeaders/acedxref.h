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
//   acedxref.h  -  XREF API Definitions
    


#ifndef   _ACEDXREF_H
#define   _ACEDXREF_H
#pragma pack (push, 8)

class AcDbBlockTableRecord;

Acad::ErrorStatus
acedXrefAttach(const ACHAR*           XrefPathname,
               const ACHAR*           XrefBlockname,
                     AcDbObjectId*   pXrefBTRid       = NULL,
                     AcDbObjectId*   pXrefRefid       = NULL,
               const AcGePoint3d*    pXrefInsertPt    = NULL,
               const AcGeScale3d*    pXrefScale       = NULL,
               const double*         pXrefRotateAngle = NULL,
               const bool            bQuiet           = true,
                     AcDbDatabase*   pHostDb          = NULL,
               const wchar_t*       wszPassword       = NULL);

Acad::ErrorStatus
acedXrefOverlay(const ACHAR*           XrefPathname,
                const ACHAR*           XrefBlockname,
                      AcDbObjectId*   pXrefBTRid       = NULL,
                      AcDbObjectId*   pXrefRefid       = NULL,
                const AcGePoint3d*    pXrefInsertPt    = NULL,
                const AcGeScale3d*    pXrefScale       = NULL,
                const double*         pXrefRotateAngle = NULL,
                const bool            bQuiet           = true,
                      AcDbDatabase*   pHostDb          = NULL,
                const wchar_t*        wszPassword      = NULL);

Acad::ErrorStatus
acedXrefUnload(const ACHAR*           XrefBlockname,
               const bool            bQuiet        = true,
                     AcDbDatabase*   pHostDb       = NULL);
Acad::ErrorStatus
acedXrefDetach(const ACHAR*           XrefBlockname,
               const bool            bQuiet        = true,
                     AcDbDatabase*   pHostDb       = NULL);
Acad::ErrorStatus
acedXrefReload(const ACHAR*           XrefBlockname,
               const bool            bQuiet        = true, 
                     AcDbDatabase*   pHostDb       = NULL);
Acad::ErrorStatus
acedXrefBind(const ACHAR*           XrefBlockname,
             const bool            bInsertBind     = false,
             const bool            bQuiet          = true,
                   AcDbDatabase*   pHostDb         = NULL);

Acad::ErrorStatus
acedXrefCreateBlockname(const ACHAR*  XrefPathname,
                              ACHAR*& XrefBlockname);

Acad::ErrorStatus
acedXrefReload(const AcDbObjectIdArray& XrefBTRids,
                     bool               bQuiet     = true,
                     AcDbDatabase*      pHostDb    = NULL);

Acad::ErrorStatus
acedXrefXBind(const AcDbObjectIdArray symbolIds,
              const bool              bQuiet       = true,
                    AcDbDatabase*     pHostDb      = NULL);

Acad::ErrorStatus
acedXrefResolve(AcDbDatabase* pHostDb, const bool bQuiet = true);

Acad::ErrorStatus
acedXrefNotifyCheckFileChanged(AcDbObjectId btrId, bool& hasChanged);

Acad::ErrorStatus
acedSkipXrefNotification(AcDbDatabase* pHostDb, const ACHAR* xrefName);

Acad::ErrorStatus ACDB_PORT 
acedSetXrefResolvedWithUpdateStatus(AcDbBlockTableRecord* pBTR);

/// <description>
/// Mark the input XRef definition object ID, that to delay resolving its referenced file path to relative type.
/// This function should be used for unnamed host drawing, in which the host drawing's file path is still not determined until it's saved,
/// so relative type path can not be saved in XRef definitions.
/// with this function, these marked XRef definitions will be resolved to relative path when the host drawing is saved.
/// </description>
/// <param name="xrefDefId">the object ID of the XRef definition object </param>
void 
acedMarkForDelayXRefRelativePathResolve(const AcDbObjectId& xrefDefId);


/// <description>
/// Unmark the input XRef definition object ID, which is marked in function acedMarkForDelayXRefRelativePathResolve()
/// If this object ID is not marked before by function acedMarkForDelayXRefRelativePathResolve(), then this function will be a no-op
/// </description>
/// <param name="xrefDefId">the object ID of the XRef definition object </param>
void 
acedUnmarkForDelayXRefRelativePathResolve(const AcDbObjectId& xrefDefId);

#pragma pack (pop)
#endif /* _ACEDXREF_H */

