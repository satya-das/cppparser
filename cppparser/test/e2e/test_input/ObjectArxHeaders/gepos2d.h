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
// This file contains the class AcGePosition2d - A 2d point entity.

#ifndef AC_GEPOS2D_H
#define AC_GEPOS2D_H

#include "adesk.h"
#include "gepent2d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGePosition2d : public AcGePointEnt2d
{
public:
    AcGePosition2d ();
    AcGePosition2d (const AcGePoint2d& pnt);
    AcGePosition2d (double x, double y);
    AcGePosition2d (const AcGePosition2d& pos);

    // Set point coordinates.
    //
    AcGePosition2d&  set        (const AcGePoint2d&);
    AcGePosition2d&  set        (double x, double y );

    // Assignment operator.
    //
    AcGePosition2d& operator =  (const AcGePosition2d& pos);
};

#pragma pack (pop)
#endif
