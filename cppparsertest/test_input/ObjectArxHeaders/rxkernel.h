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

#ifndef _rxkernel_h
#define _rxkernel_h 1

#include "rxsrvice.h"
#pragma pack (push, 8)

class AcRxClass;
class AcRxDictionary;

class ADESK_NO_VTABLE AcRxKernel : public AcRxService
{
public:
    ACRX_DECLARE_MEMBERS(AcRxKernel);
    AcRxKernel();
    virtual ~AcRxKernel();

    virtual
    AcRxDictionary* newAcRxDictionary(Adesk::Boolean sorted = Adesk::kTrue,
                                      Adesk::Boolean ignoreCase
                                                           = Adesk::kFalse) = 0;

    virtual
    AcRxDictionary* newAcRxDictionary(Adesk::UInt32 length,
                                      Adesk::Boolean delObjects,
                                      Adesk::Boolean sorted = Adesk::kTrue,
                                      Adesk::Boolean ignoreCase
                                                           = Adesk::kFalse) = 0;

    virtual
    AcRxDictionary* newAcRxDictionary(const AcRxClass * filter) = 0;
};

#define acrxKernel \
    AcRxKernel::cast(AcRxDictionary::cast(\
    acrxSysRegistry()->at(ACRX_SERVICE_DICTIONARY))->at(ACRX_KERNEL_SERVICES))

#pragma pack (pop)
#endif
