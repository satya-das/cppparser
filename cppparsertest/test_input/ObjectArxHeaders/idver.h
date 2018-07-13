//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
// This computer source code and related instructions and comments
// are the unpublished confidential and proprietary information of
// Autodesk, Inc. and are protected under applicable copyright and
// trade secret law.  They may not be disclosed to, copied or used
// by any third party without the prior written consent of Autodesk, Inc.
//
//////////////////////////////////////////////////////////////////////////////

//

#ifndef   _IDVER_H
#define   _IDVER_H

#include "id.h"

//
// use dummy versions to make sure the incremental build will not break by version // update.
#ifndef AC_BLDENV
    #define ACADV_BLDMAJOR  0   /*BuildMajor*/
    #define ACADV_BLDMINOR  0   /*BuildMinor*/
    #define ACADV_BLDBRANCH 0   /*BuildBranch*/
    #define ACADV_BLDSTREAM O   /*BuildStream*/
#else
    #include "_idver.h"
#endif

//
// This file uses the following convention to distinguish macros that
// files including this file can use (for external use) and macros that
// only this file should use (for internal use).
//
// Macros for internal use have two underscores
// Macros for external use start with ACADV_ (one underscore).
//

#define VALUE2STR(x) #x
#define ID2STR(a) ID2STR__1(a)
#define ID2STR__1(a) VALUE2STR(a)

//
// Calculate the numbers for the FILEVERSION resources.
//
// The four parts of the file version resources,
// each of which evaluates to an integer constant.
//      ACADV_{RCFILEVER1, RCFILEVER2, RCFILEVER3, RCFILEVER4}.
//
// We keep the FILEVERSION and PRODUCTVERSION numbers the same.
// So these are also used for setting the ProductVersion in rc files.
#define ACADV_RCFILEVER1 ACADV_RELMAJOR
#define ACADV_RCFILEVER2 ACADV_RELMINOR
#define ACADV_RCFILEVER3 ACADV_BLDMAJOR
#define ACADV_RCFILEVER4 ACADV_BLDMINOR
#define ACADV_RCFILEVER5 ACADV_BLDBRANCH

#define ACADV_RCFILEVER1_CORRECTION (6 + ACADV_RCFILEVER1)

// The following utility macros build the stringized form of the
// version numbers.
//
#define ACADV_RCFILEVERSTR ID2STR(ACADV_RCFILEVER1) "." \
                ID2STR(ACADV_RCFILEVER2) "." \
                ID2STR(ACADV_RCFILEVER3) "." \
                ID2STR(ACADV_RCFILEVER5) "." \
                ID2STR(ACADV_RCFILEVER4)

// Moved here from acadmfc.rc2
#define ACADV_PRODVERSION "R" ACADV_RCFILEVERSTR

//
// Build ACADV_VERNUM.
//
// Create a string form of the build numbers, e.g.,
// "N.20.0", "N.255.9999".
//
#if defined(_MSC_VER) || defined(UNICODE)
// This definition is used when included by source files
#define ACADV_VERNUM  ACRX_T(ID2STR(ACADV_BLDSTREAM)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDMAJOR)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDBRANCH)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDMINOR))
#else // !_MSC_VER
// This definition is used when included by resource files
#define ACADV_VERNUM ID2STR(ACADV_BLDSTREAM) "." \
                     ID2STR(ACADV_BLDMAJOR) "." \
                     ID2STR(ACADV_BLDBRANCH) "." \
                     ID2STR(ACADV_BLDMINOR)
#endif // !_MSC_VER

//
// Build ACADV_VERNAME
//
// Create the string form of the release numbers, e.g.,
// "16.0" or "16.1".
//
#if defined(_MSC_VER) || defined(UNICODE)
// This definition is used when included by source files
#define ACADV_VERNAME ACRX_T(ID2STR(ACADV_RELMAJOR)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_RELMINOR))
#else // !_MSC_VER
// This definition is used when included by resource files
#define ACADV_VERNAME ID2STR(ACADV_RELMAJOR) "." \
                      ID2STR(ACADV_RELMINOR)
#endif // !_MSC_VER

//
// ACADV_VERFULL varies with production and nonproduction builds.
//
#if defined(PRODUCTION)
#define ACADV_VERFULL     ACADV_VERNAME
#else
#define ACADV_VERFULL     ACADV_VERNUM
#endif

// The following macros exist to simplify usage in RC files.

#define ACADV_BLDVERSTR   ACADV_VERNUM

// And finally, a copyright string for general use.
//
#define ACAD_COPYRIGHT    "Copyright 2018 Autodesk, Inc.  All rights reserved."
#define ACAD_COPYRIGHT_YEAR   "2018"

// Type library version for AutoCAD Type Library
// (axdb<ver><lang>.tlb)
//
#define ACAD_TLBVERSION_MAJOR   1
#define ACAD_TLBVERSION_MINOR   0
#define ACAD_TLBVERSION         ACAD_TLBVERSION_MAJOR.ACAD_TLBVERSION_MINOR

// String form of the type library version (ex. "1.0")
#ifdef _MSC_VER
// This definition is used when included by source files
#define ACAD_TLBVERSIONSTR      ACRX_T(ID2STR(ACAD_TLBVERSION_MAJOR)) ACRX_T(".") \
                                ACRX_T(ID2STR(ACAD_TLBVERSION_MINOR))
#else // !_MSC_VER
// This definition is used when included by resource files
#define ACAD_TLBVERSIONSTR      ID2STR(ACAD_TLBVERSION_MAJOR) "." \
                                ID2STR(ACAD_TLBVERSION_MINOR)
#endif// !_MSC_VER

// Type library version for AutoCAD/ObjectDBX Common Type Library
// (acax<ver><lang>.tlb)
//
#define ACDB_TLBVERSION_MAJOR   1
#define ACDB_TLBVERSION_MINOR   0
#define ACDB_TLBVERSION         ACDB_TLBVERSION_MAJOR.ACDB_TLBVERSION_MINOR

// String form of the type library version (ex. "1.0")
#ifdef _MSC_VER
// This definition is used when included by source files
#define ACDB_TLBVERSIONSTR      ACRX_T(ID2STR(ACDB_TLBVERSION_MAJOR)) ACRX_T(".") \
                                ACRX_T(ID2STR(ACDB_TLBVERSION_MINOR))
#else // !_MSC_VER
// This definition is used when included by resource files
#define ACDB_TLBVERSIONSTR      ID2STR(ACDB_TLBVERSION_MAJOR) "." \
                                ID2STR(ACDB_TLBVERSION_MINOR)
#endif// !_MSC_VER


#endif /* _IDVER_H */
