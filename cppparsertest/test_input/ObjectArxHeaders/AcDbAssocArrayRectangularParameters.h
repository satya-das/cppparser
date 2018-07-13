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

class AcDbImpAssocArrayRectangularParameters;

/// <summary>
/// AcDbAssocArrayRectangularParameters class provides interface to manipulate 
/// rectangular array parameters. 
/// </summary>
///
class ACDB_PORT AcDbAssocArrayRectangularParameters : public AcDbAssocArrayCommonParameters
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocArrayRectangularParameters);

    /// <summary> 
    /// Following list of enums can be used as input to method
    /// getGripPointAt(unsigned int, AcDbArrayGripAppData* &) to get specific 
    /// type of grip. System internally uses these enums for grip operations on 
    /// rectangular array.
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
        /// Changes number of columns.
        /// </summary>
        ///
        kColumnCountGrip         = 1 << 4,
        
        /// <summary> 
        /// Changes distance between columns.
        /// </summary>
        ///
        kColumnSpacingGrip       = 1 << 5,
        
        /// <summary> 
        /// Changes distance between columns by distributing the move uniformly 
        /// across all the columns.
        /// </summary>
        ///
        kUniformColSpacingGrip   = 1 << 6,
        
        /// <summary> 
        /// Changes number of rows and columns at the same time.
        /// </summary>
        kRowColumnCountGrip      = 1 << 7,
        
        /// <summary> 
        /// Changes distance between rows and columns at the same time.
        /// </summary>
        ///
        kRowColumnSpacingGrip    = 1 << 8,
        
        /// <summary> 
        /// Changes the angle formed by the first row and the first column 
        /// w/o changing row direction.
        /// </summary>
        ///
        kColumnDirectionGrip     = 1 << 9,
        
        /// <summary> 
        /// Changes the angle formed by the first row and the first column 
        /// w/o changing column direction.
        /// </summary>
        ///
        kRowDirectionGrip        = 1 << 10,
        
        /// <summary> 
        /// Changes number of levels.
        /// </summary>
        ///
        kLevelCountGrip          = 1 << 11,
        
        /// <summary> 
        /// Changes distance between levels.
        /// </summary>
        ///
        kLevelSpacingGrip        = 1 << 12,
        
        /// <summary> 
        /// Changes distance between levels by distributing the move uniformly 
        /// across all the levels.
        /// </summary>
        ///
        kUniformLevelSpacingGrip = 1 << 13,

        /// <summary> 
        /// Changes the row axis angle(or column direction) while keeping the angle constant  
        /// between the first row and the first column. 
        /// </summary>
        ///
        kRowAxisAngleGrip        = 1 << 14,
    };

    /// <summary> 
    /// Constructor to update count and spacing of rows, columns and levels 
    /// along with row elevation and axis angle.
    /// </summary>
    /// <param name="columnSpacing">  The input spacing between adjacent columns. </param>
    /// <param name="rowSpacing">  The input spacing between adjacent rows. </param>
    /// <param name="levelSpacing">  The input spacing between adjacent levels. </param>
    /// <param name="columnCount">  The input number of columns. </param>
    /// <param name="rowCount">  The input number of rows. </param>
    /// <param name="levelCount">  The input number of levels. </param>
    /// <param name="rowElevation">  The input elevation between adjacent rows. </param>
    /// <param name="axesAngle">  The input angle between the first row and first column. </param>
    ///
    AcDbAssocArrayRectangularParameters(double columnSpacing = 1, double rowSpacing = 1, 
        double levelSpacing = 1, int columnCount = 1, int rowCount = 1, 
        int levelCount = 1, double rowElevation = 1, double axesAngle = 90);

    /// <summary> 
    /// Default destructor.
    /// </summary>
    ///
    virtual ~AcDbAssocArrayRectangularParameters(void);

    /// <summary> 
    /// Gets the column count of the rectangular array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns column count. </returns>
    ///
    int columnCount(AcString& expression, AcString& evaluatorId) const;
    inline int columnCount() const
    {
        AcString expression, evaluatorId;
        return columnCount(expression, evaluatorId);
    }
    inline int columnCount(AcString& expression) const
    {
        AcString evaluatorId;
        return columnCount(expression, evaluatorId);
    }
    /// <summary> 
    /// Gets the column spacing of the rectangular array.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns column spacing. </returns>
    ///
    double columnSpacing(AcString& expression, AcString& evaluatorId) const;
    inline double columnSpacing() const
    {
        AcString expression, evaluatorId;
        return columnSpacing(expression, evaluatorId);
    }
    inline double columnSpacing(AcString& expression) const
    {
        AcString evaluatorId;
        return columnSpacing(expression, evaluatorId);
    }
    /// <summary> 
    /// Gets the axes angle of the rectangular array. the values should be between 
    /// 0-360 degrees.
    /// If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <returns> Returns axes angle. </returns>
    ///
    double axesAngle(AcString& expression, AcString& evaluatorId) const;
    inline double axesAngle() const
    {
        AcString expression, evaluatorId;
        return axesAngle(expression, evaluatorId);
    }
    inline double axesAngle(AcString& expression) const
    {
        AcString evaluatorId;
        return axesAngle(expression, evaluatorId);
    }
    /// <summary> 
    /// Gets the direction vector for X axis of the rectangular array. It also
    /// provides Y axis direction optionally. Y axis is at axes angle from
    /// X axis wrt its base plane normal. The base plane normal can be obtained
    /// using getBasePlane method of the base class.
    /// </summary>
    /// <param name="pYAxis">  The address of vector to return Y axis direction.
    /// </param>
    /// <returns> Returns X axis direction vector. </returns>
    ///
    AcGeVector3d axisDirection(AcGeVector3d* pYAxis = NULL) const;

    /// <summary> 
    /// Sets the column count of the rectangular array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="nColumns">     The column count to set. This must be a positive value</param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setColumnCount(int nColumns, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the column spacing of the rectangular array.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="offset">       The column spacing to set. This must be non-zero value.</param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setColumnSpacing(double offset, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets angle between row and column axes of the rectangular array. The values would be rounded off 
    /// to (0-360) degrees. The default value is 90 degree.
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </summary>
    /// <param name="axesAngle">    The angle between row and column axes to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setAxesAngle(double axesAngle, const AcString& expression = AcString(), 
        const AcString& evaluatorId = AcString(), AcString& errorMessage = dummyString());

    /// <summary> 
    /// Sets the X axis direction for rectangular array. The Y axis is 
    /// at axis angle from X axis wrt its base normal. The base plane
    /// normal can be set using setBasePlane method of the base class.
    /// </summary>
    /// <param name="xAxis">  The axis direction to set. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setAxisDirection(const AcGeVector3d& xAxis);

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
    friend class AcDbImpAssocArrayRectangularParameters;
    explicit AcDbAssocArrayRectangularParameters(AcDbImpAssocArrayRectangularParameters* pSelf);
};
