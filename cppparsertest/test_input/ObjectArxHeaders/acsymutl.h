//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//  DESCRIPTION:
//
//  Namespace AcEdSymbolUtilities contains various AutoCAD-specific
//  utilities for working with symbol names, symbol records, and symbol
//  tables.  The main access to the utility functions is through
//  "acedSymUtil()", which you dereference to call the member
//  functions of AcEdSymbolUtilities::Services.
//
#ifndef _ACSYMUTL_H
#define _ACSYMUTL_H

#include <assert.h>
#include "acadstrc.h"
#include "dbsymutl.h"
#pragma pack (push, 8)

#define ACEDSYMUTIL_SERVICES_CURRENT_VERSION 100

class AcDbDatabase;

namespace AcEdSymbolUtilities
{

enum CrSpMode {
    kCrEndsInput = true
  , kCrSpEndsInput = false
};

enum NameCaseMode {
    kPreserveCase = true
  , kForceToUpper = false
};

class Services
{
public:
    enum { kCurrentVersion = ACEDSYMUTIL_SERVICES_CURRENT_VERSION };
    virtual unsigned version() const = 0;

    virtual Acad::PromptStatus getCompatibleSymbolString(
                                      ACHAR*&        pResponse,
                                      const ACHAR*   prompt,
                                      AcDbDatabase * pDb) const = 0;

    virtual Acad::PromptStatus getSymbolString(
                                      ACHAR*&      pResponse,
                                      const ACHAR* prompt,
                                      bool         onlyCrEndsInput,
                                      bool         preserveCase) const = 0;

}; // End Services

// For use by AcEdSymbolUtilities only!
#define ACEDSYMUTIL_SERVICESNAME_WITH_VERSION_1(n,v) n ## v
#define ACEDSYMUTIL_SERVICESNAME_WITH_VERSION(n,v) \
        ACEDSYMUTIL_SERVICESNAME_WITH_VERSION_1(n,v)
#define ACEDSYMUTIL_SERVICES_NAME \
        ACEDSYMUTIL_SERVICESNAME_WITH_VERSION( \
            servicesPtr, \
            ACEDSYMUTIL_SERVICES_CURRENT_VERSION)
extern const Services * ACEDSYMUTIL_SERVICES_NAME();

// --------- Inline definitions ---------

inline const Services *
servicesPtr()
{
    const Services * pSymUtil = ACEDSYMUTIL_SERVICES_NAME();
    assert(pSymUtil != 0);
    assert(pSymUtil->version() == Services::kCurrentVersion);
    return pSymUtil;
}

} // End AcEdSymbolUtilities

namespace AcEdSymUtil = AcEdSymbolUtilities;

typedef AcEdSymbolUtilities::Services AcEdSymUtilServices;

inline const AcEdSymUtilServices *
acedSymUtil()
{
    return AcEdSymbolUtilities::servicesPtr();
}

#pragma pack (pop)
#endif // _ACSYMUTL_H
