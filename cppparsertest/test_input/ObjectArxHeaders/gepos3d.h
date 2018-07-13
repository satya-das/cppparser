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
//
// DESCRIPTION:
//
// This file contains the class AcGePosition3d - A 3d point entity.

#ifndef AC_GEPOS3D_H
#define AC_GEPOS3D_H

#include "adesk.h"
#include "gepent3d.h"
#include "gepnt3d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGePosition3d : public AcGePointEnt3d
{
public:
    AcGePosition3d ();
    AcGePosition3d (const AcGePoint3d& pnt);
    AcGePosition3d (double x, double y, double z);
    AcGePosition3d (const AcGePosition3d& pos);

    // Set point coordinates.
    //
    AcGePosition3d&  set        (const AcGePoint3d&);
    AcGePosition3d&  set        (double x, double y, double z );

    // Assignment operator.
    //
    AcGePosition3d& operator =  (const AcGePosition3d& pos);
};

#pragma pack (pop)
#endif
