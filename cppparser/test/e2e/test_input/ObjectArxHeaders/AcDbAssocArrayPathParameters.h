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

class AcDbImpAssocArrayPathParameters;
class AcDbEdgeRef;

/// <summary>
/// AcDbAssocArrayPathParameters class provides interface to manipulate 
/// path array parameters. 
/// </summary>
///
class ACDB_PORT AcDbAssocArrayPathParameters : public AcDbAssocArrayCommonParameters
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocArrayPathParameters);

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
        /// Moves the array object.
        /// </summary>
        ///
        kStretchGrip             = 1 << 0,
        
        /// <summary> 
        /// Changes number of rows.
        /// </summary>
        ///
        kRowCountGrip            = 1 << 1,
        
        /// <summary> 
        /// Changes distance between rows.
        /// </summary>
        ///
        kRowSpacingGrip          = 1 << 2,
        
        /// <summary> 
        /// Changes distance between rows by distributing the move uniformly 
        /// across all the rows.
        /// </summary>
        ///
        kUniformRowSpacingGrip   = 1 << 3,
        
        /// <summary> 
        /// Changes number of levels.
        /// </summary>
        ///
        kLevelCountGrip          = 1 << 4,
        
        /// <summary> 
        /// Changes distance between levels.
        /// </summary>
        ///
        kLevelSpacingGrip        = 1 << 5,
        
        /// <summary> 
        /// Changes distance between levels by distributing the move uniformly 
        /// across all the levels.
        /// </summary>
        ///
        kUniformLevelSpacingGrip = 1 << 6,
        
        /// <summary> 
        /// Changes number of items.
        /// </summary>
        ///
        kItemCountGrip           = 1 << 7,
        
        /// <summary> 
        /// Used in measure method only.
        /// Changes distance between items. 
        /// </summary>
        ///
        kItemSpacingGrip         = 1 << 8, 

        /// <summary> 
        /// Used in measure method only.
        /// Changes distance between items by distributing the move uniformly 
        /// across all the items.
        /// </summary>
        ///
        kUniformItemSpacingGrip   = 1 << 9,
    };

    /// <summary> Constructor.</summary>
    /// <param name="itemSpacing">  The input spacing between adjacent items. </param>
    /// <param name="rowSpacing">  The input spacing between adjacent rows. </param>
    /// <param name="levelSpacing">  The input spacing between adjacent levels. </param>
    /// <param name="itemCount">  The input number of items. </param>
    /// <param name="rowCount">  The input number of rows. </param>
    /// <param name="levelCount">  The input number of levels. </param>
    /// <param name="rowElevation">  The input elevation between adjacent rows. </param>
    ///
    AcDbAssocArrayPathParameters(double itemSpacing = 1, double rowSpacing = 1, 
        double levelSpacing = 1, int itemCount = 1, int rowCount = 1, 
        int levelCount = 1, double rowElevation = 1);

    /// <summary> Default destructor.</summary>
    ///
    virtual ~AcDbAssocArrayPathParameters(void);

    /// <summary> 
    /// The method of arraying items along the path.
    /// </summary>
    ///
    enum Method
    {
        /// <summary> 
        /// Divide method arranges given number of items on entire path equidistantly.  
        /// </summary>
        ///
        kDivide,

        /// <summary> 
        /// Mesure method arranges given number of items at specified item spacing along the path.
        /// </summary>
        ///
        kMeasure,
    };

    /// <summary> 
    /// Gets the item count of the path array.
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
    inline int itemCount(AcString & expression) const
    {
        AcString evaluatorId;
        return itemCount(expression, evaluatorId);
    }

    /// <summary> 
    /// Gets the item spacing of the path array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns item spacing. </returns>
    ///
    double itemSpacing(AcString& expression, AcString& evaluatorId) const;
    inline double itemSpacing() const
    {
        AcString expression, evaluatorId;
        return itemSpacing(expression, evaluatorId);
    }
    inline double itemSpacing(AcString& expression) const
    {
        AcString evaluatorId;
        return itemSpacing(expression, evaluatorId);
    }
    /// <summary> 
    /// Gets the AcDbEdgeRef that identifies the path of the path array.
    /// </summary>
    /// <returns> Returns the AcDbEdgeRef that identifies the path. </returns>
    ///
    AcDbEdgeRef path() const;

    /// <summary> 
    /// Gets the method of arraying items along the path.
    /// </summary>
    /// <returns> Returns the method of arraying items along the path. Default method is kMeasure</returns>
    ///
    Method method() const;

    /// <summary> 
    /// Gets the align items option.
    /// </summary>
    /// <returns> Returns whether to align items. Default value is true</returns>
    ///
    bool alignItems() const;

    /// <summary> 
    /// Gets the start offset of the path array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns start offset. </returns>
    ///
    double startOffset(AcString& expression, AcString& evaluatorId) const;
    inline double startOffset() const
    {
        AcString expression, evaluatorId;
        return startOffset(expression, evaluatorId);
    }
    /// <summary> 
    /// Gets the end offset of the path array.
    /// End offset is only avaliable for Divide method.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns end offset. </returns>
    ///
    double endOffset(AcString& expression, AcString& evaluatorId) const;
    inline double endOffset() const
    {
        AcString expression, evaluatorId;
        return endOffset(expression, evaluatorId);
    }
    
    /// <summary> 
    /// Sets the item count of the path array.
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
    /// Sets the item spacing of the path array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. This has no effect if method is set to kDivide.
    /// </summary>
    /// <param name="offset">       The item spacing to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setItemSpacing(double offset, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the path of the path array.
    /// </summary>
    /// <param name="edgeRef">   The AcDbEdgeRef to set. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setPath(const AcDbEdgeRef& edgeRef);

    /// <summary> 
    /// Sets the method of arraying items along the path.
    /// </summary>
    /// <param name="method"> The input method of arraying items along the path. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setMethod(Method method);

    /// <summary> 
    /// Sets whether to align items or not.
    /// </summary>
    /// <param name="bAlignItems"> The boolean value to set. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setAlignItems(bool bAlignItems);

    /// <summary> 
    /// Sets the start offset of the path array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="startOffset">  The start offset to set. This must be non-negative value. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setStartOffset(double startOffset, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the end offset of the path array.
    /// End offset is only avaliable for Divide method.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="endOffset">    The end offset to set. This must be non-negative value.</param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setEndOffset(double endOffset, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the direction of path curve.
    /// if bAlongParams is false, then the parameter of this path curve is reversed
    /// and is created from end point to start point.
    /// </summary>
    /// <param name="bAlongParams"> The boolean value to set. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setPathDirection(bool bAlongParams);

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
    inline Acad::ErrorStatus getItemPosition(const AcDbItemLocator& locator, 
                                             AcGePoint3d& position) const
    {
        AcGeMatrix3d xform;
        return getItemPosition(locator, position,xform);
    }

protected:
    friend class AcDbImpAssocArrayPathParameters;
    explicit AcDbAssocArrayPathParameters(AcDbImpAssocArrayPathParameters* pSelf);
};
