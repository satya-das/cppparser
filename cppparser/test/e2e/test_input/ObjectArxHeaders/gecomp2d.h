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
// This file contains the class AcGeCompositeCurve2d - A mathematical
// entity used to represent a composite curve. Curve is parametrized 
// by Ravi-parametrization: that is n-th segment is parametrized by
// interval [ n, n + 1 ];

#ifndef AC_GECOMP2D_H
#define AC_GECOMP2D_H

#include "gecurv2d.h"
#include "gevptar.h"
#include "geintarr.h"
#pragma pack (push, 8)

class 
GE_DLLEXPIMPORT
AcGeCompositeCurve2d : public AcGeCurve2d
{
public:
    AcGeCompositeCurve2d  ();
    AcGeCompositeCurve2d  (const AcGeVoidPointerArray& curveList);
    AcGeCompositeCurve2d  (const AcGeVoidPointerArray& curveList,
		                   const AcGeIntArray& isOwnerOfCurves);
    AcGeCompositeCurve2d  (const AcGeCompositeCurve2d& compCurve);

    // Definition of trimmed curve
    //
    void		          getCurveList       (AcGeVoidPointerArray& curveList) const;

    // Set methods
    //
    AcGeCompositeCurve2d& setCurveList       (const AcGeVoidPointerArray& curveList);
    AcGeCompositeCurve2d& setCurveList       (const AcGeVoidPointerArray& curveList,
		                                      const AcGeIntArray& isOwnerOfCurves);
	
	// Convert parameter on composite to parameter on component curve and vice-versa.
	//
	double				  globalToLocalParam ( double param, int& crvNum ) const; 
	double				  localToGlobalParam ( double param, int crvNum ) const; 

    // Assignment operator.
    //
    AcGeCompositeCurve2d& operator =         (const AcGeCompositeCurve2d& compCurve);
};

#pragma pack (pop)
#endif
