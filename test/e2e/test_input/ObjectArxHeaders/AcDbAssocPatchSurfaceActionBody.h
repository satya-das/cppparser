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
#include "dbgrip.h"
#include "AcDbAssocPathBasedSurfaceActionBody.h"
#pragma pack (push, 8)

/// <summary>
/// Action that sets the contents of AcDbSurface entity create by surface patch operation.
/// a patch surface can be curve-based or subentity edge-based. For a curve-based patch surface
/// no continuity or bulge information is necessary.
/// The action can be fully associative or semi-associative. If fully associative, the resulting 
/// surface will always automatically regenerate when any input data is changed. If semi-associative, 
/// for subentity edge-based patch surface, when input surfaces are detached from the resulting surface, 
/// this action will be erased and the resulting surface will not regenerate and become a generic surface. 
/// for curve-based patch surface, when the original input curves are detached from the patch surface,
/// the patch surface will use the cached geometry of the curves that was first used to create the patch
/// surface to regenerate.
/// </summary>
///
class ACDB_PORT AcDbAssocPatchSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocPatchSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocPatchSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Set constraint points of the resulting patch surface
    /// </summary>
    /// <param name="constraintPoints">  Array of constraint points. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setConstraintPoints( const AcArray<AcDbVertexRef> & constraintPoints);

    /// <summary> 
    /// Set constraint curves of the resulting patch surface
    /// </summary>
    /// <param name="constraintCurves">  Array of constraint curves. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setConstraintCurves( const AcArray<AcDbEdgeRef> & constraintCurves );

    /// <summary><para> 
    /// Set continuity of the resulting patch surface. It can be only used on patch surface created from edge subentity
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kContinuityParamName". 
    /// </para></summary>
    /// <param name="continuity">  New value of the parameter. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setContinuity(int continuity, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get continuity of the resulting patch surface. It can be only used on patch surface created from edge subentity
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kContinuityParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Continuity of the resulting patch surface. </returns>
    ///
    int continuity(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary> 
    /// Get location of continuity grip point of the resulting patch surface
    /// </summary>
    /// <param name="gripPt">  Position of the continuity grip point. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getContinuityGripPoint ( AcGePoint3d&  gripPt) const;

    /// <summary><para> 
    /// Set bulge factor the resulting patch surface. It can be only used on patch surface created from edge subentity
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kBulgeParamName". 
    /// </para></summary>
    /// <param name="bulge">  New value of the parameter. Bulge must be positive or 0. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setBulge(double bulge, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get bulge factor of resulting patch surface. It can be only used on patch surface created from edge subentity
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kBulgeParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Bulge. </returns>
    ///
    double bulge(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary> 
    /// Create an instance of AcDbAssocPatchSurfaceActionBody, if the input is subentity edge 
    /// with continuity and bulge info
    /// </summary>
    /// <param name="patchSurfaceId">  Resulting patch surface id. </param>
    /// <param name="profileCurves">  Array of input profiles. </param>
    /// <param name="constraintCurves">  Array of constraint curves. </param>
    /// <param name="constraintPoints">  Array of constraint points. </param>
    /// <param name="nContinuity">  Continuity of the patch surface. </param>
    /// <param name="dBulge">  Bulge of the patch surface. </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. if True, the resulting surface will
    /// always automatically regenerate itself when any input surfaces are changed. If false, it will be 
    /// semi-associative, which means when input surfaces are detached from the resulting surface, this 
    /// action will be erased and the resulting surface will not regenerate and become a generic surface. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& patchSurfaceId,
                                             const AcArray<AcDbEdgeRef>& profileCurves,
                                             const AcArray<AcDbEdgeRef>& constraintCurves,
                                             const AcArray<AcDbVertexRef>&constraintPoints,
                                             int nContinuity,
                                             double dBulge,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);

    /// <summary> 
    /// Create an instance of AcDbAssocPatchSurfaceActionBody, if the input is AcDbCurve
    /// without continuity and bulge info
    /// </summary>
    /// <param name="patchSurfaceId">  Resulting patch surface id. </param>
    /// <param name="profileCurves">  Array of input profiles. </param>
    /// <param name="constraintCurves">  Array of constraint curves. </param>
    /// <param name="constraintPoints">  Array of constraint points. </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. if True, the resulting surface will
    /// always automatically regenerate itself when any input surfaces are changed. If false, it will be 
    /// semi-associative, which means when input curves are detached from the resulting surface,  
    /// the resulting surface will regenerate based on saved geometry of curves that first time used to create the 
    /// the patch surface. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& patchSurfaceId,
                                             const AcArray<AcDbEdgeRef>& profileCurves,
                                             const AcArray<AcDbEdgeRef>& constraintCurves,
                                             const AcArray<AcDbVertexRef>&constraintPoints,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocPatchSurfaceActionBody

#pragma pack (pop)
