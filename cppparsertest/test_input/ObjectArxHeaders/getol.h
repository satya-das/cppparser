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
// This file contains the functionality for managing tolerances within
// gelib.
//
// This is an instantiable class that is initialized to the default
// tolerances.  Subsequently, the tolerances within it can be customized
// to suite a specific need.  For example, an instance of this class
// may be specialized to be utilized during surface intersection.
//
// DESCRIPTION
//
// 1. Two points p1 and p2 are equal if and only if
//
//           (p1 - p2).length() <= equalPoint
//
// 2. Two vectors v1 and v2 are equal if and only if
//
//           (v1 - v2).length() <= equalVector
//
// 3. Two vectors v1 and v2 are parallel if and only if
//
//         ( v1/v1.length() - v2/v2.length() ).length() < equalVector
//     OR  ( v1/v1.length() + v2/v2.length() ).length() < equalVector
//
// 4. Two vectors v1 and v2 are perpendicular if and only if
//
//       abs((v1.dotProduct(v2))/(v1.length()*v2.length())) <= equalVector
//
// 5. Two lines or rays are parallel (perpendicular) if and only if
//    their directional vectors are parallel (perpendicular)
//
// 6. Two lines are equal if and only if they have points within equalPoint
//    and they are parallel.
//
// IMPORTANT: These rules mean that two lines are close to each other as
//            point sets in the part of the modeling space of diameter
//            DIAM, if only the tolerance equalVector is set tighter than
//            equalPoint/DIAM

#ifndef AC_GETOL_H
#define AC_GETOL_H

#ifndef unix
#include <stdlib.h>
#endif
#include "gedll.h"
#include "gedblar.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeTol {
public:
    AcGeTol();

    // Inquiry functions.
    //
    double  equalPoint          () const;
    double  equalVector         () const;

    // Set functions.
    //
    void    setEqualPoint       ( double val );
    void    setEqualVector      ( double val );

private:
    double				mTolArr[5];
    int                 mAbs;

    friend class AcGeTolA;
};

// Inlines for AcGeTol
//

inline void AcGeTol::setEqualVector( double val )
    { mTolArr[1] = val; }

inline double AcGeTol::equalVector() const
    { return mTolArr[1]; }

inline void AcGeTol::setEqualPoint( double val )
    { mTolArr[0] = val; }

inline double AcGeTol::equalPoint() const
    { return mTolArr[0]; }

#pragma pack (pop)
#endif
