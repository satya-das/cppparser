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

#ifndef  ACCOREDEFS_H
#define ACCOREDEFS_H

#ifndef ACCORE_PORT
#ifdef ACCORE_API
    #define ACCORE_PORT _declspec(dllexport)
    #define ACCORE_DATA_PORT _declspec(dllexport)
    #define ACCORE_STATIC_DATA_PORT _declspec(dllexport) static
#else
    #define ACCORE_PORT
    #define ACCORE_DATA_PORT _declspec(dllimport)
    #define ACCORE_STATIC_DATA_PORT _declspec(dllimport) static
#endif
#endif


#endif //ACCOREDEFS_H
