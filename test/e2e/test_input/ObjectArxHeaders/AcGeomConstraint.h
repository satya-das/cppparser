
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
#include "AcConstraintGroupNode.h"
#pragma pack (push, 8)

// Forward class declarations.
//
class AcConstrainedGeometry;
class AcHelpParameter;
class AcEqualHelpParameterConstraint;
class AcCompositeConstraint;


/// <summary>
/// This class represents a constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It is the base class for all the kind of constraints, including geometrical and 
/// dimensional constraints.
/// </summary>
///
class ACDB_PORT AcGeomConstraint : public AcConstraintGroupNode
{
public:
  ACRX_DECLARE_MEMBERS(AcGeomConstraint);

  /// <summary>
  /// The type of a geometrical constraint. It is mainly used to indicate the
  /// new constraint type to be added between geometries.
  /// </summary>
  ///
  enum GeomConstraintType
  {
    /// <summary>
    /// Horizontal constraint. Can be applied to a line or two points.
    /// </summary>
    ///
    kHorizontal    = 0,

    /// <summary>
    /// Vertical constraint. Can be applied to a line or two points.
    /// </summary> 
    ///
    kVertical         ,

    /// <summary>
    /// Parallel constraint. Can be applied between two lines.
    /// </summary> 
    ///
    kParallel         ,

    /// <summary>
    /// Perpendicular constraint. Can be applied between two lines.
    /// </summary> 
    ///
    kPerpendicular    ,

    /// <summary>
    /// Normal constraint. Currently can only be applied between a line and circle(or arc).
    /// </summary> 
    ///
    kNormal           ,

    /// <summary>
    /// Colinear constraint. Can be applied between two lines.
    /// </summary> 
    ///
    kColinear         ,

    /// <summary>
    /// Coincident constraint. Can be applied between two points, a point and a curve.
    /// </summary> 
    ///
    kCoincident       ,

    /// <summary>
    /// Concentric constraint. Can be applied between any two of circles, ellipses, arcs or bounded ellipses.
    /// </summary> 
    ///
    kConcentric       ,

    /// <summary>
    /// Tangent constraint. Can be applied between two of curves (except two lines).
    /// This constraint is not applicable for closed splines; for bounded splines, 
    /// the tangent point can only be the start or end point which is coincident with
    /// start or end point of the other bounded curve.
    /// </summary> 
    ///
    kTangent          ,

    /// <summary>
    /// EqualRadius constraint. Can be applied between any two of circles or arcs.
    /// </summary> 
    ///
    kEqualRadius      ,

    /// <summary>
    /// EqualLength constraint. Can be applied between two bounded lines (not rays).
    /// </summary> 
    ///
    kEqualLength      ,

    /// <summary>
    /// Symmetric constraint. Can be applied between two same type geometries.
    /// circle and arc are considered to be the same type of geometry.
    /// The symmetry axis is a line.
    /// </summary>
    ///
    kSymmetric		    ,

    /// <summary>
    /// G2Smooth constraint. Can be applied between a bounded spline and a bounded curve (including spline).
    /// </summary> 
    ///
    kG2Smooth         ,

    /// <summary>
    /// Fix constraint. Can be applied on any supported geometry.
    /// </summary>
    ///
    kFix			         
  };

  /// <summary> 
  /// Returns the array of pointer to AcConstrainedGeometry objects which this constraint is connected to.
  /// </summary>
  /// <param name="apConsGeoms"> 
  /// The returned array of pointer to AcConstrainedGeometry.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  virtual Acad::ErrorStatus getConnectedGeometries(AcArray<AcConstrainedGeometry*>& apConsGeoms) const;

  /// <summary><para>
  /// Returns the array of pointer to AcHelpParameter objects which this constraint is connected to.
  /// The number of the AcHelpParameter object is the same as the number of geometries involved
  /// in this constraint.
  /// </para><para>
  /// Only a few kind of constraints may have help parameters which are only applicable for
  /// splines and ellipses. For example, in case of Tangent constraint, a help parameter may be
  /// used to indicate the tangent point on a spline or ellipse.
  /// </para></summary>
  /// <param name="apHelpParameters"> 
  /// The returned array of pointer to AcHelpParameter objects.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  virtual Acad::ErrorStatus getConnectedHelpParameters(AcArray<AcHelpParameter*>& apHelpParameters) const;

  /// <summary><para> 
  /// Returns pointer to AcHelpParameter which this constraint and 
  /// the specified constrained geometry both are connected to.
  /// </para><para>
  /// A AcHelpParameter object is always connected with a AcGeomConstraint object
  /// and a AcConstrainedGeometry object.
  /// </para></summary>
  /// <param name="pConsGeom"> 
  /// The pointer to AcConstrainedGeometry object.
  /// </param>
  /// <returns> 
  /// Returns pointer to the connected AcHelpParameter object if successful,
  /// otherwise NULL is returned. 
  /// </returns>
  ///
  virtual AcHelpParameter*  getConnectedHelpParameterFor(const AcConstrainedGeometry* pConsGeom) const;

  /// <summary> 
  /// Returns the pointer to the owning AcCompositeConstraint object if 
  /// this constraint is owned by a composite constraint.
  /// </summary>
  /// <returns> Returns pointer to AcCompositeConstraint object. </returns>
  ///
  AcCompositeConstraint*    getOwningCompositeConstraint() const;

