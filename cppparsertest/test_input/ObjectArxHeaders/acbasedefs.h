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

#ifndef  ACBASEDEFS_H
#define ACBASEDEFS_H

//API exported by ac1stXX.dll

#if defined(_MSC_VER) 
    #ifdef ACBASE_API
        #define ACBASE_PORT _declspec(dllexport)
    #else
//don't use __declspec(dllimport) so that we can use the .objs with both static and dynamc linking
        #define ACBASE_PORT
    #endif // ACBASE_API
#elif defined(__clang__)
    // On OS X, we will export all symbols by default and will use GCC
    // attributes to exclude symbols we don't want to export.
    #define ACBASE_PORT
#else
    #error Visual C++ or Clang compiler is required.
#endif


#endif //ACBASEDEFS_H
