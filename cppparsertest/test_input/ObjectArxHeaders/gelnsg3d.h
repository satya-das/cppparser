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
// This file contains the class AcGeLineSeg3d - A mathematical entity
// used to represent linear segment in 3d space.

#ifndef AC_GELNSG3D_H
#define AC_GELNSG3D_H

#include "geline3d.h"
#include "geplane.h"
#pragma pack (push, 8)

class AcGeLineSeg2d;

class 
GE_DLLEXPIMPORT
AcGeLineSeg3d : public AcGeLinearEnt3d
{
public:
    AcGeLineSeg3d();
    AcGeLineSeg3d(const AcGeLineSeg3d& line);
    AcGeLineSeg3d(const AcGePoint3d& pnt, const AcGeVector3d& vec);
    AcGeLineSeg3d(const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);

    // Bisector.
    //
    void           getBisector  (AcGePlane& plane) const;

    // Barycentric combination of end points.
    //
    AcGePoint3d    baryComb     (double blendCoeff) const;

    // Definition of linear segment
    //
    AcGePoint3d    startPoint   () const;
    AcGePoint3d    midPoint     () const;
    AcGePoint3d    endPoint     () const;
    double         length       () const;
    double         length       (double fromParam, double toParam,
                                 double tol = AcGeContext::gTol.equalPoint()) const;
    // Set methods.
    //
    AcGeLineSeg3d& set          (const AcGePoint3d& pnt, const AcGeVector3d& vec);
    AcGeLineSeg3d& set          (const AcGePoint3d& pnt1, const AcGePoint3d& pnt2);
   	AcGeLineSeg3d& set          (const AcGeCurve3d& curve1,
                                 const AcGeCurve3d& curve2,
                                 double& param1, double& param2,
                                 Adesk::Boolean& success);
  	AcGeLineSeg3d& set          (const AcGeCurve3d& curve,
                                 const AcGePoint3d& point, double& param,
                                 Adesk::Boolean& success);


    // Assignment operator.
    //
    AcGeLineSeg3d& operator =   (const AcGeLineSeg3d& line);
};

#pragma pack (pop)
#endif
