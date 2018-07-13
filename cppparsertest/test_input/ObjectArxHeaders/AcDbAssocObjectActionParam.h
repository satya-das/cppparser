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
// CREATED BY: Jiri Kripac                                 March 2010
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocActionParam.h"
#pragma pack (push, 8)


/// <summary>
/// Action parameter that just keeps a dependency on an AcDbObject. It does not
/// add any more functionality as compared to directly using an AcDbAssocDependency,
/// but it may add consistency to custom action body code that may keep all the data 
/// in the form of action parameters and access the data through the action parameters. 
/// It also allows the action body to use the action parameter name (string) to get to 
/// the referenced AcDbObject.
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocObjectActionParam : public AcDbAssocActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocObjectActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocObjectActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary>
    /// Returns the AcDbObject the action parameter depends on.
    /// </summary>
    /// <param name="object"> The returned AcDbObject the action parameter depends on. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getObject(AcDbCompoundObjectId& object) const;

    /// <summary>
    /// Makes the action parameter depend on the given AcDbObject via an AcDbAssocDependency.
    /// </summary>
    /// <param name="object"> The AcDbObject to create a dependency on. </param>
    /// <param name="isReadDependency">  Read-dependency on the object should be created.  </param>
    /// <param name="isWriteDependency"> Write-dependency on the object should be created. </param>
    /// <param name="dependencyOrder"> 
    /// Specifies position of the created dependency in the ordered list of 
    /// dependencies on the object. See AcDbAssocDependency::setOrder(int) method.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setObject(const AcDbCompoundObjectId& object, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);
};

#pragma pack (pop)
