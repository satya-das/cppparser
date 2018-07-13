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
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocParamBasedActionBody.h"
#include "AcDbAssocArrayItem.h"

class AcDbVertexRef;
class AcDbAssocArrayParameters;

/// <summary><para>
/// AcDbAssocArrayActionBody class is an associative action which evaluates
/// to manage or position array items. This class in general manages assoc
/// dependencies on various objects related to associative array entity.
/// </para><para>
/// Array enity is generally represented as block reference enity, which
/// references array block table record (array BTR). Array BTR contains a list
/// of entities to represent items in the array. By default this class 
/// represents an array item as an instance of AcDbBlocReference referencing a
/// the source block table record (source BTR) positioned at item transform.
/// </para><para>
/// Derived classes may override array items and may choose to represent them
/// differently.
/// </para></summary>
/// <remarks> Deriving from this class is not supported. </remarks>
///
class ACDB_PORT AcDbAssocArrayActionBody : public AcDbAssocParamBasedActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocArrayActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocArrayActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> Destructor. </summary>
    ///
    virtual ~AcDbAssocArrayActionBody(void);

    /// <summary> Obtains parameters for read. This object must be opened 
    /// at least for read. This method will get invoked only if it is called
    /// on const AcDbAssocArrayActionBody object. </summary>
    /// <returns> Pointer to AcDbAssocArrayParameters. </returns>
    ///
    const AcDbAssocArrayParameters* parameters() const;
    
    /// <summary> Obtains parameters for write. This object must be opened 
    /// at least for write. </summary>
    /// <returns> Pointer to AcDbAssocArrayParameters. </returns>
    ///
    AcDbAssocArrayParameters* parameters();

    /// <summary> Marks the item at given index for erase/unerase. The item at 
    /// given index goes to hidden state, when marked erased. </summary>
    /// <param name="index"> The input spatial index. </param>
    /// <param name="bErase"> The input flag, whether erase or unerase.</param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    Acad::ErrorStatus deleteItem(const AcDbItemLocator& index, bool bErase = true);
    
    /// <summary> Applies a relative transform to an item at given index and 
    /// this transform is remembered by the action body. So when this action
    /// reconfigures all its items, the effect of this additional transform 
    /// will be still be present to the item at given index.
    /// </summary>
    /// <param name="index"> The input spatial index. </param>
    /// <param name="xform"> The input transformation. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    Acad::ErrorStatus transformItemBy(const AcDbItemLocator& index,
                                      const AcGeMatrix3d&    xform);

    /// <summary> Gets indices of all the items owned by this array.</summary>
    /// <param name="indices"> The output list of spatial indices. </param>
    /// <param name="skipErased"> The input flag, whether to skip erased items.
    /// </param>
    void getItems(AcArray<AcDbItemLocator>& indices, bool skipErased = true) const;
    
    /// <summary> Obtains array item at given index as well as subent path of
    /// the item. </summary>
    /// <param name="index"> The input spatial index. </param>
    /// <param name="path">  Returned subent path of item at given index. </param>
    /// <returns> Pointer to AcDbAssocArrayItem at given index, NULL if item is
    /// not available at given index. </returns>
    /// <remarks> Subent type for the returned path is AcDb::kClassSubentType, 
    /// to represent array item. </remarks>
    ///
    const AcDbAssocArrayItem* getItemAt(const AcDbItemLocator& index, 
        AcDbFullSubentPath& path) const;
    inline const AcDbAssocArrayItem* getItemAt(const AcDbItemLocator& index) const
    {
        AcDbFullSubentPath path = AcDbFullSubentPath();
        return getItemAt(index, path);
    }


    /// <summary> Obtains array item at given subent path of the array. 
    /// </summary>
    /// <param name="path"> The input subent path of the array. </param>
    /// <returns> Pointer to AcDbAssocArrayItem at given path, NULL if item is
    /// not available at given path. </returns>
    /// <remarks> The input subent path must point to an entity to locate the 
    /// array item properly. </remarks>
    ///
    const AcDbAssocArrayItem* getItemAt(const AcDbFullSubentPath& path) const;

    /// <summary> Implements evaluation logic for this action. This method is
    /// called by Associative Framework when the owning network is getting
    /// evaluated and this action needs to be evaluated. </summary>
    ///
    virtual void evaluateOverride() ADESK_OVERRIDE;
    
    /// <summary> Obtains object id of the associative array controlled by this
    /// action. </summary>
    /// <returns> AcDbObjectId of the array entity. </returns>
    ///
    virtual AcDbObjectId getArrayEntity() const; 
    
    /// <summary> <para> An item in an associative array can be controlled 
    /// either by the action which has created it or by another action which 
    /// modifies this item. </para><para>
    /// This method checks whether the given item is controlled by this
    /// action. This method returns false in two condition if the index is out
    /// of range or this action is a modification action and doesn't modify 
    /// the given item. </para></summary>
    /// <param name="index"> The input spatial index. </param>
    /// <returns> true, if the item is controlled by this action. </returns>
    ///
    virtual bool controlsItem(const AcDbAssocArrayItem& index) const;

    /// <summary> Transforms the array group/entity by given transform. 
    /// </summary>
    /// <param name="xform"> The input transform. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);
    
    /// <summary> Returns transformation matrix applied to the array group
    /// or entity. </summary>
    /// <returns> AcGeMatrix3d. </returns>
    ///
    virtual AcGeMatrix3d getTransform() const;

    //Methods related to source entities.
    
    /// <summary> Obtains list of source entities for this action. </summary>
    /// <returns> List of source entities used by the action. </returns>
    ///
    AcDbObjectIdArray getSourceEntities() const;
    
    /// <summary> Adds the given entity to the list of source items and updates
    /// each item in the array controlled by this action. The added source entity
    /// will be sent to hidden locked layer and will be managed by this action.
    /// </summary>
    /// <param name="entity"> The input entity to add. </param>
    /// <param name="basePoint"> The input reference point in WCS. This point 
    /// will be used as reference to reposition the newly added source entity.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addSourceEntity(AcDbObjectId entity, 
        const AcGePoint3d& basePoint);
    
    /// <summary> Removes the given entity from the list of source items and 
    /// updates each item in the array controlled by this action. </summary>
    /// <param name="entity"> The input entity to remove. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeSourceEntity(AcDbObjectId entity);

    /// <summary> <para>Sets base point for the source objects. 
    /// Base point is a relative point with respect to source entities using  
    /// which source entities are transformed in the array pattern.
    /// </para><para>
    /// Base point can be defined as constant point or a reference point. This 
    /// point defines grip position on first item (i.e at 0,0,0) in array. 
    /// This method may change array parameters in order to minimize changes
    /// in array object representation.
    /// </para><para>
    /// </para></summary>
    /// <param name="basePoint"> The input base point. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setSourceBasePoint(const AcDbVertexRef& basePoint);

    /// <summary> Gets base point definition for the source objects.</summary>
    /// <param name="vertexRef"> The output vertex reference point. The point
    /// evaluated on vertexRef may not match with the output position of base 
    /// point, as it is evaluated in the space of source BTR.</param>
    /// <param name="position"> The output position for base point. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getSourceBasePoint(AcDbVertexRef& vertexRef,
                                 AcGePoint3d& position) const;

    //utility methods.
    
    /// <summary> Checks if the given entity is an associative array. 
    /// </summary>
    /// <param name="pEntity"> The input entity. </param>
    /// <returns> true, if the input entity is an array. </returns>
    ///
    static bool isAssociativeArray(const AcDbEntity* pEntity);
    
    /// <summary> Obtains creation or modification array action body id 
    /// controlling the given array item. Passing NULL pItemIndex will return
    /// array creation action body. If the given entity is not an associative 
    /// array, this method will return null object id. 
    /// </summary>
    /// <param name="pEntity"> The input entity. </param>
    /// <param name="pItemIndex"> Pointer of array item index. </param>
    /// <returns> AcDbObjectId of array action body controlling given array 
    /// item. </returns>
    ///
    static AcDbObjectId getControllingActionBody(const AcDbEntity* pEntity,
        const AcDbItemLocator* pItemIndex = NULL);

    /// <summary> Extracts array items from the array group as individual items
    /// and removes associativity from the arrayed items controlled by
    /// array action. It also erases the action. Normally erasing array action 
    /// will erase all the arrayed items controlled by the action.
    /// </summary>
    /// <param name="pEntity"> The input entity. </param>
    /// <param name="newIds">  The output exploded entity ids. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    static Acad::ErrorStatus explode(AcDbEntity* pEntity, 
        AcDbObjectIdArray& newIds);

    /// <summary> Removes item override such as position, orientation or 
    /// object replacement, from the list of given items or all items of an
    /// associative array.
    /// </summary>
    /// <param name="arrayEntityId"> The input object id for array entity. 
    /// </param>
    /// <param name="indices">  The input list of item indices which needs to
    /// be reset. This parameter will be ignored if resetAll is true.</param>
    /// <param name="resetAll"> The input flag to indicate, whether all items
    /// of array needs to be reset.</param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    static Acad::ErrorStatus resetArrayItems(AcDbObjectId arrayEntityId,
        const AcArray<AcDbItemLocator>& indices, bool resetAll = false);


    /// <summary> Obtains list of AcDbItemLocator for given set of subents of 
    /// an associative array. The subents provided should be subentity of array
    /// item.
    /// </summary>
    /// <param name="subents">  The input list of item subent path. </param>
    /// <param name="indices">  The output list of AcDbItemLocator for given
    /// list of subents. </param>
    /// <returns> Acad::ErrorStatus </returns>
    /// <remarks> The input subent path must point to an entity to locate the 
    /// array item properly. </remarks>
    ///
    static Acad::ErrorStatus getArrayItemLocators(
        const AcDbFullSubentPathArray& subents, AcArray<AcDbItemLocator>& indices);

    /// <summary> <para> Creates associative array action body as well as array 
    /// entity with given parameters and source entities  This method is 
    /// responsible creating action and attaching appropriate dependencies. 
    /// </para><para> Caller must evaluate top level network after calling this 
    /// method. Non-associative array can be created by calling explode method 
    /// after this action is properly evaluated. </para></summary>
    /// <param name="sourceEntites"> The input list of source entities. </param>
    /// <param name="basePoint">     The input vertex ref to define base point. 
    /// Base point is a relative point with respect to source entities using 
    /// which source entities are transformed in the array pattern.
    /// </param>
    /// <param name="pParameters">   The input parameters for array. </param>
    /// <param name="arrayId">       The returned array object id. </param>
    /// <param name="actionBodyId">  The returned array action body id. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    static Acad::ErrorStatus createInstance(const AcDbObjectIdArray& sourceEntites, 
        AcDbVertexRef& basePoint, const AcDbAssocArrayParameters* pParameters, 
        AcDbObjectId& arrayId, AcDbObjectId& actionBodyId);

    /// <summary> Returns owning block table record for the source items.
    /// </summary>
    /// <returns> AcDbObjectId of source BTR. </returns>
    ///
    AcDbObjectId getArraySourceBTR() const;

    /// <summary>
    /// This method is called by associative framework when any of the dependent
    /// entity is being cloned. This is override of base class method. See the 
    /// description of AcDbAssocAction::addMoreObjectsToDeepClone for more info.
    /// </summary>
    /// <param name="idMap">   The input AcDbIdMapping object.</param>
    /// <param name="additionalObjectsToClone">   The input list of AcDbObjectIds 
    /// to be cloned. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus addMoreObjectsToDeepCloneOverride(AcDbIdMapping& idMap, 
                   AcDbObjectIdArray& additionalObjectsToClone) const ADESK_OVERRIDE;

    /// <summary>
    /// This method is called by associative framework when any of the dependent
    /// entity is being cloned. This is override of base class method. See the 
    /// description of AcDbAssocAction::postProcessAfterDeepClone for more info.
    /// </summary>
    /// <param name="idMap">   The input AcDbIdMapping object. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus postProcessAfterDeepCloneOverride(
                                          AcDbIdMapping& idMap) ADESK_OVERRIDE;

    /// <summary> 
    /// This function is called to notify the action when a there is a drag 
    /// operation in progress and some objects the action depends on, either
    /// directly or indirectly, are being dragged. This is override of base 
    /// class method.
    /// </summary> 
    /// <param name="status"> See the AcDb::DragStat enum. </param>
    /// <returns> Acad::ErrorStatus </returns>
    ///
    virtual Acad::ErrorStatus dragStatusOverride(const AcDb::DragStat status) ADESK_OVERRIDE;
};
