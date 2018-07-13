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
// CREATED BY: Sharad Jaiswal                           Sept 2009
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "acdbassocpathbasedsurfaceactionbody.h"
#pragma pack (push, 8)


/// <summary>
/// AcDbAssocEdgeFilletActionBody is an action body that controls edge fillet 
/// applied to a surface with the set of input data of the action. 
/// The "input data" for this action are list of edges, fillet radius and the
/// surface to which the input edges belongs.
/// </summary>
///
class ACDB_PORT AcDbAssocEdgeFilletActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocEdgeFilletActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocEdgeFilletActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> Method to set input edges for fillet. </summary>
    /// <param name="filletEdges"> List of input edges. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setInputEdges(const AcDbFullSubentPathArray& filletEdges);

    /// <summary><para> 
    /// Sets fillet radius value, expression and evaluatorId for this action.
    /// If there is no expression, the expression string and the evaluatorId 
    /// must be empty strings. 
    /// </para><para>
    /// Fillet radius can also be set using setValueParam method with paramName
    /// kFilletRadiusParamName and value index 0.
    /// </para></summary>
    /// <param name="radius"> Radius value. </param>
    /// <param name="expression">  expression of radius parameter. </param>
    /// <param name="evaluatorId"> evaluator id. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRadius(double radius, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());
    
    /// <summary><para> 
    /// Gets fillet radius value, expression and evaluatorId for this action.
    /// If there is no expression, the expression string and the evaluatorId 
    /// are empty strings. 
    /// </para><para>
    /// Fillet radius can also be obtained using getValueParam method with 
    /// paramName kFilletRadiusParamName and value index 0.
    /// </para></summary>
    /// <param name="expression">  expression of the parameter. </param>
    /// <param name="evaluatorId"> evaluator id. </param>
    /// <returns> Radius value. </returns>
    ///
    double radius(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary>
    /// Implements abstract method AcDbAssocActionBody::evaluateOverride(), this
    /// method is called while evaluating the parent action that owns this action 
    /// body object.
    /// </summary>
    ///
    virtual void evaluateOverride() ADESK_OVERRIDE;

    /// <summary><para>
    /// Utility function to create AcDbAssocEdgeFilletActionBody and attach 
    /// dependencies and actions for given filletEdges.
    /// </para><para>
    /// This method must be called before applying actual fillet on the input 
    /// edges and after calling this method, it is advised to evaluate the
    /// associative network.
    /// </para></summary>
    /// <param name="filletEdges"> List of input edges. </param>
    /// <param name="radius"> Radius value. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Object id for action owning 
    /// created instance of AcDbAssocEdgeFilletActionBody. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    /// 
    static Acad::ErrorStatus createInstance( const AcDbFullSubentPathArray& filletEdges,
                                             double radius,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);
};

#pragma pack (pop)

