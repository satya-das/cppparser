//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GEASSIGN_H
#  define AC_GEASSIGN_H
#  pragma  pack (push, 8)
class AcGePoint2d;
class AcGeVector2d;
class AcGePoint3d;
class AcGeVector3d;
inline AcGePoint2d& asPnt2d(const double* pnt)
{
  return *((AcGePoint2d*) pnt);
}
inline AcGeVector2d& asVec2d(const double* vec)
{
  return *((AcGeVector2d*) vec);
}
#  ifdef __clang__
#    pragma  clang diagnostic push
#    pragma  clang diagnostic ignored "-Wcast-align"
#  endif
inline double* asDblArray(const AcGePoint2d& pnt)
{
  return (double*) &pnt;
}
inline double* asDblArray(const AcGeVector2d& vec)
{
  return (double*) &vec;
}
#  ifdef __clang__
#    pragma  clang diagnostic pop
#  endif
inline AcGePoint3d& asPnt3d(const double* pnt)
{
  return *((AcGePoint3d*) pnt);
}
inline AcGeVector3d& asVec3d(const double* vec)
{
  return *((AcGeVector3d*) vec);
}
#  ifdef __clang__
#    pragma  clang diagnostic push
#    pragma  clang diagnostic ignored "-Wcast-align"
#  endif
inline double* asDblArray(const AcGePoint3d& pnt)
{
  return (double*) &pnt;
}
inline double* asDblArray(const AcGeVector3d& vec)
{
  return (double*) &vec;
}
#  ifdef __clang__
#    pragma  clang diagnostic pop
#  endif
#  pragma  pack (pop)
#endif
