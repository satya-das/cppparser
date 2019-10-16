//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEINTARR_H
#  define AC_GEINTARR_H
#  ifndef unix
#    include <stdlib.h>
#  endif
#  include "adesk.h"
#  include "assert.h"
#  include "acarray.h"
typedef AcArray<int> AcGeIntArray;
typedef AcArray<Adesk::IntPtr> AcGeIntPtrArray;
#  if  GE_LOCATED_NEW
GE_DLLEXPIMPORT AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeIntArray* pT);
#  endif
#endif
