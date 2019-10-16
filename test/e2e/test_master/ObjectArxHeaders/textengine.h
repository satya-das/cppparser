/////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTENGINE_H
#  define _TEXTENGINE_H	1
#  include "acgi.h"
#  include "AdAChar.h"
#  include "Adesk.h"
#  pragma  pack (push, 8)
typedef void (*PolylineCallback) (int, int const *, AcGePoint3d const *, void*);
typedef void (*UnicodeCallback) (AcFontHandle*, wchar_t const *, int, void*);
class AcGiTextEngine
{
public:
  static AcGiTextEngine* create();
  virtual ~AcGiTextEngine()
  {
  }
  virtual void getExtents(AcGiTextStyle& ts, ACHAR const * pStr, int nLength, bool bPenUp, bool bRaw, AcGePoint2d& extents) = 0;
  virtual void tessellate(AcGiTextStyle& ts, ACHAR const * pStr, int nLength, bool bRaw, double deviation, void* pVoid, PolylineCallback pPolylineCallback) = 0;
  virtual void tessellate(AcGiTextStyle& ts, ACHAR const * pString, int nLength, bool bRaw, void* pVoid, UnicodeCallback pUnicodeCallback, PolylineCallback pPolylineCallback) = 0;
};
#  pragma  pack (pop)
#endif
