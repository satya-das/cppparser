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
// The AcDbRegion class is the interface class for representing
// regions inside AutoCAD.  All the functionality supported by
// this class is implemented in the class AcDbImpRegion and its
// base classes.
#ifndef GEOMENT_DBREGION_H
#  define GEOMENT_DBREGION_H
#  include "dbmain.h"
#  include "dbsubeid.h"
#  include "gepnt3d.h"
#  include "gevec3d.h"
#  pragma  pack(push, 8)
class AcDbRegion : public AcDbEntity
{
public:
  AcDbRegion();
  virtual ~AcDbRegion();
  ACDB_DECLARE_MEMBERS(AcDbRegion);
  static Acad::ErrorStatus createFromCurves(const AcDbVoidPtrArray& curveSegments, AcDbVoidPtrArray& regions);
  virtual Acad::ErrorStatus getPerimeter(double&) const;
  virtual Acad::ErrorStatus getArea(double& regionArea) const;
  virtual void* ASMBodyCopy(bool bDeepCopy = false) const;
  virtual const void* getLockedASMBody();
  virtual void unlockASMBody();
  virtual void* getLockedWritableASMBody();
  virtual void commitWritableASMBody();
  virtual Acad::ErrorStatus setASMBody(const void* modelerBody);
  virtual Acad::ErrorStatus getAreaProp(const AcGePoint3d& origin, const AcGeVector3d& xAxis, const AcGeVector3d& yAxis, double& perimeter, double& area, AcGePoint2d& centroid, double momInertia[2], double& prodInertia, double prinMoments[2], AcGeVector2d prinAxes[2], double radiiGyration[2], AcGePoint2d& extentsLow, AcGePoint2d& extentsHigh) const;
  virtual Acad::ErrorStatus getPlane(AcGePlane& regionPlane) const;
  ACDB_PORT void dragStatus(const AcDb::DragStat) override;
  virtual Adesk::Boolean isNull() const;
  virtual Acad::ErrorStatus getNormal(AcGeVector3d&) const;
  virtual AcDbSubentId internalSubentId(void* ent) const;
  virtual void* internalSubentPtr(const AcDbSubentId& id) const;
  virtual Acad::ErrorStatus booleanOper(AcDb::BoolOperType operation, AcDbRegion* otherRegion);
  virtual Adesk::UInt32 numChanges() const;
  ACDB_PORT virtual bool usesGraphicsCache();
protected:
  Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
#  pragma  pack(pop)
#endif
