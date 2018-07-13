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
//
// acestext.h:   Define an exported function that exchanges
//               an Acad::ErrorStatus enum value for a string
//               describing the error message.

#ifndef _AD_ACESTEXT_H
#define _AD_ACESTEXT_H 1

#include "acdb.h"
#include "AdAChar.h"

const ACHAR * acadErrorStatusText(Acad::ErrorStatus);

#endif
