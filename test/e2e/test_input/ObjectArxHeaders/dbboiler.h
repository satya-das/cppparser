#ifndef AC_DBBOILER_H
#define AC_DBBOILER_H
//
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
// DESCRIPTION: Main Exported Database Library Definitions.
//     Macros primarily used in the api headers

#include "rxboiler.h"

// Macro for common declarations of classes derived from
// AcDbObject which are built into AutoCAD.
//
// This macro is NOT intended for application-defined classes derived
// from AcDbObject when declaring their class header.  This macro declares
// an internally used form of constructor, which takes the
// AcDbSystemInternals* argument.  Rx applications should not define
// such constructors for their database object classes, but they should
// be ignored by the system anyway.
//
// Application-defined classes are advised to use the ACRX_DECLARE_MEMBERS
// macro instead, and to consult the documentation for related definitions.
//
#define ACDB_DECLARE_MEMBERS(CLASSNAME) \
private: \
    friend class AcDbSystemInternals; \
protected: \
    CLASSNAME(AcDbSystemInternals*); \
public: \
    ACRX_DECLARE_MEMBERS(CLASSNAME)

#define ACDBCORE2D_DECLARE_MEMBERS(CLASSNAME) \
private: \
    friend class AcDbSystemInternals; \
protected: \
    CLASSNAME(AcDbSystemInternals*); \
public: \
    ACRX_DECLARE_MEMBERS_EXPIMP(CLASSNAME, ACDBCORE2D_PORT)

#endif
