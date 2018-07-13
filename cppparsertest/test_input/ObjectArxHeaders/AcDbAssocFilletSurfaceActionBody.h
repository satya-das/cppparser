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
// CREATED BY: Pei Zhan                                 September 2009
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocSurfaceActionBody.h"
#pragma pack (push, 8)


/// <summary>
/// Action that sets the contents of AcDbSurface entity created by surface fillet operation.
/// The action can be fully associative or semi-associative. if fully associative, the resulting 
/// surface will always automatically regenerate when any input data is changed. If semi-associative, 
/// when input surfaces are detached from the resulting surface, this action will be erased and 
/// the resulting surface will not regenerate and become a generic surface.
/// </summary>
///
class ACDB_PORT AcDbAssocFilletSurfaceActionBody : public AcDbAssocSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocFilletSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocFilletSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Get hint points that are used to create the resulting surface
    /// </summary>
    /// <param name="nPtIndex">  Point index, can be either 0 or 1 </param>
    /// <param name="pickPt">  Returned pick point. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getHintPoints(AcGePoint3d hintPoints[2]) const;

    /// <summary> 
    /// Set hint points that are used to create the resulting surface
    /// </summary>
    /// <param name="nPtIndex">  Point index, can be only 0 or 1 </param>
    /// <param name="pickPt">  New value of the pick point. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setHintPoints(const AcGePoint3d hintPoints[2], const AcGeVector3d& viewDir);

    /// <summary><para> 
    /// Set radius of the resulting fillet surface
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kFilletRadiusParamName". 
    /// </para></summary>
    /// <param name="dRadius">  New value of the parameter. Fillet radius must be positive </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRadius( double dRadius, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString() );

    /// <summary><para> 
    /// Get radius of the resulting fillet surface
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kFilletRadiusParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Fillet radius. </returns>
    ///
    double radius(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;
    
    /// <summary> 
    /// Set trim mode that is used to trim the two input surfaces
    /// </summary>
    /// <param name="trimMode">  New value of the parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setTrimMode ( AcDb::FilletTrimMode trimMode );

    /// <summary> 
    /// Get trim mode that is used to trim the two input surfaces
    /// </summary>
    /// <returns> Trim mode. </returns>
    ///
    AcDb::FilletTrimMode trimMode() const;

    /// <summary> 
    /// Get fillet handle data
    /// </summary>
    /// <param name="pt">  The location of fillet handle origin. </param>
    /// <param name="dir">  The direction of fillet handle. </param>
    /// <param name="filletCenPtr">  The center point of fillet arc. </param>
    /// <param name="filletNormal">  The normal direction of fillet arc. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getFilletHandleData (AcGePoint3d& pt, 
                                           AcGeVector3d& dir,
                                           AcGePoint3d& filletCenPt,
                                           AcGeVector3d& filletNormal) const;
					   
    /// <summary> 
    /// Create an instance of AcDbAssocFilletSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Id of the resulting surface that will get re-evaluated in the action. </param>
    /// <param name="inputSurfaceId1">  Id of the first input surface that is used to create the resulting surface. </param>
    /// <param name="pickPt1">  First pick point that used to create the resulting fillet surface. </param>
    /// <param name="inputSurfaceId2">  Id of the first input surface that is used to create the resulting surface. </param>
    /// <param name="pickPt2">  Second pick point that is used to create the resulting fillet surface. </param>
    /// <param name="trimMode">  Trim mode that is used to trim the input surfaces. </param>
    /// <param name="viewDir">  View direction that is used to create the resulting fillet surface. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. if True, the resulting surface will
    /// <param name="createdActionId"> Id of created action. </param>
    /// always automatically regenerate itself when any input surfaces are changed. If false, it will be 
    /// non-associative, which means when input surfaces are detached from the resulting surface, this 
    /// action will be erased and the resulting surface will not regenerate and become a generic surface. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId,
                                             const AcDbObjectId& inputSurfaceId1,
                                             const AcGePoint3d& pickPt1,
                                             const AcDbObjectId& inputSurfaceId2,
                                             const AcGePoint3d& pickPt2,
                                             double radius, AcDb::FilletTrimMode trimMode,
                                             const AcGeVector3d& viewDir,
                                             bool bEnabled, 
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocFilletSurfaceActionBody

#pragma pack (pop)
