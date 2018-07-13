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
// CREATED BY: Sharad Jaiswal                            March 2010
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

/// <summary>
/// AcDbItemLocator, represents spatial index of an item in a 3D array
/// i.e an item index{i,j,k} for rectangular array.
/// </summary>
///
class ACDB_PORT AcDbItemLocator
{
public:
    /// <summary>
    /// Enum to define index type for a 3D item index.
    /// </summary>
    ///
    enum IndexType 
    { 
        /// <summary>
        /// Index type indicating item position relative to the first item.
        /// </summary>
        ///
        kItemIndex,

        /// <summary>
        /// Index type indicating item position relative to the first row.
        /// </summary>
        ///
        kRowIndex, 

        /// <summary>
        /// Index type indicating item position relative to the first level.
        /// </summary>
        ///
        kLevelIndex,
    };
    
    /// <summary>
    /// Default constructor. Object constructed using this constructor remains
    /// uninitialized.
    /// </summary>
    ///
    AcDbItemLocator();
    
    /// <summary>
    /// Parameterized constructor, this initializes all indices of the object.
    /// The cannonical form of AcDbItemLocator always uses +ve value for 
    /// indices, but clients may use -ve values for indices subjected to their
    /// own interpretation of -ve vlaues.
    /// </summary>
    /// <param name="itemIndex"> The input Index relative to the first item. 
    /// </param>
    /// <param name="rowIndex"> The input Index relative to the first row. 
    /// </param>
    /// <param name="levelIndex"> The input Index relative to the first level. 
    /// </param>
    ///
    AcDbItemLocator(int itemIndex, int rowIndex, int levelIndex);
    
    /// <summary>
    /// Copy constructor, this copies all indices of the other object to this 
    /// object.
    /// </summary>
    /// <param name="other"> The other AcDbItemLocator object intended to copy from. </param>
    ///
    AcDbItemLocator(const AcDbItemLocator& other);

    /// <summary>
    /// Index operator, this returns index of a particular index type.
    /// </summary>
    /// <param name="i"> The input Index type. </param>
    /// <returns> The index of given Index type. </returns>
    ///
    int operator [] (IndexType i) const { return mIndices[i]; }
    
    /// <summary>
    /// Assignment operator, this copies all indices of the other object to 
    /// this object.
    /// </summary>
    ///
    AcDbItemLocator& operator = (const AcDbItemLocator& other);
    
    /// <summary>
    /// Subtraction operator, this returns difference from other object.
    /// </summary>
    ///
    AcDbItemLocator  operator -  (const AcDbItemLocator& other) const;
    
    /// <summary>
    /// Addition operator, this combines indices of other object and 
    /// this object to return a new object.
    /// </summary>
    ///
    AcDbItemLocator  operator +  (const AcDbItemLocator& other) const;
    
    /// <summary>
    /// Equal to operator, checks if the other object is same as this object.
    /// </summary>
    ///
    bool operator == (const AcDbItemLocator& other) const;
    
    /// <summary>
    /// Not equal to operator, checks if the other object is different than 
    /// this object.
    /// </summary>
    ///
    bool operator != (const AcDbItemLocator& other) const;
    
    /// <summary>
    /// Less operator, checks if this object is less than the other object.
    /// </summary>
    ///
    bool operator <  (const AcDbItemLocator& other) const;

    /// <summary>
    /// Greator operator, checks if this object is less than the other object.
    /// </summary>
    ///
    bool operator >  (const AcDbItemLocator& other) const { return compareWith(other) > 0; }

    /// <summary>
    /// Compares this with other object, returns 0 if the two objects are same
    /// -ve value if this is smaller than the other, +ve value if this is 
    /// greater than other object.
    /// </summary>
    ///
    int compareWith(const AcDbItemLocator& other) const;

private:
    int mIndices[3];
};

