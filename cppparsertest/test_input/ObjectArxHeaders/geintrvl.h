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
// This file contains the class AcGeInterval - a representation
// for an interval on the real line.  The following kinds of intervals
// are supported.
// . Open intervals where the bounds are not finite.
// . Closed intervals with finite bounds.
// . Half intervals such that one end is open and not finite,
//   and the other is closed and finite.
//
// Where applicable, all evaluations are performed within the
// tolerance stored within this class.

#ifndef AC_GEINTRVL_H
#define AC_GEINTRVL_H

#include "gegbl.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeInterval
{
public:
    AcGeInterval(double tol = 1.e-12);
    AcGeInterval(const AcGeInterval& src);
    AcGeInterval(double lower, double upper, double tol = 1.e-12);
    AcGeInterval(Adesk::Boolean boundedBelow, double bound,
                 double tol = 1.e-12);
    ~AcGeInterval();

    // Assignment operator.
    //
    AcGeInterval&  operator =       (const AcGeInterval& otherInterval);

    // Get/set methods.
    //
    double         lowerBound       () const;
    double         upperBound       () const;
    double         element          () const;
    void           getBounds        (double& lower, double& upper) const;
    double         length           () const;
    double         tolerance        () const;

    AcGeInterval&  set              (double lower, double upper);
    AcGeInterval&  set              (Adesk::Boolean boundedBelow, double bound);
    AcGeInterval&  set              ();
    AcGeInterval&  setUpper         (double upper);
    AcGeInterval&  setLower         (double lower);
    AcGeInterval&  setTolerance     (double tol);

    // Interval editing.
    //
    void           getMerge         (const AcGeInterval& otherInterval, AcGeInterval& result) const;
    int            subtract         (const AcGeInterval& otherInterval,
                                     AcGeInterval& lInterval,
                                     AcGeInterval& rInterval) const;
    Adesk::Boolean intersectWith    (const AcGeInterval& otherInterval, AcGeInterval& result) const;

    // Interval characterization.
    //
    Adesk::Boolean isBounded        () const;
    Adesk::Boolean isBoundedAbove   () const;
    Adesk::Boolean isBoundedBelow   () const;
    Adesk::Boolean isUnBounded      () const;
    Adesk::Boolean isSingleton      () const;

    // Relation to other intervals.
    //
    Adesk::Boolean isDisjoint       (const AcGeInterval& otherInterval) const;
    Adesk::Boolean contains         (const AcGeInterval& otherInterval) const;
    Adesk::Boolean contains         (double val) const;

    // Continuity
    //
    Adesk::Boolean isContinuousAtUpper (const AcGeInterval& otherInterval) const;
    Adesk::Boolean isOverlapAtUpper    (const AcGeInterval& otherInterval,
                                        AcGeInterval& overlap) const;
    // Equality
    //
    Adesk::Boolean operator ==      (const AcGeInterval& otherInterval) const;
    Adesk::Boolean operator !=      (const AcGeInterval& otherInterval) const;
    Adesk::Boolean isEqualAtUpper   (const AcGeInterval& otherInterval) const;
    Adesk::Boolean isEqualAtUpper   (double value) const;
    Adesk::Boolean isEqualAtLower   (const AcGeInterval& otherInterval) const;
    Adesk::Boolean isEqualAtLower   (double value) const;

    // To be used with periodic curves
    //
    Adesk::Boolean isPeriodicallyOn (double period, double& val);

    // Comparisons.
    //
    friend
    GE_DLLEXPIMPORT
    Adesk::Boolean operator >       (double val, const AcGeInterval& intrvl);
    Adesk::Boolean operator >       (double val) const;
    Adesk::Boolean operator >       (const AcGeInterval& otherInterval) const;
    friend
    GE_DLLEXPIMPORT
    Adesk::Boolean operator >=      (double val, const AcGeInterval& intrvl);
    Adesk::Boolean operator >=      (double val) const;
    Adesk::Boolean operator >=      (const AcGeInterval& otherInterval) const;
    friend
    GE_DLLEXPIMPORT
    Adesk::Boolean operator <       (double val, const AcGeInterval& intrvl);
    Adesk::Boolean operator <       (double val) const;
    Adesk::Boolean operator <       (const AcGeInterval& otherInterval) const;
    friend
    GE_DLLEXPIMPORT
    Adesk::Boolean operator <=      (double val, const AcGeInterval& intrvl);
    Adesk::Boolean operator <=      (double val) const;
    Adesk::Boolean operator <=      (const AcGeInterval& otherInterval) const;

protected:
    friend class AcGeImpInterval;

    class AcGeImpInterval  *mpImpInt;

    // Construct object from its corresponding implementation object.
    AcGeInterval (AcGeImpInterval&, int);

private:
    int              mDelInt;
};

#pragma pack (pop)
#endif
