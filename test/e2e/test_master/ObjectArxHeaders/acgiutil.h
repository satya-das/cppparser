//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ACGIUTIL_H
#  define _ACGIUTIL_H	1
#  include "dbid.h"
#  include "AdAChar.h"
#  include "acgi.h"
#  pragma  pack (push, 8)
Acad::ErrorStatus fromAcDbTextStyle(AcGiTextStyle&, const AcDbObjectId& AcDbStyleId);
Acad::ErrorStatus fromAcDbTextStyle(AcGiTextStyle&, const ACHAR* AcDbStyleName);
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&);
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&, AcDbObjectId& AcDbStyleId);
Acad::ErrorStatus toAcDbTextStyle(const AcDbObjectId AcDbStyleId, AcGiTextStyle&);
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&, const ACHAR* AcDbStyleName);
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&, const ACHAR* AcDbStyleName, AcDbObjectId& AcDbStyleId);
#  pragma  pack (pop)
#endif
