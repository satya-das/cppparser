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
//  dbAlignment.h - public header file for AcDbAlignment api
//

#ifndef _DBALIGNMENT_H
#define _DBALIGNMENT_H

#include "acdb.h"
#include "dbmain.h"

#pragma pack (push, 8)

////////////////////////////////////////////////////////////////////////
// class AcDbAlignment
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class allows applications to provide an alignment point and 
/// vector for a custom entity.
/// </summary>
///
/// <remarks>
/// Currently only called when alignment grip editing an AcDbBlockReference.
/// </remarks>
///

class ADESK_NO_VTABLE AcDbAlignment : public AcRxObject {
public:
    ACRX_DECLARE_MEMBERS(AcDbAlignment);
    /// <summary>
    /// Provide an alignment point and vector for an entity. 
    /// </summary>
    ///
    /// <param name="pEnt">
    /// [Input] The entity to align to.
    /// </param>
    /// <param name="pickPoint">
    /// [Input] Current cursor location (WCS).
    /// </param>
    /// <param name="normal">
    /// [Input] Normal of entity that is being aligned. This can be
    ///   used by an application to ignore (not align to) entities not in the
    ///   plane of the entity.
    /// </param>
    /// <param name="closestPoint">
    /// [Output] Alignment point on entity. This is usually the closest point
    ///   on the entity to the cursor, but may be a snapped or osnap point.
    /// </param>
    /// <param name="direction">
    /// [Output} WCS alignment vector.
    /// </param>
    /// 
    /// <returns>
    /// Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Returns an alignment point and vector.
    /// </remarks>
    /// 

    virtual Acad::ErrorStatus getAlignment(
        AcDbEntity*           pEnt,
        const AcArray< AcDbObjectIdArray,
            AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& 
                nestedPickedEntities,
        const AcGePoint3d&    pickPoint,
        const AcGeVector3d&   normal,
        AcGePoint3d&          closestPoint,
        AcGeVector3d&         direction) = 0;
};

#pragma pack (pop)

#endif  // _DBALIGNMENT_H

