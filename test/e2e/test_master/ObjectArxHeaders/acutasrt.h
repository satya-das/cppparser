//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ACUTASRT_H
#  define _ACUTASRT_H
#  include "pal/api/def.h"
#  include "AdAChar.h"
#  pragma  pack (push, 8)
ACPAL_PORT void acutAssertMessage(const ACHAR* condition, const ACHAR* filename, int lineNumber, const ACHAR* status);
#  pragma  pack (pop)
#endif
