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
// DoubleClickEdit.h - Double-click Editing (for external developers)
//
// DESCRIPTION: AcDbDoubleClickEdit Protocol extension abstract base class
//
// NOTE:
// Default implementation to be attached to AcDbEntity as a catch-all. This
// guarantees that this protocol extension will be found  for any entity so
// the search up the AcRxClass tree will not fail and abort AutoCAD.  
//

#ifndef DOUBLECLICKEDIT_H
#define DOUBLECLICKEDIT_H

#include "acdb.h"
#include "dbmain.h"

#pragma pack (push, 8)

class ADESK_NO_VTABLE AcDbDoubleClickEdit : public AcRxObject
//
//  AcDbDoubleClickEdit Protocol extension abstract base class. 
//
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDoubleClickEdit);

    virtual void startEdit(AcDbEntity *pEnt, AcGePoint3d pt) = 0; 
    virtual void finishEdit(void) = 0;
};

#pragma pack (pop)

#endif //DOUBLECLICKEDIT_H
