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
// CREATED BY: Pei Zhan                                 May 2009
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocPathBasedSurfaceActionBody.h"
#pragma pack (push, 8)

class AcDbRevolveOptions;

/// <summary>
/// Action that sets the contents of AcDbRevolvedSurface entity based on the 
/// input data of the action. With this action, if the original input data is 
/// changed, the revolved surface will regenerate. 
/// </summary>
///
class ACDB_PORT AcDbAssocRevolvedSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocRevolvedSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocRevolvedSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para> 
    /// Set revolve angle of the resulting revolved surface
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kRevolveAngleParamName". 
    /// </para></summary>
    /// <param name="angle">  New value of the revolve angle. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRevolveAngle(double angle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get revolve angle of the resulting revolved surface
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kRevolveAngleParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Revolve angle. </returns>
    ///
    double revolveAngle(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary> 
    /// Create an instance of AcDbAssocRevolvedSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Object id of resulting revolved surface. </param>
    /// <param name="revolvePath">  Input profile that is to be revolved to create the resulting surface. </param>
    /// <param name="axisPath">  Input profile that is to be revolved around to create the resulting surface, if the axis is not an entity but a vector, pass AcDbPathRef(NULL). </param>
    /// <param name="dAngle">  Revolve angle that used to create the resulting revolved surface. </param>
    /// <param name="dStartAngle">  Start angle that used to create the resulting revolved surface. </param>
    /// <param name="revolveOptions">  Revolve option that used to create the resulting revolved surface. </param>
    /// <param name="bFlipAxisDirection"> When a linear entity is used as axis, the vector is calculated as (endpoint - startpoint), set this option if the vector should be reversed. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId, 
                                             const AcDbPathRef& revolvePath,
                                             const AcDbPathRef& axisPath,
                                             double dAngle,
                                             double dStartAngle,
                                             const AcDbRevolveOptions& revolveOptions,
                                             bool bFlipAxisDirection,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocRevolvedSurfaceActionBody

#pragma pack (pop)
