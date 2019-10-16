//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef DB_MIGRATION_H
#  define DB_MIGRATION_H
#  include "adsmigr.h"
#  include "acutmigr.h"
#  define acdbSetCurrentVPort	acedSetCurrentVPort
#  define acdbGetCurrentSelectionSet	acedGetCurrentSelectionSet
#  define acdbCurDwg	acdbHostApplicationServices()->workingDatabase
#  define acdbGetRGB	acedGetRGB
#  define acdbGetCurViewportObjectId	acedGetCurViewportObjectId
#  define getCurDwgXrefGraph	acedGetCurDwgXrefGraph
#endif
