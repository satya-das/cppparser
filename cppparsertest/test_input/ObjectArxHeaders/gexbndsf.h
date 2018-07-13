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
// This files implements the AcGeExternalBoundedSurface class,
// which is a representation of the geometry associated with a
// face entity.
//

#ifndef AC_GEXBNDSF_H
#define AC_GEXBNDSF_H

#include "gegbl.h"
#include "gesurf.h"
#pragma pack (push, 8)

class AcGeExternalSurface;
class AcGeCurveBoundary;

class
GX_DLLEXPIMPORT
AcGeExternalBoundedSurface : public AcGeSurface
{
public:
   AcGeExternalBoundedSurface();
   AcGeExternalBoundedSurface(void* surfaceDef, AcGe::ExternalEntityKind surfaceKind,
                              Adesk::Boolean makeCopy = Adesk::kTrue);
   AcGeExternalBoundedSurface(const AcGeExternalBoundedSurface&);

   // Surface data.
   //
   AcGe::ExternalEntityKind   externalSurfaceKind  () const;
   Adesk::Boolean             isDefined            () const;
   void                       getExternalSurface   (void*& surfaceDef) const;

    // Access to unbounded surface.
    //

    void getBaseSurface        (AcGeSurface*& surfaceDef) const;

	void getBaseSurface        (AcGeExternalSurface& unboundedSurfaceDef) const;

    // Type queries on the unbounded base surface.
    Adesk::Boolean isPlane() const;
    Adesk::Boolean isSphere() const;
    Adesk::Boolean isCylinder() const;
    Adesk::Boolean isCone() const;
    Adesk::Boolean isTorus() const;
    Adesk::Boolean isNurbs() const;
    Adesk::Boolean isExternalSurface() const;

         // Access to the boundary data.
    //
    int          numContours  () const;
    void         getContours  (int& numContours, AcGeCurveBoundary*& curveBoundaries) const;

    // Set methods
    //
    AcGeExternalBoundedSurface& set  (void* surfaceDef,
                                      AcGe::ExternalEntityKind surfaceKind,
                                      Adesk::Boolean makeCopy = Adesk::kTrue);

    // Assignment operator.
    //
    AcGeExternalBoundedSurface& operator = (const AcGeExternalBoundedSurface&);

    // Surface ownership.
    //
        Adesk::Boolean               isOwnerOfSurface() const;
    AcGeExternalBoundedSurface&  setToOwnSurface();
};

#pragma pack (pop)
#endif
