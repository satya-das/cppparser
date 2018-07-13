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
// This file contains the class AcGeExternalCurve2d - A
// representation for a curve that has its definition external to
// gelib.

#ifndef AC_GEEXTC2D_H
#define AC_GEEXTC2D_H

#include "gecurv2d.h"
#include "gearc2d.h"
#include "gevec2d.h"
#include "gepnt2d.h"
#pragma pack (push, 8)

class AcGeNurbCurve2d;
class AcGeExternalCurve2d;
class AcGeExternalCurve2d;

class
GX_DLLEXPIMPORT
AcGeExternalCurve2d : public AcGeCurve2d
{
public:
    AcGeExternalCurve2d();
    AcGeExternalCurve2d(const AcGeExternalCurve2d&);
    AcGeExternalCurve2d(void* curveDef, AcGe::ExternalEntityKind curveKind,
                        Adesk::Boolean makeCopy = Adesk::kTrue);

    Adesk::Boolean isNurbCurve() const;
    Adesk::Boolean isNurbCurve(AcGeNurbCurve2d& nurbCurve) const;
    Adesk::Boolean isDefined  () const;

    void           getExternalCurve(void*& curveDef) const;

    // Type of the external curve.
    //
    AcGe::ExternalEntityKind externalCurveKind() const;

    // Reset surface
    //
    AcGeExternalCurve2d& set(void* curveDef, AcGe::ExternalEntityKind curveKind,
                             Adesk::Boolean makeCopy = Adesk::kTrue);
    // Assignment operator
    //
    AcGeExternalCurve2d& operator = (const AcGeExternalCurve2d& src);

    // Ownership of curve
    //
    Adesk::Boolean       isOwnerOfCurve() const;
    AcGeExternalCurve2d& setToOwnCurve();
};

#pragma pack (pop)
#endif
