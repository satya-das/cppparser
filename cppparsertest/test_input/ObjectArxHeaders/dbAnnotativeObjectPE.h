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
// dbAnnotativeObjectPE.H
//
// DESCRIPTION: Protocol extension base classes
//                AcDbAnnotativeObjectPE
//                AcDbPaperOrientationPE
//
#pragma once

#include "acdb.h"
#include "dbmain.h"

class AcDbViewport;

#pragma pack (push, 8)

/// <summary>
/// This protocol extension interface must be implemented for any object
/// which supports annotation scaling. 
/// </summary>
///
class AcDbAnnotativeObjectPE : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcDbAnnotativeObjectPE);

    /// <summary>
    /// Determines whether the object is annotative.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the AcDbObject supporting annotation scaling.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the object is annotative, otherwise it returns
    /// false. 
    /// </returns>
    ///
    virtual bool annotative(AcDbObject* pObject) const = 0;

    /// <summary>
    /// Sets the annotative property of an object.
    /// </summary>
    ///
    /// <param name="pObject">
    /// The AcDbObject to set the property on.
    /// </param>
    ///
    /// <param name="bAnnotative">
    /// The new value for the annotative property.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    virtual Acad::ErrorStatus setAnnotative( AcDbObject* pObject,
                                             const bool  bAnnotative ) = 0;

    /// <summary>
    /// Sets the annotative property of an object from its (optionally)
    /// associated style. 
    /// </summary>
    /// 
    /// <param name="pObject">
    /// A pointer to the AcDbObject to the set the annotative property on.
    /// </param>
    ///
    /// <param name="bUpdated">
    /// Set to "true" on successful return if the annotative property
    /// of the object changed.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Some annotative objects can be associated with styles which also have
    /// annotative properties. For example, a text object references an
    /// associated style. This method can be used to update the annotative
    /// property of an object with an associated style so that the object has
    /// the same value for the property as its associated style. 
    /// </remarks>
    ///
    virtual Acad::ErrorStatus setFromStyle(AcDbObject* pObject, 
                                           bool&       bUpdated) = 0;

    /// <summary>
    /// Whether to ignore the ANNOALLVISIBLE system variable and
    /// force this object to display regardless of the current 
    /// annotation scale.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the AcDbObject from which to read the property.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the object is forced to be visible in all
    /// annotation scales. 
    /// </returns>
    ///
    virtual bool forceAnnoAllVisible(AcDbObject* pObj) const { 
        ADESK_UNREFED_PARAM(pObj);
        return false;
    } 

    /// <summary>
    /// Whether to ignore the ANNOALLVISIBLE system variable and
    /// force this object to display regardless of the current 
    /// annotation scale.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the AcDbObject on which to the set the property.
    /// </param>
    ///
    /// <param name="bForce>
    /// True to ignore the ANNOALLVISIBLE system variable and be visible
    /// in all annotation scales.
    /// </param>
    /// 
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Only objects of type AcDbEntity are required to implement this
    /// function when they implement the protocol extension.
    /// </remarks>
    virtual Acad::ErrorStatus setForceAnnoAllVisible(AcDbObject* pObj,
            bool bForce) const 
    {
        ADESK_UNREFED_PARAM(pObj);
        ADESK_UNREFED_PARAM(bForce);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Resets any scale dependent object properties to the default 
    /// values. 
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the object to reset.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Objects implement this function to support AutoCAD's ANNORESET command.
    /// Objects may implement properties which are scale dependent, for example
    /// the position or rotation of the object. Objects that wish to support
    /// the ANNORESET command should provide an implementation of this method
    /// which resets all scale-dependent properties to match the properties of
    /// the current scale (or of a default scale, determined by the object, if
    /// the object doesn't support the current scale). 
    /// </remarks>
    virtual Acad::ErrorStatus resetScaleDependentProperties (
                                                AcDbObject* pObject) 
    {
        ADESK_UNREFED_PARAM(pObject);
        return Acad::eNotImplemented;
    }
};


/// <summary>
/// This protocol extension interface can optionally be implemented by objects
/// which support "paper orientation" behavior. 
/// </summary>
///
class AcDbPaperOrientationPE : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcDbPaperOrientationPE);

    /// <summary>
    /// Retrieves the current value of the paper orientation property on
    /// an annotative object.
    /// </summary>
    /// 
    /// <param name="pObject">
    /// A pointer to the annotative object supporting paper orientation.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the object is currently oriented with the paper.
    /// </returns>
    ///
    virtual bool paperOrientation(AcDbObject* pObject) const = 0;

    /// <summary>
    /// Sets the current value of the paper orientation property
    /// on an annotative object.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the annotative object supporting paper orientation.
    /// </param>
    ///
    /// <param name="bPaperOrientation">
    /// The new value for the paper orientation property.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    virtual Acad::ErrorStatus setPaperOrientation( 
                                         AcDbObject* pObject,
                                         const bool  bPaperOrientation ) = 0;

    /// <summary>
    /// Transforms the object to align it to the paper-space viewport
    /// if the object supports the paper orientation property.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the annotative object supporting paper orientation.
    /// </param>
    ///
    /// <param name="pVport">
    /// A pointer to the viewport in which the object is to be displayed.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful, or eNotImplemented if the object
    /// does not have the paper orientation property.
    /// </returns>
    ///
    virtual Acad::ErrorStatus applyPaperOrientationTransform ( 
                                         AcDbObject* pObject,
                                         const AcDbViewport *pVport ) const
    {
        ADESK_UNREFED_PARAM(pObject);
        ADESK_UNREFED_PARAM(pVport);
        return Acad::eNotImplemented; 
    }
};

#pragma pack (pop)

