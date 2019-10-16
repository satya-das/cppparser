//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_GECLIP2D_H
#  define AC_GECLIP2D_H
#  include "adesk.h"
#  include "assert.h"
#  include "geent2d.h"
#  include "gepnt2d.h"
#  include "gept2dar.h"
#  include "gegbl.h"
#  include "geintarr.h"
#  pragma  pack (push, 8)
class AcGeImpClipBoundary2d;
class GE_DLLEXPIMPORT AcGeClipBoundary2d : public AcGeEntity2d
{
public:
  AcGeClipBoundary2d();
  AcGeClipBoundary2d(const AcGePoint2d& cornerA, const AcGePoint2d& cornerB);
  AcGeClipBoundary2d(const AcGePoint2dArray& clipBoundary);
  AcGeClipBoundary2d(const AcGeClipBoundary2d& src);
  AcGe::ClipError set(const AcGePoint2d& cornerA, const AcGePoint2d& cornerB);
  AcGe::ClipError set(const AcGePoint2dArray& clipBoundary);
  AcGe::ClipError clipPolygon(const AcGePoint2dArray& rawVertices, AcGePoint2dArray& clippedVertices, AcGe::ClipCondition& clipCondition, AcGeIntArray* pClippedSegmentSourceLabel = 0) const;
  AcGe::ClipError clipPolyline(const AcGePoint2dArray& rawVertices, AcGePoint2dArray& clippedVertices, AcGe::ClipCondition& clipCondition, AcGeIntArray* pClippedSegmentSourceLabel = 0) const;
  AcGeClipBoundary2d& operator =(const AcGeClipBoundary2d& crvInt);
};
#  pragma  pack (pop)
#endif
