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


#ifndef _RXSHAREDOBJ_H_
#define _RXSHAREDOBJ_H_
#pragma once

#include "acbasedefs.h"
#include "PAL/api/def.h"
#include "adesk.h"
#include "pimplapi.h"
#include "AcHeapOpers.h"
#include <memory>

#undef PAL
namespace Autodesk { namespace AutoCAD {namespace PAL { class AcRxSharedObjImp; } } }

class AcRxSharedObject
    : public Pimpl::ApiPart<AcHeapOperators, Autodesk::AutoCAD::PAL::AcRxSharedObjImp>
{
private:
    AcRxSharedObject(Autodesk::AutoCAD::PAL::AcRxSharedObjImp* soImp);

    AcRxSharedObject(const AcRxSharedObject& from) = delete;
    AcRxSharedObject& operator=(const AcRxSharedObject& from) = delete;
    AcRxSharedObject(const wchar_t*) = delete;
public:
    ACBASE_PORT AcRxSharedObject();
    ACBASE_PORT AcRxSharedObject(void* nativeHandle);
    ACBASE_PORT ~AcRxSharedObject() = default;
    ACBASE_PORT AcRxSharedObject(AcRxSharedObject&& from) = default;
    ACBASE_PORT AcRxSharedObject& operator=(AcRxSharedObject&& from);
    

    ACBASE_PORT bool isLoaded() const noexcept;
    ACBASE_PORT void * getSymbol(const char * /*ascii*/ name) const noexcept;

    static ACBASE_PORT AcRxSharedObject tryLoad(const wchar_t* path, bool autoRelease = true);    
};

#endif 