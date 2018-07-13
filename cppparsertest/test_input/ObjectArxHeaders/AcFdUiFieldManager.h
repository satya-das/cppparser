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
// Name:            AcFdUiFieldManager.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcFdUi.h"
#include "AcFdUiFieldDialogHook.h"


class AcTcUiSystemInternals;
class CAcFdUiFieldCatalog;
class CAcFdUiFieldDialogHook;


class ACFDUI_PORT CAcFdUiFieldManager : public CObject
{
public:
    CAcFdUiFieldManager(void);
    ~CAcFdUiFieldManager(void);

    BOOL			RegisterFieldDialogHook	(CAcFdUiFieldDialogHook* pDlgHook);
    BOOL			UnregisterFieldDialogHook(const CAcFdUiFieldDialogHook* pDlgHook);
    int				GetRegisteredDialogHooks(AcFdUiFieldDialogHookArray& hooks);

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;
};
