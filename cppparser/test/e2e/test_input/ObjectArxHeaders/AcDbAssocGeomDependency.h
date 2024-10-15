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
// CREATED BY: Jiri Kripac                                 April 2007
//
// DESCRIPTION:
//
// AcDbAssocGeomDependency class. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocDependency.h"
#include "AcDbAssocPersSubentId.h"
#pragma pack (push, 8)


/// <summary> <para>
/// This class represents a dependency on a subentity (face/edge/vertex) of
/// a geometric entity. It keeps an AcDbAssocPersSubentId that persistently 
/// identitfies the subentity and provides new protocol to set the referenced 
/// subentity and get/set the subentity geometry.
/// </para> <para>
/// This class may also optionally cache the geometry of the referenced 
/// subentity that then allows to filter-out irrelevant change notifications 
/// that do no affect the referenced subentity. The caching is controlled by 
/// the setCachingSubentityGeometry() method.
/// </para> <para>
/// By default the dependency does not cache the geoemetry of the referenced 
/// subentity. The isRelevantChange() predicate uses the base class implementation 
/// that calls AcDbAssocAction::isRelevantDependencyChange() of the owning action, 
/// letting the action that owns the dependency to decide, such as by caching the 
/// geometry of the referenced subentity and comparing it with the current 
/// subentity geometry.
/// </para> <para>
/// When the dependency caches the geometry of the referenced subentity, the
/// isRelevantChange() predicate returns false if the geometry of the 
/// referenced subentity is the same as the cached geometry. This is how the 
/// dependency can filer-out irrelevant change notifications when the referenced 
/// subentity geometry does not really change, when something else changes.
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocGeomDependency : public AcDbAssocDependency
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocGeomDependency);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocGeomDependency(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Returns pointer to the internally held AcDbAssocPersSubentId that
    /// identifies a subentity of the dependent-on entity. The returned pointer 
    /// points to internal data owned by this class. The caller must not change 
    /// or hold-on to this returned AcDbAssocPersSubentId, only call read-only 
    /// methods on it. The retuned pointer may be NULL.
    /// </summary>
    /// <returns> Pointer to the internal AcDbAssocPersSubentId or NULL. </returns>
    ///
    const AcDbAssocPersSubentId* persistentSubentId() const;

    /// <summary> 
    /// Returns the transient AcDbSubentIds of the dependent-on entity
    /// corresponding to the internally held AcDbAssocPersSubentId. Notice that
    /// one AcDbAssocPersSubentId may generally correspond to none, one, or 
    /// more than one subentity, though in typical cases it will be exactly one 
    /// subentity.
    /// </summary>
    /// <param name="transientSubentIds"> 
    /// The returned transient AcDbSubentIds corresponding to the internally 
    /// held AcDbAssocPersSubentId. 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getTransientSubentIds(AcArray<AcDbSubentId>& transientSubentIds) const;

    /// <summary>
    /// Sets the internally held AcDbAssocPersSubentId to persistently identify
    /// the given subentity. The subentity must be on the entity the dependency
    /// currently depends on.
    /// </summary>
    /// <param name="transientSubentId"> 
    /// The subentity to be identified by the internally held AcDbAssocPersSubentId.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setSubentity(const AcDbSubentId& transientSubentId);

    /// <summary>
    /// Returns the type of the persistently referenced subentity or 
    /// kNullSubentType if no subentity is referenced.
    /// </summary>
    /// <returns> The referenced subentity type. </returns>
    ///
    AcDb::SubentType subentType() const;

    /// <summary>
    /// Returns the number of transient AcDbSubentIds corresponding to the
    /// internally held AcDbAssocPersSubentId. In typical cases it is just 
    /// a single subentity but in general case it may be none, one or any number 
    /// of subentities.
    /// </summary>
    /// <returns> The transient subentity count (usually 1). </returns>
    ///
    int transientSubentCount() const;

    /// <summary>
    /// Returns true iff the dependency keeps cache of the referenced subentity
    /// geometry (even if the cache may currently be empty). The initial state 
    /// is false, i.e. the dependency does not keep the subentity geometry cache.
    /// </summary>
    /// <returns>
    /// Returns true iff the dependency keeps cache of the referenced subentity
    /// geometry. 
    /// </returns>
    ///
    bool isCachingSubentityGeometry() const;

    /// <summary>
    /// Sets whether the dependency is to keep the cache of the referenced 
    /// subentity geometry. The initial state is false, i.e. the dependency 
    /// does not keep the subentity geometry cache.
    /// </summary>
    /// <param name="yesNo"> Controls whether the dependency should keep the 
    /// cache of the referenced subentity geometry.
    /// </param>
    ///
    void setCachingSubentityGeometry(bool yesNo);

    /// <summary>
    /// Gets coordinates of vertex subentities corresponding to the internally 
    /// held AcDbAssocPersSubentId, which must identify a vertex subentity type.
    /// Notice that one AcDbAssocPersSubentId may generally correspond to any 
    /// number of subentities, though in most cases it will be just one subentity.
    /// </summary>
    /// <param name="vertexPositions"> Returned coordinates of vertex subentities. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getVertexSubentityGeometry(AcGePoint3dArray& vertexPositions) const;

    /// <summary>
    /// Gets curves of edge subentities corresponding to the internally 
    /// held AcDbAssocPersSubentId, which must identify an edge subentity type. 
    /// Notice that one AcDbAssocPersSubentId may generally correspond to any 
    /// number of subentities, though in most cases it will be just one subentity. 
    /// The caller will become the owner of the returned curves and is 
    /// responsible for freeing them after thay are not needed. 
    /// </summary>
    /// <param name="edegeCurves"> 
    /// Returned curves of edge subentities (the caller becomes their owner). 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getEdgeSubentityGeometry(AcArray<AcGeCurve3d*>& edgeCurves) const;

    /// <summary>
    /// Gets surfaces of face subentities corresponding to the internally 
    /// held AcDbAssocPersSubentId, which must identify a face subentity type. 
    /// Notice that one AcDbAssocPersSubentId may generally correspond to any 
    /// number of subentities, though in most cases it will be just one subentity. 
    /// The caller will become the owner of the returned surfaces and is 
    /// responsible for freeing them after thay are not needed. 
    /// </summary>
    /// <param name="faceSurfaces"> 
    /// Returned surfaces of face subentities (the caller becomes their owner). 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getFaceSubentityGeometry(AcArray<AcGeSurface*>& faceSurfaces) const;

    /// <summary>
    /// Sets coordinates of vertex subentities corresponding to the internally 
    /// held AcDbAssocPersSubentId, which must identify a vertex subentity type.
    /// Notice that one AcDbAssocPersSubentId may generally correspond to any 
    /// number of subentities, though in most cases it will be just one subentity.
    /// The length of the input array must be the same as the number of subentities
    /// corresponding to the internally held AcDbAssocPersSubentId.
    /// </summary>
    /// <param name="newVertexPositions">  New coordinates of vertex subentities. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setVertexSubentityGeometry(const AcGePoint3dArray& newVertexPositions);

    /// <summary>
    /// Sets curves of edge subentities corresponding to the internally 
    /// held AcDbAssocPersSubentId, which must identify an edge subentity type. 
    /// Notice that one AcDbAssocPersSubentId may generally correspond to any 
    /// number of subentities, though in most cases it will be just one subentity. 
    /// The length of the input array must be the same as the number of subentities
    /// corresponding to the internally held AcDbAssocPersSubentId.
    /// The pased-in curves are not reused but copied, they do not become owned 
    /// by the dependency.
    /// </summary>
    /// <param name="newEdgeCurves"> 
    /// New curves of edge subentities (copied, not reused). 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setEdgeSubentityGeometry(const AcArray<const AcGeCurve3d*>& newEdgeCurves);

    /// <summary>
    /// Sets surfaces of face subentities corresponding to the internally 
    /// held AcDbAssocPersSubentId, which must identify a surface subentity type. 
    /// Notice that one AcDbAssocPersSubentId may generally correspond to any 
    /// number of subentities, though in most cases it will be just one subentity. 
    /// The length of the input array must be the same as the number of subentities
    /// corresponding to the internally held AcDbAssocPersSubentId.
    /// The pased-in surfraces are not reused but copied, they do not become 
    /// owned by the dependency.
    /// </summary>
    /// <param name="newFaceSurfaces"> 
    /// New surfaces of face subentities (copied, not reused). 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setFaceSubentityGeometry(const AcArray<const AcGeSurface*>& newFaceSurfaces);

    /// <summary>
    /// Called by the client code to inform the AcDbAssocGeomDependency that 
    /// the object, whose subentity it depends on, has been mirrored. The 
    /// dependency then mirrors the AcDbAssocPersSubentId it holds. For the 
    /// majority of dependent-on entity types it is just a no-op, but for some
    /// entity types (such as for AcDbArc) the AcDbAssocPersSubentId needs to 
    /// be actually updated. 
    /// </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus dependentOnObjectMirrored();

    /// <summary>
    /// Returns true iff the dependency keeps cache of the referenced subentity
    /// geometry and the cache is not empty.
    /// </summary>
    /// <returns>
    /// Returns true iff the dependency holds the cached geoemetry of the 
    /// referenced subentity.
    /// </returns>
    ///
    /// bool hasCachedValue() const;

    /// <summary>
    /// If caching the subentity geometry, evaluates the subentity geometry 
    /// cache from the current geometry of the referenced subentity and sets 
    /// the status to kIsUpToDateAssocStatus. Otherwise the base class 
    /// implementation of this method forwards the call to the owning action's 
    /// AcDbAssocAction::evaluateDependency() method. 
    /// </summary>
    ///
    /// void evaluate();

    /// <summary> 
    /// If caching the subentity geometry, returns true iff the geometry of the 
    /// referenced subentity is different from the cached subentity geometry.
    /// Otherwise the base class implementation of this method forwards the call 
    /// to the owning action's AcDbAssocAction::isRelevantDependencyChange() 
    /// predicate.
    /// </summary> 
    /// <returns> 
    /// <para> true  = The subentity geometry changed. </para>
    /// <para> false = The subentity geometry didn't change. </para>
    /// </returns>
    ///
    /// bool isRelevantChange() const;

    /// <summary> 
    /// Returns true iff this dependency depends on exactly the same subentity
    /// of the same geometric entity as the other dependency.
    /// </summary> 
    /// <param name="pOtherDependency"> The other AcDbAssocGeomDependency, open at least for read. </param>
    /// <returns> 
    /// True iff both dependencies depend on exactly the same subentity of the same entity.
    /// </returns>
    ///
    /// bool isDependentOnTheSameThingAs(const AcDbAssocDependency* pOtherDependency) const;

    /// <summary> 
    /// Gets all AcDbAssocGeomDependencies on the old object that reference
    /// the given oldSubentId of that object and redirects them to reference 
    /// the newSubentId of the new object.
    /// </summary>
    /// <param name="oldObjectId"> 
    /// The AcDbObject whose AcDbAssocGeomDependencies are to be redirected. 
    /// It will be opened for write.
    /// </param>
    /// <param name="oldSubentId"> 
    /// The AcDbSubentId of the AcDbAssocGeomDependencies that is to be
    /// redirected.
    /// </param>
    /// <param name="newObjectId"> 
    /// The object to redirect the dependencies to. It will be opened for write.
    /// </param>
    /// <param name="newSubentId"> The new AcDbSubentId in the new object. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus redirectToAnotherSubentity(const AcDbObjectId& oldObjectId,
                                                        const AcDbSubentId& oldSubentId,
                                                        const AcDbObjectId& newObjectId,
                                                        const AcDbSubentId& newSubentId);

}; // class AcDbAssocGeomDependency

#pragma pack (pop)


