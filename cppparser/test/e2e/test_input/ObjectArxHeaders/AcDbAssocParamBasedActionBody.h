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
#include "AcDbAssocActionBody.h"
#pragma pack (push, 8)


/// <summary>
/// Deprecated in AutoCAD 2013. Please derive directly from the AcDbAssocActionBody class
/// that now contains all the methods of the deprecated AcDbAssocParamBasedActionBody
/// derived class.
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocParamBasedActionBody : public AcDbAssocActionBody
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocParamBasedActionBody);

    explicit AcDbAssocParamBasedActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);
};


#pragma pack (pop)

