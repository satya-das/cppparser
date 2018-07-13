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
// AcDbAssocValueDependency concrete class. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocDependency.h"
#pragma pack (push, 8)


/// <summary>
/// A concrete dependency class that represents a dependency on a scalar value,
/// such as on a numerical variable. The dependent-on object needs to expose
/// AcDbAssocValueProviderPE protocol extension class that is used to obtain the
/// value from the object. It is possible to specify the name of the value in 
/// case the object provides more than one value.
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocValueDependency : public AcDbAssocDependency
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocValueDependency);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocValueDependency(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Returns the name of the referenced value or an empty string if the value 
    /// name is not needed because the referenced object exposes only a single 
    /// value (it is a common case, such as for AcDbAssocVariable objects).
    /// </summary>
    /// <returns> Name of the referenced value or an empty string. </returns>
    ///
    const AcString& valueName() const;

    /// <summary> 
    /// Sets the name of the referenced value or an empty string if the value
    /// name is not needed because the referenced object exposes only a single 
    /// value (it is a common case, such as for AcDbAssocVariable objects).
    /// </summary>
    /// <param name="newValueName"> Name of a different referenced value (empty string allowed). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueName(const AcString& newValueName);

    /// <summary>
    /// Returns true iff the dependency currently holds the cached value.
    /// </summary>
    /// <returns>
    /// Returns true iff the dependency holds the cached value.
    /// </returns>
    ///
    /// bool hasCachedValue() const;

    /// <summary> 
    /// Queries the dependent-on object and returns its value. If the object cannot
    /// be opened, but the dependency holds the cached value of the object (its
    /// hasCachedValue() predicate returns true), it returns this cached value
    /// and Acad::eOk Acad::ErrorStatus. 
    /// </summary>
    /// <param name="objectValue"> The value of the dependent-on object. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getDependentOnObjectValue(AcDbEvalVariant& objectValue) const;

    /// <summary> 
    /// Sets the value in the dependent-on object and updates the cached value.
    /// </summary>
    /// <param name="newObjectValue"> The new value to be set on the dependent-on object. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setDependentOnObjectValue(const AcDbEvalVariant& newObjectValue);

    /// <summary>
    /// Checks whether the value cached in this dependency is the same as the 
    /// value provided by the referenced object via its AcDbAssocValueProviderPE 
    /// protocol extension. Returns true if they are different, false otherwise.
    /// </summary> 
    /// <returns> 
    /// True iff cached value is different from the value provided by the referened object.
    /// </returns>
    ///
    /// bool isRelevantChange() const;

    /// <summary> 
    /// Returns true if both this and the other dependency depend on the same 
    /// object and on the same named value in the object.
    /// </summary> 
    /// <param name="otherDepepndencyId"> The other AcDbAssocValueDependency, open at least for read. </param>
    /// <returns> 
    /// True iff oth dependencies depend on exactly the same named value of the same object. 
    /// </returns>
    ///
    /// bool isDependentOnTheSameThingAs(const AcDbAssocDependency* pOtherDependency) const;

    /// <summary>
    /// Sets the value cached in this dependency from the current named value of the
    /// dependent-on object. Resets the dependency status to kIsUpToDateAssocStatus.
    /// </summary>
    ///
    /// void evaluate();

}; // class AcDbAssocValueDependency

#pragma pack (pop)


