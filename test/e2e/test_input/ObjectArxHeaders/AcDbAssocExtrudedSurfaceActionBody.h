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
// CREATED BY: Jiri Kripac                                 February 2009
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocPathBasedSurfaceActionBody.h"
#pragma pack (push, 8)

class AcDbSweepOptions;

/// <summary>
/// Action that sets the contents of AcDbExtrudedSurface entity based on the 
/// input data of the action if the surface is associative. With this action, 
/// the extruded surface will always automatically regenerate when any input data 
/// is changed.
/// </summary>
///
class ACDB_PORT AcDbAssocExtrudedSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocExtrudedSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocExtrudedSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para> 
    /// Set taper angle of the resulting extruded surface( correspondent to draft angle in AcDbSweepOptions )
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kExtrusionTaperAngle". 
    /// </para></summary>
    /// <param name="dTaperAngle">  New value of the parameter. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setTaperAngle( double dTaperAngle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get taper angle of the resulting extruded surface( correspondent to draft angle in AcDbSweepOptions )
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kExtrusionTaperAngle". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Taper angle. </returns>
    ///
    double            taperAngle(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;

    /// <summary><para> 
    /// Set extrusion height of the resulting extruded surface
    /// </para><para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kExtrusionHeightParamName". 
    /// </para></summary>
    /// <param name="dHeight">  New value of the parameter. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setHeight( double dHeight, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString());

    /// <summary><para> 
    /// Get extrusion height of the resulting extruded surface
    /// </para><para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kExtrusionHeightParamName". 
    /// </para></summary>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Extrusion height. </returns>
    ///
    double            height(AcString& expression = dummyString(), AcString& evaluatorId = dummyString()) const;
    
    /// <summary> 
    /// Create an instance of AcDbAssocExtrudedSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Resulting extruded surface id. </param>
    /// <param name="inputPath">  Extrusion profile to generate the resulting extruded surface. </param>
    /// <param name="directionVec">  Input the vector that indicates the direction and distance of the sweep operation . </param>
    /// <param name="sweptOptions">  Input sweep options. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Id of created action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId, 
                                             const AcDbPathRef& inputPath,
                                             const AcGeVector3d& directionVec,
                                             const AcDbSweepOptions& sweptOptions,
                                             bool  bEnabled,
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocExtrudedSurfaceActionBody

#pragma pack (pop)
