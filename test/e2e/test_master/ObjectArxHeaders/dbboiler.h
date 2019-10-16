#ifndef AC_DBBOILER_H
#  define AC_DBBOILER_H
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#  include "rxboiler.h"
#  define ACDB_DECLARE_MEMBERS(CLASSNAME)	 \
private: \
    friend class AcDbSystemInternals; \
protected: \
    CLASSNAME(AcDbSystemInternals*); \
public: \
    ACRX_DECLARE_MEMBERS(CLASSNAME)
#  define ACDBCORE2D_DECLARE_MEMBERS(CLASSNAME)	 \
private: \
    friend class AcDbSystemInternals; \
protected: \
    CLASSNAME(AcDbSystemInternals*); \
public: \
    ACRX_DECLARE_MEMBERS_EXPIMP(CLASSNAME, ACDBCORE2D_PORT)
#endif
