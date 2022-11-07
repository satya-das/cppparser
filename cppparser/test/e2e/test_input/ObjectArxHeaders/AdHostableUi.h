//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 by Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef ADHOSTABLEUI_H
#define ADHOSTABLEUI_H
#include "adesk.h"

#ifdef  ADHOSTABLE_API
#define ADHOSTABLE_PORT __declspec(dllexport)
#else
#define ADHOSTABLE_PORT
#endif


#endif 
