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
#if  !defined(_ACHTMLAPI_H_INCLUDED_)
#	define _ACHTMLAPI_H_INCLUDED_
#	if  _MSC_VER >= 1000
#		pragma  once
#	endif
class CAdUiPaletteSet;
int acedAddHTMLPalette(CAdUiPaletteSet* ps, const ACHAR* name, const ACHAR* uriOfHtmlPage);
bool acedShowHTMLModalWindow(HWND owner, const ACHAR* uriOfHtmlPage, bool persistSizeAndPosition = true);
HWND acedShowHTMLModelessWindow(HWND owner, const ACHAR* uriOfHtmlPage, bool persistSizeAndPosition = true);
struct HtmlWindowOptions
{
	enum HtmlWindowFlags
	{
		eAllowResize = 0x0001,
		eAllowMinimize = 0x0002,
		eAllowMaximize = 0x0004,
		eInitPosition = 0x0008,
		eInitSize = 0x0010,
		eMaxSize = 0x0020,
		eMinSize = 0x0040,
		ePersistSizeAndPosition = 0x0080
	};
	UINT flags;
	UINT x;
	UINT y;
	UINT width;
	UINT height;
	UINT maxWidth;
	UINT maxHeight;
	UINT minWidth;
	UINT minHeight;
};
bool acedShowHTMLModalWindow(HWND owner, const ACHAR* uriOfHtmlPage, HtmlWindowOptions opts);
class AcApDocWindow;
AcApDocWindow* acedAddHTMLDocWindow(const ACHAR* title, const ACHAR* uriOfHtmlPage);
void acedLoadJSScript(const ACHAR* pUriOfJSFile);
#endif