  /// <summary> <para>
  /// Leaves the AcGeomConstraint node in the AcDbAssoc2dConstraintGroup but 
  /// removes it from the DCM dimension system. 
  /// </para><para>
  /// Currently only implemented for AcExplicitConstraint because we need to
  /// temporarily deactivate them during grip-point editing of dimensional 
  /// constraint attachment grips.
  /// </para></summary>
  ///
  Acad::ErrorStatus deactivate();

  /// <summary><para>
  /// Takes an inactive AcGeomConstraint and adds it to the DCM dimension system. 
  /// </para><para>
  /// Currently only implemented for AcExplicitConstraint because we need to
  /// temporarily deactivate them during grip-point editing of dimensional 
  /// constraint attachment grips.
  /// </para></summary>
  ///
  Acad::ErrorStatus reactivate();

  /// <summary>
  /// Returns true iff the AcGeomConstraint is in DCM dimension system.
  /// </summary>
  ///
  bool isActive() const;

  /// <summary>
  /// Returns true iff the AcGeomConstraint is implied. This flag "implied"
  /// means the constraints are applied by the framework for implied geometric 
  /// conditions, such as end point constraints for bounded curve. In polyline,
  /// if any geometric constrains are applied to the segment(s), there would be
  /// a few implied point-point or point-curve constraints added by the 
  /// framework, these are implied constraints and the constraint UI 
  /// (constraint bar/icon) should not show these constraints.
  /// </summary>
  /// <returns> True if it is implied; false if not. </returns>
  ///
  bool isImplied() const;

  /// <summary>
  /// Sets the isImplied() flag. This method is not intended for public use.
  /// </summary>
  /// <param name="yesNo"> True if it is to be made implied; false if not. </param>
  ///
  void setIsImplied(bool yesNo);

  /// <summary>
  /// Returns true iff the constraint is implied or is part of a composite constraint.
  /// Internal constraints should not be directly dealt with at client-code level.
  /// </summary>
  /// <returns> True if it is internal; false if not. </returns>
  ///
  bool isInternal() const;

  /// <summary>
  /// Returns true iff the constraint is enabled
  /// </summary>
  /// <returns> True if it is enabled; false if not. </returns>
  ///
  bool isEnabled() const;

protected:

  /// <summary> Protected default constructor. </summary>
  /// 
  AcGeomConstraint();
};

/// <summary><para>
/// This class represents a help parameter node in the owning AcDbAssoc2dConstraintGroup.
/// Help parameters are only applicable for splines and ellipses and are required for some 
/// kind of constraints.
/// </para><para>
/// A AcHelpParameter object is always connected with a AcGeomConstraint object and
/// a AcConstrainedGeometry object.
/// </para></summary>
///
class ACDB_PORT AcHelpParameter : public AcConstraintGroupNode
{
public:
  ACRX_DECLARE_MEMBERS(AcHelpParameter);

  /// <summary> default constructor. </summary>
  /// 
  AcHelpParameter(bool bCreateImp = true);

  /// <summary> 
  /// Returns the pointer to AcConstrainedGeometry which this help parameter is connected to.
  /// </summary>
  /// <param name="pGeometry"> 
  /// The returned pointer to AcConstrainedGeometry.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getConnectedGeometry(AcConstrainedGeometry*& pGeometry) const;

  /// <summary> 
  /// Returns the pointer to AcGeomConstraint which this help parameter is connected to.
  /// This method does not take in account of equal parameter constraints applied on this help parameter
  /// </summary>
  /// <param name="pConstraint"> 
  /// The returned pointer to AcGeomConstraint.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getConnectedConstraint(AcGeomConstraint*& pConstraint) const;

  /// <summary>
  /// Returns the array of pointer to AcEqualHelpParameterConstraint object which this constraint
  /// is connected to.
  /// </summary>
  /// <param name="apEqualParamConstrs"> 
  /// The returned array of pointer to AcEqualHelpParameterConstraint. If this help parameter
  /// is not involved in any equal help parameter constraint, the array returned is empty.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getConnectedEqualparamConstraints(AcArray<AcEqualHelpParameterConstraint*>& apEqualParamConstrs) const;

  /// <summary>
  /// Returns the value of this help parameter, the value is always larger than or equal to 0.0
  /// </summary>
  /// <returns> Returns double parameter value. </returns>
  ///
  double getValue() const;
};

/// <summary>
/// This class represents a composite constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It is the base class for all the kind of composite constraints, the owned constraints are 
/// all applied on(connected with) the same constrained geometries.
/// </summary>
///
class ACDB_PORT AcCompositeConstraint : public AcGeomConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcCompositeConstraint);

  /// <summary>
  /// Returns the array of pointer to AcGeomConstraint objects which are 
  /// owned by this composite constraint.
  /// </summary>
  /// <param name="apSubConstraints"> 
  /// The returned array of pointer to AcGeomConstraint objects. 
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getOwnedConstraints(AcArray<AcGeomConstraint*>& apSubConstraints) const;

protected:

  /// <summary> Protected default constructor. </summary>
  /// 
  AcCompositeConstraint(){}
};

#pragma pack (pop)
