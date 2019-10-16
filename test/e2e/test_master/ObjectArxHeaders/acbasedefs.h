//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#ifndef ACBASEDEFS_H
#  define ACBASEDEFS_H
#  if  defined(_MSC_VER) 
#    ifdef ACBASE_API
#      define ACBASE_PORT	_declspec(dllexport)
#    else 
#      define ACBASE_PORT
#    endif
#  elif  defined(__clang__)
#    define ACBASE_PORT
#  else 
#  endif
#endif
