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
// CREATED BY: Jiri Kripac                                 August 2007
//
// DESCRIPTION:
//
// AcDbAssocDependencyPE AcRx protocol extension base class. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbCompoundObjectId.h"
#include "AcDbAssocGlobal.h"
#pragma pack (push, 8)


/// <summary> <para>
/// AcRx protocol extension base class that allows objects and entities to 
/// control whether they allow AcDbAssocDependencies to be attached to them.
/// When there is no protocol extension for the object's class, it means that 
/// the object allows both read and write-type dependencies.
/// </para> <para>
/// Other AcDbAssocDependency-related protocol may later be added.
/// </para>
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocDependencyPE : public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocDependencyPE);

    /// <summary>
    /// Predicate enabling objects to control whether they allow AcDbAssocDependencies 
    /// being attached to them or not.
    /// </summary>
    /// <param name="pObject"> The queried object, must be open for read. </param>
    /// <param name="isWriteDependency"> The dependency will also modify the object. </param>
    /// <param name="pActionBodyOrActionClass"> 
    /// AcRcClass of the AcDbAssocActionBody that is requesting the dependency to be
    /// attached to the object. It may also be AcRxClass of the derived AcDbAssocAction 
    /// class for actions that have no action body. The pointer may be NULL, meaning 
    /// it is not explicitly specified what kind of action body or action is requesting
    /// the dependency.
    /// </param>
    /// <param name="pDependency"> 
    /// The dependency that wants to be attached to the object. If provided (not NULL),
    /// this additional information can be used to learn more about the concrete 
    /// database-resident action that is trying to attach a dependency to the object, 
    /// because from the dependency it is possible to go to the action and from the 
    /// action to go to the action body.
    /// </param>
    /// <param name="pContext"> Additional optional context information (currently not used). </param>
    /// <returns> True iff the object allows attaching AcDbAssocDependencies to itself. </returns>
    ///
    virtual bool allowsDependencies(const AcDbObject*          pObject, 
                                    bool                       isWriteDependency, 
                                    const AcRxClass*           pActionBodyOrActionClass, 
                                    const AcDbAssocDependency* pDependency, 
                                    const AcRxObject*          pContext) const = NULL;

    /// <summary><para>
    /// Allows objects to whom dependencies are being attached by AcDbAssocDependency::attachToObject() 
    /// method to instruct the attachToObject() method to attach the dependency to some other objects
    /// instead of to themselves. The default implementation returns the given AcDbCompoundObjectId, 
    /// i.e. no attachment redirection happens.
    /// </para><para>
    /// This allows objects to seamlessly redirect dependencies on themselves to be actually 
    /// attached to some other objects without the client code even knowning about it. The 
    /// client code requests a dependency to be attached to one object, but the dependency 
    /// is actually attached to another object.
    /// </para></summary>
    /// <param name="pObject"> The object the dependency is being attached to, must be opened for write. </param>
    /// <param name="compoundObjectId"> The nesting of the object the dependency is being attached to. </param>
    /// <param name="pDependency"> The dependency whose attachToObject() is being executed. </param>
    /// <param name="redirectedCompoundObjectId"> The object the dependency is redirected to be attached to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus redirectDependencyAttachment(AcDbObject*                 pObject,
                                                           const AcDbCompoundObjectId& compoundObjectId, 
                                                           AcDbAssocDependency*        pDependency,
                                                           AcDbCompoundObjectId&       redirectedCompoundObjectId)
    {
        ADESK_UNREFED_PARAM(pDependency);
        ADESK_UNREFED_PARAM(pObject);
        redirectedCompoundObjectId = compoundObjectId;
        return Acad::eOk;
    }

}; // class AcDbAssocDependencyPE

#pragma pack (pop)


