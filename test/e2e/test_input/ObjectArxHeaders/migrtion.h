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
// DESCRIPTION: Migration assistance from R14 to R15.
//
// WARNING: This file will not be available for releases subsequent to
// R15. At some point, you should make global substitutions in your code.
//

#ifndef DB_MIGRATION_H
#define DB_MIGRATION_H

#include "adsmigr.h"
#include "acutmigr.h"

#define acdbSetCurrentVPort acedSetCurrentVPort
#define acdbGetCurrentSelectionSet acedGetCurrentSelectionSet

// The following macro will require that you #include "dbapserv.h" and
// add AcUtil15.lib to the LINK line in your makefile.
//
#define acdbCurDwg acdbHostApplicationServices()->workingDatabase

#define  acdbGetRGB acedGetRGB

#define acdbGetCurViewportObjectId acedGetCurViewportObjectId

#define getCurDwgXrefGraph acedGetCurDwgXrefGraph

#endif // DB_MIGRATION_H
