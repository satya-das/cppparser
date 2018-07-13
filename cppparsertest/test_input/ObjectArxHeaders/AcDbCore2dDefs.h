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
#pragma once

#if defined (ACDBCORE2D_API)
    #define   ACDBCORE2D_PORT _declspec(dllexport)
    #define   ACDBCORE2D_DATA_PORT _declspec(dllexport)
#else
#if defined (ACDBCORE2D_STATIC)
    #define   ACDBCORE2D_PORT 
    #define   ACDBCORE2D_DATA_PORT
#else
    #define ACDBCORE2D_PORT
    #define ACDBCORE2D_DATA_PORT _declspec(dllimport)
#endif
#endif