class AcDbImpAssocArrayItem;
/// <summary>
/// AcDbAssocArrayItem class represents transformation and other meta data of
/// an item in an array. This class provides interface to obtain item transform,
/// it's locator (spatial index), relative transform etc.
/// </summary>
/// <remarks> This class is currently for internal use only. </remarks>
///
class ACDB_PORT AcDbAssocArrayItem : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocArrayItem);

    /// <summary>
    /// Default constructor.
    /// </summary>
    ///
    AcDbAssocArrayItem();
    
    /// <summary>
    /// Parameterized constructor, initializes locator and default transform.
    /// </summary>
    /// <param name="locator"> The input AcDbItemLocator. </param>
    /// <param name="transform"> The input transformation matrix. </param>
    ///
    AcDbAssocArrayItem(AcDbItemLocator& locator, const AcGeMatrix3d& transform);
    
    /// <summary>
    /// Default destructor.
    /// </summary>
    ///
    virtual ~AcDbAssocArrayItem();

    /// transformation specific query methods.

    /// <summary>
    /// Obtains default or compounded transform of this item. Default transform
    /// defines original transform for the item in the array. Compounded 
    /// transform includes relative transformation (if any) applied to the item.
    /// </summary>
    /// <param name="transform"> Returned transformation matrix. </param>
    /// <param name="bCompounded"> A flag to indicate whether compounded or 
    /// default transform to be obtained. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    Acad::ErrorStatus getTransform(AcGeMatrix3d& transform, bool bCompounded = true) const;
    
    /// <summary>
    /// Checks if this items has a relative transform.
    /// </summary>
    /// <returns> true, if item has a relative transform. </returns>
    ///
    bool hasRelativeTransform() const;

    /// <summary>
    /// Applies relative transform to this item.
    /// </summary>
    /// <param name="transform"> Input transformation matrix. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    Acad::ErrorStatus transformBy(const AcGeMatrix3d& transform);
    
    /// <summary>
    /// Sets default transform of this item.
    /// </summary>
    /// <param name="transform"> Input transformation matrix. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    Acad::ErrorStatus setDefaultTransform(const AcGeMatrix3d& transform);
    
    /// Query methods for other properties.

    /// <summary>
    /// Marks the item erased.
    /// </summary>
    /// <param name="bErased"> Input flag to mark erased. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    Acad::ErrorStatus setErased(bool bErased);
    
    /// <summary>
    /// Checks if the item is erased.
    /// </summary>
    /// <returns> true, if this item is erased. </returns>
    ///
    bool isErased() const;

    /// <summary>
    /// Obtains item's spatial index/locator.
    /// </summary>
    /// <returns> AcDbItemLocator, spatial index of the item. </returns>
    ///
    const AcDbItemLocator& locator() const;
    
    /// <summary>
    /// Obtains entity provider for this item.
    /// </summary>
    /// <returns> Object id of entity provider. </returns>
    ///
    const AcDbObjectId& entityProvider() const;
    
    /// <summary>
    /// Sets entity provider for this item.
    /// </summary>
    /// <param name="provider"> Input Object id of entity provider. </param>
    ///
    void setEntityProvider(AcDbObjectId provider);

    /// <summary>
    /// Copies item's content from other object.
    /// </summary>
    /// <param name="other"> Pointer to other item. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

    /// <summary> This function is called by dwgIn(). 
    /// Its purpose is to allow the object to read in its data.
    /// </summary>
    /// <param name="pFiler"> Input pointer to filer to use to read in 
    /// the object's data. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);

    /// <summary> This function is called by dwgOut(). 
    /// Its purpose is to allow the object to write out its data.
    /// </summary>
    /// <param name="pFiler"> Input pointer to filer to use to write out 
    /// the object's data. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

    /// <summary> This function is called by dxfIn(). 
    /// Its purpose is to allow the object to read in its data.
    /// </summary>
    /// <param name="pFiler"> Input pointer to filer to use to read in 
    /// the object's data. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler);

    /// <summary> This function is called by dxfOut(). 
    /// Its purpose is to allow the object to write out its data.
    /// </summary>
    /// <param name="pFiler"> Input pointer to filer to use to write out 
    /// the object's data. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

private:
    AcDbAssocArrayItem(const AcDbAssocArrayItem& other); //Copy constructor.
    friend class AcDbImpAssocArrayItem;
    AcDbImpAssocArrayItem* mpSelf;
};
