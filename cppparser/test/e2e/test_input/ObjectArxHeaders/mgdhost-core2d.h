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

#include "AdAChar.h"
#include "acadstrc.h"
#include "AcDbCore2dDefs.h"

#pragma once
class AcString;

class AcDbManagedHost
{
public:
    virtual int version() { return 1;}
    virtual Acad::ErrorStatus load(const ACHAR * fname)=0;
    virtual bool loadIndirectString(const AcString& resAssemblyPath, const AcString& cmdString, AcString& localCmd) = 0;
    virtual bool isLoaded() = 0;
};

ACDBCORE2D_PORT AcDbManagedHost* ADESK_STDCALL acdbGetManagedHost();
ACDBCORE2D_PORT Acad::ErrorStatus ADESK_STDCALL acdbSetManagedHost(AcDbManagedHost* pHost);
