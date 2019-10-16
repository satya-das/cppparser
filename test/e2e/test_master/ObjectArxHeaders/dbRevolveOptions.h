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
#ifndef DBREVOLVEOPTIONS_H
#  define DBREVOLVEOPTIONS_H
#  include "dbmain.h"
#  include "gepnt3d.h"
#  include "gevec3d.h"
#  pragma  pack(push, 8)
class AcDbRevolveOptions
{
public:
  AcDbRevolveOptions();
  AcDbRevolveOptions(const AcDbRevolveOptions& src);
  ~AcDbRevolveOptions();
  AcDbRevolveOptions& operator =(const AcDbRevolveOptions& src);
  double draftAngle() const;
  void setDraftAngle(double ang);
  double twistAngle() const;
  void setTwistAngle(double ang);
  bool closeToAxis() const;
  void setCloseToAxis(bool val);
  Acad::ErrorStatus checkRevolveCurve(AcDbEntity* pRevEnt, const AcGePoint3d& axisPnt, const AcGeVector3d& axisDir, bool& closed, bool& endPointsOnAxis, bool& planar, bool displayErrorMessages = false);
private:
  void* mpImpRevolveOptions;
  friend class AcDbImpRevolveOptions;
};
#  pragma  pack(pop)
#endif
