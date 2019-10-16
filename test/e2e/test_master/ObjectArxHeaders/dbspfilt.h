//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBSPFILT_H
#  define AD_DBSPFILT_H
#  include "dbfilter.h"
#  include "gepnt2d.h"
#  include "gevec2d.h"
#  include "gept2dar.h"
#  pragma  pack (push, 8)
#  define ACDB_INFINITE_XCLIP_DEPTH	(1.0e+300)
class AcDbExtents;
class AcDbSpatialFilter : public AcDbFilter
{
  ACDB_DECLARE_MEMBERS(AcDbSpatialFilter);
public:
  AcDbSpatialFilter();
  virtual ~AcDbSpatialFilter();
  virtual AcRxClass* indexClass() const override;
  virtual void queryBounds(AcDbExtents& ext, const AcDbBlockReference* pRefBlkRef) const;
  AcDbSpatialFilter(const AcGePoint2dArray& pts, const AcGeVector3d& normal, double elevation, double frontClip, double backClip, Adesk::Boolean enabled);
  void queryBounds(AcDbExtents& ext) const;
  Acad::ErrorStatus getVolume(AcGePoint3d& fromPt, AcGePoint3d& toPt, AcGeVector3d& upDir, AcGeVector2d& viewField) const;
  Acad::ErrorStatus setDefinition(const AcGePoint2dArray& pts, const AcGeVector3d& normal, double elevation, double frontClip, double backClip, Adesk::Boolean enabled);
  Acad::ErrorStatus getDefinition(AcGePoint2dArray& pts, AcGeVector3d& normal, double& elevation, double& frontClip, double& backClip, Adesk::Boolean& enabled) const;
  AcGeMatrix3d& getClipSpaceToWCSMatrix(AcGeMatrix3d& mat) const;
  AcGeMatrix3d& getOriginalInverseBlockXform(AcGeMatrix3d& mat) const;
  Acad::ErrorStatus setPerspectiveCamera(const AcGePoint3d& fromPt);
  Adesk::Boolean clipVolumeIntersectsExtents(const AcDbExtents& ext) const;
  Adesk::Boolean hasPerspectiveCamera() const;
  ACDBCORE2D_PORT bool isInverted() const;
  ACDBCORE2D_PORT Acad::ErrorStatus setInverted(bool bInverted);
};
#  pragma  pack (pop)
#endif
