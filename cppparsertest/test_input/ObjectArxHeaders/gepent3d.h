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
// This file contains the class AcGePointEnt3d - An abstract base
// class to represent point entities.

#ifndef AC_GEPENT3D_H
#define AC_GEPENT3D_H

#include "adesk.h"
#include "geent3d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGePointEnt3d : public AcGeEntity3d
{
public:
    // Return point coordinates.
    //
    AcGePoint3d     point3d     () const;

    // Conversion operator to convert to AcGePoint3d.
    //
    operator        AcGePoint3d () const;

    // Assignment operator.
    //
    AcGePointEnt3d& operator =  (const AcGePointEnt3d& pnt);

protected:
    AcGePointEnt3d ();
    AcGePointEnt3d (const AcGePointEnt3d&);
};

#pragma pack (pop)
#endif
