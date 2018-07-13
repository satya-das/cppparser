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
// DESCRIPTION: 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ACDB_DBXUTIL_H
#define ACDB_DBXUTIL_H 1

#include "acdbport.h"

ACDB_PORT bool acdbGetPreviewBitmapFromDwg(const ACHAR* pszDwgfilename,
    HBITMAP* pPreviewBmp,
    HPALETTE* pRetPal);


#endif // ACDB_DBXUTIL_H
