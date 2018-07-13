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
// CREATED BY: Pei Zhan                                 March 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "dbgrip.h"
#include "AcDbAssocPathBasedSurfaceActionBody.h"
#pragma pack (push, 8)

class AcDbLoftProfile;
class AcDbBlendOptions;

/// <summary>
/// Action that sets the contents of AcDbSurface entity based on surface blend operation.
/// If this action is erased, the surface it attached to will become a lofted surface and
/// all the information stored in this action will get lost.
/// The action can be fully associative or semi-associative. if fully associative, the resulting 
/// surface will always automatically regenerate when any input data is changed. If non-associative, 
/// when input surfaces are detached from the resulting surface, this action will be erased and 
/// the resulting surface will not regenerate and become a generic lofted surface.
/// </summary>
///

class ACDB_PORT AcDbAssocBlendSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocBlendSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocBlendSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para> 
    /// Get continuity of start profile that is used to create the resulting surface
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kContinuityParamName" and index "0". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Continuity of start profile. It can be 0(G0), 1(G1), 2(G2) </returns>
    ///
    Adesk::Int16       startEdgeContinuity(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary><para> 
    /// Set continuity of start profile of the resulting surface
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kContinuityParamName" and index "0". 
    /// </para></summary>
    /// <param name="value">  New value of the parameter. It can be 0(G0), 1(G1), 2(G2)</param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus  setStartEdgeContinuity (Adesk::Int16 value, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString()); 

    /// <summary><para> 
    /// Get continuity of end profile of the resulting surface
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kContinuityParamName" and index "1". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Continuity of end edge. It can be 0(G0), 1(G1), 2(G2)</returns>
    ///
    Adesk::Int16       endEdgeContinuity(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary><para> 
    /// Set continuity of end profile of the resulting surface
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kContinuityParamName" and index "1". 
    /// </para></summary>
    /// <param name="value">  New value of the parameter. it can be 0(G0), 1(G1), 2(G2)</param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus  setEndEdgeContinuity (Adesk::Int16 value, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString()); 

    /// <summary><para> 
    /// Get bulge factor of end profile and its possible expression
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kBulgeParamName" and index "0". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Bulge factor of start profile. </returns>
    ///
    double             startEdgeBulge(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary><para> 
    /// Set bulge factor of start profile of the resulting surface
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kBulgeParamName" and index "0". 
    /// </para></summary>
    /// <param name="value">  New value of the parameter. Value must be positive or 0. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus  setStartEdgeBulge(double value, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString()); 

    /// <summary><para> 
    /// Get bulge factor of end profile and its possible expression
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kBulgeParamName" and index "1". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Bulge factor of end edge. </returns>
    ///
    double             endEdgeBulge(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary><para> 
    /// Set bulge factor of end profile that of the resulting surface.
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kBulgeParamName" and index "1". 
    /// </para></summary>
    /// <param name="value">  New value of the parameter. Value must be positive or 0. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus  setEndEdgeBulge(double value, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString()); 

    /// <summary> 
    /// Get location of continuity grip points
    /// </summary>
    /// <param name="startEdgePt">  Continuity grip point at start edge. </param>
    /// <param name="endEdgePt"> Continuity grip point at end edge. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus  getContinuityGripPoints(AcGePoint3d& startEdgePt,
		                              AcGePoint3d& endEdgePt) const;

    /// <summary> 
    /// Get profiles that are used to create the blend surface during action evaluation
    /// caller is reponsible for releasing the returned pointers
    /// </summary>
    /// <param name="pStartProfile">  Start profile. </param>
    /// <param name="pEndProfile"> End profile. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus  getProfiles(AcDbLoftProfile* & pStartProfile,
                                   AcDbLoftProfile* & pEndProfile) const;

    /// <summary> 
    /// Get blend options used for blend surface 
    /// </summary>
    /// <param name="AcDbBlendOptions">  Blend options. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus  getBlendOptions( AcDbBlendOptions& blendOptions ) const;

    /// <summary> 
    /// Set blend options for blend surface
    /// </summary>
    /// <param name="AcDbBlendOptions">  New blend options. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus  setBlendOptions (const AcDbBlendOptions& blendOptions );

    /// <summary> 
    /// Create an instance of AcDbAssocBlendSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Id of the resulting surface that will get re-evaluated in the action. </param>
    /// <param name="startProfile">  Start profile that is used to create the blend surface. </param>
    /// <param name="endProfile">  End profile that is used to create the blend surface. </param>
    /// <param name="blendOptions">  Various options used to create the blend surface in ASM. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. If True, the resulting surface will
    /// <param name="createdActionId"> Id of created blend surface action. </param>
    /// always automatically regenerate itself when any input surfaces are changed. If false, it will be 
    /// non-associative, which means when input surfaces are detached from the resulting surface, this  
    /// action will be erased and the resulting surface will not regenerate and become a generic lofted surface. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId,
                                             const AcDbLoftProfile* startProfile,
                                             const AcDbLoftProfile* endProfile,
                                             const AcDbBlendOptions& blendOptions,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocBlendSurfaceActionBody

#pragma pack (pop)
