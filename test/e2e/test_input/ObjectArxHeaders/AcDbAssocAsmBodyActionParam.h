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
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocEdgeActionParam.h"
#include "AcDbAssocCompoundActionParam.h"
#pragma pack (push, 8)


/// <summary>
/// Action parameter that keeps reference to an AcDbEntity that uses an ASM (Autodesk
/// Shape Manager) body to represent the entity geometry. Alternatively, it may 
/// keep the ASM body directly inside the action parameter, instead of referencing 
/// some other AcDbEntity. Currently AcDbSurface and derived classes, AcDb3dSolid, 
/// AcDbRegion and AcDbBody entities use ASM to represent the geometry.
/// </summary>
///
class ACDB_PORT AcDbAssocAsmBodyActionParam : public AcDbAssocActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocAsmBodyActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocAsmBodyActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// For Autodesk Internal Use only.
    /// If the given pAsmEntity is database-resident, it creates an AcDbAssocDependency 
    /// and attaches it to pAsmEntity. Otherwise it copies the ASM body kept in 
    /// pAsmEntity and stores the ASM body directly inside this action parameter.
    /// </summary>
    /// <param name="pAsmEntity">  Entity that keeps an ASM body. </param>
    /// <param name="isReadDependency">  Read-dependency on the entity should be created.  </param>
    /// <param name="isWriteDependency"> Write-dependency on the entity should be created. </param>
    /// <param name="dependencyOrder"> 
    /// Specifies position of the created dependency in the ordered list of 
    /// dependencies on the entity. See AcDbAssocDependency::setOrder(int) method.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setBody(const AcDbEntity* pAsmEntity, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);

    /// <summary> 
    /// For Autodesk Internal Use only.
    /// Creates an AcDbAssocDependency and attaches it to asmEntityId.
    /// </summary>
    /// <param name="asmEntityId"> Referenced entity that keeps an ASM body. </param>
    /// <param name="isReadDependency">  Read-dependency on the entity should be created.  </param>
    /// <param name="isWriteDependency"> Write-dependency on the entity should be created. </param>
    /// <param name="dependencyOrder"> 
    /// Specifies position of the created dependency in the ordered list of 
    /// dependencies on the entity. See AcDbAssocDependency::setOrder(int) method.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setBody(AcDbObjectId asmEntityId, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);

    /// <summary> 
    /// For Autodesk Internal Use only.
    /// Sets the given ASM body to the AcDbAssocAsmBodyActionParam, optionally 
    /// making a copy. No dependency on any entity is created, the ASM body is 
    /// directly owned by this action parameter.
    /// </summary>
    /// <param name="pAsmBody"> The ASM body to set to the action parameter. </param>
    /// <param name="makeCopy"> 
    /// If true, makes copy of the ASM body and keeps it, otherwise it keeps the
    /// provided ASM body directly.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setBody(void* pAsmBody, bool makeCopy); 

    /// <summary> 
    /// For Autodesk Internal Use only.
    /// Returns pointer to the ASM body that is either owned by an AcDbEntity 
    /// referenced via an AcDbAssocDependency, or directly owned by this action 
    /// parameter. 
    /// </summary>
    /// <param name="makeCopy"> 
    /// If true, returns a copy of the ASM body, otherwise returns pointer to the
    /// ASM body owned by an AcDbEntity or in this action parameter. In the latter
    /// case the ASM body must not be modified bt the client code.
    /// </param>
    /// <returns> Void pointer that actually points to an ASM body object. </returns>
    ///
    virtual void* body(bool makeCopy) const;

    /// <summary>
    /// If this action parameter depends on an AcDbEntity via an AcDbAssocDependency,
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
