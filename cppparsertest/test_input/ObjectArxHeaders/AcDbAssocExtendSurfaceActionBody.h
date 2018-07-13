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

class AcDbSurface;
#include "dbsurf.h" // for AcDbSurface::EdgeExtensionType

/// <summary>
/// Action that sets the contents of AcDbSurface created by edge extension, this action can works
/// for both the extend modes: 1. append mode and it is a creation action, a new surface is created 
/// by extending given edges of the input surface. The surface will update itself when input surface 
/// is modified. In this mode, the action can be fully associative or semi-associative. if fully 
/// associative, the resulting surface will always automatically regenerate when any input data is changed. 
/// If semi-associative, when input surfaces are detached from the resulting surface, this action will be 
/// erased and the resulting surface will not regenerate and become a generic surface. 
/// 2. merge mode as a modification action, instead of creating a new surface, this action modifies 
/// the input surface by extending its given edges.
/// </summary>
///
class ACDB_PORT AcDbAssocExtendSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocExtendSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocExtendSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para> 
    /// Set extension distance
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kExtendDistanceParamName". 
    /// </para></summary>
    /// <param name="distance">  New value of the extension distance, must be positive. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setDistance(double distance, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get extension distance and its possible expression
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kExtendDistanceParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Extension distance. </returns>
    ///
    double distance(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary> 
    /// Create an instance of AcDbAssocExtendSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Resulting surface id, in append mode, it will ge the new surface id, for merge mode, it should be the id of the input surface. </param>
    /// <param name="extendEdges">  Extension edges of input surface. </param>
    /// <param name="distance">  Extension distance. </param>
    /// <param name="option">  Extension options, specify the mode of extend operation (append, merge etc.), it should be the same as argument "extOption" in AcDbSurface::extendEdges(). </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. Only applies in append mode. If True, the resulting surface will
    /// <param name="createdActionId"> Id of created action. </param>
    /// always automatically regenerate itself when any input surfaces are changed. If false, it will be 
    /// non-associative, which means when input surfaces are detached from the resulting surface, this 
    /// action will be erased and the resulting surface will not regenerate and become a generic surface. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId,
                                             const AcArray<AcDbEdgeRef>& extendEdges,
                                             double distance, 
                                             AcDbSurface::EdgeExtensionType option, 
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId );

}; // class AcDbAssocExtendSurfaceActionBody

#pragma pack (pop)
