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
// Description: class  AcGeCurveCurveInt2d to hold data for intersectios
// of two 2d curves

#ifndef AC_GECINT2D_H
#define AC_GECINT2D_H

#include "adesk.h"
#include "gegbl.h"
#include "geent2d.h"
#include "geponc2d.h"
#include "geintrvl.h"
#pragma pack (push, 8)

class AcGeCurve2d;


class  
GE_DLLEXPIMPORT
AcGeCurveCurveInt2d : public AcGeEntity2d
{

public:
    // Constructors.
    //
    AcGeCurveCurveInt2d ();
    AcGeCurveCurveInt2d (const AcGeCurve2d& curve1, const AcGeCurve2d& curve2,
                         const AcGeTol& tol = AcGeContext::gTol );
    AcGeCurveCurveInt2d (const AcGeCurve2d& curve1, const AcGeCurve2d& curve2,
                         const AcGeInterval& range1, const AcGeInterval& range2,
                         const AcGeTol& tol = AcGeContext::gTol);
    AcGeCurveCurveInt2d (const AcGeCurveCurveInt2d& src);

    // General query functions.
    //
    const AcGeCurve2d  *curve1          () const;
    const AcGeCurve2d  *curve2          () const;
    void               getIntRanges     (AcGeInterval& range1,
                                         AcGeInterval& range2) const;
    AcGeTol            tolerance        () const;

    // Intersection query methods.
    //
    int                numIntPoints     () const;
    AcGePoint2d        intPoint         (int intNum) const;
    void               getIntParams     (int intNum,
                                         double& param1, double& param2) const;
    void               getPointOnCurve1 (int intNum, AcGePointOnCurve2d&) const;
    void               getPointOnCurve2 (int intNum, AcGePointOnCurve2d&) const;
    void			   getIntConfigs    (int intNum, AcGe::AcGeXConfig& config1wrt2, 
                                         AcGe::AcGeXConfig& config2wrt1) const;
    Adesk::Boolean     isTangential     (int intNum) const;
    Adesk::Boolean     isTransversal    (int intNum) const;
    double             intPointTol      (int intNum) const;
    int                overlapCount     () const;
	Adesk::Boolean	   overlapDirection () const;
    void               getOverlapRanges (int overlapNum,
                                         AcGeInterval& range1,
                                         AcGeInterval& range2) const;

    // Curves change their places
    //
    void               changeCurveOrder (); 
        
    // Order with respect to parameter on the first/second curve.
    //
    AcGeCurveCurveInt2d& orderWrt1  ();    
    AcGeCurveCurveInt2d& orderWrt2  ();
    
	// Set functions.
    //
    AcGeCurveCurveInt2d& set        (const AcGeCurve2d& curve1,
                                     const AcGeCurve2d& curve2,
                                     const AcGeTol& tol = AcGeContext::gTol);
    AcGeCurveCurveInt2d& set        (const AcGeCurve2d& curve1,
                                     const AcGeCurve2d& curve2,
                                     const AcGeInterval& range1,
                                     const AcGeInterval& range2,
                                     const AcGeTol& tol = AcGeContext::gTol);

    // Assignment operator.
    //
    AcGeCurveCurveInt2d& operator = (const AcGeCurveCurveInt2d& src);
};

#pragma pack (pop)
#endif
