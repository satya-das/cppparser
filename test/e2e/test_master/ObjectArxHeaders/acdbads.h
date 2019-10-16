//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _acdbads_h
#  define _acdbads_h	1
#  include "adsdef.h"
#  include "acmem.h"
#  include "AdAChar.h"
#  pragma  pack (push, 8)
#  ifdef __cplusplus
#    include "adesk.h"
#    include "acdbcore2ddefs.h"
#  endif
void acdbFail(const ACHAR* str);
int acdbHandEnt(const ACHAR* handle, ads_name entres);
#  ifdef __cplusplus
ACDBCORE2D_PORT int acdbXdRoom(const ads_name ent, Adesk::Int32* result);
ACDBCORE2D_PORT int acdbXdSize(const resbuf* rb, Adesk::Int32* result);
ACDBCORE2D_PORT ACHAR* acdbXStrSave(ACHAR* pSource, ACHAR** pDest);
ACDBCORE2D_PORT int acdbXStrCase(ACHAR* str, size_t strLen);
#  endif
#  ifdef __STDC__
#    define acdbNameSet(from, to)	  (memcpy(to, from, sizeof(ads_name)))
#    define acdbPointSet(from,to)	  (memcpy(to, from, sizeof(ads_point)))
#  else 
#    define acdbNameSet(from, to)	  (*(to)= *(from), (to)[1]=(from)[1])
#    define acdbPointSet(from, to)	 (*(to)= *(from), (to)[1]=(from)[1], (to)[2]=(from)[2])
#  endif
#  define acdbNameClear(name)	    name[0] = name[1] = 0
#  define acdbNameNil(name)	      (name[0] == 0 && name[1] == 0)
#  define acdbNameEqual(name1, name2)	  (name1[0]==name2[0] \
                                       && name1[1]==name2[1])
#  pragma  pack (pop)
#endif
