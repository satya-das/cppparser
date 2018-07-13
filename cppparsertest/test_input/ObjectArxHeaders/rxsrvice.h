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

#ifndef _rxsrvice_h
#define _rxsrvice_h 1

#include "rxobject.h"
#pragma pack (push, 8)

extern "C" {
    typedef AcRx::AppRetCode (*DepFuncPtr)(AcRx::AppMsgCode, void*);
}

class AcRxServicePrototype;
class AcRxService;

class AcRxService: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxService);
    AcRxService();
    virtual ~AcRxService();

    AcRxObject* getSysInfo() const;
    void        setSysInfo(AcRxObject* sysInfoObj);

    void        addDependency();
    void        removeDependency();

    Adesk::Boolean unloadable() const;

    // The following functions are not currently implemented
    // They are present as place holders so that they can be
    // implemented in the future without breaking binary
    // compatibility
    //
    DepFuncPtr dependencyFunctionPtr();
    void setDependencyFunctionPtr(DepFuncPtr);

private:
    AcRxServicePrototype* mpImpService;
};

#pragma pack (pop)
#endif
