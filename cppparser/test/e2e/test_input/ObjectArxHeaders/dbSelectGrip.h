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
//  dbSelectVPGrip.h - public header file for AcDbSelectVPGrip api
//

#ifndef _DBSELECTGRIP_H
#define _DBSELECTGRIP_H

#include "acdb.h"
#include "dbmain.h"

#pragma pack (push, 8)

////////////////////////////////////////////////////////////////////////
// class AcDbSelectGrip
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class allows applications to determine whether a grip on a 
/// custom entity is selectable.
/// </summary>
///
/// <remarks>
/// Currently only called from the AutoCAD grip mechanism before
/// snapping to, hovering, or heating a grip.
/// </remarks>
///

class ADESK_NO_VTABLE AcDbSelectGrip : public AcRxObject {
public:
    ACRX_DECLARE_MEMBERS(AcDbSelectGrip);
    /// <summary>
    /// Determine whether a grip on a custom entity is selectable. 
    /// </summary>
    ///
    /// <param name="pEnt">
    /// [Input] Pointer to the entity that this grip belongs to.
    /// </param>
    /// 
    /// <param name="pVd">
    /// [Input] Pointer to a current viewport context AcGiViewportDraw object.
    /// </param>
    /// 
    /// <param name="pAppData">
    /// [Input] The private AcDbGripData appdata assigned to the custom grip.
	///   Use this private appdata along with pVd to determine whether the grip 
	///   is selectable in the current (viewport) context.
    /// </param>
    /// 
    /// <returns>
    /// Returns true if the grip is selectable and false if not.
    /// </returns>
    ///

    virtual bool SelectGrip(const AcDbEntity * pEnt, 
		                    const AcGiViewportDraw* pVd,
							const void * pAppData) = 0;
};

#pragma pack (pop)

#endif  // _DBSELECTGRIP_H

