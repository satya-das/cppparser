//
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
// dbPropertyFilterCustomizationPEPE.H
//
// DESCRIPTION: Protocol extension base class
//                AcDbPropertyFilterCustomizationPE
//
#pragma once

#include "acdb.h"
#include "dynprops-AcFilterablePropertyContext.h"

#pragma pack (push, 8)


/// <summary>
/// This protocol extension interface can be implemented and associated with
/// an AcRxClass to take some level of control over the way an entity type
/// participates in property filter customization in the CUI dialog.  If this
/// protocol extension is not associated with the AcRxClass of a particular
/// entity type, the entity type will be handled in a "default" manner.  The
/// "default" behavior is as follows.
/// The CUI property filter customization framework will make the entity type
/// available for property filter customization when it is registered in the
/// class dictionary by instantiating an instance of the entity via the
/// AcRxClass::create() method.  It will check if this entity is able to
/// function properly when it's not database resident by seeing if the entity
/// implements the IAcadBaseObject2 interface and checking that interface's
/// "ForceDbResident()" method.  If the interface is implemented and
/// "ForceDbResident()" indicates that the entity does not need to be database
/// resident, the entity will be used as is for determining its display name
/// and properties.  If the entity does not support non-database residency,
/// it will be added to model space of a temporary database before being used
/// to determine its display name and properties.
/// </summary>
///
class AcDbPropertyFilterCustomizationPE : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcDbPropertyFilterCustomizationPE);

    /// <summary>
    /// Gives an ARxClass a chance to opt out of the CUI
    /// property filter customization framework.
    /// </summary>
    ///
    /// <param name="context">
    /// An enum value that indicates what context the property filter will
    /// be used for.  The current contexts that exist are for the Quick
    /// Properties feature and the Rollover Tooltips feature.
    /// </param>
    ///
    /// <param name="pCls">
    /// A pointer to an AcRxClass that indicates the entity type which
    /// would be eligible for property filter customization in the CUI dialog.
    /// </param>
    ///
    /// <returns>
    /// A boolean value indicating whether this type should be blocked
    /// from property filter customization for the passed in context.
    /// Returning "true" would block participation.
    /// </returns>
    ///
    virtual bool vetoCustomization(AcFilterablePropertyContext context,
                                   AcRxClass* pCls) const = 0;

    /// <summary>
    /// Gives an ARxClass a chance to do its own creation of an entity
    /// instance that will be used for interrogation by the CUI
    /// property filter customization framework.  This may be necessary
    /// if the entity type requires special initialization steps in order to
    /// reliably provide its set of properties or display name.
    /// </summary>
    ///
    /// <param name="pDb">
    /// A pointer to a temporary database that can be used if the object type
    /// requires database-residency for property access.
    /// </param>
    ///
    /// <param name="pCls">
    /// A pointer to an AcRxClass that indicates the type for which an
    /// instance is needed.
    /// </param>
    ///
    /// <param name="ppEnt">
    /// A pointer to a pointer to an AcDbEntity.  This is an output parameter
    /// which should be used to pass an entity instance back if the
    /// implementation creates a non-database resident instance for
    /// interrogation by the CUI property filter customization framework.
    /// The framework will free this instance's memory when it's no longer
    /// needed.
    /// </param>
    ///
    /// <param name="objId">
    /// A reference to an AcDbObjectId.  This is an output parameter
    /// which should be used to pass an AcDbObjectId back if the
    /// implementation creates a database resident instance for
    /// interrogation by the CUI property filter customization framework.
    /// If a database resident instance is created, it should reside in
    /// the temporary database created by the framework to which
    /// the "pDb" input parameter refers.
    /// </param>
    ///
    /// <param name="sGUID">
    /// A const reference to an AcString. This is an input parameter
    /// which indicates the type of sub-entity that needs to be created.
    /// An empty sGUID indicates that there is no subtype.
    /// </param>
    ///
    /// <returns>
    /// Return true if implementation has successfully created an instance
    /// and has populated either the output "ppEnt" parameter or
    /// the "objId" parameter.  If false is returned, the framework
    /// will create an object instance via the "default" methodology described
    /// in the summary for this protocol extension interface.
    /// </returns>
    ///
    virtual bool createObject(AcDbDatabase* pDb,
                              AcRxClass* pCls,
                              AcDbEntity** ppEnt,
                              AcDbObjectId& objId,
                              const AcString& sGUID) const = 0;
};

#pragma pack (pop)

