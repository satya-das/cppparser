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


#pragma once

//This header file is used to suppress warnings from the /analyze flag. These warnings
//are very useful and should be dealt with but we can't unleash them all at once
//
//The compiler can only handle 56 #pragma warning statements so we group the warnings by 10
#pragma warning(disable:6011 6309 6308 6244 6031 6387 6320 6255 6322 6386 6385 6246)
#pragma warning(disable:6209 6276 6335 6510 6516 6001 6262 6054 6211 6293 6295 6297)
#pragma warning(disable:6269 6305 6216 6239 6059 6328 6326 6202 6200 6263 6271 6292)
#pragma warning(disable:6258 6400)
//#pragma warning(error:4238 4296 4213)
