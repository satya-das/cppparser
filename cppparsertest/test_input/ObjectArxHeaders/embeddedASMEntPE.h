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

#include "acdbport.h"
#include "rxobject.h"

class AcDbEmbeddedASMEntPropsPE : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbEmbeddedASMEntPropsPE);
    ACDB_PORT virtual void setIsEmbeddedEnt(AcDbObject* pObj, bool bIsEmbedded = true);
};






