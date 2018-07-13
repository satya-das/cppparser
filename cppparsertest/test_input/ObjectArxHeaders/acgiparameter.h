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

#include "rxcopyonwriteobject.h"

#pragma pack(push, 8)

class AcGiParameterImp;

///////////////////////////////////////////////////////////////////////////////
// class AcGiParameter
//
class ACDBCORE2D_PORT AcGiParameter : public AcRxCopyOnWriteObject
{
    friend class AcGiParameterImp;

public:
    ACRX_DECLARE_MEMBERS_READWRITE(AcGiParameter, AcGiParameterImp);

    AcGiParameter(AcGiParameterImp* pImp);
    AcGiParameter(const AcGiParameter& other);
    const AcGiParameter& operator=(const AcGiParameter& other);
};

#pragma pack(pop)
