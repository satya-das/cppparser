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
//

#ifndef _ACGIUTIL_H
#define _ACGIUTIL_H 1

#include "dbid.h"
#include "AdAChar.h"
#include "acgi.h"

#pragma pack (push, 8)

Acad::ErrorStatus fromAcDbTextStyle(AcGiTextStyle&,
                              const AcDbObjectId& AcDbStyleId);
Acad::ErrorStatus fromAcDbTextStyle(AcGiTextStyle&, const ACHAR * AcDbStyleName);

// This version of toAcDbTextStyle will use the styleName of the
// AcGiTextStyle as the name of the AcDbTextStyle to write to.  If
// the AcGiTextStyle's styleName == NULL, then a random name will
// be generated and used for the AcDbTextStyle and the AcGiTextStyle's
// styleName will be set to the random name as well.
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&);

// This version of toAcDbTextStyle will use the styleName of the
// AcGiTextStyle as the name of the AcDbTextStyle to write to.  If
// the AcGiTextStyle's styleName == NULL, then a random name will
// be generated and used for the AcDbTextStyle and the AcGiTextStyle's
// styleName will be set to the random name as well.
//
// AcDbStyleId is set to the objectId of the AcDbTextStyleTableRecord
// object that maps to the AcGiTextStyle's name.
//
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&,
                                  AcDbObjectId& AcDbStyleId);

// Agruments reversed to avoid ambiguious function overloading. In
// this version,  the AcDbObjectId is the Id of the AcDbTextStyleTableRecord
// to write.
//
Acad::ErrorStatus toAcDbTextStyle(const AcDbObjectId AcDbStyleId,
                                  AcGiTextStyle&);

Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&, const ACHAR * AcDbStyleName);

// AcDbStyleId is set to the objectId of the AcDbTextStyleTableRecord
// object that maps to the AcGiTextStyle's name.
//
Acad::ErrorStatus toAcDbTextStyle(AcGiTextStyle&, const ACHAR * AcDbStyleName,
                                  AcDbObjectId& AcDbStyleId);


#pragma pack (pop)

#endif // ACGIUTIL_H
