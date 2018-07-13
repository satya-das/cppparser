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
// This file contains the class AcGeLinSeg2d - A mathematical entity
// used to represent a 2d line segment

#ifndef AC_GELNSG2D_H
#define AC_GELNSG2D_H

#include "geline2d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeLineSeg2d : public AcGeLinearEnt2d
{
public:
    AcGeLineSeg2d();
    AcGeLineSeg2d(const AcGeLineSeg2d& line);
    AcGeLineSeg2d(const AcGePoint2d& pnt1, const AcGePoint2d& pnt2);
    AcGeLineSeg2d(const AcGePoint2d& pnt, const AcGeVector2d& vec);

    // Set methods.
    //
    AcGeLineSeg2d& set(const AcGePoint2d& pnt, const AcGeVector2d& vec);
    AcGeLineSeg2d& set(const AcGePoint2d& pnt1, const AcGePoint2d& pnt2);
    AcGeLineSeg2d& set(const AcGeCurve2d& curve1,
                       const AcGeCurve2d& curve2,
                       double& param1, double& param2,
                       Adesk::Boolean& success);
    AcGeLineSeg2d& set(const AcGeCurve2d& curve, const AcGePoint2d& point,
                       double& param, Adesk::Boolean& success);


    // Bisector.
    //
    void           getBisector(AcGeLine2d& line) const;

    // Barycentric combination of end points.
    //
    AcGePoint2d    baryComb   (double blendCoeff) const;

    // Definition of linear segment
    //
    AcGePoint2d    startPoint   () const;
    AcGePoint2d    midPoint     () const;
    AcGePoint2d    endPoint     () const;
    double         length       () const;
    double         length       (double fromParam, double toParam,
                                 double tol = AcGeContext::gTol.equalPoint())
                                const;
    // Assignment operator.
    //
    AcGeLineSeg2d& operator =  (const AcGeLineSeg2d& line);
};

#pragma pack (pop)
#endif
