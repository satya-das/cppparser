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

#pragma once

#include "acbasedefs.h"
#include "adesk.h"
#include "acadstrc.h"
#include "rxmember.h"

class AcRxValue;
class AcRxMethodImp;
class AcRxMethodIteratorImp;

//*************************************************************************
// AcRxMemberQueryEngine
//*************************************************************************
/// <summary>
/// This class defines a method.
/// </summary>
///
class AcRxMethod : public AcRxMember
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxMethod, ACBASE_PORT);

    /// <summary>
    /// This method is called to execute a method.
    ///
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object that the method is applicable.
    /// </param>
    ///
    /// <param name="param">
    /// Reference to AcRxValue object that the method can set.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus invoke(AcRxObject* pO, AcRxValue& param) const;

    /// <summary>
    /// This method is called to check if the method can be executed.
    ///
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object that the method is applicable.
    /// </param>
    ///
    /// <param name="param">
    /// Input reference to AcRxValue object that the method can use.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus isExecutable(const AcRxObject* pO, const AcRxValue& param) const;

protected:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT ~AcRxMethod();
    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// Input name of the method.
    /// </param>
    ///
    /// <param name="type">
    /// Input reference to type of the member.
    /// </param>
    ///
    ACBASE_PORT AcRxMethod(const ACHAR* name, const AcRxValueType& type);

    /// <summary>
    /// Derived classes can override this method to execute the method.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object that the method is applicable.
    /// </param>
    ///
    /// <param name="param">
    /// Reference to AcRxValue object that the method can set.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    virtual Acad::ErrorStatus subInvoke(AcRxObject* pO, AcRxValue& param) const;

    /// <summary>
    /// Derived classes can override this method to return a status, if the method can executed 
    /// in its current state.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object that the method is applicable.
    /// </param>
    ///
    /// <param name="param">
    /// Input reference to AcRxValue object that the method can use.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    virtual Acad::ErrorStatus subIsExecutable(const AcRxObject* pO, const AcRxValue& param) const;

protected:
    friend class AcRxMethodImp;
    ACBASE_PORT AcRxMethod(AcRxMethodImp*);
};

