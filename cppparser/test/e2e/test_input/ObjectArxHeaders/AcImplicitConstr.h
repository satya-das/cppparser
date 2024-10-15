//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#pragma once
#include "AcConstrainedGeometry.h"
#include "AcGeomConstraint.h"
#pragma pack (push, 8)

/// <summary>
/// This class represents a Perpendicular constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two lines.
/// </summary>
///
class ACDB_PORT AcPerpendicularConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcPerpendicularConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcPerpendicularConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Normal constraint node in the owning AcDbAssoc2dConstraintGroup.
/// Currently tt can only be applied between a line and circle(or arc).
/// </summary>
///
class ACDB_PORT AcNormalConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcNormalConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcNormalConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a PointCurve (coincident) constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a constrained point and a constrained curve.
/// </summary>
///
class ACDB_PORT AcPointCurveConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcPointCurveConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcPointCurveConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Colinear (coincident) constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained line.
/// </summary>
///
class ACDB_PORT AcColinearConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcColinearConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcColinearConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a PointCoincidence (coincident) constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained point.
/// </summary>
///
class ACDB_PORT AcPointCoincidenceConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcPointCoincidenceConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcPointCoincidenceConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Concentric constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two circles, arcs or ellipses.
/// </summary>
///
class ACDB_PORT AcConcentricConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConcentricConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcConcentricConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Concentric constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a point and a circle, arc or ellipse.
/// </summary>
///
class ACDB_PORT AcCenterPointConstraint: public AcConcentricConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcCenterPointConstraint);
};

/// <summary>
/// This class represents a Tangent constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained curve.
/// </summary>
///
class ACDB_PORT AcTangentConstraint : public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcTangentConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcTangentConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a EqualRadius constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained circles (arcs).
/// </summary>
///
class ACDB_PORT AcEqualRadiusConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcEqualRadiusConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualRadiusConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a EqualDistance constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two pairs of points.
/// </summary>
///
class ACDB_PORT AcEqualDistanceConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcEqualDistanceConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualDistanceConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a EqualLength constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained bounded lines (not rays).
/// </summary>
///
class ACDB_PORT AcEqualLengthConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcEqualLengthConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualLengthConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Parallel constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained lines.
/// </summary>
///
class ACDB_PORT AcParallelConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcParallelConstraint);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  /// <param name="bCreateImp">
  /// Input Boolean indicating whether the implementation object should be created.
  /// The default value is true.
  /// </param>
  ///
  AcParallelConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Horizontal constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied on one constrained line.
/// </summary>
///
class ACDB_PORT AcHorizontalConstraint: public AcParallelConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcHorizontalConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcHorizontalConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Vertical constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied on one constrained line.
/// </summary>
///
class ACDB_PORT AcVerticalConstraint: public AcParallelConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcVerticalConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcVerticalConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a EqualCurvature constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a bounded spline and a bounded curve.
/// </summary>
///
class ACDB_PORT AcEqualCurvatureConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcEqualCurvatureConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualCurvatureConstraint(bool bCreateImp = true);
};


/// <summary>
/// This class represents a Symmetric constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two same type of constrained geometries (except spline).
/// </summary>
///
class ACDB_PORT AcSymmetricConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcSymmetricConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcSymmetricConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a MidPoint constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a point and a bounded line (not ray) or arc.
/// </summary>
///
class ACDB_PORT AcMidPointConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcMidPointConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcMidPointConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Fixed constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied on any constrained geometry.
/// </summary>
///
class ACDB_PORT AcFixedConstraint : public AcGeomConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcFixedConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcFixedConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a EqualHelpParameter constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two AcHelpParameter objects which belong to the same spline or ellipse.
/// </summary>
///
class ACDB_PORT AcEqualHelpParameterConstraint : public AcGeomConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcEqualHelpParameterConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualHelpParameterConstraint(bool bCreateImp = true);

  /// <summary> 
  /// Returns pointers to the two AcHelpParameter objects which this constraint is connected to.
  /// </summary>
  /// <param name="pHelpParameter1"> 
  /// The returned pointer to the first AcHelpParameter object.
  /// </param>
  /// <param name="pHelpParameter2"> 
  /// The returned pointer to the second AcHelpParameter object.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getEqualHelpParameters(AcHelpParameter*& pHelpParameter1, AcHelpParameter*& pHelpParameter2) const;
};

/// <summary>
/// This class represents a G2Smooth composite constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a constrained bounded spline and other constrained bounded curve.
/// It is a combination of AcTangentConstraint and AcEqualCurvatureConstraint.
/// </summary>
///
class ACDB_PORT AcG2SmoothConstraint : public AcCompositeConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcG2SmoothConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcG2SmoothConstraint(bool bCreateImp = true);
};

#pragma pack (pop)
