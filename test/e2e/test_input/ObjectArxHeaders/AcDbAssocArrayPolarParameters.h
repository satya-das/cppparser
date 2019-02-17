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
// CREATED BY: Mei Jiayin                            March 2010
//
// DESCRIPTION: 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcDbAssocArrayCommonParameters.h"

class AcDbImpAssocArrayPolarParameters;

/// <summary>
/// AcDbAssocArrayPolarParameters class provides interface to manipulate 
/// polar array parameters. 
/// </summary>
///
class ACDB_PORT AcDbAssocArrayPolarParameters : public AcDbAssocArrayCommonParameters
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocArrayPolarParameters);

    /// <summary> Constructor.</summary>
    /// <param name="angle">  The input angle formed by any two adjacent items and 
    /// the center of polar array. The value should be between 0-360 degrees. </param>
    /// <param name="rowSpacing">  The input spacing between adjacent rows. </param>
    /// <param name="levelSpacing">  The input spacing between adjacent levels. </param>
    /// <param name="itemCount">  The input number of items. </param>
    /// <param name="rowCount">  The input number of rows. </param>
    /// <param name="levelCount">  The input number of levels. </param>
    /// <param name="rowElevation">  The input elevation between adjacent rows. </param>
    ///
    AcDbAssocArrayPolarParameters(double angle = 15, double rowSpacing = 1, 
        double levelSpacing = 1, int itemCount = 1, int rowCount = 1, 
        int levelCount = 1, double rowElevation = 1);

    /// <summary> Default destructor.</summary>
    ///
    virtual ~AcDbAssocArrayPolarParameters(void);

    /// <summary> 
    /// Following list of enums can be used as input to method
    /// getGripPointAt(unsigned int, AcDbArrayGripAppData* &) to get specific 
    /// type of grip. System internally uses these enums for grip operations on 
    /// path array.
    /// </summary>
    ///
    enum GripModes
    {
        /// <summary> 
        /// Moves the polar array.
        /// </summary>
        ///
        kCenterPointGrip         = 1 << 0, 

        /// <summary> 
        /// Changes radius of the polar array.
        /// </summary>
        ///
        kStretchRadiusGrip       = 1 << 1,

        /// <summary> 
        /// Changes number of rows.
        /// </summary>
        ///
        kRowCountGrip            = 1 << 2,
        
        /// <summary> 
        /// Changes distance between rows.
        /// </summary>
        ///
        kRowSpacingGrip          = 1 << 3,
        
        /// <summary> 
        /// Changes distance between rows by distributing the move uniformly 
        /// across all the rows.
        /// </summary>
        ///
        kUniformRowSpacingGrip   = 1 << 4,
        
        /// <summary> 
        /// Changes number of levels.
        /// </summary>
        ///
        kLevelCountGrip          = 1 << 5,
        
        /// <summary> 
        /// Changes distance between levels.
        /// </summary>
        ///
        kLevelSpacingGrip        = 1 << 6,
        
        /// <summary> 
        /// Changes distance between levels by distributing the move uniformly 
        /// across all the levels.
        /// </summary>
        ///
        kUniformLevelSpacingGrip = 1 << 7,
        
        /// <summary> 
        /// Changes number of items.
        /// </summary>
        ///
        kItemCountGrip           = 1 << 8,
        
        /// <summary> 
        /// Changes angle between items. 
        /// </summary>
        ///
        kAngleBetweenItemsGrip   = 1 << 9, 

        /// <summary> 
        /// Changes the fill angle of Polar array.
        /// </summary>
        ///
        kFillAngleGrip           = 1 << 10,

    };

    /// <summary> 
    /// Specifies the direction of the arc which array items depend on.
    /// </summary>
    ///
    enum Direction
    {
        kClockwise,
        kCounterClockwise,
    };

    /// <summary> 
    /// Gets the item count of the polar array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns item count. </returns>
    ///
    int itemCount(AcString& expression, AcString& evaluatorId) const;
    inline int itemCount() const
    {
        AcString expression, evaluatorId;
        return itemCount(expression, evaluatorId);
    }
    inline int itemCount(AcString& expression) const
    {
        AcString evaluatorId;
        return itemCount(expression, evaluatorId);
    }
    /// <summary> 
    /// Gets the angle between items of the polar array.
    /// The value is between (0-360] degrees.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns angle between items. </returns>
    ///
    double angleBetweenItems(AcString& expression , AcString& evaluatorId) const;
    inline double angleBetweenItems() const
    {
        AcString expression, evaluatorId;
        return angleBetweenItems(expression, evaluatorId);
    }
    inline double angleBetweenItems(AcString& expression) const
    {
        AcString evaluatorId;
        return angleBetweenItems(expression, evaluatorId);
    }
    /// <summary> 
    /// Gets angle between first and last item in array.
    /// The value is between (0-360] degrees.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns angle between first and last item. </returns>
    ///
    double fillAngle(AcString& expression, AcString& evaluatorId) const;
    inline double fillAngle() const
    {
        AcString expression, evaluatorId;
        return fillAngle(expression, evaluatorId);
    }
    inline double fillAngle(AcString& expression) const
    {
        AcString evaluatorId;
        return fillAngle(expression, evaluatorId);
    }

    /// <summary> 
    /// Gets the angle for the first item in array.
    /// The value should be between 0-360 degrees.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns angle between first and last item. </returns>
    ///
    double startAngle(AcString& expression, AcString& evaluatorId) const;

    /// <summary> 
    /// Gets the direction of arc.
    /// </summary>
    /// <returns> Returns the direction of arc. </returns>
    ///
    Direction direction() const;

    /// <summary> 
    /// Gets the retate rotate items option.
    /// </summary>
    /// <returns> Returns whether to rotate items. </returns>
    ///
    bool rotateItems() const;

    /// <summary> 
    /// Gets the radius of the polar array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns the radius. </returns>
    ///
    double radius(AcString& expression, AcString& evaluatorId) const;
    inline double radius() const
    {
        AcString expression, evaluatorId;
        return radius(expression, evaluatorId);
    }
    inline double radius(AcString& expression) const
    {
        AcString evaluatorId;
        return radius(expression, evaluatorId);
    }
    /// <summary> 
    /// Sets the item count of the polar array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="nItems">     The item count to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setItemCount(int nItems, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the angle between items of the polar array.
    /// The input value will be rounded off to (0-360] degree
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="angle">        The angle to set. This must be a positive value</param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setAngleBetweenItems(double angle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets angle between first and last item in array.
    /// The value will be rounded off to (0-360] degree
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="fillAngle">    The angle to set. Absolute value of this parameter is used. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setFillAngle(double fillAngle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the angle for the first item in polar array.
    /// The value will be rounded off to [0-360] degree
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="angle">        The angle to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setStartAngle(double angle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the direction of arc.
    /// </summary>
    /// <param name="direction"> The input direction of arc. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setDirection(Direction direction);

    /// <summary> 
    /// Sets whether to rotate items or not.
    /// </summary>
    /// <param name="bRotateItems"> The input boolean to set. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRotateItems(bool bRotateItems);

    /// <summary> 
    /// Sets the radius of the polar array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="radius">     The radius to set. Absolute value of this parameter is used. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setRadius(double radius, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> <para>
    /// Obtains list of items patterned by the set of owned parameters. Each
    /// parameters class uses its own logic based on owned value as well as 
    /// geometry parameters to define a set of items to be patterned as array.
    /// </para><para>
    /// The owning AcDbAssocArrayActionBody calls this method while evaluating
    /// the array to update transforms of each item in the array. The caller
    /// may pass its current list of items for update. The input list can be
    /// modified by this implementation to cater change in value parameters
    /// controlling number of items in various directions.
    /// </para></summary>
    /// <param name="items"> The updated list of items. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getItems(AcArray<AcDbAssocArrayItem*>& items) const;

    /// <summary>
    /// Obtains position as well as orientation of an item at given spatial 
    /// index specified by the locator.
    /// </summary>
    /// <param name="locator">  The input item locator or spatial index. </param>
    /// <param name="position"> The returned positon of the item whose location is
    /// indicated by the input locator. </param>
    /// <param name="xform">    The returned orientation transform of the item.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getItemPosition(const AcDbItemLocator& locator, 
        AcGePoint3d& position, AcGeMatrix3d& xform) const;

protected:
    friend class AcDbImpAssocArrayPolarParameters;
    explicit AcDbAssocArrayPolarParameters(AcDbImpAssocArrayPolarParameters* pSelf);
};
