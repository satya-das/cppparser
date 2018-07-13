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
// This header file contains the declaration of acutAssertMessage.
// We provide a separate header file for this function to avoid header-file
// dependencies caused by placing the declaration in our header files.
// This header file needs to be "benign" for safe usage in other header
// files that provide assert-like macros.
// 

#ifndef _ACUTASRT_H
#define _ACUTASRT_H

#include "pal/api/def.h"
#include "AdAChar.h"
#pragma pack (push, 8)

ACPAL_PORT void acutAssertMessage(
    const ACHAR *condition,
    const ACHAR *filename,
    int         lineNumber,
    const ACHAR *status);

#pragma pack (pop)
#endif // !_ACUTASRT_H
