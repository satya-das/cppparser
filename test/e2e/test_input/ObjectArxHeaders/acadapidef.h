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

#ifndef ACADAPIDEF_H
#define ACADAPIDEF_HH

#ifndef _ADESK_MAC_
#ifndef ACAD_PORT
	#ifdef ACAD_API
		#define ACAD_PORT _declspec(dllexport)
	#else
		#define ACAD_PORT _declspec(dllimport)
	#endif
#endif
#else
// On OS X, we will export all symbols by default and will use GCC
// attributes to exclude symbols we don't want to export.
#define ACAD_PORT
#endif // _ADESK_MAC_


#endif //ACADAPIDEF_H
