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
// CREATED BY: Jiri Kripac                         June 2008
//
// DESCRIPTION:
//
// AcDbAssocDimDependencyBody derived class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocDimDependencyBodyBase.h"


/// <summary>
/// AcDbAssocDimDependencyBody manages an AcDbDimension entity that serves 
/// as the graphical representation of a dimensional constaint. It inherits
/// common functionality from the AcDbAssocDimDependencyBodyBase class and 
/// overrides the base-class pure virtual methods in which it implements the
/// AcDbDimension-specific functionality.
/// </summary>
///
class ACDB_PORT AcDbAssocDimDependencyBody : public AcDbAssocDimDependencyBodyBase
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocDimDependencyBody);

    /// <summary> Default constructor.</summary>
    AcDbAssocDimDependencyBody();

    /// <summary> Destructor. </summary>
    virtual ~AcDbAssocDimDependencyBody();

    // Implementation of pure virtual methods in the AcDbAssocDimDependencyBodyBase 
    // class. They deal with the controlled entity that is assumed to be an 
    /// AcDbDimension

    /// <summary> Returns the text of the controlled AcDimension. </summary>
    /// <returns> AcDbDimension text. </returns>
    ///
    virtual AcString getEntityTextOverride() const ADESK_OVERRIDE;

    /// <summary> Sets the text property in the controlled AcDbDimension. </summary>
    /// <param  name="newText"> New text to set in the AcDbDimension.</param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    virtual Acad::ErrorStatus setEntityTextOverride(const AcString& newText) ADESK_OVERRIDE;

    /// <summary> Gets the measurement from the controlled AcDbDimension. </summary>
    /// <returns> AcDbDimension measurement. </returns>
    ///
    virtual double getEntityMeasurementOverride() const ADESK_OVERRIDE;

    /// <summary> Returns true iff the attachment of the controlled AcDbDimension
    /// changed, such as the AcDbDimension has been repositioned. </summary>
    /// <returns> Returns true if attachment changed. </returns>
    ///
    virtual bool isEntityAttachmentChangedOverride() const ADESK_OVERRIDE;

    // Overridden method from the AcDbAssocDependencyBody base class

    /// <summary> Updates position, size and orientation of the controlled AcDbDimension.
    /// </summary>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    virtual Acad::ErrorStatus updateDependentOnObjectOverride() ADESK_OVERRIDE;

    /// <summary>
    /// "Pseudo constructor". Creates a new AcDbAssocDependency object owning 
    /// a new AcDbAssocDimDependencyBody object and makes the dependent-on object
    /// of the new dependency to be the provided AcDbDimension. Posts both objects 
    /// to the database of the AcDbDimension.
    /// </summary>
    /// <param name="dimId"> AcDbObjectId of the AcDbDimension. </param>
    /// <param name="dimDepId"> AcDbObjectId of the created AcDbAssocDependency. </param>
    /// <param name="dimDepBodyId"> AcDbObjectId of the created AcDbAssocDimDependencyBody. </param>
    /// <returns> Acad::eOk if successful. </returns>
    ///
    static Acad::ErrorStatus
                createAndPostToDatabase(const AcDbObjectId& dimId,
                                        AcDbObjectId&       dimDepId,
                                        AcDbObjectId&       dimDepBodyId);
};

