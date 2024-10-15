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
// CREATED BY: Pei Zhan                                 July 2009
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocEdgeActionParam.h"
#include "AcDbGeomRef.h"
#pragma pack (push, 8)


/// <summary>
/// Action parameter that keeps reference to a vertex subentity of an AcDbEntity,
/// or directly keeps AcGePoint3d geometry.
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocVertexActionParam : public AcDbAssocActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocVertexActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocVertexActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para>
    /// The input AcDbVertexRef is a non-persistent reference to a vertex geometry,
    /// the AcDbAssocVertexActionParam will make a persistent reference to that vertex. 
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced vertex subentity. In case the whole AcDbPoint 
    /// entity is referenced, not a subentity of an AcDbEntity, an AcDbAssocDependency 
    /// is used. If it is constant geometry in the form of an AcGePoint3d, no 
    /// dependency is created.
    /// </para></summary>
    /// <param name="vertexRef"> 
    /// Reference to an "vertex" subentity of an entity, to a AcDbPoint entity, 
    /// or to an AcGePoint3d constant geometry. See AcDbVertexRef for details.
    /// </param>
    /// <param name="isReadDependency">  Read-dependency on the entity should be created.  </param>
    /// <param name="isWriteDependency"> Write-dependency on the entity should be created. </param>
    /// <param name="dependencyOrder"> 
    /// Specifies position of the created dependency in the ordered list of 
    /// dependencies on the entity. See AcDbAssocDependency::setOrder(int) method.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setVertexRef(const AcDbVertexRef& vertexRef, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);

    /// <summary> <para>
    /// Returns references to the transient subentities of an AcDbEntity, that 
    /// correspond to the persistent subentity that this vertex action parameter 
    /// references. It can also be reference to the whole AcDbPoint entity or to
    /// constant AcGePoint3d geometry. See AcDbVertexRef for details.
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced vertex subentity. In case the whole AcDbPoint 
    /// entity is referenced, not a subentity of an AcDbEntity, an AcDbAssocDependency 
    /// is used. If it is constant geometry in the form of an AcGePoint3d, no 
    /// dependency is created.
    /// </para></summary>
    /// <param name="vertexRefs"> 
    /// References to the transient subentities of an AcDbEntity, that correspond 
    /// to the persistent subentity that this vertex action parameter references. 
    /// It can also be reference to the whole AcDbPoint entity or to constant 
    /// AcGePoint3d geometry. See AcDbVertexRef for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getVertexRef(AcArray<AcDbVertexRef>& vertexRefs) const;

    /// <summary>
    /// A utility method that calls getVertexRef(AcArray AcDbVertexRef) and
    /// returns the first AcDbVertexRef in the array, or an non-eOk ErrorStatus 
    /// if no vertex subentities were found.
    /// </summary>
    /// <param name="vertexRef"> 
    /// Reference to a single transient subentity of an AcDbEntity, that corresponds 
    /// to the persistent subentity that this vertex action parameter references. 
    /// It can also be reference to the whole AcDbPoint entity or to constant 
    /// AcGePoint3d geometry. See AcDbVertexRef for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getVertexRef(AcDbVertexRef& vertexRef) const;

    /// <summary><para>
    /// Sets new geometry of the referenced subentity of the AcDbEntity the action parameter
    /// depends on via an AcDbAssocDependency or AcDbAssocGeomDependency.
    /// If the action parameter currently references more than one subentity of the AcDbEntity 
    /// (e.g. because the original single subentity was split into several subentities), 
    /// it returns eNotApplicable. This is because the most common use case is to set the 
    /// subentity geometry if only a single subentity is referenced by the action parameter.
    /// </para><para>
    /// If client code needs to set geometry of the individual subentities the action parameter
    /// references, it needs to do it manually through the dependencies of the action parameter.
    /// </para></summary>
    /// <param name="newPosition"> New coordinates of the vertex subentity. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setVertexSubentityGeometry(const AcGePoint3d& newPosition);

    /// <summary>
    /// If this action parameter depends on an AcDbEntity via an AcDbAssocDependency
    /// or AcDbAssocGeomDependency, it returns AcDbCompoundObjectId of the entity 
    /// this dependency depends on.
    /// </summary>
    /// <param name="compoundId"> 
    /// The AcDbCompoundObjectId of the entity this action parameter depends on,
    /// or an empty compound object id if the action parameter does not depend
    /// on any entity.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getDependentOnCompoundObject(AcDbCompoundObjectId& compoundId) const;
};

#pragma pack (pop)
