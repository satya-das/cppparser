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
// CREATED BY: Jiri Kripac                                 March 2009
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocParamBasedActionBody.h"
#pragma pack (push, 8)

/// <summary>
/// Base action body class for surface modeling actions whose result is a single 
/// surface. The base class just keeps a dependency on the resulting surface
/// and the "is semiassociative" flag.
/// </summary>
///
class ACDB_PORT AcDbAssocSurfaceActionBody : public AcDbAssocParamBasedActionBody
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocSurfaceActionBody);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocSurfaceActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para> 
    /// Returns the AcDbDependency on the AcDbSurface that is the result of the
    /// evaluation of this action, optionally creating the dependency, it it does
    /// not exist yet. 
    /// </para><para>
    /// If isWriteOnlyDependency is true, the depedency is write-only, the action 
    /// is the creation action on the surface, and is positioned as the very first 
    /// action in the list of actions on the surface. Otherwise the dependency
    /// is read-write and the action is a modification action on the surface.
    /// There is always just a single creation action on a surface but any number 
    /// of modification actions.
    /// </para></summary>
    ///
    AcDbObjectId resultingSurfaceDep(bool createIfDoesNotExist, bool isWriteOnlyDependency = true);

    /// <summary> 
    /// Returns the AcDbSurface that is the result of the evaluation of this action. 
    /// The action has a write-only or read-write dependency on the surface. 
    /// </summary>
    ///
    AcDbObjectId resultingSurface() const;

    /// <summary><para> 
    /// Sets the AcDbSurface that is the result of the evaluation of this action. 
    /// The action has a write-only or read-write dependency on the surface. 
    /// If the dependency does not exist yet, it is created. 
    /// </para><para>
    /// If isWriteOnlyDependency is true, the depedency is write-only, the action 
    /// is the creation action on the surface, and is positioned as the very first 
    /// action in the list of actions on the surface. Otherwise the dependency
    /// is read-write and the action is a modification action on the surface.
    /// There is always just a single creation action on a surface but any number 
    /// of modification actions.
    /// </para></summary>
    ///
    Acad::ErrorStatus setResultingSurface(const AcDbObjectId& surfaceId, bool isWriteOnlyDependency = true);

    /// <summary><para> 
    /// Semi-associative surface shows special surface properties (such as offset
    /// distance for an ofest surface or tangency grips for patach surface) if the 
    /// dependent-on geometries are in the correct positions relative to the 
    /// resulting surface, such as the input profiles of a patch surface coincide 
    /// with the edges of the patch surface. If they are not, the surface becomes 
    /// non-associative and all the actions on the surface are erased.
    /// </para><para>
    /// Internally it means that a semi-associative the surface is in fact fully 
    /// associative, but its evaluate method behaves differently, similarly to 
    /// when an action is evaluated in kModifyActionAssocEvaluationMode mode. 
    /// </para><para>
    /// Instead of updating the surface to match the dependent-on geometries,
    /// it checks if the relation between the dependent-on geometries and the
    /// surface is as expected, and if not, it makes the surface non-associative,
    /// erasing all its actions.
    /// </para></summary> 
    ///
    bool isSemiAssociative() const;

    /// <summary>
    /// Derived surface creation action body classes implement this method to check
    /// and report whether their semi-associativity is satisfied (it is called only 
    /// when the action body is semi-associative). The base-class implementation
    /// just returns true.
    /// </summary>
    ///
    virtual bool isSemiAssociativitySatisfiedOverride() const;

    /// <summary> Overridden implementation of the base class method. </summary>
    ///
    virtual void evaluateOverride() override;

    /// <summary> Overridden implementation of the base class method. </summary>
    ///
    virtual Acad::ErrorStatus getDependentActionsToEvaluateOverride(AcDbActionsToEvaluateCallback*) const override;

    /// <summary> Overridden implementation of the base class method. </summary>
    ///
    virtual Acad::ErrorStatus addMoreObjectsToDeepCloneOverride(
        AcDbIdMapping&, AcDbObjectIdArray& additionalObjectsToClone) const override;

    /// <summary> Overridden implementation of the base class method. </summary>
    ///
    virtual Acad::ErrorStatus dragStatusOverride(const AcDb::DragStat) override;

    /// <summary> 
    /// Finds all actions that affected the given topological subentity (face,
    /// edge, vertex) of the given ASM-based entity (AcDbSurface, AcDb3dSolid, 
    /// AcDbRegion).
    /// </summary>
    /// <remarks>
    /// It does it by collecting all StepIds on the ASM entity and finding all 
    /// actions on the given AcDbObject whose StepId is one of the StepIds
    /// on the ASM entity. These are the actions that somehow caused the 
    /// creation or change of the ASM face/edge/vertex.
    /// </remarks>
    ///
    static Acad::ErrorStatus findActionsThatAffectedTopologicalSubentity(
        const AcDbEntity*  pAsmBasedEntity, 
        const AcDbSubentId&, 
        AcDbObjectIdArray& actionIds);

    /// <summary>
    /// The given AcDbEntity is expected to be of an ASM-based entity (AcDbSurface,
    /// AcDb3dSolid, AcDbRegion). If the entity has actions on it that create or 
    /// modify the entity, then for each action it returns the subentities (faces, 
    /// edges, vertices) of the ASM body that were created or modified by that 
    /// action. Notice that a single subentity may be modified by several actions, 
    /// therefore may show up in the actionSubentIds array of more than one action.
    /// </summary>
    /// <remarks>
    /// The returned array of actionIds is of all actions on the entity, including
    /// internal actions.
    /// </remarks>
    ///
    static Acad::ErrorStatus getTopologicalSubentitiesForActionsOnEntity(
        const AcDbEntity*                pAsmBasedEntity,
        bool                             alsoUseAdjacentTopology,
        AcDbObjectIdArray&               actionIds,
        AcArray<AcArray<AcDbSubentId> >& actionSubentIds);

    /// <summary>
    /// Given an object, finds all AcDbSurfaces that have an action that takes the
    /// given object as input (the action has a read-only dependency on the
    /// object) and the AcDbSurface as output (the action has write-only or 
    /// read-write dependency on the AcDbSurface). The surfaces depend on the
    /// object because when the object is changed, the actions that use this object 
    /// as input are re-evaluated and update the surfaces.
    /// </summary>
    ///
    static Acad::ErrorStatus getSurfacesDirectlyDependentOnObject(
        const AcDbObject*, 
        AcDbObjectIdArray& dependentSurfaceIds);

    /// <summary>
    /// This method is analogous to the like-named method in AcDbEntity. When an 
    /// AcDbSurface has actions that control it and this method is called on the 
    /// AcDbSurface entity, the call is redirected to the corresponding method 
    /// in the creation action of the surface. The action then provides the data 
    /// or performs the operation instead of the AcDbSurface.
    /// </summary>    
    ///
    virtual Acad::ErrorStatus getGripPoints( 
        AcGePoint3dArray& gripPoints,
        AcDbIntArray&     osnapModes,
        AcDbIntArray&     geomIds) const;

    /// <summary>
    /// This method is analogous to the like-named method in AcDbEntity. When an 
    /// AcDbSurface has actions that control it and this method is called on the 
    /// AcDbSurface entity, the call is redirected to the corresponding method 
    /// in the creation action of the surface. The action then provides the data 
    /// or performs the operation instead of the AcDbSurface.
    /// </summary>    
    ///
    virtual Acad::ErrorStatus getGripPoints( 
        AcDbGripDataPtrArray& grips,
        const double          curViewUnitSize,
        const int             gripSize,
        const AcGeVector3d&   curViewDir,
        const int             bitflags) const;

    /// <summary>
    /// This method is analogous to the like-named method in AcDbEntity. When an 
    /// AcDbSurface has actions that control it and this method is called on the 
    /// AcDbSurface entity, the call is redirected to the corresponding method 
    /// in the creation action of the surface. The action then provides the data 
    /// or performs the operation instead of the AcDbSurface.
    /// </summary>    
    ///
    virtual Acad::ErrorStatus moveGripPoints( 
        const AcDbIntArray& indices,
        const AcGeVector3d& offset);

    /// <summary>
    /// This method is analogous to the like-named method in AcDbEntity. When an 
    /// AcDbSurface has actions that control it and this method is called on the 
    /// AcDbSurface entity, the call is redirected to the corresponding method 
    /// in the creation action of the surface. The action then provides the data 
    /// or performs the operation instead of the AcDbSurface.
    /// </summary>    
    ///
    virtual Acad::ErrorStatus moveGripPoints( 
        const AcDbVoidPtrArray& gripAppData,
        const AcGeVector3d&     offset,
        const int               bitflags);

    /// <summary>
    /// This method is analogous to the like-named method in AcDbEntity. When an 
    /// AcDbSurface has actions that control it and this method is called on the 
    /// AcDbSurface entity, the call is redirected to the corresponding method 
    /// in the creation action of the surface. The action then provides the data 
    /// or performs the operation instead of the AcDbSurface.
    /// </summary>    
    ///
    virtual Acad::ErrorStatus moveStretchPoints( 
        const AcDbIntArray& indices,
        const AcGeVector3d& offset);

    /// <summary>
    /// This method is analogous to the like-named method in AcDbEntity. When an 
    /// AcDbSurface has actions that control it and this method is called on the 
    /// AcDbSurface entity, the call is redirected to the corresponding method 
    /// in the creation action of the surface. The action then provides the data 
    /// or performs the operation instead of the AcDbSurface.
    /// </summary>    
    ///
    virtual void gripStatus(const AcDb::GripStat status);

    /// <summary>
    /// This method is analogous to the like-named method in AcDbEntity. When an 
    /// AcDbSurface has actions that control it and this method is called on the 
    /// AcDbSurface entity, the call is redirected to the corresponding method 
    /// in the creation action of the surface. The action then provides the data 
    /// or performs the operation instead of the AcDbSurface.
    /// </summary>    
    ///
    virtual Acad::ErrorStatus getGripEntityUCS( 
        const void*   pGripAppData, 
        AcGeVector3d& normalVec,
        AcGePoint3d&  origin,
        AcGeVector3d& xAxis) const;

    /// <summary>
    /// This method is analogous to the like-named method in AcDbEntity. When an 
    /// AcDbSurface has actions that control it and this method is called on the 
    /// AcDbSurface entity, the call is redirected to the corresponding method 
    /// in the creation action of the surface. The action then provides the data 
    /// or performs the operation instead of the AcDbSurface.
    /// </summary>    
    ///
    virtual void list() const;

}; // class AcDbAssocSurfaceActionBody


#pragma pack (pop)

