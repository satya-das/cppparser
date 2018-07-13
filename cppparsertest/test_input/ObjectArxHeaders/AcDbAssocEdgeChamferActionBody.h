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
/// AcDbAssocEdgeChamferActionBody is an action body that controls edge chamfer 
/// applied to a surface with the set of input data of the action. 
/// The "input data" for this action are list of edges, chamfer distances, base
/// face from which chamfer base distance is measured and the surface to which  
/// the input edges belongs.
/// </summary>
///
class ACDB_PORT AcDbAssocEdgeChamferActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocEdgeChamferActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocEdgeChamferActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> Method to set input edges for chamfer. </summary>
    /// <param name="chamferEdges"> List of input edges. </param>
    /// <param name="baseFace"> Face subent id for base face from which chamfer
    /// base distance is to be measured. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setInput(const AcDbFullSubentPathArray& chamferEdges, const AcDbSubentId& baseFace);

    /// <summary><para> 
    /// Sets base distance value for chamfer, expression and evaluatorId for 
    /// this action. If there is no expression, the expression string and the
    /// evaluatorId must be empty strings. 
    /// </para><para>
    /// Base distance can also be set using setValueParam method with paramName
    /// kChamferDistanceParamName and value index 0.
    /// </para></summary>
    /// <param name="baseDistance">  new value of baseDistance parameter. </param>
    /// <param name="expression">  expression of baseDistance parameter. </param>
    /// <param name="evaluatorId"> evaluator id. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setBaseDistance(double baseDistance, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Sets other distance value for chamfer, expression and evaluatorId for 
    /// this action. If there is no expression, the expression string and the
    /// evaluatorId must be empty strings. 
    /// </para><para>
    /// Other distance can also be set using setValueParam method with paramName
    /// kChamferDistanceParamName and value index 1.
    /// </para></summary>
    /// <param name="otherDistance">  new value of otherDistance parameter. </param>
    /// <param name="expression">  expression of otherDistance parameter. </param>
    /// <param name="evaluatorId"> evaluator id. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setOtherDistance(double otherDistance, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());
    
    /// <summary><para> 
    /// Gets base distance value for chamfer, expression and evaluatorId for 
    /// this action. If there is no expression, the expression string and the
    /// evaluatorId are empty strings. 
    /// </para><para>
    /// Base distance can also be obtained using getValueParam method with 
    /// paramName kChamferDistanceParamName and value index 0.
    /// </para></summary>
    /// <param name="expression">  expression of the parameter. </param>
    /// <param name="evaluatorId"> evaluator id. </param>
    /// <returns> base distance value. </returns>
    ///
    double baseDistance(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;
    
    /// <summary><para> 
    /// Gets other distance value for chamfer, expression and evaluatorId for 
    /// this action. If there is no expression, the expression string and the
    /// evaluatorId are empty strings. 
    /// </para><para>
    /// Other distance can also be obtained using getValueParam method with 
    /// paramName kChamferDistanceParamName and value index 1.
    /// </para></summary>
    /// <param name="expression">  expression of the parameter. </param>
    /// <param name="evaluatorId"> evaluator id. </param>
    /// <returns> other distance value. </returns>
    ///
    double otherDistance(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;
    
    /// <summary>
    /// Implements abstract method AcDbAssocActionBody::evaluateOverride(), this
    /// method is called while evaluating the parent action that owns this action 
    /// body object.
    /// </summary>
    ///
    virtual void evaluateOverride() ADESK_OVERRIDE;

    /// <summary>
    /// Utility function to create AcDbAssocEdgeChamferActionBody and attach 
    /// dependencies and actions for given chamferEdges.
    /// </summary>
    /// <param name="chamferEdges"> List of input edges. </param>
    /// <param name="baseFace"> Face subent id for base face. </param>
    /// <param name="baseDistance"> Base distance value. </param>
    /// <param name="otherDistance"> Other distance value. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Object id for action owning 
    /// created instance of AcDbAssocEdgeChamferActionBody. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    /// 
    static Acad::ErrorStatus createInstance( const AcDbFullSubentPathArray& chamferEdges,
                                             const AcDbSubentId& baseFace,
                                             double baseDistance, 
                                             double otherDistance,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);
};

#pragma pack (pop)

