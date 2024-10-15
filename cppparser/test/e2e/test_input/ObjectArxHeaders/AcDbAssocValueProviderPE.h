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
// CREATED BY: Jiri Kripac                                 April 2007
//
// DESCRIPTION:
//
// AcDbAssocValueProviderPE AcRx protocol extension pure virtual base class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "acdb.h"
#include "dbeval.h"
#include "AcDbAssocGlobal.h"
#pragma pack (push, 8)


/// <summary> <para>
/// AcRx protocol extension pure virtual base class that defines protocol to
/// get and set arbitrary simple scalar values of AcDbObjects. The values are 
/// identified by string names (needed if there is more than one of them for 
/// the same object) and their meaning is up to the implementor of the concrete 
/// protocol extension derived classes.
/// </para> <para>
/// The derived concrete classes implement this protocol for the individual
/// AcDbObject classes that want to offer some named values. The immediate
/// clients of this protocol are AcDbAssocVariable class that exposes this 
/// interface to provide the value of the variable and AcDbAssocValueDependency 
/// class that uses this interface to obtain the value from the dependent-on
/// object.
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocValueProviderPE : public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocValueProviderPE);

    /// <summary>
    /// Checks whether it is possible to get the value identified by valueName.
    /// The default implementation always returns true for any valueName.
    /// </summary>
    /// <param name="pObject"> The object must be open for read. </param>
    /// <param name="valueName"> The name of the queried value. </param>
    /// <returns> 
    /// True iff a value with the given name can be obtained. The default 
    /// implementation always returns true.
    /// </returns>
    ///
    virtual bool canGetValue(const AcDbObject* pObject, const AcString& valueName) { 
        ADESK_UNREFED_PARAM(pObject);
        ADESK_UNREFED_PARAM(valueName);
        return true;
    }

    /// <summary>
    /// Checks whether it is possible to set the value identified by valueName.
    /// The default implementation always returns false for any valueName.
    /// </summary>
    /// <param name="pObject"> The object must be open for read. </param>
    /// <param name="valueName"> The name of the queried value. </param>
    /// <returns> 
    /// True iff a value with the given name can be changed. The default 
    /// implementation always returns false.
    /// </returns>
    ///
    virtual bool canSetValue(const AcDbObject* pObject, const AcString& valueName) { 
        ADESK_UNREFED_PARAM(pObject);
        ADESK_UNREFED_PARAM(valueName);
        return false;
    }

    /// <summary>
    /// Gets the value identified by valueName. This method must always be 
    /// overridden by concrete derived classes.
    /// </summary>
    /// <param name="pObject"> The object must be open for read. </param>
    /// <param name="valueName"> The name of the queried value. </param>
    /// <param name="value"> The returned value. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getValue(const AcDbObject* pObject, 
                                       const AcString&   valueName, 
                                       AcDbEvalVariant&  value) = 0;

    /// <summary>
    /// Sets the value identified by valueName. The default implementation always
    /// returns Acad::eNotHandled for any valueName.
    /// </summary>
    /// <param name="pObject"> The object must be open for write. </param>
    /// <param name="valueName"> The name of the value to be set. </param>
    /// <param name="newValue"> The new value. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setValue(AcDbObject*            pObject, 
                                       const AcString&        valueName, 
                                       const AcDbEvalVariant& newValue) 
    {
        ADESK_UNREFED_PARAM(pObject);
        ADESK_UNREFED_PARAM(valueName);
        ADESK_UNREFED_PARAM(newValue);
        return Acad::eNotHandled;
    }

    /// <summary>
    /// Simple utility methods that open the object, query for its AcDbAssocValueProviderPE
    /// and get/set the value with the given name.
    /// </summary>
    ///
    static Acad::ErrorStatus getObjectValue(const AcDbObjectId&, const AcString& valueName, AcDbEvalVariant& value);
    static Acad::ErrorStatus setObjectValue(const AcDbObjectId&, const AcString& valueName, const AcDbEvalVariant& value);

}; // class AcDbAssocValueProviderPE

#pragma pack (pop)


