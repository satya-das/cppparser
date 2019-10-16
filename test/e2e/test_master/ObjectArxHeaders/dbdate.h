//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  dbdate.h
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBDATE_H
#  define AD_DBDATE_H
#  include <ctime>
#  include "acdb.h"
#  include "acadstrc.h"
#  include "AcDbCore2dDefs.h"
#  include "acdbport.h"
#  pragma  pack(push, 8)
class AcDbDwgFiler;
class AcString;
typedef struct _SYSTEMTIME SYSTEMTIME;
class AcDbDate
{
public:
  enum InitialValue
  {
    kInitZero = 1,
    kInitLocalTime = 2,
    kInitUniversalTime = 3
  };
  AcDbDate();
  AcDbDate(InitialValue i);
  AcDbDate(const AcDbDate&);
  virtual ~AcDbDate();
  const AcDbDate& operator=(const AcDbDate&);
  void getDate(short& month, short& day, short& year) const;
  ACDBCORE2D_PORT AcString getLocalDisplayString() const;
  ACDBCORE2D_PORT void setDate(int month, int day, int year);
  short month() const;
  short day() const;
  short year() const;
  ACDBCORE2D_PORT void setMonth(int);
  ACDBCORE2D_PORT void setDay(int);
  ACDBCORE2D_PORT void setYear(int);
  ACDB_PORT void getTime(SYSTEMTIME& st) const;
  void getTime(std::tm& st) const;
  ACDBCORE2D_PORT void setTime(const std::tm& st);
  void getTime(time_t& st) const;
  ACDB_PORT void setTime(const SYSTEMTIME& st);
  void getTime(short& hour, short& min, short& sec, short& msec) const;
  ACDBCORE2D_PORT void setTime(int hour, int min, int sec, int msec);
  int getApproximateTime() const;
  void setApproximateTime(int time);
  short hour() const;
  short minute() const;
  short second() const;
  short millisecond() const;
  ACDBCORE2D_PORT void setHour(int);
  ACDBCORE2D_PORT void setMinute(int);
  ACDBCORE2D_PORT void setSecond(int);
  ACDBCORE2D_PORT void setMillisecond(int);
  void setToZero();
  void getLocalTime();
  void getUniversalTime();
  void localToUniversal();
  void universalToLocal();
  Adesk::Int32 julianDay() const;
  Adesk::Int32 msecsPastMidnight() const;
  void setJulianDay(Adesk::Int32 julianDay);
  void setMsecsPastMidnight(Adesk::Int32 msec);
  void setJulianDate(Adesk::Int32 julianDay, Adesk::Int32 msec);
  double julianFraction() const;
  void setJulianFraction(double);
  bool operator==(const AcDbDate&) const;
  bool operator >(const AcDbDate&) const;
  bool operator >=(const AcDbDate&) const;
  bool operator <(const AcDbDate&) const;
  bool operator <=(const AcDbDate&) const;
  const AcDbDate operator +(const AcDbDate& date) const;
  const AcDbDate operator -(const AcDbDate& date) const;
  const AcDbDate& operator +=(const AcDbDate& date);
  const AcDbDate& operator -=(const AcDbDate& date);
  const AcDbDate& add(const AcDbDate& date);
  const AcDbDate& subtract(const AcDbDate& date);
  Acad::ErrorStatus dwgOut(AcDbDwgFiler* outFiler) const;
  Acad::ErrorStatus dwgIn(AcDbDwgFiler* inFiler);
private:
  friend class AcDbImpDate;
  class AcDbImpDate* mpImpDate;
};
inline const AcDbDate AcDbDate::operator +(const AcDbDate& d) const
{
  return AcDbDate(*this) += d;
}
inline const AcDbDate AcDbDate::operator -(const AcDbDate& d) const
{
  return AcDbDate(*this) -= d;
}
inline bool AcDbDate::operator <(const AcDbDate& d) const
{
  return !operator >=(d);
}
inline bool AcDbDate::operator <=(const AcDbDate& d) const
{
  return !operator >(d);
}
inline const AcDbDate& AcDbDate::add(const AcDbDate& date)
{
  return operator +=(date);
}
inline const AcDbDate& AcDbDate::subtract(const AcDbDate& date)
{
  return operator -=(date);
}
#  pragma  pack(pop)
#endif
