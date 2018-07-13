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
//  DESCRIPTION:  Header for Document and Document Manager Classes.
//
#ifndef ACPLPLOTREACTORMGR_H
#define ACPLPLOTREACTORMGR_H

#include "AcPl.h"

class ADESK_NO_VTABLE AcPlPlotReactorMgr
{
public:

    // Adds the given reactor to the reactor chain
    ACPL_PORT void addReactor(AcPlPlotReactor* pReactor);

    // Removes the given reactor from the reactor chain
    ACPL_PORT void removeReactor(AcPlPlotReactor* pReactor);
};

ACPL_PORT AcPlPlotReactorMgr* __stdcall acplPlotReactorMgrPtr();
#define acplPlotReactorMgr acplPlotReactorMgrPtr()

#endif // ACPLPLOTREACTORMGR_H
