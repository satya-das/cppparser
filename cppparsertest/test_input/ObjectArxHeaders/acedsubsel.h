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


#ifndef _acedsubsel_h
#define _acedsubsel_h 1

#pragma once

class AcDbFullSubentPath;

#include "acarray.h"
#include "acdb.h"
#include "adsdef.h"

#pragma pack (push, 8)

/* AutoCAD Sub-entity selection set routines */

int            acedSSSubentLength (const ads_name sname, Adesk::Int32 index, Adesk::Int32* len);

int            acedSSSubentAdd    (const AcDbFullSubentPath& subentity, 
                                   const ads_name sname, 
                                   ads_name result);

int            acedSSSubentDel    (const AcDbFullSubentPath& subentity, 
                                   const ads_name ss);

int            acedSSSubentMemb   (const AcDbFullSubentPath& subentity,
                                   const ads_name ss);

int            acedSSSubentName   (const ads_name ss, 
                                   Adesk::Int32 entIndex, 
                                   Adesk::Int32 subentIndex, 
                                   AcDbFullSubentPath& subentity);

int            acedSSSubentNameX  (struct resbuf** rbpp, 
                                   const ads_name ss,
                                   const Adesk::Int32 entIndex, 
                                   const Adesk::Int32 subentIndex,
                                   unsigned int flags);

int            acedSSSetSubentTypes(const AcArray<AcDb::SubentType>& types);


#pragma pack (pop)
#endif  /* !_acedads_h */
