//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEVC2DAR_H
#  define AC_GEVC2DAR_H
#  include "adesk.h"
#  include "assert.h"
#  include "gevec2d.h"
#  include "acarray.h"
typedef AcArray<AcGeVector2d> AcGeVector2dArray;
#  if  GE_LOCATED_NEW
GE_DLLEXPIMPORT AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeVector2dArray* pT);
#  endif
#endif
