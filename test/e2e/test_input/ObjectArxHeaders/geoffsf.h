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
// Description:
//
// This file contains the class AcGeOffsetSurface, a
// representation for an offset surface
//

#ifndef AC_GEOFFSF_H
#define AC_GEOFFSF_H

#include "gegbl.h"
#include "gepnt3d.h"
#include "gesurf.h"
#pragma pack (push, 8)

class AcGePlane;
class AcGeBoundedPlane;
class AcGeCylinder;
class AcGeCone;
class AcGeSphere;
class AcGeTorus;

class
GX_DLLEXPIMPORT
AcGeOffsetSurface : public AcGeSurface
{
public:
    AcGeOffsetSurface();
    AcGeOffsetSurface(AcGeSurface* baseSurface,
                      double offsetDist,
                      Adesk::Boolean makeCopy = Adesk::kTrue);
    AcGeOffsetSurface(const AcGeOffsetSurface& offset);

    // Test whether this offset surface can be converted to a simple surface
    //
    Adesk::Boolean    isPlane        () const;
    Adesk::Boolean    isBoundedPlane () const;
    Adesk::Boolean    isSphere       () const;
    Adesk::Boolean    isCylinder     () const;
    Adesk::Boolean    isCone         () const;
    Adesk::Boolean    isTorus        () const;

    // Convert this offset surface to a simple surface
    //
        Adesk::Boolean    getSurface(AcGeSurface*&) const;

    // Get a copy of the construction surface.
    //
    void              getConstructionSurface (AcGeSurface*& base) const;

    double            offsetDist     () const;

    // Reset surface
    //
    AcGeOffsetSurface& set        (AcGeSurface*, double offsetDist,
                                    Adesk::Boolean makeCopy = Adesk::kTrue);

    // Assignment operator.
    //
    AcGeOffsetSurface& operator =  (const AcGeOffsetSurface& offset);
};

#pragma pack (pop)
#endif
