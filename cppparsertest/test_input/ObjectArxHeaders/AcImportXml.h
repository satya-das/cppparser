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
#include "adesk.h"
#ifdef _ADESK_WINDOWS_
#ifndef AC_DO_NO_IMPORT
#pragma warning (push)
#pragma warning(disable : 4279)
#pragma warning(disable : 4192)
#import "msxml6.dll" named_guids rename_namespace("MSXML") rename("offset", "MSXMLoffset")
#pragma warning (pop)
#else // AC_DO_NO_IMPORT
#include "msxml6.tlh"
#endif
__declspec(selectany) extern const GUID CLSID_DOMDocumentAcad = MSXML::CLSID_DOMDocument60;
#endif // _ADESK_WINDOWS_
