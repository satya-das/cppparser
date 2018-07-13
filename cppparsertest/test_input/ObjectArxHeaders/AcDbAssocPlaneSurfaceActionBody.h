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
// CREATED BY: Pei Zhan                                 June 2009
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocPathBasedSurfaceActionBody.h"
#pragma pack (push, 8)

/// <summary>
/// Action that sets the contents of AcDbPlaneSurface entity based on the 
/// input data of the action. With this action, when the input edges that was used to create
/// a plane surface are changed, the plane surface will regenerated
/// </summary>
///

class ACDB_PORT AcDbAssocPlaneSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocPlaneSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocPlaneSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Create an instance of AcDbAssocPlaneSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Resulting plane surface id. </param>
    /// <param name="inputPath">  Input closed edges that used to create the plane surface. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId, 
                                             const AcDbPathRef& inputPath,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocPlaneSurfaceActionBody

#pragma pack (pop)
