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
//
// DESCRIPTION:  Class header for AcDbFrame
//               Common Base for Raster and OLE 2 Container Features
//
//    AcDbEntity
//      AcDbFrame
//        AcDbOleFrame
//          AcDbOle2Frame  
//

#ifndef AD_DBFRAME_H
#define AD_DBFRAME_H

#include "dbmain.h"
#include "gepnt3d.h"

#pragma pack (push, 8)

class ADESK_NO_VTABLE AcDbFrame: public AcDbEntity
{
protected:
    AcDbFrame();
public:
    ACDB_DECLARE_MEMBERS(AcDbFrame);
    virtual ~AcDbFrame();

    // --- AcDbObject Protocol

    // virtual Adesk::Boolean worldDraw(AcGiWorldDraw*);
    // virtual void viewportDraw(AcGiViewportDraw* mode);
    // virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;

};

#pragma pack (pop)

#endif  // AD_DBRAME_H

