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


#ifndef _acdbads_h
#define _acdbads_h 1

#include "adsdef.h"
#include "acmem.h"
#include "AdAChar.h"

#pragma pack (push, 8)

#ifdef __cplusplus
#include "adesk.h"
#include "acdbcore2ddefs.h"
#endif

// These functions are exported with both extern "C" and C++ linkage. Some day
// we may drop support for C applications, however.

void           acdbFail (const ACHAR *str);
int            acdbHandEnt (const ACHAR *handle, ads_name entres);

// These functions are only available to C++ apps.
#ifdef __cplusplus

ACDBCORE2D_PORT int  acdbXdRoom (const ads_name ent, Adesk::Int32 *result);
ACDBCORE2D_PORT int  acdbXdSize (const resbuf *rb, Adesk::Int32 *result);

// Function to save a string ensuring no buffer overflow if,
// when converted, characters expand to \U+ sequences 
ACDBCORE2D_PORT ACHAR * acdbXStrSave (ACHAR *pSource, ACHAR **pDest);

// Function to uppercase a table name
ACDBCORE2D_PORT int     acdbXStrCase (ACHAR *str, size_t strLen);

#endif

/* Define macros to copy them.  NOTE that the result is the SECOND argument,
   consistent with ADS usage.  The standard C ones require <string.h> */
#ifdef __STDC__
#define acdbNameSet(from, to)  (memcpy(to, from, sizeof(ads_name)))
#define acdbPointSet(from,to)  (memcpy(to, from, sizeof(ads_point)))
#else
#define acdbNameSet(from, to)  (*(to)= *(from), (to)[1]=(from)[1])
#define acdbPointSet(from, to) (*(to)= *(from), (to)[1]=(from)[1], (to)[2]=(from)[2])
#endif  /* !__STDC__ */

/* Define null value for ads_names.  These values are NOT guaranteed valid;
   that is, there is no actual guarantee (such as C gives with NULL) that the
   system will never under any circumstances generate the values as valid data.
   The correct values will be created as part of the Lisp reinitialization
   project, if we go through with that one, and will then be inserted here.
   */
#define acdbNameClear(name)    name[0] = name[1] = 0
#define acdbNameNil(name)      (name[0] == 0 && name[1] == 0)
#define acdbNameEqual(name1, name2)  (name1[0]==name2[0] \
                                       && name1[1]==name2[1])
#pragma pack (pop)

#endif // !acdbads.h

