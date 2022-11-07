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
//  DESCRIPTION:  Header for Plot Error Handler Lock.
//

#ifndef ACPLPLOTERRORHANDLERLOCK_H
#define ACPLPLOTERRORHANDLERLOCK_H

#include "AdAChar.h"
#include "AcPlObject.h"

class AcPlPlotErrorHandler;

class AcPlPlotErrorHandlerLock : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlPlotErrorHandlerLock);
public:
    enum LockStatus {
        kLocked,
        kUnLocked
    };

    ACPL_PORT AcPlPlotErrorHandlerLock();
    ACPL_PORT AcPlPlotErrorHandlerLock(AcPlPlotErrorHandler* pAppErrHandler, 
                             const ACHAR * pAppName);

    ACPL_PORT LockStatus status() const;
    ACPL_PORT bool lock(AcPlPlotErrorHandler* pAppErrHandler, const ACHAR * pAppName);
    ACPL_PORT bool unLock(AcPlPlotErrorHandler* pAppErrHandler);
    ACPL_PORT void getErrorHandler(AcPlPlotErrorHandler*& pAppErrHandler) const;
    ACPL_PORT const ACHAR * appName() const;
};

#endif // ACPLPLOTERRORHANDLERLOCK_H
