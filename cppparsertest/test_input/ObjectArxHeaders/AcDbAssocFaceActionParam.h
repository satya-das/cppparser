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
#include "AcDbAssocActionParam.h"
#include "AcDbGeomRef.h"
#pragma pack (push, 8)


/// <summary>
/// Action parameter that keeps reference to a face. It uses AcDbAssocGeomDependency 
/// to define a persistent reference to a face subentity of an AcDbEntity. Alternatively,
/// it may directly keep the face geometry in the action parameter in the form 
/// of an ASM body, instead of referencing some other AcDbEntity.
/// </summary>
///
class ACDB_PORT AcDbAssocFaceActionParam : public AcDbAssocActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocFaceActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocFaceActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para>
    /// The input AcDbFaceRef is a non-persistent reference to a face geometry, 
    /// the AcDbAssocEdgeActionParam will make a persistent reference to that face. 
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced face subentity.  If it is constant geometry 
    /// in the form of a face of an ASM body, no dependency is created.
    /// </para></summary>
    /// <param name="faceRef"> 
    /// Reference to a "face" subentity of an entity, or constant geometry in the 
    /// form of a face of an ASM body. See AcDbFaceRef for details.
    /// </param>
    /// <param name="isReadDependency">  Read-dependency on the entity should be created.  </param>
    /// <param name="isWriteDependency"> Write-dependency on the entity should be created. </param>
    /// <param name="dependencyOrder"> 
    /// Specifies position of the created dependency in the ordered list of 
    /// dependencies on the entity. See AcDbAssocDependency::setOrder(int) method.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setFaceRef(const AcDbFaceRef& faceRef, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);

    /// <summary> <para>
    /// Returns references to the transient subentities of an AcDbEntity, that 
    /// correspond to the persistent subentity that this face action parameter 
    /// references. It can also be a constant geometry in the form of a face of
    /// an ASM body. See AcDbFaceRef for details.
    /// </para><para>
    /// When a single face (such as face of a solid or surface) is referenced by 
    /// this AcDbAssocFaceActionParam and some parameters of the solid/surface 
    /// are changed and the solid/surface is re-evaluated from its actions, this 
    /// single face may then correspond to any number of faces, because the original 
    /// face might have gotten split, merged, or even may have disappeared. That 
    /// is why the output is an array of FaceRefs, but in typical case the array 
    /// will contain just a single element.
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced face subentity.
    /// </para></summary>
    /// <param name="faceRefs"> 
    /// References to the transient subentities of an AcDbEntity, that correspond 
    /// to the persistent subentity that this face action parameter references. 
    /// See AcDbFaceRef for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getFaceRef(AcArray<AcDbFaceRef>& faceRefs) const;

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
    /// <param name="pNewFaceSurface"> New surface of the face subentity (copied, not reused). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setFaceSubentityGeometry(const AcGeSurface* pNewFaceSurface);

    /// <summary>
    /// If this action parameter depends on an AcDbEntity via an AcDbAssocGeomDependency, 
    /// it returns AcDbCompoundObjectId of the entity this dependency depends on.
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

