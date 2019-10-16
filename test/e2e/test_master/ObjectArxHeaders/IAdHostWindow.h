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
#ifndef ADHOSTWINDOW_H
#  define ADHOSTWINDOW_H
#  include "adhostableui.h"
class IAdHostWindow
{
public:
  virtual HWND windowHandle() = 0;
};
#endif
