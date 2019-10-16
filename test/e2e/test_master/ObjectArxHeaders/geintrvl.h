//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEINTRVL_H
#  define AC_GEINTRVL_H
#  include "gegbl.h"
#  pragma  pack (push, 8)
class GE_DLLEXPIMPORT AcGeInterval
{
public:
  AcGeInterval(double tol = 1.e-12);
  AcGeInterval(const AcGeInterval& src);
  AcGeInterval(double lower, double upper, double tol = 1.e-12);
  AcGeInterval(Adesk::Boolean boundedBelow, double bound, double tol = 1.e-12);
  ~AcGeInterval();
  AcGeInterval& operator =(const AcGeInterval& otherInterval);
  double lowerBound() const;
  double upperBound() const;
  double element() const;
  void getBounds(double& lower, double& upper) const;
  double length() const;
  double tolerance() const;
  AcGeInterval& set(double lower, double upper);
  AcGeInterval& set(Adesk::Boolean boundedBelow, double bound);
  AcGeInterval& set();
  AcGeInterval& setUpper(double upper);
  AcGeInterval& setLower(double lower);
  AcGeInterval& setTolerance(double tol);
  void getMerge(const AcGeInterval& otherInterval, AcGeInterval& result) const;
  int subtract(const AcGeInterval& otherInterval, AcGeInterval& lInterval, AcGeInterval& rInterval) const;
  Adesk::Boolean intersectWith(const AcGeInterval& otherInterval, AcGeInterval& result) const;
  Adesk::Boolean isBounded() const;
  Adesk::Boolean isBoundedAbove() const;
  Adesk::Boolean isBoundedBelow() const;
  Adesk::Boolean isUnBounded() const;
  Adesk::Boolean isSingleton() const;
  Adesk::Boolean isDisjoint(const AcGeInterval& otherInterval) const;
  Adesk::Boolean contains(const AcGeInterval& otherInterval) const;
  Adesk::Boolean contains(double val) const;
  Adesk::Boolean isContinuousAtUpper(const AcGeInterval& otherInterval) const;
  Adesk::Boolean isOverlapAtUpper(const AcGeInterval& otherInterval, AcGeInterval& overlap) const;
  Adesk::Boolean operator ==(const AcGeInterval& otherInterval) const;
  Adesk::Boolean operator !=(const AcGeInterval& otherInterval) const;
  Adesk::Boolean isEqualAtUpper(const AcGeInterval& otherInterval) const;
  Adesk::Boolean isEqualAtUpper(double value) const;
  Adesk::Boolean isEqualAtLower(const AcGeInterval& otherInterval) const;
  Adesk::Boolean isEqualAtLower(double value) const;
  Adesk::Boolean isPeriodicallyOn(double period, double& val);
  GE_DLLEXPIMPORT friend Adesk::Boolean operator >(double val, const AcGeInterval& intrvl);
  Adesk::Boolean operator >(double val) const;
  Adesk::Boolean operator >(const AcGeInterval& otherInterval) const;
  GE_DLLEXPIMPORT friend Adesk::Boolean operator >=(double val, const AcGeInterval& intrvl);
  Adesk::Boolean operator >=(double val) const;
  Adesk::Boolean operator >=(const AcGeInterval& otherInterval) const;
  GE_DLLEXPIMPORT friend Adesk::Boolean operator <(double val, const AcGeInterval& intrvl);
  Adesk::Boolean operator <(double val) const;
  Adesk::Boolean operator <(const AcGeInterval& otherInterval) const;
  GE_DLLEXPIMPORT friend Adesk::Boolean operator <=(double val, const AcGeInterval& intrvl);
  Adesk::Boolean operator <=(double val) const;
  Adesk::Boolean operator <=(const AcGeInterval& otherInterval) const;
protected:
  friend class AcGeImpInterval;
  class AcGeImpInterval* mpImpInt;
  AcGeInterval(AcGeImpInterval&, int);
private:
  int mDelInt;
};
#  pragma  pack (pop)
#endif
