//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#ifndef DBSWEEPOPTIONS_H
#  define DBSWEEPOPTIONS_H
#  include "dbmain.h"
#  include "dbsubeid.h"
#  include "gepnt3d.h"
#  include "gevec3d.h"
#  pragma  pack(push, 8)
class AcDbSweepOptions
{
public:
  AcDbSweepOptions();
  AcDbSweepOptions(const AcDbSweepOptions& src);
  ~AcDbSweepOptions();
  AcDbSweepOptions& operator =(const AcDbSweepOptions& src);
  bool operator ==(const AcDbSweepOptions&) const;
  enum AlignOption
  {
    kNoAlignment,
    kAlignSweepEntityToPath,
    kTranslateSweepEntityToPath,
    kTranslatePathToSweepEntity
  };
  enum MiterOption
  {
    kDefaultMiter,
    kOldMiter,
    kNewMiter,
    kCrimpMiter,
    kBendMiter
  };
  double draftAngle() const;
  void setDraftAngle(double ang);
  double startDraftDist() const;
  void setStartDraftDist(double val);
  double endDraftDist() const;
  void setEndDraftDist(double val);
  double twistAngle() const;
  void setTwistAngle(double ang);
  double scaleFactor() const;
  void setScaleFactor(double val);
  double alignAngle() const;
  void setAlignAngle(double ang);
  AcDbSweepOptions::AlignOption align() const;
  void setAlign(AcDbSweepOptions::AlignOption val);
  AcDbSweepOptions::MiterOption miterOption() const;
  void setMiterOption(AcDbSweepOptions::MiterOption val);
  bool alignStart() const;
  void setAlignStart(bool val);
  AcGePoint3d basePoint() const;
  void setBasePoint(AcGePoint3d& pnt);
  bool bank() const;
  void setBank(bool val);
  bool checkIntersections() const;
  void setCheckIntersections(bool val);
  AcGeVector3d twistRefVec() const;
  void setTwistRefVec(const AcGeVector3d& vec);
  bool getSweepEntityTransform(AcGeMatrix3d& mat);
  void setSweepEntityTransform(AcGeMatrix3d& mat);
  Acad::ErrorStatus setSweepEntityTransform(AcArray<AcDbEntity*>& sweepEntities, bool displayErrorMessages = false);
  bool getPathEntityTransform(AcGeMatrix3d& mat);
  void setPathEntityTransform(AcGeMatrix3d& mat);
  Acad::ErrorStatus setPathEntityTransform(AcDbEntity* pPathEnt, bool displayErrorMessages = false);
  Acad::ErrorStatus checkSweepCurve(AcDbEntity* pSweepEnt, AcDb::Planarity& planarity, AcGePoint3d& pnt, AcGeVector3d& vec, bool& closed, double& approxArcLen, bool displayErrorMessages = false);
  Acad::ErrorStatus checkPathCurve(AcDbEntity* pPathEnt, bool displayErrorMessages = false);
private:
  void* mpImpSweepOptions;
  friend class AcDbImpSweepOptions;
};
#  pragma  pack(pop)
#endif
