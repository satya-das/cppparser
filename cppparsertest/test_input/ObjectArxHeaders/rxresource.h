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


#ifndef _RXRESOURCE_H_
#define _RXRESOURCE_H_
#pragma once

#include "acbasedefs.h"
#include "PAL/api/def.h"
#include "adesk.h"
#include "pimplapi.h"
#include "AcHeapOpers.h"

class AcString;

#undef PAL
namespace Autodesk { namespace AutoCAD {namespace PAL { class AcRxResourceInstanceImp; } } }

class AcRxResourceInstance 
    : public Pimpl::ApiPart<AcHeapOperators, Autodesk::AutoCAD::PAL::AcRxResourceInstanceImp>
{
public:
    ACBASE_PORT explicit AcRxResourceInstance(const wchar_t* path);

    //for compatibility with existing code, do not use in new code
    ACBASE_PORT AcRxResourceInstance(void* hInst);

    ACBASE_PORT AcRxResourceInstance(const AcRxResourceInstance& other);

    ACBASE_PORT ~AcRxResourceInstance();

    /// <summary>
    /// Move constructor
    /// </summary>
    AcRxResourceInstance(AcRxResourceInstance&&) = delete;

    /// <summary>
    /// Assignment operator
    /// </summary>
    AcRxResourceInstance& operator= (AcRxResourceInstance&&) = delete;

    // disable copy assignment operator
    AcRxResourceInstance& operator= (const AcRxResourceInstance& other) = delete;

    ACBASE_PORT bool tryLoadString(Adesk::Int32 id, AcString& out) const noexcept;
    ACBASE_PORT bool isLoaded() const noexcept;
    
    ACBASE_PORT bool loadDataResource(Adesk::Int32 id, unsigned long& resourceSize, const void*& data) const noexcept;

    /// <summary>
    /// For Autodesk internal use only
    /// frees a resource loaded by loadDataResource.
    /// </summary>
    /// 
    /// <param name="data">a reference to a pointer set by loadDataResource</param>
    ACBASE_PORT void freeDataResource(const void*& data) const noexcept;

    /// <summary>
    /// Static accessor for a default empty AcRxResourceInstance
    /// </summary>
    /// 
    /// <returns>
    /// Returns a const reference to the the global empty default AcRxResourceInstance
    /// </returns>

    ACBASE_PORT const static AcRxResourceInstance& empty();
};
#endif 