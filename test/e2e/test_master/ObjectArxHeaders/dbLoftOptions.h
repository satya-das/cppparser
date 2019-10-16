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
#ifndef DBLOFTOPTIONS_H
#  define DBLOFTOPTIONS_H
#  include "dbmain.h"
#  include "dbsubeid.h"
#  include "gepnt3d.h"
#  include "gevec3d.h"
#  pragma  pack(push, 8)
class AcDbLoftOptions
{
public:
  AcDbLoftOptions();
  AcDbLoftOptions(const AcDbLoftOptions& src);
  ~AcDbLoftOptions();
  AcDbLoftOptions& operator =(const AcDbLoftOptions& src);
  bool operator ==(const AcDbLoftOptions&) const;
  enum NormalOption
  {
    kNoNormal,
    kFirstNormal,
    kLastNormal,
    kEndsNormal,
    kAllNormal,
    kUseDraftAngles
  };
  double draftStart() const;
  void setDraftStart(double ang);
  double draftEnd() const;
  void setDraftEnd(double ang);
  double draftStartMag() const;
  void setDraftStartMag(double val);
  double draftEndMag() const;
  void setDraftEndMag(double val);
  bool arcLengthParam() const;
  void setArcLengthParam(bool val);
  bool noTwist() const;
  void setNoTwist(bool val);
  bool alignDirection() const;
  void setAlignDirection(bool val);
  bool simplify() const;
  void setSimplify(bool val);
  bool closed() const;
  void setClosed(bool val);
  bool periodic() const;
  void setPeriodic(bool val);
  bool ruled() const;
  void setRuled(bool val);
  bool virtualGuide() const;
  void setVirtualGuide(bool val);
  AcDbLoftOptions::NormalOption normal() const;
  void setNormal(AcDbLoftOptions::NormalOption val);
  Acad::ErrorStatus setOptionsFromSysvars();
  Acad::ErrorStatus setSysvarsFromOptions();
  Acad::ErrorStatus checkOptions(bool displayErrorMessages = false);
  Acad::ErrorStatus checkLoftCurves(AcArray<AcDbEntity*>& crossSectionCurves, AcArray<AcDbEntity*>& guideCurves, AcDbEntity* pPathCurve, bool& allOpen, bool& allClosed, bool& allPlanar, bool displayErrorMessages = false);
  Acad::ErrorStatus checkCrossSectionCurves(AcArray<AcDbEntity*>& crossSectionCurves, bool& allOpen, bool& allClosed, bool& allPlanar, bool displayErrorMessages = false);
  Acad::ErrorStatus checkGuideCurves(AcArray<AcDbEntity*>& guideCurves, bool displayErrorMessages = false);
  Acad::ErrorStatus checkPathCurve(AcDbEntity* pPathCurve, bool displayErrorMessages = false);
private:
  void* mpImpLoftOptions;
  friend class AcDbImpLoftOptions;
};
#  pragma  pack(pop)
#endif
