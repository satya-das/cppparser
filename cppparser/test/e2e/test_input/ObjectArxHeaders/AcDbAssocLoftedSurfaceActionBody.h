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

class AcDbPathRef;
class AcDbLoftOptions;

/// <summary>
/// Action that sets the contents of AcDbLoftedSurface entity based on the 
/// input data of the action. 
/// </summary>
///
class ACDB_PORT AcDbAssocLoftedSurfaceActionBody : public AcDbAssocPathBasedSurfaceActionBody
{
public:
    /// <summary>
    /// The type of a profile in creating a lofted surface.
    /// </summary>
    ///
    enum ProfileType {
        /// <summary>
        /// First profile of cross section, can be a point or curve/subentity edge
        /// </summary>
        ///
        kStartCrossSection  = 0x01,

        /// <summary>
        /// Last profile of cross section, can be a point or curve/subentity edge
        /// </summary>
        ///
        kEndCrossSection    = 0x02,

        /// <summary>
        /// First profile of guide curves
        /// </summary>
        ///
        kStartGuide         = 0x04,

        /// <summary>
        /// Last profile of guide curves
        /// </summary>
        ///
        kEndGuide           = 0x08
    };
    ACRX_DECLARE_MEMBERS(AcDbAssocLoftedSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocLoftedSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary>
    /// <para> Get continuity of a specific profile of the resulting lofted surface </para>
    /// <para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kContinuityParamName" and corresponding index as following: 
    /// </para>
    /// <para> kStartCrossSection  : "0". </para>
    /// <para> kEndCrossSection : number of cross sections - 1. </para>
    /// <para> kStartGuide  : number of cross sections. </para>
    /// <para> kEndGuide : number of cross sections + number of guide curves - 1. </para>
    /// </summary>
    /// <param name="type">  Specify which profile to get continuity. </param>
    /// <param name="continuity">  Returned continuity, can be 0(G0), 1(G1), 2(G2). </param>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getContinuity( ProfileType type, int &continuity, AcString& expression = dummyString(), 
        AcString& evaluatorId = dummyString() ) const;

    /// <summary>
    /// <para> Set continuity of a specific profile of the resulting lofted surface </para>
    /// <para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kContinuityParamName" and corresponding index as following: 
    /// </para>
    /// <para> kStartCrossSection  : "0". </para>
    /// <para> kEndCrossSection : number of cross sections - 1. </para>
    /// <para> kStartGuide  : number of cross sections. </para>
    /// <para> kEndGuide : number of cross sections + number of guide curves - 1. </para>
    /// </summary>
    /// <param name="type">  Specify which profile to set continuity. </param>
    /// <param name="continuity">  New continuity value, can be 0(G0), 1(G1), 2(G2). </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setContinuity( ProfileType type, int continuity, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString() );

    /// <summary>
    /// <para> Get bulge factor of a specific profile of the resulting lofted surface </para>
    /// <para>
    /// the same parameter can be accessed through class AcDbAssocAction by calling method 
    /// getValueParam with name "kBulgeParamName" and corresponding index as following: 
    /// </para>
    /// <para> kStartCrossSection  : "0". </para>
    /// <para> kEndCrossSection : number of cross sections - 1. </para>
    /// <para> kStartGuide  : number of cross sections. </para>
    /// <para> kEndGuide : number of cross sections + number of guide curves - 1. </para>
    /// </summary>
    /// <param name="type">  Specify which profile to get bulge. </param>
    /// <param name="bulge">  Returned bulge. </param>
    /// <param name="expression">  Expression of the parameter, empty string if no expression is being used. </param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, empty string if no expression is being used </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getBulge( ProfileType type, double &bulge, AcString& expression = dummyString(), 
        AcString& evaluatorId = dummyString() ) const;

    /// <summary>
    /// <para> Set bulge factor of a specific profile of the resulting lofted surface </para>
    /// <para>
    /// the same parameter can be set through class AcDbAssocAction by calling method 
    /// setValueParam with name "kBulgeParamName" and corresponding index as following: 
    /// </para>
    /// <para> kStartCrossSection  : "0". </para>
    /// <para> kEndCrossSection : number of cross sections - 1. </para>
    /// <para> kStartGuide  : number of cross sections. </para>
    /// <para> kEndGuide : number of cross sections + number of guide curves - 1. </para>
    /// </summary>
    /// <param name="type">  Specify which profile to set bulge. </param>
    /// <param name="bulge">  New bulge value. </param>
    /// <param name="expression">  Expression of the parameter, if the value is controlled by other parameters</param>
    /// <param name="evaluatorId"> The id of the expression evaluator that is used to parse the expression, if an expression is used. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setBulge( ProfileType type, double bulge, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString() );

    /// <summary> 
    /// Create an instance of AcDbAssocLoftedSurfaceActionBody
    /// </summary>
    /// <param name="resultingSurfaceId">  Id of the resulting lofted surface that will get re-evaluate in the action. </param>
    /// <param name="crossSections">  Input array of cross sections, it can be either type of AcDbVertexRef (for start and edge cross sections) or AcDbPathRef. </param>
    /// <param name="guideCurves"> Input array of guide profiles that will be used to create the lofted surface. </param>
    /// <param name="pathCurve">  Input path curve that will be used to create the lofted surface. </param>
    /// <param name="loftOptions">  Loft options that will be used to create the lofted surface. </param>
    /// <param name="continuityArray"> Array of continuity factors for each cross section and guide profiles, each element in the array is correspondent to one cross section or guide profile in the order of cross section array and guide array, hence the length of the continuity array will be the sum of the length of cross section array and guide profile array. </param>
    /// <param name="bulgeArray"> Array of bulge factors for each cross section and guide profiles, each element in the array is correspondent to one cross section or guide profile in the order of cross section array and guide array, hence the length of the bulge array will be the sum of the length of cross section array and guide profile array. </param>
    /// <param name="bEnabled">  Specify if the action is fully associative. </param>
    /// <param name="createdActionId"> Id of created new lofted surface action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus createInstance( const AcDbObjectId& resultingSurfaceId, 
                                             const AcArray<AcDbGeomRef *>& crossSections,
                                             const AcArray<AcDbPathRef>& guideCurves,
                                             const AcDbPathRef& pathCurve, 
                                             const AcDbLoftOptions& loftOptions,
                                             const AcArray<int>& continuityArray,
                                             const AcArray<double>& bulgeArray,
                                             bool bEnabled,
                                             AcDbObjectId& createdActionId);

}; // class AcDbAssocLoftedSurfaceActionBody

#pragma pack (pop)
