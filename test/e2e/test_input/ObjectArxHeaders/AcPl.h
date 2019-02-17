//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//  DESCRIPTION:  Common header for plot APIs
//

#ifndef ACPL_H
#define ACPL_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// Note: _ACPL_BUILD should be defined only when building the DLL.

#ifdef  _ACPL_BUILD
#  define ACPL_PORT  __declspec(dllexport)
#else
#  define ACPL_PORT
#endif


#endif // ACPL_H
