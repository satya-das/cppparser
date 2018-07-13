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
// This file contains the class AcGeRay2d - A mathematical entity
// used to represent a ray (half line) in 2-space.

#ifndef AC_GERAY2D_H
#define AC_GERAY2D_H

#include "gelent2d.h"
#pragma pack (push, 8)

class 
GE_DLLEXPIMPORT
AcGeRay2d : public AcGeLinearEnt2d
{
public:
    AcGeRay2d();
    AcGeRay2d(const AcGeRay2d& line);
    AcGeRay2d(const AcGePoint2d& pnt, const AcGeVector2d& vec);
    AcGeRay2d(const AcGePoint2d& pnt1, const AcGePoint2d& pnt2);

    // Set methods.
    //
    AcGeRay2d&     set         (const AcGePoint2d& pnt, const AcGeVector2d& vec);
    AcGeRay2d&     set         (const AcGePoint2d& pnt1, const AcGePoint2d& pnt2);

    // Assignment operator.
    //
    AcGeRay2d&     operator =  (const AcGeRay2d& line);
};

#pragma pack (pop)
#endif
