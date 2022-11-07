////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// CREATED BY: Jiri Kripac                                 March 2007
//
// DESCRIPTION:
//
// AcDbAssocPersSubentIdPE AcRx protocol extension abstract base class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocSimplePersSubentId.h"
#pragma pack (push, 8)

class AcDbCompoundObjectId;
class AcDbIdMapping;

#ifndef ADESK_UNREFED_PARAM
#define ADESK_UNREFED_PARAM(P)  (P)
#endif

/// <summary> Rigid set type. </summary>
///
enum RigidSetType
{
  /// <summary> Not a rigid set. </summary>
  kNotRigidSet = 0,

  /// <summary> A rigid set that can be uniformly scaled. </summary>
  kScalableRigidSet,

  /// <summary> A rigid set that cannot be scaled. </summary>
  kNonScalableRigidSet
};


/// <summary> <para>
/// AcRx protocol extension base class that defines protocol to obtain a persistent 
/// AcDbAssocPersSubentId from a transient AcDbSubentId. It also adds subentity 
/// query and manipulation protocol that is not available in the AcDbEntity class 
/// proper so that the client code can manipulate subentities of entities.
/// </para> <para>
/// The derived concrete classes implement this protocol for the individual
/// derived AcDbEntity classes. Only the methods that are pertinent to the 
/// particular AcDbEntity type need to be overridden.
/// </para> <para>
/// Notice that ObjectARX provides implementation of the AcDbAssocPersSubentIdPE
/// protocol extension for the common entity types such as AcDbLine, AcDbCircle,
/// AcDbArc, AcDbPolyline, AcDb2dPolyline, etc.
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocPersSubentIdPE : public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocPersSubentIdPE);

    /// <summary> <para>
    /// Mapping: AcDbSubentId --> AcDbAssocPersSubentId
    /// <para> </para>
    /// Creates a new AcDbAssocPersSubentId object from a given AcDbSubentId. 
    /// The default implementation creates an AcDbSimplePersSubentId that just
    /// holds the given AcDbSubentId.
    /// </para> </summary>
    /// <param name="pEntity"> 
    /// The entity must be open for write, but usually no changes to the 
    /// entity will be made (usually no assertWriteEnabled() will be called).
    /// </param>
    /// <param name="pDatabase"> 
    /// The database that the newly created AcDbAssocPersSubentId is going to belong to.
    /// It may be a different database than the database of the given AcDbEntity when
    /// the entity is in an XREF database but the AcDbAssocPersSubentId is going to
    /// be owned by an object in the host database. If the database pointer is NULL,
    /// the database of the entity is used.
    /// </param>
    /// <param name="compId"> 
    /// Contains optional full context path to pEntity. Can be empty for simple reference.
    /// </param>
    /// <param name="subentId"> Transient AcDbSubentId. </param>
    /// <returns> The newly created AcDbAssocPersSubentId or NULL if it cannot be created. </returns>
    ///
    virtual AcDbAssocPersSubentId* createNewPersSubent(AcDbEntity*                 pEntity,
                                                       AcDbDatabase*               pDatabase,
                                                       const AcDbCompoundObjectId& /*compId*/,
                                                       const AcDbSubentId&         subentId)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(pDatabase);

        return new AcDbAssocSimplePersSubentId(subentId);
    }

    /// <summary>
    /// Needs to be called when an AcDbAssocPersSubentId is no more needed, to inform
    /// to release and resources possibly associated with this AcDbAssocPersSubentId.
    /// The AcDbAssocPersSubentId object may just keep an index and there is a complex
    /// data structure somewhere that keeps data for that index. Deleting the 
    /// AcDbAssocPersSubentId would just make this data in the complex data structure 
    /// orphaned, but the data would stay around and never removed.
    /// </summary>
    /// <param name="pEntity"> 
    /// The entity must be open for write, but usually no changes to the 
    /// entity will be made (usually no assertWriteEnabled() will be called).
    /// </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param  name="pPerSubentId"> 
    /// The persistent subentity id on the entity that is to be released. 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus releasePersSubent(AcDbEntity*                  pEntity, 
                                                AcDbDatabase*                pDatabase,
                                                const AcDbAssocPersSubentId* pPerSubentId)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(pDatabase);
        ADESK_UNREFED_PARAM(pPerSubentId);
        return Acad::eOk;
    }

    /// <summary>
    /// Redirects the given AcDbAssocPersSubentId that currently refers to a subentity
    /// in the current entity to refer to the same subentity in the new entity.
    /// It is assumed that the old and new entities are topologically equal (such as the 
    /// new entity is a clone of the old one), so that the transfer can be accomplished 
    /// by simply remapping the data associatied with the AcDbAssocPersSubentId. Notice 
    /// that the AcDbAssocPersSubentId itself does not change, only the data associated
    /// with it and kept somewhere else.
    /// </summary>
    /// <param name="pToEntity"> 
    /// The entity to redirect the AcDbAssocPersSubentId to. It must be open for write, 
    /// but usually no changes to the entity will be made (usually no assertWriteEnabled() 
    /// will be called).
    /// </param>
    /// <param name="pToDatabase"> 
    /// The database that the AcDbAssocPersSubentId should belong to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param name="pFromEntity"> 
    /// The entity to redirect the AcDbAssocPersSubentId from. It must be open for write, 
    /// but usually no changes to the entity will be made (usually no assertWriteEnabled() 
    /// will be called). It may even be NULL, e.g. when the entity is not available any more.
    /// </param>
    /// <param name="pFromDatabase"> 
    /// The database that the AcDbAssocPersSubentId currently belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param  name="pPersSubentId"> 
    /// The persistent subentity id that is going to be redirected to refer to a subentity
    /// in the new entity. Notice that the AcDbAssocPersSubentId is const does not change, 
    /// only the data associated with it and kept somewhere else.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus transferPersSubentToAnotherEntity(
        AcDbEntity*                  pToEntity,
        AcDbDatabase*                pToDatabase,
        AcDbEntity*                  pFromEntity,
        AcDbDatabase*                pFromDatabase,
        const AcDbAssocPersSubentId* pPersSubentId)
    {
        ADESK_UNREFED_PARAM(pToEntity);
        ADESK_UNREFED_PARAM(pToDatabase);
        ADESK_UNREFED_PARAM(pFromEntity);
        ADESK_UNREFED_PARAM(pFromDatabase);
        ADESK_UNREFED_PARAM(pPersSubentId);
        return Acad::eOk;
    }

    /// <summary><para>
    /// Allows to automatically call releasePersSubent() on the AcDbAssocPersSubentId if
    /// it is no more used. What "no more used" means, who checks for it, and which code 
    /// implements the purging is defined by the application that the AcDbAssocPersSubentId 
    /// relates to. By default the AcDbAssocPersSubentIds are not automatically purgeable.
    /// </para><para>
    /// When an AcDbAssocPersSubentId is created by AcDbAssocGeomDependency::setSubentity(),
    /// the created AcDbAssocPersSubentIds is made purgeable, because on file open all
    /// AcDbAssocActions, AcDbAssocDependencies and all AcDbObjects the dependencies depend
    /// are visited, all used ids can be safely collected and the not used ones can be automatically 
    /// purged.
    /// </para><para>
    /// This purging is because of the infamous lazy-erase mess in AutoCAD when only
    /// the parent object is erased but not its children. The children are not erased,
    /// do not know that their parent was erased, but when saving to a file, they are not 
    /// saved, because their parent is not saved. 
    /// When the file is open, these objects are not in the file any more. If there are 
    /// some other resources related to these not-saved objects but kept in some other place, 
    /// these resources are not released because the not-saved objects had no opportunity 
    /// to request to release these resources, i.e., in our scenario to call releasePersSubent().
    /// </para><para>
    /// Currently this method is only implemented by AcDbAssocAsmBasedEntityPersSubentIdPE
    /// that interacts with AcDbAssocPersSubentManager.
    /// </para></summary>
    /// <param name="pEntity"> 
    /// The entity must be open for write, but usually no changes to the 
    /// entity will be made (usually no assertWriteEnabled() will be called).
    /// </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param  name="pPerSubentId"> 
    /// The persistent subentity id on the entity that is to be made purgeable or not. 
    /// </param>
    /// <param  name="yesNo"> Make the given AcDbAssocPersSubentId purgeable or not. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus makePersSubentPurgeable(AcDbEntity*                  pEntity, 
                                                      AcDbDatabase*                pDatabase,
                                                      const AcDbAssocPersSubentId* pPerSubentId,
                                                      bool                         yesNo) 
    { 
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(pDatabase);
        ADESK_UNREFED_PARAM(yesNo);
        ADESK_UNREFED_PARAM(pPerSubentId);
        return Acad::eOk; 
    }

    /// <summary> <para>
    /// Mapping: AcDbAssocPersSubentId --> AcDbSubentId(s)
    /// </para> <para>
    /// Obtains all AcDbSubentIds of the provided AcDbEntity that correspond to
    /// the provided AcDbAssocPersSubentId.
    /// </para> </summary>
    /// <remarks>
    /// Notice that one AcDbAssocPersSubentId may correspond to none, one or more
    /// that one AcDbSubentId, because the entity may have changed and there may 
    /// not be just a single subentity corresponding to the original subentity 
    /// identified by the AcDbAssocPersSubentId.
    /// </remarks>
    /// <param  name="pEntity"> The entity needs to be open for read. </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param  name="pPersSubentId"> The persistent subentity id on the entity. </param>
    /// <param  name="subents"> The returned AcDbSubentIds. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getTransientSubentIds(const AcDbEntity*            pEntity, 
                                                    AcDbDatabase*                pDatabase,
                                                    const AcDbAssocPersSubentId* pPersSubentId,
                                                    AcArray<AcDbSubentId>&       subents) const;

    /// <summary>
    /// Gets all subentities of the given type. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="subentType"> The required type of the subentities. </param>
    /// <param name="allSubentIds">  Returned AcDbSubentIds of the required type. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getAllSubentities(const AcDbEntity*      pEntity,
                                                AcDb::SubentType       subentType,
                                                AcArray<AcDbSubentId>& allSubentIds)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(subentType);
        ADESK_UNREFED_PARAM(allSubentIds);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets all subentities of the given class for kClassSubentType subentity type.
    /// The default implementation just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="pSubentClass"> The required class of the subentities for kClassSubentType. </param>
    /// <param name="allSubentIds">  Returned AcDbSubentIds of the required type. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getAllSubentities(const AcDbEntity*      pEntity,
                                                const AcRxClass*       pSubentClass,
                                                AcArray<AcDbSubentId>& allSubentIds)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(pSubentClass);
        ADESK_UNREFED_PARAM(allSubentIds);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the vertex AcDbSubentIds corresponding to the given edge AcDbSubentId.
    /// This protocol is needed to query the relations between the edge and vertex
    /// subentities. The default implementation just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="edgeSubentId"> 
    /// Edge AcDbSubentId whose vertex AcDbSubentIds are to be obtained. 
    /// </param>
    /// <param name="startVertexSubentId"> 
    /// Returned AcDbSubentId of the start vertex of the edge (or kNullSubentId 
    /// if there is not any). 
    /// </param>
    /// <param name="endVertexSubentId"> 
    /// Returned AcDbSubentId of the end vertex of the edge (or kNullSubentId 
    /// if there is not any). 
    /// </param>
    /// <param name="otherVertexSubentIds"> 
    /// Returned other AcDbSubentIds associated with the edge, such as the 
    /// circle or arc center, spline control and fit points, etc.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getEdgeVertexSubentities(const AcDbEntity*      pEntity,
                                                       const AcDbSubentId&    edgeSubentId,
                                                       AcDbSubentId&          startVertexSubentId,
                                                       AcDbSubentId&          endVertexSubentId,
                                                       AcArray<AcDbSubentId>& otherVertexSubentIds)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(edgeSubentId);
        ADESK_UNREFED_PARAM(startVertexSubentId);
        ADESK_UNREFED_PARAM(endVertexSubentId);
        ADESK_UNREFED_PARAM(otherVertexSubentIds);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the vertex AcDbSubentIds corresponding to the given edge AcDbSubentId
    /// whose geometry is defined by a spline. 
    /// This protocol is needed to query the relations between the edge and vertex
    /// subentities. The default implementation just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="edgeSubentId"> 
    /// Edge AcDbSubentId whose vertex AcDbSubentIds are to be obtained. 
    /// </param>
    /// <param name="startVertexSubentId"> 
    /// Returned AcDbSubentId of the start vertex of the edge (or kNullSubentId 
    /// if there is not any). 
    /// </param>
    /// <param name="endVertexSubentId"> 
    /// Returned AcDbSubentId of the end vertex of the edge (or kNullSubentId 
    /// if there is not any). 
    /// </param>
    /// <param name="controlPointSubentIds"> 
    /// Returned AcDbSubentIds identifying the spline control points. The order
    /// is the same as the order of the spline control points.
    /// </param>
    /// <param name="fitPointSubentIds"> 
    /// Returned AcDbSubentIds identifying the spline fit points (if any). 
    /// The order is the same as the order of the spline fit points.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getSplineEdgeVertexSubentities(const AcDbEntity*      pEntity,
                                                             const AcDbSubentId&    edgeSubentId,
                                                             AcDbSubentId&          startVertexSubentId,
                                                             AcDbSubentId&          endVertexSubentId,
                                                             AcArray<AcDbSubentId>& controlPointSubentIds,
                                                             AcArray<AcDbSubentId>& fitPointSubentIds)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(edgeSubentId);
        ADESK_UNREFED_PARAM(startVertexSubentId);
        ADESK_UNREFED_PARAM(endVertexSubentId);
        ADESK_UNREFED_PARAM(controlPointSubentIds);
        ADESK_UNREFED_PARAM(fitPointSubentIds);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the coordinates of a vertex subentity. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="vertexSubentId"> Vertex AcDbSubentId whose position is to be obtained. </param>
    /// <param name="vertexPosition"> Returned coordinates of the vertex subentity. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getVertexSubentityGeometry(const AcDbEntity*   pEntity,
                                                         const AcDbSubentId& vertexSubentId,
                                                         AcGePoint3d&        vertexPosition)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(vertexSubentId);
        ADESK_UNREFED_PARAM(vertexPosition);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the curve of an edge subentity. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="edgeSubentId"> Edge AcDbSubentId whose curve is to be obtained. </param>
    /// <param name="pEdgeCurve"> Returned curve of the edge subentity (the caller becomes its owner). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getEdgeSubentityGeometry(const AcDbEntity*   pEntity,
                                                       const AcDbSubentId& edgeSubentId,
                                                       AcGeCurve3d*&       pEdgeCurve)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(edgeSubentId);
        ADESK_UNREFED_PARAM(pEdgeCurve);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Gets the surface of a face subentity. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="faceSubentId"> Face AcDbSubentId whose surface is to be changed. </param>
    /// <param name="pFaceSurface"> Returned surface of the face subentity (the caller becomes its owner). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getFaceSubentityGeometry(const AcDbEntity*   pEntity,
                                                       const AcDbSubentId& faceSubentId,
                                                       AcGeSurface*&       pFaceSurface)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(faceSubentId);
        ADESK_UNREFED_PARAM(pFaceSurface);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Change the geometry of a vertex subentity. The subentity can also be
    /// transformed, but for doing so there already is AcDbEntity protocol so
    /// no protocol extension is needed. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="vertexSubentId"> Vertex AcDbSubentId whose position is to be changed. </param>
    /// <param name="newVertexPosition"> New coordinates of the vertex subentity. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setVertexSubentityGeometry(AcDbEntity*         pEntity,
                                                         const AcDbSubentId& vertexSubentId,
                                                         const AcGePoint3d&  newVertexPosition)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(vertexSubentId);
        ADESK_UNREFED_PARAM(newVertexPosition);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Change the curve of an edge subentity. The subentity can also be
    /// transformed, but for doing so there already is AcDbEntity protocol so
    /// no protocol extension is needed.  The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="edgeSubentId"> Edge AcDbSubentId whose curve is to be changed. </param>
    /// <param name="pNewEdgeCurve"> New curve of the edge subentity (copied, not reused). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setEdgeSubentityGeometry(AcDbEntity*         pEntity,
                                                       const AcDbSubentId& edgeSubentId,
                                                       const AcGeCurve3d*  pNewEdgeCurve)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(edgeSubentId);
        ADESK_UNREFED_PARAM(pNewEdgeCurve);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Change the surface of a face subentity. The subentity can also be
    /// transformed, but for doing so there already is AcDbEntity protocol so
    /// no protocol extension is needed. The default implementation
    /// just returns Acad::eNotImplemented.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="faceSubentId"> Face AcDbSubentId whose surface is to be changed. </param>
    /// <param name="pNewFaceSurface"> New surface of the face subentity (copied, not reused). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setFaceSubentityGeometry(AcDbEntity*         pEntity,
                                                       const AcDbSubentId& faceSubentId,
                                                       const AcGeSurface*  pNewFaceSurface)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(faceSubentId);
        ADESK_UNREFED_PARAM(pNewFaceSurface);
        return Acad::eNotImplemented;
    }

    /// <summary><para>
    /// Gets the geometry of a subentity. 
    /// </para><para>
    /// For AcDb::kFaceSubentTpe, AcDb::kEdgeSubentType, AcDb::kVertexSubentType the default 
    /// implementation calls getFace/Edge/VertexSubentityGeometry(). For other subentity types 
    /// the default implementation returns Acad::eNotImplemented.
    /// </para></summary>
    /// <remarks>
    /// Geometry of a vertex subentity is returned in an AcGePosition3d object.
    /// </remarks>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="subentId"> AcDbSubentId whose geometry is to be obtained. </param>
    /// <param name="pSubentityGeometry"> Returned geometry of the subentity. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getSubentityGeometry(const AcDbEntity*   pEntity,
                                                   const AcDbSubentId& subentId,
                                                   AcGeEntity3d*&      pSubentityGeometry);

    /// <summary><para>
    /// Changes the geometry of a subentity. 
    /// </para><para>
    /// For AcDb::kFaceSubentTpe, AcDb::kEdgeSubentType, AcDb::kVertexSubentType the default 
    /// implementation calls setFace/Edge/VertexSubentityGeometry(). For other subentity types 
    /// the default implementation returns Acad::eNotImplemented.
    /// </para></summary>
    /// <remarks>
    /// Geometry of a vertex subentity is passed in as an AcGePosition3d object.
    /// </remarks>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="subentId"> AcDbSubentId whose geometry is to be changed. </param>
    /// <param name="pNewSubentityGeometry"> New geometry of the subentity (copied, not reused). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setSubentityGeometry(AcDbEntity*         pEntity,
                                                   const AcDbSubentId& subentId,
                                                   const AcGeEntity3d* pNewSubentityGeometry);

    /// <summary><para>
    /// Gets silhouette curves of a face at the given projection. If transientSilhIds is empty, 
    /// it returns all of them because it is the way silhouettes are usually evaluated by the
    /// modeling system. If transientSilhIds contains transient ids of some silhouettes,
    /// it only returns silhouette curves for these silhouettes of the face. 
    /// </para><para>
    /// The transientSilhIds are relative to the given face and the given projection, 
    /// not global for the whole entity.
    /// </para><para>
    /// The default implementation just clears the output silhCurves array and returns Acad::eNotImplemented.
    /// </para></summary>
    /// <param name="pEntity"> The entity must be open for write (in case it needs to do some caching). </param>
    /// <param name="pContext"> Additional context info that may be needed. Its meaning is client-specific. </param>
    /// <param name="pEntityTransform"> Optional transform of the entity (may be NULL). </param>
    /// <param name="faceSubentId"> Face AcDbSubentId whose silhouette curves are to be obtained. </param>
    /// <param name="pProjector"> Current projection parameters. Silhouettes are view-dependent. </param>
    /// <param name="transientSilhIds"><para>
    /// If the paassed-in array is empty, it is used as an output argument to return ids 
    /// of all the returned silhouette curves. The ids are transient, i.e. when the entity 
    /// changes, different ids may be returned. 
    /// </para><para>
    /// If the passed-in array is not empty, it is used as an input argument specifying which 
    /// sihouette curves to return.
    /// </para><para>
    /// Id 0 is reserved and means null id, and must not be used as a transient id of a valid silhouette.
    /// </para></param>
    /// <param name="silhCurves"> 
    /// Returned face silhouette curves (the caller becomes their owner).
    /// The length of the silhCurves and silhIds arrays must be the same.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getFaceSilhouetteGeometry(AcDbEntity*                  pEntity,
                                                        AcRxObject*                  pContext,
                                                        const AcDbSubentId&          faceSubentId,
                                                        const AcGeMatrix3d*          pEntityTransform,
                                                        class AcDbGeometryProjector* pGeometryProjector,
                                                        AcArray<int>&                transientSilhIds, // Either in or out argument
                                                        AcArray<AcGeCurve3d*>&       silhCurves)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(pContext);
        ADESK_UNREFED_PARAM(faceSubentId);
        ADESK_UNREFED_PARAM(pEntityTransform);
        ADESK_UNREFED_PARAM(pGeometryProjector);
        ADESK_UNREFED_PARAM(transientSilhIds);

        silhCurves.removeAll();
        return Acad::eNotImplemented;
    }

    /// <summary><para>
    /// Returns a persistent silhouette id for the given transient silhouette id of a face. 
    /// Notice that a transient silhouette id is just an integer number but a persistent
    /// silhouette id is a complete AcDbAssocPersSubentId object.
    /// </para><para>
    /// The transientSilhId is relative to the given face and the given projection, 
    /// not global for the whole entity.
    /// </para><para>
    /// Id 0 is reserved and means null id, and must not be used as a transient id of a valid silhouette.
    /// </para><para>
    /// The default implementation just returns NULL.
    /// </para></summary>
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write (in case it needs to do some caching). </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param name="pContext"> Additional context info that may be needed. Its meaning is client-specific. </param>
    /// <param name="compId"> Contains optional full context path to pEntity. Can be empty for simple reference. </param>
    /// <param name="pEntityTransform"> Optional transform of the entity (may be NULL). </param>
    /// <param name="faceSubentId"> Face AcDbSubentId whose persistent silhouette id  is to be obtained. </param>
    /// <param name="pProjector"> Current projection parameters. Silhouettes are view-dependent. </param>
    /// <param name="transientSilhId"> Transient id of a silhouette of a face </param>
    /// <returns> Persistent silhouette id, or 0 if cannot be created. </returns>
    ///
    virtual AcDbAssocPersSubentId* createNewPersFaceSilhouetteId(AcDbEntity*                  pEntity,
                                                                 AcDbDatabase*                pDatabase,
                                                                 AcRxObject*                  pContext,
                                                                 const AcDbCompoundObjectId&  /*compId*/,
                                                                 const AcDbSubentId&          faceSubentId,
                                                                 const AcGeMatrix3d*          pEntityTransform,
                                                                 class AcDbGeometryProjector* pGeometryProjector,
                                                                 int                          transientSilhId)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(pDatabase);
        ADESK_UNREFED_PARAM(pContext);
        ADESK_UNREFED_PARAM(faceSubentId);
        ADESK_UNREFED_PARAM(pEntityTransform);
        ADESK_UNREFED_PARAM(pGeometryProjector);
        ADESK_UNREFED_PARAM(transientSilhId);
        return NULL; 
    }

    /// <summary><para>
    /// Returns all transient silhouette ids for the given persistent silhouette id of a face. 
    /// Notice that a transient silhouette id is just an integer number but a persistent
    /// silhouette id is a complete AcDbAssocPersSubentId object.
    /// </para><para>
    /// The transientSilhId is relative to the given face and the given projection, 
    /// not global for the whole entity.
    /// </para><para>
    /// Id 0 is reserved and means null id, and must not be used as a transient id of a valid silhouette.
    /// </para><para>
    /// The default implementation just clears the output transientSilhIds array and returns Acad::eNotImplemented.
    /// </para></summary>
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write (in case it needs to do some caching). </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param name="pContext"> Additional context info that may be needed. Its meaning is client-specific. </param>
    /// <param name="pEntityTransform"> Optional transform of the entity (may be NULL). </param>
    /// <param name="faceSubentId"> Face AcDbSubentId whose persistent silhouette id  is to be obtained. </param>
    /// <param name="pProjector"> Current projection parameters. Silhouettes are view-dependent. </param>
    /// <param name="pPersSilhId"> Persistent id of a silhouette of a face. </param>
    /// <param name="transientSilhIds"> 
    /// All transient ids of a silhouette of a face that correspond to the given persistentSilhId. 
    /// </param>
    /// <returns> Persistent silhouette id, or 0 if cannot be obtained. </returns>
    ///
    virtual Acad::ErrorStatus getTransientFaceSilhouetteIds(AcDbEntity*                  pEntity,
                                                            AcDbDatabase*                pDatabase,
                                                            AcRxObject*                  pContext,
                                                            const AcDbSubentId&          faceSubentId,
                                                            const AcGeMatrix3d*          pEntityTransform,
                                                            class AcDbGeometryProjector* pGeometryProjector,
                                                            const AcDbAssocPersSubentId* pPersSilhId,
                                                            AcArray<int>&                transientSilhIds)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(pDatabase);
        ADESK_UNREFED_PARAM(pContext);
        ADESK_UNREFED_PARAM(faceSubentId);
        ADESK_UNREFED_PARAM(pEntityTransform);
        ADESK_UNREFED_PARAM(pGeometryProjector);
        ADESK_UNREFED_PARAM(pPersSilhId);

        transientSilhIds.removeAll();
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Call this method to obtain block transformation matrix for a given 
    /// sub-entity within the block reference.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="fullSubentPath">
    /// Full path of the sub-entity whose collective transformation matrix is 
    /// to be determined.
    /// </param>
    /// <param name="trans"> Output block transformation matrix. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getSubentGeometryXform(const AcDbEntity*        pEntity,
                                                     const AcDbObjectIdArray& fullSubentPath,
                                                     AcGeMatrix3d&            trans) const
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(fullSubentPath);
        ADESK_UNREFED_PARAM(trans);

        trans.setToIdentity();
        return Acad::eOk;
    }

    /// <summary> <para>
    /// Mirrors the given AcDbAssocPersSubentId, i.e. it changes it so that it
    /// identitifies the same subentity in the mirrored entity as it identified
    /// before the entity has been mirrored. It is called from the default
    /// implementation of the AcDbAssocPersSubentId::mirror() method.
    /// </para> <para>
    /// The default implementation is a no-op, but some derived AcDbAssocPersSubentIdPE 
    /// protocol extension classes (such as AcDbAssocArcPersSubentIdPE) may need 
    /// to override this method.
    /// </para> </summary>
    /// <param  name="pMirroredEntity"> 
    /// The entity that has been mirrored. It needs to be open for read. 
    /// </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param name="pPersSubentIdToMirror"> 
    /// The AcDbAssocPersSubentId to be changed to reflect the fact that the 
    /// entity has been mirrored.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus mirrorPersSubent(const AcDbEntity*      pMirroredEntity,
                                               AcDbDatabase*          pDatabase,
                                               AcDbAssocPersSubentId* pPersSubentIdToMirror)
    {
        ADESK_UNREFED_PARAM(pMirroredEntity);
        ADESK_UNREFED_PARAM(pDatabase);
        ADESK_UNREFED_PARAM(pPersSubentIdToMirror);
        return Acad::eOk;
    }

    /// <summary>
    /// Returns kScalableRigidSet or kNonScalableRigidSet if the entity is a rigid 
    /// set, i.e. it can be rotated and translated as a whole, but its subentities 
    /// cannot be individually changed.
    /// The default implementation returns kNotRigidSet.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <returns> kScalableRigidSet or kNonScalableRigidSet if the entity is a rigid set. </returns>
    ///
    virtual int getRigidSetState(const AcDbEntity* pEntity) 
    {
        ADESK_UNREFED_PARAM(pEntity);
        return kNotRigidSet; 
    }

    /// <summary>
    /// Get the transformation of the rigid set entity.
    /// The default implementation returns Acad::eNotApplicable.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for read. </param>
    /// <param name="trans"> The returned transformation matrix. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getRigidSetTransform(const AcDbEntity* pEntity,
                                                   AcGeMatrix3d&     trans)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(trans);
        return Acad::eNotApplicable;
    }

    /// <summary>
    /// Set the transformation of the rigid set entity.
    /// The default implementation returns Acad::eNotApplicable.
    /// </summary>
    /// <param name="pEntity"> The entity must be open for write. </param>
    /// <param name="trans"> New transformation matrix of the rigid set entity. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setRigidSetTransform(AcDbEntity*         pEntity, 
                                                   const AcGeMatrix3d& trans)
    {
        ADESK_UNREFED_PARAM(pEntity);
        ADESK_UNREFED_PARAM(trans);
        return Acad::eNotApplicable;
    }

}; // class AcDbAssocPersSubentIdPE


#pragma pack (pop)


